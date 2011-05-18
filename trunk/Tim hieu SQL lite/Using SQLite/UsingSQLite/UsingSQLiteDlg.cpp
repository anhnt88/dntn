// UsingSQLiteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UsingSQLite.h"
#include "UsingSQLiteDlg.h"
#include "DataAccess.h"
#include "Users.h"
#include "AddUser.h"
//#include "SQLite3Recordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsingSQLiteDlg dialog

CUsingSQLiteDlg::CUsingSQLiteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUsingSQLiteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUsingSQLiteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsingSQLiteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsingSQLiteDlg)
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_BTN_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BTN_REFRESH, m_btnRefresh);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDe);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResultView);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUsingSQLiteDlg, CDialog)
	//{{AFX_MSG_MAP(CUsingSQLiteDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_GETTABLE, OnBtnGettable)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_TEST, OnTestRs)
	ON_BN_CLICKED(IDC_RSEDIT, OnRsedit)
	ON_BN_CLICKED(IDC_THREAD1, OnThread1)
	ON_BN_CLICKED(IDC_THREAD2, OnThread2)
	ON_BN_CLICKED(IDC_STOPTHREAD1, OnStopthread1)
	ON_BN_CLICKED(IDC_STOPTHREAD2, OnStopthread2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsingSQLiteDlg message handlers

BOOL CUsingSQLiteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_listResultView.SetExtendedStyle(LVS_REPORT|LVS_EX_FULLROWSELECT);
	m_listResultView.InsertColumn(0, "Account", LVCFMT_LEFT, 70);
	m_listResultView.InsertColumn(1, "Name", LVCFMT_LEFT, 150);
	m_listResultView.InsertColumn(2, "Address", LVCFMT_LEFT, 100);
	m_listResultView.InsertColumn(3, "Alarm Time", LVCFMT_LEFT, 140);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUsingSQLiteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUsingSQLiteDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUsingSQLiteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUsingSQLiteDlg::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	std::vector<CUsers> vUsers;
	CDataAccess db;

	if(db.GetUsers2(vUsers))//dung sql query
	{
		m_listResultView.DeleteAllItems();
		for (int i=0; i<vUsers.size();i++)
		{
			m_listResultView.InsertItem(i, vUsers[i].m_strAccount);
			m_listResultView.SetItemText(i, 1, vUsers[i].m_strName);
			m_listResultView.SetItemText(i, 2, vUsers[i].m_strAddress);
			CString strDate;
			strDate=vUsers[i].m_alarmTime.Format("%H:%M:%S Ngµy %d-%m-%Y");
			
			m_listResultView.SetItemText(i, 3, strDate);
		}
	}
}

void CUsingSQLiteDlg::OnBtnGettable() 
{
	// TODO: Add your control notification handler code here
	std::vector<CUsers> vUsers;
	CDataAccess db;

	if(db.GetUsers(vUsers))
	{
		m_listResultView.DeleteAllItems();
		for (int i=0; i<vUsers.size();i++)//dung get_table
		{
			m_listResultView.InsertItem(i, vUsers[i].m_strAccount);
			m_listResultView.SetItemText(i, 1, vUsers[i].m_strName);
			m_listResultView.SetItemText(i, 2, vUsers[i].m_strAddress);
			CString strDate;
			strDate=vUsers[i].m_alarmTime.Format("%H:%M:%S Ngµy %d-%m-%Y");
			
			m_listResultView.SetItemText(i, 3, strDate);
		}
	}
}

void CUsingSQLiteDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	CAddUser userDlg;
	if (userDlg.DoModal()==IDOK)
	{
		if(userDlg.m_strAccount!="")
		{
			CUsers user;
			user.m_strAccount=userDlg.m_strAccount;
			user.m_strName=userDlg.m_strName;
			user.m_strAddress=userDlg.m_strAddress;
			user.m_alarmTime.SetDateTime(userDlg.m_date.GetYear(), userDlg.m_date.GetMonth(), userDlg.m_date.GetDay(), \
			userDlg.m_time.GetHour(), userDlg.m_time.GetMinute(), userDlg.m_time.GetSecond());
	

			std::vector<CUsers> vUsers;
			CDataAccess db;

			db.AddUser(user);

			OnBtnGettable();
		}
	}
}

void CUsingSQLiteDlg::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	pos=m_listResultView.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		//TRACE(_T("No items were selected!\n"));
	}
	else
	{
		int nItem = m_listResultView.GetNextSelectedItem(pos);
		//TRACE(_T("Item %d was selected!\n"), nItem);

		CString strAccount=m_listResultView.GetItemText(nItem, 0);
		CDataAccess db;
		CUsers user;

		db.GetUser(strAccount, user);

		CAddUser userDlg;
		userDlg.m_strAccount=user.m_strAccount;
		userDlg.m_strName=user.m_strName;
		userDlg.m_strAddress=user.m_strAddress;
		userDlg.m_date.SetDate(user.m_alarmTime.GetYear(), user.m_alarmTime.GetMonth(),user.m_alarmTime.GetDay());
		userDlg.m_time.SetTime(user.m_alarmTime.GetHour(), user.m_alarmTime.GetMinute(),user.m_alarmTime.GetSecond());
		if (userDlg.DoModal()==IDOK)
		{
			if(userDlg.m_strAccount!="")
			{
				user.m_strAccount=userDlg.m_strAccount;
				user.m_strName=userDlg.m_strName;
				user.m_strAddress=userDlg.m_strAddress;
				user.m_alarmTime.SetDateTime(userDlg.m_date.GetYear(), userDlg.m_date.GetMonth(), userDlg.m_date.GetDay(), \
											userDlg.m_time.GetHour(), userDlg.m_time.GetMinute(), userDlg.m_time.GetSecond());
				
				std::vector<CUsers> vUsers;
				CDataAccess db;
				db.UpdateUser(user, strAccount);
				
				OnBtnGettable();
			}
		}
	}	
}

void CUsingSQLiteDlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	pos=m_listResultView.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
	{
		//TRACE(_T("No items were selected!\n"));
	}
	else
	{
		while(pos!=NULL)
		{
			int nItem = m_listResultView.GetNextSelectedItem(pos);
			//TRACE(_T("Item %d was selected!\n"), nItem);
			
			CString strAccount=m_listResultView.GetItemText(nItem, 0);
			
			CDataAccess db;

			db.DelUser(strAccount);
		}
		
		OnBtnGettable();
	}	
}

void CUsingSQLiteDlg::OnTestRs() 
{
	// TODO: Add your control notification handler code here
	CDataAccess db;

	db.TestAddNew();

	OnBtnGettable();
}

void CUsingSQLiteDlg::OnRsedit() 
{
	// TODO: Add your control notification handler code here
	CDataAccess db;
	db.TestEdit();

	OnBtnGettable();
}

UINT threadInsert2(LPVOID pParam)
{
	CUsingSQLiteDlg *dlg=(CUsingSQLiteDlg*)pParam;
	int i=0;
	while(dlg->m_bRunningThread2)
	{
		CDataAccess data;
		CString strTmp="";
		
		COleDateTime d=COleDateTime::GetCurrentTime();
		float f=d.m_dt;
		strTmp.Format("%f",f);
		
		if(data.TestEdit()/*data.TesThreadInsert(strTmp)*/)
		{
			
		}
		
		dlg->m_list2.AddString(strTmp);
		
		if(i<32767)
			i++;
		else
		{
			dlg->m_list2.ResetContent();
			i=0;
		}
	}
	return 4;
}

UINT threadInsert1(LPVOID pParam)
{
	CUsingSQLiteDlg *dlg=(CUsingSQLiteDlg*)pParam;
	int i=0;
	while(dlg->m_bRunningThread1)
	{
		CDataAccess data;
		CString strTmp="";
		
		COleDateTime d=COleDateTime::GetCurrentTime();
		float f=d.m_dt;
		strTmp.Format("%f",f);
		
		if(data.TestEdit()/*data.TesThreadInsert(strTmp)*/)
		{
			
		}
		
		dlg->m_list1.AddString(strTmp);
		
		if(i<32767)
			i++;
		else
		{
			dlg->m_list1.ResetContent();
			i=0;
		}
	}
	return 3;
}

UINT threadProc1(LPVOID pParam)
{
	CUsingSQLiteDlg *dlg=(CUsingSQLiteDlg*)pParam;
	int i=0;
	while(dlg->m_bRunningThread1)
	{
		CDataAccess data;
		CString strResult="";
		CString strTmp="";

		CUsers user;
		
		user.m_strAccount="thunn";
		user.m_strName="Tuan Anh";
		user.m_strAddress="HD";

		if(data.UpdateUser(user, "thunn"))
		{
			strTmp.Format("%s -- %d", strResult, i);
			dlg->m_list1.InsertString(0,strTmp);
		}
	

		
		if(i<32767)
			i++;
		else
		{
			dlg->m_list1.ResetContent();
			i=0;
		}
	}
	return 1;
}

UINT threadProc2(LPVOID pParam)
{
	CUsingSQLiteDlg *dlg=(CUsingSQLiteDlg*)pParam;
	int i=0;
	while(dlg->m_bRunningThread2)
	{
		CDataAccess data;
		CString strResult="";
		CString strTmp="";

	CUsers user;
		
		user.m_strAccount="anhnt";
		user.m_strName="Tuan Anh";
		user.m_strAddress="HD";
	

		if(data.UpdateUser(user, "anhnt"))
		{
			strTmp.Format("%s -- %d", strResult, i);
			dlg->m_list2.InsertString(0, strTmp);
		}
		

		
		if(i<32767)
			i++;
		else
		{
			dlg->m_list2.ResetContent();
			i=0;
		}
	}
	return 2;
}

void CUsingSQLiteDlg::OnThread1() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STOPTHREAD1)->EnableWindow(TRUE);
	GetDlgItem(IDC_THREAD1)->EnableWindow(FALSE);

	m_bRunningThread1=true;
//	AfxBeginThread(threadProc1, this);
	AfxBeginThread(threadInsert1, this);
	
}

void CUsingSQLiteDlg::OnThread2() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STOPTHREAD2)->EnableWindow(TRUE);
	GetDlgItem(IDC_THREAD2)->EnableWindow(FALSE);

	m_bRunningThread2=true;
//	AfxBeginThread(threadProc2, this);
	AfxBeginThread(threadInsert2, this);
	
}

void CUsingSQLiteDlg::OnStopthread1() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_THREAD1)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOPTHREAD1)->EnableWindow(FALSE);
	m_bRunningThread1=false;


}

void CUsingSQLiteDlg::OnStopthread2() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_THREAD2)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOPTHREAD2)->EnableWindow(FALSE);
	m_bRunningThread2=false;
}



void CUsingSQLiteDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CDataAccess db;
	
	db.TestEditLoop();

	OnBtnRefresh();
	
}
