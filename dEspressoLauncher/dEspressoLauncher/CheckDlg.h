#pragma once


// CCheckDlg dialog

class CCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckDlg)

public:
	CCheckDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckDlg();

// Dialog Data
	enum { IDD = IDD_CHECK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
