#if !defined(AFX_MYTREE_H__271F7E9E_A61E_4FB3_B9F0_1174F067294E__INCLUDED_)
#define AFX_MYTREE_H__271F7E9E_A61E_4FB3_B9F0_1174F067294E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTree.h : header file
//
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CMyTree window

class CMyTree : public CTreeCtrl
{
// Construction
public:
	CMyTree();

// Attributes
public:
	int m_nNumItem;
	std::vector<CString> m_vData;
// Operations
	void SetCheckChildValue(HTREEITEM hItem, BOOL bValue);
	void SetNodeCheckValue(HTREEITEM hItem, BOOL bValue);
	HTREEITEM InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTree)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREE_H__271F7E9E_A61E_4FB3_B9F0_1174F067294E__INCLUDED_)
