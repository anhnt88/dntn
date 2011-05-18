// DataAccess.h: interface for the CDataAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAACCESS_H__12A0F330_8937_4806_8544_E2D1FC2B78D6__INCLUDED_)
#define AFX_DATAACCESS_H__12A0F330_8937_4806_8544_E2D1FC2B78D6__INCLUDED_

#include "Users.h"
#include <vector>

#include "CppSQLite3.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataAccess  
{
public:
	BOOL TestRowID();
	BOOL TestEditLoop();
	BOOL TesThreadInsert(const CString & strValues);
	BOOL TesThreadReadDB(CString& strResult);
	BOOL TestEdit2();
	BOOL TestEdit();
	BOOL TestAddNew();
	bool UpdateUser(CUsers user, CString strAccount);
	bool DelUser(CString strAccount);
	bool AddUser(CUsers user);
	bool GetUsers2(std::vector<CUsers> & vUser);
	bool GetUsers(std::vector<CUsers> & vUser);
	bool GetUser(CString strAccount, CUsers & User);
	
	void SetPath(CString strPath);	
	CDataAccess();
	virtual ~CDataAccess();

protected:
	void CloseDatabase();
	int OpenDatabase(CString strPath);
	CppSQLite3DB* m_pDatabase;
	CString m_strPath;


};

#endif // !defined(AFX_DATAACCESS_H__12A0F330_8937_4806_8544_E2D1FC2B78D6__INCLUDED_)
