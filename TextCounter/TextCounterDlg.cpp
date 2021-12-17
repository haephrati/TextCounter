// TextCounterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "framework.h"
#include "TextCounter.h"
#include "SentencesCounter.h"
#include "TextCounterDlg.h"
#include "afxdialogex.h"
#include "utils.h"
#include "SG_PDF2TXT.h"


int CurFile{ 0 };
int TotalFiles{ -1 };

// MainDlg dialog


MainDlg::~MainDlg()
{
}

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TextCounter_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_SOFTWAREICON);
	DECLARE_EASYSIZE
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_Language);
	DDX_Control(pDX, IDC_EDIT_PDF_FILE_PATH, m_PDF_FilePath);
	DDX_Control(pDX, IDC_EDIT_TEXTFOUND, m_FoundText);
	DDX_Control(pDX, IDC_EDIT_CHAR_1, m_1);
	DDX_Control(pDX, IDC_EDIT_CHAR_2, m_2);
	DDX_Control(pDX, IDC_EDIT_CHAR_3, m_3);
	DDX_Control(pDX, IDC_EDIT_CHAR_4, m_4);
	DDX_Control(pDX, IDC_EDIT_CHAR_5, m_5);
	DDX_Control(pDX, IDC_EDIT_CHAR_6, m_6);
	DDX_Control(pDX, IDC_EDIT_CHAR_7, m_7);
	DDX_Control(pDX, IDC_EDIT_CHAR_8, m_8);
	DDX_Control(pDX, IDC_EDIT_CHAR_9, m_9);
	DDX_Control(pDX, IDC_EDIT_CHAR_10, m_10);
	DDX_Control(pDX, IDC_EDIT_CHAR_11, m_11);
	DDX_Control(pDX, IDC_EDIT_CHAR_12, m_12);
	DDX_Control(pDX, IDC_EDIT_CHAR_13, m_13);
	DDX_Control(pDX, IDC_EDIT_CHAR_14, m_14);
	DDX_Control(pDX, IDC_EDIT_CHAR_15, m_15);
	DDX_Control(pDX, IDC_EDIT_CHAR_16, m_16);
	DDX_Control(pDX, IDC_EDIT_CHAR_17, m_17);
	DDX_Control(pDX, IDC_EDIT_CHAR_18, m_18);
	DDX_Control(pDX, IDC_EDIT_CHAR_19, m_19);
	DDX_Control(pDX, IDC_EDIT_CHAR_20, m_20);
	DDX_Control(pDX, IDC_EDIT_CHAR_21, m_21);
	DDX_Control(pDX, IDC_EDIT_CHAR_22, m_22);
	DDX_Control(pDX, IDC_EDIT_CHAR_23, m_23);
	DDX_Control(pDX, IDC_EDIT_CHAR_24, m_24);
	DDX_Control(pDX, IDC_EDIT_CHAR_25, m_25);
	DDX_Control(pDX, IDC_EDIT_CHAR_26, m_26);
	DDX_Control(pDX, IDC_EDIT_CHAR_27, m_27);
	DDX_Control(pDX, IDC_EDIT_CHAR_28, m_28);
	DDX_Control(pDX, IDC_EDIT_CHAR_29, m_29);
	DDX_Control(pDX, IDC_EDIT_CHAR_30, m_30);
	DDX_Control(pDX, IDC_EDIT_CHAR_31, m_31);
	DDX_Control(pDX, IDC_EDIT_CHAR_32, m_32);
	DDX_Control(pDX, IDC_EDIT_CHAR_33, m_33);
	DDX_Control(pDX, IDC_EDIT_CHAR_34, m_34);
	DDX_Control(pDX, IDC_EDIT_CHAR_35, m_35);
	DDX_Control(pDX, IDC_EDIT_CHAR_36, m_36);

	DDX_Control(pDX, IDC_BUTTON_GO, m_Go);
	DDX_Control(pDX, IDC_BUTTON_SET_NO_OF_CHARACTERS, m_Set);
	DDX_Control(pDX, IDC_BUTTON_SELECT_PDF, m_SelectPDF);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_Export);
	DDX_Control(pDX, IDC_EDIT_NO_OF_CHARACTERS, m_NoChars);
	DDX_Control(pDX, IDC_STATIC_TARGET, m_Target);
	for (int i = 0; i < 36; i++)
		DDX_Control(pDX, IDC_EDIT_CHARCOUNT_1 + i, m_E[i]);

	DDX_Control(pDX, IDC_SCORE, m_Score);
	DDX_Control(pDX, IDC_SD, m_SD);
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_PDF, &MainDlg::OnBnClickedButtonSelectPdf)
	ON_BN_CLICKED(IDC_BUTTON_GO, &MainDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &MainDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &MainDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SET_NO_OF_CHARACTERS, &MainDlg::OnBnClickedButtonSetNoOfCharacters)
	ON_BN_CLICKED(IDC_BUTTON_OPTIMIZE, &MainDlg::OnBnClickedButtonOptimize)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &MainDlg::OnBnClickedButtonLog)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(MainDlg)
	EASYSIZE(IDC_BUTTON_GO, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_EDIT_NO_OF_CHARACTERS, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_BUTTON_SET_NO_OF_CHARACTERS, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_EDIT_PDF_FILE_PATH, ES_BORDER, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_EDIT_TEXTFOUND, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_BUTTON_EXPORT, ES_KEEPSIZE, ES_KEEPSIZE, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_BUTTON_OPTIMIZE, ES_KEEPSIZE, ES_KEEPSIZE, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_BUTTON_EXIT, ES_KEEPSIZE, ES_KEEPSIZE, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_STATIC_TARGET, ES_KEEPSIZE, ES_KEEPSIZE, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP

vector<Sentence> GlobalData;		// a global variable for all accumulated sentences
vector<Sentence> SelectedData;
// MainDlg message handlers

void MainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	UPDATE_EASYSIZE;
	Invalidate();
}
BOOL MainDlg::TargetReached()
{
	BOOL result{ TRUE };
	CString temp;
	CString Issues;
	m_NoChars.GetWindowText(temp);
	int target = _wtol(temp.GetString());
	if (GlobalData.size() > 0)
	{
		Sentence last = GlobalData.back();
		for (int i = 0; i < 40; i++)
		{
			int lastCounter = last.counter[i];

			if (lastCounter >= target)
				Issues.AppendFormat(L"Only %d 'A' character%c\n", lastCounter, lastCounter == 1 ? L' ' : L's');
			else
				result = FALSE;
		}
		if (!result) MessageBox(Issues, L"Target of " + temp + L" occourances of the following characters wasn't reached");
	}

	return result;
}

BOOL MainDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			ShowStatus(L"Pressed ESC...");
			if (m_hTerminate == NULL)
			{
				m_dwThreadID = 0;
				CloseHandle(m_hThread);
				m_hThread = NULL;
				CloseHandle(m_hTerminate);
				m_hTerminate = NULL;
			}
			else
			{
				SetEvent(m_hTerminate);
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

bool MainDlg::ShowFoundText(CString text, bool reset)
{
	bool result{ false };
	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();
	if (pMainDlg->mySentences.CreateSentences(GlobalData, text.GetString()))
	{
		// Target reached
		result = true;
	}
	pMainDlg->Invalidate(FALSE);
	pMainDlg->RedrawWindow();
	//	pMainDlg->BringWindowToTop();

#ifdef _DEBUG
	if (!PlaySound(MAKEINTRESOURCE(soundName), NULL, SND_SYNC | SND_RESOURCE))
		WriteLogFile(L"Can't play sound :(");
#endif
	return result;
}
BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Language.AddString(L"Albanian");
	m_Language.SetCurSel(0);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Go.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_Go.m_bTransparent = false;
	m_Go.SetTextColor(RGB(255, 255, 255));
	m_Go.SetFaceColor(RGB(245, 5, 33), true);

	m_Set.m_nFlatStyle = (CMFCButton::FlatStyle)(CMFCButton::BUTTONSTYLE_NOBORDERS | CMFCButton::BUTTONSTYLE_3D);
	m_Set.m_bTransparent = false;
	m_Set.SetTextColor(RGB(255, 255, 255));
	m_Set.SetFaceColor(RGB(39, 111, 245), true);

	m_SelectPDF.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_SelectPDF.m_bTransparent = false;
	m_SelectPDF.SetTextColor(RGB(255, 255, 255));
	m_SelectPDF.SetFaceColor(RGB(39, 111, 245), true);

	m_Export.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_Export.m_bTransparent = false;
	m_Export.SetTextColor(RGB(255, 255, 255));
	m_Export.SetFaceColor(RGB(11, 186, 63), true);

	CString version = GetVersionString();
	CString title;
	title.Format(L"Text Counter Version date: %s by Secured Globe, Inc.", version.GetString());

	SetWindowText(title);
	m_NoChars.SetWindowTextW(L"100");
	UpdateData(FALSE);
	INIT_EASYSIZE;

	SetTimer(1000, 2000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void MainDlg::OnTimer(UINT_PTR nIDEvent)
{
	MainDlg::UpdateCharsCount(mySentences.GetTotals());
	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();

	CWnd* f = GetDlgItem(IDC_BUTTON_SELECT_PDF); 
	if(TargetSet)
		f->EnableWindow(TRUE); 
	else
		f->EnableWindow(FALSE); 
	CWnd* f2 = GetDlgItem(IDC_BUTTON_GO); 
	if(PathSelected)
		f2->EnableWindow(TRUE); 
	else
		f2->EnableWindow(FALSE); 


	CWnd* f3 = GetDlgItem(IDC_BUTTON_EXPORT); 
	if(ProcessingCompleted)
		f3->EnableWindow(TRUE); 
	else
		f3->EnableWindow(FALSE); 

	CWnd* f4 = GetDlgItem(IDC_BUTTON_OPTIMIZE); 
	if(ProcessingCompleted)
		f4->EnableWindow(TRUE); 
	else
		f4->EnableWindow(FALSE); 

	CDialogEx::OnTimer(nIDEvent);
}

void MainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR MainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void MainDlg::OnBnClickedButtonSelectPdf()
{
	if (TargetSet == false)
	{
		MessageBox(L"Please set targets");
		return;
	}
	HRESULT hr = S_OK;

	// Create a new common open file dialog.
	IFileOpenDialog *pfd = NULL;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr))
	{
		// Set the dialog as a folder picker.
		DWORD dwOptions;
		hr = pfd->GetOptions(&dwOptions);
		if (SUCCEEDED(hr))
		{
			hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
		}

		// Set the title of the dialog.
		if (SUCCEEDED(hr))
		{
			hr = pfd->SetTitle(L"Select a folder of PDF files");
		}
		// Show the open file dialog.
		if (SUCCEEDED(hr))
		{
			hr = pfd->Show(m_hWnd);
			if (SUCCEEDED(hr))
			{
				// Get the selection from the user.
				IShellItem *psiResult = NULL;
				hr = pfd->GetResult(&psiResult);
				if (SUCCEEDED(hr))
				{
					PWSTR pszPath = NULL;
					hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
					if (SUCCEEDED(hr))
					{
						CString sFilePath = pszPath;
						m_PDF_FilePath.SetWindowTextW(sFilePath);
						ShowStatus(L"Selected folder %s for PDF files", sFilePath.GetString());
						PathSelected = true;
						CoTaskMemFree(pszPath);
					}
					psiResult->Release();
				}
			}
		}

		pfd->Release();
	}
}

void GetAllFilesNames(CStringArray &strArray, CString Path, int Limit)
{
	Path.Append( L"\\*.pdf");
	int LimitCount = Limit;
	strArray.RemoveAll();
	WIN32_FIND_DATA fileData;
	memset(&fileData, 0, sizeof(WIN32_FIND_DATA));
	HANDLE handle = FindFirstFile(Path, &fileData);

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (_tcscmp(fileData.cFileName, _T(".")) != 0 && // ignore "." and ".."
				_tcscmp(fileData.cFileName, _T("..")) != 0)
			{
#ifdef _DEBUG
				WriteLogFile(L"Added file %s to queue", fileData.cFileName);
#endif
				strArray.Add(fileData.cFileName);
				LimitCount--;
				if (LimitCount <= 0)
				{
					CString Msg;
					Msg.Format(L"You can only select a folder with up to %d files. The first %d will be processed and the rest will be ignored", Limit,Limit);
					MessageBox(NULL,Msg, L"Too many files", MB_OK);
					break;
				}
			}
		}
		while (FindNextFile(handle, &fileData));

		FindClose(handle);
	}
}
void MainDlg::SetThreadCheckFunc(fpThreadStopCheck p_fpThreadCheck, LPVOID p_pParent)
{
	m_fpThreadStop = p_fpThreadCheck;
	m_pParent = p_pParent;
}
#define TEMP_TXT_FILE L"temp.txt"
void MainDlg::ShowStatus(LPCWSTR lpText, ...)
{
	va_list ptr;
	va_start(ptr, lpText);
	
	CString sMsg;
	sMsg.FormatV(lpText, ptr);
	va_end(ptr);

	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();
	if (!pMainDlg->m_hTerminate)
	{
		static CString lastMsg{ L"" };
		if (sMsg == lastMsg) return;
		lastMsg = sMsg;

		CWnd* pWnd = NULL;
		try
		{
			CWinApp* pApp = AfxGetApp();
			if (!pApp) return;
			pWnd = pApp->m_pMainWnd;
			if (!pWnd) return;
		}
		catch (...)
		{
			return;
		}
	}

	::SetDlgItemText(pMainDlg->GetSafeHwnd(), IDC_STATIC_TARGET, sMsg.GetBuffer());

	sMsg.ReleaseBuffer();
#ifdef _DEBUG
	WriteLogFile(L"Status: %s", sMsg.GetBuffer());
#endif
	// Added by BOZO
	sMsg.ReleaseBuffer();
}

DWORD MainDlg::HandleProcessPath(LPVOID lpParam)
{
	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();

	CString sFilePath, sFolderPath;
	pMainDlg->m_PDF_FilePath.GetWindowTextW(sFolderPath);
	// Run over all files
	CStringArray files;
	GetAllFilesNames(files, sFolderPath);
	GlobalData.clear();
	pMainDlg->mySentences.ResetResults();
	CString TempPath;
	TotalFiles = files.GetSize();
	for (int i = 0; i < TotalFiles; i++)
	{
		CurFile = i+1;
		TempPath = sFolderPath + L"\\" + TEMP_TXT_FILE;

		if (PathFileExists(TempPath) && DeleteFile(TempPath) == FALSE)
		{
			pMainDlg->MessageBox(L"Error: File " + TempPath + L" is opened by another program");
			continue;
		}

		sFilePath = sFolderPath + L"\\" + files[i];
		ShowStatus(L"Converting PDF file %s to Text...", sFilePath.GetString());
		SG_PDF2TXT(sFilePath.GetString(), TempPath.GetString());

		if (PathFileExists(TempPath.GetString()) == FALSE)
		{
			ShowStatus(L"File %s can't be processed", sFilePath.GetString());
			continue;
		}
		else
		{
			ShowStatus(L"Working on file %s", sFilePath.GetString());
			CString fileText{ L"" };
			wstring line;
						
			wifstream mFile(TempPath.GetString());
			mFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

			if (mFile.is_open())
			{
				while (!mFile.eof())
				{
					getline(mFile, line);

					fileText.Append( (CString)(line.c_str()) + L"\r\n"); // Use ostringstream to use std::endl
				}
				mFile.close();
			}
#ifdef _DEBUG
			WriteLogFile(L"File: %s", TEMP_TXT_FILE);
#endif
			if (ShowFoundText(fileText, false))
			{
#ifdef _DEBUG
				WriteLogFile(L"Target reached");
#endif
				return true;
			}
		}
	}
	ShowStatus(L"Completed");
	pMainDlg->ProcessingCompleted = true;
	// finish thread
	pMainDlg->m_dwThreadID = 0;
	CloseHandle(pMainDlg->m_hThread);
	pMainDlg->m_hThread = NULL;
	CloseHandle(pMainDlg->m_hTerminate);
	pMainDlg->m_hTerminate = NULL;

	return 0;
}
bool MainDlg::ThreadStopCheck(LPVOID lpParam)
{
	// check stop thread
	if (lpParam != NULL)
	{
		if (WaitForSingleObject(((MainDlg*)lpParam)->m_hTerminate, 0) == WAIT_OBJECT_0)
			return true;
	}

	return false;
}

void MainDlg::OnBnClickedButtonGo()
{
	DeleteFile(LOGFILENAME);
	if (PathSelected == false)
	{
		MessageBox(L"Please select a path first");
		OnBnClickedButtonGo();
	}
#ifdef _DEBUG
	DeleteLogFile();
#endif
	UpdateTargets();
	m_hTerminate = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThread = CreateThread(NULL, 0, HandleProcessPath, this, 0, &m_dwThreadID);
}

void MainDlg::DisplayValue(int Ctrl, int Val, bool reset)
{
	MainDlg* pMainDlg = (MainDlg*)AfxGetApp()->GetMainWnd();

	int CurVal = Val;
	if (!reset)
	{
		CString temp;
		pMainDlg->GetDlgItemText(Ctrl, temp);
#ifdef _DEBUG
		WriteLogFile(L"Control %d: Old value (%s)%d Requested val %d",
			Ctrl, temp.GetString(), _wtol(temp.GetString()), Val);
#endif
		CurVal += _wtol(temp.GetString());
#ifdef _DEBUG
		WriteLogFile(L"  New value %d", CurVal);
#endif
	}
	pMainDlg->SetDlgItemText(Ctrl, to_wstring(CurVal).c_str());
}

void MainDlg::UpdateCharsCount(CounterTotals s)
{
	bool reset = true;
	for (int i = 0; i < 36; i++)
		DisplayValue(IDC_EDIT_CHAR_1 + i, s.counter[i], reset);
}

HBRUSH hBrYellow = []()
{
	return CreateSolidBrush(COLOR_YELLOW);
}();
HBRUSH hBrBackground = []()
{
	return CreateSolidBrush(NEW_COLOR_BACKGROUND);
}();

HBRUSH MainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// Our custom edit-control
	int CtrlId = pWnd->GetDlgCtrlID();
	switch (CtrlId)
	{
		case IDC_EDIT_NO_OF_CHARACTERS:
		{
			pDC->SetBkColor(COLOR_YELLOW);
			return hBrYellow;
		}
		case IDC_EDIT_CHAR_1:
		case IDC_EDIT_CHAR_2:
		case IDC_EDIT_CHAR_3:
		case IDC_EDIT_CHAR_4:
		case IDC_EDIT_CHAR_5:
		case IDC_EDIT_CHAR_6:
		case IDC_EDIT_CHAR_7:
		case IDC_EDIT_CHAR_8:
		case IDC_EDIT_CHAR_9:
		case IDC_EDIT_CHAR_10:
		case IDC_EDIT_CHAR_11:
		case IDC_EDIT_CHAR_12:
		case IDC_EDIT_CHAR_13:
		case IDC_EDIT_CHAR_14:
		case IDC_EDIT_CHAR_15:
		case IDC_EDIT_CHAR_16:
		case IDC_EDIT_CHAR_17:
		case IDC_EDIT_CHAR_18:
		case IDC_EDIT_CHAR_19:
		case IDC_EDIT_CHAR_20:
		case IDC_EDIT_CHAR_21:
		case IDC_EDIT_CHAR_22:
		case IDC_EDIT_CHAR_23:
		case IDC_EDIT_CHAR_24:
		case IDC_EDIT_CHAR_25:
		case IDC_EDIT_CHAR_26:
		case IDC_EDIT_CHAR_27:
		case IDC_EDIT_CHAR_28:
		case IDC_EDIT_CHAR_29:
		case IDC_EDIT_CHAR_30:
		case IDC_EDIT_CHAR_31:
		case IDC_EDIT_CHAR_32:
		case IDC_EDIT_CHAR_33:
		case IDC_EDIT_CHAR_34:
		case IDC_EDIT_CHAR_35:
		case IDC_EDIT_CHAR_36:
		{
			pDC->SetBkColor(NEW_COLOR_BACKGROUND);
			return hBrBackground;
		}
	}

	// All the rest
	return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

void MainDlg::OnBnClickedButtonExport()
{
	mySentences.ExportSentencesToCsv(SelectedData, CSV_EXPORT_FILE);
	ProcessingCompleted = true;
	ShellExecute(GetForegroundWindow()->GetSafeHwnd(), L"OPEN", CSV_EXPORT_FILE, NULL, NULL, TRUE);

}

void MainDlg::OnBnClickedButtonExit()
{
	OnClose();
	EndDialog(0);
}

void MainDlg::UpdateTargets()
{
	CounterTotals t;
	CString temp;
	for (int i = 0; i < 36; i++)
	{
		m_E[i].GetWindowText(temp);
		VERIFY_TARGETS_WERE_SET;
		t.counter[i] = _wtol(temp.GetString());
	}
	mySentences.SetTargets(t);
}
void MainDlg::OnBnClickedButtonSetNoOfCharacters()
{
	CString temp;
	m_NoChars.GetWindowText(temp);
	int DefSelectedVal = _wtol(temp.GetString());
	for (int i = 0; i < 36; i++)
		m_E[i].SetWindowText(temp);
	
	// Set rare characters
	/*
		5 (Dh)
		10 (Gj)
		16 (Ll)
		19 (Nj)
		24 (Rr)
		26 (Sh)
		28 (Th)
		32 (Xh)
		35 (Zh)
	*/
	CString temp2 = to_wstring(DefSelectedVal / 10).c_str();
	m_E[5].SetWindowText(temp2);
	m_E[10].SetWindowText(temp2);
	m_E[16].SetWindowText(temp2);
	m_E[19].SetWindowText(temp2);
	m_E[24].SetWindowText(temp2);
	m_E[28].SetWindowText(temp2);
	m_E[32].SetWindowText(temp2);
	m_E[35].SetWindowText(temp2);
	TargetSet = true;
	ShowStatus(L"Target: %s occourances of each character", temp.GetString());
}

void MainDlg::OnBnClickedButtonOptimize()
{
	UpdateTargets();
	//mySentences.SolveExtended(GlobalData);
	mySentences.SolveIR(GlobalData, SelectedData);
	ProcessingCompleted = true;
}


void MainDlg::OnBnClickedButtonLog()
{
	ShellExecute(GetForegroundWindow()->GetSafeHwnd(), L"OPEN", LOGFILENAME, NULL, NULL, TRUE);
}
