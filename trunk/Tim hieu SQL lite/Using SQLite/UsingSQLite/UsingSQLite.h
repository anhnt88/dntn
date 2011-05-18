// UsingSQLite.h : main header file for the USINGSQLITE application
//

#if !defined(AFX_USINGSQLITE_H__BA28A280_9C9A_4880_99CE_5AF10B7DF5AE__INCLUDED_)
#define AFX_USINGSQLITE_H__BA28A280_9C9A_4880_99CE_5AF10B7DF5AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUsingSQLiteApp:
// See UsingSQLite.cpp for the implementation of this class
//

class CUsingSQLiteApp : public CWinApp
{
public:
	CUsingSQLiteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingSQLiteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsingSQLiteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGSQLITE_H__BA28A280_9C9A_4880_99CE_5AF10B7DF5AE__INCLUDED_)
