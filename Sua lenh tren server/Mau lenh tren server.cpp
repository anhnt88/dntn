int ResponseSEARCH_CLD(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
 enum SEARCH_CLD_ERROR_CODE
 {
  SEARCH_CLD_SUCCESS = 0,
  SEARCH_CLD_FAIL  = 1
 };
 int iIndex = 0;
 CString strTemp;
 DWORD dwResult = SEARCH_CLD_SUCCESS;
 COleDateTime FromDate;
 COleDateTime ToDate;
 if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,strTemp))
  return COMMAND_QUIT;
 FromDate.m_dt = atof(strTemp);
 if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,strTemp))
  return COMMAND_QUIT;
 ToDate.m_dt = atof(strTemp);
 if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,strTemp))
  return COMMAND_QUIT;

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
 CString strStartTime;
 CString strEndTime;
 COleDateTime dDate;
 strStartTime = FromDate.Format("'%m/%d/%y %H:%M:0'");
 strEndTime = ToDate.Format("'%m/%d/%y %H:%M:59'");
 strQuery.Format("SELECT CalendarID,Version FROM [Calendar_table] WHERE (\
  (\
   (CreatorEmail IN ('%s'))\
  ) \
  OR \
  (\
     (\
    (Private = 0) \
     )\
  ) \
  OR \
  (\
     (\
    CalendarID IN (SELECT CalendarID FROM [MenInCalendar_table] WHERE Email IN ('%s')) \
     )\
  ) \
  OR \
  (\
   (\
    CalendarID IN \
     (\
      SELECT CalendarID FROM [GroupInCalendar_table] WHERE \
       GroupID IN (SELECT GroupID FROM [MenInGroup_table] WHERE Email IN ('%s'))\
     )\
   )\
  ) \
  OR \
  (\
   (\
    CalendarID IN \
     (\
      SELECT CalendarID FROM [DepInCalendar_table] INNER JOIN user_dep_table ON DepInCalendar_table.DepID = user_dep_table.DepID COLLATE Vietnamese_CI_AS WHERE \
       user_dep_table.DepID IN (SELECT DepID FROM [User_Dep_table] WHERE email IN ('%s'))\
     )\
   ) \
  ) ) AND (Status <> %d) AND ((StartTime BETWEEN  %s AND %s) OR (EndTime BETWEEN  %s AND %s) ) AND ((CalendarName like '#%s#') OR (Description like '#%s#') OR (Location like '#%s#')) ", 
  lpPerSocketContext->m_strUser, lpPerSocketContext->m_strUser,lpPerSocketContext->m_strUser,lpPerSocketContext->m_strUser,GENARAL_DISABLE ,strStartTime,strEndTime,strStartTime,strEndTime,strTemp,strTemp,strTemp);
 strQuery.Replace('#','%');
 if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
 {
  pAdodb.Close();
  //delete pAdodb;//pAdodb=NULL;
  return COMMAND_QUIT ;
 }
 CInfoStruct info_struct;
 long CalendarID;
 int Version;
 info_struct.AddData(rs.GetRecordCount());
 
 while (!rs.IsEOF()) 
 {
  rs.GetFieldValue("CalendarID",CalendarID);
  rs.GetFieldValue("Version",Version);
  rs.MoveNext();
  info_struct.AddData(CalendarID);
  info_struct.AddData(Version);
 }

 rs.Close();
 pAdodb.Close();
 //delete pAdodb;//pAdodb=NULL;
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
