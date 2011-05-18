// AddUser.cpp : implementation file
//

#include "stdafx.h"
#include "UsingSQLite.h"
#include "AddUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddUser dialog


CAddUser::CAddUser(CWnd* pParent /*=NULL*/)
	: CDialog(CAddUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddUser)
	m_strAccount = _T("");
	m_strAddress = _T("");
	m_strName = _T("");
	m_bUpdate = FALSE;
	m_time = COleDateTime::GetCurrentTime();
	m_date = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CAddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddUser)
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_ctlAcount);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_strAccount);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddUser, CDialog)
	//{{AFX_MSG_MAP(CAddUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddUser message handlers

BOOL CAddUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctlAcount.EnableWindow(!m_bUpdate);
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
