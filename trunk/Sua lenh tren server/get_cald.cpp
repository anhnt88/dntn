int ResponseADD_CLD_NEW(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
	enum ADD_CLD_NEW_ERROR_CODE
	{
		ADD_CLD_SUCCESS = 0,
		ADD_CLD_FAIL = 1
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
//Gui nhan du lieu thua, 		
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Calendar.CreateTime))
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
			return COMMAND_QUIT;
		}
  
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Role))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,man.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
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
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.Role))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Group.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
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
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.Role))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Dep.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
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
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.strUser))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.Quantity))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.strApprover))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.iPosition))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.Status))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			return COMMAND_QUIT;
		}
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,Resource.Note))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
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
			return COMMAND_QUIT;
		}
		pListTag->push_back(tag);
	}
	// tuantab 25/8 conflict lich
	LIST_CALENDAR_CONFLICT *pListConflict = new (LIST_CALENDAR_CONFLICT);
	bool bConflict = false;
 
	if (IgnoreConflict == 0) 
	{
		if (!FindConflict(&bConflict,&Calendar,pListMen,pListDep,pListGroup,pListResource,pListConflict,0))
		{
			delete pListMen;pListMen=NULL;
			delete pListResource;pListResource=NULL;
			delete pListDep;pListDep=NULL;
			delete pListGroup;pListGroup=NULL;
			delete pListTag;pListTag=NULL;
			delete pListConflict;pListConflict=NULL;
			return COMMAND_QUIT;
		}
	} 
	if (!bConflict) 
	{
		AddCalendarToDatabase(&Calendar,pListMen,pListDep,pListGroup,pListResource,pListTag);
		NotifyCalendarToMember(&Calendar,pListMen,pListDep,pListGroup,pListResource,CALENDAR_UPDATE);
		SendInviteMail(Calendar,pListMen);
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
		CALENDAR_CONFLICT obcon= pListConflict->at(i); 
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
	delete pListConflict;pListConflict=NULL;
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
	ADD_CLD_SUCCESS,
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
 
 
void GetCalendar(int iCalendarID, CALENDAR_INFO &calend)
{
	CADODatabase db;
	db.SetConnectionString(g_strDBConnectionString);
	if(!db.Open())
	{

	}
	CADORecordset rs(&db);
	CString strQuery;
	strQuery.Format("SELECT * FROM Calendar_table WHERE CalendarID=%i",iCalendarID);
	if(!rs.Open(strQuery,CADORecordset::openQuery))
	{
	}
	if(!rs.IsEOF() && rs.GetRecordCount()>0)
	{
		rs.GetFieldValue("Version",calend.Version);
		rs.GetFieldValue("CalendarName",calend.CalendarName);
		rs.GetFieldValue("CreatorEmail",calend.CreatorEmail);
		rs.GetFieldValue("Location",calend.Location);
		rs.GetFieldValue("StartTime",calend.StartTime);
		rs.GetFieldValue("EndTime",calend.EndTime);
		rs.GetFieldValue("RescureType",calend.RescureType);
		rs.GetFieldValue("RescureTime",calend.RescureTime);
		rs.GetFieldValue("Description",calend.Description);
		rs.GetFieldValue("Private",calend.Private);
		rs.GetFieldValue("Priority",calend.Priority);
		rs.GetFieldValue("Blocking",calend.Blocking);
		rs.GetFieldValue("NotifyUpdate",calend.NotifyUpdate);
		rs.GetFieldValue("LastUpdateTime",calend.LastUpdateTime);
		rs.GetFieldValue("LatsUpdatePerson",calend.LatsUpdatePerson);
		rs.GetFieldValue("Status",calend.Status);
	}
	rs.Close();
	db.Close();
};
 
int ResponseGET_CLD_NEW(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
	enum GET_CLD_NEW_ERROR_CODE
	{
		GET_CLD_SUCCESS = 0,
		GET_CLD_FAIL = 1
	};
	CString strUser(lpPerSocketContext->m_strUser);
	int iIndex = 0;
	int iSoCalendar;
	long CalendarID;
	CString strListCalendar;
	CString strTemp;
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,iSoCalendar))
		return COMMAND_QUIT;
	for (int i =0; i < iSoCalendar; i++) 
	{
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,CalendarID))
		return COMMAND_QUIT;
		strTemp.Format("%d",CalendarID);
		if (strListCalendar.IsEmpty()) 
		{
			strListCalendar = strTemp;
		} 
		else
		{
			strListCalendar = strListCalendar + "," + strTemp;
		}
	}
	CADODatabase pAdodb;// = NULL;
	//pAdodb = new CADODatabase();
	//  if (pAdodb == NULL) 
	//  {
	//   return COMMAND_QUIT;
	//  }
 
	pAdodb.SetConnectionString(g_strDBConnectionString);
	if(!pAdodb.Open())
	{
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT;
	}

	CString strQuery;
	CADORecordset rs(&pAdodb);
	strQuery.Format("SELECT * FROM [Calendar_table] WHERE CalendarID IN (%s)", strListCalendar);
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
	CInfoStruct info_struct;
	info_struct.AddData(rs.GetRecordCount());
	CALENDAR_INFO Calendar;
	Calendar.CalendarID = 0;   // ID c?a l?ch
	Calendar.Version = 0; //Phiên b?n c?a l?ch, m?i ngu?i update phiên b?n l?i tang
	Calendar.StartTime = "";         // Th?i gian b?t d?u cu?c h?p
	Calendar.EndTime = "";  //Th?i gian k?t thúc cu?c h?p
	Calendar.RescureTime = "";
	Calendar.LastUpdateTime = "";  // Th?i gian update cu?i cùng
	Calendar.NotifyBeforeStartTime = "";  // C?nh báo tru?c khi cu?c h?p di?n ra bao lâu
	Calendar.CreatorEmail= "";    // Ngu?i l?p l?ch
	Calendar.LatsUpdatePerson = "";  //Ngu?i cu?i cùng update
	Calendar.CalendarName = "";  // Tên l?ch
	Calendar.Description = "";     //Mô t? n?i dung l?ch
	Calendar.Location = "";      // Ð?a di?m di?n ra cu?c h?p
	Calendar.RescureType = 0;  //Tính l?p l?i: Hàng tu?n, tháng, nam, ngày nào dó,….
	Calendar.Blocking = 0;//Có th? chèn l?ch khác cùng th?i di?m không
	Calendar.Priority = 0;       //M?c d? uu tiên
	Calendar.Private = 0;  // N?i dung cu?c h?p là cá nhân hay có th? Public
	Calendar.Status = 0;         // Tr?ng thái, active? Non active
	Calendar.Notify = 0; // Có notify hay không
	Calendar.NotifyUpdate = 0; //C?nh báo khi có thay d?i l?ch
	COleDateTime date;
	Calendar.NotifyBeforeStartTime.Format("%f",date.m_dt);
	
	Calendar.CreateTime = ""; //Thoi gian tao lich
	int RecurrenceDay = 0;	//Thu lap lai lich trong tuan
 
	LIST_MEN_IN_CALENDAR *pListMen = new (LIST_MEN_IN_CALENDAR);
	if (pListMen == NULL) 
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
	LIST_DEP_IN_CALENDAR *pListDep= new (LIST_DEP_IN_CALENDAR);
	if (pListDep == NULL) 
	{
		delete pListMen;pListMen=NULL;
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
	LIST_GROUP_IN_CALENDAR *pListGroup= new (LIST_GROUP_IN_CALENDAR);
	if (pListGroup == NULL) 
	{
		delete pListMen;pListMen=NULL;
		delete pListDep;pListDep=NULL;
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
	LIST_RESOURCE_IN_CALENDAR *pListResource = new (LIST_RESOURCE_IN_CALENDAR);
	if (pListResource == NULL) 
	{
		delete pListMen;pListMen=NULL;
		delete pListDep;pListDep=NULL;
		delete pListGroup;pListGroup=NULL;
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
	LIST_ATTACH_IN_CALENDAR *pListAttach = new (LIST_ATTACH_IN_CALENDAR);
	if (pListAttach == NULL) 
	{
		delete pListResource;pListResource=NULL;
		delete pListMen;pListMen=NULL;
		delete pListDep;pListDep=NULL;
		delete pListGroup;pListGroup=NULL;
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
	LIST_STRING *pListTags = new (LIST_STRING);
	if (pListTags == NULL) 
	{
		delete pListAttach;pListAttach=NULL;
		delete pListResource;pListResource=NULL;
		delete pListMen;pListMen=NULL;
		delete pListDep;pListDep=NULL;
		delete pListGroup;pListGroup=NULL;
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return COMMAND_QUIT ;
	}
 
	while (!rs.IsEOF()) 
	{
		pListMen->clear();
		pListResource->clear();
		pListAttach->clear();
		pListDep->clear();
		pListGroup->clear();
		rs.GetFieldValue("CalendarID",Calendar.CalendarID);
		rs.GetFieldValue("Version",Calendar.Version);
		rs.GetFieldValue("StartTime",date);
		Calendar.StartTime.Format("%f",date.m_dt);
		rs.GetFieldValue("EndTime",date);
		Calendar.EndTime.Format("%f",date.m_dt);
		rs.GetFieldValue("RescureTime",date);
		Calendar.RescureTime.Format("%f",date.m_dt);
		rs.GetFieldValue("CreatorEmail",Calendar.CreatorEmail);
		rs.GetFieldValue("Private",Calendar.Private);
		rs.GetFieldValue("RecurrenceDay",date);
		Calendar.CreateTime.Format("%f", date.m_dt);
		rs.GetFieldValue("CreateTime",Calendar.RecurrenceDay);

		bool bCanSee = CanSeeCalendar(&pAdodb,Calendar.CalendarID,lpPerSocketContext->m_strUser, pListMen,pListDep,pListGroup,Calendar.NotifyBeforeStartTime, Calendar.Notify);

		if ((Calendar.Private && bCanSee) || (!Calendar.Private ))
		{
			rs.GetFieldValue("LastUpdateTime",date);
			Calendar.LastUpdateTime.Format("%f",date.m_dt);
			rs.GetFieldValue("LatsUpdatePerson",Calendar.LatsUpdatePerson);
			rs.GetFieldValue("CalendarName",Calendar.CalendarName);
			rs.GetFieldValue("Description",Calendar.Description);
			rs.GetFieldValue("Location",Calendar.Location);
			rs.GetFieldValue("RescureType",Calendar.RescureType);
			rs.GetFieldValue("Blocking",Calendar.Blocking);
			rs.GetFieldValue("Priority",Calendar.Priority);
			rs.GetFieldValue("Status",Calendar.Status);
			rs.GetFieldValue("NotifyUpdate",Calendar.NotifyUpdate);
			
			GetResourceCalendar(&pAdodb,Calendar.CalendarID, pListResource);
			GetAttachCalendar(&pAdodb,Calendar.CalendarID, pListAttach);
			GetTagsCalendar(&pAdodb,Calendar.CalendarID, pListTags);
		}
		rs.MoveNext();
		PackCalendarNew(&info_struct,Calendar, pListMen,pListDep,pListGroup,pListResource,pListAttach, pListTags);
	}
	rs.Close();
	pAdodb.Close();
	//delete pAdodb;//pAdodb=NULL;
	delete pListAttach;pListAttach=NULL;
	delete pListResource;pListResource=NULL;
	delete pListMen;pListMen=NULL;
	delete pListDep;pListDep=NULL;
	delete pListGroup;pListGroup=NULL;
	delete pListTags;pListTags=NULL;
	char *pData;
	int iSize;
	info_struct.PackData(iSize,pData);
	char* buff = (char*)malloc(iSize+100);
	PackResponse(buff,
		lpPerSocketContext->CommandState.dwTag,
		lpPerSocketContext->CommandState.nCommand,
		GET_CLD_SUCCESS,
		pData,
		iSize);
	free(pData);
	AddDataToClient(lpPerSocketContext,buff,iSize);
	free(buff);
	lpPerSocketContext->m_ReceiveBuffer.erase(lpPerSocketContext->m_ReceiveBuffer.begin(),
			lpPerSocketContext->m_ReceiveBuffer.begin()+lpPerSocketContext->CommandState.dwHeaderSize);
	return COMMAND_OK;
}
 