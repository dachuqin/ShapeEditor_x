// EditorToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "EditorToolBar.h"
#include "MenuButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorToolBar

CEditorToolBar::CEditorToolBar()
{
}

CEditorToolBar::~CEditorToolBar()
{
}


BEGIN_MESSAGE_MAP(CEditorToolBar, CToolBar)
	//{{AFX_MSG_MAP(CEditorToolBar)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDITOR_MENU, OnEditorMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorToolBar message handlers

int CEditorToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!LoadToolBar (IDR_EDITOR))
        return -1;
    CClientDC dc (this);
    m_font.CreatePointFont (80, _T ("MS Sans Serif"));
    CFont* pOldFont = dc.SelectObject (&m_font);
	
    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    int cxChar = tm.tmAveCharWidth;
    int cyChar = tm.tmHeight + tm.tmExternalLeading;
	
    dc.SelectObject (pOldFont);
	
	SetButtonInfo (0, ID_EDITOR_MENU, TBBS_SEPARATOR, cxChar*14);
	CRect	rect;
	GetItemRect (0, &rect);
	if(!m_MenuButton.Create ("",WS_CHILD | WS_VISIBLE,rect, this, ID_EDITOR_MENU))
		return -1;
	m_MenuButton.SetMenuID(IDR_MENU_EDITOR);
	m_MenuButton.SetText(" ±à¼­Æ÷");

//	if(!CreateSketchButton())
//		return -1;
	return 0;
}

void CEditorToolBar::OnEditorMenu() 
{
   if( m_MenuButton.isClick() ) 
   { 
	   //ÏìÓ¦°´Å¥²Ù×÷
   }
}

BOOL CEditorToolBar::CreateSketchButton()
{
    CClientDC dc (this);
    CFont* pOldFont = dc.SelectObject (&m_font);
	
    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    int cxChar = tm.tmAveCharWidth;
    int cyChar = tm.tmHeight + tm.tmExternalLeading;
	
    dc.SelectObject (pOldFont);
	
	SetButtonInfo (11, ID_EDITOR_SKECTH, TBBS_SEPARATOR , cyChar*3);
	CRect	rect;
	GetItemRect (11, &rect);
	if(!m_FS_MenuButton.Create ("",WS_CHILD | WS_VISIBLE,rect, this, ID_EDITOR_SKECTH))
		return FALSE;
	m_FS_MenuButton.SetMenuID(IDR_MENU_SKETCH);

	m_FS_MenuButton.SetIcon(AfxGetApp ()->LoadIcon(IDI_SKETCH));
	return TRUE;
}
