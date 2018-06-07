// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ShpEditor.h"

#include "MainFrm.h"
#include "EditorToolBar.h"
#include "MapToolBar.h"
#include "ShpEditorView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDITOR_VISIBLE, OnEditorVisible)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_VISIBLE, OnUpdateEditorVisible)
	ON_COMMAND(ID_TOOLS_VISIBLE, OnToolsVisible)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VISIBLE, OnUpdateToolsVisible)
	ON_COMMAND(ID_LAYER_MANAGE, OnLayerManage)
	ON_UPDATE_COMMAND_UI(ID_LAYER_MANAGE, OnUpdateLayerManage)
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FEATURE_PROPERTY,OnChangeFeature)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CRect rtClient;
	GetClientRect(&rtClient);
	
	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, rtClient.right/4);
	

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	if(!CreateToolbar())	return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::CreateToolbar()
{
////******创建Tools工具栏*************/////////////////////
    if (!m_wndMapToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP| WS_VISIBLE 
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)
		|| !m_wndMapToolBar.LoadToolBar(IDR_MAP_TOOLS)) 
        return FALSE;
	
    m_wndMapToolBar.SetWindowText (_T ("浏览工具"));
    m_wndMapToolBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
    DockControlBar (&m_wndMapToolBar);
	
///////*******创建Editor工具栏*******************88/////////////////////////////////////
    if (!m_wndEditorToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
        return FALSE;	
	
    m_wndEditorToolBar.SetWindowText (_T ("编辑器"));
    m_wndEditorToolBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
    DockControlBar (&m_wndEditorToolBar, AFX_IDW_DOCKBAR_RIGHT|AFX_IDW_DOCKBAR_TOP  );

	////创建TOCBar窗口
    if (!m_wndLayerManageBar.Create(_T("图层管理器"), this, 123))
    {
        TRACE0("Failed to create mybar\n");
        return -1;      // fail to create
	}
	m_wndLayerManageBar.SetSCBStyle(m_wndLayerManageBar.GetSCBStyle() |
		SCBS_SIZECHILD);
    m_wndLayerManageBar.SetBarStyle(m_wndLayerManageBar.GetBarStyle() |
									CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndLayerManageBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndLayerManageBar, AFX_IDW_DOCKBAR_LEFT );
    return TRUE;
}


void CMainFrame::OnEditorVisible() 
{
	m_wndEditorToolBar.ShowWindow(m_wndEditorToolBar.IsWindowVisible() ? SW_HIDE:SW_SHOW);
	RecalcLayout();	
}

void CMainFrame::OnUpdateEditorVisible(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndEditorToolBar.IsWindowVisible());		
}

void CMainFrame::OnToolsVisible() 
{
	m_wndMapToolBar.ShowWindow(m_wndMapToolBar.IsWindowVisible() ? SW_HIDE:SW_SHOW);
	RecalcLayout();		
}

void CMainFrame::OnUpdateToolsVisible(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndMapToolBar.IsWindowVisible());	
}

void CMainFrame::OnLayerManage() 
{
	m_wndLayerManageBar.ShowWindow(m_wndLayerManageBar.IsWindowVisible() ? SW_HIDE:SW_SHOW);
	RecalcLayout();		
}

void CMainFrame::OnUpdateLayerManage(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndLayerManageBar.IsWindowVisible());	
}

//退出程序时提示
void CMainFrame::OnClose() 
{
	CShpEditorView *pView=(CShpEditorView*)this->GetActiveView();
	BOOL	bIsClose;
	bIsClose=pView->ExitApp();
	if(bIsClose==TRUE)
		CFrameWnd::OnClose();
}

void CMainFrame::ShowCoordinate(double X, double Y)
{
	CRect	rc;
	GetClientRect(&rc);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,rc.right/4);
	CString	strCoord;
	strCoord.Format("  X: %f  ,  Y: %f",X,Y);
	m_wndStatusBar.SetPaneText(1,strCoord);
}

LRESULT CMainFrame::OnChangeFeature(WPARAM wParam, LPARAM lParam)
{
	CShpEditorView *pView=(CShpEditorView*)this->GetActiveView();
	
	pView->SendMessage (WM_FEATURE_PROPERTY, wParam, lParam);
    return 0;
	
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	CShpEditorView *pView=(CShpEditorView*)this->GetActiveView();
	if(pView->m_pMGFeedback!=NULL)
		pView->m_pMGFeedback=NULL;
	
	CFrameWnd::OnMouseMove(nFlags, point);
}
