// Users.cpp: implementation of the CUsers class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UsingSQLite.h"
#include "Users.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsers::CUsers()
{
	m_strAccount="";
	m_strAddress="";
	m_strName="";
}

CUsers::~CUsers()
{

}

void CUsers::setAccount(CString strAccount)
{
	m_strAccount=strAccount;
}

void CUsers::setName(CString strName)
{
	m_strName=strName;
}

void CUsers::setAddress(CString strAddress)
{
	m_strAddress=strAddress;
}

void CUsers::setAlarmTime(COleDateTime date)
{
	m_alarmTime=date;
}