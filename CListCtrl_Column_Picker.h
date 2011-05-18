

#pragma once

#include <atlbase.h>
#include "EditList.h"

class CListCtrl_Column_Picker : public CListCtrl
{
	struct ColumnState
	{
		ColumnState()
			:m_Visible(false)
			,m_OrgWidth(0)
			,m_OrgPosition(-1)
		{}
		bool m_Visible;
		int  m_OrgWidth;	// Width it had before being hidden
		int  m_OrgPosition;	// Position it had before being hidden
	};
	CSimpleArray<ColumnState>	m_ColumnStates;
	int GetColumnStateCount();
	void InsertColumnState(int nCol, bool bVisible, int nOrgWidth = 0);
	void DeleteColumnState(int nCol);
	ColumnState& GetColumnState(int nCol);

	DECLARE_MESSAGE_MAP()

	virtual afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual afx_msg LRESULT OnDeleteColumn(WPARAM wParam, LPARAM lParam);
	virtual afx_msg LRESULT OnInsertColumn(WPARAM wParam, LPARAM lParam);
	virtual afx_msg LRESULT OnSetColumnWidth(WPARAM wParam, LPARAM lParam);
	virtual afx_msg BOOL OnHeaderBeginResize(UINT id, NMHDR* pNmhdr, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderEndDrag(UINT id, NMHDR* pNmhdr, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderDividerDblClick(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnContextMenu(CWnd*, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	
	//virtual afx_msg void OnLButtonUp

	virtual void PreSubclassWindow();

public:
	bool IsColumnVisible(int nCol);
	int GetFirstVisibleColumn();
	BOOL ShowColumn(int nCol, bool bShow);
	BOOL SetColumnWidthAuto(int nCol = -1, bool includeHeader = false);
};