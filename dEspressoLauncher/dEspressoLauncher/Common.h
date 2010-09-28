#define UPDATE_DLL _T("dEspressoUpdate.dll")
#define UPDATE_XML _T("dEspressoUpdate.xml")
//#define UPDATE_URL _T("http://www.dcafe.net/update/dEspressoUpdate.xml")
#define UPDATE_URL _T("http://www.dcafe.net/update/dEspressoUpdate.xml")
#define PROGRAM_NAME _T("dEspresso")
#define TRIGGER_PROGRAM _T("dEspresso.exe")

#define WM_USER_SEND			WM_USER+100
#define WM_USER_UPDATE_CLOSE	WM_USER+101
#define WM_USER_ASK_MSG			WM_USER+102

#define CHECK_TIMER				1000
#define CHECK_RUN_TIMER			1001

typedef void (*UPDATE_TRANS_NOTIFYFUNC)	(ULONG);
typedef struct _UPDATE_TRANSINFO
{
	const char*		lpszSrcURL;
	const char*		lpszDestXmlFile;
	//#ifdef _V3
	int				bNewCreateFile;
	const char*		lpszFileType;
	//#endif // _V3
	HWND			hNotifyWnd;
	UINT			nNotifyMsg;
	UINT			nRebootAskMsg;
	int				nRebootAskResult;

	UPDATE_TRANS_NOTIFYFUNC	pNotifyFunc;
	int				nErrno;
	ULONG			lParam;

	const char*		lpszURLLoginId;
	const char*		lpszURLLoginPassword;	
} UPDATE_TRANSINFO, *PUPDATE_TRANSINFO;


typedef struct _UPDATE_TRANSNOTIFY
{
	PUPDATE_TRANSINFO	pInfo;
	
	unsigned long		nTotalPos;
	unsigned long		nSendPos;
	unsigned long		nRequiredTime;
	int					nErrno;
	
	int					nTotalCount;
	int					nCurrentCount;

	unsigned long		nCurrentSize;
	unsigned long		nTotalSize;

	char*				lpszName;
	char*				lpszVersion;
	char*				lpszDownURL;
	char*				lpszDownPath;
	char*				lpszDescription;
	
	ULONG				lParam;

} UPDATE_TRANSNOTIFY, *PUPDATE_TRANSNOTIFY;


// error
#define UPDATE_ERROR_UNKNOWN					-1
#define UPDATE_ERROR_NONE						1
#define UPDATE_ERROR_INFORMATION				2
#define UPDATE_ERROR_FAIL_DOWNLOADXMLFILE		3
#define UPDATE_ERROR_FILE_NOT_FOUND				4

#define UPDATE_ERROR_CANT_MAKE_ITEMLIST_SOURCE	5
#define UPDATE_ERROR_CANT_MAKE_ITEMLIST_DEST	6

#define UPDATE_ERROR_CANT_READ_XML_SOURCE		7
#define UPDATE_ERROR_CANT_READ_XML_DEST			8

#define UPDATE_ERROR_CANT_OPEN_XML_FILE			9
#define UPDATE_ERROR_CANT_MAKE_XML_FILE			10

#define UPDATE_ERROR_CANT_MAKE_DOWNLOAD_THREAD	11

#define UPDATE_ERROR_NONE_NOT_EXECUTE				12
#define UPDATE_ERROR_NONE_NOT_EXECUTE_AND_REBOOT	13

#define UPDATE_SUCCESS_REGSVR_DLL				100
#define UPDATE_ERROR_DLL_LOAD_LIBRARY			101
#define UPDATE_ERROR_DLL_GET_PROC_ADDRESS		102

#define UPDATE_HTTP_FAIL_PARSE_URL 						301
#define UPDATE_HTTP_FAIL_INTERNET_SESSION				302
#define UPDATE_HTTP_FAIL_INTERNET_CONNECTION			303
#define UPDATE_HTTP_FAIL_INTERNET_OPEN_REQUEST			304
#define UPDATE_HTTP_FAIL_INTERNET_SEND_REQUEST 			305
#define UPDATE_HTTP_FAIL_INTERNET_QUERY_STATUS_CODE		306
#define UPDATE_HTTP_FAIL_INTERNET_QUERY_CONTENT_LENGTH 	307
#define UPDATE_HTTP_FAIL_INTERNET_CREATE_FILE			308
#define UPDATE_HTTP_FAIL_INTERNET_READ_FILE				309
#define UPDATE_HTTP_FAIL_INTERNET_STATUS_DENIED			310
#define UPDATE_HTTP_FAIL_INTERNET_STATUS_NOT_FOUND		311
#define UPDATE_HTTP_FAIL_INTERNET_OTHER_FAIL			312
#define UPDATE_HTTP_FAIL_PARSE_DOWN_PATH 				313
#define UPDATE_HTTP_FAIL_CANCEL			 				314
#define UPDATE_HTTP_FAIL_INTERNET_CREATE_FILE_HIDE		315
#define UPDATE_HTTP_FAIL_INTERNET_CREATE_FILE_REBOOT	316