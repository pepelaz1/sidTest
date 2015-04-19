
// SidTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SidTest.h"
#include "SidTestDlg.h"
#include "afxdialogex.h"
#include <Sddl.h>
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSidTestDlg dialog




CSidTestDlg::CSidTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSidTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSidTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPUTER_SID_EDIT, m_edtComputerSid);
	DDX_Control(pDX, IDC_COMPUTER_NAME_EDIT, m_edtComputerName);
}

BEGIN_MESSAGE_MAP(CSidTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GET, &CSidTestDlg::OnBnClickedButtonGet)
END_MESSAGE_MAP()


// CSidTestDlg message handlers

BOOL CSidTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSidTestDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSidTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSidTestDlg::OnBnClickedButtonGet()
{
	char name[100];
	DWORD length=100;
	GetComputerName(name, &length);

	std::string computerName(name);
	m_edtComputerName.SetWindowText(name);

    DWORD cbSid = 0;
    DWORD ReferencedDomainNameSize = 0;
 
    SID_NAME_USE eUse = SidTypeInvalid;
 
    BOOL resultOK = LookupAccountName(
        NULL,                   
        computerName.c_str(),      // like "computername"
        NULL,                      // address of SID buffer (to get size)
        &cbSid,                    // required size for SID
        NULL,                      // buffer for domain name (NULL to get size)
        &ReferencedDomainNameSize, // size of domain name string buffer
        &eUse);                     // kind of SID;

	std::vector<char> Sid(cbSid);       // allocate the SID buffer
	std::vector<char> ReferencedDomainName(ReferencedDomainNameSize); // ... buffer
 
    // Now the same with allocated buffers -- should be OK.
    resultOK = LookupAccountName(
        NULL,                   
        computerName.c_str(),      // like "computername"
        &Sid[0],                   // address of SID buffer
        &cbSid,                    // required size for SID
        &ReferencedDomainName[0],  // string buffer for domain name
        &ReferencedDomainNameSize, // size of domain name string buffer
        &eUse);                    // kind of SID
 
	 // Convert the SID to 
    char * pStringSid = NULL;
    resultOK = ConvertSidToStringSid(&Sid[0], &pStringSid);


	m_edtComputerSid.SetWindowText(pStringSid);

	if (pStringSid != NULL)
        LocalFree(pStringSid); // allocated by ConvertSidToStringSid()
}
