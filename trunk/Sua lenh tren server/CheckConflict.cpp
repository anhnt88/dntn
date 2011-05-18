struct CALENDAR_INFO
{
	long CalendarID;   // ID c?a l?ch
	int Version; //Phiên b?n c?a l?ch, m?i ngu?i update phiên b?n l?i tang
	CString StartTime;         // Th?i gian b?t d?u cu?c h?p
	CString EndTime;  //Th?i gian k?t thúc cu?c h?p
	CString RescureTime;
	CString LastUpdateTime;  // Th?i gian update cu?i cùng
	CString NotifyBeforeStartTime;  // C?nh báo tru?c khi cu?c h?p di?n ra bao lâu
	CString CreatorEmail;    // Ngu?i l?p l?ch
	CString LatsUpdatePerson;  //Ngu?i cu?i cùng update
	CString CalendarName;  // Tên l?ch
	CString Description;     //Mô t? n?i dung l?ch
	CString Location;      // Ð?a di?m di?n ra cu?c h?p
	int RescureType;  //Tính l?p l?i: Hàng tu?n, tháng, nam, ngày nào dó,….
	int Blocking;//Có th? chèn l?ch khác cùng th?i di?m không
	int Priority;       //M?c d? uu tiên
	int Private;  // N?i dung cu?c h?p là cá nhân hay có th? Public
	int Status;         // Tr?ng thái, active? Non active
	int Notify; // Có notify hay không
	int NotifyUpdate; //C?nh báo khi có thay d?i l?ch
	CString CreateTime; //Thoi gian tao lich
	int RecurrenceDay;	//Thu lap lai lich trong tuan
};
 
 
bool FindConflict(bool *bConflict,
      CALENDAR_INFO* pCalendar,
      LIST_MEN_IN_CALENDAR *pListMen,
      LIST_DEP_IN_CALENDAR *pListDep,
      LIST_GROUP_IN_CALENDAR *pListGroup,
      LIST_RESOURCE_IN_CALENDAR *pListResource,
      LIST_CALENDAR_CONFLICT *pListConflictOut,
      bool bUpdate)
{
	*bConflict = false;
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
	UserConflictMap  ListUser;
	int i;
	ListUser.InitHashTable(MAX_CONNECTIONS);
	for (i=0; i <pListMen->size(); i++) 
	{
		MAN_CONFLICT man;
		man.Email = pListMen->at(i).Email;
		man.Status = pListMen->at(i).Status;
		ListUser.SetAt(man.Email,man);
	}
	CString strTemp;
	CString strList = "";
	for (i=0; i <pListGroup->size(); i++) 
	{
		if (strList.IsEmpty()) 
		{
			strTemp.Format("%d",pListGroup->at(i).GroupID);
		} else
		{
			strTemp.Format(",%d",pListGroup->at(i).GroupID);
		}
		strList = strList + strTemp;
	}
	if (!strList.IsEmpty()) 
	{
		strQuery.Format("SELECT email FROM MenInGroup_table WHERE GroupID IN (%s)", strList);
		if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
		{
			pAdodb.Close();
			//delete pAdodb;//pAdodb=NULL;
			return false ;
		}
		while (!rs.IsEOF()) 
		{
			rs.GetFieldValue("Email",strTemp);
			MAN_CONFLICT man;
			man.Email = strTemp;
			man.Status = 0;
			ListUser.SetAt(man.Email,man);
			rs.MoveNext();
		}
		rs.Close();
	}
	rs.Close();
	strList = "";
	for (i=0; i <pListDep->size(); i++) 
	{
		if (strList.IsEmpty()) 
		{
			strTemp.Format("'%s'",pListDep->at(i).DepID);
		} else
		{
			strTemp.Format(",'%s'",pListDep->at(i).DepID);
		}
		strList = strList + strTemp;
	}
	if (!strList.IsEmpty()) 
	{
		strQuery.Format("SELECT email FROM User_Dep_table WHERE DepID IN (%s)", strList);
		if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
		{
			pAdodb.Close();
			//delete pAdodb;//pAdodb=NULL;
			return false ;
		}
		while (!rs.IsEOF()) 
		{
			rs.GetFieldValue("Email",strTemp);
			MAN_CONFLICT man;
			man.Email = strTemp;
			man.Status = 0;
			ListUser.SetAt(man.Email,man);
			rs.MoveNext();
		}
		rs.Close();
	}
	rs.Close();
	long CalendarID;
	CString strStartTime;
	CString strEndTime;
	COleDateTime dDate;
	dDate.m_dt = atof(pCalendar->StartTime);
	strStartTime = dDate.Format("'%m/%d/%y %H:%M:0'");
	dDate.m_dt = atof(pCalendar->EndTime);
	strEndTime = dDate.Format("'%m/%d/%y %H:%M:0'");
	std::vector<int> vResourceQuantity;
	CString strListRSID("");
	for (i = 0; i <pListResource->size(); i++) 
	{
		if(strListRSID.IsEmpty())
		{
			strTemp.Format("%d",pListResource->at(i).ResourceID);
		}
		else strTemp.Format(",%d",pListResource->at(i).ResourceID);
		strListRSID+=strTemp;
		vResourceQuantity.push_back(0);
	}
	if(pListResource->size() > 0)
	{
		strQuery.Format("SELECT ResourceID, Quantity FROM [Resource_table] WHERE ResourceID IN (%s)",strListRSID);
		if(rs.Open(strQuery,CADORecordset::openQuery))
		{
			while (!rs.IsEOF())
			{
				int iRSID,iQuantity;
				rs.GetFieldValue("ResourceID",iRSID);
				rs.GetFieldValue("Quantity",iQuantity);
				rs.MoveNext();

				for(i=0;i<pListResource->size();i++)
					if(pListResource->at(i).ResourceID == iRSID)
					{
						vResourceQuantity[i]=iQuantity-pListResource->at(i).Quantity;
					}
			}
			rs.Close();
		}
	}
	if (bUpdate) 
	{
		strQuery.Format("SELECT * FROM Calendar_table\
			   WHERE\
			   (\
				(\
				 (StartTime >=%s AND StartTime < %s) OR (EndTime > %s AND EndTime <= %s) OR ( StartTime <= %s AND EndTime >= %s )\
				 OR (\
				   (RescureType > 0)AND\
				   (\
					(RescureTime > %s AND RescureTime<= %s) OR ( StartTime <= %s AND RescureTime >= %s)\
				   )\
				  )\
				)\
				AND (CalendarID <> %d)\
			   )",strStartTime, strEndTime, strStartTime, strEndTime,strStartTime, strEndTime,strStartTime,strEndTime,strStartTime,strEndTime,pCalendar->CalendarID);
	} else
	{
		strQuery.Format("SELECT * FROM Calendar_table\
				WHERE\
				(\
				 (\
				  (StartTime >=%s AND StartTime < %s) OR (EndTime > %s AND EndTime <= %s) OR ( StartTime <= %s AND EndTime >= %s )\
				  OR (\
					(RescureType > 0)AND\
					(\
					 (RescureTime > %s AND RescureTime<= %s) OR ( StartTime <= %s AND RescureTime >= %s)\
					)\
				   )\
				 )\
				)",strStartTime, strEndTime, strStartTime, strEndTime,strStartTime, strEndTime,strStartTime,strEndTime,strStartTime,strEndTime);
	}
	rs.Close();
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
		return true;
	} else
	{
		strList = "";
		while (!rs.IsEOF()) 
		{
			rs.GetFieldValue("CalendarID",CalendarID);
			rs.MoveNext();
			if (strList.IsEmpty()) 
			{
				strTemp.Format("%d",CalendarID);
			} else
			{
				strTemp.Format(",%d",CalendarID);
			}
			strList = strList + strTemp;
		}
		rs.MoveFirst();
	}
	LIST_MAN_CONFLICT ListUserInCalendar;
	LIST_RESOURCE_IN_CALENDAR ResourceList;
	while (!rs.IsEOF()) 
	{
		CALENDAR_CONFLICT CalendarConflict;
		rs.GetFieldValue("CalendarID",CalendarConflict.CalendarID);
		rs.GetFieldValue("CalendarName",CalendarConflict.CalendarName);
		COleDateTime startTime,endTime,RescureTime;
		rs.GetFieldValue("EndTime",endTime);
		CalendarConflict.EndTime.Format("%f", endTime.m_dt);
		rs.GetFieldValue("StartTime",startTime); 
		CalendarConflict.StartTime.Format("%f", startTime.m_dt);
		int iRescure;
		rs.GetFieldValue("RescureType",iRescure);
		CalendarConflict.RescureType=iRescure;
		rs.GetFieldValue("RescureTime",RescureTime);
		rs.GetFieldValue("Blocking",CalendarConflict.Blocking);
		int iRecurrenceDay;
		rs.GetFieldValue("RecurrenceDay",iRecurrenceDay);
		rs.GetFieldValue("CreatorEmail",CalendarConflict.EmailCreator);
		rs.GetFieldValue("CreateTime",CalendarConflict.CreateTime);
		rs.MoveNext();
		bool bAdd=true;
		if(iRescure > 0)
		{
			COleDateTime sTime,eTime;
			sTime.m_dt= atof(pCalendar->StartTime);
			eTime.m_dt= atof(pCalendar->EndTime);
			bAdd=false;
			bool bStop=false;
			std::vector<int> vRecurrenceDay;
			switch (iRescure)
			{
			case 1:// lap lai hang ngay
				do 
				{
					if(startTime>=sTime && startTime < eTime)
					{
						bAdd = true;
						bStop = true;
					}
					if(endTime > sTime && endTime <= eTime)
					{
						bAdd = true;
						bStop = true;
					}
					if(startTime <= sTime && endTime >= eTime)
					{
						bAdd = true;
						bStop = true;
					}
					startTime+=1;
					endTime+=1;
				} while (!bStop && endTime< RescureTime && startTime < eTime);
				break;
			case 2:// lap lai hang tuan
				vRecurrenceDay.clear();
				for (j=0; j<7; j++)
				{
					DWORD dwTmp=1;
					dwTmp<<=j;
					if (dwTmp&iRecurrenceDay)
						vRecurrenceDay.push_back(j+1);
				}
				do 
				{
					if(startTime>=sTime && startTime < eTime)
					{
						bAdd = true;
						bStop = true;
					}
					if(endTime > sTime && endTime <= eTime)
					{
						bAdd = true;
						bStop = true;
					}
					if(startTime <= sTime && endTime >= eTime)
					{
						bAdd = true;
						bStop = true;
					}
					
					int nDayOfWeek = startTime.GetDayOfWeek();	
					bool bNotIn=true;
					for(j=0; j<vRecurrenceDay.size();j++)
					{
						if((nDayOfWeek==vRecurrenceDay[j]))
						{
							bNotIn=false;
							if (j==vRecurrenceDay.size()-1)//Phan tu cuoi cung
							{
								int nIncreaseTime=7-vRecurrenceDay[j]+vRecurrenceDay[0];
								startTime+=nIncreaseTime;
								endTime+=nIncreaseTime;
							}
							else
							{
								int nIncreaseTime=vRecurrenceDay[j+1]-vRecurrenceDay[j];
								startTime+=nIncreaseTime;
								endTime+=nIncreaseTime;
							}
						}
					}
					if(bNotIn)
					{
						//Loi: lap theo tuan ma thu cua lich khong co trong RecurrenceDay
						break;
					}
				} while (!bStop && endTime< RescureTime && startTime < eTime);
				break;		
			case 3:// lap lai hang thang
				int nMonth=startTime.GetMonth();
				int nYear=startTime.GetYear();
				int nDay=startTime.GetDay();
				int iHour=startTime.GetHour();
				int iMinute=startTime.GetMinute();
				COleDateTime runSTime,runETime;
				runSTime=startTime;
				runETime=endTime;
				do 
				{
					if(runSTime>=sTime && runSTime < eTime)
					{
						bAdd = true;
						bStop = true;
					}
					if(runETime > sTime && runETime <= eTime)
					{
						bAdd = true;
						bStop = true;
					}
					if(runSTime<=sTime && runETime >= eTime)
					{
						bAdd = true;
						bStop = true;
					}
					nMonth+=1;
					if(nMonth>12)
					{
						nYear+=1;
						nMonth-=12;
					}
					int nNextMonth=nMonth+1;
					COleDateTime tmpTime;
					if(nNextMonth>12)
					{
						tmpTime.SetDateTime(nYear+1,nNextMonth-12,1,0,0,0);
					}
					else
						tmpTime.SetDateTime(nYear,nNextMonth,1,0,0,0);
					tmpTime-=1; // Get Last Day Of current Month;
					if(nDay > tmpTime.GetDay())
					{
						int iDay=tmpTime.GetDay();
						runSTime.SetDateTime(nYear,nMonth,iDay,iHour,iMinute,0);
					}
					else runSTime.SetDateTime(nYear,nMonth,nDay,iHour,iMinute,0);
					int nSpaceDay=runSTime-startTime;
					runETime=endTime;
					runETime+=nSpaceDay;
				} while (!bStop && runETime< RescureTime && runSTime < eTime);
				break;
			}
		}
		if(bAdd)
		{
			ListUserInCalendar.clear();
			ResourceList.clear();
			GetListUserResource(&pAdodb,CalendarConflict.CalendarID,&ListUserInCalendar,&ResourceList);
			MAN_CONFLICT UserConflict;

			bool bHasConflict = false;
			bool bRefuse=false;// kiem tra xem lich bi tu choi chua
//nham			
//			CalendarConflict.CalendarID = CalendarID;
			for (i = 0; i <ListUserInCalendar.size(); i++) 
			{
			//    CString strEmail=ListUserInCalendar.at(i).Email;
				if ( 0!=ListUser.Lookup(ListUserInCalendar.at(i).Email,UserConflict) )
				{
					CalendarConflict.ListMen.push_back(UserConflict);
					*bConflict = true;
					bHasConflict = true;
				}
			}
	   
			int test = pListResource->size();
			if(pListResource->size() > 0)
			{
				CADORecordset rs2(&pAdodb);
				//tuantab 25/8 conflict lich voi Resource, neu lich bi tu choi Respond = -1 thi ko bao conflict
				// conflict chi xet voi nhung tai nguyen thiet lap la public , iPublicType=0, cac tai nguyen khac dat vo tu
				strQuery.Format(" SELECT [Tbl_Resource_Xetduyet].Respond FROM [Tbl_Resource_Xetduyet]\
					   WHERE ([Tbl_Resource_Xetduyet].CalendarID =%i) AND\
						 ([Tbl_Resource_Xetduyet].ResourceID IN (%s)) AND\
						 ([Tbl_Resource_Xetduyet].ResourceID IN (SELECT [Resource_table].ResourceID FROM [Resource_table] WHERE PublicType=0)\
					   )",CalendarConflict.CalendarID,strListRSID);
				if(rs2.Open(strQuery,CADORecordset::openQuery))
				{
					int iRespond;
					while (!rs2.IsEOF())
					{
						//duyet qua toan bo ket qua, neu lich bi tu choi thi set bRefuse= true
						rs2.GetFieldValue("Respond",iRespond);
						if (iRespond==-1)
						{
							bRefuse=true;
							break;
						}
						rs2.MoveNext();
					}
					rs2.Close();
				}
				rs2.Close();
				//////////////////////////////////////////////////////////////////////////
				strQuery.Format(" SELECT [ResourceInCalendar_table].ResourceID, [ResourceInCalendar_table].Quantity, [ResourceInCalendar_table].Status FROM [ResourceInCalendar_table]\
					 WHERE ([ResourceInCalendar_table].CalendarID =%i) AND\
					   ([ResourceInCalendar_table].ResourceID IN (%s)) AND\
					   ([ResourceInCalendar_table].ResourceID IN (SELECT [Resource_table].ResourceID FROM [Resource_table] WHERE PublicType=0)\
					   )",CalendarConflict.CalendarID,strListRSID);
				if(rs2.Open(strQuery,CADORecordset::openQuery))
				{
					while(!rs2.IsEOF())
					{
						int iID,iQuantity, iStatus;
						rs2.GetFieldValue("ResourceID",iID);
						rs2.GetFieldValue("Quantity",iQuantity);
						rs2.GetFieldValue("Status",iStatus);
						for(i=0;i<pListResource->size();i++)
						if(pListResource->at(i).ResourceID == iID)
						{
							vResourceQuantity[i]-=iQuantity;
							if(vResourceQuantity[i] < 0)
							{
								RESOURCE_CONFLICT Resource;
								Resource.ResourceID =iID;
								Resource.Status  =iStatus;
								CalendarConflict.ListResource.push_back(Resource);
								*bConflict = true;
								bHasConflict = true;
							}
						}
						rs2.MoveNext();
					}
					rs2.Close();
				}
				rs2.Close();
			}
	   
			if (bHasConflict&&!bRefuse) 
			{
				pListConflictOut->push_back(CalendarConflict);
				*bConflict=true;
			}
			else
				*bConflict=false;
		}
		//   else
		//   {
		//    pListConflictOut->push_back(CalendarConflict);
		//   }
	}
	rs.Close();
	pAdodb.Close();
	//delete pAdodb;//pAdodb=NULL;
	return true;
}
 
bool AddCalendarToDatabase(CALENDAR_INFO* pCalendar,
      LIST_MEN_IN_CALENDAR *pListMen,
      LIST_DEP_IN_CALENDAR *pListDep,
      LIST_GROUP_IN_CALENDAR *pListGroup,
      LIST_RESOURCE_IN_CALENDAR *pListResource,
      LIST_STRING *pListTags)
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
	strQuery.Format("SELECT * FROM [Calendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	rs.AddNew();
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
	rs.SetFieldValue("Version",1); 
	// rs.SetFieldValue("Notify",pCalendar->Notify);
	rs.SetFieldValue("Status",pCalendar->Status);
	rs.SetFieldValue("RecurrenceDay",pCalendar->RecurrenceDay);
	rs.Update();
	rs.GetFieldValue("CalendarID", pCalendar->CalendarID);
	rs.Close();
	strQuery.Format("SELECT * FROM [MenInCalendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	int i;
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

	int test1=pListResource->size();
	strQuery.Format("SELECT * FROM [ResourceInCalendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
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
	//////////////////////////////////////////////////////////////////////////
	///tuantab 30/7/2010 - them lich vao bang csdl moi Tbl_Resource_Xetduyet
	strQuery.Format("SELECT * FROM [Tbl_Resource_Xetduyet] WHERE 1=2");

	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
 
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
		rs.SetFieldValue("Respond",0);  
		rs.Update();
	}
	rs.Close();
	//////////////////////////////////////////////////////////////////////////

	strQuery.Format("SELECT * FROM [TagsInCalendar_table] WHERE 1=2");
	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return false ;
	}
	for (i = 0; i <pListTags->size(); i++ ) 
	{
		rs.AddNew();
		rs.SetFieldValue("CalendarID",pCalendar->CalendarID);
		rs.SetFieldValue("Tag",pListTags->at(i));
		rs.Update();
	}
	rs.Close();

	pAdodb.Close();
	//delete pAdodb;//pAdodb=NULL;
	return true;
}

bool PackCalendarNew(CInfoStruct *pInfo_struct,
      CALENDAR_INFO Calendar,
      LIST_MEN_IN_CALENDAR *pListMen,
      LIST_DEP_IN_CALENDAR *pListDep,
      LIST_GROUP_IN_CALENDAR *pListGroup,
      LIST_RESOURCE_IN_CALENDAR *pListResource,
      LIST_ATTACH_IN_CALENDAR *pListAttach,
      LIST_STRING *pListTags)
{
	pInfo_struct->AddData(Calendar.CalendarID);
	pInfo_struct->AddData(Calendar.Version);
	pInfo_struct->AddData(Calendar.StartTime);
	pInfo_struct->AddData(Calendar.EndTime);
	pInfo_struct->AddData(Calendar.RescureTime);
	pInfo_struct->AddData(Calendar.LastUpdateTime);
	pInfo_struct->AddData(Calendar.NotifyBeforeStartTime);
	pInfo_struct->AddData(Calendar.CreatorEmail);
	pInfo_struct->AddData(Calendar.LatsUpdatePerson);
	pInfo_struct->AddData(Calendar.CalendarName);
	pInfo_struct->AddData(Calendar.Description);
	pInfo_struct->AddData(Calendar.Location);
	pInfo_struct->AddData(Calendar.RescureType);
	pInfo_struct->AddData(Calendar.Blocking);
	pInfo_struct->AddData(Calendar.Priority);
	pInfo_struct->AddData(Calendar.Private);
	pInfo_struct->AddData(Calendar.Status);
	pInfo_struct->AddData(Calendar.Notify);
	pInfo_struct->AddData(Calendar.NotifyUpdate);
	
	pInfo_struct->AddData(Calendar.CreateTime);
	pInfo_struct->AddData(Calendar.RecurrenceDay);
	
	pInfo_struct->AddData(pListMen->size());
	pInfo_struct->AddData(pListGroup->size());
	pInfo_struct->AddData(pListDep->size());
	pInfo_struct->AddData(pListResource->size());
	pInfo_struct->AddData(pListAttach->size());
	pInfo_struct->AddData(pListTags->size());
	int i;
	for (i = 0; i < pListMen->size(); i++) 
	{
		pInfo_struct->AddData(pListMen->at(i).Email);
		pInfo_struct->AddData(pListMen->at(i).Role);
		pInfo_struct->AddData(pListMen->at(i).Status);
		pInfo_struct->AddData(pListMen->at(i).Note);
	}
	for (i = 0; i < pListGroup->size(); i++) 
	{
		pInfo_struct->AddData(pListGroup->at(i).GroupID);
		pInfo_struct->AddData(pListGroup->at(i).Role);
		pInfo_struct->AddData(pListGroup->at(i).Status);
		pInfo_struct->AddData(pListGroup->at(i).Note);
	}
	for (i = 0; i < pListDep->size(); i++) 
	{
		pInfo_struct->AddData(pListDep->at(i).DepID);
		pInfo_struct->AddData(pListDep->at(i).Role);
		pInfo_struct->AddData(pListDep->at(i).Status);
		pInfo_struct->AddData(pListDep->at(i).Note);
	}
	for (i = 0; i < pListResource->size(); i++) 
	{
		pInfo_struct->AddData(pListResource->at(i).ResourceID);
		pInfo_struct->AddData(pListResource->at(i).strUser);
		pInfo_struct->AddData(pListResource->at(i).Quantity);
		pInfo_struct->AddData(pListResource->at(i).strApprover);
		pInfo_struct->AddData(pListResource->at(i).iPosition);
		pInfo_struct->AddData(pListResource->at(i).Status);
		pInfo_struct->AddData(pListResource->at(i).Note);
	}

	for (i = 0; i < pListAttach->size(); i++) 
	{
		pInfo_struct->AddData(pListAttach->at(i).AttachID);
		pInfo_struct->AddData(pListAttach->at(i).AttachType);
		pInfo_struct->AddData(pListAttach->at(i).AttachName);
		pInfo_struct->AddData(pListAttach->at(i).Status);
	}
	for (i = 0; i < pListTags->size(); i++) 
	{
		pInfo_struct->AddData(pListTags->at(i));
	}
	return true;
}

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
		rs.GetFieldValue("CreateTime",date);
		Calendar.CreateTime.Format("%f", date.m_dt);
		rs.GetFieldValue("RecurrenceDay",Calendar.RecurrenceDay);

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
 
 