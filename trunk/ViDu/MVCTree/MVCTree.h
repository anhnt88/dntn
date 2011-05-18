// MVCTree.h : main header file for the MVCTREE application
//

#if !defined(AFX_MVCTREE_H__D63B3EB4_87BA_4A48_923E_2F3B4B096F2D__INCLUDED_)
#define AFX_MVCTREE_H__D63B3EB4_87BA_4A48_923E_2F3B4B096F2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMVCTreeApp:
// See MVCTree.cpp for the implementation of this class
//

class CMVCTreeApp : public CWinApp
{
public:
	CMVCTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVCTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMVCTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVCTREE_H__D63B3EB4_87BA_4A48_923E_2F3B4B096F2D__INCLUDED_)
