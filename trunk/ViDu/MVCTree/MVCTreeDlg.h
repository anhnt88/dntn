// MVCTreeDlg.h : header file
//

#if !defined(AFX_MVCTREEDLG_H__EA37B528_789F_4822_B5D3_536BA60715B6__INCLUDED_)
#define AFX_MVCTREEDLG_H__EA37B528_789F_4822_B5D3_536BA60715B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTree.h"

/////////////////////////////////////////////////////////////////////////////
// CMVCTreeDlg dialog

class CMVCTreeDlg : public CDialog
{
// Construction
public:
	CMVCTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMVCTreeDlg)
	enum { IDD = IDD_MVCTREE_DIALOG };
	CMyTree	m_ctrlTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVCTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMVCTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVCTREEDLG_H__EA37B528_789F_4822_B5D3_536BA60715B6__INCLUDED_)
