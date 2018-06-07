// MapToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "MapToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapToolBar

CMapToolBar::CMapToolBar()
{
}

CMapToolBar::~CMapToolBar()
{
}


BEGIN_MESSAGE_MAP(CMapToolBar, CToolBar)
	//{{AFX_MSG_MAP(CMapToolBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapToolBar message handlers

int CMapToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if(!LoadToolBar(IDR_MAP_TOOLS))
		return -1;
	
	return 0;
}
