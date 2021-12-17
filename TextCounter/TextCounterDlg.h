// TextCounterDlg.h : header file
//

#pragma once
#define COLOR_YELLOW RGB(215,235,235)
#define NEW_COLOR_BACKGROUND RGB(240,240,220)
#define VERIFY_TARGETS_WERE_SET 	if (temp == L"") {MessageBox(L"Please set target value/s"); return;}
#define CSV_EXPORT_FILE				L"export.csv"

void GetAllFilesNames(CStringArray &strArray, CString Path, int Limit=300);
extern int CurFile;
extern int TotalFiles;

// SGForensicsDialogDlg dialog

class MainDlg : public CDialogEx
{
	DECLARE_EASYSIZE
	public:
	MainDlg(CWnd* pParent = nullptr);	// standard constructor
	~MainDlg() override;

	DWORD m_dwThreadID;
	HANDLE m_hThread;
	HANDLE m_hTerminate;

	SentencesCounter mySentences;
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_TextCounter_DIALOG
	};
#endif

	bool TargetSet{ false };
	bool PathSelected{ false };
	bool ProcessingCompleted{ false };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

														// check stop function
	typedef bool(*fpThreadStopCheck)(LPVOID lpParam);
	void SetThreadCheckFunc(fpThreadStopCheck p_fpThreadCheck, LPVOID p_pParent);

	private:
	// thread function variable
	fpThreadStopCheck m_fpThreadStop;
	LPVOID m_pParent;

	protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
	public:
	CComboBox m_Language;
	CEdit m_PDF_FilePath;
	CEdit m_FoundText;
	BOOL TargetReached();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static bool ShowFoundText(CString text, bool reset = false);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedButtonSelectPdf();

	afx_msg void OnBnClickedButtonGo();
	static void ShowStatus(LPCWSTR lpText, ...);
	static DWORD WINAPI HandleProcessPath(LPVOID lpParam);
	static bool ThreadStopCheck(LPVOID lpParam);

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	static void DisplayValue(int Ctrl, int Val, bool reset = false);
	static void UpdateCharsCount(CounterTotals s);

	CEdit m_1;
	CEdit m_2;
	CEdit m_3;
	CEdit m_4;
	CEdit m_5;
	CEdit m_6;
	CEdit m_7;
	CEdit m_8;
	CEdit m_9;
	CEdit m_10;
	CEdit m_11;
	CEdit m_12;
	CEdit m_13;
	CEdit m_14;
	CEdit m_15;
	CEdit m_16;
	CEdit m_17;
	CEdit m_18;
	CEdit m_19;
	CEdit m_20;
	CEdit m_21;
	CEdit m_22;
	CEdit m_23;
	CEdit m_24;
	CEdit m_25;
	CEdit m_26;
	CEdit m_27;
	CEdit m_28;
	CEdit m_29;
	CEdit m_30;
	CEdit m_31;
	CEdit m_32;
	CEdit m_33;
	CEdit m_34;
	CEdit m_35;
	CEdit m_36;
	CMFCButton m_Go;
	CMFCButton m_Set;
	CMFCButton m_SelectPDF;
	CMFCButton m_Export;
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonExit();
	CEdit m_NoChars;
	CStatic m_Target;
	void UpdateTargets();
	afx_msg void OnBnClickedButtonSetNoOfCharacters();
	CEdit m_E[36];
	CEdit m_Score;
	CEdit m_SD;
	afx_msg void OnBnClickedButtonOptimize();
	afx_msg void OnBnClickedButtonLog();
};
