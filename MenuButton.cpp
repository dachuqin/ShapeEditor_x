// MenuButton.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "MenuButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuButton

CMenuButton::CMenuButton()
{
	m_MenuID = 0;        //�˵�ID
    b_InFlag = false;    //�����־
    m_State = 0;         //��ʼ״̬
    b_ClickFlag = false; //����ѡ������־
    b_ClickBut = false;  //������������־
    m_strText = _T("");  //��ť�ı�
    m_ForeColor = RGB(0,0,0);    //������ɫ
    m_BackColor = GetSysColor( COLOR_3DFACE );  //����ɫ	
}

CMenuButton::~CMenuButton()
{
}


BEGIN_MESSAGE_MAP(CMenuButton, CButton)
	//{{AFX_MSG_MAP(CMenuButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuButton message handlers
void CMenuButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC ); 
    m_ButRect = lpDrawItemStruct->rcItem;    //��ȡ��ť�ߴ�
    int nSavedDC = pDC->SaveDC(); 
    VERIFY( pDC ); 
	
    DrawButton(pDC);    //���ư�ť
	
    pDC->RestoreDC( nSavedDC ); 
	   
}
void CMenuButton::PreSubclassWindow()
{
    ModifyStyle( 0, BS_OWNERDRAW );    //���ð�ť����Ϊ�Ի�ʽ
	
    CButton::PreSubclassWindow(); 
	
}
void CMenuButton::DrawButton(CDC *pDC) 
{ 
    m_LRect.SetRect( m_ButRect.left, m_ButRect.top, 
        m_ButRect.right, m_ButRect.bottom );  //��ť�������ߴ�
	
    CPen Pen; 
    Pen.CreatePen(PS_SOLID, 1, RGB(192,192,192) ); 
    pDC->SelectObject( &Pen ); 
	
    pDC->FillSolidRect( m_ButRect, m_BackColor );  //������
    switch( m_State )    //��ͬ״̬����ͬ�߿�
    { 
    case 0:        //������ť
//        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER  , BF_RECT ); 
//		  pDC->MoveTo( m_ButRect.TopLeft() ); 
//		  pDC->LineTo( m_ButRect.right, m_ButRect.top ); 
        break; 
    case 1:        //������ʱ�İ�ť
        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER, BF_RECT ); 
        break; 
    case 2:   
		//������ť������ʱ�İ�ť
		pDC->FillSolidRect( m_ButRect, m_BackColor );  //������
        pDC->DrawEdge( &m_LRect, BDR_RAISEDINNER, BF_RECT ); 
		pDC->MoveTo( m_ButRect.TopLeft() ); 
		pDC->LineTo( m_ButRect.right, m_ButRect.top ); 
		pDC->MoveTo( m_ButRect.BottomRight()); 
		pDC->LineTo( m_ButRect.right, m_ButRect.top ); 

			
        break; 
    } 
		m_BackColor = GetSysColor( COLOR_3DFACE );  //����ɫ	
	
    POINT    m_pt[3], m_ptCentre;        //��ͷ����(��������)
    m_ptCentre = m_LRect.CenterPoint();  //ѡ�����е�λ��
	m_ptCentre.x=m_ptCentre.x+22;
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
    pDC->DrawText( m_strText, &m_LRect, DT_SINGLELINE | DT_LEFT
				   | DT_VCENTER | DT_END_ELLIPSIS); 
} 

void CMenuButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
 if( m_LRect.PtInRect(point) && m_MenuID )  //����ѡ����
    { 
        m_State = 2; 
        b_ClickBut = false;    //���������ť��־
        Invalidate();          //�ػ水ť
        b_ClickFlag = !b_ClickFlag;    //����ѡ������־
        if( b_ClickFlag )    //һ�ε����������˵�
        { 
            CRect rect = m_LRect; 
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

void CMenuButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_State = 0;    //�ָ�Ϊ������ť
    Invalidate();   //�ػ水ť
	
	CButton::OnLButtonUp(nFlags, point);
}

void CMenuButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !b_InFlag || GetCapture()!=this )    //�����밴ť
    { 
        b_InFlag = true;    //���ý����־
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
            b_ClickBut = false;  //���������־
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
void CMenuButton::SetMenuID(int nID) 
{ 
    m_MenuID = nID; 
} 

//���ð�ť�ı�
void CMenuButton::SetText(CString str) 
{ 
    m_strText = str; 
} 

//�����ı���ɫ
void CMenuButton::SetForeColor(COLORREF color) 
{ 
    m_ForeColor = color; 
    Invalidate(); 
} 

//���ñ�����ɫ
void CMenuButton::SetBkColor(COLORREF color) 
{ 
    m_BackColor = color; 
    Invalidate(); 
} 

//�Ƿ񵥻�����ť��
BOOL CMenuButton::isClick() 
{ 
    return b_ClickBut; 
} 
