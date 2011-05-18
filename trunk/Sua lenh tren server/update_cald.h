int ResponseUPDATE_CLD_NEW(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
	enum ATTACH_CLD_NEW_ERROR_CODE
	{
		UPDATE_CLD_NEW_SUCCESS = 0,
		UPDATE_CLD_NEW_FAIL = 1
	};
	int iIndex = 0;
	int IgnoreConflict;
	CALENDAR_INFO Calendar;

	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,IgnoreConflict))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.CalendarID))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Version))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.StartTime))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.EndTime))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.RescureTime))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.LastUpdateTime))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.NotifyBeforeStartTime))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.CreatorEmail))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.LatsUpdatePerson))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.CalendarName))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Description))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Location))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.RescureType))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Blocking))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Priority))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Private))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Status))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.Notify))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.NotifyUpdate))
		return COMMAND_QUIT;
  
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.RecurrenceDay))
		return COMMAND_QUIT;
		
	Calendar.LatsUpdatePerson = lpPerSocketContext->m_strUser;
	int MenNum, GroupNum, DepNum, ResourceNum, TagNum;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,MenNum))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,GroupNum))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,DepNum))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,ResourceNum))
		return COMMAND_QUIT;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,TagNum))
		return COMMAND_QUIT;
 
	LIST_MEN_IN_CALENDAR *pListMen = new(LIST_MEN_IN_CALENDAR);
	if (pListMen == NULL) 
	{
		return COMMAND_QUIT;
	}
	LIST_RESOURCE_IN_CALENDAR *pListResource = new(LIST_RESOURCE_IN_CALENDAR);
	if (pListResource == NULL) 
	{
		delete pListMen;pListMen=NULL;
		return COMMAND_QUIT;
	}
	LIST_DEP_IN_CALENDAR *pListDep = new(LIST_DEP_IN_CALENDAR);
	if (pListDep == NULL) 
	{
		delete pListMen;pListMen=NULL;
		delete pListResource;pListResource=NULL;
		return COMMAND_QUIT;
	}
	LIST_GROUP_IN_CALENDAR *pListGroup = new(LIST_GROUP_IN_CALENDAR);
	if (pListGroup == NULL) 
	{
		delete pListMen;pListMen=NULL;
		delete pListResource;pListResource=NULL;
		delete pListDep;pListDep=NULL;
		return COMMAND_QUIT;
	}
	LIST_STRING *pListTag = new(LIST_STRING);
	if (pListTag == NULL) 
	{
		delete pListMen;pListMen=NULL;
		delete pListResource;pListResource=NULL;
		delete pListDep;pListDep=NULL;
		delete pListGroup;pListGroup=NULL;
		return COMMAND_QUIT;
	}
	int i = 0;
	for (i = 0; i < MenNum; i++) 
	{
		MEN_IN_CALENDAR man;
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Email))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Role))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		pListMen->push_back(man);
	}
	for (i = 0; i < GroupNum; i++) 
	{
		GROUP_IN_CALENDAR Group;
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.GroupID))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.Role))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		pListGroup->push_back(Group);
	}
	for (i = 0; i < DepNum; i++) 
	{
		DEP_IN_CALENDAR Dep;
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.DepID))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.Role))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		pListDep->push_back(Dep);
	}

	for (i = 0; i < ResourceNum; i++) 
	{
		RESOURCE_IN_CALENDAR Resource;
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.ResourceID))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.strUser))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.Quantity))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.strApprover))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.iPosition))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		pListResource->push_back(Resource);
	}
	for (i = 0; i < TagNum; i++) 
	{
		CString tag;
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,tag))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			return COMMAND_QUIT;
		}
		pListTag->push_back(tag);
	}
	LIST_CALENDAR_CONFLICT *pListConflict = new (LIST_CALENDAR_CONFLICT);
	bool bConflict = false;

	if (IgnoreConflict == 0) 
	{
		if (!FindConflict(&bConflict,&Calendar,pListMen,pListDep,pListGroup,pListResource,pListConflict,1))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			delete pListConflict;pListConflict=NULL;
			return COMMAND_QUIT;
		}
	} 
	if (!bConflict) 
	{
		UserConflictMap *pUserMap = new (UserConflictMap);
		if (pUserMap == NULL) 
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			delete pListConflict;pListConflict=NULL;
			return COMMAND_QUIT;
		}
		LIST_MAN_CONFLICT *pListInCalendar = new (LIST_MAN_CONFLICT);
		if (pListInCalendar == NULL) 
		{
			delete pUserMap;pUserMap=NULL;
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag; pListTag=NULL;
			delete pListConflict;pListConflict=NULL;
			return COMMAND_QUIT;
		}
		LIST_STRING *pListUserRemove = new (LIST_STRING);
		if (pListUserRemove == NULL) 
		{
			delete pListInCalendar;pListInCalendar=NULL;
			delete pUserMap;pUserMap=NULL;
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag;pListTag=NULL;
			delete pListConflict;pListConflict=NULL;
			return COMMAND_QUIT;
		}
		GetAllUserFromDepGroup(pListGroup,pListDep,pListMen,pUserMap);
		GetAllUserInCalendar(Calendar.CalendarID,pListInCalendar);
		for (i = 0; i<pListInCalendar->size(); i++) 
		{
			MAN_CONFLICT manConflict;
			if (0 == pUserMap->Lookup(pListInCalendar->at(i).Email,manConflict)) 
			{
			pListUserRemove->push_back(manConflict.Email);
			}
		}
		CALENDAR_INFO calendOld,calendNew;
		GetCalendar(Calendar.CalendarID,calendOld);
		ETASK_LOG log;
		log.iType=2;
		log.strUser=lpPerSocketContext->m_strUser;
		log.logTime=COleDateTime::GetCurrentTime();
		NotifyCalendarRemove(Calendar.CalendarID,pListUserRemove);
		delete pListUserRemove;pListUserRemove=NULL;
		delete pUserMap;pUserMap=NULL;
		
		UpdateCalendarToDatabaseNew(&Calendar,pListMen,pListDep,pListGroup,pListResource);
		UpdateCalendarToResourceXetDuyetTbl(&Calendar,pListResource,lpPerSocketContext->m_strUser);
		NotifyCalendarToMember(&Calendar,pListMen,pListDep,pListGroup,pListResource,CALENDAR_UPDATE);
		GetCalendar(Calendar.CalendarID,calendNew);
		CompareCalendar(calendOld,calendNew,log.strDescription);
		AddNewLog(log);
		SendUpdateMailCal(Calendar,pListMen);
		delete pListInCalendar;pListInCalendar=NULL;
	} 
	delete pListMen;pListMen=NULL;
	delete pListResource;pListResource=NULL;
	delete pListDep;pListDep=NULL;
	delete pListGroup;pListGroup=NULL;
	delete pListTag;pListTag=NULL;

	CInfoStruct info_struct;
	info_struct.AddData(Calendar.CalendarID);
	info_struct.AddData(pListConflict->size());
	for (i = 0; i < pListConflict->size(); i++ ) 
	{
		info_struct.AddData(pListConflict->at(i).CalendarID);
		info_struct.AddData(pListConflict->at(i).CalendarName);
		info_struct.AddData(pListConflict->at(i).StartTime);
		info_struct.AddData(pListConflict->at(i).EndTime);
		info_struct.AddData(pListConflict->at(i).RescureType);
		info_struct.AddData(pListConflict->at(i).Blocking);
		info_struct.AddData(pListConflict->at(i).EmailCreator);
		info_struct.AddData(pListConflict->at(i).CreateTime);
		info_struct.AddData(pListConflict->at(i).ListMen.size());
		info_struct.AddData(pListConflict->at(i).ListResource.size());
		int j;
		for ( j = 0; j < pListConflict->at(i).ListMen.size(); j++) 
		{
			info_struct.AddData(pListConflict->at(i).ListMen.at(j).Email);
			info_struct.AddData(pListConflict->at(i).ListMen.at(j).Status);
		}
		for ( j = 0; j < pListConflict->at(i).ListResource.size(); j++) 
		{
			info_struct.AddData(pListConflict->at(i).ListResource.at(j).ResourceID);
			info_struct.AddData(pListConflict->at(i).ListResource.at(j).Status);
		}
	}
	delete pListConflict;
	int iTotalSize = 0;
	char* pTotalData = NULL;

	if (!info_struct.PackData(iTotalSize,pTotalData))
	{

	} else
	{

	}

	char* buff = (char*)malloc(iTotalSize+200);
	PackResponse(buff,
			lpPerSocketContext->CommandState.dwTag,
			lpPerSocketContext->CommandState.nCommand,
			UPDATE_CLD_SUCCESS,
			pTotalData,
			iTotalSize);
	if (pTotalData) 
	{
		free(pTotalData);
	}
 
	AddDataToClient(lpPerSocketContext,buff,iTotalSize);
	free(buff);

	lpPerSocketContext->m_ReceiveBuffer.erase(lpPerSocketContext->m_ReceiveBuffer.begin(),
			lpPerSocketContext->m_ReceiveBuffer.begin()+lpPerSocketContext->CommandState.dwHeaderSize);
	return COMMAND_OK;
}
 
bool UpdateCalendarToDatabaseNew(CALENDAR_INFO* pCalendar,
      LIST_MEN_IN_CALENDAR *pListMen,
      LIST_DEP_IN_CALENDAR *pListDep,
      LIST_GROUP_IN_CALENDAR *pListGroup,
      LIST_RESOURCE_IN_CALENDAR *pListResource)
{
	CADODatabase pAdodb;// = NULL;
	//pAdodb = new CADODatabase();
	//  if (pAdodb == NULL) 
	//  {
	//   return false;
	//  }
	 
	pAdodb.SetConnectionString(g_strDBConnectionString);
	if(!pAdodb.Open())
	{
		//delete pAdodb;//pAdodb=NULL;
		return false;
	}

	CString strQuery;
	CADORecordset rs(&pAdodb);
	strQuery.Format("SELECT * FROM [Calendar_table] WHERE CalendarID=%d", pCalendar->CalendarID);
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	if (rs.GetRecordCount() <= 0) 
	{
		rs.Close();
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	rs.GetFieldValue("Version",pCalendar->Version);
	pCalendar->Version++;
	rs.Edit();
	rs.SetFieldValue("CreatorEmail",pCalendar->CreatorEmail);
	rs.SetFieldValue("CalendarName",pCalendar->CalendarName);
	rs.SetFieldValue("Description",pCalendar->Description);
	rs.SetFieldValue("Location",pCalendar->Location);
	COleDateTime dDate;
	dDate.m_dt = atof(pCalendar->StartTime);
	rs.SetFieldValue("StartTime",dDate);
	dDate.m_dt = atof(pCalendar->EndTime);
	rs.SetFieldValue("EndTime",dDate);
	dDate.m_dt = atof(pCalendar->RescureTime);
	rs.SetFieldValue("RescureTime",dDate);

	rs.SetFieldValue("RescureType",pCalendar->RescureType);
	rs.SetFieldValue("Blocking",pCalendar->Blocking);
	rs.SetFieldValue("NotifyUpdate",pCalendar->NotifyUpdate);
	// dDate.m_dt = atof(pCalendar->NotifyBeforeStartTime);
	// rs.SetFieldValue("NotifyBeforeStartTime",dDate);
	rs.SetFieldValue("Priority",pCalendar->Priority);
	rs.SetFieldValue("Private",pCalendar->Private);
	dDate = COleDateTime::GetCurrentTime();
	rs.SetFieldValue("LastUpdateTime",dDate);
	rs.SetFieldValue("LatsUpdatePerson",pCalendar->LatsUpdatePerson);
	rs.SetFieldValue("Version",pCalendar->Version);
	// rs.SetFieldValue("Notify",pCalendar->Notify);
	rs.SetFieldValue("Status",pCalendar->Status);
	rs.SetFieldValue("RecurrenceDay",pCalendar->RecurrenceDay);
	
	rs.Update();
	rs.Close();
	strQuery.Format("DELETE FROM [MenInCalendar_table] WHERE CalendarID = %d",pCalendar->CalendarID);
	pAdodb.Execute(strQuery);
	strQuery.Format("DELETE FROM [DepInCalendar_table] WHERE CalendarID = %d",pCalendar->CalendarID);
	pAdodb.Execute(strQuery);
	strQuery.Format("DELETE FROM [GroupInCalendar_table] WHERE CalendarID = %d",pCalendar->CalendarID);
	pAdodb.Execute(strQuery);
	strQuery.Format("DELETE FROM [ResourceInCalendar_table] WHERE CalendarID = %d",pCalendar->CalendarID);
	pAdodb.Execute(strQuery);
	strQuery.Format("SELECT * FROM [MenInCalendar_table] WHERE 1=2");
	pAdodb.Execute(strQuery);
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	int i;
	int test1=pListMen->size();
	for (i = 0; i <pListMen->size(); i++ ) 
	{
		rs.AddNew();
		rs.SetFieldValue("CalendarID",pCalendar->CalendarID);
		rs.SetFieldValue("Email",pListMen->at(i).Email);
		rs.SetFieldValue("Role",pListMen->at(i).Role);
		rs.SetFieldValue("Status",pListMen->at(i).Status);
		rs.SetFieldValue("Note",pListMen->at(i).Note);
		rs.SetFieldValue("Notify",pCalendar->Notify);
		dDate.m_dt = atof(pCalendar->NotifyBeforeStartTime);
		rs.SetFieldValue("NotifyBeforeStartTime",dDate);
		rs.Update();
	}
	rs.Close();
	strQuery.Format("SELECT * FROM [GroupInCalendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	int test2=pListGroup->size();
	for (i = 0; i <pListGroup->size(); i++ ) 
	{
		rs.AddNew();
		rs.SetFieldValue("CalendarID",pCalendar->CalendarID);
		rs.SetFieldValue("GroupID",pListGroup->at(i).GroupID);
		rs.SetFieldValue("Role",pListGroup->at(i).Role);
		rs.SetFieldValue("Status",pListGroup->at(i).Status);
		rs.SetFieldValue("Note",pListGroup->at(i).Note);
		rs.SetFieldValue("Notify",pCalendar->Notify);
		dDate.m_dt = atof(pCalendar->NotifyBeforeStartTime);
		rs.SetFieldValue("NotifyBeforeStartTime",dDate);
		rs.Update();
	}
	rs.Close();
	strQuery.Format("SELECT * FROM [DepInCalendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	int test3=pListDep->size();
	for (i = 0; i <pListDep->size(); i++ ) 
	{
		rs.AddNew();
		rs.SetFieldValue("CalendarID",pCalendar->CalendarID);
		rs.SetFieldValue("DepID",pListDep->at(i).DepID);
		rs.SetFieldValue("Role",pListDep->at(i).Role);
		rs.SetFieldValue("Status",pListDep->at(i).Status);
		rs.SetFieldValue("Note",pListDep->at(i).Note);
		rs.SetFieldValue("Notify",pCalendar->Notify);
		dDate.m_dt = atof(pCalendar->NotifyBeforeStartTime);
		rs.SetFieldValue("NotifyBeforeStartTime",dDate);
		rs.Update();
	}
	rs.Close();
	strQuery.Format("SELECT * FROM [ResourceInCalendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	int test4=pListResource->size();
	for (i = 0; i <pListResource->size(); i++ ) 
	{
		rs.AddNew();
		rs.SetFieldValue("CalendarID",pCalendar->CalendarID);
		rs.SetFieldValue("ResourceID",pListResource->at(i).ResourceID);
		rs.SetFieldValue("ResourceUser",pListResource->at(i).strUser);
		rs.SetFieldValue("Approver",pListResource->at(i).strApprover);
		rs.SetFieldValue("Position",pListResource->at(i).iPosition);
		rs.SetFieldValue("Quantity",pListResource->at(i).Quantity);
		rs.SetFieldValue("Status",pListResource->at(i).Status);
		rs.SetFieldValue("Note",pListResource->at(i).Note);
		rs.Update();
	}
	rs.Close();
	pAdodb.Close();
	//delete pAdodb;//pAdodb=NULL;
	return true;
}
