// UpdateDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "UpdateDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDllApp

BEGIN_MESSAGE_MAP(CUpdateDllApp, CWinApp)
	//{{AFX_MSG_MAP(CUpdateDllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDllApp construction

CUpdateDllApp::CUpdateDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUpdateDllApp object

CUpdateDllApp theApp;
CItemListAgent g_ItemListAgent;

BOOL CUpdateDllApp::InitInstance() 
{

	g_ItemListAgent.RemoveAll();

	return CWinApp::InitInstance();
}

int CUpdateDllApp::ExitInstance() 
{
	
	g_ItemListAgent.RemoveAll();
	
	return CWinApp::ExitInstance();
}

UPDATE_DLLEXPORT 
BOOL WINAPI StartUpdate(PUPDATE_TRANSINFO pInfo, BOOL *pbCancel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (g_ItemListAgent.Start(pInfo, pbCancel));
}
