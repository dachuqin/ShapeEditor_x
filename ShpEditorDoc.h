// ShpEditorDoc.h : interface of the CShpEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHPEDITORDOC_H__83BA97E8_8B5B_4256_AF29_36E1310EABC5__INCLUDED_)
#define AFX_SHPEDITORDOC_H__83BA97E8_8B5B_4256_AF29_36E1310EABC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShpEditorDoc : public CDocument
{
protected: // create from serialization only
	CShpEditorDoc();
	DECLARE_DYNCREATE(CShpEditorDoc)

// Attributes
public:
	IMapControl3Ptr	m_pMapControl;
	IMapPtr			m_pMap;
	IWorkspacePtr	m_pWorkspace;
	IWorkspacePtr	m_pTempWorkspace;

	IDatasetPtr		m_pDataset;
	IDatasetPtr		m_pRefDataset;
	IFeatureLayerPtr	m_pRefLayer;
	IFeatureLayerPtr	m_pEditLayer;

	BSTR			m_BPath;
	BSTR			m_BName;
	IGeometryPtr	m_pGeometry;
// Operations
public:
	HRESULT	AddShp(CString *bName);
	HRESULT	NewShpFile(CString *strName,IFeatureClass**	pFeaClass);
	HRESULT	SaveASShp(IFeatureClass *pEditFeaClass,IFeatureClass**	pFeaClass);
	HRESULT	AddReference(CString *bName);
	HRESULT CreateShapefile( BSTR bstrPath, BSTR bstrName,IFeatureClass ** pFeatureClass);

	HRESULT	CreateShapefile( BSTR bstrPath, BSTR bstrName,
							IFeatureClassPtr pEditFeaClass,
							IFeatureClass** pFeatureClass);
	HRESULT MoveSelectedFeature(IMapPtr	pMap,IFeatureLayerPtr pEditLayer,IPointPtr  fromPoint,IPointPtr toPoint);
	HRESULT	GetSelectedFeature(IMapPtr pMap,long *lSeletedCount,IGeometry ** pResultGeometry);
	HRESULT DeleFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer);
	
	HRESULT	NewFeatures(IFeatureLayerPtr pEditLayer,IGeometryPtr	pGeometry);
	HRESULT	NewFeatures(IFeatureLayerPtr pEditLayer,IFeaturePtr	pOldFeature,IGeometryPtr pGeometry);

	HRESULT	DocInsertFeature(IFeatureCursor* pInFeatCur,IFeatureBuffer* pInFeatBuf,
									IFeature* pOrigFeat, IGeometry* pGeom);
	
	HRESULT	BufferFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer,double distance);
	HRESULT QueryFeature(IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry,esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur);
	HRESULT	ClipFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry,double distance,int method);
	HRESULT Merge(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometry **pNewGeo);
	HRESULT UnionFeatures(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometry **pNewGeo);
	HRESULT Divide(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry);
	HRESULT	ConvertGeometry(IGeometryPtr pRingGeo,IGeometryCollection ** pOutCol);
	HRESULT CutFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IPolylinePtr pLine);
	HRESULT IntersectFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer);
	BOOL	IsReferenceLayer(IFeatureLayerPtr pEditLayer,IFeaturePtr	pFeature);
	HRESULT SnapQueryFeature(IFeatureLayerPtr pFeaLayer,IGeometryPtr pGeometry,
								esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur);
		// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShpEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShpEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	IArrayPtr	m_pFeatureArray;

// Generated message map functions
protected:
	BOOL	SelectReferenceFeature(IMapPtr pMap,IFeature **pRefFeature);
	CString vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype);
	//{{AFX_MSG(CShpEditorDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHPEDITORDOC_H__83BA97E8_8B5B_4256_AF29_36E1310EABC5__INCLUDED_)
