#include "SG_PDF2TXT.h"

#include <aconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#ifdef DEBUG_FP_LINUX
#  include <fenv.h>
#  include <fpu_control.h>
#endif
#include "gmem.h"
#include "gmempp.h"
#include "parseargs.h"
#include "GString.h"
#include "GList.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Stream.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "Catalog.h"
#include "Page.h"
#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "CharTypes.h"
#include "UnicodeMap.h"
#include "TextString.h"
#include "Error.h"
#include "config.h"

static int firstPage = 1;
static int lastPage = 0;
static GBool physLayout = gFalse;
static GBool simpleLayout = gFalse;
static GBool simple2Layout = gFalse;
static GBool tableLayout = gFalse;
static GBool linePrinter = gFalse;
static GBool rawOrder = gFalse;
static double fixedPitch = 0;
static double fixedLineSpacing = 0;
static GBool clipText = gFalse;
static GBool discardDiag = gFalse;
static char textEncName[128] = "";
static char textEOL[16] = "";
static GBool noPageBreaks = gFalse;
static GBool insertBOM = gFalse;
static double marginLeft = 0;
static double marginRight = 0;
static double marginTop = 0;
static double marginBottom = 0;
static char ownerPassword[33] = "\001";
static char userPassword[33] = "\001";
static GBool quiet = gFalse;
static char cfgFileName[256] = "";
static GBool listEncodings = gFalse;
static GBool printVersion = gFalse;
static GBool printHelp = gFalse;

int SG_PDF2TXT(std::wstring input, std::wstring output)
{
	// convert unicode path to utf8 path
	std::wstring w_wszPath = input;
	int w_nLen = WideCharToMultiByte(CP_UTF8, 0, w_wszPath.data(), -1, NULL, NULL, NULL, NULL);
	char* w_pszPath = new char[w_nLen + 1];
	memset(w_pszPath, 0x00, w_nLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, w_wszPath.data(), (int)w_wszPath.size(), w_pszPath, w_nLen, NULL, NULL);
	std::string w_szPath(w_pszPath);
	delete[] w_pszPath;
	std::string w_szOutPath(output.begin(), output.end());

	// process pdf2txt
	return(pdf2txt(w_szPath, w_szOutPath));
}
int pdf2txt(std::string p_szPDFFilePath, std::string p_szTxtFilePath)
{
	PDFDoc* doc;
	char* fileName;
	GString* textFileName;
	GString* ownerPW, *userPW;
	TextOutputControl textOutControl;
	TextOutputDev* textOut;
	UnicodeMap* uMap;
	int exitCode;

	exitCode = 99;

	fileName = (char*)p_szPDFFilePath.c_str();

	// read config file
	globalParams = new GlobalParams(cfgFileName);
	if (textEncName[0])
	{
		globalParams->setTextEncoding(textEncName);
	}
	if (textEOL[0])
	{
		if (!globalParams->setTextEOL(textEOL))
		{
			fprintf(stderr, "Bad '-eol' value on command line\n");
		}
	}
	if (noPageBreaks)
	{
		globalParams->setTextPageBreaks(gFalse);
	}
	if (quiet)
	{
		globalParams->setErrQuiet(quiet);
	}

	// get mapping to output encoding
	globalParams->setTextEncoding(DEFAULT_ENCODING);
	if (!(uMap = globalParams->getTextEncoding()))
	{
		error(errConfig, -1, "Couldn't get text encoding");
		goto err1;
	}

	// open PDF file
	ownerPW = ownerPassword[0] != '\001' ? new GString(ownerPassword) : NULL;
	userPW = userPassword[0] != '\001' ? new GString(userPassword) : NULL;


	doc = new PDFDoc(fileName, ownerPW, userPW);
	if (userPW)
	{
		delete userPW;
	}
	if (ownerPW)
	{
		delete ownerPW;
	}
	if (!doc->isOk())
	{
		exitCode = 1;
		goto err2;
	}

	// check for copy permission
	if (!doc->okToCopy())
	{
		error(errNotAllowed, -1,
			"Copying of text from this document is not allowed.");
		exitCode = 3;
		goto err2;
	}

	// construct text file name
	textFileName = new GString(p_szTxtFilePath.c_str());

	// get page range
	if (firstPage < 1)
	{
		firstPage = 1;
	}
	if (lastPage < 1 || lastPage > doc->getNumPages())
	{
		lastPage = doc->getNumPages();
	}

	// write text file
	if (tableLayout)
	{
		textOutControl.mode = textOutTableLayout;
		textOutControl.fixedPitch = fixedPitch;
	}
	else if (physLayout)
	{
		textOutControl.mode = textOutPhysLayout;
		textOutControl.fixedPitch = fixedPitch;
	}
	else if (simpleLayout)
	{
		textOutControl.mode = textOutSimpleLayout;
	}
	else if (simple2Layout)
	{
		textOutControl.mode = textOutSimple2Layout;
	}
	else if (linePrinter)
	{
		textOutControl.mode = textOutLinePrinter;
		textOutControl.fixedPitch = fixedPitch;
		textOutControl.fixedLineSpacing = fixedLineSpacing;
	}
	else if (rawOrder)
	{
		textOutControl.mode = textOutRawOrder;
	}
	else
	{
		textOutControl.mode = textOutReadingOrder;
	}
	textOutControl.clipText = clipText;
	textOutControl.discardDiagonalText = discardDiag;
	textOutControl.insertBOM = insertBOM;
	textOutControl.marginLeft = marginLeft;
	textOutControl.marginRight = marginRight;
	textOutControl.marginTop = marginTop;
	textOutControl.marginBottom = marginBottom;
	textOut = new TextOutputDev(textFileName->getCString(), &textOutControl,
		gFalse, gTrue);
	if (textOut->isOk())
	{
		doc->displayPages(textOut, firstPage, lastPage, 72, 72, 0,
			gFalse, gTrue, gFalse);
	}
	else
	{
		delete textOut;
		exitCode = 2;
		goto err3;
	}
	delete textOut;

	exitCode = 0;

	// clean up
err3:
	delete textFileName;
err2:
	delete doc;
	uMap->decRefCnt();
err1:
	delete globalParams;

	// check for memory leaks
	Object::memCheck(stderr);
	gMemReport(stderr);

	return exitCode;
}