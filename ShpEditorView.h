// ShpEditorView.h : interface of the CShpEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHPEDITORVIEW_H__F340B0EC_6AB5_4EB2_93F7_ABFA834178E2__INCLUDED_)
#define AFX_SHPEDITORVIEW_H__F340B0EC_6AB5_4EB2_93F7_ABFA834178E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ShpEditorDoc.h"
#include "PictureDisp.h"
#include "TreeLayer.h"
#include "BS_NewCircleArc.h"
#include "SnapSketch.h"
#include "FS_NewPolygon.h"
#include "FS_ModifyPolygon1.h"
#include "FS_FeatureProperty.h"

class CShpEditorView : public CFormView
{
protected: // create from serialization only
	CShpEditorView();
	DECLARE_DYNCREATE(CShpEditorView)

public:
	//{{AFX_DATA(CShpEditorView)
	enum{ IDD = IDD_SHPEDITOR_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CShpEditorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShpEditorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShpEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	enum esriEditType
	{
		esriTools=0,
		esriDrawLine,
		esriDrawPolygon,
		esriDrawCircle,
		esriDrawArc,
		esriMoveGeometry,
		esriNothing
	}esriStateType;//枚举当前动作类型

protected:
	IWorkspacePtr		m_pWorkspace;
	IWorkspaceEditPtr	m_pWorkspaceEdit;	//编辑器
	IWorkspaceEditPtr	m_pTempWorkspaceEdit;
	IMapControl3Ptr		m_pMapControl;
	IFeatureLayerPtr	m_pRefLayer;		//参考层
	IFeatureLayerPtr	m_pCurrentLayer;	//活动层
	IFeatureLayerPtr	m_pEditLayer;		//编辑层
	
	INewLineFeedbackPtr			m_pNLFeedback;		//切割划线操作
	INewCircleFeedbackPtr		m_pNCFeedback;		//画圆操作
	CFS_NewPolygon				*m_pNPFeedback;		//画Polygon操作
	CNewCircleArc 				*m_pNCArc;			//画弧和多边形操作
	CFS_ModifyPolygon			*m_pModifyPolygon;	//修改要素操作
public:
	IMoveGeometryFeedbackPtr	m_pMGFeedback;		//移动要素操作
protected:
	CFS_FeatureProperty * m_Property;				//要素属性编辑对话框
	
protected:
	
	
	IMapPtr				m_pMap;	
	esriARTool			m_esriARTool;	//Tools工具栏的鼠标控制类型
protected:
	IGeometryPtr		m_pGeometry;		//保存选中的要素
	IPointPtr			m_pfromPoint;		//移动要素时保存起始点
	IDatasetPtr			m_pEditDataset;		//编辑要素集
	IDatasetPtr			m_pRefDataset;		//参考要素集

	IPolylinePtr		m_pLine;			//保存切割时画的线
	ISymbolPtr			m_pSymbol;			//选中的填充符号
	IScreenDisplayPtr	m_pScrD;			//用于画圆
	
	BOOL				m_bIsPanFinish;		//判断平移图层是否结束
	BOOL				m_bEdit;			//判断编辑器是否启动
	BOOL				m_bIsHasEditLayer;	//判断编辑曾是否存在
	enum esriEditType	m_esriEditType;		//当前动作类型
	BOOL				m_bSelected;		//判断是否有要素选中
	BOOL				m_OnSelFea;			//判断当前鼠标是否在选中的要素上方
	BOOL				m_bDrag;			//判断是否处于拖动状态
	BOOL				m_bPressDown;		//
	long				m_lSeleteCount;		//保存选中要素的个数
	BOOL				m_bSelectedMultiPart;//选中的要素是否是多个部分组成
	
	int					m_nLayerType;		//插入的层的类型1：编辑层，2：参考层
	BOOL				m_bSnap;			//是否选中了捕捉功能
	IGeometryPtr		m_pCirCleElem;		//在鼠标捕获的点处画小圆圈
	IPointPtr			m_pCatchPoint;		//选择了Snaping键时，有鼠标捕获的点

	CPictureDisp		m_pMouseCrossCircle;
	CPictureDisp		m_pMouseEditNormal;	
	CPictureDisp		m_pMouseMove;
	CPictureDisp		m_pMouseModify;	
	
	BOOL				m_bSnapEditLayer;
	IArrayPtr			m_pRefLayerArray;		//保存已导入的所有参考层
	IArrayPtr			m_pEditLayerArray;		//保存已导入的所有编辑层
	//////////////////////////////////////////////////////////////////////////
	BS_DrawType			m_BS_DrawType;			//保存当前画图的类型（Arc和Polygon）
	BOOL				m_bIsHitSketchMenu;		//判断画图过程中是否单击了菜单命令（如加入绝对坐标）
protected:
	BOOL				m_bMouseMove;
	BOOL				m_bMouseModify;
	BOOL				m_bMouseCross;
	BOOL				m_bMouseNormal;
protected:
	IFeaturePtr			m_pFeaClipboard;
	IGeometryPtr		m_pClipboard;			//保存剪切复制的要素
	BOOL				m_bIsCut;				//是否进行了剪切
protected:
	IPointPtr			m_pArcCurrentPoint;		//保存画图过程中的当前点
	CSnapSketch			*m_SnapOperator;		//捕获操作

	BOOL				m_bIsCatch;				//判断当前是否捕获到目标
protected:
	BOOL				m_bIsEditLayerLabelVisibel;
	BOOL				m_bIsRefLayerLabelVisibel;
	long				m_nIndex;
	long				m_nEditIndex;
	long				m_nRefIndex;
public:
	long GetLabelIndex();
	BOOL	GetCurrentLayer(IFeatureLayer ** pCurrentLayer);
	BOOL	GetEditLayerLableVisible();
	void	FS_Refresh();

	void	ShowFeatureLabel(CString strLayerType,BOOL &bIsVisible);			//显示隐藏要素标记
	void	ShowFeatureLabel(CString strLayerType);								//编辑要素后，显示隐藏要素标记
	void	ShowFeatureLabel();													//编辑要素后，显示隐藏要素标记

	
	HRESULT GetSelectedFeatures(IFeature **pSelectedFeature,BOOL &bIsReference);	//得到选中的要素
	HRESULT GetSelectedFeatures(IArray **pFeatureSet);								//得到选中的要素

	HRESULT GetWorkspaceEdit(IWorkspaceEdit** pWorkspaceEdit);
	BOOL	GetEditLayer(IFeatureLayer ** pEditLayer);								//得到当前编辑层

	HRESULT	AddFile();									//加入编辑层
	HRESULT	AddReferenceFile();							//加入参考层
	void	DeleteLayer(CString strLayerName);			//删除层
	void	SetLayerSymbol(CString strLayerName);		//设置图层的填充符号
	BOOL	ExitApp();									//退出程序时提示保存
	TC_HTREEITEM	GetCurrentItemState(HTREEITEM hti); //得到Tree中所对应的层是否可显示
	CString vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype);
	HRESULT PitchOnFeature(IGeometryPtr pGeometry);					//使指定要素为选中状态
	
protected:
	BOOL IsMultiPart(IGeometryPtr pGeometry);
	HRESULT GetFeatureByGeometry(IGeometryPtr pRefGeo,IFeature **pFeature);
	long	SelectLabelField(IFeatureLayerPtr	pLayer);
	BOOL	IsSelected(IFeaturePtr pHitFeature);
	void	AddFeatureLayerLabel(IFeatureLayerPtr pFeaLayer,IColorPtr pColor,long nIndex);
		
	HRESULT AddFeatureToSeletedSet(IFeaturePtr	 pFeature);			//把指定要素加入选择集
	void	FinishModify();											//结束要素修改
	void	AddFeatureToLayer(IGeometryPtr	pGeometry);				//把新建的要素加到编辑层
	void	FS_Dump();												//结束当前操作
	HRESULT GetSelectedFeaturePoint(IPoint **Point);
	void	ESC_Command();											//按ESC键的操作实现
	void	StopEditor();											//停止编辑
	BOOL	DeleteLayerOfArrar(ILayerPtr pLayer);					//把指定的层从数组中删除
	void	ClearMemory();											//当退出程序时把内存清零

	void	ShowCoordinate(double X,double Y);						//显示鼠标当前位置
	void	SetMouse();
	HRESULT _SelectFeature(IEnvelopePtr pEnv,BOOL bIsHit);
	HRESULT	GetSelectedFeatures();									//得到选中的要素
	HRESULT	DeleteSelectedFeature();								//删除选中的要素
	HRESULT	BufferSelectedFeature(double distance);					//给选中的要素设置缓冲区

	HRESULT NewFile();												//新建编辑层
	HRESULT SaveCurrentFile();										//保存当前文件
	HRESULT SaveAsCurrentFile();									//当前文件另存为
		
	///////////////***********鼠标按下的操作******************////////////////////////////////////////////////
	void	DownToolsOperation(IActiveViewPtr pActiveView,IPointPtr	pPoint);		//Tools工具栏内的操作
	void	DownDrawLineOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);		//画线动作
	void	DownDrawPolygonOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);	//画多边形的动作
	void	DownDrawCircleOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);	//画圆的动作
	void	DownDrawArcOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);
	void	DownDrawArcOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint,
								double dRadius,int IsClockwise,int nArcType);
	void	DownMoveGeometryOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);	//移动要素的动作
	void	SelectFeatureOperation(double mapX, double mapY);	//选择要素的操作
	void	SelectFeatureOperation(IPointPtr pPoint);
	
	///////////////***********鼠标移动过程的操作******************////////////////////////////////////////////////
	void	MoveDrawLineOperation(IPointPtr	pPoint);			//画线动作
	void	MoveDrawPolygonOperation(IPointPtr	pPoint);		//画多边形的动作
	void	MoveDrawCircleOperation(IPointPtr	pPoint);		//画圆的动作
	void	MoveDrawArcOperation(IPointPtr	pPoint);			//画圆的动作
	void	MoveMoveGeometryOperation(VARIANT_BOOL vb, long button,IPointPtr pPoint);	//移动要素的动作
	
	void	UpMoveGeometryOperation(IPointPtr	pPoint);	//移动要素的动作
	void	UpDrawPolygonOperation(IPointPtr pPoint);

	///////////////***********鼠标双击的操作******************////////////////////////////////////////////////
	void	DoubleClickDrawLine(IPointPtr pPoint);
	void	DoubleClickDrawPolygon(IPointPtr pPoint);
	void	DoubleClickDrawCircle(IPointPtr pPoint);//画圆
	void	DoubleClickDrawArc(IPointPtr pPoint);
		
	HRESULT IsHasLayer(CString sLayerName);			//判断层是否已经导入
		
	HRESULT GetLayerByName(CString sLayerName,ILayer ** pLayer);	//根据层的名字得到层 
	HRESULT	AddLayerNameToTree(CString strName);					//把层名字加入Tree控件
	void	SetFillSymbol();										//设置层的填充符号
	void	TempWorkspaceEditorStart();
	void	ShowLayer(IFeatureLayerPtr	pShowLayer,BOOL bLayerType);	//设置曾是否可见
	void	CopyFeatureClass(IFeatureClassPtr pEditFeaClass,
							IFeatureClassPtr pNewFeaClass);				//另存为时用到的要素类复制
	HRESULT CreateNewGeom(IFeatureClass* pOutFC, IGeometry* pNewGeom);	//要素类复制中用到的创建空Geometry
	
		//{{AFX_MSG(CShpEditorView)
	afx_msg void OnAddReference();
	afx_msg void OnFileAddshp();
	afx_msg void OnFileNewshp();
	afx_msg void OnFileSaveshp();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSaveshpAs();
	afx_msg void OnEditorStar();
	afx_msg void OnUpdateEditorStar(CCmdUI* pCmdUI);
	afx_msg void OnEditorStop();
	afx_msg void OnUpdateEditorStop(CCmdUI* pCmdUI);
	afx_msg void OnEditorUndo();
	afx_msg void OnUpdateEditorUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditorRedo();
	afx_msg void OnUpdateEditorRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditorMenu();
	afx_msg void OnMapZoomin();
	afx_msg void OnMapZoomout();
	afx_msg void OnMapPan();
	afx_msg void OnMapFullextent();
	afx_msg void OnMapArrow();
	afx_msg void OnMapSelect();
	afx_msg void OnUpdateMapZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMapZoomout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMapPan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMapArrow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMapSelect(CCmdUI* pCmdUI);
	afx_msg void OnOnMouseDownMapcontrol(long button, long shift, long x, long y, double mapX, double mapY);
	afx_msg void OnOnMouseMoveMapcontrol(long button, long shift, long x, long y, double mapX, double mapY);
	afx_msg void OnOnMouseUpMapcontrol(long button, long shift, long x, long y, double mapX, double mapY);
	afx_msg void OnOnDoubleClickMapcontrol(long button, long shift, long x, long y, double mapX, double mapY);
	afx_msg void OnEditorSelect();
	afx_msg void OnUpdateEditorSelect(CCmdUI* pCmdUI);
	afx_msg void OnEditorSkecthPolygon();
	afx_msg void OnUpdateEditorSkecthPolygon(CCmdUI* pCmdUI);
	afx_msg void OnEditorSketchLine();
	afx_msg void OnUpdateEditorSketchLine(CCmdUI* pCmdUI);
	afx_msg void OnEditorCopy();
	afx_msg void OnUpdateEditorCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditorPaste();
	afx_msg void OnUpdateEditorPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditorDelete();
	afx_msg void OnUpdateEditorDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditorMove();
	afx_msg void OnUpdateEditorMove(CCmdUI* pCmdUI);
	afx_msg void OnEditorDivide();
	afx_msg void OnUpdateEditorDivide(CCmdUI* pCmdUI);
	afx_msg void OnEditorMerge();
	afx_msg void OnUpdateEditorMerge(CCmdUI* pCmdUI);
	afx_msg void OnEditorUnion();
	afx_msg void OnUpdateEditorUnion(CCmdUI* pCmdUI);
	afx_msg void OnEditorIntersect();
	afx_msg void OnUpdateEditorIntersect(CCmdUI* pCmdUI);
	afx_msg void OnEditorBuffer();
	afx_msg void OnUpdateEditorBuffer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditorMenu(CCmdUI* pCmdUI);
	afx_msg void OnEditorSnapping();
	afx_msg void OnUpdateEditorSnapping(CCmdUI* pCmdUI);
	afx_msg void OnEditorClip();
	afx_msg void OnUpdateEditorClip(CCmdUI* pCmdUI);
	afx_msg void OnEditorCutFeature();
	afx_msg void OnUpdateMapFullextent(CCmdUI* pCmdUI);
	afx_msg void OnChangeLayerState(HTREEITEM hti);
	afx_msg void OnLayerColor();
	afx_msg void OnOnAfterDrawMapcontrol(const VARIANT FAR& display, long viewDrawPhase);
	afx_msg void OnUpdateEditorCutFeature(CCmdUI* pCmdUI);
	afx_msg void OnEditorCut();
	afx_msg void OnUpdateEditorCut(CCmdUI* pCmdUI);
	afx_msg void OnEditorSketchCircle();
	afx_msg void OnUpdateEditorSketchCircle(CCmdUI* pCmdUI);
	afx_msg void OnEditorSketchArc();
	afx_msg void OnUpdateEditorSketchArc(CCmdUI* pCmdUI);
	afx_msg void OnDrawCoordinate();
	afx_msg void OnDrawFinishAndRadius();
	afx_msg void OnDrawRadius();
	afx_msg void OnDrawOffset();
	afx_msg void OnDrawDeleteSketch();
	afx_msg void OnDrawConcelMenu();
	afx_msg void OnOnKeyDownMapcontrol(long keyCode, long shift);
	afx_msg void OnOnKeyUpMapcontrol(long keyCode, long shift);
	afx_msg void OnEditorSkecth();
	afx_msg void OnUpdateEditorSkecth(CCmdUI* pCmdUI);
	afx_msg void OnEditorModifyInsertVertex();
	afx_msg void OnUpdateEditorModifyInsertVertex(CCmdUI* pCmdUI);
	afx_msg void OnEditorModifyDeleteVertex();
	afx_msg void OnUpdateEditorModifyDeleteVertex(CCmdUI* pCmdUI);
	afx_msg void OnEditorModifyBack();
	afx_msg void OnUpdateEditorModifyBack(CCmdUI* pCmdUI);
	afx_msg void OnEditorModifyCancel();
	afx_msg void OnUpdateEditorModifyCancel(CCmdUI* pCmdUI);
	afx_msg void OnEditorProperty();
	afx_msg void OnUpdateEditorProperty(CCmdUI* pCmdUI);
	afx_msg void OnLayerProperty();
	afx_msg void OnUpdateLayerProperty(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveshp(CCmdUI* pCmdUI);
	afx_msg void OnEditorExchangeLayerIndex();
	afx_msg void OnUpdateEditorExchangeLayerIndex(CCmdUI* pCmdUI);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnChangeFeature(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShpEditorView.cpp
inline CShpEditorDoc* CShpEditorView::GetDocument()
   { return (CShpEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHPEDITORVIEW_H__F340B0EC_6AB5_4EB2_93F7_ABFA834178E2__INCLUDED_)
