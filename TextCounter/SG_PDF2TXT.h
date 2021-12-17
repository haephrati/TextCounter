#pragma once

#include <string>

int SG_PDF2TXT(std::wstring input, std::wstring output);
int pdf2txt(std::string p_szPDFFilePath, std::string p_szTxtFilePath);
#define DEFAULT_ENCODING "UTF-8"