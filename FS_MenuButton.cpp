// FS_MenuButton.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "FS_MenuButton.h"
#include "MaskedBitmap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_MenuButton

CFS_MenuButton::CFS_MenuButton()
{
	m_MenuID = 0;        //菜单ID
    b_InFlag = FALSE;    //进入标志
    m_State = 0;         //初始状态
    b_ClickFlag = FALSE; //单击选择区标志
    b_ClickBut = FALSE;  //单击主体区标志
    m_strText = _T("");  //按钮文本
    m_ForeColor = RGB(0,0,0);    //文字颜色
    m_BackColor = GetSysColor( COLOR_3DFACE );  //背景色	
	m_LRectBackColor= GetSysColor( COLOR_3DFACE );  //背景色
}

CFS_MenuButton::~CFS_MenuButton()
{
}


BEGIN_MESSAGE_MAP(CFS_MenuButton, CButton)
	//{{AFX_MSG_MAP(CFS_MenuButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_MenuButton message handlers
void CFS_MenuButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC ); 
    m_ButRect = lpDrawItemStruct->rcItem;    //获取按钮尺寸
    int nSavedDC = pDC->SaveDC(); 
    VERIFY( pDC ); 
	
    DrawButton(pDC);    //绘制按钮
	
    pDC->RestoreDC( nSavedDC ); 
	   
}
void CFS_MenuButton::PreSubclassWindow()
{
    ModifyStyle( 0, BS_OWNERDRAW );    //设置按钮属性为自绘式
	
    CButton::PreSubclassWindow(); 
	
}
void CFS_MenuButton::DrawButton(CDC *pDC) 
{ 
    m_LRect.SetRect( m_ButRect.left, m_ButRect.top, 
        m_ButRect.right-15, m_ButRect.bottom );  //按钮主体区尺寸
    m_RRect.SetRect( m_ButRect.right-14, m_ButRect.top, 
        m_ButRect.right, m_ButRect.bottom );    //按钮选择区尺寸
	
    CPen Pen; 
    Pen.CreatePen(PS_SOLID, 1, RGB(192,192,192) ); 
    pDC->SelectObject( &Pen ); 

    pDC->FillSolidRect( m_ButRect, m_BackColor );  //画背景
    pDC->FillSolidRect( m_LRect, m_LRectBackColor );  //主体画背景
    switch( m_State )    //不同状态画不同边框
    { 
//    case 0:        //正常按钮
 //         pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER  , BF_RECT ); 
//	      pDC->DrawEdge( &m_RRect, BDR_RAISEDINNER  , BF_RECT ); 
//        break; 
    case 1:        //鼠标进入时的按钮
        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER, BF_RECT ); 
        pDC->DrawEdge( &m_RRect, BDR_RAISEDINNER, BF_RECT ); 
        pDC->MoveTo( m_ButRect.TopLeft() ); 
        pDC->LineTo( m_ButRect.right, m_ButRect.top ); 
 
		break; 
    case 2:        //单击按钮主体区时的按钮
        pDC->DrawEdge( &m_LRect, BDR_SUNKENINNER, BF_RECT ); 
        break; 
    case 3:        //单击按钮选择区时的按钮
        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER, BF_RECT ); 
        break; 
    }
	POINT	ptCenter;
	
	ptCenter=m_LRect.TopLeft();

	CMaskedBitmap  bitmap;
	bitmap.LoadBitmap (IDB_SKETCH);
	bitmap.DrawTransparent (pDC, (int)ptCenter.x+2, (int)ptCenter.y+3, RGB (0, 255, 0));
	
    POINT    m_pt[3], m_ptCentre;        //箭头坐标(三个顶点)
    m_ptCentre = m_RRect.CenterPoint();  //选择区中点位置
    m_pt[0].x = m_ptCentre.x-3;        //计算箭头坐标
    m_pt[0].y = m_ptCentre.y-2; 
    m_pt[1].x = m_ptCentre.x+4; 
    m_pt[1].y = m_ptCentre.y-2; 
    m_pt[2].x = m_ptCentre.x; 
    m_pt[2].y = m_ptCentre.y+2; 
	
    pDC->SelectStockObject( BLACK_BRUSH );  //定义画刷（黑色）
    CRgn rgn; 
    rgn.CreatePolygonRgn( m_pt, 3, ALTERNATE ); 
    pDC->PaintRgn( &rgn );            //画选择区箭头
	
    pDC->SetTextColor( m_ForeColor ); //画主体区文字
    pDC->SetBkMode( TRANSPARENT ); 
    pDC->DrawText( m_strText, &m_LRect, DT_SINGLELINE | DT_CENTER 
				   | DT_VCENTER | DT_END_ELLIPSIS); 
}

void CFS_MenuButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_LRect.PtInRect(point) )    //单击按钮主体区
    { 
        m_State = 2;        //置按钮状态(2-正常按钮)
        b_ClickBut = TRUE;  //设置单击按钮标志
		m_LRectBackColor = GetSysColor( COLOR_3DLIGHT );  //背景色	
		
        Invalidate();       //重绘按钮
    } 
    else if( m_RRect.PtInRect(point) && m_MenuID )  //单击选择区
    { 
        m_State = 3; 
//        b_ClickBut = false;    //清除单击按钮标志
        Invalidate();          //重绘按钮
        b_ClickFlag = !b_ClickFlag;    //单击选择区标志
        if( b_ClickFlag )    //一次单击，弹出菜单
        { 
            CRect rect = m_RRect; 
            ClientToScreen(rect);    //转换为屏幕坐标
            point = rect.BottomRight(); 
            point.x -= rect.Width(); //设置弹出菜单的位置
			
            VERIFY(m_Menu.LoadMenu(m_MenuID));  //装入菜单资源
			
            CMenu* pPopup = m_Menu.GetSubMenu(0); 
            ASSERT(pPopup != NULL); 
            CWnd* pWndPopupOwner = this; 
			
            while (pWndPopupOwner->GetStyle() & WS_CHILD) 
                pWndPopupOwner = pWndPopupOwner->GetParent(); 
			
            pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, 
                point.x, point.y, pWndPopupOwner);  //弹出菜单
        } 
        else        //再次单击，清除菜单
        { 
            m_Menu.Detach(); 
            m_Menu.DestroyMenu(); 
        } 
    } 
	
	CButton::OnLButtonDown(nFlags, point);
}

void CFS_MenuButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	b_ClickBut = TRUE;  //设置单击按钮标志
	m_LRectBackColor = GetSysColor( COLOR_3DLIGHT );  //背景色	
	
	m_State = 2;    //恢复为正常按钮
//   Invalidate();   //重绘按钮
	
	CButton::OnLButtonUp(nFlags, point);
}

void CFS_MenuButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !b_InFlag || GetCapture()!=this )    //鼠标进入按钮
    { 
        b_InFlag = TRUE;    //设置进入标志
        SetCapture();       //捕获鼠标
        m_State = 1;        //置按钮状态(1-当前按钮)
        if( b_ClickFlag )   //检测单击选择区标志
        { 
            m_Menu.Detach();    //清除打开的菜单
            m_Menu.DestroyMenu(); 
            b_ClickFlag = false; 
        } 
        Invalidate();       //重绘按钮
    } 
    else 
    { 
        if ( !m_ButRect.PtInRect(point) )    //鼠标离开按钮
        { 
            b_InFlag = false;    //清除进入标志
            ReleaseCapture();    //释放鼠标捕获
 //           b_ClickBut = false;  //清除单击标志
            m_State = 0;         //置按钮状态(0-正常按钮)
            if( b_ClickFlag )    //检测单击选择区标志
            { 
                m_Menu.Detach();    //清除打开的菜单
                m_Menu.DestroyMenu(); 
                b_ClickFlag = false; 
            } 
            Invalidate();        //重绘按钮
        } 
    } 
	
	CButton::OnMouseMove(nFlags, point);
}

//设置关联菜单ID
void CFS_MenuButton::SetMenuID(int nID) 
{ 
    m_MenuID = nID; 
} 

//设置按钮文本
void CFS_MenuButton::SetText(CString str) 
{ 
    m_strText = str; 
} 

//设置文本颜色
void CFS_MenuButton::SetForeColor(COLORREF color) 
{ 
    m_ForeColor = color; 
    Invalidate(); 
} 

//设置背景颜色
void CFS_MenuButton::SetBkColor(COLORREF color) 
{ 
    m_BackColor = color; 
    Invalidate(); 
} 

//是否单击主按钮区
BOOL CFS_MenuButton::isClick() 
{ 
    return b_ClickBut; 
} 
