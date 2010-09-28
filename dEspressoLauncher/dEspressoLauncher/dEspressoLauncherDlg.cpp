// dEspressoLauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dEspressoLauncher.h"
#include "dEspressoLauncherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdEspressoLauncherDlg dialog
extern BOOL g_bShow;
extern BOOL g_bRun;

CdEspressoLauncherDlg::CdEspressoLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdEspressoLauncherDlg::IDD, pParent)
	, m_strCurFile(_T(""))
	, m_strCurState(_T(""))
	, m_strCount(_T(""))
	, m_strAllState(_T(""))
	, m_stcElapsedTime(_T(""))
	, m_stcLeftTime(_T(""))
	, m_stcTransferRate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	Initialize();
}

CdEspressoLauncherDlg::~CdEspressoLauncherDlg() 
{
	Finalize();
}

void CdEspressoLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CURRENT_FILE, m_strCurFile);
	DDX_Text(pDX, IDC_CURRENT_STATE, m_strCurState);
	DDX_Control(pDX, IDC_CURRENT_PROGRESS, m_ctrlCurProg);
	DDX_Control(pDX, IDC_TOTAL_PROGRESS, m_ctrlAllProg);
	DDX_Text(pDX, IDC_COUNT, m_strCount);
	DDX_Text(pDX, IDC_ALL_STATE, m_strAllState);
	DDX_Text(pDX, IDC_ELAPSED_TIME, m_stcElapsedTime);
	DDX_Text(pDX, IDC_LEFT_TIME, m_stcLeftTime);
	DDX_Text(pDX, IDC_TRANSFER_RATE, m_stcTransferRate);
}

BEGIN_MESSAGE_MAP(CdEspressoLauncherDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_SEND, OnSendNotify)
	ON_MESSAGE(WM_USER_UPDATE_CLOSE, OnUpdateDlgClose)
ON_WM_CREATE()
END_MESSAGE_MAP()


// CdEspressoLauncherDlg message handlers

BOOL CdEspressoLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CdEspressoLauncherDlg::OnPaint()
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
		CDialog::OnPaint();
	}


	if(!g_bRun) {
		SetTimer(CHECK_RUN_TIMER, 1000, NULL);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CdEspressoLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


static int UpdateThread(LPVOID lParam)
{
	CdEspressoLauncherDlg *pCtrl = (CdEspressoLauncherDlg*)lParam;
	if(pCtrl->StartUpdateThread()) pCtrl->m_bUpdateSuccess = TRUE;
	else pCtrl->m_bUpdateSuccess = FALSE;

	if(!pCtrl->m_bCancel)
		SendMessage(pCtrl->GetSafeHwnd(), WM_USER_UPDATE_CLOSE, 0 , 0);

	pCtrl->m_pUpdateThread = NULL;
	return 0;
}

// Find Current Execute Directory
void CdEspressoLauncherDlg::MakeBasePath()
{	
	CString strTmp;
	LPWCH buf = (LPWCH)malloc(MAX_PATH);
	GetModuleFileName(AfxGetApp()->m_hInstance, buf, MAX_PATH);
	
	strTmp.Format(_T("%s"), buf);

    m_strCurrentPath = strTmp.Left( strTmp.ReverseFind( '\\' ) );
	m_strCurrentPath += "\\";
}


BOOL CdEspressoLauncherDlg::CreateCheck(CString strPath)
{
	if( !CreateDirectory(strPath, 0) ){
		int ret = GetLastError();
		if(ret == ERROR_ALREADY_EXISTS){
			return TRUE;
		}
		return FALSE;
	}

	return TRUE;
}

BOOL CdEspressoLauncherDlg::CheckFolder(CString strPath)
{
	CString strFindPath = strPath;
	CString strTmp;
	BOOL bSuccess = TRUE;
	int nFind = 3;
	int nEnd = strPath.ReverseFind('\\');
	
	while(nFind <= nEnd && bSuccess)
	{	
		nFind = strPath.Find('\\', nFind);
		strTmp = strFindPath.Left( nFind );
		bSuccess = CreateCheck(strTmp);
		nFind++;
	}
	
	if(!bSuccess)
		return FALSE;
	
	return TRUE;
}

void CdEspressoLauncherDlg::Initialize()
{
	m_hInst = LoadLibrary(UPDATE_DLL);

	if(m_hInst == NULL){
		CString strMSG;
		AfxFormatString1(strMSG, IDS_KOREAN_ErrMSG_UpdateDll_Not_Exist, UPDATE_DLL);
		MessageBox(strMSG, PROGRAM_NAME, MB_OK|MB_ICONINFORMATION);
		return;
	}

	m_bCancel = FALSE;
	m_strDestLocalFilePath = _T("");
	//m_pUpdateDialog = NULL;
}

void CdEspressoLauncherDlg::Finalize()
{
	if(m_pUpdateThread){
		m_bCancel = TRUE;
		while(m_pUpdateThread){
//			TRACE("while(m_pUpdateThread)\n");
			DoEvent();
		}
		//Sleep(100);
	}

	if(m_hInst != NULL) {
		FreeLibrary(m_hInst);
	}

	::ShellExecute(
		this->m_hWnd, _T("open"), 
		TRIGGER_PROGRAM, 
		NULL, 
		m_strCurrentPath, SW_NORMAL); 
//	DestroyWindow();
}

typedef int (WINAPI* StartUpdateProc)(PUPDATE_TRANSINFO, BOOL *);
BOOL CdEspressoLauncherDlg::StartUpdate(CString strSrcURL, CString strDestLocalFilePath) 
{
	if(m_hInst == NULL)
		return FALSE;
	
	PUPDATE_TRANSINFO pInfo;
	pInfo = new UPDATE_TRANSINFO;
	memset(pInfo, 0, sizeof(UPDATE_TRANSINFO));

	USES_CONVERSION;
	m_bExecuteFile = TRUE;
	pInfo->hNotifyWnd = GetSafeHwnd();
	pInfo->nNotifyMsg = WM_USER_SEND;
	pInfo->lpszSrcURL = T2CA((LPCTSTR)strSrcURL);
	pInfo->lpszDestXmlFile = T2CA((LPCTSTR)strDestLocalFilePath);
	pInfo->nErrno = UPDATE_ERROR_NONE;

	StartUpdateProc UpdateStart = (StartUpdateProc)GetProcAddress(m_hInst, "StartUpdate");

	if(UpdateStart == NULL){
		if(pInfo)
			delete pInfo;
		pInfo = NULL;
		return FALSE;
	}
	m_bFirstUpdate = TRUE;
	BOOL retval = UpdateStart(pInfo, &m_bCancel);

	if(!retval){
		ErrorMessage(pInfo->nErrno);
	}
	
	if(pInfo) delete pInfo;
	pInfo = NULL;

	return retval;
}

LRESULT	CdEspressoLauncherDlg::OnSendNotify(WPARAM wParam, LPARAM lParam) 
{
	PUPDATE_TRANSNOTIFY pNotify = (PUPDATE_TRANSNOTIFY)lParam;
	CString msg;
		
	if(m_bFirstUpdate){
		if(pNotify->nTotalCount != 0 && pNotify->nCurrentCount == 1){
				//m_pUpdateDialog->ShowWindow(SW_SHOW);
				int ntime = 0;
	#ifdef _DEBUG
				ntime = 3000;
	#else
				ntime = 1000;
	#endif
				SetTimer(CHECK_TIMER, ntime, NULL);
				/*while(m_bCheckDlg){
					DoEvent();
				}*/
				m_bFirstUpdate = FALSE;

				//m_pUpdateDialog->ShowWindow(SW_SHOW);

				m_dwStartTicks = ::GetTickCount();
				m_dwCurrentTicks = m_dwStartTicks;
				m_dwLastTotalBytes = 0;
				SetAllProgressRange(pNotify->nTotalSize);
		}
	}
	
	if(m_nCurrentFileCount != pNotify->nCurrentCount){
		UpdateUIInit(pNotify);
		m_nCurrentFileCount = pNotify->nCurrentCount;
		m_dwCurrentTotalSendPos = pNotify->nSendPos;
	}
	else{
		m_dwCurrentTotalSendPos += pNotify->nSendPos;
		UpdateUIDuringTransfer(pNotify, m_dwStartTicks, m_dwCurrentTicks, m_dwCurrentTotalSendPos, m_dwLastTotalBytes);
	}

	return 0L;
}


BOOL CdEspressoLauncherDlg::StartUpdateThread()
{
	BOOL retval = FALSE;
	if(StartUpdate(UPDATE_URL, m_strDestLocalFilePath))
		retval = TRUE;
	else
		retval = FALSE;
	
	return retval;
}

void CdEspressoLauncherDlg::ErrorMessage(int nErrorNo)
{
	CString strMsg = _T("");
	
	switch(nErrorNo)
	{
		case UPDATE_ERROR_NONE /* == UPDATE_SUCCESS*/:
			break;

		case UPDATE_ERROR_INFORMATION:
		case UPDATE_ERROR_FAIL_DOWNLOADXMLFILE:
		case UPDATE_ERROR_FILE_NOT_FOUND:
		case UPDATE_ERROR_CANT_MAKE_ITEMLIST_SOURCE:
		case UPDATE_ERROR_CANT_MAKE_ITEMLIST_DEST:
		case UPDATE_ERROR_CANT_READ_XML_SOURCE:
		case UPDATE_ERROR_CANT_READ_XML_DEST:
		case UPDATE_ERROR_CANT_OPEN_XML_FILE:
		case UPDATE_ERROR_CANT_MAKE_XML_FILE:
		case UPDATE_ERROR_DLL_LOAD_LIBRARY:
		case UPDATE_ERROR_DLL_GET_PROC_ADDRESS:
		case UPDATE_HTTP_FAIL_PARSE_URL:
		case UPDATE_HTTP_FAIL_INTERNET_SESSION:
		case UPDATE_HTTP_FAIL_INTERNET_CONNECTION:
		case UPDATE_HTTP_FAIL_INTERNET_OPEN_REQUEST:
		case UPDATE_HTTP_FAIL_INTERNET_SEND_REQUEST:
		case UPDATE_HTTP_FAIL_INTERNET_QUERY_STATUS_CODE:
		case UPDATE_HTTP_FAIL_INTERNET_QUERY_CONTENT_LENGTH:
		case UPDATE_HTTP_FAIL_INTERNET_CREATE_FILE:
		case UPDATE_HTTP_FAIL_INTERNET_CREATE_FILE_HIDE:
		case UPDATE_HTTP_FAIL_INTERNET_READ_FILE:
		case UPDATE_HTTP_FAIL_INTERNET_STATUS_DENIED:
		case UPDATE_HTTP_FAIL_INTERNET_STATUS_NOT_FOUND:
		case UPDATE_HTTP_FAIL_INTERNET_OTHER_FAIL:
		case UPDATE_HTTP_FAIL_PARSE_DOWN_PATH:
		default:
			break;
	}

	if(strMsg != "") {
		if(nErrorNo == UPDATE_HTTP_FAIL_INTERNET_CREATE_FILE_HIDE) {
			//MessageBox(strMsg, "idisk", MB_OK | MB_ICONINFORMATION);
		} else {
			MessageBox(strMsg, PROGRAM_NAME, MB_OK | MB_ICONERROR);
		}
	}

	return;
}

LRESULT CdEspressoLauncherDlg::OnUpdateDlgClose(WPARAM wParam, LPARAM lParam)
{
	if(GetSafeHwnd())
	{
		OnOK();
		TRACE("Finalize() :: delete m_pCheckDialog\n");
	}

	g_bShow = FALSE;
	return 0L;
}

BOOL CdEspressoLauncherDlg::IsFileExist(LPCTSTR lpszFilePath)
{
	BOOL retval = FALSE;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(lpszFilePath, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE){
		retval = FALSE;
	}
	else{	
		FindClose(hFind);
		retval = TRUE;
	}

	return retval;
}

void CdEspressoLauncherDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == CHECK_TIMER)
	{
		KillTimer(CHECK_TIMER);
		//m_bCheckDlg = FALSE;
	}else if(nIDEvent == CHECK_RUN_TIMER) {
		KillTimer(CHECK_RUN_TIMER);

		g_bRun = TRUE;
		WebDiskUpdate();
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CdEspressoLauncherDlg::WebDiskUpdate() 
{	
	if(m_hInst == NULL)
	{
		CString strMSG;
		AfxFormatString1(strMSG, IDS_KOREAN_ErrMSG_UpdateDll_Not_Exist, UPDATE_DLL);
		MessageBox(strMSG, PROGRAM_NAME, MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	MakeBasePath();

	// Start Version Check Dialog
	m_nCurrentFileCount = 0;
	m_strDestLocalFilePath = m_strCurrentPath + UPDATE_XML;

	m_pUpdateThread = NULL;
	m_pUpdateThread = AfxBeginThread((AFX_THREADPROC)UpdateThread, (LPVOID)this);

	while (m_pUpdateThread){
		Sleep(0);
		DoEvent();
	}
	return m_bUpdateSuccess;
}


int CdEspressoLauncherDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	return 0;
}



// Update UI Init State
void CdEspressoLauncherDlg::UpdateUIInit(UPDATE_TRANSNOTIFY* pNotify)
{	
	BSTR bstr, bstr2;
	int nLen = MultiByteToWideChar(CP_ACP, 0, pNotify->lpszDownPath, strlen(pNotify->lpszDownPath), NULL, NULL);
	bstr = SysAllocStringLen(NULL, nLen);
	MultiByteToWideChar(CP_ACP, 0, pNotify->lpszDownPath, strlen(pNotify->lpszDownPath), bstr, nLen);
	
	CString strDownPath;
	strDownPath.Format(_T("%s"), bstr);
	SysFreeString(bstr);

	if( strDownPath.ReverseFind('\\') != (strDownPath.GetLength()-1) )
		strDownPath += '\\';

	nLen = MultiByteToWideChar(CP_ACP, 0, pNotify->lpszName, strlen(pNotify->lpszName), NULL, NULL);
	bstr2 = SysAllocStringLen(NULL, nLen);
	MultiByteToWideChar(CP_ACP, 0, pNotify->lpszName, strlen(pNotify->lpszName), bstr2, nLen);
	
	m_strCurFile.Format(_T("%s%s"), strDownPath, bstr2);
	SysFreeString(bstr2);

//	m_strCurFile = pNotify->lpszName;
	
	// Current File State
	m_strCurState.Format(_T("0 / %d KBytes"), (pNotify->nCurrentSize)/1024);
	m_ctrlCurProg.SetWindowText(m_strCurState);

	// Current File ProgressBar
	SetCurProgressRange(pNotify->nCurrentSize);
	DWORD dwZero = 0;
	SetCurProgress(dwZero);

	// All File State
	m_strCount.Format(_T("( %d / %d )"), pNotify->nCurrentCount, pNotify->nTotalCount);
	UpdateWindow();
}


void CdEspressoLauncherDlg::UpdateUIDuringTransfer(UPDATE_TRANSNOTIFY* pNotify, DWORD& dwStartTicks, DWORD& dwCurrentTicks,
										DWORD& dwCurTotalBytesRead, DWORD& dwLastTotalBytes)
{
	CString strReadSizeTmp = _T(""), strFileSizeTmp = _T("");
	strReadSizeTmp.Format(_T("%d"),dwCurTotalBytesRead/1024);
	strFileSizeTmp.Format(_T("%d"),(pNotify->nCurrentSize)/1024);
	
	AddComma(&strReadSizeTmp);
	AddComma(&strFileSizeTmp);

	// Update the Current File State
	m_strCurState.Format(_T("%s / %s KBytes"), strReadSizeTmp, strFileSizeTmp);
	m_ctrlCurProg.SetWindowText(m_strCurState);

	strReadSizeTmp = _T("");
	strFileSizeTmp = _T("");

	strReadSizeTmp.Format(_T("%d"),(pNotify->nTotalPos)/1024);
	strFileSizeTmp.Format(_T("%d"),(pNotify->nTotalSize)/1024);

	AddComma(&strReadSizeTmp);
	AddComma(&strFileSizeTmp);

	// Update the All File State
	m_strAllState.Format(_T("%s / %s KBytes"), strReadSizeTmp, strFileSizeTmp);

	// Update the Progress control Bar
	SetCurProgress(dwCurTotalBytesRead);
	SetAllProgress(pNotify->nTotalPos);

	//Update the transfer rate amd estimated time left every second
	DWORD dwNowTicks = ::GetTickCount();
	DWORD dwTimeTaken = dwNowTicks - dwCurrentTicks;
	if (dwTimeTaken > 1000){
		double KbPerSecond = ((double)(pNotify->nTotalPos) - (double)(dwLastTotalBytes)) / ((double)(dwTimeTaken));
		SetTransferRate(KbPerSecond);

		DWORD dwElapsedTime = dwNowTicks - dwStartTicks;
		dwElapsedTime = dwElapsedTime/1000;
		SetElapsedTime(dwElapsedTime);

		//Setup for the next time around the loop
		dwCurrentTicks = dwNowTicks;
		dwLastTotalBytes = pNotify->nTotalPos;

		//Update the estimated time left
		if (pNotify->nTotalPos){
			DWORD dwSecondsLeft = (DWORD) (((double)dwNowTicks - dwStartTicks) / (pNotify->nTotalPos) * 
											(pNotify->nTotalSize - pNotify->nTotalPos) / 1000);
			SetTimeLeft(dwSecondsLeft);
		}
	}
	
	UpdateWindow();
	UpdateData(FALSE);
}


// Elapsed Time Count UI Update
void CdEspressoLauncherDlg::SetElapsedTime(DWORD& dwElapsedTime)
{
	if (dwElapsedTime < 60){
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwElapsedTime);
		AfxFormatString1(m_stcElapsedTime, IDS_HTTPDOWNLOAD_SECONDS, sSeconds);
	}
	else{
		DWORD dwMinutes = dwElapsedTime / 60;
		DWORD dwSeconds = dwElapsedTime % 60;
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwSeconds);
		CString sMinutes;
		sMinutes.Format(_T("%d"), dwMinutes);

		if (dwSeconds == 0)
			AfxFormatString1(m_stcElapsedTime, IDS_HTTPDOWNLOAD_MINUTES, sMinutes);
		else
			AfxFormatString2(m_stcElapsedTime, IDS_HTTPDOWNLOAD_MINUTES_AND_SECONDS, sMinutes, sSeconds);
	}
}


// Left Time Count UI Update
void CdEspressoLauncherDlg::SetTimeLeft(DWORD& dwSecondsLeft)
{
	if (dwSecondsLeft < 60){
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwSecondsLeft);
		AfxFormatString1(m_stcLeftTime, IDS_HTTPDOWNLOAD_SECONDS, sSeconds);
	}
	else{
		DWORD dwMinutes = dwSecondsLeft / 60;
		DWORD dwSeconds = dwSecondsLeft % 60;
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwSeconds);
		CString sMinutes;
		sMinutes.Format(_T("%d"), dwMinutes);

		if (dwSeconds == 0)
			AfxFormatString1(m_stcLeftTime, IDS_HTTPDOWNLOAD_MINUTES, sMinutes);
		else
			AfxFormatString2(m_stcLeftTime, IDS_HTTPDOWNLOAD_MINUTES_AND_SECONDS, sMinutes, sSeconds);
	}
}

// Transfer Rate UI Update
void CdEspressoLauncherDlg::SetTransferRate(double& KbPerSecond)
{
	if (KbPerSecond < 1){
		CString sBytesPerSecond;
		sBytesPerSecond.Format(_T("%0.0f"), KbPerSecond*1024);
		AfxFormatString1(m_stcTransferRate, IDS_HTTPDOWNLOAD_BYTESPERSECOND, sBytesPerSecond);
	}
	else if (KbPerSecond < 10){
		CString sKiloBytesPerSecond;
		sKiloBytesPerSecond.Format(_T("%0.2f"), KbPerSecond);
		AfxFormatString1(m_stcTransferRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
	}
	else{
		CString sKiloBytesPerSecond;
		sKiloBytesPerSecond.Format(_T("%0.0f"), KbPerSecond);
		AfxFormatString1(m_stcTransferRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
	}
}

void CdEspressoLauncherDlg::AddComma(CString* pstrString)
{
	CString strTmp = *pstrString;
	wchar_t *buf = strTmp.GetBuffer(strTmp.GetLength()*4/3);

	int len, i, j;
	for(len=strTmp.GetLength(), i=0, j=0; i<len; i++, j++){		
		if( !((len-i)%3) && i != 0){
			if(j > 0 && buf[j-1] != '-')
				buf[j++] = ',';
		}
		buf[j] = pstrString->GetAt(i);
	}
	buf[j] = 0;

	strTmp.ReleaseBuffer();

	*pstrString = strTmp;
}

void CdEspressoLauncherDlg::SetCurProgressRange(DWORD& dwFileSize)
{
	m_ctrlCurProg.SetRange(0, (short)((dwFileSize+512)/1024));
}

void CdEspressoLauncherDlg::SetCurProgress(DWORD& dwBytesRead)
{
	m_ctrlCurProg.SetPos(dwBytesRead/1024);
}

void CdEspressoLauncherDlg::SetAllProgressRange(DWORD& dwFileSize)
{
	m_ctrlAllProg.SetRange(0, (short)((dwFileSize+512)/1024));
}

void CdEspressoLauncherDlg::SetAllProgress(DWORD& dwBytesRead)
{															   
	m_ctrlAllProg.SetPos(dwBytesRead/1024);					   
}															   
