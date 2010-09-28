// WidgetList.cpp : implementation file
//

#include "stdafx.h"
#include "dEspresso.h"
#include "WidgetList.h"
#include "Common.h"

// CWidgetList dialog

IMPLEMENT_DYNAMIC(CWidgetList, CDialog)

CWidgetList::CWidgetList(CWnd* pParent /*=NULL*/)
	: CDialog(CWidgetList::IDD, pParent)
{
	MakeBasePath();
}

CWidgetList::~CWidgetList()
{
}

void CWidgetList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWidgetList, CDialog)
	ON_BN_CLICKED(IDC_CLOCK, &CWidgetList::OnBnClickedClock)
	ON_BN_CLICKED(IDC_CALENDAR, &CWidgetList::OnBnClickedCalendar)
	ON_BN_CLICKED(IDC_ADDRESSBOOK, &CWidgetList::OnBnClickedAddressbook)
	ON_BN_CLICKED(IDC_SCRAP, &CWidgetList::OnBnClickedScrap)
	ON_BN_CLICKED(IDC_PICTURE, &CWidgetList::OnBnClickedPicture)
	ON_MESSAGE(WM_LAUNCH_WIDGET, LaunchWidget)
END_MESSAGE_MAP()

void CWidgetList::MakeBasePath()
{	
	CString strTmp;
	LPWCH buf = (LPWCH)malloc(MAX_PATH);
	GetModuleFileName(AfxGetApp()->m_hInstance, buf, MAX_PATH);
	
	strTmp.Format(_T("%s"), buf);

    m_strCurrentPath = strTmp.Left( strTmp.ReverseFind( '\\' ) );
	m_strCurrentPath += "\\";
}

static void LaunchWidgetThread(LPVOID wParam)
{
	HINSTANCE hInst;
	EXECUTE_WIDGET_INFO* exeInfo = (EXECUTE_WIDGET_INFO*)wParam;
	if(exeInfo == NULL) return;

	switch(exeInfo->lParam) {
		case ID_WIDGET_CLOCK:
			hInst = ::ShellExecute(
				NULL, _T("open"), 
				EXE_WIDGET_CLOCK, 
				NULL, 
				exeInfo->executeBasePath, 
				SW_NORMAL); 
			break;

		case ID_WIDGET_CALENDAR:
			hInst = ::ShellExecute(
				NULL, _T("open"), 
				EXE_WIDGET_CALENDAR, 
				NULL, 
				exeInfo->executeBasePath, 
				SW_NORMAL); 
			break;

		case ID_WIDGET_ADDRESSBOOK:
			hInst = ::ShellExecute(
				NULL, _T("open"), 
				EXE_WIDGET_ADDRESSBOOK, 
				NULL, 
				exeInfo->executeBasePath, 
				SW_NORMAL); 
			break;

		case ID_WIDGET_PICTURE:
			hInst = ::ShellExecute(
				NULL, _T("open"), 
				EXE_WIDGET_PICTURE, 
				NULL, 
				exeInfo->executeBasePath, 
				SW_NORMAL); 
			break;

		case ID_WIDGET_SCRAP:
			hInst = ::ShellExecute(
				NULL, _T("open"), 
				EXE_WIDGET_SCRAP, 
				NULL, 
				exeInfo->executeBasePath, 
				SW_NORMAL); 
			break;
	}
	SetEvent( exeInfo->executeEventHandle );  
}

// CWidgetList message handlers
LRESULT CWidgetList::LaunchWidget(WPARAM wParam, LPARAM lParam) 
{
	HANDLE m_hThreadEndEvent = ::CreateEvent(NULL , TRUE, FALSE, NULL );

	EXECUTE_WIDGET_INFO exeInfo;
	exeInfo.executeBasePath = m_strCurrentPath;
	exeInfo.executeEventHandle = m_hThreadEndEvent;
	exeInfo.lParam = (int)wParam;

	CWinThread* m_pUpdateThread;
	m_pUpdateThread = AfxBeginThread((AFX_THREADPROC)LaunchWidgetThread, (LPVOID)&exeInfo);
	ResetEvent( m_hThreadEndEvent );

	if(m_pUpdateThread){
		DWORD wait = ::WaitForSingleObject(m_hThreadEndEvent, INFINITE);
	}
	return 0L;
}

void CWidgetList::OnBnClickedClock()
{
	SendMessage(WM_LAUNCH_WIDGET, ID_WIDGET_CLOCK);
}

void CWidgetList::OnBnClickedCalendar()
{
	SendMessage(WM_LAUNCH_WIDGET, ID_WIDGET_CALENDAR);
}

void CWidgetList::OnBnClickedAddressbook()
{
	SendMessage(WM_LAUNCH_WIDGET, ID_WIDGET_ADDRESSBOOK);
}

void CWidgetList::OnBnClickedPicture()
{
	SendMessage(WM_LAUNCH_WIDGET, ID_WIDGET_PICTURE);
}

void CWidgetList::OnBnClickedScrap()
{
	SendMessage(WM_LAUNCH_WIDGET, ID_WIDGET_SCRAP);
}