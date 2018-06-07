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
	m_MenuID = 0;        //�˵�ID
    b_InFlag = FALSE;    //�����־
    m_State = 0;         //��ʼ״̬
    b_ClickFlag = FALSE; //����ѡ������־
    b_ClickBut = FALSE;  //������������־
    m_strText = _T("");  //��ť�ı�
    m_ForeColor = RGB(0,0,0);    //������ɫ
    m_BackColor = GetSysColor( COLOR_3DFACE );  //����ɫ	
	m_LRectBackColor= GetSysColor( COLOR_3DFACE );  //����ɫ
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
    m_ButRect = lpDrawItemStruct->rcItem;    //��ȡ��ť�ߴ�
    int nSavedDC = pDC->SaveDC(); 
    VERIFY( pDC ); 
	
    DrawButton(pDC);    //���ư�ť
	
    pDC->RestoreDC( nSavedDC ); 
	   
}
void CFS_MenuButton::PreSubclassWindow()
{
    ModifyStyle( 0, BS_OWNERDRAW );    //���ð�ť����Ϊ�Ի�ʽ
	
    CButton::PreSubclassWindow(); 
	
}
void CFS_MenuButton::DrawButton(CDC *pDC) 
{ 
    m_LRect.SetRect( m_ButRect.left, m_ButRect.top, 
        m_ButRect.right-15, m_ButRect.bottom );  //��ť�������ߴ�
    m_RRect.SetRect( m_ButRect.right-14, m_ButRect.top, 
        m_ButRect.right, m_ButRect.bottom );    //��ťѡ�����ߴ�
	
    CPen Pen; 
    Pen.CreatePen(PS_SOLID, 1, RGB(192,192,192) ); 
    pDC->SelectObject( &Pen ); 

    pDC->FillSolidRect( m_ButRect, m_BackColor );  //������
    pDC->FillSolidRect( m_LRect, m_LRectBackColor );  //���廭����
    switch( m_State )    //��ͬ״̬����ͬ�߿�
    { 
//    case 0:        //������ť
 //         pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER  , BF_RECT ); 
//	      pDC->DrawEdge( &m_RRect, BDR_RAISEDINNER  , BF_RECT ); 
//        break; 
    case 1:        //������ʱ�İ�ť
        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER, BF_RECT ); 
        pDC->DrawEdge( &m_RRect, BDR_RAISEDINNER, BF_RECT ); 
        pDC->MoveTo( m_ButRect.TopLeft() ); 
        pDC->LineTo( m_ButRect.right, m_ButRect.top ); 
 
		break; 
    case 2:        //������ť������ʱ�İ�ť
        pDC->DrawEdge( &m_LRect, BDR_SUNKENINNER, BF_RECT ); 
        break; 
    case 3:        //������ťѡ����ʱ�İ�ť
        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER, BF_RECT ); 
        break; 
    }
	POINT	ptCenter;
	
	ptCenter=m_LRect.TopLeft();

	CMaskedBitmap  bitmap;
	bitmap.LoadBitmap (IDB_SKETCH);
	bitmap.DrawTransparent (pDC, (int)ptCenter.x+2, (int)ptCenter.y+3, RGB (0, 255, 0));
	
    POINT    m_pt[3], m_ptCentre;        //��ͷ����(��������)
    m_ptCentre = m_RRect.CenterPoint();  //ѡ�����е�λ��
    m_pt[0].x = m_ptCentre.x-3;        //�����ͷ����
    m_pt[0].y = m_ptCentre.y-2; 
    m_pt[1].x = m_ptCentre.x+4; 
    m_pt[1].y = m_ptCentre.y-2; 
    m_pt[2].x = m_ptCentre.x; 
    m_pt[2].y = m_ptCentre.y+2; 
	
    pDC->SelectStockObject( BLACK_BRUSH );  //���廭ˢ����ɫ��
    CRgn rgn; 
    rgn.CreatePolygonRgn( m_pt, 3, ALTERNATE ); 
    pDC->PaintRgn( &rgn );            //��ѡ������ͷ
	
    pDC->SetTextColor( m_ForeColor ); //������������
    pDC->SetBkMode( TRANSPARENT ); 
    pDC->DrawText( m_strText, &m_LRect, DT_SINGLELINE | DT_CENTER 
				   | DT_VCENTER | DT_END_ELLIPSIS); 
}

void CFS_MenuButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_LRect.PtInRect(point) )    //������ť������
    { 
        m_State = 2;        //�ð�ť״̬(2-������ť)
        b_ClickBut = TRUE;  //���õ�����ť��־
		m_LRectBackColor = GetSysColor( COLOR_3DLIGHT );  //����ɫ	
		
        Invalidate();       //�ػ水ť
    } 
    else if( m_RRect.PtInRect(point) && m_MenuID )  //����ѡ����
    { 
        m_State = 3; 
//        b_ClickBut = false;    //���������ť��־
        Invalidate();          //�ػ水ť
        b_ClickFlag = !b_ClickFlag;    //����ѡ������־
        if( b_ClickFlag )    //һ�ε����������˵�
        { 
            CRect rect = m_RRect; 
            ClientToScreen(rect);    //ת��Ϊ��Ļ����
            point = rect.BottomRight(); 
            point.x -= rect.Width(); //���õ����˵���λ��
			
            VERIFY(m_Menu.LoadMenu(m_MenuID));  //װ��˵���Դ
			
            CMenu* pPopup = m_Menu.GetSubMenu(0); 
            ASSERT(pPopup != NULL); 
            CWnd* pWndPopupOwner = this; 
			
            while (pWndPopupOwner->GetStyle() & WS_CHILD) 
                pWndPopupOwner = pWndPopupOwner->GetParent(); 
			
            pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, 
                point.x, point.y, pWndPopupOwner);  //�����˵�
        } 
        else        //�ٴε���������˵�
        { 
            m_Menu.Detach(); 
            m_Menu.DestroyMenu(); 
        } 
    } 
	
	CButton::OnLButtonDown(nFlags, point);
}

void CFS_MenuButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	b_ClickBut = TRUE;  //���õ�����ť��־
	m_LRectBackColor = GetSysColor( COLOR_3DLIGHT );  //����ɫ	
	
	m_State = 2;    //�ָ�Ϊ������ť
//   Invalidate();   //�ػ水ť
	
	CButton::OnLButtonUp(nFlags, point);
}

void CFS_MenuButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !b_InFlag || GetCapture()!=this )    //�����밴ť
    { 
        b_InFlag = TRUE;    //���ý����־
        SetCapture();       //�������
        m_State = 1;        //�ð�ť״̬(1-��ǰ��ť)
        if( b_ClickFlag )   //��ⵥ��ѡ������־
        { 
            m_Menu.Detach();    //����򿪵Ĳ˵�
            m_Menu.DestroyMenu(); 
            b_ClickFlag = false; 
        } 
        Invalidate();       //�ػ水ť
    } 
    else 
    { 
        if ( !m_ButRect.PtInRect(point) )    //����뿪��ť
        { 
            b_InFlag = false;    //��������־
            ReleaseCapture();    //�ͷ���겶��
 //           b_ClickBut = false;  //���������־
            m_State = 0;         //�ð�ť״̬(0-������ť)
            if( b_ClickFlag )    //��ⵥ��ѡ������־
            { 
                m_Menu.Detach();    //����򿪵Ĳ˵�
                m_Menu.DestroyMenu(); 
                b_ClickFlag = false; 
            } 
            Invalidate();        //�ػ水ť
        } 
    } 
	
	CButton::OnMouseMove(nFlags, point);
}

//���ù����˵�ID
void CFS_MenuButton::SetMenuID(int nID) 
{ 
    m_MenuID = nID; 
} 

//���ð�ť�ı�
void CFS_MenuButton::SetText(CString str) 
{ 
    m_strText = str; 
} 

//�����ı���ɫ
void CFS_MenuButton::SetForeColor(COLORREF color) 
{ 
    m_ForeColor = color; 
    Invalidate(); 
} 

//���ñ�����ɫ
void CFS_MenuButton::SetBkColor(COLORREF color) 
{ 
    m_BackColor = color; 
    Invalidate(); 
} 

//�Ƿ񵥻�����ť��
BOOL CFS_MenuButton::isClick() 
{ 
    return b_ClickBut; 
} 
