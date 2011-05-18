/////////////////////////////////////////////////////////////////
//Dap ung cua server khi client gui lenh check tai nguyen trong//
/////////////////////////////////////////////////////////////////

//GET_AVAILABLE_RESOURCE=169
int ResponseGET_AVAILABLE_RESOURCE(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
 enum GET_AVAILABLE_RESOURCE_ERROR_CODE
 {
  GET_AVAILABLE_RESOURCE_SUCCESS = 0,
  GET_AVAILABLE_RESOURCE_FAIL  = 1
 };
 int iIndex = 0;
 CString strTemp;
 DWORD dwResult = GET_AVAILABLE_RESOURCE_SUCCESS;
 COleDateTime FromDate;
 COleDateTime ToDate;
 if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,strTemp))
  return COMMAND_QUIT;
 FromDate.m_dt = atof(strTemp);
 if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,strTemp))
  return COMMAND_QUIT;
 ToDate.m_dt = atof(strTemp);
 
 CADODatabase pAdodb;
 
 pAdodb.SetConnectionString(g_strDBConnectionString);
 if(!pAdodb.Open())
 {
  return COMMAND_QUIT;
 }
 CString strQuery;
 CADORecordset rs(&pAdodb);
 CString strStartTime;
 CString strEndTime;

 strStartTime = FromDate.Format("'%m/%d/%y %H:%M:0'");
 strEndTime = ToDate.Format("'%m/%d/%y %H:%M:59'");
 
 strQuery.Format("SELECT dbo.ResourceInCalendar_table.ResourceID, SUM(dbo.ResourceInCalendar_table.Quantity) AS da_dung, MAX(dbo.Resource_table.Quantity )AS tong_so\
				FROM dbo.Calendar_table INNER JOIN dbo.ResourceInCalendar_table ON dbo.Calendar_table.CalendarID=dbo.ResourceInCalendar_table.CalendarID\
				INNER JOIN dbo.Resource_table ON dbo.ResourceInCalendar_table.ResourceID=dbo.Resource_table.ResourceID\
				WHERE (StartTime BETWEEN  %s AND %s) OR (EndTime BETWEEN  %s AND %s) \
				GROUP BY dbo.ResourceInCalendar_table.ResourceID", strStartTime, strEndTime, strStartTime, strEndTime);
 
 if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
 {
  pAdodb.Close();
  return COMMAND_QUIT ;
 }

 int ResourceID;
 int nQuantity;
 int nUsed;
 std::vector<int> vUnavailableRes;
 vUnavailableRes.clear();
 
 while (!rs.IsEOF()) 
 {
  rs.GetFieldValue("ResourceID",ResourceID);
  rs.GetFieldValue("tong_so",nQuantity);
  rs.GetFieldValue("da_dung",nUsed);
  rs.MoveNext();

  if(nUsed>=nQuantity)
	vUnavailableRes.push_back(ResourceID);
 }

 rs.Close();
 pAdodb.Close();
 
 CInfoStruct info_struct;
 info_struct.AddData(vUnavailableRes.size());
 for(int i=0; i<vUnavailableRes.size();i++)
 {
	info_struct.AddData(vUnavailableRes[i]);
 }
 vUnavailableRes.clear();
 
 char *pData;
 int iSize;
 info_struct.PackData(iSize,pData);
 char* buff = (char*)malloc(iSize+100);
 PackResponse(buff,
    lpPerSocketContext->CommandState.dwTag,
    lpPerSocketContext->CommandState.nCommand,
    SEARCH_CLD_SUCCESS,
    pData,
    iSize);
 free(pData);
 AddDataToClient(lpPerSocketContext,buff,iSize);
 free(buff);
 lpPerSocketContext->m_ReceiveBuffer.erase(lpPerSocketContext->m_ReceiveBuffer.begin(),
            lpPerSocketContext->m_ReceiveBuffer.begin()+lpPerSocketContext->CommandState.dwHeaderSize);
 return COMMAND_OK;
}

////////////////////////////////////////////
//Tao trang HTML thong bao conflict lich
//
CString BuildConflictReport(CCalendar newCald, CCalendar conflictCald)
{
	strContent=CGVUtils::GetFileContent("ConflictReport.htm");
	int nPos=strContent.Find("#body_temp#");
	if(nPos==-1)
		return;
	CString strTemplate=strContent.Mid(nPos+11);
	strContent=strContent.Left(nPos);
	strContent+=BuildHTML(strTemplate, newCald);
	strContent+=BuildHTML(strTemplate, conflictCald);
	strContent+="</tr></table></body></html>";
	return strContent;
}

CString BuildHTML(CString strTemplate, CCalendar cald)
{
	CString strContent=strTemplate;
	strContent.Replace("#title#",CGVUtils::ConvertTCVNToUTF8(cald.m_strTitle));
	CString strTime,strCreator, strStartTime, strStopTime, strDuration, strDate;
	strCreator=GetUserName(cald.m_strOwner);
	
	strStartTime=cald.m_startTime.Format("%Hh%M");
	strStopTime=cald.m_stopTime.Format("%Hh%M");
	strDate=cald.m_stopTime.Format("%d/%d/%Y");
	int iH=cald.m_stopTime.GetHour()-cald.m_startTime.GetHour();
	int iM=cald.m_stopTime.GetMinute()-cald.m_startTime.GetMinute();
	if (iH>0)
		if(iM>0)
			strDuration.Format("%d giê %d phót", iH, iM);
		else
			strDuration.Format("%d giê", iH);
	else
		strDuration.Format("%d phót", iM);
		
	strTime.Format("<b>%s - %s</b> ngµy %s : <b>%s</b>", strStartTime, strStopTime, strDate, strDuration);
	strContent.Replace("#creator#",CGVUtils::ConvertTCVNToUTF8(strCreator));
	strContent.Replace("#time#",CGVUtils::ConvertTCVNToUTF8(strTime));
	
	CString strLocation="";
	if (cald.m_strLocation!="")
		strLocation+=cald.m_strLocation;
	
	for (int i=0; i<cald.m_vresources.size(); i++)
		strLocation+=cald.m_vresources[i].strResourceName;
	
	strContent.Replace("#location#",CGVUtils::ConvertTCVNToUTF8(strLocation));
	strContent.Replace("#description#",CGVUtils::ConvertTCVNToUTF8(cald.m_strDescription));
	
	CString strParticipant;
	
	for(i=0;i<cald.m_vparticipants.size();i++)
	{
		CString strResond;
		switch(cald.m_vparticipants[i].iStatus)
		{
		case 1:
			strResond="§ång ý";
			break;
		case 2:
			strResond="Tõ chèi";
			break;
		default:
			strResond="Ch­a ph¶n håi";
			break;
		}
		strParticipant+="<table><tr class='noborder'><td class='part'>"+GetUserName(cald.m_vparticipants[i].strName)+"</td><td class='noborder'>"+strResond+"</td></tr></table>";
	}
	strContent.Replace("#participants#",CGVUtils::ConvertTCVNToUTF8(strParticipant));
	return strContent;
}