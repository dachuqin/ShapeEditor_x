// ShpEditorView.cpp : implementation of the CShpEditorView class
//

#include "stdafx.h"
#include "ShpEditor.h"

#include "ShpEditorDoc.h"
#include "ShpEditorView.h"
#include "StarDlg.h"
#include "ClipDlg.h"
#include "DistanceDlg.h"
#include "Coordinate.h"
#include "MainFrm.h"
#include "comutil.h"
#include <math.h>
#include "winuser.h"
#include "TreeLayer.h"
#include "iostream.h"
#include "DrawArcDlg.h"
#include "FS_FieldsDlg.h"
#include "FS_FeatureProperty.h"
#include "FS_SelectLabelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShpEditorView

IMPLEMENT_DYNCREATE(CShpEditorView, CFormView)

BEGIN_MESSAGE_MAP(CShpEditorView, CFormView)
	//{{AFX_MSG_MAP(CShpEditorView)
	ON_COMMAND(ID_ADD_REFERENCE, OnAddReference)
	ON_COMMAND(ID_FILE_ADDSHP, OnFileAddshp)
	ON_COMMAND(ID_FILE_NEWSHP, OnFileNewshp)
	ON_COMMAND(ID_FILE_SAVESHP, OnFileSaveshp)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVESHP_AS, OnFileSaveshpAs)
	ON_COMMAND(ID_EDITOR_STAR, OnEditorStar)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_STAR, OnUpdateEditorStar)
	ON_COMMAND(ID_EDITOR_STOP, OnEditorStop)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_STOP, OnUpdateEditorStop)
	ON_COMMAND(ID_EDITOR_UNDO, OnEditorUndo)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_UNDO, OnUpdateEditorUndo)
	ON_COMMAND(ID_EDITOR_REDO, OnEditorRedo)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_REDO, OnUpdateEditorRedo)
	ON_COMMAND(ID_EDITOR_MENU, OnEditorMenu)
	ON_COMMAND(ID_MAP_ZOOMIN, OnMapZoomin)
	ON_COMMAND(ID_MAP_ZOOMOUT, OnMapZoomout)
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_COMMAND(ID_MAP_FULLEXTENT, OnMapFullextent)
	ON_COMMAND(ID_MAP_ARROW, OnMapArrow)
	ON_COMMAND(ID_MAP_SELECT, OnMapSelect)
	ON_UPDATE_COMMAND_UI(ID_MAP_ZOOMIN, OnUpdateMapZoomin)
	ON_UPDATE_COMMAND_UI(ID_MAP_ZOOMOUT, OnUpdateMapZoomout)
	ON_UPDATE_COMMAND_UI(ID_MAP_PAN, OnUpdateMapPan)
	ON_UPDATE_COMMAND_UI(ID_MAP_ARROW, OnUpdateMapArrow)
	ON_UPDATE_COMMAND_UI(ID_MAP_SELECT, OnUpdateMapSelect)
	ON_COMMAND(ID_EDITOR_SELECT, OnEditorSelect)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SELECT, OnUpdateEditorSelect)
	ON_COMMAND(ID_EDITOR_SKECTH_POLYGON, OnEditorSkecthPolygon)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKECTH_POLYGON, OnUpdateEditorSkecthPolygon)
	ON_COMMAND(ID_EDITOR_SKETCH_LINE, OnEditorSketchLine)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKETCH_LINE, OnUpdateEditorSketchLine)
	ON_COMMAND(ID_EDITOR_COPY, OnEditorCopy)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_COPY, OnUpdateEditorCopy)
	ON_COMMAND(ID_EDITOR_PASTE, OnEditorPaste)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_PASTE, OnUpdateEditorPaste)
	ON_COMMAND(ID_EDITOR_DELETE, OnEditorDelete)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_DELETE, OnUpdateEditorDelete)
	ON_COMMAND(ID_EDITOR_MOVE, OnEditorMove)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MOVE, OnUpdateEditorMove)
	ON_COMMAND(ID_EDITOR_DIVIDE, OnEditorDivide)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_DIVIDE, OnUpdateEditorDivide)
	ON_COMMAND(ID_EDITOR_MERGE, OnEditorMerge)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MERGE, OnUpdateEditorMerge)
	ON_COMMAND(ID_EDITOR_UNION, OnEditorUnion)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_UNION, OnUpdateEditorUnion)
	ON_COMMAND(ID_EDITOR_INTERSECT, OnEditorIntersect)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_INTERSECT, OnUpdateEditorIntersect)
	ON_COMMAND(ID_EDITOR_BUFFER, OnEditorBuffer)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_BUFFER, OnUpdateEditorBuffer)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MENU, OnUpdateEditorMenu)
	ON_COMMAND(ID_EDITOR_SNAPPING, OnEditorSnapping)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SNAPPING, OnUpdateEditorSnapping)
	ON_COMMAND(ID_EDITOR_CLIP, OnEditorClip)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_CLIP, OnUpdateEditorClip)
	ON_COMMAND(ID_EDITOR_CUT_FEATURE, OnEditorCutFeature)
	ON_UPDATE_COMMAND_UI(ID_MAP_FULLEXTENT, OnUpdateMapFullextent)
	ON_MESSAGE(WM_CHANGE_STATE,OnChangeLayerState)
	ON_COMMAND(ID_LAYER_COLOR, OnLayerColor)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_CUT_FEATURE, OnUpdateEditorCutFeature)
	ON_COMMAND(ID_EDITOR_CUT, OnEditorCut)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_CUT, OnUpdateEditorCut)
	ON_COMMAND(ID_EDITOR_SKETCH_CIRCLE, OnEditorSketchCircle)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKETCH_CIRCLE, OnUpdateEditorSketchCircle)
	ON_COMMAND(ID_EDITOR_SKETCH_ARC, OnEditorSketchArc)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKETCH_ARC, OnUpdateEditorSketchArc)
	ON_COMMAND(ID_DRAW_COORDINATE, OnDrawCoordinate)
	ON_COMMAND(ID_DRAW_FINISH, OnDrawFinishAndRadius)
	ON_COMMAND(ID_DRAW_RADIUS, OnDrawRadius)
	ON_COMMAND(ID_DRAW_OFFSET, OnDrawOffset)
	ON_COMMAND(ID_DRAW_DELETE_SKETCH, OnDrawDeleteSketch)
	ON_COMMAND(ID_DRAW_CONCEL_MENU, OnDrawConcelMenu)
	ON_COMMAND(ID_EDITOR_SKECTH, OnEditorSkecth)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SKECTH, OnUpdateEditorSkecth)
	ON_COMMAND(ID_EDITOR_MODIFY_INSERT_VERTEX, OnEditorModifyInsertVertex)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MODIFY_INSERT_VERTEX, OnUpdateEditorModifyInsertVertex)
	ON_COMMAND(ID_EDITOR_MODIFY_DELETE_VERTEX, OnEditorModifyDeleteVertex)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MODIFY_DELETE_VERTEX, OnUpdateEditorModifyDeleteVertex)
	ON_COMMAND(ID_EDITOR_MODIFY_BACK, OnEditorModifyBack)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MODIFY_BACK, OnUpdateEditorModifyBack)
	ON_COMMAND(ID_EDITOR_MODIFY_CANCEL, OnEditorModifyCancel)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_MODIFY_CANCEL, OnUpdateEditorModifyCancel)
	ON_COMMAND(ID_EDITOR_PROPERTY, OnEditorProperty)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_PROPERTY, OnUpdateEditorProperty)
	ON_COMMAND(ID_LAYER_PROPERTY, OnLayerProperty)
	ON_UPDATE_COMMAND_UI(ID_LAYER_PROPERTY, OnUpdateLayerProperty)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVESHP, OnUpdateFileSaveshp)
	ON_COMMAND(ID_EDITOR_EXCHANGE_LAYER_INDEX, OnEditorExchangeLayerIndex)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_EXCHANGE_LAYER_INDEX, OnUpdateEditorExchangeLayerIndex)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FEATURE_PROPERTY,OnChangeFeature)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShpEditorView construction/destruction

CShpEditorView::CShpEditorView()
	: CFormView(CShpEditorView::IDD)
{
	//{{AFX_DATA_INIT(CShpEditorView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CShpEditorView::~CShpEditorView()
{
}

void CShpEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShpEditorView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CShpEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CShpEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//////////////////////////////////////////////////////////////////////////
	 HRESULT	hr;
	m_pMapControl=GetDlgItem(IDC_MAPCONTROL)->GetControlUnknown();
	hr=m_pMapControl->get_Map(&m_pMap);
	
	SetMouse();

	m_pRefLayerArray.CreateInstance(CLSID_Array);
	m_pEditLayerArray.CreateInstance(CLSID_Array);
	m_bMouseMove=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseNormal=FALSE;
	m_bMouseCross=FALSE;

	m_nIndex=-1;
	m_nEditIndex=-1;
	m_nRefIndex=-1;
	m_bSelectedMultiPart=FALSE;
	
	m_bIsHitSketchMenu=FALSE;
	m_Property = NULL;
	m_bIsEditLayerLabelVisibel	= FALSE;
	m_bIsRefLayerLabelVisibel	= FALSE;

	m_pNCArc=NULL;
	m_SnapOperator=NULL;
	m_pModifyPolygon=NULL;
	
	m_bIsPanFinish=FALSE;
	

	m_bSnapEditLayer=FALSE;
	m_bSnap=FALSE;
	m_bEdit=FALSE;
	m_bIsHasEditLayer=FALSE;
	m_bSelected=FALSE;
	m_bDrag=FALSE;
	m_OnSelFea=FALSE;
	m_lSeleteCount=0;
	m_bIsCut=FALSE;
	
	m_pNPFeedback=NULL;

	m_bIsCatch=FALSE;
	
/*	CStarDlg	starDlg;
	HRESULT		hr;
	if(starDlg.DoModal()==IDOK)
	{
		int nstate;
		nstate=starDlg.m_nState;
		if(nstate==1)
		{
			hr=AddReferenceFile();
			if(FAILED(hr))	return;
			hr=NewFile();
			if(FAILED(hr))	return;
		}
		else
		{
			hr=AddFile();
			if(FAILED(hr))	return;
		}
	}
*/
}

/////////////////////////////////////////////////////////////////////////////
// CShpEditorView diagnostics

#ifdef _DEBUG
void CShpEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CShpEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CShpEditorDoc* CShpEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShpEditorDoc)));
	return (CShpEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShpEditorView message handlers


void CShpEditorView::OnAddReference() 
{
	HRESULT	hr;
	hr=AddReferenceFile();
	if(FAILED(hr))	return;
}

void CShpEditorView::OnFileAddshp() 
{
	HRESULT	hr;
	hr=AddFile();
	if(FAILED(hr))
		if(FAILED(hr))	return;
	else
		m_bIsHasEditLayer=TRUE;
}

void CShpEditorView::OnFileNewshp()
{
	HRESULT	hr;
	hr=NewFile();
	if(FAILED(hr))
		return;
	else
		m_bIsHasEditLayer=TRUE;

	CFS_FieldsDlg	LayerProperty;	
	LayerProperty.DoModal();
}

void CShpEditorView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if(m_pMapControl!=NULL)
	{
		CRect rc;
		GetClientRect(&rc);
		GetDlgItem(IDC_MAPCONTROL)->MoveWindow(rc);
	}
}
//////////////***********加入层***************////////////////////////////////////////

HRESULT	CShpEditorView::AddFile()
{
	HRESULT	hr;
	CShpEditorDoc *m_pDocument;
	m_pDocument=GetDocument();
	if(m_pMapControl==NULL)
	{
		hr=m_pMapControl=GetDlgItem(IDC_MAPCONTROL)->GetControlUnknown();
		if(FAILED(hr))	return hr;
	}
	CString	strName;
	hr=m_pDocument->AddShp(&strName);//打开编辑文件和文件名
	if(FAILED(hr))	return hr;

	hr=IsHasLayer(strName);
	if(!FAILED(hr)) 
	{
		MessageBox("该图层已被加入!","面编辑工具",MB_OK|MB_ICONWARNING);
		return E_FAIL;
	}

	m_nLayerType=1;

	hr=AddLayerNameToTree(strName);
	if(FAILED(hr))	return hr;

	m_pWorkspace=m_pDocument->m_pWorkspace;	 //得到工作区
	if(m_pWorkspace!=NULL)
		m_pWorkspaceEdit=(IWorkspaceEditPtr)m_pWorkspace;//开始编辑

//////********从工作区中得到m_pEditLayer******/////////////////////////

	
	m_pEditDataset=m_pDocument->m_pDataset;
	IFeatureClassPtr	pFeatureClass(m_pEditDataset);
	IFeatureLayerPtr	pEditLayer(CLSID_FeatureLayer);
	hr=pEditLayer->putref_FeatureClass(pFeatureClass);
	if(FAILED(hr)) return hr;

	m_pEditLayerArray->Add((LPUNKNOWN) pEditLayer);
	pEditLayer->put_Visible(VARIANT_FALSE);
	ShowLayer(pEditLayer,TRUE);
	
	hr=m_pMap->AddLayer(m_pEditLayer);
	if(FAILED(hr))	return hr;
	
	hr=m_pMap->MoveLayer(m_pEditLayer,0);
	IActiveViewPtr	pActiveView(m_pMap);
	pActiveView->Refresh();
	return S_OK;
}

//////////////***********加入参考层***************////////////////////////////////////////
HRESULT	CShpEditorView::AddReferenceFile()
{
	HRESULT	hr;
	CShpEditorDoc *m_pDocument;
	m_pDocument=GetDocument();

	if(m_pMapControl==NULL)
	{
		hr=m_pMapControl=GetDlgItem(IDC_MAPCONTROL)->GetControlUnknown();
		if(FAILED(hr))	return hr;
	}
	CString strName;
	hr=m_pDocument->AddReference(&strName);
	if(FAILED(hr))	return hr;

	hr=IsHasLayer(strName);
	if(!FAILED(hr)) 
	{
		MessageBox("该图层已被加入!","面编辑工具",MB_OK|MB_ICONWARNING);
		return E_FAIL;
	}
	
	m_nLayerType=2;


	hr=AddLayerNameToTree(strName);//把层的名字加到树控键中
	if(FAILED(hr))	return hr;

	IFeatureLayerPtr	pRepLayer;
	pRepLayer=m_pDocument->m_pRefLayer;//得到参考层
	if (pRepLayer==NULL) return E_FAIL;

	hr=m_pMap->AddLayer(pRepLayer);

	m_pRefLayerArray->Add((LPUNKNOWN) pRepLayer);//加入数组
	pRepLayer->put_Visible(VARIANT_FALSE);
	ShowLayer(pRepLayer,FALSE);

	if(FAILED(hr))	return hr;
	if(m_pEditLayer!=NULL)
		m_pMap->MoveLayer(m_pEditLayer,0);

	IActiveViewPtr	pActiveView;
	m_pMapControl->get_ActiveView(&pActiveView);
	pActiveView->Refresh();
	return S_OK;
}
//////////////***********新建层***************////////////////////////////////////////

HRESULT CShpEditorView::NewFile()
{
	HRESULT	hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	
	if(1) //m_pEditLayer==NULL)//检查参考图层是否打开
	{
		IFeatureClassPtr	pFeaClass;
		CString strName;
		hr=pDocument->NewShpFile(&strName,&pFeaClass);
		if(FAILED(hr))	return hr;
		m_nLayerType=1;
		
		hr=AddLayerNameToTree(strName);
		m_pWorkspace=pDocument->m_pWorkspace;
		m_pWorkspaceEdit=m_pWorkspace;

		IFeatureLayerPtr	pFeaLayer(CLSID_FeatureLayer);
		pFeaLayer->putref_FeatureClass(pFeaClass);

		IFeatureLayerPtr	pEditLayer;
		pEditLayer=pFeaLayer;
		m_pEditLayerArray->Add((LPUNKNOWN) pEditLayer);
		pEditLayer->put_Visible(VARIANT_FALSE);
		ShowLayer(pEditLayer,TRUE);
		
		m_pMap->AddLayer(m_pEditLayer);
		m_pMap->MoveLayer(m_pEditLayer,0);
	}
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
	
	return	S_OK;

}

void CShpEditorView::OnFileSaveshp()
{
	HRESULT	hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();

	if(m_pEditLayer==NULL)	return;
	hr=SaveCurrentFile();
	if(FAILED(hr))	return;
}

//另存为
void CShpEditorView::OnFileSaveshpAs() 
{
	HRESULT	hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();

	if(m_pEditLayer==NULL)	return;

	ILayerPtr	pLayer;
	m_pMap->get_Layer(0,&pLayer);
	IFeatureLayerPtr	pFeaLayer;
	pFeaLayer=(IFeatureLayerPtr) pLayer;

	if(m_pEditLayer!=NULL)//检查是否有新建的图层
	{
		IFeatureClassPtr	pFeaClass;
		CString strName;
		IFeatureClassPtr	pEditFeaClass;

		m_pEditLayer->get_FeatureClass(&pEditFeaClass);
		hr=pDocument->SaveASShp(pEditFeaClass,&pFeaClass);
		if(FAILED(hr))	return ;
		if(hr==E_NOINTERFACE) return;

		IWorkspacePtr	pWorkspace;
		pWorkspace=pDocument->m_pTempWorkspace;
		m_pTempWorkspaceEdit=(IWorkspaceEditPtr)pWorkspace;
/////////////////////////////////////////////////////////////////
		TempWorkspaceEditorStart();

		m_pTempWorkspaceEdit->StartEditOperation();
		m_pEditLayer->get_FeatureClass(&pEditFeaClass);
		
		CopyFeatureClass(pEditFeaClass,pFeaClass);
		
		m_pTempWorkspaceEdit->StopEditOperation();
		hr=SaveAsCurrentFile();
////////////////////////////////////////////////////////////////
	}
}

///////////********开始编辑*************////////////////////////////////
void CShpEditorView::OnEditorStar()
{
	HRESULT	hr;
	VARIANT_BOOL pIsBeingEdited;
	hr=m_pWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if(FAILED(hr))	return;
	if (pIsBeingEdited==VARIANT_FALSE)
	{
        hr=m_pWorkspaceEdit->StartEditing(VARIANT_TRUE);
		if(hr==-2147217069)
		{
			MessageBox("此文件正被另一程序使用!","面编辑工具",MB_OK|MB_ICONWARNING);
			return;
		}
		if(FAILED(hr))	return;
        hr=m_pWorkspaceEdit->EnableUndoRedo();
		if(FAILED(hr))	return;
		m_bEdit=TRUE;
		m_esriEditType=esriMoveGeometry;
	}
}

void CShpEditorView::OnUpdateEditorStar(CCmdUI* pCmdUI) 
{
	if( m_bEdit==TRUE)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(m_pWorkspaceEdit!=NULL && m_pEditLayer!=NULL);	
}

void CShpEditorView::TempWorkspaceEditorStart()
{
	HRESULT	hr;
	VARIANT_BOOL pIsBeingEdited;
	hr=m_pTempWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if(FAILED(hr))	return;
	if (pIsBeingEdited==VARIANT_FALSE)
	{
        hr=m_pTempWorkspaceEdit->StartEditing(VARIANT_TRUE);
		if(FAILED(hr))	return;
        hr=m_pTempWorkspaceEdit->EnableUndoRedo();
		if(FAILED(hr))	return;
	}		
}

//////////////********停止编辑*************/////////////////////////////

void CShpEditorView::OnEditorStop() 
{
	StopEditor();

}

void CShpEditorView::OnUpdateEditorStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit);	
}
///////************撤消操作*****************////////////////////////

void CShpEditorView::OnEditorUndo() 
{
	HRESULT		hr;
	IActiveViewPtr		pActiveView(m_pMap);
	
	VARIANT_BOOL bHasUndos;
	hr=m_pWorkspaceEdit->HasUndos(&bHasUndos);
	if(FAILED(hr))	return;
	if (bHasUndos==VARIANT_TRUE) 
	{
		hr=m_pWorkspaceEdit->UndoEditOperation();
		if(FAILED(hr))	return;
		hr=GetSelectedFeatures();//选中移动后的图形
		if(FAILED(hr))	hr;

		if(m_bIsEditLayerLabelVisibel)
			ShowFeatureLabel();
		
		pActiveView->Refresh();
	}	
}

void CShpEditorView::OnUpdateEditorUndo(CCmdUI* pCmdUI) 
{
	if(m_pWorkspaceEdit!=NULL)
	{
		HRESULT		hr;
		
		VARIANT_BOOL bHasUndos;
		hr=m_pWorkspaceEdit->HasUndos(&bHasUndos);
		if(FAILED(hr))	return;
		pCmdUI->Enable(bHasUndos==VARIANT_TRUE);	
	}
	else
		pCmdUI->Enable(FALSE);	
}
///////************重复操作*****************////////////////////////

void CShpEditorView::OnEditorRedo() 
{
	IActiveViewPtr		pActiveView(m_pMap);
	HRESULT		hr;
	
	VARIANT_BOOL bHasRedos;
	hr=m_pWorkspaceEdit->HasRedos(&bHasRedos);
	if(FAILED(hr))	return;
	if (bHasRedos==VARIANT_TRUE) 
	{
        m_pWorkspaceEdit->RedoEditOperation();
		
		pActiveView->Refresh();
	}
}

void CShpEditorView::OnUpdateEditorRedo(CCmdUI* pCmdUI)
{
	if(m_pWorkspaceEdit!=NULL)
	{
		HRESULT		hr;
		
		VARIANT_BOOL bHasRedos;
		hr=m_pWorkspaceEdit->HasRedos(&bHasRedos);
		if(FAILED(hr))	return;
		pCmdUI->Enable(bHasRedos==VARIANT_TRUE);	
	}
	else
		pCmdUI->Enable(FALSE);
}

void CShpEditorView::OnEditorMenu() 
{
	// TODO: Add your command handler code here
	
}

void CShpEditorView::OnMapArrow() 
{
	// TODO: Add your command handler code here
	m_esriARTool=esriARToolNoneSelected;
	m_esriEditType=esriTools;
	m_pMapControl->put_MousePointer(esriPointerDefault);
	
}

void CShpEditorView::OnMapZoomin() 
{
	// TODO: Add your command handler code here
	m_esriARTool=esriARToolMapZoomIn;
	m_esriEditType=esriTools;
	m_pMapControl->put_MousePointer(esriPointerZoomIn);
	
}

void CShpEditorView::OnMapZoomout() 
{
	// TODO: Add your command handler code here
	m_esriEditType=esriTools;
	m_esriARTool=esriARToolMapZoomOut;
	m_pMapControl->put_MousePointer(esriPointerZoomOut);
	
}

void CShpEditorView::OnMapPan() 
{
	// TODO: Add your command handler code here
	m_esriEditType=esriTools;
	m_esriARTool=esriARToolMapPan;
	m_pMapControl->put_MousePointer(esriPointerPan);
	
}

void CShpEditorView::OnMapFullextent() 
{
	// TODO: Add your command handler code here
	IActiveViewPtr pActiveView;
	HRESULT hr;
	hr=	m_pMapControl->get_ActiveView(&pActiveView);
	if(FAILED(hr)) return;
	
	IEnvelopePtr ipEnvelope;
	hr=pActiveView->get_FullExtent(&ipEnvelope);
	if(FAILED(hr)) return;
	pActiveView->put_Extent(ipEnvelope);
	pActiveView->Refresh();
}
void CShpEditorView::OnMapSelect()
{
	m_esriEditType=esriTools;
	m_esriARTool=esriARToolMapMeasure;
	m_pMapControl->put_MousePointer(esriPointerLabel);
}
void CShpEditorView::OnUpdateMapSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriARTool==esriARToolMapMeasure && m_esriEditType==esriTools);
	pCmdUI->Enable(m_pMapControl!=NULL);
}

void CShpEditorView::OnUpdateMapArrow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriARTool==esriARToolNoneSelected && m_esriEditType==esriTools);
	pCmdUI->Enable(m_pMapControl!=NULL);
	
}

void CShpEditorView::OnUpdateMapZoomin(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriARTool==esriARToolMapZoomIn && m_esriEditType==esriTools);
	pCmdUI->Enable(m_pMapControl!=NULL);
	
}

void CShpEditorView::OnUpdateMapZoomout(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_esriARTool==esriARToolMapZoomOut && m_esriEditType==esriTools);
	pCmdUI->Enable(m_pMapControl!=NULL);
	
}

void CShpEditorView::OnUpdateMapPan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_esriARTool==esriARToolMapPan && m_esriEditType==esriTools);
	pCmdUI->Enable(m_pMapControl!=NULL);
}
void CShpEditorView::OnUpdateMapFullextent(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pMapControl!=NULL);
}


BEGIN_EVENTSINK_MAP(CShpEditorView, CFormView)
    //{{AFX_EVENTSINK_MAP(CShpEditorView)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 1 /* OnMouseDown */, OnOnMouseDownMapcontrol, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 3 /* OnMouseMove */, OnOnMouseMoveMapcontrol, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 2 /* OnMouseUp */, OnOnMouseUpMapcontrol, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 4 /* OnDoubleClick */, OnOnDoubleClickMapcontrol, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 9 /* OnAfterDraw */, OnOnAfterDrawMapcontrol, VTS_VARIANT VTS_I4)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 13 /* OnKeyDown */, OnOnKeyDownMapcontrol, VTS_I4 VTS_I4)
	ON_EVENT(CShpEditorView, IDC_MAPCONTROL, 14 /* OnKeyUp */, OnOnKeyUpMapcontrol, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CShpEditorView::OnOnMouseDownMapcontrol(long button, long shift, long x, long y, double mapX, double mapY) 
{

	HRESULT hr;
	IPointPtr	pPoint(CLSID_Point);
	pPoint->PutCoords(mapX,mapY);
	m_pfromPoint=pPoint;//保存鼠标按下的点

	IActiveViewPtr	pActiveView(m_pMap);
	if(m_esriEditType!=esriTools)
		if (m_bEdit==FALSE) return;
	if(button==2)
	{
		switch(m_esriEditType) {
		case esriTools://Tools工具栏的操作
			{
			//	DownToolsOperation(pActiveView,pPoint);
			}
			break;
		case esriDrawLine://画线操作
			if(m_pNLFeedback!=NULL)
			{
				FS_Dump();
			}
			break;
		case esriDrawPolygon://画多边形操作
			{
				CMenu menu;
				menu.LoadMenu(IDR_MENU_DRAW_POLYGON);
				CPoint	point;
				::GetCursorPos(&point);
				menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
			}
			break;
		case esriDrawCircle://画圆形操作
			{
				m_pNCFeedback=NULL;
			}
			break;
		case esriDrawArc://画弧形操作
			{
				CMenu menu;
				menu.LoadMenu(IDR_MENU_DRAW_ARC);
				CPoint	point;
				::GetCursorPos(&point);
				menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
			}
			break;
		case esriMoveGeometry://移动要素操作
			{
				if(m_pModifyPolygon!=NULL)
				{
					if(m_pModifyPolygon->MouseMove(button,pPoint))
						m_pModifyPolygon->RightClick(pPoint);
				}
				else
				{
					CMenu menu;
					menu.LoadMenu(IDR_MENU_SELECT);
					CPoint	point;
					::GetCursorPos(&point);
					menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
						TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
				}
			}
			break;
		}		
		return;
	}
	
	IScreenDisplayPtr	pScrD;
	hr=pActiveView->get_ScreenDisplay(&pScrD);
	if(FAILED(hr)) return;


	switch(m_esriEditType) {
	case esriTools://Tools工具栏的操作
		{
			DownToolsOperation(pActiveView,pPoint);
		}
		break;
	case esriDrawLine://画线操作
		DownDrawLineOperation(pScrD,pPoint);
		break;
	case esriDrawPolygon://画多边形操作
	//	DownDrawPolygonOperation(pScrD,pPoint);
	//	m_pMapControl->put_MousePointer(esriPointerCrosshair);
//		break;
	case esriDrawCircle://画圆操作
		DownDrawCircleOperation(pScrD,pPoint);
	//	m_pMapControl->put_MousePointer(esriPointerCrosshair);
		break;
  	case esriDrawArc://画弧操作
		DownDrawArcOperation(pScrD,pPoint);
	//	m_pMapControl->put_MousePointer(esriPointerCrosshair);
 		break;
	case esriMoveGeometry://移动要素操作
		{
			if(m_pModifyPolygon!=NULL)
			{
				m_bIsCatch=m_pModifyPolygon->MouseDown(pPoint);
				if(m_bIsCatch==FALSE)
				{
					if(m_pModifyPolygon->IsModify())
						FinishModify();
					else
					{
						delete m_pModifyPolygon;
						m_pModifyPolygon=NULL;
						if(m_bSelected==TRUE && m_OnSelFea==TRUE)//移动要素
							DownMoveGeometryOperation(pScrD,pPoint);
						else
							SelectFeatureOperation(mapX,mapY);
					}
				}
			}
			else
			{
				if(m_bSelected==TRUE && m_OnSelFea==TRUE && shift!=2)//移动要素
					DownMoveGeometryOperation(pScrD,pPoint);
				else
				{
					if(shift==2)
					{
						SelectFeatureOperation(pPoint);
					}
					else
						SelectFeatureOperation(mapX,mapY);
				}
			}
			if(	m_Property!=NULL)
			{
				m_Property->GetSelectedFeature();
			}			
		}
		break;
	default:
		break;
	}
}

void CShpEditorView::OnOnMouseMoveMapcontrol(long button, long shift, long x, long y, double mapX, double mapY) 
{
//	if (m_bEdit==FALSE) return;

	ShowCoordinate(mapX,mapY);
	HRESULT hr;
	IActiveViewPtr			pActiveView(m_pMap);
	IScreenDisplayPtr		pScrD;
	pActiveView->get_ScreenDisplay(&pScrD);

	IPointPtr	pPoint(CLSID_Point);
	pPoint->PutCoords(mapX,mapY);

	switch(m_esriEditType) {
	case esriTools:
		if(m_esriARTool==esriARToolMapPan)
		{
			if(m_bIsPanFinish==TRUE)
			{
				pActiveView->Refresh();
				m_bIsPanFinish=FALSE;
			}
		}

		break;
	case esriDrawLine:
		MoveDrawLineOperation(pPoint);
		break;
	case esriDrawPolygon:
		{
			if(m_SnapOperator!=NULL)
			{
				m_SnapOperator->MoveTo(pPoint);
				m_pMapControl->put_MousePointer(esriPointerCrosshair);
				m_bMouseNormal=FALSE;
				m_bMouseModify=FALSE;
				m_bMouseMove=FALSE;
				

				BOOL bISCatch;
				IPointPtr	pCatchPoint;
				bISCatch=m_SnapOperator->GetCatchPoint(&pCatchPoint);
				if(bISCatch==TRUE)
					m_pCatchPoint=pCatchPoint;
				else
					m_pCatchPoint=NULL;
			}
			
			MoveDrawPolygonOperation(pPoint);
		}
		break;
	case esriDrawCircle:
		MoveDrawCircleOperation(pPoint);
		break;
	case esriDrawArc:
		{
			if(m_SnapOperator!=NULL)
			{
				m_SnapOperator->MoveTo(pPoint);
				
				BOOL bISCatch;
				IPointPtr	pCatchPoint;
				bISCatch=m_SnapOperator->GetCatchPoint(&pCatchPoint);
				if(bISCatch==TRUE)
				{
					m_pCatchPoint=pCatchPoint;
				}
				else
				{
					m_pCatchPoint=NULL;
				}
			}
			if(m_bMouseCross!=TRUE)
			{
				m_pMapControl->put_MousePointer(esriPointerCrosshair);
				m_bMouseNormal=FALSE;
				m_bMouseModify=FALSE;
				m_bMouseMove=FALSE;
				
				m_bMouseCross=TRUE;
			}
			MoveDrawArcOperation(pPoint);
		}
		break;
	case esriMoveGeometry:
		{
			BOOL	bIsCatch=FALSE;
			if(m_pModifyPolygon!=NULL)
			{
				bIsCatch=m_pModifyPolygon->MouseMove(button,pPoint);
			}

			if(bIsCatch==TRUE|| m_bIsCatch==TRUE)
			{
				if(bIsCatch==FALSE && button!=1)
				{
					if(m_bMouseNormal!=TRUE)
					{
						m_pMapControl->put_MousePointer(esriPointerCustom);
						m_pMapControl->putref_MouseIcon(m_pMouseEditNormal);
						m_bMouseNormal=TRUE;
						m_bMouseModify=FALSE;
						m_bMouseMove=FALSE;
					}
				}
				else
				{
					if (m_bMouseModify!=TRUE)
					{
						m_pMapControl->put_MousePointer(esriPointerCustom);
						m_pMapControl->putref_MouseIcon(m_pMouseModify);
						m_bMouseModify=TRUE;
						m_bMouseNormal=FALSE;
						m_bMouseMove=FALSE;
					}
				}
			}
			else
			{
				
				VARIANT_BOOL	vb;
				if(m_pGeometry!=NULL)
				{
					IRelationalOperatorPtr	pRelOpe(m_pGeometry);
					hr=pRelOpe->Contains(pPoint,&vb);//判断鼠标是否在选中的要素上方
					if(FAILED(hr))	return;
				}
			
				MoveMoveGeometryOperation(vb,button,pPoint);
			}			
		}
		break;
	}
}

void CShpEditorView::OnOnMouseUpMapcontrol(long button, long shift, long x, long y, double mapX, double mapY) 
{
	if(button!=1)
	{
		return;
	}
//	if (m_bEdit==FALSE) return;

	HRESULT hr;
	VARIANT_BOOL	vb;
	IPointPtr	pPoint(CLSID_Point);
	pPoint->PutCoords(mapX,mapY);

	IActiveViewPtr	ipActiveView(m_pMap);
				
	switch(m_esriEditType) {
	case esriMoveGeometry:
		{
			if(m_pModifyPolygon!=NULL)
			{
				m_pModifyPolygon->MouseUp(button,pPoint);
				ipActiveView->PartialRefresh(esriViewForeground,0,0);
				return;
			}
			if(m_pGeometry!=NULL)
			{
				IRelationalOperatorPtr	pRelOpe;
				pRelOpe=m_pGeometry;
				hr=pRelOpe->Contains(pPoint,&vb);//判断鼠标是否在选中的要素上方
				if(FAILED(hr))	return;
			}
			if(m_pMGFeedback!=NULL)
			{
				UpMoveGeometryOperation(pPoint);//移动要素
			}
			if(m_bIsEditLayerLabelVisibel)
				ShowFeatureLabel();
			
			ipActiveView->Refresh();
			
			if(vb==VARIANT_TRUE)
			{
				if(m_bMouseMove!=TRUE)
				{
					hr=m_pMapControl->put_MousePointer(esriPointerCustom);
					hr=m_pMapControl->putref_MouseIcon(m_pMouseMove);
					m_bMouseMove=TRUE;
					m_bMouseNormal=FALSE;
					m_bMouseModify=FALSE;
				}
			}
			else
			{
				if(m_bMouseNormal!=TRUE)
				{
					m_pMapControl->put_MousePointer(esriPointerCustom);
					m_pMapControl->putref_MouseIcon(m_pMouseEditNormal);
					m_bMouseNormal=TRUE;
					m_bMouseMove=FALSE;
					m_bMouseModify=FALSE;
				}
			}
			m_bDrag=FALSE;
			m_bPressDown=FALSE;
		}
		break;
	case esriTools:
		{

			if(m_esriARTool==esriARToolMapPan)
			{

				IActiveViewPtr	ipActiveView(m_pMap);
				ipActiveView->Refresh();
			}
		}
		break;
	}

	
}

void CShpEditorView::OnOnDoubleClickMapcontrol(long button, long shift, long x, long y, double mapX, double mapY) 
{
	if(button!=1)	return;
	HRESULT	hr;
	IPointPtr	pPoint(CLSID_Point);
	pPoint->PutCoords(mapX,mapY);


	switch(m_esriEditType) {
	case esriDrawLine:
		{
		//****************开始记录编辑**************************
			hr=m_pWorkspaceEdit->StartEditOperation();
			if(FAILED(hr))	return;
			DoubleClickDrawLine(pPoint);
		//******************停止编辑**************************
			hr=m_pWorkspaceEdit->StopEditOperation();
			m_pNLFeedback=NULL;
		}
		break;
	case esriDrawPolygon:
		{
		//****************开始记录编辑**************************
			hr=m_pWorkspaceEdit->StartEditOperation();
			if(FAILED(hr))	return;

			DoubleClickDrawPolygon(pPoint);

		//******************停止编辑**************************
			hr=m_pWorkspaceEdit->StopEditOperation();
			if(FAILED(hr))	return;	
//			m_pNPFeedback=NULL;
		}
		break;
	case esriDrawCircle:
		{
			DoubleClickDrawCircle(pPoint);
		}
		break;
	case esriDrawArc:
		{
			DoubleClickDrawArc(pPoint);
		}
		break;
	case esriMoveGeometry:
		{
			if(m_pEditLayer==NULL) return;
			if(m_lSeleteCount>1) return;
			if(m_pModifyPolygon==NULL)
			{
				IActiveViewPtr	pAct(m_pMap);
				IScreenDisplayPtr	pScrD;
				pAct->get_ScreenDisplay(&pScrD);

				m_pModifyPolygon=new CFS_ModifyPolygon;
				m_pModifyPolygon->Put_Display(pScrD);
				m_pModifyPolygon->Put_Layer(m_pEditLayer);
				m_pModifyPolygon->DoubleClick(pPoint);
				m_bMouseModify=FALSE;				
			}
			else
			{
				m_pModifyPolygon->DoubleClick(pPoint);
			}
			
		}
		break;
	}
//	IActiveViewPtr	pActiveView(m_pMap);
//	pActiveView->Refresh();

}
///////////////***********鼠标按下的操作******************////////////////////////////////////////////////

///////////////***********Tools工具栏内的操作******************////////////////////////////////////////////////

void CShpEditorView::DownToolsOperation(IActiveViewPtr	pActiveView,IPointPtr	pPoint)
{
	HRESULT	hr;

	switch(m_esriARTool) {
	case esriARToolNoneSelected:
		{
			IEnvelopePtr	ipEnvelope;
			m_pMapControl->TrackRectangle(&ipEnvelope);
		}
	break;
	case esriARToolMapZoomIn:
		{
			IEnvelopePtr ipEnvelope;
			hr=pActiveView->get_Extent(&ipEnvelope);
			if(FAILED(hr))
				return;
			hr=m_pMapControl->TrackRectangle(&ipEnvelope);
			if(FAILED(hr)) return;
			if(ipEnvelope==NULL) return;
			double xMin,yMin,xMax,yMax;
			if(S_OK!=ipEnvelope->get_XMin(&xMin)) xMin=0;
			if(S_OK!=ipEnvelope->get_YMin(&yMin)) yMin=0;
			if(S_OK!=ipEnvelope->get_XMax(&xMax)) xMax=0;
			if(S_OK!=ipEnvelope->get_YMax(&yMax)) yMax=0;
			if(xMin!=xMax && yMin!=yMax) // 用户拉框选择区域放大	
			{
				pActiveView->put_Extent(ipEnvelope);
			}
			else// 用户点击进行放大						
			{
				hr=pActiveView->get_Extent(&ipEnvelope);
				if(FAILED(hr)) return;
				ipEnvelope->CenterAt(pPoint);
				ipEnvelope->Expand(0.5,0.5,VARIANT_TRUE);
				pActiveView->put_Extent(ipEnvelope);
			}
			pActiveView->Refresh();				
			pActiveView->PartialRefresh(esriViewForeground,0,0);
		}
	break;
	case esriARToolMapZoomOut:
		{
			IEnvelopePtr ipEnvelope;
			hr=m_pMapControl->TrackRectangle(&ipEnvelope);
			if(FAILED(hr)) return;
			if(ipEnvelope==NULL) return;
			hr=pActiveView->get_Extent(&ipEnvelope);//// 用户点击进行缩小
			if(FAILED(hr)) return;
			ipEnvelope->CenterAt(pPoint);
			ipEnvelope->Expand(2,2,true);
			pActiveView->put_Extent(ipEnvelope);
			pActiveView->Refresh();	
			pActiveView->PartialRefresh(esriViewForeground,0,0);
		}
	break;
	case esriARToolMapPan:
		{

			m_pMapControl->Pan();
			if(m_bIsPanFinish==FALSE)
				m_bIsPanFinish=TRUE;
			
			IActiveViewPtr pActiveView(m_pMap);
			pActiveView->Refresh();
			pActiveView->PartialRefresh(esriViewForeground,0,0);
			
		}
		break;
	case esriARToolMapMeasure:
		{
			double mapX,mapY;
			pPoint->get_X(&mapX);
			pPoint->get_Y(&mapY);
			SelectFeatureOperation(mapX, mapY);
		}
	default:
		break;
	}

}
/////////////**************画线动作*********************888////////////////////////////////////

void CShpEditorView::DownDrawLineOperation(IScreenDisplayPtr pScrD,IPointPtr pPoint)
{
	HRESULT hr;
	
	if(m_pNLFeedback==NULL)
	{
		CoCreateInstance(CLSID_NewLineFeedback,
			NULL,CLSCTX_ALL,
			IID_INewLineFeedback,
			(void**)&m_pNLFeedback);
		ISymbolPtr	pSymbol;
		if(m_pNLFeedback==NULL)	return;
		m_pNLFeedback->get_Symbol(&pSymbol);
		ISimpleLineSymbolPtr	pSLSymbol(pSymbol);
		IRgbColorPtr pColor(CLSID_RgbColor);
		//设置填充色
		pColor->put_Blue(0);
		pColor->put_Green(200);
		pColor->put_Red(54);
			
		if(pSLSymbol!=NULL)
		pSLSymbol->put_Color(pColor);
		
		hr=m_pNLFeedback->putref_Display(pScrD);
		if(FAILED(hr)) return;
		hr=m_pNLFeedback->Start(pPoint);
		if(FAILED(hr)) return;
	}
	else
		hr=m_pNLFeedback->AddPoint(pPoint);
}
//画多边形的动作
void CShpEditorView::DownDrawPolygonOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint)
{
//	HRESULT hr;
//	BOOL	bValue;
	IActiveViewPtr			pActiveView(m_pMap);
//	IGraphicsContainerPtr	pGraCont(pActiveView);
	IElementPtr pRectElem ;
	if(m_pNPFeedback==NULL)
	{
		/*
		CoCreateInstance(CLSID_NewPolygonFeedback,
							NULL,CLSCTX_ALL,
							IID_INewPolygonFeedback,
							(void**)&m_pNPFeedback);
							*/
		m_pNPFeedback=new CFS_NewPolygon;
		ISymbolPtr	pSymbol;
		if(m_pNPFeedback==NULL)	return;
//		m_pNPFeedback->get_Symbol(&pSymbol);
		ISimpleLineSymbolPtr	pSLSymbol(CLSID_SimpleLineSymbol);
		IRgbColorPtr pColor(CLSID_RgbColor);
		//设置填充色
		pColor->put_Green(200);

		if(pSLSymbol!=NULL)
		{
			pSLSymbol->put_Color(pColor);
			pSLSymbol->put_Width(1);
		}
		pSymbol=pSLSymbol;
		
		m_pNPFeedback->putref_Display(pScrD);
		m_pNPFeedback->putref_Symbol(pSymbol);
//		if(FAILED(hr)) return;
		if(m_pCatchPoint!=NULL)//当鼠标捕获到要素的极点时，把此点加入新建要素
		{
			pPoint=m_pCatchPoint;			
			m_pCatchPoint=NULL;
		}
		m_pNPFeedback->Start(pPoint);
//		hr=DrawSmallRectangle( pPoint);//加入小方块
		
	}
	else
	{
		if(m_pCatchPoint!=NULL)//当鼠标捕获到要素的极点时，把此点加入新建要素
		{
			pPoint=m_pCatchPoint;			
			m_pCatchPoint=NULL;
		}
		m_pNPFeedback->AddPoint(pPoint);
	//	hr=DrawSmallRectangle( pPoint);//加入小方块
	}
}
//画圆的动作
void CShpEditorView::DownDrawCircleOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint)
{
	if(m_pNCFeedback==NULL)
	{
		CoCreateInstance(CLSID_NewCircleFeedback,
							NULL,CLSCTX_ALL,
							IID_INewCircleFeedback,
							(void**)&m_pNCFeedback);
		m_pNCFeedback->putref_Display(pScrD);
		m_pNCFeedback->Start(pPoint);
	}
}

void CShpEditorView::DownDrawArcOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint)
{	
	if(m_pCatchPoint!=NULL)//当鼠标捕获到要素的极点时，把此点加入新建要素
	{
		pPoint=m_pCatchPoint;			
	}
	
	if(!m_pNCArc->IsStart())
	{
		m_pNCArc->putref_Symbol(m_pSymbol);
		m_pNCArc->putref_Display(pScrD);
		m_pNCArc->Start(pPoint);
		m_bMouseCross=FALSE;
		m_bMouseCross=FALSE;
	}
	else
	{
		m_pNCArc->AddPoint(pPoint);
	}
	m_pArcCurrentPoint=pPoint;
	IActiveViewPtr	pAct(m_pMap);
	pAct->PartialRefresh(esriViewForeground,0,0);
	
	if(m_pCatchPoint!=NULL)
	{
		m_SnapOperator->LButtonDown(pPoint);
		m_SnapOperator->LButtonDown(pPoint);
		m_pCatchPoint=NULL;		
	}	
}

void CShpEditorView::DownDrawArcOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint,
										  double dRadius,int IsClockwise,int nArcType)
{
	
	if(!m_pNCArc->IsStart())
	{
		m_pNCArc->putref_Symbol(m_pSymbol);
		m_pNCArc->putref_Display(pScrD);
		m_pNCArc->Start(pPoint);
		m_bMouseCross=FALSE;		
	}
	else
	{
		int nState;
		nState=m_pNCArc->GetDrawArcState();
		if(nState==1)
		{
			m_pArcCurrentPoint=pPoint;
			m_pNCArc->AddRadius(pPoint,dRadius,IsClockwise,nArcType);
		}
		else if(nState==2)
			m_pNCArc->AddRadius(NULL,dRadius,IsClockwise,nArcType);
		
	}
	IActiveViewPtr	pAct(m_pMap);
	pAct->PartialRefresh(esriViewForeground,0,0);
}

void CShpEditorView::DownMoveGeometryOperation(IScreenDisplayPtr pScrD,IPointPtr pPoint)//移动要素的动作
{
	HRESULT	hr;
	if(m_pMGFeedback==NULL)
	{
		if(m_bMouseMove!=TRUE)
		{
			hr=m_pMapControl->put_MousePointer(esriPointerCustom);
			hr=m_pMapControl->putref_MouseIcon(m_pMouseMove);
			m_bMouseMove=TRUE;
			m_bMouseNormal=FALSE;
			m_bMouseModify=FALSE;
		}
		CoCreateInstance(CLSID_MoveGeometryFeedback,
						NULL,
						CLSCTX_ALL,
						IID_IMoveGeometryFeedback,
						(void **)&m_pMGFeedback);
		hr=m_pMGFeedback->putref_Display(pScrD);
		if(FAILED(hr)) return;
		hr=m_pMGFeedback->AddGeometry(m_pGeometry);
		if(FAILED(hr)) return;
		hr=m_pMGFeedback->Start(pPoint);
		if(FAILED(hr)) return;
		m_bPressDown=TRUE;
	}
}
///////////////***********鼠标移动过程的操作******************////////////////////////////////////////////////

void	CShpEditorView::MoveDrawLineOperation(IPointPtr	pPoint)		//画线动作
{
	m_pMapControl->put_MousePointer(esriPointerCrosshair);
	m_bMouseNormal=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseMove=FALSE;
	
	if(m_pNLFeedback!=NULL)
	{
		m_pNLFeedback->MoveTo(pPoint);
		//				m_pNLFeedback->Refresh(0);
	}
}

void	CShpEditorView::MoveDrawPolygonOperation(IPointPtr	pPoint)		//画多边形的动作
{
	HRESULT hr;
	hr=m_pMapControl->put_MousePointer(esriPointerCrosshair);
	m_bMouseNormal=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseMove=FALSE;
	
	if(m_pNPFeedback==NULL)	return;

	m_pNPFeedback->MoveTo(pPoint);
}

void	CShpEditorView::MoveDrawCircleOperation(IPointPtr	pPoint)		//画圆的动作
{
		m_pMapControl->put_MousePointer(esriPointerCrosshair);
		m_bMouseNormal=FALSE;
		m_bMouseModify=FALSE;
		m_bMouseMove=FALSE;
		
		if(m_pNCFeedback!=NULL)
		m_pNCFeedback->MoveTo(pPoint);
	
}
void	CShpEditorView::MoveDrawArcOperation(IPointPtr	pPoint)		//画弧的动作
{
	
	if (m_pNCArc!=NULL)
	{
		m_pNCArc->MoveTo(pPoint);
	}
}

void CShpEditorView::MoveMoveGeometryOperation(VARIANT_BOOL vb, long button,IPointPtr	pPoint)	//移动要素的动作
{
	HRESULT hr;
	
	if(vb==VARIANT_TRUE || m_bDrag==TRUE)
	{
		m_OnSelFea=TRUE;
		if((button==1) && (m_bPressDown==TRUE))//当鼠标按下的点不在要素上时不执行拖动操作
		{
			if(m_bMouseMove!=TRUE)
			{
				hr=m_pMapControl->put_MousePointer(esriPointerCustom);
				hr=m_pMapControl->putref_MouseIcon(m_pMouseMove);
				m_bMouseMove=TRUE;
				m_bMouseNormal=FALSE;
				m_bMouseModify=FALSE;
			}

			if(m_pMGFeedback!=NULL)
			{					
				hr=m_pMGFeedback->MoveTo(pPoint);
				if(FAILED(hr))	return;
				m_bDrag=TRUE;
			}
		}
		else
		{
			if(m_bMouseMove!=TRUE)
			{
				hr=m_pMapControl->put_MousePointer(esriPointerCustom);
				hr=m_pMapControl->putref_MouseIcon(m_pMouseMove);
				m_bMouseMove=TRUE;
				m_bMouseNormal=FALSE;
				m_bMouseModify=FALSE;
			}
			if(m_pMGFeedback!=NULL)
			{
				m_pMGFeedback=NULL;
				m_bDrag=FALSE;
				IActiveViewPtr	pActiveView(m_pMap);
				pActiveView->Refresh();
			}
		}
	}
	else
	{
		m_OnSelFea=FALSE;
		if(m_bMouseNormal!=TRUE)
		{
			hr=m_pMapControl->put_MousePointer(esriPointerCustom);
			hr=m_pMapControl->putref_MouseIcon(m_pMouseEditNormal);
			m_bMouseNormal=TRUE;
			m_bMouseMove=FALSE;
			m_bMouseModify=FALSE;
		}
	}
}

//////////////*************鼠标放开时的操作*********************////////////////////////////////////
////////////////////********移动要素的动作**********//////////////////////////

void CShpEditorView::UpMoveGeometryOperation(IPointPtr pToPoint)
{
	HRESULT hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	//****************开始编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	hr=m_pMGFeedback->ClearGeometry();
	if(FAILED(hr))	return;
	hr=pDocument->MoveSelectedFeature(m_pMap,m_pEditLayer,m_pfromPoint,pToPoint);
	if(FAILED(hr))	return;
	hr=pDocument->GetSelectedFeature(m_pMap,&m_lSeleteCount,&m_pGeometry);//是移动后的要素处于选中状态
	if(FAILED(hr))	return;
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return;	
	
	m_pMGFeedback=NULL;
}

void CShpEditorView::UpDrawPolygonOperation(IPointPtr pPoint)
{
}

//选择要素
HRESULT CShpEditorView::_SelectFeature(IEnvelopePtr ipEnvelope,BOOL bIsHit)
{
	if(ipEnvelope==NULL)
	{
		MessageBox("No Envelope","面编辑工具",MB_OK);
		return S_FALSE;
	}

	HRESULT hr;

	ISelectionEnvironmentPtr	ipSelectionEnvironment(CLSID_SelectionEnvironment);
	if(bIsHit)
	{
		hr=m_pMap->SelectByShape(ipEnvelope,ipSelectionEnvironment,VARIANT_TRUE);
		if(FAILED(hr))	return S_FALSE;
	}
	else
	{
		hr=m_pMap->SelectByShape(ipEnvelope,ipSelectionEnvironment,VARIANT_FALSE);
		if(FAILED(hr))	return S_FALSE;
	}
	IActiveViewPtr	ipActiveView(m_pMap);
	ipActiveView->Refresh();
	return S_OK;
}
//////////////**************鼠标双击操作******************//////////////////////////////////////////
//////////////***********画线*****************************/////////////////////////////////////////////////////////

void CShpEditorView::DoubleClickDrawLine(IPointPtr pPoint)
{
	if (m_bEdit==FALSE) return;
	
	HRESULT					hr;
	IActiveViewPtr			pActiveView(m_pMap);
	IGraphicsContainerPtr	pGraCont(pActiveView);
	IPolylinePtr			pPolyLine;
	IGeometryPtr			pGeometry;
	ILineElementPtr			pLineElem(CLSID_LineElement);
	
	if(m_pNLFeedback==NULL)		return;

	hr=m_pNLFeedback->Stop(&pPolyLine);//得到线
	if(FAILED(hr))	return;
	if(pPolyLine!=NULL)
	{
		if(m_pSymbol!=NULL)
		{
			ILineSymbolPtr	pLineSymbol(m_pSymbol);
			pLineElem->put_Symbol(pLineSymbol);
		}
		pGeometry=pPolyLine;
		m_pLine=pPolyLine;
		
		IElementPtr				pElem(pLineElem);
		
		pElem->put_Geometry(pGeometry);
		pGraCont->AddElement(pElem,0);		
	}
//////**********执行切割操作************////////////////////////////////////////////////////////////////////
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
				
//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	hr=pDocument->CutFeature(m_pMap,m_pEditLayer,pPolyLine);
	if(FAILED(hr))	return;

//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	m_pGeometry=NULL;
	if(m_bIsEditLayerLabelVisibel)
		ShowFeatureLabel();
	pActiveView->Refresh();
}

//////////////***********画多边形***********************/////////////////////////////////////////////////////////

void CShpEditorView::DoubleClickDrawPolygon(IPointPtr pPoint)
{
	if(m_pNPFeedback==NULL) return;
	IGeometryPtr	pGeometry(CLSID_Polygon);
	m_pNPFeedback->Stop(&pGeometry);
	
	AddFeatureToLayer(pGeometry);
	FS_Dump();
}
//画圆
void CShpEditorView::DoubleClickDrawCircle(IPointPtr pPoint)
{
	HRESULT	hr;
	if(m_pNCFeedback==NULL)	return;
	ICircularArcPtr	pCircularArc;
	m_pNCFeedback->Stop(&pCircularArc);

	ISegmentCollectionPtr	pSegmCol(CLSID_Polygon);
	ISegmentPtr		pSegm(pCircularArc);

	hr=pSegmCol->AddSegment(pSegm);
	IGeometryPtr pGeometry(pSegmCol);
	AddFeatureToLayer(pGeometry);
	
	m_pNCFeedback=NULL;
//	m_pTracePointCol=NULL;
}

//画弧
void CShpEditorView::DoubleClickDrawArc(IPointPtr pPoint)
{
//	HRESULT	hr;
	if(m_pNCArc==NULL) return;
	IGeometryPtr	pGeometry;
	m_pNCArc->Stop(&pGeometry);
	//if(FAILED(hr))	return;
	AddFeatureToLayer(pGeometry);
	
//	FS_Dump();
}

///////******************选择要素的操作***************//////////////////////

void CShpEditorView::SelectFeatureOperation(double mapX, double mapY)
{
	HRESULT	hr;
	IEnvelopePtr	pEnv;

	hr=m_pMapControl->TrackRectangle(&pEnv);
	double XMin,YMin,XMax,YMax;
	if(S_OK!=pEnv->get_XMin(&XMin)) XMin=0.0;
	if(S_OK!=pEnv->get_YMin(&YMin)) YMin=0.0;
	if(S_OK!=pEnv->get_XMax(&XMax)) XMax=0.0;
	if(S_OK!=pEnv->get_YMax(&YMax)) YMax=0.0;
	BOOL bIsHit=FALSE;
	if(XMin==XMax && YMin==YMin)
	{
		hr=pEnv->PutCoords(mapX,mapY,mapX,mapY);
		if(FAILED(hr)) return;
		bIsHit=TRUE;
	}
	hr=_SelectFeature(pEnv,bIsHit);//选择要素
	if(FAILED(hr)) return;
	
	hr=GetSelectedFeatures();
	if(FAILED(hr)) return;
	
	if(m_lSeleteCount==0)//判断是否选中要素
	{
		m_bSelected=FALSE;
		m_pGeometry=NULL;
		return;
	}
	if(m_bMouseMove!=TRUE)
	{
		hr=m_pMapControl->put_MousePointer(esriPointerCustom);
		hr=m_pMapControl->putref_MouseIcon(m_pMouseMove);
		m_bMouseMove=TRUE;
		m_bMouseNormal=FALSE;
		m_bMouseModify=FALSE;
	}
	
	m_bSelected=TRUE;
}
void CShpEditorView::SelectFeatureOperation(IPointPtr pPoint)
{
	HRESULT	 hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	
	IEnvelopePtr	pEnv;
	
	hr=m_pMapControl->TrackRectangle(&pEnv);
	double XMin,YMin,XMax,YMax;
	if(S_OK!=pEnv->get_XMin(&XMin)) XMin=0.0;
	if(S_OK!=pEnv->get_YMin(&YMin)) YMin=0.0;
	if(S_OK!=pEnv->get_XMax(&XMax)) XMax=0.0;
	if(S_OK!=pEnv->get_YMax(&YMax)) YMax=0.0;
	BOOL bIsHit=FALSE;
	if(XMin==XMax && YMin==YMin)
	{
		double	mapX,mapY;
		
		pPoint->QueryCoords(&mapX,&mapY);
		
		hr=pEnv->PutCoords(mapX,mapY,mapX,mapY);
		if(FAILED(hr)) return;
		bIsHit=TRUE;
	}	
	
	IFeatureCursorPtr	pFeaCur;
	hr=pDocument->QueryFeature(m_pEditLayer,(IGeometryPtr)pEnv,esriSpatialRelIntersects,&pFeaCur);
	
	if(pFeaCur==NULL) return;
	IFeaturePtr	pFeature;
	hr=pFeaCur->NextFeature(&pFeature);
	if(FAILED(hr)) return;
	

	while (pFeature!=NULL)
	{
		hr=AddFeatureToSeletedSet(pFeature);
		hr=pFeaCur->NextFeature(&pFeature);
		if(FAILED(hr)) return;
	}

	if(m_bMouseMove!=TRUE)
	{
		hr=m_pMapControl->put_MousePointer(esriPointerCustom);
		hr=m_pMapControl->putref_MouseIcon(m_pMouseMove);
		m_bMouseMove=TRUE;
		m_bMouseNormal=FALSE;
		m_bMouseModify=FALSE;
	}
	
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
	
}

//////////////**************得到选择的要素******************//////////////////////////////////////////

HRESULT	CShpEditorView::GetSelectedFeatures()
{
	HRESULT	hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	hr=pDocument->GetSelectedFeature(m_pMap,&m_lSeleteCount,&m_pGeometry);
	if(FAILED(hr))	return hr;
	if(m_lSeleteCount==0)
	{
		m_bSelected=FALSE;
		m_pGeometry=NULL;
		return E_FAIL;
	}
	if(m_pGeometry==NULL)
		return E_FAIL;

	m_bSelected=TRUE;
	m_bSelectedMultiPart=IsMultiPart(m_pGeometry);

	return S_OK;
}


void CShpEditorView::OnEditorSelect()
{
	FS_Dump();
	
	m_esriEditType=esriMoveGeometry;

	if(m_bMouseNormal!=TRUE)
	{
		m_pMapControl->put_MousePointer(esriPointerCustom);
		m_pMapControl->putref_MouseIcon(m_pMouseEditNormal);
		m_bMouseNormal=TRUE;
		m_bMouseMove=FALSE;
		m_bMouseModify=FALSE;
	}
}

void CShpEditorView::OnUpdateEditorSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriEditType==esriMoveGeometry);	
	pCmdUI->Enable(m_bEdit);
}

void CShpEditorView::OnEditorSkecth() 
{	
	FS_Dump();
	if(m_pNCArc==NULL)
	{
		m_pNCArc=new CNewCircleArc;
		m_pNCArc->SelectedDrawType(BS_Polygon);
		
		m_esriEditType=esriDrawArc;
		m_BS_DrawType=BS_Polygon;	
		m_bMouseCross=FALSE;
		
		m_pMapControl->put_MousePointer(esriPointerCrosshair);
		m_bMouseNormal=FALSE;
		m_bMouseModify=FALSE;
		m_bMouseMove=FALSE;
		
	}	
}

void CShpEditorView::OnUpdateEditorSkecth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_pNCArc!=NULL);
	pCmdUI->Enable(m_bEdit);
}


void CShpEditorView::OnEditorSkecthPolygon() 
{	
	if(m_pNCArc==NULL)
	{
		FS_Dump();
		m_pNCArc=new CNewCircleArc;
		m_pNCArc->SelectedDrawType(BS_Polygon);
		
		m_pMapControl->put_MousePointer(esriPointerCrosshair);
		m_bMouseNormal=FALSE;
		m_bMouseModify=FALSE;
		m_bMouseMove  =FALSE;
	}

	m_esriEditType=esriDrawArc;
	m_bMouseCross=FALSE;
	m_pNCArc->SelectedDrawType(BS_Polygon);
	m_BS_DrawType=BS_Polygon;
}

void CShpEditorView::OnUpdateEditorSkecthPolygon(CCmdUI* pCmdUI) 
{	
	pCmdUI->SetCheck(m_BS_DrawType==BS_Polygon && m_esriEditType==esriDrawArc);
	pCmdUI->Enable(m_bEdit);	
}

void CShpEditorView::OnEditorSketchArc()
{	
	if(m_pNCArc==NULL)
	{
		FS_Dump();
		m_pNCArc=new CNewCircleArc;
		m_pNCArc->SelectedDrawType(BS_Polygon);
		
		m_pMapControl->put_MousePointer(esriPointerCrosshair);
		m_bMouseNormal=FALSE;
		m_bMouseModify=FALSE;
		m_bMouseMove  =FALSE;		
	}
	
	m_bMouseCross=FALSE;
	
	m_esriEditType=esriDrawArc;
	m_pNCArc->SelectedDrawType(BS_Arc1);
	m_BS_DrawType=BS_Arc1;
}

void CShpEditorView::OnUpdateEditorSketchArc(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_BS_DrawType==BS_Arc1 && m_esriEditType==esriDrawArc);
	pCmdUI->Enable(m_bEdit);	
}

void CShpEditorView::OnEditorSketchCircle() 
{
	FS_Dump();
	
	m_esriEditType=esriDrawCircle;
	m_pMapControl->put_MousePointer(esriPointerCrosshair);
	m_bMouseNormal=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseMove=FALSE;
	
}

void CShpEditorView::OnUpdateEditorSketchCircle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriEditType==esriDrawCircle);
	pCmdUI->Enable(m_bEdit);	
}

void CShpEditorView::OnEditorSketchLine() 
{
	m_esriEditType=esriDrawLine;
	m_pMapControl->put_MousePointer(esriPointerCrosshair);
	m_bMouseNormal=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseMove=FALSE;
	
}

void CShpEditorView::OnUpdateEditorSketchLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriEditType==esriDrawLine);
	pCmdUI->Enable(m_bEdit);
}

void CShpEditorView::OnEditorCopy() 
{
	HRESULT	hr;
	hr=GetSelectedFeatures();
	m_pClipboard=m_pGeometry;
	
	m_bIsCut=TRUE;

}

void CShpEditorView::OnUpdateEditorCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected);	
}
void CShpEditorView::OnEditorCut() 
{
	HRESULT	hr;
	hr=GetSelectedFeatures();

	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return ;
	
	m_pClipboard=m_pGeometry;
	hr=DeleteSelectedFeature();
	if(FAILED(hr))	return;
	
	m_bIsCut=TRUE;
	
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return ;
	
}

void CShpEditorView::OnUpdateEditorCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected);	
}

void CShpEditorView::OnEditorPaste()
{
	HRESULT	 hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();

	IFeaturePtr	pFeature;
	hr=GetFeatureByGeometry(m_pClipboard,&pFeature);
	
	//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return ;

	if(pFeature!=NULL)
	{
		hr=pDocument->NewFeatures(m_pEditLayer,pFeature,m_pClipboard);
		if(FAILED(hr))	return ;
	}
	else
	{
		hr=pDocument->NewFeatures(m_pEditLayer,m_pClipboard);
		if(FAILED(hr))	return ;
	}

	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return ;
	
	if(m_bIsEditLayerLabelVisibel)
		ShowFeatureLabel();

	hr=PitchOnFeature(m_pClipboard);
	
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

void CShpEditorView::OnUpdateEditorPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bIsCut);	
}

void CShpEditorView::OnEditorDelete() 
{
	HRESULT	hr;
	hr=DeleteSelectedFeature();
	if(FAILED(hr))	return;
	if(m_pModifyPolygon!=NULL)
	{
		delete m_pModifyPolygon;
		m_pModifyPolygon=NULL;
	}

}


void CShpEditorView::OnUpdateEditorDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected);	
}

void CShpEditorView::OnEditorMove() 
{
	HRESULT	hr;
	if(m_bSelected==TRUE)	
	{
		IPointPtr	pPoint;

		hr=GetSelectedFeaturePoint(&pPoint);
		if(FAILED(hr)) return;
		if(pPoint==NULL) return;

		CCoordinate	coordDlg;
		double	x,y;

		pPoint->get_X(&x);
		pPoint->get_Y(&y);
		coordDlg.m_X=x;
		coordDlg.m_Y=y;
		UpdateData(FALSE);
 
		if(coordDlg.DoModal()==IDOK)
		{
			CShpEditorDoc *pDocument;
			pDocument=GetDocument();
			
			x+=coordDlg.m_X;
			y+=coordDlg.m_Y;

			IPointPtr	toPoint(CLSID_Point);
			toPoint->PutCoords(x,y);
//****************开始记录编辑**************************
			hr=m_pWorkspaceEdit->StartEditOperation();
			if(FAILED(hr))	return;

			hr=pDocument->MoveSelectedFeature(m_pMap,m_pEditLayer,pPoint,toPoint);
			if(FAILED(hr))	return;

			hr=pDocument->GetSelectedFeature(m_pMap,&m_lSeleteCount,&m_pGeometry);//选中移动后的图形
			if(FAILED(hr))	hr;

//******************停止编辑**************************
			hr=m_pWorkspaceEdit->StopEditOperation();
			if(FAILED(hr))	return;			
		}
		if(m_bIsEditLayerLabelVisibel)
			ShowFeatureLabel();
		
		IActiveViewPtr	pActiveView(m_pMap);
		pActiveView->Refresh();
	}	
}

void CShpEditorView::OnUpdateEditorMove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected);	
}

void CShpEditorView::OnEditorDivide()
{
	HRESULT	hr;
	if(m_lSeleteCount==0)	return;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();

	//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	hr=pDocument->Divide(m_pMap,m_pEditLayer,m_pGeometry);
	if(FAILED(hr))	return;
	
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return;

	m_pGeometry=NULL;
	m_bSelected=FALSE;

	if(m_bIsEditLayerLabelVisibel)
		ShowFeatureLabel();
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

void CShpEditorView::OnUpdateEditorDivide(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected && m_bSelectedMultiPart);	
}

void CShpEditorView::OnEditorMerge()
{
	HRESULT	hr;
	if(m_lSeleteCount<2)	return;

	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	IGeometryPtr	pNewGeometry;
	//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	hr=pDocument->Merge(m_pMap,m_pEditLayer,&pNewGeometry);
	if(FAILED(hr))	return;
	
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	m_pGeometry=NULL;

	if(pNewGeometry!=NULL)
		PitchOnFeature(pNewGeometry);

	if(m_bIsEditLayerLabelVisibel)
		ShowFeatureLabel();
	
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
	
}

void CShpEditorView::OnUpdateEditorMerge(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected && (m_lSeleteCount>=2));		
}

void CShpEditorView::OnEditorUnion() 
{
	HRESULT	hr;
	if(m_lSeleteCount==0)	return;
	
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	
	IGeometryPtr	pNewGeometry;

	//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	hr=pDocument->UnionFeatures(m_pMap,m_pEditLayer,&pNewGeometry);
	if(FAILED(hr))	return;
	
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return;

	if(pNewGeometry!=NULL)
		PitchOnFeature(pNewGeometry);
	
	if(m_bIsEditLayerLabelVisibel)
		ShowFeatureLabel();
	
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

void CShpEditorView::OnUpdateEditorUnion(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable( m_bSelected && (m_lSeleteCount>=2));
}

void CShpEditorView::OnEditorIntersect() 
{
	HRESULT	hr;
	if(m_lSeleteCount==0)	return;

	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	hr=pDocument->IntersectFeature(m_pMap,m_pEditLayer);
	if(FAILED(hr))	return;

//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return;
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();	
}

void CShpEditorView::OnUpdateEditorIntersect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected && (m_lSeleteCount>=2));	
}

void CShpEditorView::OnEditorCutFeature() 
{
	FS_Dump();
	
	m_esriEditType=esriDrawLine;
	m_pMapControl->put_MousePointer(esriPointerCrosshair);
	m_bMouseNormal=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseMove=FALSE;
}

void CShpEditorView::OnUpdateEditorCutFeature(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_esriEditType==esriDrawLine);
	pCmdUI->Enable(m_bEdit);	
}

void CShpEditorView::OnEditorBuffer() 
{
	HRESULT hr;
	if(m_lSeleteCount==0)	return;
//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;
	
	CDistanceDlg distanceDlg;
	if(distanceDlg.DoModal()==IDOK)
	{
		double	dDistance;
		dDistance=distanceDlg.m_dDistance;
		if(dDistance==0.0)	return;
		
		hr=BufferSelectedFeature(dDistance);
		if(FAILED(hr))	return;		
	}	
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return;

	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
	
}

void CShpEditorView::OnUpdateEditorBuffer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected);		
}
////////////////*******剪切图形**************////////////////////////////////////////
void CShpEditorView::OnEditorClip() 
{
	HRESULT	hr;
	if(m_lSeleteCount==0)	return;
	//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;

	if(m_bSelected==TRUE && m_lSeleteCount==1)	
	{
		CClipDlg clipDlg;
		if(clipDlg.DoModal()==IDOK)
		{
			CShpEditorDoc *pDocument;
			pDocument=GetDocument();
			
			int method;
			double distance;
			method=clipDlg.m_method;
			distance=clipDlg.m_Distance;
			hr=pDocument->ClipFeature(m_pMap,m_pEditLayer,m_pGeometry,distance,method);
			if(FAILED(hr))	return;	
		}
	}
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	IActiveViewPtr pAct(m_pMap);
	pAct->Refresh();
	
}

void CShpEditorView::OnUpdateEditorClip(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected );		
}

void CShpEditorView::OnUpdateEditorMenu(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CShpEditorView::OnEditorSnapping()
{	
	if(m_SnapOperator==NULL)
	{
		m_SnapOperator=new CSnapSketch;

		IActiveViewPtr			pActiveView(m_pMap);
		IScreenDisplayPtr		m_pScrD;
		pActiveView->get_ScreenDisplay(&m_pScrD);

		if(m_pScrD==NULL || m_pMapControl==NULL)
			return;		

		m_SnapOperator->PutRef_Display(m_pScrD);
		m_SnapOperator->PutRef_MapControl(m_pMapControl);

		if(m_pEditLayer==NULL && m_pRefLayer==NULL)
			return;
		
		if(m_pEditLayer!=NULL)
			m_SnapOperator->AddLayer(m_pEditLayer);
		if(m_pRefLayer!=NULL)
			m_SnapOperator->AddLayer(m_pRefLayer);
	}
		m_SnapOperator->Start();
		
	m_bSnap=m_SnapOperator->IsCatch();
}

void CShpEditorView::OnUpdateEditorSnapping(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit);
	pCmdUI->SetCheck(m_bSnap==TRUE);
}

HRESULT	CShpEditorView::DeleteSelectedFeature()
{
	HRESULT	hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();

	if(m_lSeleteCount==0)	return E_FAIL;

	hr=m_pWorkspaceEdit->StartEditOperation();//开始编辑
	if(FAILED(hr))	return hr;

	hr=pDocument->DeleFeature(m_pMap,m_pEditLayer);
	if(FAILED(hr))	return hr;

	m_pGeometry=NULL;


	hr=m_pWorkspaceEdit->StopEditOperation();//开始编辑
	if(FAILED(hr))	return hr;
	m_bSelected=FALSE;

	if(m_bIsEditLayerLabelVisibel)
		ShowFeatureLabel();

	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
	
	return S_OK;
}


void CShpEditorView::AddFeatureToLayer(IGeometryPtr	pGeometry)
{
	if(pGeometry==NULL)	return ;
	HRESULT	 hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return ;

	hr=pDocument->NewFeatures(m_pEditLayer,pGeometry);
	if(FAILED(hr))	return ;
	
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return ;

	hr=PitchOnFeature(pGeometry);

	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();

//	CFS_FeatureProperty Property;
//	Property.DoModal();
}


HRESULT	CShpEditorView::BufferSelectedFeature(double distance)
{
	HRESULT	 hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();

	hr=pDocument->BufferFeature(m_pMap,m_pEditLayer,distance);
	if(FAILED(hr)) return hr;

	hr=DeleteSelectedFeature();

	return S_OK;
	
}
////////*********保存当前层**************///////////////////////

HRESULT CShpEditorView::SaveCurrentFile()
{
	//关闭编辑工作区
	
	VARIANT_BOOL pIsBeingEdited;
	m_pWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if (pIsBeingEdited==VARIANT_TRUE)
	{
        VARIANT_BOOL bHasEdits ;
        VARIANT_BOOL bSave;
		bSave=VARIANT_FALSE;
		
        m_pWorkspaceEdit->HasEdits(&bHasEdits);
		if(bHasEdits==VARIANT_TRUE)
		{
			int nState;
			nState=MessageBox (_T ("是否保存当前文件?"),_T ("面编辑工具"), MB_YESNOCANCEL|MB_ICONQUESTION);
			if(nState==IDYES)
				bSave=VARIANT_TRUE;
		}
        m_pWorkspaceEdit->StopEditing(bSave);//如果bSave为True保存，否则放弃
		m_bEdit=FALSE;
	}
//再次打开编辑工作区
	HRESULT	hr;
	hr=m_pWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if(FAILED(hr))	return hr;
	
	if (pIsBeingEdited==VARIANT_FALSE)
	{
        hr=m_pWorkspaceEdit->StartEditing(VARIANT_TRUE);
		if(hr==-2147217069)
		{
			MessageBox("此文件正被另一程序使用!","面编辑工具",MB_OK|MB_ICONWARNING);
			return E_FAIL;
		}
		if(FAILED(hr))	return hr;
        hr=m_pWorkspaceEdit->EnableUndoRedo();
		if(FAILED(hr))	return hr;
		m_bEdit=TRUE;
//		m_esriEditType=esriMoveGeometry;
	}
	return S_OK;
}

HRESULT CShpEditorView::SaveAsCurrentFile()
{
	HRESULT	hr;
	VARIANT_BOOL pIsBeingEdited;
	m_pTempWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if (pIsBeingEdited==VARIANT_TRUE)
	{
        VARIANT_BOOL bHasEdits;
		
        m_pTempWorkspaceEdit->HasEdits(&bHasEdits);
		if(bHasEdits==VARIANT_TRUE)
			m_pTempWorkspaceEdit->StopEditing(VARIANT_TRUE);//如果bSave为True保存，否则放弃
	}
	if(m_bEdit)
	{
		VARIANT_BOOL IsBeingEdited;
		hr=m_pWorkspaceEdit->IsBeingEdited(&IsBeingEdited);
		if(FAILED(hr))	return hr;
		if (IsBeingEdited==VARIANT_FALSE)
		{
			hr=m_pWorkspaceEdit->StartEditing(VARIANT_TRUE);
			if(FAILED(hr))	return hr;
			hr=m_pWorkspaceEdit->EnableUndoRedo();
			if(FAILED(hr))	return hr;
		}
	}
	return S_OK;
}

////////*********改变层的状态**************///////////////////////
void CShpEditorView::OnChangeLayerState(HTREEITEM hti)
{
	HRESULT	 hr;
	CMainFrame *pMainFrm=(CMainFrame*) AfxGetMainWnd();
	CTreeLayer *LayerTree=& pMainFrm->m_wndLayerManageBar.m_wndTree;
	CString sLayerName=LayerTree->GetItemText(hti);
	HTREEITEM	RootItem=LayerTree->GetParentItem(hti);
	
	CString		strRootName=LayerTree->GetItemText(RootItem);

	ILayerPtr		pLayer;
	
	IActiveViewPtr	pActiveView(m_pMap);
	hr=GetLayerByName(sLayerName,&pLayer);
	if(FAILED(hr))	return;

	
		if(strRootName=="参考层")
		{
			m_pRefLayer=pLayer;
			ShowLayer(pLayer,FALSE);
		}
		else
		{
			m_pEditLayer=pLayer;
			ShowLayer(pLayer,TRUE);
		}
	pActiveView->Refresh();
}

/////////////*******通过层名字得到层*********//////////////////////////////////
HRESULT CShpEditorView::GetLayerByName(CString sLayerName,ILayer ** pLayer)
{
	ILayerPtr pTempLayer;
	IFeatureLayerPtr	pFeaLayer;
	IFeatureClassPtr	pFeaClass;
	long count;
	HRESULT		hr;
	BSTR	bName;
	m_pMap->get_LayerCount(&count);
	if(count<0)	return E_FAIL;
	for(int i=0; i< count; i++)
	{
		hr=m_pMap->get_Layer(i,&pTempLayer);
		pFeaLayer=pTempLayer;

		hr=pFeaLayer->get_FeatureClass(&pFeaClass);
		pFeaClass->get_AliasName(&bName);
		
		if((LPWSTR)bName==sLayerName)
			break;
	}
	*pLayer=pTempLayer;
	if(*pLayer)
	{
		(*pLayer)->AddRef();
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CShpEditorView::IsHasLayer(CString sLayerName)
{
	ILayerPtr pTempLayer;
	IFeatureLayerPtr	pFeaLayer;
	IFeatureClassPtr	pFeaClass;
	long count;
	HRESULT		hr;
	BSTR	bName;
	m_pMap->get_LayerCount(&count);
	if(count<0)	return E_FAIL;
	for(int i=0; i< count; i++)
	{
		hr=m_pMap->get_Layer(i,&pTempLayer);
		pFeaLayer=pTempLayer;
		
		hr=pFeaLayer->get_FeatureClass(&pFeaClass);
		pFeaClass->get_AliasName(&bName);
		
		if((LPWSTR)bName==sLayerName)
			return S_OK;
	}
	return E_FAIL;
}
/////////////////**********把新加入的层的名字加到树控键中*************/////////////////////////////////////////////////////////

HRESULT	CShpEditorView::AddLayerNameToTree(CString strName)
{
	CMainFrame *pMainFrm=(CMainFrame*) AfxGetMainWnd();
	CTreeLayer *LayerTree=& pMainFrm->m_wndLayerManageBar.m_wndTree;
	CString	strLayerType;
	
	LayerTree->AddLayerItem(m_nLayerType,TRUE,strName);
	
	return S_OK;
}

void CShpEditorView::DeleteLayer(CString strLayerName)
{
	ILayerPtr	pLayer;
	IActiveViewPtr	pAct(m_pMap);
	GetLayerByName(strLayerName,&pLayer);

	BOOL	bIsEditLayer=DeleteLayerOfArrar(pLayer);
	if(bIsEditLayer==TRUE)
	{
		long count;
		m_pEditLayerArray->get_Count(&count);
		if(count==0)
		{
			StopEditor();
			m_pWorkspaceEdit=NULL;
		}
	}
	m_pMap->DeleteLayer(pLayer);
	
	IGraphicsContainerPtr pGrapcont(pAct);
	pGrapcont->DeleteAllElements();
	pAct->Refresh();
}

void CShpEditorView::OnLayerColor() 
{
	SetFillSymbol();	
}
void CShpEditorView::SetLayerSymbol(CString strLayerName)
{
	SetFillSymbol();//打开填充符号对话框

	ILayerPtr	pLayer;
	IActiveViewPtr	pAct(m_pMap);
	GetLayerByName(strLayerName,&pLayer);

	ISimpleRendererPtr	pSimpleRenderer(CLSID_SimpleRenderer);
	IFeatureRendererPtr	pFeaRenderer;

	pSimpleRenderer->putref_Symbol(m_pSymbol);
	pFeaRenderer=pSimpleRenderer;

	IGeoFeatureLayerPtr	pFeaLayer;
	pFeaLayer=pLayer;
	
	pFeaLayer->putref_Renderer(pFeaRenderer);
	pAct->Refresh();
}

void CShpEditorView::SetFillSymbol()
{
	ISymbolSelectorPtr		pSymbolSel(CLSID_SymbolSelector);
	ISimpleFillSymbolPtr	pSFSymbol(CLSID_SimpleFillSymbol);
	ISymbolPtr		pSymbol;
	VARIANT_BOOL	bOK;
	HRESULT			hr;
	if(pSymbolSel==NULL)
		return;
	pSymbol=pSFSymbol;
	pSymbolSel->AddSymbol(pSymbol,&bOK);
	hr=pSymbolSel->SelectSymbol(0,&bOK);
	if(bOK)
	{
		pSymbolSel->GetSymbolAt(0,&m_pSymbol);
	}
}


void CShpEditorView::OnOnAfterDrawMapcontrol(const VARIANT FAR& display, long viewDrawPhase) 
{
	switch(m_esriEditType) {
	case esriDrawPolygon:
		if(m_pNPFeedback!=NULL)
			m_pNPFeedback->DrawPolygon();
		break;
	case esriTools:
		if(m_pNCArc!=NULL)
			m_pNCArc->DrawPolygon();
		break;
	case esriDrawArc:
		if(m_pNCArc!=NULL)
			m_pNCArc->DrawPolygon();
		break;
	case esriMoveGeometry:
		if(m_pModifyPolygon!=NULL)
			m_pModifyPolygon->DrawPolygon();
		break;
	}
}

///////////////*********退出程序时提示保存*************////////////////////////////

BOOL CShpEditorView::ExitApp()
{
	ClearMemory();//内存清零
	VARIANT_BOOL pIsBeingEdited;
	if(m_pWorkspaceEdit==NULL) return TRUE;
	m_pWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if (pIsBeingEdited==VARIANT_TRUE)
	{
        VARIANT_BOOL bHasEdits ;
        VARIANT_BOOL bSave;
		bSave=VARIANT_FALSE;
		
        m_pWorkspaceEdit->HasEdits(&bHasEdits);
		if(bHasEdits==VARIANT_TRUE)
		{
			int nState;
			nState=MessageBox (_T ("是否保存当前文件?"),_T ("面编辑工具"), MB_YESNOCANCEL|MB_ICONQUESTION);
			if(nState==IDYES)
				bSave=VARIANT_TRUE;
			if(nState==IDCANCEL )
				return FALSE;
		}
        m_pWorkspaceEdit->StopEditing(bSave);//如果bSave为True保存，否则放弃
		m_bEdit=FALSE;
	}
	return TRUE;
}



void	CShpEditorView::ShowLayer(IFeatureLayerPtr	pShowLayer,BOOL	bLayerType)
{
	ASSERT(pShowLayer!=NULL);
	IArrayPtr	pArray(CLSID_Array);
	
	VARIANT_BOOL	bVisible;
	pShowLayer->get_Visible(&bVisible);
	bVisible=!bVisible;

	pShowLayer->put_Visible(bVisible);
	if(m_SnapOperator!=NULL)
	{
		if(bVisible==1)
		{
			if(bLayerType==TRUE)
			{
				if(m_pEditLayer!=NULL)
					m_SnapOperator->DeleteLayer(m_pEditLayer);
			}
			else
			{
				if(m_pRefLayer!=NULL)
					m_SnapOperator->DeleteLayer(m_pRefLayer);
			}

			m_SnapOperator->AddLayer(pShowLayer);
		}
		else
		{
			m_SnapOperator->DeleteLayer(pShowLayer);
		}
	}

	if(bLayerType==TRUE)
	{
		if(bVisible==1)
			m_pEditLayer=pShowLayer;//将当前显示的层定为编辑层
		else
		{
			m_pEditLayer=NULL;
//			StopEditor();
			//退出编辑状态
		}
		
		pArray=m_pEditLayerArray;
	}
	else
	{
		if(bVisible==1)
			m_pRefLayer=pShowLayer;//将当前显示的层定为参考层
		else
			m_pRefLayer=NULL;
		pArray=m_pRefLayerArray;
	}

	long	layerCount;
	pArray->get_Count(&layerCount);

	for(long l=0;l<layerCount;l++)
	{
		IFeatureLayerPtr	pFeaLayer;
		pArray->get_Element(l,(LPUNKNOWN*) &pFeaLayer);
		if(pFeaLayer!=pShowLayer)
			pFeaLayer->put_Visible(VARIANT_FALSE);
	}
//	pArray->RemoveAll();
}

TC_HTREEITEM CShpEditorView::GetCurrentItemState(HTREEITEM hti)
{
	CMainFrame *pMainFrm=(CMainFrame*) AfxGetMainWnd();
	CTreeLayer *LayerTree=& pMainFrm->m_wndLayerManageBar.m_wndTree;
	CString	strLayerType;
	CString	strLayerName;
	strLayerName=LayerTree->GetItemText(hti);

	TC_HTREEITEM	TC_hti;
	TC_hti.hti=hti;
	ILayerPtr	pLayer;

	GetLayerByName(strLayerName,&pLayer);
	VARIANT_BOOL	bVisible;
	pLayer->get_Visible(&bVisible);

	if(bVisible==VARIANT_FALSE)
		TC_hti.bIsVisible=FALSE;
	else
		TC_hti.bIsVisible=TRUE;

//	if(strLayerName=="参考层")
//		TC_hti.strRootName="参考层";
//	else
//		TC_hti.strRootName="编辑层";
	return TC_hti;
}

void CShpEditorView::CopyFeatureClass(IFeatureClassPtr ipDataFC,IFeatureClassPtr pNewFeaClass)
{
	long totalFeatureCount;
	ipDataFC->FeatureCount(0, &totalFeatureCount);
	if (totalFeatureCount == 0)
	{
		cerr << "No features found in shapefile. Exiting." << endl;
		return ;
	}
		
//	HRESULT	hr;
	CShpEditorDoc	*pDocument=GetDocument();
	
	IFeatureCursorPtr ipInsertFeatureCursor;
	pNewFeaClass->Insert(VARIANT_TRUE, &ipInsertFeatureCursor);
	IFeatureBufferPtr ipInsertFeatureBuffer;
	pNewFeaClass->CreateFeatureBuffer(&ipInsertFeatureBuffer);
	
	IFeatureCursorPtr ipFeatureCursor;
	ipDataFC->Search(0, VARIANT_TRUE, &ipFeatureCursor);

	IFeaturePtr ipFeature;
	ipFeatureCursor->NextFeature(&ipFeature);
	
	int featureCount = 0;
	int emptyFeatureCount = 0;
	while(ipFeature != 0)
	{
		// Update progress information
		featureCount += 1;
		cerr << featureCount << " of " << totalFeatureCount 
			<< " Features processed." << endl;
		
		// If the feature has an invalid shape, create a new empty one
		IGeometryPtr ipGeom;
		ipFeature->get_Shape(&ipGeom);
		if (ipGeom == 0)
		{
			CreateNewGeom(pNewFeaClass, ipGeom);
			ipFeature->putref_Shape(ipGeom);
		}
		
		// Simplify each feature and insert into new feature class
		((ITopologicalOperator2Ptr) ipGeom)->put_IsKnownSimple(VARIANT_FALSE);
		((ITopologicalOperator2Ptr) ipGeom)->Simplify();
		pDocument->DocInsertFeature(ipInsertFeatureCursor, ipInsertFeatureBuffer,
			ipFeature, (IGeometry2Ptr) ipGeom);
		
		// Count the number of empty features
		VARIANT_BOOL vbIsEmpty;
		((IGeometry2Ptr) ipGeom)->get_IsEmpty(&vbIsEmpty);
		if (vbIsEmpty)
			emptyFeatureCount += 1;
		
		// Get the next feature
		ipFeatureCursor->NextFeature(&ipFeature);
	}
	
	ipInsertFeatureBuffer = 0;
	ipInsertFeatureCursor = 0;
	
	cerr << endl << "Operation completed successfully." << endl;

}

HRESULT CShpEditorView::CreateNewGeom(IFeatureClass* pOutFC, IGeometry* pNewGeom)
{
	esriGeometryType esriGeom;
	pOutFC->get_ShapeType(&esriGeom);
	
	switch(esriGeom)
	{
	case esriGeometryPoint:
		{  
			IPointPtr ipPoint(CLSID_Point);
			pNewGeom = ipPoint;
		} 
		break;
	case esriGeometryMultipoint:
		{
			IMultipointPtr ipMultipoint(CLSID_Multipoint);
			pNewGeom = ipMultipoint;
		}
		break;
	case esriGeometryPolyline:
		{
			IPolylinePtr ipPolyline(CLSID_Polyline);
			pNewGeom = ipPolyline;
		}
		break;
	case esriGeometryPolygon:
		{
			IPolygonPtr ipPolygon(CLSID_Polygon);
			pNewGeom = ipPolygon;
		}
		break;
	default:
		cerr << "shape type not supported" << endl;
		return E_FAIL;
		break;
	}
	return S_OK;
}

void CShpEditorView::OnDrawCoordinate() 
{
	IActiveViewPtr	pAct(m_pMap);
	IScreenDisplayPtr	pScrD;
	pAct->get_ScreenDisplay(&pScrD);

	CCoordinate		coordDlg;
	double	x,y;
	m_pfromPoint->get_X(&x);
	m_pfromPoint->get_Y(&y);
	coordDlg.m_X=x;
	coordDlg.m_Y=y;
//	UpdateData(FALSE);
	if(coordDlg.DoModal()==IDOK)
	{
		x=coordDlg.m_X;
		y=coordDlg.m_Y;

		IPointPtr	pPoint(CLSID_Point);
		
		pPoint->PutCoords(x,y);

		
		switch(m_esriEditType) {
		case esriDrawArc:
			DownDrawArcOperation(pScrD,pPoint);		
			break;
		case esriDrawPolygon:
			DownDrawPolygonOperation(pScrD,pPoint);		
			break;
		}
	}

	m_pNCArc->bIsHitMenu=TRUE;
	m_bIsHitSketchMenu=TRUE;
	pAct->PartialRefresh(esriViewForeground,0,0);
}


void CShpEditorView::OnDrawRadius() 
{
	m_pNCArc->SelectedDrawType(BS_Arc1);
	
	IActiveViewPtr	pAct(m_pMap);
	IScreenDisplayPtr	pScrD;
	pAct->get_ScreenDisplay(&pScrD);
	
	CDrawArcDlg		DrawArcDlg;
	
	double	preX,preY,x,y;

	int nState=m_pNCArc->GetDrawArcState();

	if(nState==1)
	{
		m_pArcCurrentPoint->get_X(&preX);
		m_pArcCurrentPoint->get_Y(&preY);
		DrawArcDlg.m_StarX=preX;
		DrawArcDlg.m_StarY=preY;
		
		m_pfromPoint->get_X(&x);
		m_pfromPoint->get_Y(&y);
		
		DrawArcDlg.m_EndX=x;
		DrawArcDlg.m_EndY=y;
	}
	else
	{
		long nCount;
		m_pNCArc->GetPolygonPointCount(&nCount);
		
		IPointPtr	pFrom,pEnd;
		m_pNCArc->GetPolygonPoint(nCount-2,&pFrom);
		m_pNCArc->GetPolygonPoint(nCount-1,&pEnd);
		
		pFrom->get_X(&preX);
		pFrom->get_Y(&preY);
		DrawArcDlg.m_StarX=preX;
		DrawArcDlg.m_StarY=preY;
		
		pEnd->get_X(&x);
		pEnd->get_Y(&y);
		
		DrawArcDlg.m_EndX=x;
		DrawArcDlg.m_EndY=y;
	}



	UpdateData(FALSE);
	
	if(DrawArcDlg.DoModal()==IDOK)
	{
		double	dRadius;
		int		IsCockWise,nArcType;

		x=DrawArcDlg.m_EndX;
		y=DrawArcDlg.m_EndY;
		dRadius=DrawArcDlg.m_Radius;
		IsCockWise = DrawArcDlg.m_nClockwise;
		nArcType   = DrawArcDlg.m_nArcType;
		
		IPointPtr	pPoint(CLSID_Point);
		
		pPoint->PutCoords(x,y);
		DownDrawArcOperation(pScrD,pPoint,dRadius,IsCockWise,nArcType);
		
	}
	if(m_BS_DrawType==BS_Polygon)
		m_pNCArc->SelectedDrawType(BS_Polygon);

	m_pNCArc->bIsHitMenu=TRUE;
	m_bIsHitSketchMenu=TRUE;
	pAct->PartialRefresh(esriViewForeground,0,0);
	
}


void CShpEditorView::OnDrawOffset() 
{
	IActiveViewPtr	pAct(m_pMap);
	IScreenDisplayPtr	pScrD;
	pAct->get_ScreenDisplay(&pScrD);
	
	CCoordinate		coordDlg;
	double	x,y;
	m_pArcCurrentPoint->get_X(&x);
	m_pArcCurrentPoint->get_Y(&y);

	double	endx,endy;
	m_pfromPoint->get_X(&endx);
	m_pfromPoint->get_Y(&endy);
	
	coordDlg.m_X = endx-x;
	coordDlg.m_Y = endy-y;
	
	UpdateData(FALSE);
	if(coordDlg.DoModal()==IDOK)
	{
		x+=coordDlg.m_X;
		y+=coordDlg.m_Y;

		IPointPtr	pPoint(CLSID_Point);

		pPoint->PutCoords(x,y);
		switch(m_esriEditType) {
		case esriDrawArc:
			DownDrawArcOperation(pScrD,pPoint);		
			break;
		case esriDrawPolygon:
			DownDrawPolygonOperation(pScrD,pPoint);		
			break;
		}
	}
	m_pNCArc->bIsHitMenu=TRUE;
	m_bIsHitSketchMenu=TRUE;
	pAct->PartialRefresh(esriViewForeground,0,0);
	
}

void CShpEditorView::OnDrawFinishAndRadius() 
{
	switch(m_esriEditType) {
	case esriDrawArc:
		DoubleClickDrawArc(0);
		break;
	case esriDrawPolygon:
		DoubleClickDrawPolygon(0);
		break;
	}
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();	
}

void CShpEditorView::OnDrawDeleteSketch() 
{
	IActiveViewPtr	pActiveView(m_pMap);
	pActiveView->Refresh();
	switch(m_esriEditType) {
	case esriDrawArc:
		{
			m_pNCArc->ClearGarbage();
		}
		break;
	case esriDrawPolygon:
		{
			delete m_pNPFeedback;
			m_pNPFeedback=NULL;
		}
		break;
	}	
}

void CShpEditorView::OnDrawConcelMenu() 
{	
}

void CShpEditorView::SetMouse()
{
	BOOL	hr;
	
	hr=m_pMouseCrossCircle.LoadResource(IDR_USER_CROSS,"CUR");
	hr=m_pMouseEditNormal.LoadResource(IDR_USER_NORMAL,"CUR");	
	hr=m_pMouseMove.LoadResource(IDR_USER_MOVE1,"CUR");
	hr=m_pMouseModify.LoadResource(IDR_USER_MODIFY,"CUR");	
}

void CShpEditorView::ShowCoordinate(double X,double Y)
{
	CMainFrame* pWnd=(CMainFrame*) AfxGetMainWnd();
	pWnd->ShowCoordinate(X,Y);
}

void CShpEditorView::ClearMemory()
{
	if(m_SnapOperator!=NULL)
	{
		delete m_SnapOperator;
		m_SnapOperator=NULL;
	}
	if(m_pNCArc!=NULL)
	{
		delete m_pNCArc;
		m_pNCArc=NULL;
	}
	if(m_pNPFeedback!=NULL)
	{
		delete m_pNPFeedback;
		m_pNPFeedback=NULL;
	}
	m_bMouseMove=FALSE;
	m_bMouseModify=FALSE;
	m_bMouseNormal=FALSE;
	m_bMouseCross=FALSE;
	
	m_nIndex=-1;
	m_nEditIndex=-1;
	m_nRefIndex=-1;
	m_bSelectedMultiPart=FALSE;
	
	m_bIsHitSketchMenu=FALSE;
	m_Property = NULL;
	m_bIsEditLayerLabelVisibel	= FALSE;
	m_bIsRefLayerLabelVisibel	= FALSE;
	
	m_pNCArc=NULL;
	m_SnapOperator=NULL;
	m_pModifyPolygon=NULL;
	
	m_bIsPanFinish=FALSE;
	
	
	m_bSnapEditLayer=FALSE;
	m_bSnap=FALSE;
	m_bEdit=FALSE;
	m_bIsHasEditLayer=FALSE;
	m_bSelected=FALSE;
	m_bDrag=FALSE;
	m_OnSelFea=FALSE;
	m_lSeleteCount=0;
	m_bIsCut=FALSE;
		
	m_bIsCatch=FALSE;
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

BOOL CShpEditorView::DeleteLayerOfArrar(ILayerPtr pLayer)
{
	long	Count=0;
	m_pEditLayerArray->get_Count(&Count);
	for(long l=0;l<Count;l++)
	{
		ILayerPtr pEditLayer;
		m_pEditLayerArray->get_Element(l,(IUnknown**)&pEditLayer);
		if(pEditLayer==pLayer)
		{
			if(pLayer==m_pEditLayer)
			{
				if(m_SnapOperator!=NULL)
					m_SnapOperator->DeleteLayer(m_pEditLayer);					
			}
			m_pEditLayerArray->Remove(l);
			return TRUE;
		}
	}

	m_pRefLayerArray->get_Count(&Count);
	for( l=0;l<Count;l++)
	{
		ILayerPtr pEditLayer;
		m_pRefLayerArray->get_Element(l,(IUnknown**)&pEditLayer);
		if(pEditLayer==pLayer)
		{
			if(pLayer==m_pRefLayer)
			{
				if(m_SnapOperator!=NULL)
					m_SnapOperator->DeleteLayer(m_pRefLayer);					
			}
			m_pRefLayerArray->Remove(l);
			return FALSE;
		}
	}
	return FALSE;
}

void CShpEditorView::StopEditor()
{
	ClearMemory();//内存清零
	VARIANT_BOOL pIsBeingEdited;
	m_pWorkspaceEdit->IsBeingEdited(&pIsBeingEdited);
	if (pIsBeingEdited==VARIANT_TRUE)
	{
        VARIANT_BOOL bHasEdits ;
        VARIANT_BOOL bSave;
		bSave=VARIANT_FALSE;
		
        m_pWorkspaceEdit->HasEdits(&bHasEdits);
		if(bHasEdits==VARIANT_TRUE)
		{
			int nState;
			nState=MessageBox (_T ("是否保存当前文件?"),_T ("面编辑工具"), MB_YESNOCANCEL|MB_ICONQUESTION);
			if(nState==IDYES)
				bSave=VARIANT_TRUE;
		}
        m_pWorkspaceEdit->StopEditing(bSave);//如果bSave为True保存，否则放弃
		m_bEdit=FALSE;
		m_esriEditType=	esriNothing;
	}
}



void CShpEditorView::OnOnKeyDownMapcontrol(long keyCode, long shift) 
{

}

void CShpEditorView::OnOnKeyUpMapcontrol(long keyCode, long shift) 
{
	switch(keyCode) {
	case VK_ESCAPE:
		ESC_Command();
		break;
	}	
}

void CShpEditorView::ESC_Command()
{
	IActiveViewPtr		pActiveView(m_pMap);
	switch(m_esriEditType) {
	case esriDrawPolygon:
		{
			if(m_pNPFeedback==NULL)	return;
			m_pNPFeedback->DeleteCurrentPoint();
		}
		break;
	case esriDrawArc:
			if(m_pNCArc==NULL)	return;
			m_pNCArc->DeleteCurrentPoint();
		break;
	case esriMoveGeometry:
		if(m_pModifyPolygon==NULL)	return;
		m_pModifyPolygon->Back();
		break;
	case esriDrawLine:
		if(m_pNLFeedback!=NULL)
			m_pNLFeedback=NULL;
	}
	pActiveView->PartialRefresh(esriViewForeground,0,0);
}

HRESULT CShpEditorView::GetSelectedFeaturePoint(IPoint **pPoint)
{
	if(m_pGeometry==NULL)	return E_FAIL;
	
	HRESULT	hr;
	IPointCollectionPtr		ptCollection;
	ptCollection=m_pGeometry;
	hr=ptCollection->get_Point(0,pPoint);
	if(*pPoint)
	{
		(*pPoint)->AddRef();
		return S_OK;
	}
	else
		return E_FAIL;
}

void CShpEditorView::FS_Dump()
{
	if(m_pNCArc!=NULL)
	{
		delete m_pNCArc;
		m_pNCArc=NULL;
	}
	if(m_pNPFeedback!=NULL)
	{
		delete m_pNPFeedback;
		m_pNPFeedback=NULL;
	}
	if(m_pNLFeedback!=NULL)
		m_pNLFeedback=NULL;

	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

void CShpEditorView::FinishModify()
{
	IGeometryPtr	pGeometry;
	m_pModifyPolygon->Stop(&pGeometry);
	if(pGeometry==NULL)	return;
	
	delete m_pModifyPolygon;
	m_pModifyPolygon=NULL;
	
	HRESULT	 hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	
	if(m_lSeleteCount==0)	return ;
	IFeaturePtr	pFeature;
//****************开始记录编辑**************************
	hr=m_pWorkspaceEdit->StartEditOperation();
	if(FAILED(hr))	return;
	
	hr=GetFeatureByGeometry(m_pGeometry,&pFeature);

	hr=pDocument->DeleFeature(m_pMap,m_pEditLayer);
	if(FAILED(hr))	return ;
	
	hr=pDocument->NewFeatures(m_pEditLayer,pFeature,pGeometry);
	if(FAILED(hr))	return ;
	
//******************停止编辑**************************
	hr=m_pWorkspaceEdit->StopEditOperation();
	if(FAILED(hr))	return ;

	hr=PitchOnFeature(pGeometry);

	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();}

void CShpEditorView::OnEditorModifyInsertVertex() 
{

	if(m_pModifyPolygon!=NULL)
		m_pModifyPolygon->OnInsertVertex();
	IActiveViewPtr	pAct(m_pMap);
	pAct->PartialRefresh(esriViewForeground,0,0);
	
}

void CShpEditorView::OnUpdateEditorModifyInsertVertex(CCmdUI* pCmdUI) 
{
	if(m_pModifyPolygon!=NULL)
	{
		int	nCatchType;
		nCatchType=m_pModifyPolygon->GetCatchType();
		if(nCatchType==2)
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CShpEditorView::OnEditorModifyDeleteVertex() 
{
	if(m_pModifyPolygon!=NULL)
		m_pModifyPolygon->OnDeleteVertex();
	IActiveViewPtr	pAct(m_pMap);
	pAct->PartialRefresh(esriViewForeground,0,0);	
}

void CShpEditorView::OnUpdateEditorModifyDeleteVertex(CCmdUI* pCmdUI) 
{
	if(m_pModifyPolygon!=NULL)
	{
		int	nCatchType;
		nCatchType=m_pModifyPolygon->GetCatchType();
		if(nCatchType==1)
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CShpEditorView::OnEditorModifyBack() 
{
	if(m_pModifyPolygon!=NULL)
		m_pModifyPolygon->OnBack();
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
	
}

void CShpEditorView::OnUpdateEditorModifyBack(CCmdUI* pCmdUI) 
{
	if(m_pModifyPolygon!=NULL)
	{
		BOOL	bIsModify=FALSE;
		bIsModify=m_pModifyPolygon->IsModify();
		pCmdUI->Enable(bIsModify==TRUE);
	}	
}

void CShpEditorView::OnEditorModifyCancel() 
{
	if(m_pModifyPolygon!=NULL)
	{
		m_pModifyPolygon=NULL;
	}
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

void CShpEditorView::OnUpdateEditorModifyCancel(CCmdUI* pCmdUI) 
{
	if(m_pModifyPolygon!=NULL)
	{
		BOOL	bIsModify=FALSE;
		bIsModify=m_pModifyPolygon->IsModify();
		pCmdUI->Enable(bIsModify==TRUE);
	}	
}

void CShpEditorView::OnEditorProperty() 
{
	m_Property =new CFS_FeatureProperty;
	if(m_pWorkspaceEdit!=NULL && m_bEdit)
		m_pWorkspaceEdit->StartEditOperation();

	m_Property->Create(IDD_FEATURE_PROPERTY);
	m_Property->ShowWindow(SW_SHOW);
		


	if(m_pWorkspaceEdit!=NULL && m_bEdit)
		m_pWorkspaceEdit->StopEditOperation();
}

void CShpEditorView::OnUpdateEditorProperty(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEdit && m_bSelected);
}

void CShpEditorView::OnLayerProperty() 
{
	CFS_FieldsDlg	LayerProperty;

	LayerProperty.DoModal();

	IActiveViewPtr	pAtc(m_pMap);
	pAtc->Refresh();

}

void CShpEditorView::OnUpdateLayerProperty(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pEditLayer!=NULL && m_bEdit==FALSE);	
}

BOOL CShpEditorView::GetEditLayer(IFeatureLayer ** pEditLayer)
{
	(*pEditLayer)=m_pEditLayer;
	if((*pEditLayer))
	{
		(*pEditLayer)->AddRef();
		return TRUE;
	}
	return FALSE;
}

HRESULT CShpEditorView::GetSelectedFeatures(IFeature **pSelectedFeature,BOOL &bIsReference)
{
	HRESULT	hr;
	CShpEditorDoc *pDocument;
	pDocument=GetDocument();
	
	long lSelectedCount;
	hr=m_pMap->get_SelectionCount(&lSelectedCount);//选中要素的个数
	if(FAILED(hr))	return hr;
	if(lSelectedCount==0)	return E_FAIL;
	IEnumFeaturePtr		ipEnumFeature;
	ISelectionPtr		ipSelection;
	hr=m_pMap->get_FeatureSelection(&ipSelection);
	if(FAILED(hr))	return hr;
	ipEnumFeature=ipSelection;

	ipEnumFeature->Next(pSelectedFeature);

	bIsReference=pDocument->IsReferenceLayer(m_pEditLayer,*pSelectedFeature);

	if(*pSelectedFeature)
	{
		(*pSelectedFeature)->AddRef();
		return S_OK;
	}
	return E_FAIL;


//	BOOL bIsRef;
//	bIsRef=IsReferenceLayer(m_pEditLayer,pFeature);//判断是够是要素层
	
}

HRESULT CShpEditorView::GetSelectedFeatures(IArray **pFeatureSet)								//得到选中的要素
{
	HRESULT	hr;
	IArrayPtr	pArray(CLSID_Array);
	
	if(m_lSeleteCount==0)	return E_FAIL;

	IEnumFeaturePtr		pEnumFeature;
	ISelectionPtr		pSelection;

	hr=m_pMap->get_FeatureSelection(&pSelection);
	if(FAILED(hr))	return hr;
	pEnumFeature=pSelection;
	
	IFeaturePtr	pFeature;
	pEnumFeature->Next(&pFeature);
	while (pFeature!=NULL)
	{
		pArray->Add((IUnknown*)pFeature);
		pEnumFeature->Next(&pFeature);	
	}
	*pFeatureSet=pArray;
	if(*pFeatureSet)
	{
		(*pFeatureSet)->AddRef();
		return S_OK;
	}
	return E_FAIL;	
}

HRESULT CShpEditorView::GetWorkspaceEdit(IWorkspaceEdit **pWorkspaceEdit)
{
	if(m_pWorkspaceEdit==NULL) return E_FAIL;
	*pWorkspaceEdit=m_pWorkspaceEdit;
	if (*pWorkspaceEdit)
		(*pWorkspaceEdit)->AddRef();
	return S_OK;


}

LRESULT CShpEditorView::OnChangeFeature(WPARAM wParam, LPARAM lParam)
{
	m_Property = NULL;
    return 0;	
}

HRESULT CShpEditorView::AddFeatureToSeletedSet(IFeaturePtr pHitFeature)
{
	m_pGeometry=NULL;
	
	if(m_pEditLayer==NULL) return E_FAIL;
	
	HRESULT hr;
	ILayerPtr	pLayer;
	pLayer=m_pEditLayer;
	
	long lSelectedCount;
	m_pMap->get_SelectionCount(&lSelectedCount);
	if(lSelectedCount==0) 
	{
		m_pMap->SelectFeature(pLayer,pHitFeature);
		
		IGeometryPtr	pGeo;
		pHitFeature->get_Shape(&pGeo);
		m_pGeometry=pGeo;
		m_lSeleteCount=1;
		m_bSelected=TRUE;
		return S_OK;
	}
	
	IEnumFeaturePtr		ipEnumFeature;
	ISelectionPtr		ipSelection;
	
	hr=m_pMap->get_FeatureSelection(&ipSelection);
	if(FAILED(hr))	return hr;
	ipEnumFeature=ipSelection;
	
	IFeaturePtr		ipFeature;
	hr=ipEnumFeature->Next(&ipFeature);
	if(FAILED(hr))	return hr;
	if(ipFeature==NULL) return E_FAIL;
	
	IGeometryCollectionPtr	pSelectedGeometryBag(CLSID_GeometryBag);
	m_pMap->ClearSelection();
	
	long FeaOID,HitFeaOID;
	pHitFeature->get_OID(&HitFeaOID);
	
	BOOL	bIsSeleted=TRUE;
	
	while (!(ipFeature==0)) {
		
		ipFeature->get_OID(&FeaOID);
		
		if(FeaOID==HitFeaOID)
		{
			bIsSeleted=FALSE;
		}
		else
		{
			m_pMap->SelectFeature(pLayer,ipFeature);		
			IGeometryPtr	ipGeometry;
			ipFeature->get_Shape(&ipGeometry);
			
			hr=pSelectedGeometryBag->AddGeometry(ipGeometry,&vtMissing,&vtMissing);
			if(FAILED(hr))	return hr;
		}
		
		hr=ipEnumFeature->Next(&ipFeature);
		if(FAILED(hr))	return hr;
	}
	
	if(bIsSeleted)
	{
		m_pMap->SelectFeature(pLayer,pHitFeature);		
		IGeometryPtr	ipGeometry;
		pHitFeature->get_Shape(&ipGeometry);
		hr=pSelectedGeometryBag->AddGeometry(ipGeometry,&vtMissing,&vtMissing);
	}
/*	
	m_pMap->get_SelectionCount(&lSelectedCount);
	
	m_lSeleteCount=lSelectedCount;
	if(lSelectedCount==0)
	{
		m_bSelected=FALSE;
		return S_OK;
	}
	m_bSelected=TRUE;
	
	IGeometryPtr	pTempGeo(CLSID_Polygon);
	ITopologicalOperatorPtr	ipTopoOpt;
	ipTopoOpt=pTempGeo;
	
	IEnumGeometryPtr	ipEnumGeometry(pSelectedGeometryBag);
	hr=ipTopoOpt->ConstructUnion(ipEnumGeometry);
	if(FAILED(hr))	return hr;
	ipTopoOpt->Simplify();
	
	m_pGeometry=pTempGeo;
	long npartCount;
	IGeometryCollectionPtr	pGeoCol;
	pGeoCol=m_pGeometry;
	pGeoCol->get_GeometryCount(&npartCount);
	*/
	hr=GetSelectedFeatures();
	if(FAILED(hr)) return hr;
	return S_OK;
	
}

BOOL CShpEditorView::IsSelected(IFeaturePtr pHitFeature)
{
	HRESULT hr;
	ILayerPtr	pLayer;
	pLayer=m_pEditLayer;
	m_pMap->SelectFeature(pLayer,pHitFeature);
	
	IEnumFeaturePtr		ipEnumFeature;
	ISelectionPtr		ipSelection;
	
	hr=m_pMap->get_FeatureSelection(&ipSelection);
	if(FAILED(hr))	return hr;
	ipEnumFeature=ipSelection;
	
	IFeaturePtr		ipFeature;
	hr=ipEnumFeature->Next(&ipFeature);
	if(FAILED(hr))	return hr;
	if (ipFeature==NULL) return FALSE;
	
	while (ipFeature!=NULL)
	{
		long FeaOID,HitFeaOID;
		ipFeature->get_OID(&FeaOID);
		pHitFeature->get_OID(&HitFeaOID);
		
		if(FeaOID==HitFeaOID)
			return TRUE;		
	}
	return FALSE;
}


HRESULT CShpEditorView::PitchOnFeature(IGeometryPtr pGeometry)
{
	m_pGeometry=NULL;
	m_lSeleteCount=0;
	
	if(m_pEditLayer==NULL) return E_FAIL;
	if(pGeometry==NULL)     return E_FAIL;
	
	HRESULT hr;

	IQueryFilterPtr	pQueryFielter(CLSID_QueryFilter);
	IFeatureCursorPtr	pCursor;
	m_pEditLayer->Search(pQueryFielter,VARIANT_TRUE,&pCursor);
	
	IRelationalOperatorPtr	pRelOpe;
	pRelOpe=pGeometry;

	IFeaturePtr	pFeature;
	pCursor->NextFeature(&pFeature);

	while(pFeature!=NULL)
	{
		IGeometryPtr pTempGeo;
		pFeature->get_Shape(&pTempGeo);
		VARIANT_BOOL vtb;
		pRelOpe->Equals(pTempGeo,&vtb);

		if(vtb==VARIANT_TRUE)
			break;
		pCursor->NextFeature(&pFeature);
	}

	if(pFeature==NULL) return E_FAIL;
	
	ILayerPtr	pLayer;
	pLayer=m_pEditLayer;

	hr=m_pMap->ClearSelection();				//清除所有要素的选择
	hr=m_pMap->SelectFeature(pLayer,pFeature);
	
	long lSelectedCount;
	hr=m_pMap->get_SelectionCount(&lSelectedCount);
	
	if(lSelectedCount==0) return E_FAIL;
	m_bSelected=TRUE;				//保存是否选中了要素
	m_lSeleteCount=lSelectedCount;	//保存选中的要素个数

	m_pGeometry=pGeometry;			//保存选中的要素
	return S_OK;
}

void CShpEditorView::OnUpdateFileSaveshp(CCmdUI* pCmdUI)
{
	VARIANT_BOOL	bHasEdits;
	if(m_pWorkspaceEdit==NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	m_pWorkspaceEdit->HasEdits(&bHasEdits);
	pCmdUI->Enable(bHasEdits==VARIANT_TRUE);	
}

void CShpEditorView::OnEditorExchangeLayerIndex() 
{
	ILayerPtr	pFirstLayer;
	m_pMap->get_Layer(0,&pFirstLayer);
	if(pFirstLayer==(ILayerPtr)m_pEditLayer)
		m_pMap->MoveLayer(m_pRefLayer,0);
	else
		m_pMap->MoveLayer(m_pEditLayer,0);
	IActiveViewPtr	pAct(m_pMap);
	pAct->Refresh();
}

void CShpEditorView::OnUpdateEditorExchangeLayerIndex(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pEditLayer!=NULL && m_pRefLayer!=NULL);	
}

void CShpEditorView::ShowFeatureLabel()
{
	ShowFeatureLabel("编辑层");
}

void CShpEditorView::ShowFeatureLabel(CString sLayerType,BOOL &bIsVisible)
{
	HRESULT	hr;

	IActiveViewPtr			pActiveView(m_pMap);
	IGraphicsContainerPtr	pGraCont(pActiveView);
	pGraCont->DeleteAllElements();

	IRgbColorPtr	pColor(CLSID_RgbColor);
	
	IFeatureLayerPtr	pFeaLayer;
	if(sLayerType=="编辑层")
	{
		if(m_bIsRefLayerLabelVisibel)
		{
			pColor->put_Red(255);
			AddFeatureLayerLabel(m_pRefLayer,pColor,m_nRefIndex);
		}
		pColor->put_Blue(255);
		pFeaLayer=m_pEditLayer;
		m_pCurrentLayer=m_pEditLayer;
		m_bIsEditLayerLabelVisibel=bIsVisible;  //保存当前编辑层是否显示Label
	
		if(!bIsVisible)
		{
			m_nEditIndex=-1;
			m_nIndex=-1;
			bIsVisible=!bIsVisible;
			return;
		}
	}
	else
	{
		if(m_bIsEditLayerLabelVisibel)
		{
			pColor->put_Blue(255);
			AddFeatureLayerLabel(m_pEditLayer,pColor,m_nEditIndex);
		}

		pFeaLayer=m_pRefLayer;
		m_pCurrentLayer=m_pRefLayer;
		pColor->put_Red(255);
		m_bIsRefLayerLabelVisibel=bIsVisible;  //保存当前编辑层是否显示Label
		
		if(!bIsVisible)
		{
			m_nRefIndex=-1;
			m_nIndex=-1;
			bIsVisible=!bIsVisible;
			return;
		}
	}

		
	long nIndex;
	nIndex=SelectLabelField(pFeaLayer);
	if(nIndex==-1)
		return;
	
	if(sLayerType=="编辑层")
	{
		m_nEditIndex=nIndex;
	}
	else
	{
		m_nRefIndex=nIndex;
	}
	
	bIsVisible=!bIsVisible;

	ITextSymbolPtr	pTextSymbol(CLSID_TextSymbol);
	hr=pTextSymbol->put_Color(pColor);

	hr=pTextSymbol->put_VerticalAlignment(esriTVACenter);
	
	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=pFeaLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	IQueryFilterPtr		pQueryFielter(CLSID_QueryFilter);
	IFeatureCursorPtr	pCursor;

	pFeaLayer->Search(pQueryFielter,VARIANT_TRUE,&pCursor);

	IScreenDisplayPtr		pScrD;
	pActiveView->get_ScreenDisplay(&pScrD);
	
	IElementCollectionPtr	pElemCol(CLSID_ElementCollection);
	IFeaturePtr	pFeature;
	pCursor->NextFeature(&pFeature);
	while(pFeature!=NULL)
	{
		IFieldsPtr	pFields;
		pFeature->get_Fields(&pFields);

		IFieldPtr	pField;
		pFields->get_Field(nIndex,&pField);

		esriFieldType	fieldtype;
		hr=pField->get_Type(&fieldtype);

		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);

		hr=pFeature->get_Value(nIndex,&vtFieldValue);
		if(vtFieldValue.vt==VT_EMPTY)
			continue;
		CString strFieldValue;
		strFieldValue=vtToCString(vtFieldValue,fieldtype);
					
		BSTR BLabel;
		BLabel=strFieldValue.AllocSysString();


		ITextElementPtr	pTextElement(CLSID_TextElement);
		hr=pTextElement->put_Symbol(pTextSymbol);
		hr=pTextElement->put_ScaleText(VARIANT_TRUE);
		hr=pTextElement->put_Text(BLabel);

		IElementPtr	pElement;
		pElement=pTextElement;

		IGeometryPtr	pTextGeo;
		hr=pFeature->get_Shape(&pTextGeo);
		
		IPolygonPtr	pPolygon;
		pPolygon=pTextGeo;

		IAreaPtr	pArea;
		pArea=pPolygon;

		IPointPtr	pPoint;
		hr=pArea->get_LabelPoint(&pPoint);
		
		hr=pElement->put_Geometry(pPoint);
		hr=pElement->Activate(pScrD);
		
		hr=pGraCont->AddElement(pElement,0);
		hr=pCursor->NextFeature(&pFeature);		

	}

//	pActiveView->PartialRefresh(esriViewGraphics,0,0);	
}

void CShpEditorView::ShowFeatureLabel(CString sLayerType)
{
	HRESULT	hr;

	IActiveViewPtr			pActiveView(m_pMap);
	IGraphicsContainerPtr	pGraCont(pActiveView);
	pGraCont->DeleteAllElements();

	IRgbColorPtr	pColor(CLSID_RgbColor);
	
	pColor->put_Blue(255);

	ITextSymbolPtr	pTextSymbol(CLSID_TextSymbol);
	hr=pTextSymbol->put_Color(pColor);

	hr=pTextSymbol->put_VerticalAlignment(esriTVACenter);
	
	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer = m_pEditLayer;

	ITablePtr	pTable;
	pTable = pGeoLayer;

	IQueryFilterPtr		pQueryFielter(CLSID_QueryFilter);
	IFeatureCursorPtr	pCursor;

	m_pEditLayer->Search(pQueryFielter,VARIANT_TRUE,&pCursor);

	IScreenDisplayPtr		pScrD;
	pActiveView->get_ScreenDisplay(&pScrD);
	
	IElementCollectionPtr	pElemCol(CLSID_ElementCollection);
	IFeaturePtr	pFeature;
	pCursor->NextFeature(&pFeature);
	while(pFeature!=NULL)
	{
		IFieldsPtr	pFields;
		pFeature->get_Fields(&pFields);

		IFieldPtr	pField;
		pFields->get_Field(m_nIndex,&pField);

		esriFieldType	fieldtype;
		hr=pField->get_Type(&fieldtype);

		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);

		hr=pFeature->get_Value(m_nIndex,&vtFieldValue);
		if(vtFieldValue.vt==VT_EMPTY)
			continue;
		CString strFieldValue;
		strFieldValue=vtToCString(vtFieldValue,fieldtype);
					
		BSTR BLabel;
		BLabel=strFieldValue.AllocSysString();

		ITextElementPtr	pTextElement(CLSID_TextElement);
		hr=pTextElement->put_Symbol(pTextSymbol);
		hr=pTextElement->put_ScaleText(VARIANT_TRUE);
		hr=pTextElement->put_Text(BLabel);

		IElementPtr	pElement;
		pElement=pTextElement;

		IGeometryPtr	pTextGeo;
		hr=pFeature->get_Shape(&pTextGeo);
		
		IPolygonPtr	pPolygon;
		pPolygon=pTextGeo;

		IAreaPtr	pArea;
		pArea=pPolygon;

		IPointPtr	pPoint;
		hr=pArea->get_LabelPoint(&pPoint);
		
		hr=pElement->put_Geometry(pPoint);
		hr=pElement->Activate(pScrD);
		
		hr=pGraCont->AddElement(pElement,0);
		hr=pCursor->NextFeature(&pFeature);
	}
}

long CShpEditorView::SelectLabelField(IFeatureLayerPtr	pLayer)
{
	CFS_SelectLabelDlg	SelectLabelDlg;

	CString strSelectedField;
	if(SelectLabelDlg.DoModal()==IDOK)
	{
		strSelectedField=SelectLabelDlg.m_strSelectedField;
	}
	else
		return -1;

	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=pLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	if(strSelectedField=="")
		return -1;

	BSTR	BFieldName;
	BFieldName=strSelectedField.AllocSysString();

	long nIndex;
	pTable->FindField(BFieldName,&nIndex);
	
	m_nIndex=nIndex;
	return nIndex;
}

void CShpEditorView::AddFeatureLayerLabel(IFeatureLayerPtr pFeaLayer,IColorPtr	pColor,long nIndex)
{
	HRESULT	hr;
	IActiveViewPtr	pActiveView(m_pMap);
	IGraphicsContainerPtr	pGraCont(pActiveView);
	
	ITextSymbolPtr	pTextSymbol(CLSID_TextSymbol);
	hr=pTextSymbol->put_Color(pColor);
	
	hr=pTextSymbol->put_VerticalAlignment(esriTVACenter);
	
	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=pFeaLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;
	
	IQueryFilterPtr		pQueryFielter(CLSID_QueryFilter);
	IFeatureCursorPtr	pCursor;
	
	hr=pFeaLayer->Search(pQueryFielter,VARIANT_TRUE,&pCursor);
	
	
	IElementCollectionPtr	pElemCol(CLSID_ElementCollection);
	IFeaturePtr	pFeature;
	pCursor->NextFeature(&pFeature);
	while(pFeature!=NULL)
	{
		IFieldsPtr	pFields;
		pFeature->get_Fields(&pFields);
		
		IFieldPtr	pField;
		pFields->get_Field(nIndex,&pField);
		
		esriFieldType	fieldtype;
		hr=pField->get_Type(&fieldtype);
		
		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);
		
		hr=pFeature->get_Value(nIndex,&vtFieldValue);
		if(vtFieldValue.vt==VT_EMPTY)
			continue;
		CString strFieldValue;
		strFieldValue=vtToCString(vtFieldValue,fieldtype);
		
		BSTR BLabel;
		BLabel=strFieldValue.AllocSysString();
		
		
		ITextElementPtr	pTextElement(CLSID_TextElement);
		hr=pTextElement->put_Symbol(pTextSymbol);
		hr=pTextElement->put_ScaleText(VARIANT_TRUE);
		hr=pTextElement->put_Text(BLabel);
		
		IElementPtr	pElement;
		pElement=pTextElement;
		
		IGeometryPtr	pTextGeo;
		hr=pFeature->get_Shape(&pTextGeo);
		
		IPolygonPtr	pPolygon;
		pPolygon=pTextGeo;
		
		IAreaPtr	pArea;
		pArea=pPolygon;
		
		IPointPtr	pPoint;
		hr=pArea->get_LabelPoint(&pPoint);
		
		hr=pElement->put_Geometry(pPoint);
		
		hr=pGraCont->AddElement(pElement,0);
		hr=pCursor->NextFeature(&pFeature);		
		
	}
}

CString CShpEditorView::vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype)
{
	CString	strFieldValue;
	
	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:	
		short nFieldVal;
		nFieldVal=(short)vtFieldValue.iVal;
		strFieldValue.Format("%d",nFieldVal);
		break;
	case esriFieldTypeInteger:
		long lFieldVal;
		lFieldVal=(long)vtFieldValue.lVal;
		strFieldValue.Format("%ld",lFieldVal);
		break;
	case esriFieldTypeSingle:
		float fFieldVal;
		fFieldVal=(float)vtFieldValue.fltVal;
		strFieldValue.Format("%f",fFieldVal);
		break;
	case esriFieldTypeDouble:
		double dFieldVal;
		dFieldVal=(double)vtFieldValue.dblVal;
		strFieldValue.Format("%lf",dFieldVal);
		break;
	case esriFieldTypeString:
		strFieldValue=(LPCWSTR)vtFieldValue.bstrVal;
		break;
	case esriFieldTypeDate:
		{
			COleDateTime dtFieldVal;
			dtFieldVal=(COleDateTime) vtFieldValue.date;
			int nYear,nMonth,nDay;
			nYear=dtFieldVal.GetYear();
			nMonth=dtFieldVal.GetMonth();
			nDay=dtFieldVal.GetDay();
			
			strFieldValue.Format("%d-%d-%d",nYear,nMonth,nDay);
		}
		break;
	default:
		strFieldValue="0";
		break;
	}
	return strFieldValue;
}

void CShpEditorView::FS_Refresh()
{
	IActiveViewPtr	pActiveView(m_pMap);
	pActiveView->Refresh();
}

BOOL CShpEditorView::GetEditLayerLableVisible()
{
	return 		m_bIsEditLayerLabelVisibel;  //保存当前编辑层是否显示Label	
}

BOOL CShpEditorView::GetCurrentLayer(IFeatureLayer ** pCurrentLayer)
{
	(*pCurrentLayer)=m_pCurrentLayer;
	if(*pCurrentLayer)
	{
		(*pCurrentLayer)->AddRef();
		return TRUE;
	}
	return FALSE;
}

long CShpEditorView::GetLabelIndex()
{
	if(m_nIndex==-1)
		return 0;
	return m_nIndex;
}

HRESULT CShpEditorView::GetFeatureByGeometry(IGeometryPtr pRefGeo, IFeature **pFeature)
{
	m_pGeometry=NULL;
	m_lSeleteCount=0;
	
	if(m_pEditLayer==NULL) return E_FAIL;
	if(pRefGeo==NULL)     return E_FAIL;
	
	HRESULT hr;
	
	IQueryFilterPtr	pQueryFielter(CLSID_QueryFilter);
	IFeatureCursorPtr	pCursor;
	m_pEditLayer->Search(pQueryFielter,VARIANT_TRUE,&pCursor);
	
	IRelationalOperatorPtr	pRelOpe;
	pRelOpe=pRefGeo;
	
	IFeaturePtr	pTempFeature;
	hr=pCursor->NextFeature(&pTempFeature);
	
	while(pTempFeature!=NULL)
	{
		IGeometryPtr pTempGeo;
		pTempFeature->get_Shape(&pTempGeo);

		VARIANT_BOOL vtb;
		pRelOpe->Equals(pTempGeo,&vtb);
		
		if(vtb==VARIANT_TRUE)
			break;
		hr=pCursor->NextFeature(&pTempFeature);
	}
	
	if(pTempFeature==NULL) return E_FAIL;
	*pFeature=pTempFeature;
	if(*pFeature)
	{
		(*pFeature)->AddRef();
		return S_OK;
	}

	return E_FAIL;
}

BOOL CShpEditorView::IsMultiPart(IGeometryPtr pGeometry)
{
	if(pGeometry==NULL) return FALSE;
	IGeometryCollectionPtr	pGeometryBag(CLSID_GeometryBag);
	pGeometryBag=pGeometry;

	long nParts;
	pGeometryBag->get_GeometryCount(&nParts);
	if (nParts>1)
		return TRUE;
	else
		return FALSE;
}
