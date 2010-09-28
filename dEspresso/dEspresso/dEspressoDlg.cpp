// dEspressoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dEspresso.h"
#include "dEspressoDlg.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdEspressoDlg dialog
CdEspressoDlg::CdEspressoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdEspressoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_widgetList = new CWidgetList;
	scrollLeft = 0; // scroll left
}

CdEspressoDlg::~CdEspressoDlg() {
	if(m_widgetList) {
		delete m_widgetList;
	}
}

void CdEspressoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WIDGETLIST_PLACEHOLDER, m_ctrlWidgetList);
}

BEGIN_MESSAGE_MAP(CdEspressoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PREVWIDGET, &CdEspressoDlg::OnBnClickedPrevwidget)
	ON_BN_CLICKED(IDC_NEXTWIDGET, &CdEspressoDlg::OnBnClickedNextwidget)
	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CdEspressoDlg message handlers

BOOL CdEspressoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if(!::IsWindow(m_widgetList->GetSafeHwnd()))
        m_widgetList->Create(IDD_WIDGETLIST, &m_ctrlWidgetList);
    m_widgetList->ShowWindow(SW_SHOW); 


	// width
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	// height
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);


	CRect rect;
	GetWindowRect(&rect);
	LONG width = rect.right - rect.left;
	LONG height = rect.bottom - rect.top;

	MoveWindow(
		cx - width, 
		cy - height, 
		width, 
		height, 
		TRUE);
	UpdateWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CdEspressoDlg::OnPaint()
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
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CdEspressoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CdEspressoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	return 0;
}

void CdEspressoDlg::OnBnClickedPrevwidget()
{
	CRect rect;
	m_widgetList->GetWindowRect(&rect);
	m_widgetList->ScreenToClient(&rect);

	if(scrollLeft < 0) {
		for(int i=0; i<WIDGET_ITEM_WIDTH; i++) {
			Sleep(3);
			m_widgetList->MoveWindow(++scrollLeft, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
			UpdateWindow();
		}
	}
}

void CdEspressoDlg::OnBnClickedNextwidget()
{
	CRect rect;
	m_widgetList->GetWindowRect(&rect);
	m_widgetList->ScreenToClient(&rect);

	if(scrollLeft > -(WIDGET_ITEM_WIDTH * (WIDGET_ITEM_COUNT - 3))) {
		for(int i=0; i<WIDGET_ITEM_WIDTH; i++) {
			Sleep(3);
			m_widgetList->MoveWindow(--scrollLeft, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
			UpdateWindow();
		}
	}
}

void CdEspressoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	SendMessage(WM_MOUSEMOVE);

	CDialog::OnLButtonDown(nFlags, point);
}
