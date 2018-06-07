#if !defined(AFX_MENUBUTTON_H__2DF74340_0CCE_4DB8_A237_CFEE1F5B391D__INCLUDED_)
#define AFX_MENUBUTTON_H__2DF74340_0CCE_4DB8_A237_CFEE1F5B391D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuButton window

class CMenuButton : public CButton
{
// Construction
public: 
    CMenuButton();        //构造函数
    void SetMenuID(int nID);        //设置关联菜单ID
    void SetForeColor(COLORREF color);   //设置文本颜色
    void SetBkColor(COLORREF color);     //设置背景颜色
    void SetText(CString str); //设置按钮文本
    BOOL isClick();            //是否单击主按钮区
	// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMenuButton();

	// Generated message map functions
private: 
    int         m_State;        //按钮状态
    BOOL        b_InFlag;       //鼠标进入标志
    BOOL        b_ClickFlag;    //单击选择区
    BOOL        b_ClickBut;     //单击主体区
    CString     m_strText;      //按钮文字
    COLORREF    m_ForeColor;    //文本颜色
    COLORREF    m_BackColor;    //背景色
    CRect       m_ButRect;      //按钮尺寸
    CRect       m_LRect;        //按钮左部尺寸
 //   CRect       m_RRect;        //按钮右部尺寸
    CMenu       m_Menu;         //弹出菜单
    int         m_MenuID;       //菜单ID
	
    void DrawButton(CDC *pDC);    //绘制按钮
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

#endif // !defined(AFX_MENUBUTTON_H__2DF74340_0CCE_4DB8_A237_CFEE1F5B391D__INCLUDED_)
