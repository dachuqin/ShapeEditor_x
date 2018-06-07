// FS_ListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "shpeditor.h"
#include "FS_ListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_ListCtrl

CFS_ListCtrl::CFS_ListCtrl()
{
}

CFS_ListCtrl::~CFS_ListCtrl()
{
}


BEGIN_MESSAGE_MAP(CFS_ListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFS_ListCtrl)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_ListCtrl message handlers


void CFS_ListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POSITION   pos;   
	pos=m_ListCtrl.GetFirstSelectedItemPosition(); 
	int   n=m_ListCtrl.GetNextSelectedItem(pos);
	CString strFieldName,strFieldType;
	m_strField=m_ListCtrl.GetItemText(n,0);
	m_strFieldType=m_ListCtrl.GetItemText(n,1);	
	CListCtrl::OnLButtonUp(nFlags, point);
}
