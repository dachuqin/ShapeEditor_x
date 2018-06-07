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
	}esriStateType;//ö�ٵ�ǰ��������

protected:
	IWorkspacePtr		m_pWorkspace;
	IWorkspaceEditPtr	m_pWorkspaceEdit;	//�༭��
	IWorkspaceEditPtr	m_pTempWorkspaceEdit;
	IMapControl3Ptr		m_pMapControl;
	IFeatureLayerPtr	m_pRefLayer;		//�ο���
	IFeatureLayerPtr	m_pCurrentLayer;	//���
	IFeatureLayerPtr	m_pEditLayer;		//�༭��
	
	INewLineFeedbackPtr			m_pNLFeedback;		//�и�߲���
	INewCircleFeedbackPtr		m_pNCFeedback;		//��Բ����
	CFS_NewPolygon				*m_pNPFeedback;		//��Polygon����
	CNewCircleArc 				*m_pNCArc;			//�����Ͷ���β���
	CFS_ModifyPolygon			*m_pModifyPolygon;	//�޸�Ҫ�ز���
public:
	IMoveGeometryFeedbackPtr	m_pMGFeedback;		//�ƶ�Ҫ�ز���
protected:
	CFS_FeatureProperty * m_Property;				//Ҫ�����Ա༭�Ի���
	
protected:
	
	
	IMapPtr				m_pMap;	
	esriARTool			m_esriARTool;	//Tools������������������
protected:
	IGeometryPtr		m_pGeometry;		//����ѡ�е�Ҫ��
	IPointPtr			m_pfromPoint;		//�ƶ�Ҫ��ʱ������ʼ��
	IDatasetPtr			m_pEditDataset;		//�༭Ҫ�ؼ�
	IDatasetPtr			m_pRefDataset;		//�ο�Ҫ�ؼ�

	IPolylinePtr		m_pLine;			//�����и�ʱ������
	ISymbolPtr			m_pSymbol;			//ѡ�е�������
	IScreenDisplayPtr	m_pScrD;			//���ڻ�Բ
	
	BOOL				m_bIsPanFinish;		//�ж�ƽ��ͼ���Ƿ����
	BOOL				m_bEdit;			//�жϱ༭���Ƿ�����
	BOOL				m_bIsHasEditLayer;	//�жϱ༭���Ƿ����
	enum esriEditType	m_esriEditType;		//��ǰ��������
	BOOL				m_bSelected;		//�ж��Ƿ���Ҫ��ѡ��
	BOOL				m_OnSelFea;			//�жϵ�ǰ����Ƿ���ѡ�е�Ҫ���Ϸ�
	BOOL				m_bDrag;			//�ж��Ƿ����϶�״̬
	BOOL				m_bPressDown;		//
	long				m_lSeleteCount;		//����ѡ��Ҫ�صĸ���
	BOOL				m_bSelectedMultiPart;//ѡ�е�Ҫ���Ƿ��Ƕ���������
	
	int					m_nLayerType;		//����Ĳ������1���༭�㣬2���ο���
	BOOL				m_bSnap;			//�Ƿ�ѡ���˲�׽����
	IGeometryPtr		m_pCirCleElem;		//����겶��ĵ㴦��СԲȦ
	IPointPtr			m_pCatchPoint;		//ѡ����Snaping��ʱ������겶��ĵ�

	CPictureDisp		m_pMouseCrossCircle;
	CPictureDisp		m_pMouseEditNormal;	
	CPictureDisp		m_pMouseMove;
	CPictureDisp		m_pMouseModify;	
	
	BOOL				m_bSnapEditLayer;
	IArrayPtr			m_pRefLayerArray;		//�����ѵ�������вο���
	IArrayPtr			m_pEditLayerArray;		//�����ѵ�������б༭��
	//////////////////////////////////////////////////////////////////////////
	BS_DrawType			m_BS_DrawType;			//���浱ǰ��ͼ�����ͣ�Arc��Polygon��
	BOOL				m_bIsHitSketchMenu;		//�жϻ�ͼ�������Ƿ񵥻��˲˵���������������꣩
protected:
	BOOL				m_bMouseMove;
	BOOL				m_bMouseModify;
	BOOL				m_bMouseCross;
	BOOL				m_bMouseNormal;
protected:
	IFeaturePtr			m_pFeaClipboard;
	IGeometryPtr		m_pClipboard;			//������и��Ƶ�Ҫ��
	BOOL				m_bIsCut;				//�Ƿ�����˼���
protected:
	IPointPtr			m_pArcCurrentPoint;		//���滭ͼ�����еĵ�ǰ��
	CSnapSketch			*m_SnapOperator;		//�������

	BOOL				m_bIsCatch;				//�жϵ�ǰ�Ƿ񲶻�Ŀ��
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

	void	ShowFeatureLabel(CString strLayerType,BOOL &bIsVisible);			//��ʾ����Ҫ�ر��
	void	ShowFeatureLabel(CString strLayerType);								//�༭Ҫ�غ���ʾ����Ҫ�ر��
	void	ShowFeatureLabel();													//�༭Ҫ�غ���ʾ����Ҫ�ر��

	
	HRESULT GetSelectedFeatures(IFeature **pSelectedFeature,BOOL &bIsReference);	//�õ�ѡ�е�Ҫ��
	HRESULT GetSelectedFeatures(IArray **pFeatureSet);								//�õ�ѡ�е�Ҫ��

	HRESULT GetWorkspaceEdit(IWorkspaceEdit** pWorkspaceEdit);
	BOOL	GetEditLayer(IFeatureLayer ** pEditLayer);								//�õ���ǰ�༭��

	HRESULT	AddFile();									//����༭��
	HRESULT	AddReferenceFile();							//����ο���
	void	DeleteLayer(CString strLayerName);			//ɾ����
	void	SetLayerSymbol(CString strLayerName);		//����ͼ���������
	BOOL	ExitApp();									//�˳�����ʱ��ʾ����
	TC_HTREEITEM	GetCurrentItemState(HTREEITEM hti); //�õ�Tree������Ӧ�Ĳ��Ƿ����ʾ
	CString vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype);
	HRESULT PitchOnFeature(IGeometryPtr pGeometry);					//ʹָ��Ҫ��Ϊѡ��״̬
	
protected:
	BOOL IsMultiPart(IGeometryPtr pGeometry);
	HRESULT GetFeatureByGeometry(IGeometryPtr pRefGeo,IFeature **pFeature);
	long	SelectLabelField(IFeatureLayerPtr	pLayer);
	BOOL	IsSelected(IFeaturePtr pHitFeature);
	void	AddFeatureLayerLabel(IFeatureLayerPtr pFeaLayer,IColorPtr pColor,long nIndex);
		
	HRESULT AddFeatureToSeletedSet(IFeaturePtr	 pFeature);			//��ָ��Ҫ�ؼ���ѡ��
	void	FinishModify();											//����Ҫ���޸�
	void	AddFeatureToLayer(IGeometryPtr	pGeometry);				//���½���Ҫ�ؼӵ��༭��
	void	FS_Dump();												//������ǰ����
	HRESULT GetSelectedFeaturePoint(IPoint **Point);
	void	ESC_Command();											//��ESC���Ĳ���ʵ��
	void	StopEditor();											//ֹͣ�༭
	BOOL	DeleteLayerOfArrar(ILayerPtr pLayer);					//��ָ���Ĳ��������ɾ��
	void	ClearMemory();											//���˳�����ʱ���ڴ�����

	void	ShowCoordinate(double X,double Y);						//��ʾ��굱ǰλ��
	void	SetMouse();
	HRESULT _SelectFeature(IEnvelopePtr pEnv,BOOL bIsHit);
	HRESULT	GetSelectedFeatures();									//�õ�ѡ�е�Ҫ��
	HRESULT	DeleteSelectedFeature();								//ɾ��ѡ�е�Ҫ��
	HRESULT	BufferSelectedFeature(double distance);					//��ѡ�е�Ҫ�����û�����

	HRESULT NewFile();												//�½��༭��
	HRESULT SaveCurrentFile();										//���浱ǰ�ļ�
	HRESULT SaveAsCurrentFile();									//��ǰ�ļ����Ϊ
		
	///////////////***********��갴�µĲ���******************////////////////////////////////////////////////
	void	DownToolsOperation(IActiveViewPtr pActiveView,IPointPtr	pPoint);		//Tools�������ڵĲ���
	void	DownDrawLineOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);		//���߶���
	void	DownDrawPolygonOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);	//������εĶ���
	void	DownDrawCircleOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);	//��Բ�Ķ���
	void	DownDrawArcOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);
	void	DownDrawArcOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint,
								double dRadius,int IsClockwise,int nArcType);
	void	DownMoveGeometryOperation(IScreenDisplayPtr pScrD,IPointPtr	pPoint);	//�ƶ�Ҫ�صĶ���
	void	SelectFeatureOperation(double mapX, double mapY);	//ѡ��Ҫ�صĲ���
	void	SelectFeatureOperation(IPointPtr pPoint);
	
	///////////////***********����ƶ����̵Ĳ���******************////////////////////////////////////////////////
	void	MoveDrawLineOperation(IPointPtr	pPoint);			//���߶���
	void	MoveDrawPolygonOperation(IPointPtr	pPoint);		//������εĶ���
	void	MoveDrawCircleOperation(IPointPtr	pPoint);		//��Բ�Ķ���
	void	MoveDrawArcOperation(IPointPtr	pPoint);			//��Բ�Ķ���
	void	MoveMoveGeometryOperation(VARIANT_BOOL vb, long button,IPointPtr pPoint);	//�ƶ�Ҫ�صĶ���
	
	void	UpMoveGeometryOperation(IPointPtr	pPoint);	//�ƶ�Ҫ�صĶ���
	void	UpDrawPolygonOperation(IPointPtr pPoint);

	///////////////***********���˫���Ĳ���******************////////////////////////////////////////////////
	void	DoubleClickDrawLine(IPointPtr pPoint);
	void	DoubleClickDrawPolygon(IPointPtr pPoint);
	void	DoubleClickDrawCircle(IPointPtr pPoint);//��Բ
	void	DoubleClickDrawArc(IPointPtr pPoint);
		
	HRESULT IsHasLayer(CString sLayerName);			//�жϲ��Ƿ��Ѿ�����
		
	HRESULT GetLayerByName(CString sLayerName,ILayer ** pLayer);	//���ݲ�����ֵõ��� 
	HRESULT	AddLayerNameToTree(CString strName);					//�Ѳ����ּ���Tree�ؼ�
	void	SetFillSymbol();										//���ò��������
	void	TempWorkspaceEditorStart();
	void	ShowLayer(IFeatureLayerPtr	pShowLayer,BOOL bLayerType);	//�������Ƿ�ɼ�
	void	CopyFeatureClass(IFeatureClassPtr pEditFeaClass,
							IFeatureClassPtr pNewFeaClass);				//���Ϊʱ�õ���Ҫ���ิ��
	HRESULT CreateNewGeom(IFeatureClass* pOutFC, IGeometry* pNewGeom);	//Ҫ���ิ�����õ��Ĵ�����Geometry
	
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
