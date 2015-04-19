
// SidTestDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CSidTestDlg dialog
class CSidTestDlg : public CDialogEx
{
// Construction
public:
	CSidTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SIDTEST_DIALOG };

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
	CEdit m_edtComputerSid;
	afx_msg void OnBnClickedButtonGet();
	CEdit m_edtComputerName;
};
