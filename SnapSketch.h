// SnapSketch.h: interface for the CSnapSketch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPSKETCH_H__859DB43C_7E6C_4D40_9890_34D6ABC7E33E__INCLUDED_)
#define AFX_SNAPSKETCH_H__859DB43C_7E6C_4D40_9890_34D6ABC7E33E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSnapSketch  
{
public:
	CSnapSketch();
	virtual ~CSnapSketch();
public:
	void Start();	
	void PutRef_MapControl(IMapControl3Ptr	pMapControl);
	void PutRef_Display(IScreenDisplayPtr	pScrD);
	void AddLayer(IFeatureLayerPtr	pFeatureLayer);			//������Ҫ����Ĳ�
	void MoveTo(IPointPtr pPoint);
	BOOL GetCatchPoint(IPoint ** pCatchPoint);				//�õ���ǰ����ĵ�
	void DeleteLayer(IFeatureLayerPtr pDelLayer);			//��m_pLayerCollection��ɾ��һ����
	BOOL IsCatch();											//�Ƿ񲶻�
	void LButtonDown(IPointPtr pPoint);
	
protected:
	IMapControl3Ptr		m_pMapControl;
	IActiveViewPtr		m_pActiveView;
	IScreenDisplayPtr	m_pScrD;
	ISymbolPtr			m_pSymbol;
	IArrayPtr			m_pLayerCollection;		//������Ҫ����Ĳ�
	IPointPtr			m_pCatchPoint;			//���沶��ĵ�

	BOOL				m_bPointSnap;			//�Ƿ�ѡ���˵㲶��
	BOOL				m_bLineSnap;			//�Ƿ�ѡ�����߲���
	BOOL				bCatched;			//�Ƿ񲶻񵽵�
	long				m_i;				//���ڽ���༭��Ͳο���
protected:
	double	_GetMapDistance( long lDistance);	//��Ҫ�ؾ���ת����

	HRESULT CatchLine(IGeometryPtr pMouseGeo, IPointPtr pPoint);
	HRESULT QueryFeature(IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry,
							esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur);
	HRESULT SnapQueryFeature(IFeatureLayerPtr pRefLayer,IGeometryPtr pGeometry,
								esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur);
	HRESULT DrawSmallCircle(IPointPtr	pPoint);
	void	GetMouseCiecle(IPointPtr pMousePoint,IGeometry** pCirGeo);
	HRESULT CatchPt(IGeometryPtr pMouseGeo,IPointPtr pPoint);
	HRESULT	GetIntersectGeometry(IGeometryPtr pMouseGeo,IGeometry ** pResultGeo,long nIndex);		
	HRESULT	GetIntersectGeometrys(IGeometryPtr pMouseGeo,IFeatureCursor ** pFeaCur,long nIndex);
		
};
/////////////////////////////////////////////////////////////////////////////
// CSnapMethodDlg dialog

class CSnapMethodDlg : public CDialog
{
	// Construction
public:
	CSnapMethodDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CSnapMethodDlg)
	enum { IDD = IDD_SNAPING };
	CButton	m_ctrSnapPoint;
	CButton	m_ctrSnapLine;
	BOOL	m_bSnapLine;
	BOOL	m_bSnapPoint;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnapMethodDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CSnapMethodDlg)
	afx_msg void OnSnapLine();
	afx_msg void OnSnapPoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_SNAPSKETCH_H__859DB43C_7E6C_4D40_9890_34D6ABC7E33E__INCLUDED_)
