// UsingSQLiteDlg.h : header file
//

#if !defined(AFX_USINGSQLITEDLG_H__6D53B52F_9112_477E_8E66_D3759EE9695C__INCLUDED_)
#define AFX_USINGSQLITEDLG_H__6D53B52F_9112_477E_8E66_D3759EE9695C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUsingSQLiteDlg dialog

class CUsingSQLiteDlg : public CDialog
{
// Construction
public:
	CUsingSQLiteDlg(CWnd* pParent = NULL);	// standard constructor

	bool m_bRunningThread1;
	bool m_bRunningThread2;

// Dialog Data
	//{{AFX_DATA(CUsingSQLiteDlg)
	enum { IDD = IDD_USINGSQLITE_DIALOG };
	CListBox	m_list2;
	CListBox	m_list1;
	CButton	m_btnUpdate;
	CButton	m_btnRefresh;
	CButton	m_btnDe;
	CButton	m_btnAdd;
	CListCtrl	m_listResultView;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingSQLiteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUsingSQLiteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnGettable();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnUpdate();
	afx_msg void OnTestRs();
	afx_msg void OnRsedit();
	afx_msg void OnThread1();
	afx_msg void OnThread2();
	afx_msg void OnStopthread1();
	afx_msg void OnStopthread2();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGSQLITEDLG_H__6D53B52F_9112_477E_8E66_D3759EE9695C__INCLUDED_)
