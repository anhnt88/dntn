int ResponseUPDATE_CHAT_TASK_NEW(PPER_SOCKET_CONTEXT lpPerSocketContext)

{

enum UPDATE_CHAT_ERROR_CODE

{

UPDATE_CHAT_NEW_SUCCESS = 0,

UPDATE_CHAT_NEW_FAIL = 1

};

int iIndex = 0;

int i;

long TaskID;

long InstructionID;

if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,TaskID))

return ResponseQUIT(lpPerSocketContext);

if(!CInfoStruct::GetValue(&lpPerSocketContext->m_ReceiveBuffer[0],iIndex++,InstructionID))

return ResponseQUIT(lpPerSocketContext);

CADODatabase pAdodb;// = NULL;

/*//pAdodb = new CADODatabase();

if (pAdodb == NULL) 

{

return ResponseQUIT(lpPerSocketContext);

}*/


pAdodb.SetConnectionString(g_strDBConnectionString);

if(!pAdodb.Open())

{

////delete pAdodb;//pAdodb=NULL;

return ResponseQUIT(lpPerSocketContext);

}

CString strQuery;

CADORecordset rs(&pAdodb);

strQuery.Format("SELECT * FROM [TaskInstruction_table] WHERE (TaskID = %d) AND (InstructionID > %d) AND ((RootInstructionID IN (SELECT InstructionID FROM [TaskInstructionReceiver_table] WHERE EmailReceiver = '%s') OR RootInstructionID IN (Select RootInstructionID FROM [TaskInstruction_table] WHERE TaskID = %d AND Private = 0)) OR ((Private = 0) AND (TaskID IN (Select TaskID FROM [MenInTask_table] WHERE Email = '%s'))))",TaskID,InstructionID,lpPerSocketContext->m_strUser,TaskID,lpPerSocketContext->m_strUser);

if(rs.Open(strQuery,CADORecordset::openQuery) == FALSE)

{

pAdodb.Close();

////delete pAdodb;//pAdodb=NULL;

return ResponseQUIT(lpPerSocketContext) ;

}

LIST_TASK_INSTRUCTION_CONTENT *pList = new (LIST_TASK_INSTRUCTION_CONTENT);

if (pList == NULL) 

{

rs.Close();

pAdodb.Close();

////delete pAdodb;//pAdodb=NULL;

return ResponseQUIT(lpPerSocketContext);

}

TASK_INSTRUCTION_CONTENT TaskInContent;

COleDateTime date;

while (!rs.IsEOF()) 

{

rs.GetFieldValue("InstructionID",TaskInContent.InstructionID);

TaskInContent.TaskID = TaskID;

rs.GetFieldValue("EmailSender",TaskInContent.EmailSender);

rs.GetFieldValue("Comment",TaskInContent.Comment);

rs.GetFieldValue("UpdateTime",date);

rs.GetFieldValue("Private",TaskInContent.Private);

rs.GetFieldValue("SharedAttachID",TaskInContent.SharedAttachID);

//rs

rs.GetFieldValue("ParentID",TaskInContent.ParentID);

rs.GetFieldValue("RootInstructionID",TaskInContent.RootInstructionID);

TaskInContent.Type = 0;

rs.GetFieldValue("Type",TaskInContent.Type);

TaskInContent.UpdateTime.Format("%f",date.m_dt);

rs.MoveNext();

pList->push_back(TaskInContent);

}

rs.Close();

 

CInfoStruct info_struct;


int iInstructionNum = pList->size();

info_struct.AddData(iInstructionNum);

for (i = 0; i<iInstructionNum;i++) 

{ 

info_struct.AddData(pList->at(i).InstructionID);

info_struct.AddData(pList->at(i).TaskID);

info_struct.AddData(pList->at(i).EmailSender);

info_struct.AddData(pList->at(i).Comment);

info_struct.AddData(pList->at(i).UpdateTime);

info_struct.AddData(pList->at(i).Private);

info_struct.AddData(pList->at(i).SharedAttachID);

info_struct.AddData(pList->at(i).Type);

info_struct.AddData(pList->at(i).ParentID);

info_struct.AddData(pList->at(i).RootInstructionID);

strQuery.Format("SELECT * FROM [TaskInstructionReceiver_table] WHERE InstructionID = %d",pList->at(i).InstructionID);

if(rs.Open(strQuery,CADORecordset::openQuery))

{

info_struct.AddData((int)rs.GetRecordCount());

if (rs.GetRecordCount() > 0)

{

rs.MoveFirst();

CString strReceiver;

while(!rs.IsEOF())

{


rs.GetFieldValue("EmailReceiver",strReceiver);

info_struct.AddData(strReceiver);

rs.MoveNext();

}

}

rs.Close();

}

else

{

info_struct.AddData((int)0);

}

}

rs.Close();

pAdodb.Close();

////delete pAdodb;//pAdodb=NULL;

delete pList;pList=NULL;

int iSize;

char* buff;

info_struct.PackData(iSize,buff);

char *pData = (char*)malloc(iSize + 100);

PackResponse(pData,

lpPerSocketContext->CommandState.dwTag,

lpPerSocketContext->CommandState.nCommand,

UPDATE_CHAT_NEW_SUCCESS,

buff,

iSize);

free (buff);

buff = NULL;

bool bresult=AddDataToClient(lpPerSocketContext,pData,iSize);


free(pData);

pData = NULL;


lpPerSocketContext->m_ReceiveBuffer.erase(lpPerSocketContext->m_ReceiveBuffer.begin(),

lpPerSocketContext->m_ReceiveBuffer.begin()+lpPerSocketContext->CommandState.dwHeaderSize);


return (bresult?COMMAND_OK:COMMAND_QUIT);

}

 
