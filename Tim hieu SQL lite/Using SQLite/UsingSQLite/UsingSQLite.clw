; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUsingSQLiteDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UsingSQLite.h"

ClassCount=4
Class1=CUsingSQLiteApp
Class2=CUsingSQLiteDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_USINGSQLITE_DIALOG
Class4=CAddUser
Resource4=IDD_ADD_USER

[CLS:CUsingSQLiteApp]
Type=0
HeaderFile=UsingSQLite.h
ImplementationFile=UsingSQLite.cpp
Filter=N

[CLS:CUsingSQLiteDlg]
Type=0
HeaderFile=UsingSQLiteDlg.h
ImplementationFile=UsingSQLiteDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:CAboutDlg]
Type=0
HeaderFile=UsingSQLiteDlg.h
ImplementationFile=UsingSQLiteDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_USINGSQLITE_DIALOG]
Type=1
Class=CUsingSQLiteDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDC_LIST_RESULT,SysListView32,1350631425
Control3=IDC_BTN_REFRESH,button,1342242816
Control4=IDC_BTN_ADD,button,1342242816
Control5=IDC_BTN_DEL,button,1342242816
Control6=IDC_BTN_UPDATE,button,1342242816
Control7=IDC_BTN_GETTABLE,button,1342242816
Control8=IDC_TEST,button,1342242816
Control9=IDC_RSEDIT,button,1342242816
Control10=IDC_THREAD1,button,1342242816
Control11=IDC_THREAD2,button,1342242816
Control12=IDC_STOPTHREAD1,button,1476460544
Control13=IDC_STOPTHREAD2,button,1476460544
Control14=IDC_LIST1,listbox,1352732931
Control15=IDC_LIST2,listbox,1352728835
Control16=IDC_BUTTON1,button,1342242816

[DLG:IDD_ADD_USER]
Type=1
Class=CAddUser
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_ACCOUNT,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_NAME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_ADDRESS,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242857

[CLS:CAddUser]
Type=0
HeaderFile=AddUser.h
ImplementationFile=AddUser.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DATETIMEPICKER1

