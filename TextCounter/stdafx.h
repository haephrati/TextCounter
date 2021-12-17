// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef STDAFX_H
#define STDAFX_H
#include <limits>

#include "framework.h"
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <io.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ctype.h"
#include <vector>

#define NOMINMAX
// add headers that you want to pre-compile here
#include <gdiplus.h>
#include <afxdhtml.h>
#include <afxsock.h>
#include <WinInet.h>
#include <string>
#include <iostream>
#include <Netlistmgr.h>
#include <WinIoCtl.h>
#include <mfidl.h>
#include <lm.h>
#include <vector>
#include <list>
#define SECURITY_WIN32
#include <Security.h>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <mmsystem.h>
#include <locale>

#include <winternl.h>
#include <VersionHelpers.h>
using namespace Gdiplus;
using namespace std;
#pragma comment(lib, "Version.lib")
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "Winmm.lib")

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "easysize.h"
#endif //STDAFX_H
