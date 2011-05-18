// MyTree.cpp : implementation file
//

#include "stdafx.h"
#include "MVCTree.h"
#include "MyTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTree

CMyTree::CMyTree()
{
	m_vData.clear();
	m_nNumItem=0;
}

CMyTree::~CMyTree()
{
	m_vData.clear();
}


BEGIN_MESSAGE_MAP(CMyTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTree)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTree message handlers

HTREEITEM CMyTree::InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParentT, HTREEITEM hInsertAfter)
{
	m_nNumItem++;
	CString strData;
	strData.Format("phan tu thu %d", m_nNumItem);
	m_vData.push_back(strData);
	HTREEITEM hItem = CTreeCtrl::InsertItem(lpszItem, nImage, nSelectedImage, hParentT);

	this->SetItemData(hItem, m_nNumItem-1);

	return hItem;
}

void CMyTree::SetNodeCheckValue(HTREEITEM hItem, BOOL bValue)
{
	//SetCheck(hItem,bValue);
	HTREEITEM childItem;
	childItem=GetNextItem(hItem,TVGN_CHILD);
	while(childItem!=NULL)
	{
		SetCheckChildValue(childItem,bValue);
		childItem=GetNextItem(childItem,TVGN_NEXT);
	}
	
	bool iStop=false;
	HTREEITEM hParent=hItem;
	while(!iStop)
	{
		hParent=GetParentItem(hParent);
		if(hParent==NULL)
			break;
		if(!bValue)
		{
			SetCheck(hParent,bValue);
		}
		else
		{
			childItem=GetNextItem(hParent,TVGN_CHILD);
			BOOL bCheck=TRUE;
			while(childItem!=NULL)
			{
				if(hItem!=childItem)
					if(!GetCheck(childItem))
					{
						bCheck=FALSE;
						break;
					}
					childItem=GetNextItem(childItem,TVGN_NEXT);
			}
			SetCheck(hParent,bCheck);
			if(bValue!=bCheck)
				iStop=true;
		}
	}
}


void CMyTree::SetCheckChildValue(HTREEITEM hItem, BOOL bValue)
{
	SetCheck(hItem,bValue);
	HTREEITEM childItem=GetNextItem(hItem,TVGN_CHILD);
	while(childItem!=NULL)
	{
		SetCheckChildValue(childItem,bValue);
		childItem=GetNextItem(childItem,TVGN_NEXT);
	}
}

void CMyTree::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint Position;
	GetCursorPos(&Position);
	ScreenToClient(&Position);
	HTREEITEM Clicked;
	
	TV_HITTESTINFO Info;
	Info.pt=Position;
	HitTest(&Info);
	if(Info.hItem!=NULL&&Info.flags==TVHT_ONITEMSTATEICON)
	{
		Clicked=Info.hItem;
		
		BOOL bValue=GetCheck(Info.hItem);
		SetNodeCheckValue(Info.hItem,!bValue);
		
	//	SetCheck(Info.hItem,bValue);
		this->Select(Info.hItem,TVGN_CARET);
		
		AfxMessageBox(m_vData[this->GetItemData(Clicked)]);
		//::PostMessage(this->GetParent()->GetParent()->GetSafeHwnd(),TM_NODE_CHECK_CHANGE,(WPARAM)Info.hItem,0);
	}
	else
		Clicked=NULL;
	*pResult = 0;
}
