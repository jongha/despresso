// dEspressoLauncherDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "TextProgressCtrl.h"

// CdEspressoLauncherDlg dialog
class CdEspressoLauncherDlg : public CDialog
{
// Construction
public:
	CdEspressoLauncherDlg(CWnd* pParent = NULL);	// standard constructor
	~CdEspressoLauncherDlg();

// Dialog Data
	enum { IDD = IDD_DESPRESSOLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CString			m_strCurrentPath;
	CString			m_strDestLocalFilePath;

protected:
	BOOL			CheckFolder(CString strPath);
	BOOL			CreateCheck(CString strPath);
	void			SetCurProgressRange(DWORD& dwFileSize);		// "SET" Current Download File Progress Bar Range
	void			SetCurProgress(DWORD& dwBytesRead);			// "SET" Current Download File Progress Bar Position
	void			SetAllProgressRange(DWORD& dwFileSize);		// "SET" Entire Download Files Progress Bar Range
	void			SetAllProgress(DWORD& dwBytesRead);			// "SET" Entire Download Files Progress Bar Position
	void			SetElapsedTime(DWORD& dwElapsedTime);
	void			SetTimeLeft(DWORD& dwSecondsLeft);
	void			SetTransferRate(double& KbPerSecond);
	void			AddComma(CString* pstrString);
	void			UpdateUIDuringTransfer(UPDATE_TRANSNOTIFY* pNotify, DWORD& dwStartTicks, DWORD& dwCurrentTicks,
										DWORD& dwCurTotalBytesRead, DWORD& dwLastTotalBytes);

	void			MakeBasePath();
	BOOL			m_bCheckDlg;
	BOOL			m_bFirstUpdate;
	DWORD			m_dwStartTicks;
	DWORD			m_dwCurrentTicks;
	DWORD			m_dwLastTotalBytes;	
	DWORD			m_dwCurrentTotalSendPos;
	int				m_nCurrentFileCount;

public:
	CTextProgressCtrl	m_ctrlCurProg;
	CTextProgressCtrl	m_ctrlAllProg;
	CWinThread*		m_pUpdateThread;
	BOOL			m_bUpdateSuccess;

	BOOL		WebDiskUpdate();
	BOOL		StartUpdateThread();
	BOOL		StartUpdate(CString strSrcURL, CString strDestLocalFilePath);
	LRESULT		OnSendNotify(WPARAM wParam, LPARAM lParam);
	LRESULT		OnUpdateDlgClose(WPARAM wParam, LPARAM lParam);
	
	void		Finalize();
	void		Initialize();
	void		ErrorMessage(int nErrorNo);
	BOOL		IsFileExist(LPCTSTR lpszFilePath);
	
	HINSTANCE	m_hInst;
	BOOL		m_bInitialized;
	HWND		m_hInstWnd;
	BOOL		m_bCancel;

	BOOL		m_bExecuteFile;	
	void		UpdateUIInit(UPDATE_TRANSNOTIFY*);
	void DoEvent()
	{
		MSG message;
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)) {
			::TranslateMessage(&message);
			::DispatchMessage(&message); 
		}
	}
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	CString m_strCurFile;
public:
	CString m_strCurState;
public:
	CString m_strCount;
public:
	CString m_strAllState;
public:
	CString m_stcElapsedTime;
public:
	CString m_stcLeftTime;
public:
	CString m_stcTransferRate;
};
