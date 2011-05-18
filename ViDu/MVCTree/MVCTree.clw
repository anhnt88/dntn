; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyTree
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MVCTree.h"

ClassCount=4
Class1=CMVCTreeApp
Class2=CMVCTreeDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMyTree
Resource3=IDD_MVCTREE_DIALOG

[CLS:CMVCTreeApp]
Type=0
HeaderFile=MVCTree.h
ImplementationFile=MVCTree.cpp
Filter=N

[CLS:CMVCTreeDlg]
Type=0
HeaderFile=MVCTreeDlg.h
ImplementationFile=MVCTreeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TREE

[CLS:CAboutDlg]
Type=0
HeaderFile=MVCTreeDlg.h
ImplementationFile=MVCTreeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MVCTREE_DIALOG]
Type=1
Class=CMVCTreeDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TREE,SysTreeView32,1350632199

[CLS:CMyTree]
Type=0
HeaderFile=MyTree.h
ImplementationFile=MyTree.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC

