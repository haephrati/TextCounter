#pragma once
#define FRIEDLY_DATEFORMAT L"%d-%m-%Y, %H:%M:%S"
#define DATEFORMAT L"%Y%m%d%H%M%S"
void DeleteLogFile();
int WriteLogFile(LPCWSTR lpText, ...);
CString GetLogLineFormat(LPCWSTR msg, ...);
int WriteLinesToLogFile(vector<CString> logLines);
CString GetLogLine(CString msg);
extern wchar_t *LOGFILENAME;
CString GetVersionString();
