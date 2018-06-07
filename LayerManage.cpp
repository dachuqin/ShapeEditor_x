// LayerManage.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "LayerManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerManage

CLayerManage::CLayerManage()
{
}

CLayerManage::~CLayerManage()
{
}


BEGIN_MESSAGE_MAP(CLayerManage, baseCMyBar)
	//{{AFX_MSG_MAP(CLayerManage)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerManage message handlers

int CLayerManage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (baseCMyBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	m_wndTree.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
		| TVS_DISABLEDRAGDROP|TVS_EDITLABELS,
		CRect(10, 10, 300, 100), this, ID_TREECTRL);
	
	
	//	m_TreeCtrl.SetImageList(&m_images,TVSIL_NORMAL);
	// set "normal" GUI-font
	CFont *font = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
	m_wndTree.SetFont(font);
	
	m_wndTree.InitTreeCtrl();
	return 0;
}

void CLayerManage::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	m_wndTree.OnLButtonDown(nFlags,point);
	
	baseCMyBar::OnLButtonDown(nFlags, point);
}

