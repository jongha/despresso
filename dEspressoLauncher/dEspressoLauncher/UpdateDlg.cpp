// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dEspressoLauncher.h"
#include "UpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CUpdateDlg dialog


CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hBkBrush = CreateSolidBrush(RGB(255,255,255));
}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDlg)
	DDX_Control(pDX, IDC_STATIC_LOGO, m_stcInfo);
	DDX_Control(pDX, IDC_STATIC_TRANSFERRATE, m_stcTransferRate);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlCurProg);
	DDX_Control(pDX, IDC_PROGRESS2, m_ctrlAllProg);
	DDX_Control(pDX, IDC_STATIC_CURCNT, m_stcCount);
	DDX_Control(pDX, IDC_STATIC_ElAPSEDTIME, m_stcElapsedTime);
	DDX_Control(pDX, IDC_STATIC_LEFTTIME, m_stcLeftTime);
	DDX_Control(pDX, IDC_STATIC_CURRENTFILE, m_stcCurFile);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_stcViewText);
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_stcTotal);
	DDX_Control(pDX, IDC_STATIC_CURRENT, m_stcCurrent);
	DDX_Control(pDX, IDC_STATIC_ElAPSEDTIME_LABEL, m_stcElapsedTimeLabel);
	DDX_Control(pDX, IDC_STATIC_TRANSFERRATE_LABEL, m_stcTransferRateLabel);
	DDX_Control(pDX, IDC_STATIC_LEFTTIME_LABEL, m_stcLeftTimeLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDlg)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg message handlers

BOOL CUpdateDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1){
		return TRUE;
	}
	else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE){
		return TRUE;
	}
	else	
		return CDialog::PreTranslateMessage(pMsg);	
}

void CUpdateDlg::OnClose() 
{
/*
	int nPos = m_ctrlAllProg.GetPos();
	if(nPos != 0){
		if(MessageBox("현재 파일 전송중입니다.\\n중지하시면 프로그램을 실행 시키실 수 없습니다.\n그래도 중지 하시겠습니까?", 
			SERVICE_TITL, MB_OK|MB_YESNOCANCEL) != IDYES)
		{
			return;	
		}
	}
*/
//	CDialog::OnClose();
}

void CUpdateDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DeleteObject(m_hBkBrush);
	DeleteObject(m_hFontBold);
	// TODO: Add your message handler code here
	
}

BOOL CUpdateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//--------------------------------------------------------
	// close button disable
	CMenu* mnu = this->GetSystemMenu(FALSE);
	mnu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED );
	mnu->EnableMenuItem( SC_CLOSE, MF_BYCOMMAND|MF_GRAYED);
	//---------------------------------------------------------
//*/
	CString strtmpMSG;

    CFont* pFont = GetFont();
    LOGFONT lfLogFont;
	pFont->GetLogFont(&lfLogFont);
    lfLogFont.lfWeight = FW_BOLD;
    m_hFontBold.CreateFontIndirect(&lfLogFont);

/*
	// font setup
	BOOL bfont;
	bfont = m_Font.CreatePointFont(g_nFontSize*10,_T(g_lpszFont));
	if(!bfont){
		AfxFormatString1(strtmpMSG, IDS_KOREAN_ErrMSG_11, "");
		ErrMsgBox(strtmpMSG);
		return FALSE;
	}

	this->SetFont(&m_Font);
	
	m_stcLeftTimeLabel.SetFont(&m_Font);
	m_stcTransferRateLabel.SetFont(&m_Font);
	m_stcElapsedTimeLabel.SetFont(&m_Font);
	m_stcCurrent.SetFont(&m_Font);
	m_stcTotal.SetFont(&m_Font);
	m_stcViewText.SetFont(&m_Font);
	m_stcCurFile.SetFont(&m_Font);
	m_stcTransferRate.SetFont(&m_Font);
	m_stcLeftTime.SetFont(&m_Font);
	m_stcElapsedTime.SetFont(&m_Font);
	m_stcCount.SetFont(&m_Font);
*/
	m_stcInfo.SetFont(&m_hFontBold);
	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update, _T(""));
	SetWindowText(strtmpMSG);
	
	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_Info, _T(""));
	m_stcInfo.SetWindowText(strtmpMSG);

	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_Text, _T(""));
	m_stcViewText.SetWindowText(strtmpMSG);

	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_Current, _T(""));
	m_stcCurrent.SetWindowText(strtmpMSG);

	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_Total, _T(""));
	m_stcTotal.SetWindowText(strtmpMSG);

	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_ElapsedTime, _T(""));
	m_stcElapsedTimeLabel.SetWindowText(strtmpMSG);

	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_LeftTime, _T(""));
	m_stcLeftTimeLabel.SetWindowText(strtmpMSG);

	AfxFormatString1(strtmpMSG, IDS_KOREAN_Dlg_Update_TransferRate, _T(""));
	m_stcTransferRateLabel.SetWindowText(strtmpMSG);
/*
	m_ctrlCurProg.SetBkColour(RGB(218,218,218));
//	m_ctrlCurProg.SetForeColour(RGB(172,211,115));
	m_ctrlCurProg.SetForeColour(RGB(141,198,63));
//	m_ctrlCurProg.SetTextForeColour();
	m_ctrlAllProg.SetBkColour(RGB(218,218,218));
	m_ctrlAllProg.SetForeColour(RGB(0,174,239));
//	m_ctrlAllProg.SetTextForeColour()
*/	
	DWORD dwRange = 100;
	SetAllProgressRange(dwRange);
	SetCurProgressRange(dwRange);
	dwRange = 0;
	SetAllProgress(dwRange);
	SetCurProgress(dwRange);

	m_stcCurFile.SetWindowText(_T(""));
	m_stcCount.SetWindowText(_T(""));
	m_stcTransferRate.SetWindowText(_T(""));
	m_stcLeftTime.SetWindowText(_T(""));
	m_stcElapsedTime.SetWindowText(_T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CUpdateDlg::UpdateUIDuringTransfer(UPDATE_TRANSNOTIFY* pNotify, DWORD& dwStartTicks, DWORD& dwCurrentTicks,
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
	m_ctrlAllProg.SetWindowText(m_strAllState);

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
}

// Elapsed Time Count UI Update
void CUpdateDlg::SetElapsedTime(DWORD& dwElapsedTime)
{
	CString sElapsedTime;
	if (dwElapsedTime < 60){
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwElapsedTime);
		AfxFormatString1(sElapsedTime, IDS_HTTPDOWNLOAD_SECONDS, sSeconds);
	}
	else{
		DWORD dwMinutes = dwElapsedTime / 60;
		DWORD dwSeconds = dwElapsedTime % 60;
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwSeconds);
		CString sMinutes;
		sMinutes.Format(_T("%d"), dwMinutes);

		if (dwSeconds == 0)
			AfxFormatString1(sElapsedTime, IDS_HTTPDOWNLOAD_MINUTES, sMinutes);
		else
			AfxFormatString2(sElapsedTime, IDS_HTTPDOWNLOAD_MINUTES_AND_SECONDS, sMinutes, sSeconds);
	}

	m_stcElapsedTime.SetWindowText(sElapsedTime);
}


// Left Time Count UI Update
void CUpdateDlg::SetTimeLeft(DWORD& dwSecondsLeft)
{
	CString sTimeLeft;
	if (dwSecondsLeft < 60){
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwSecondsLeft);
		AfxFormatString1(sTimeLeft, IDS_HTTPDOWNLOAD_SECONDS, sSeconds);
	}
	else{
		DWORD dwMinutes = dwSecondsLeft / 60;
		DWORD dwSeconds = dwSecondsLeft % 60;
		CString sSeconds;
		sSeconds.Format(_T("%d"), dwSeconds);
		CString sMinutes;
		sMinutes.Format(_T("%d"), dwMinutes);

		if (dwSeconds == 0)
			AfxFormatString1(sTimeLeft, IDS_HTTPDOWNLOAD_MINUTES, sMinutes);
		else
			AfxFormatString2(sTimeLeft, IDS_HTTPDOWNLOAD_MINUTES_AND_SECONDS, sMinutes, sSeconds);
	}

	m_stcLeftTime.SetWindowText(sTimeLeft);
}

// Transfer Rate UI Update
void CUpdateDlg::SetTransferRate(double& KbPerSecond)
{
	CString sRate;
	if (KbPerSecond < 1){
		CString sBytesPerSecond;
		sBytesPerSecond.Format(_T("%0.0f"), KbPerSecond*1024);
		AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_BYTESPERSECOND, sBytesPerSecond);
	}
	else if (KbPerSecond < 10){
		CString sKiloBytesPerSecond;
		sKiloBytesPerSecond.Format(_T("%0.2f"), KbPerSecond);
		AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
	}
	else{
		CString sKiloBytesPerSecond;
		sKiloBytesPerSecond.Format(_T("%0.0f"), KbPerSecond);
		AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
	}
  
	m_stcTransferRate.SetWindowText(sRate);

}


// Update UI Init State
void CUpdateDlg::UpdateUIInit(UPDATE_TRANSNOTIFY* pNotify)
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
	m_stcCurFile.SetWindowText(m_strCurFile);
	
	// Current File State
	m_strCurState.Format(_T("0 / %d KBytes"), (pNotify->nCurrentSize)/1024);
	m_ctrlCurProg.SetWindowText(m_strCurState);

	// Current File ProgressBar
	SetCurProgressRange(pNotify->nCurrentSize);
	DWORD dwZero = 0;
	SetCurProgress(dwZero);

	// All File State
	m_strCount.Format(_T("( %d / %d )"), pNotify->nCurrentCount, pNotify->nTotalCount);
	m_stcCount.SetWindowText(m_strCount);

	UpdateWindow();
}

//////////////////////////////////////////////////////////////////
// Progress Bar Range & Position Setting
void CUpdateDlg::SetCurProgressRange(DWORD& dwFileSize)
{
	m_ctrlCurProg.SetRange(0, (short)((dwFileSize+512)/1024));
}

void CUpdateDlg::SetCurProgress(DWORD& dwBytesRead)
{
	m_ctrlCurProg.SetPos(dwBytesRead/1024);
}

void CUpdateDlg::SetAllProgressRange(DWORD& dwFileSize)
{
	m_ctrlAllProg.SetRange(0, (short)((dwFileSize+512)/1024));
}

void CUpdateDlg::SetAllProgress(DWORD& dwBytesRead)
{															   
	m_ctrlAllProg.SetPos(dwBytesRead/1024);					   
}															   

void CUpdateDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	RECT rect;
	GetClientRect(&rect);
	rect.bottom = 72;
	::FillRect(dc.m_hDC, &rect, m_hBkBrush);

	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH CUpdateDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEXT || pWnd->GetDlgCtrlID() == IDC_STATIC_LOGO){
		pDC->SetBkMode(TRANSPARENT);
		hbr = m_hBkBrush;
	}

	return hbr;
}

void CUpdateDlg::AddComma(CString* pstrString)
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

void CUpdateDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	delete this;
}
int CUpdateDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
