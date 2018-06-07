#if !defined(AFX_FS_MODIFYPOLYGON1_H__7AC21B3F_B914_40C6_BBD4_A3DCA051F449__INCLUDED_)
#define AFX_FS_MODIFYPOLYGON1_H__7AC21B3F_B914_40C6_BBD4_A3DCA051F449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_ModifyPolygon1.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CFS_ModifyPolygon command target

class CFS_ModifyPolygon : public CCmdTarget
{
	DECLARE_DYNCREATE(CFS_ModifyPolygon)

	CFS_ModifyPolygon();           // protected constructor used by dynamic creation
	virtual ~CFS_ModifyPolygon();

protected:
	
	
// Attributes
public:
	int GetCatchType();

	void	DoubleClick(IPointPtr pPoint);
	void	RightClick(IPointPtr pPoint);
	BOOL	MouseDown(IPointPtr pPoint);
	BOOL	MouseMove(long button,IPointPtr	pPoint);
	BOOL	MouseUp(long button,IPointPtr	pPoint);
	void	Stop(IGeometry ** pPolygon);
	void	Put_Display(IScreenDisplayPtr	pScrD);
	void	Put_Layer(IFeatureLayerPtr	pLayer);
	void	Back();
	BOOL	IsModify();
	void	DrawPolygon();

	void	OnInsertVertex();
	void	OnUpdateInsertVertex(CCmdUI* pCmdUI);
	void	OnDeleteVertex();
	void	OnUpdateDeleteVertex(CCmdUI* pCmdUI);
	void	OnBack();
	void	OnUpdateBack(CCmdUI* pCmdUI);

protected:
	IPointCollectionTrackerPtr	m_pPCTracker;
	IGeometryCollectionPtr	m_pGeoTracker;
//	IPointCollectionPtr		m_ptCol;
	IScreenDisplayPtr		m_pScrD;
	IFeatureLayerPtr		m_pLayer;
	ISegmentCollectionPtr	m_pSegCol;
	IPointPtr				m_ptCatch;
	IPointPtr				m_pPrePoint;
	IArrayPtr				m_ptColArray;

	IGeometryPtr			m_ModGeo;
	IArrayPtr				m_pGeoArray;
	
	long					m_nPartIndex;
	BOOL					m_bIsCatch;
	BOOL					m_bIsStart;
	long					m_hitSegmentIndex;
	long					m_hitLineIndex;
	BOOL					m_bIsCatchLine;
	BOOL					m_bIsHasModify;
protected:

	void	GetFeaturePoint(IGeometryPtr pGeometry);
	HRESULT CatchLine(IPointPtr pPoint);
	void	CreatePolygon();
	void	CreatePolygon(IGeometryPtr pGeometry);//
	void	AddPointToPolygon(IPointPtr pPoint);
	HRESULT	IsCatch(IPointPtr pPoint);
	HRESULT GetGeomtery(IGeometryPtr pPoint,IGeometry **pGeometry);
	void	InvertDoubleLine(IPointPtr pPoint);
	void	GetMouseCiecle(IPointPtr pMousePoint,IGeometry** pCirGeo);
	double	_GetMapDistance(long lDistance);
	void	Dump();
	// Generated message map functions
	//{{AFX_MSG(CFS_ModifyPolygon)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_MODIFYPOLYGON1_H__7AC21B3F_B914_40C6_BBD4_A3DCA051F449__INCLUDED_)
