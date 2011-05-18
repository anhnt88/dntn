#if !defined(AFX_ADDUSER_H__B2A704F5_DB3E_462D_9408_EBDC9EB42C78__INCLUDED_)
#define AFX_ADDUSER_H__B2A704F5_DB3E_462D_9408_EBDC9EB42C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddUser dialog

class CAddUser : public CDialog
{
// Construction
public:
	BOOL m_bUpdate;
	CAddUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddUser)
	enum { IDD = IDD_ADD_USER };
	CEdit	m_ctlAcount;
	CString	m_strAccount;
	CString	m_strAddress;
	CString	m_strName;
	COleDateTime	m_time;
	COleDateTime	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddUser)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDUSER_H__B2A704F5_DB3E_462D_9408_EBDC9EB42C78__INCLUDED_)
