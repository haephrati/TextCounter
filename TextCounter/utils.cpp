#include "stdafx.h"
#include "utils.h"

wchar_t *LOGFILENAME{ L"logfile.txt" };

void DeleteLogFile()
{
	DeleteFile(LOGFILENAME);
}

int WriteLogFile(LPCWSTR lpText, ...)
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	va_list ptr;
	va_start(ptr, lpText); // no va_end?

	CString sMsg;
	sMsg.FormatV(lpText, ptr);
	va_end(ptr);

	CString sLine = GetLogLine(sMsg);
	CStringA line = sLine + "\n";

	//CStringA line = (CStringA)sMsg + "\n";	
	errno_t errCode;
	WriteFile(
		hStdout,               // output handle 
		line.GetString(),           // prompt string 
		line.GetLength(), // string length 
		NULL,             // bytes written 
		NULL);

	FILE *fp;

	try
	{
		errCode = _wfopen_s(&fp, LOGFILENAME, L"a,ccs=UTF-8");
		if (fp && (errCode == 0))
		{
			fwprintf(fp, L"%s\n", sLine.GetString());

			if (fp->_Placeholder)
				fclose(fp);
		}
	}
	catch (...)
	{
		if (fp->_Placeholder)
			fclose(fp);

		return FALSE;
	}

	return TRUE;
}

int WriteLinesToLogFile(vector<CString> logLines)
{
	errno_t errCode;
	FILE *fp;

	try
	{
		errCode = _wfopen_s(&fp, LOGFILENAME, L"a,ccs=UTF-8");
		if (fp && (errCode == 0))
		{
			for each (CString logLine in logLines)
			{
				fwprintf(fp, L"%s\n", logLine.GetString());
			}

			if (fp->_Placeholder)
				fclose(fp);
		}
	}
	catch (...)
	{
		if (fp->_Placeholder)
			fclose(fp);

		return FALSE;
	}

	return TRUE;
}

CString GetLogLineFormat(LPCWSTR msg, ...)
{
	va_list ptr;
	va_start(ptr, msg); // no va_end?

	CString fMsg;
	fMsg.FormatV(msg, ptr);

	return GetLogLine(fMsg);
}

CString GetLogLine(CString msg)
{
	CTime Today = CTime::GetCurrentTime();
	CString sLine;
	sLine.Format(L"%s: %s\n", (LPCTSTR)Today.FormatGmt(L"%d.%m.%Y %H:%M"), (LPCTSTR)msg);
	return sLine;
}

CTime Time2UTC(CTime original)
{
	CTime result;	

	CString fOriginal = original.FormatGmt(DATEFORMAT);
	if (fOriginal != L"" && fOriginal.GetLength() >= 12)
	{	
		int Year, Month, Day, Hour, Minute;
		Year = _wtol(fOriginal.Left(4));
		Month = _wtol(fOriginal.Mid(4, 2));
		Day = _wtol(fOriginal.Mid(6, 2));
		Hour = _wtol(fOriginal.Mid(8, 2));
		Minute = _wtol(fOriginal.Mid(10, 2));
		result = CTime(Year, Month, Day, Hour, Minute, 0);
	}
	else
	{
		result = (CTime)NULL;
	}

	return result;
}
CTime GetFileDateTime(LPCWSTR FileName)
{
	FILETIME ftCreate, ftAccess, ftWrite;

	HANDLE hFile;
	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return (CTime)NULL;
	}

	// Retrieve the file times for the file.
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
		return (CTime)NULL;

	CTime FileTime( ftWrite );
	CloseHandle(hFile);// shouldnt this be moved 2 lines up?

	return FileTime;
}

CTime GetSelfDateTimeGMT(void)
{
	WCHAR szExeFileName[MAX_PATH];
	GetModuleFileName(NULL, szExeFileName, MAX_PATH);
	return Time2UTC(GetFileDateTime(szExeFileName));
}

CString GetVersionString()
{
	CString message;
	message = GetSelfDateTimeGMT().Format(FRIEDLY_DATEFORMAT);
	return message;
}