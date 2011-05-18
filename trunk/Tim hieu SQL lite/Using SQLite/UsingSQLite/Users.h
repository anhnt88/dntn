// Users.h: interface for the CUsers class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERS_H__BF886247_354E_44CC_9AC7_E3C9FCADE683__INCLUDED_)
#define AFX_USERS_H__BF886247_354E_44CC_9AC7_E3C9FCADE683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUsers  
{
public:
	void setName(CString strName);
	void setAddress(CString strAddress);
	void setAccount(CString strAccount);
	void setAlarmTime(COleDateTime date);
	CString m_strAccount;
	CString m_strName;
	CString m_strAddress;
	COleDateTime m_alarmTime;
	CUsers();
	virtual ~CUsers();

};

#endif // !defined(AFX_USERS_H__BF886247_354E_44CC_9AC7_E3C9FCADE683__INCLUDED_)
