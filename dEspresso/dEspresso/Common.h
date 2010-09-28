#define WIDGET_ITEM_WIDTH	92.5
#define WIDGET_ITEM_COUNT	4

#define WM_LAUNCH_WIDGET		WM_USER + 100

#define ID_WIDGET_CLOCK			1
#define ID_WIDGET_CALENDAR		2
#define ID_WIDGET_ADDRESSBOOK	3
#define ID_WIDGET_PICTURE		4
#define ID_WIDGET_SCRAP			5

#define EXE_WIDGET_CLOCK		_T("dEspresso_Clock.exe")
#define EXE_WIDGET_CALENDAR		_T("dEspresso_Calendar.exe")
#define EXE_WIDGET_ADDRESSBOOK	_T("dEspresso_Addressbook.exe")
#define EXE_WIDGET_PICTURE		_T("dEspresso_Picture.exe")
#define EXE_WIDGET_SCRAP		_T("dEspresso_Scrap.exe")


typedef struct _EXECUTE_WIDGET_INFO
{
	CString		executeBasePath;
	HANDLE		executeEventHandle;
	ULONG		lParam;

} EXECUTE_WIDGET_INFO, *PEXECUTE_WIDGET_INFO;
