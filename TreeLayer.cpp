// TreeLayer.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "TreeLayer.h"
#include "MainFrm.h"
#include "ShpEditorView.h"
#include "ShpEditor.h"
#include <afxwin.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeLayer

CTreeLayer::CTreeLayer()
{
}

CTreeLayer::~CTreeLayer()
{
}


BEGIN_MESSAGE_MAP(CTreeLayer, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeLayer)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_DELLAYER,OnLayerDelete)
	ON_COMMAND(ID_FILE_ADDSHP,OnAddLayer)
	ON_COMMAND(ID_ADD_REFERENCE,OnAddRefLayer)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_LAYER_SYMBOL, OnLayerSymbol)
	ON_COMMAND(ID_LAYER_SHOW_LABEL, OnLayerShowLabel)
	ON_UPDATE_COMMAND_UI(ID_LAYER_SHOW_LABEL, OnUpdateLayerShowLabel)
	ON_UPDATE_COMMAND_UI(ID_FILE_DELLAYER, OnUpdateFileDellayer)
	ON_UPDATE_COMMAND_UI(ID_LAYER_SYMBOL, OnUpdateLayerSymbol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeLayer message handlers

void CTreeLayer::InitTreeCtrl()
{
	SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CShpEditorApp	*pAPP=(CShpEditorApp*) AfxGetApp();
	m_TypeImgList.Create(13,13,ILC_COLOR,2,10);
	m_TypeImgList.Add(pAPP->LoadIcon(IDI_TREEBOOT));
	m_TypeImgList.Add(pAPP->LoadIcon(IDI_ICON_POLYGON));
	
	m_StatusBmpList.Create(IDB_STATUS_BITMAP,13,3,RGB(255,255,255));
	SetImageList(&m_StatusBmpList,TVSIL_STATE);
	SetImageList(&m_TypeImgList,TVSIL_NORMAL);

	HTREEITEM EditRoot = InsertItem("编辑层",0,0);
	HTREEITEM RefRoot = InsertItem("参考层",0,0);

	m_TCPreRefItem.bIsVisible=FALSE;
	m_TCPreRefItem.hti=NULL;
	m_TCPreRefItem.strRootName="参考层";

	m_TCPreEditItem.bIsVisible=FALSE;
	m_TCPreEditItem.hti=NULL;
	m_TCPreEditItem.strRootName="编辑层";

	m_bIsEditLayerLabelVisibel=TRUE;
	m_bIsRefLayerLabelVisibel=TRUE;
//	DelBmp=new	CBitmap; 
//	AddBmp=new	CBitmap; 
//	DelBmp->LoadBitMap(IDB_LAYER_DELETE);
//	AddBmp->LoadBitmap(IDB_LAYER_ADD);
}

void CTreeLayer::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags=0;
	HTREEITEM hti=HitTest(point,&uFlags);
	CMainFrame *pMF=(CMainFrame *) AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView *) pMF->GetActiveView();
	if(uFlags & TVHT_ONITEMSTATEICON)
	{
		int nImage=GetItemState(hti,TVIS_STATEIMAGEMASK) >>12;
		SetItemState(hti,INDEXTOSTATEIMAGEMASK(nImage==1 ? 2:1),TVIS_STATEIMAGEMASK);

		TC_HTREEITEM	TC_hti;
		TC_hti=pView->GetCurrentItemState(hti);

		HTREEITEM Root=this->GetParentItem(hti);
		CString	sLayerType;
		sLayerType=GetItemText(Root);//得到层的类型
		TC_hti.strRootName=sLayerType;

		if(TC_hti.bIsVisible==FALSE)
		{
			if(TC_hti.strRootName=="参考层")
			{	
				m_TCPreRefItem=pView->GetCurrentItemState(m_TCPreRefItem.hti);
				
				//检查上一次单击的项目是否可显
				if(m_TCPreRefItem.bIsVisible==TRUE && m_TCPreRefItem.hti!=hti)
				{
					int nImage=GetItemState(m_TCPreRefItem.hti,TVIS_STATEIMAGEMASK) >>12;
					SetItemState(m_TCPreRefItem.hti,INDEXTOSTATEIMAGEMASK(nImage==1 ? 2:1),TVIS_STATEIMAGEMASK);
				}
				m_TCPreRefItem=TC_hti;
				m_TCPreRefItem.bIsVisible=!m_TCPreRefItem.bIsVisible;
					
			}
			else if(TC_hti.strRootName=="编辑层")
			{

				m_TCPreEditItem=pView->GetCurrentItemState(m_TCPreEditItem.hti);
				
				//检查上一次单击的项目是否可显
				if(m_TCPreEditItem.bIsVisible==TRUE && m_TCPreEditItem.hti!=hti)
				{
					int nImage=GetItemState(m_TCPreEditItem.hti,TVIS_STATEIMAGEMASK) >>12;
					SetItemState(m_TCPreEditItem.hti ,INDEXTOSTATEIMAGEMASK(nImage==1 ? 2:1),TVIS_STATEIMAGEMASK);
				
				}
				m_TCPreEditItem=TC_hti;
				m_TCPreEditItem.bIsVisible=!m_TCPreEditItem.bIsVisible;
			}
		}
		else
		{
			if(TC_hti.strRootName=="参考层")
			{
				m_TCPreRefItem=TC_hti;
				m_TCPreRefItem.bIsVisible=!m_TCPreRefItem.bIsVisible;
			}
			else
			{
				m_TCPreEditItem=TC_hti;
				m_TCPreEditItem.bIsVisible=!m_TCPreEditItem.bIsVisible;
			}
		}
		pView->PostMessage(WM_CHANGE_STATE,(WPARAM)hti,0);
		return;
	}	
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CTreeLayer::AddLayerItem(int nLayerType,BOOL IsVisible,CString LayerName)
{
	HTREEITEM Root=GetRootItem();
	HTREEITEM item;
	switch(nLayerType) {
	case 1:
		{
			item=InsertItem(LayerName,1,1,Root);
			SetItemImage(item,1,1);
			Expand(Root,TVE_EXPAND);

			SetItemState(item,INDEXTOSTATEIMAGEMASK(2),TVIS_STATEIMAGEMASK);
			if(m_TCPreEditItem.hti!=NULL && m_TCPreEditItem.bIsVisible==TRUE)
			{
					int nImage=GetItemState(m_TCPreEditItem.hti,TVIS_STATEIMAGEMASK) >>12;
					SetItemState(m_TCPreEditItem.hti ,INDEXTOSTATEIMAGEMASK(nImage==1 ? 2:1),TVIS_STATEIMAGEMASK);
			}
			
			m_TCPreEditItem.bIsVisible=TRUE;
			m_TCPreEditItem.strRootName="编辑层";
			m_TCPreEditItem.hti=item;	
		}
		break;
	case 2:
		{
			HTREEITEM RefRoot=GetNextSiblingItem(Root);
			item=InsertItem(LayerName,1,1,RefRoot);
			SetItemImage(item,1,1);
			Expand(RefRoot,TVE_EXPAND);

			SetItemState(item,INDEXTOSTATEIMAGEMASK(2),TVIS_STATEIMAGEMASK);
			if(m_TCPreRefItem.hti!=NULL && m_TCPreRefItem.bIsVisible==TRUE)
			{
				int nImage=GetItemState(m_TCPreRefItem.hti,TVIS_STATEIMAGEMASK) >>12;
				SetItemState(m_TCPreRefItem.hti ,INDEXTOSTATEIMAGEMASK(nImage==1 ? 2:1),TVIS_STATEIMAGEMASK);
			}

			m_TCPreRefItem.bIsVisible=TRUE;
			m_TCPreRefItem.strRootName="参考层";
			m_TCPreRefItem.hti=item;
		}
		break;
	}
}

void CTreeLayer::OnAddLayer()
{
	HRESULT hr;
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	hr=pView->AddFile();
}

void CTreeLayer::OnAddRefLayer()
{
	HRESULT hr;
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	hr=pView->AddReferenceFile();
}

void CTreeLayer::OnLayerDelete()
{
	HTREEITEM hti=GetSelectedItem();
	HTREEITEM Root=this->GetParentItem(hti);
	if(Root==NULL)	return;

	CString	sLayerType;
	sLayerType=GetItemText(Root);//得到层的类型

	CString	sLayerName;
	sLayerName=GetItemText(hti);//得到层的名字

	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	pView->DeleteLayer(sLayerName);
	DeleteItem(hti);
	if(sLayerType=="编辑层")
	{
		m_TCPreEditItem.hti=NULL;
		m_TCPreEditItem.bIsVisible=FALSE;
	}
	else
	{
		m_TCPreRefItem.hti=NULL;
		m_TCPreRefItem.bIsVisible=FALSE;		
	}
}

void CTreeLayer::OnRButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags=0;
	HTREEITEM hti=HitTest(point,&uFlags);
	SelectItem(hti);
	if(hti!=NULL)
	{
		CMenu menu;
		menu.LoadMenu(IDR_LAYER_MENU);
//		menu.SetMenuItemBitmaps(ID_FILE_DELLAYER,MF_BYCOMMAND,&DelBmp,&DelBmp);
//		menu.SetMenuItemBitmaps(ID_FILE_ADDSHP,MF_BYCOMMAND,&AddBmp,&AddBmp);
		::GetCursorPos(&point);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	}
//	CTreeCtrl::OnRButtonDown(nFlags, point);//????有此语句时弹出菜单命令得到的对话框无法捕获鼠标.????
}

void CTreeLayer::OnLayerSymbol() 
{
	HTREEITEM hti=GetSelectedItem();
	CString	sLayerName;
	sLayerName=GetItemText(hti);
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	pView->SetLayerSymbol(sLayerName);
}

void CTreeLayer::OnLayerShowLabel() 
{
	HTREEITEM hti=GetSelectedItem();
	HTREEITEM Root=this->GetParentItem(hti);
	if(Root==NULL)	return;
	
	CString	sLayerType;
	sLayerType=GetItemText(Root);//得到层的类型
	
	CString	sLayerName;
	sLayerName=GetItemText(hti);//得到层的名字
	
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	if(sLayerType=="编辑层")
		pView->ShowFeatureLabel(sLayerType,m_bIsEditLayerLabelVisibel);
	else
		pView->ShowFeatureLabel(sLayerType,m_bIsRefLayerLabelVisibel);
	pView->FS_Refresh();
}

void CTreeLayer::OnUpdateLayerShowLabel(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bIsEditLayerLabelVisibel);
	pCmdUI->Enable(TRUE);
}

void CTreeLayer::OnUpdateFileDellayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	// TODO: Add your command update UI handler code here
	
}

void CTreeLayer::OnUpdateLayerSymbol(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	// TODO: Add your command update UI handler code here
	
}
