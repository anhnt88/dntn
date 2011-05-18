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
