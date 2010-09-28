#pragma once


// CUpdateDlg dialog
#include "TextProgressCtrl.h"

class CUpdateDlg : public CDialog
{
// Construction
public:
	CUpdateDlg(CWnd* pParent = NULL);   // standard constructor
	~CUpdateDlg();
// Dialog Data
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_UPDATE_DIALOG };
	CStatic	m_stcTransferRate;
	CTextProgressCtrl	m_ctrlCurProg;
	CTextProgressCtrl	m_ctrlAllProg;
	CStatic	m_stcInfo;
	CStatic	m_stcCount;
	CStatic	m_stcElapsedTime;
	CStatic	m_stcLeftTime;
	CStatic	m_stcCurFile;
	CStatic	m_stcViewText;
	CStatic	m_stcTotal;
	CStatic	m_stcCurrent;
	CStatic	m_stcElapsedTimeLabel;
	CStatic	m_stcTransferRateLabel;
	CStatic	m_stcLeftTimeLabel;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON		m_hIcon;
	HBRUSH		m_hBkBrush;
	CFont		m_hFontBold;
	CString		m_strTransferRate;		// Transfer Rate
	CString		m_strLeftTime;			// Left Time
	CString		m_strElapsedTime;		// Elapsed Time
	CString		m_strCount;				// Total Download File count
	CString		m_strAllState;			// Entire Download files State
	CString		m_strCurState;			// Current Download file State
	CString		m_strCurFile;			// Current Download file Name

	void SetCurProgressRange(DWORD& dwFileSize);		// "SET" Current Download File Progress Bar Range
	void SetCurProgress(DWORD& dwBytesRead);			// "SET" Current Download File Progress Bar Position
public:
	void SetAllProgressRange(DWORD& dwFileSize);		// "SET" Entire Download Files Progress Bar Range
protected:
	void SetAllProgress(DWORD& dwBytesRead);			// "SET" Entire Download Files Progress Bar Position

	void SetTransferRate(double& pKbPerSecond);		// "SET" Transfer Rate
	void SetTimeLeft(DWORD& pdwSecondsLeft);			// "SET" Time Left
	void SetElapsedTime(DWORD& pdwElapsedTime);		// "SET" Elapsed Time	
	void AddComma(CString* pstrString);
	
public:
	int m_nDownfileCount;
	void DoEvent()
	{
		MSG message;
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)) {
			::TranslateMessage(&message);
			::DispatchMessage(&message); 
		}
	}

	// Each Download file Initialize GUI
	void UpdateUIInit(UPDATE_TRANSNOTIFY* pNotify);
	// During Transfer Entire Download file Update GUI
	void UpdateUIDuringTransfer(UPDATE_TRANSNOTIFY* pNotify, DWORD& dwStartTicks, DWORD& dwCurrentTicks,
										DWORD& dwCurTotalBytesRead, DWORD& dwLastTotalBytes);

	// Generated message map functions
	//{{AFX_MSG(CUpdateDlg)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

