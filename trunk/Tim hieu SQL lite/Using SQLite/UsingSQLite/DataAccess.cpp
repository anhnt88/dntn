// DataAccess.cpp: implementation of the CDataAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UsingSQLite.h"
#include "DataAccess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataAccess::CDataAccess()
{
// 	CString strPath;
// 	TCHAR szFullPath[512];
// 	TCHAR szDir[512];
// 	TCHAR szDrive[3];
// 	HINSTANCE hInst = AfxGetInstanceHandle();	
// 	GetModuleFileName(hInst, szFullPath, 256);
// 	_splitpath(szFullPath, szDrive, szDir, NULL, NULL);
// 	strPath.Format("%s%sdatabase.s3db", szDrive, szDir); 

	m_strPath="database.s3db";
	m_pDatabase=NULL;
}

CDataAccess::~CDataAccess()
{
	CloseDatabase();

}

void CDataAccess::SetPath(CString strPath)
{
	m_strPath=strPath;
}

void CDataAccess::CloseDatabase()
{
	if (m_pDatabase!=NULL)
	{
		//m_pDatabase->close();
		delete m_pDatabase;
		m_pDatabase = NULL;
	}	
}

int CDataAccess::OpenDatabase(CString strConnection)
{
	if (m_pDatabase==NULL)
		m_pDatabase = new CppSQLite3DB();
	else
	{
		m_pDatabase->close();
		delete m_pDatabase;
		m_pDatabase = new CppSQLite3DB();
	}
	try
	{
		if(m_pDatabase!=NULL)
		{
			m_pDatabase->open(strConnection);	
			return 0;
		}
		else
			return -1;
	}
	catch (CppSQLite3Exception e)
	{
		return -1;
	}
}

bool CDataAccess::GetUsers(std::vector<CUsers> & vUser)
{
	vUser.clear();
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CString sQuery="";
		try
		{	
			CppSQLite3Table t = m_pDatabase->getTable("select * from user order by 1;");
			for (int row = 0; row < t.numRows(); row++)
			{
				t.setRow(row);
				CUsers user;
				user.setAccount(t.fieldValue(0));
				user.setName(t.fieldValue(1));
				user.setAddress(t.fieldValue(2));

				COleDateTime time;
				time.m_dt=t.getFloatField(3);
				user.setAlarmTime(time);
				vUser.push_back(user);	
			}
		}
		catch (CppSQLite3Exception& e)
		{	
			//CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}	
		//CloseDatabase();
		return TRUE;
	}else
		return FALSE;
}

bool CDataAccess::GetUsers2(std::vector<CUsers> & vUser)
{
	vUser.clear();
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CString sQuery="select * from user;";
		CSQLite3Recordset rs(m_pDatabase);
		try
		{	
			rs.Open(sQuery, CSQLite3Recordset::openQuery);
			while (!rs.IsEof())
			{
				CUsers user;
				CString strTmp;
				rs.GetFieldValue("account", strTmp);
				user.setAccount(strTmp);
				rs.GetFieldValue(2, strTmp);
				user.setName(strTmp);
				user.setAddress(rs.fieldValue(3));
				COleDateTime date;
				rs.GetFieldValue("AlarmTime", date);
				user.setAlarmTime(date);
				vUser.push_back(user);
				
				rs.MoveNext();
			}
			rs.Close();
		}
		catch (CppSQLite3Exception& e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}	
		CloseDatabase();
		return TRUE;
	}else
		return FALSE;
}

bool CDataAccess::GetUser(CString strAccount, CUsers & user)
{
	
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CString strQuery="";
		CSQLite3Recordset rs(m_pDatabase);
		strQuery.Format("select * from user where account='%s';", strAccount);
		try
		{
			rs.Open(strQuery, CSQLite3Recordset::openQuery);
	
			user.setAccount(rs.fieldValue("account"));
			user.setName(rs.fieldValue(2));
			user.setAddress(rs.fieldValue(3));
			COleDateTime date;
			rs.GetFieldValue("AlarmTime", date);
			user.setAlarmTime(date);

			rs.Close();
			CloseDatabase();
			return TRUE;
		
		}
		catch (CppSQLite3Exception& e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}	
	}else
		return FALSE;
}

bool CDataAccess::AddUser(CUsers user)
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CString strQuery="";
		try
		{	
			strQuery.Format("INSERT INTO user VALUES ('%s', '%s', '%s', '%f');", user.m_strAccount, user.m_strName, user.m_strAddress, user.m_alarmTime.m_dt);
			
			m_pDatabase->execDML(strQuery);
			
		}
		catch (CppSQLite3Exception& e)
		{	
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}	
		CloseDatabase();
		return TRUE;
	}else
		return FALSE;
}

bool CDataAccess::DelUser(CString strAccount)
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CString strQuery="";
		strQuery.Format("DELETE FROM user WHERE account='%s';", strAccount);
		CSQLite3Recordset rs(m_pDatabase);
		try
		{				
			rs.Open(strQuery, CSQLite3Recordset::openQuery);

			//Phai close recordset truoc khi close database
			//Neu khong thi khong can close cai nao ca
			rs.Close();
			CloseDatabase();
			return TRUE;
		}
		catch (CppSQLite3Exception& e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}	
	}else
		return FALSE;
}

bool CDataAccess::UpdateUser(CUsers user, CString strAccount)
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		CString strQuery="";
		strQuery.Format("UPDATE user SET account='%s', name='%s', address='%s' , AlarmTime='%f' WHERE account='%s';", user.m_strAccount, user.m_strName, user.m_strAddress, user.m_alarmTime.m_dt, strAccount);
		try
		{
			rs.Open(strQuery, CSQLite3Recordset::openQuery);
		}
		catch (CppSQLite3Exception& e)
		{	
			//CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}	
		//CloseDatabase();
		return TRUE;
	}else
		return FALSE;
}

BOOL CDataAccess::TestAddNew()
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		try
		{
			if (rs.Open("user", CSQLite3Recordset::openTable))
			{	
				for (int i=0;i<10;i++)
				{
					CString strName;
					strName.Format("Name %d", i);
					rs.AddNew();
					rs.SetFieldValue("account", strName);
					rs.SetFieldValue(2, "Nguyen Thi Mai Xuan");
					rs.SetFieldValue(3, "Ha Giang");
					rs.SetFieldValue(3, "Hai Duong");
					rs.SetFieldValue(4, COleDateTime::GetCurrentTime());
					
					rs.Update();
					
					rs.GetFieldValue("account", strName);
					//	AfxMessageBox(strName);
				}
				rs.Close();
				CloseDatabase();
				return TRUE;
			}
			else
			{
				rs.Close();
				CloseDatabase();
				return FALSE;
			}
		}
		catch (CppSQLite3Exception e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}
	}
	else
		return FALSE;
}

BOOL CDataAccess::TestEdit()
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		try
		{
			m_pDatabase->BeginTransaction();
			if (rs.Open("select * from user where account='anhnt'", CSQLite3Recordset::openQuery))
			{
				if (rs.GetRecordCount()>0)
				{
					rs.Edit();
					//rs.SetFieldValue("account", "maixuan");
					rs.SetFieldValue(2, "Nguyen Tua Anh");
					rs.SetFieldValue("address", "Ha Giang");
					//	rs.SetFieldValue(3, "Hai Duong");
					rs.SetFieldValue(4, COleDateTime::GetCurrentTime());
					
					rs.Update();
					
					CString strName;
					rs.GetFieldValue("account", strName);
				//	AfxMessageBox(strName);
				}
				
				m_pDatabase->CommitTransaction();
				rs.Close();
				CloseDatabase();
				return TRUE;
			}
			else
			{
				rs.Close();
				CloseDatabase();
				return FALSE;
			}
		}
		catch (CppSQLite3Exception e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}
	}
	else
		return FALSE;
}

BOOL CDataAccess::TestEdit2()
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		try
		{
			m_pDatabase->BeginTransaction();
			if (rs.Open("select * from user where account='thunn'", CSQLite3Recordset::openQuery))
			{
				if (rs.GetRecordCount()>0)
				{
					rs.Edit();
					//rs.SetFieldValue("account", "maixuan");
					rs.SetFieldValue(2, "Nguyen Tua Anh");
					rs.SetFieldValue("address", "Ha Giang");
					//	rs.SetFieldValue(3, "Hai Duong");
					rs.SetFieldValue(4, COleDateTime::GetCurrentTime());
					
					rs.Update();
					
					CString strName;
					rs.GetFieldValue("account", strName);
					//	AfxMessageBox(strName);
				}
				Sleep(60000);
				m_pDatabase->CommitTransaction();
				rs.Close();
				CloseDatabase();
				return TRUE;
			}
			else
			{
				rs.Close();
				CloseDatabase();
				return FALSE;
			}
		}
		catch (CppSQLite3Exception e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}
	}
	else
		return FALSE;
}

BOOL CDataAccess::TesThreadReadDB(CString &strResult)
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		try
		{
			if (rs.Open("user", CSQLite3Recordset::openTable))
			{	
				rs.GetFieldValue("account", strResult);
				rs.Close();
				CloseDatabase();
				return TRUE;
			}
			else
			{
				rs.Close();
				CloseDatabase();
				return FALSE;
			}
		}
		catch (CppSQLite3Exception e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}
	}
	else
		return FALSE;
}

BOOL CDataAccess::TesThreadInsert(const CString & strValue)
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		try
		{
			CString strQuery;
			strQuery.Format("Insert into user1 (name) Values('%s')",strValue);
			if (rs.Open(strQuery, CSQLite3Recordset::openQuery))
			{	
				rs.Close();
				CloseDatabase();
				return TRUE;
			}
			else
			{
				rs.Close();
				CloseDatabase();
				return FALSE;
			}
		}
		catch (CppSQLite3Exception e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}
	}
	else
		return FALSE;
}


BOOL CDataAccess::TestEditLoop()
{
	if (m_strPath=="") {
		AfxMessageBox("Database path is invalid!");
		return FALSE;
	}	
	if(OpenDatabase(m_strPath)==0)
	{
		CSQLite3Recordset rs(m_pDatabase);
		try
		{
			CString strQuery;
			strQuery.Format("SELECT * FROM User WHERE name='%s'", "tuan anh");
			if (rs.Open(strQuery, CSQLite3Recordset::openQuery))
			{	
				BOOL bIsE=rs.IsEmpty();
				if (!bIsE)
				{
					while(!rs.IsEof())
					{
						rs.Edit();
						rs.SetFieldValue("address", "Hai Duong");
						rs.Update();

						rs.MoveNext();
					}
				}
				rs.Close();
				CloseDatabase();
				return TRUE;
			}
			else
			{
				rs.Close();
				CloseDatabase();
				return FALSE;
			}
		}
		catch (CppSQLite3Exception e)
		{	
			rs.Close();
			CloseDatabase();
			AfxMessageBox(e.errorMessage());
			return FALSE;
		}
	}
	else
		return FALSE;
}