#if !defined(AFX_FS_MENUBUTTON_H__C225B70E_5C13_404E_A4CF_C0F51EACD05A__INCLUDED_)
#define AFX_FS_MENUBUTTON_H__C225B70E_5C13_404E_A4CF_C0F51EACD05A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_MenuButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFS_MenuButton window

class CFS_MenuButton : public CBitmapButton
{
// Construction
public:
	CFS_MenuButton();
    void SetMenuID(int nID);        //���ù����˵�ID
    void SetForeColor(COLORREF color);   //�����ı���ɫ
    void SetBkColor(COLORREF color);     //���ñ�����ɫ
    void SetText(CString str); //���ð�ť�ı�
    BOOL isClick();            //�Ƿ񵥻�����ť��
	// Attributes
public:
	
	// Operations
public:
	
	// Implementation
public:
	virtual ~CFS_MenuButton();	
	
private: 
    int         m_State;        //��ť״̬
    BOOL        b_InFlag;       //�������־
    BOOL        b_ClickFlag;    //����ѡ����
    BOOL        b_ClickBut;     //����������
    CString     m_strText;      //��ť����
    COLORREF    m_ForeColor;    //�ı���ɫ
    COLORREF    m_BackColor;    //����ɫ
    COLORREF    m_LRectBackColor;    //����ɫ

    CRect       m_ButRect;      //��ť�ߴ�
    CRect       m_LRect;        //��ť�󲿳ߴ�
    CRect       m_RRect;        //��ť�Ҳ��ߴ�
    CMenu       m_Menu;         //�����˵�
    int         m_MenuID;       //�˵�ID
	
    void DrawButton(CDC *pDC);    //���ư�ť
protected:
	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void	PreSubclassWindow();
	
	//{{AFX_MSG(CMenuButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_MENUBUTTON_H__C225B70E_5C13_404E_A4CF_C0F51EACD05A__INCLUDED_)
