// dEspressoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "WidgetList.h"

// CdEspressoDlg dialog
class CdEspressoDlg : public CDialog
{
// Construction
public:
	CdEspressoDlg(CWnd* pParent = NULL);	// standard constructor
	~CdEspressoDlg();

// Dialog Data
	enum { IDD = IDD_DESPRESSO_DIALOG };

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
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedPrevwidget();
	afx_msg void OnBnClickedNextwidget();
	CStatic m_ctrlWidgetList;
	CWidgetList* m_widgetList;

private:
	LONG scrollLeft;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
