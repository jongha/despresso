#pragma once


// CWidgetList dialog

class CWidgetList : public CDialog
{
	DECLARE_DYNAMIC(CWidgetList)

public:
	CWidgetList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWidgetList();

// Dialog Data
	enum { IDD = IDD_WIDGETLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedClock();
	afx_msg void OnBnClickedCalendar();
	afx_msg void OnBnClickedAddressbook();
	afx_msg void OnBnClickedScrap();
	afx_msg void OnBnClickedPicture();
	afx_msg LRESULT LaunchWidget(WPARAM, LPARAM);
	
private:
	CString m_strCurrentPath;
	void MakeBasePath();
};
