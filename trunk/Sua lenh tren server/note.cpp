//Bo lenh DEL_TASKNOTE
//UPD_TASKNOTE	176
//GET_TASKNOTE	175


int ResponseGET_TASKNOTE_NEW(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
	enum GET_TASK_NOTE_ERROR_CODE
	{
		GET_TASK_NOTE_SUCCESS = 0,
		GET_TASK_NOTE_FAIL = 1
	};

	int iIndex = 0;
	int iTaskID = 0;

	int iNumTask = 0;
	int i= 0;
	int iTmp=0;

	DWORD dwResult = GET_TASK_NOTE_SUCCESS;

	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,iNumTask))
		return ResponseQUIT(lpPerSocketContext);
	std::vector<int> vTaskID;
	vTaskID.clear();
	for(i=0; i<iNumTask;i++)
	{
		if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,iTmp))
			return ResponseQUIT(lpPerSocketContext); 
		vTaskID.push_back(iTmp);
	}

	//////////////////////////////////////////////////////////////////////////

	char *pHead = NULL; 
	int iHeadSize = 0;

	CInfoStruct head_struct;
	CADODatabase pAdodb;// = NULL;

	////////////////pAdodb = new CADODatabase();
	// if (pAdodb == NULL) 
	// {
	// return ResponseQUIT(lpPerSocketContext);
	// }

	pAdodb.SetConnectionString(g_strDBConnectionString);
	if(!pAdodb.Open())
	{
		//delete pAdodb;//pAdodb=NULL;
		return ResponseQUIT(lpPerSocketContext);
	}

	CString strQuery;
	CADORecordset rs(&pAdodb);

	//check to see if user can see the task?
	strQuery.Format("SELECT * FROM [TaskNote_table] WHERE (TaskID = %d) AND (Email = '%s')",iTaskID,lpPerSocketContext->m_strUser);

	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		rs.Close();
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return ResponseQUIT(lpPerSocketContext) ;
	}

	if (rs.GetRecordCount() <= 0)
	{
		if (rs.IsOpen())
		{
			rs.Close();
		}

		if (pAdodb.IsOpen())
		{
			pAdodb.Close();
			//delete pAdodb;//pAdodb=NULL;
		}
		return ResponseQUIT(lpPerSocketContext) ;
	}

	rs.MoveFirst();
	CString strComment,strEmail;
	int iVersion;

	head_struct.AddData(rs.GetRecordCount());
	while (!rs.IsEOF())
	{
		rs.GetFieldValue("TaskID",iTaskID);
		head_struct.AddData(iTaskID);
		rs.GetFieldValue("Email",strEmail);
		head_struct.AddData(strEmail);
		rs.GetFieldValue("Comment",strComment);
		head_struct.AddData(strComment);
		rs.GetFieldValue("Version",iVersion);
		head_struct.AddData(iVersion);
		
		rs.MoveNext();
	}

	rs.Close();
	pAdodb.Close();


	//delete pAdodb;//pAdodb=NULL;
	//////////////////////////////////////////////////////////////////////////
	char *buff;
	head_struct.PackData(iHeadSize,buff);
	pHead = (char*)malloc(iHeadSize + 100);

	PackResponse(pHead,lpPerSocketContext->CommandState.dwTag,
		lpPerSocketContext->CommandState.nCommand,
		GET_TASK_NOTE_SUCCESS,
		buff,
		iHeadSize);

	freeEx (buff); 
	AddDataToClient(lpPerSocketContext,pHead,iHeadSize);

	freeEx(pHead);

	lpPerSocketContext->m_ReceiveBuffer.erase(lpPerSocketContext->m_ReceiveBuffer.begin(),
	lpPerSocketContext->m_ReceiveBuffer.begin()+lpPerSocketContext->CommandState.dwHeaderSize);

	return COMMAND_OK;
}

 
int ResponseSET_TASKNOTE_NEW(PPER_SOCKET_CONTEXT lpPerSocketContext)
{
	enum GET_TASK_NOTE_ERROR_CODE
	{
		SET_TASK_NOTE_SUCCESS = 0,
		SET_TASK_NOTE_FAIL = 1
	};

	int iIndex = 0;
	int iTaskID =0;
	int iVersion =1;

	CString strComment;
	CString strName;
	CString strNotifyTime;
	CString strRelation;
	COleDateTime dDate;

	DWORD dwResult = SET_TASK_NOTE_SUCCESS;

	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,iTaskID))
		return ResponseQUIT(lpPerSocketContext);
		
	if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,strComment))
		return ResponseQUIT(lpPerSocketContext);
	
	//////////////////////////////////////////////////////////////////////////

	char *pHead = NULL; 
	int iHeadSize = 0;
	CInfoStruct head_struct;

	CADODatabase pAdodb;// = NULL;

	////////////////pAdodb = new CADODatabase();
	// if (pAdodb == NULL) 
	// {
	// return ResponseQUIT(lpPerSocketContext);
	// }
	// 
	pAdodb.SetConnectionString(g_strDBConnectionString);
	if(!pAdodb.Open())
	{
		//delete pAdodb;//pAdodb=NULL;
		return ResponseQUIT(lpPerSocketContext);
	}

	CString strQuery;
	CADORecordset rs(&pAdodb);
	strQuery.Format("SELECT * FROM [TaskNote_table] WHERE (TaskID = %d)AND (Email = '%s')",iTaskID,lpPerSocketContext->m_strUser);

	if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)
	{
		pAdodb.Close();
		//delete pAdodb;//pAdodb=NULL;
		return ResponseQUIT(lpPerSocketContext) ;
	}
	if (rs.GetRecordCount() <= 0)
	{
		rs.AddNew();
		//////////////////////////////////////////////////////////////////////////
		rs.SetFieldValue("TaskID",iTaskID);
		rs.SetFieldValue("Comment",strComment);
		rs.SetFieldValue("Email",CString(lpPerSocketContext->m_strUser));
		rs.SetFieldValue("Version",iVersion);
		rs.Update();
	}
	else
	{
		rs.GetFieldValue("Version", iVersion);
		iVersion+=1;
		rs.Edit();
	
		rs.SetFieldValue("Comment",strComment);
		rs.SetFieldValue("Version",iVersion);
		rs.Update();
	}

	rs.Close();

	pAdodb.Close(); 
	//delete pAdodb;//pAdodb=NULL;
	head_struct.AddData(iVersion);
	
	//////////////////////////////////////////////////////////////////////////
	char *buff;
	head_struct.PackData(iHeadSize,buff);
	pHead = (char*)malloc(iHeadSize + 100);
	PackResponse(pHead,
		lpPerSocketContext->CommandState.dwTag,
		lpPerSocketContext->CommandState.nCommand,
		SET_TASK_NOTE_SUCCESS,
		buff,
		iHeadSize);

	freeEx (buff); 
	AddDataToClient(lpPerSocketContext,pHead,iHeadSize);
	freeEx(pHead);

	lpPerSocketContext->m_ReceiveBuffer.erase(lpPerSocketContext->m_ReceiveBuffer.begin(),
	lpPerSocketContext->m_ReceiveBuffer.begin()+lpPerSocketContext->CommandState.dwHeaderSize);

	return COMMAND_OK;
}

 