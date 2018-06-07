// SnapSketch.cpp: implementation of the CSnapSketch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShpEditor.h"
#include "SnapSketch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapSketch::CSnapSketch()
{
	m_pLayerCollection.CreateInstance(CLSID_Array);
	m_pCatchPoint=NULL;
	m_bPointSnap=FALSE;
	m_bLineSnap=FALSE;
	m_i=0;
	//////////////////////////////////////////////////////////////////////////
	
	ISimpleMarkerSymbolPtr  pMarkerSymbol(CLSID_SimpleMarkerSymbol);
	
	IRgbColorPtr	pColorLine(CLSID_RgbColor);
	IRgbColorPtr	pColor(CLSID_RgbColor);
	
	pColor->put_Green(0);
	pColor->put_Blue(200);
	pColor->put_Red(200);
	pColorLine->put_RGB((OLE_COLOR)RGB(255, 255, 255));
	
	pMarkerSymbol->put_Color(pColor);
	pMarkerSymbol->put_Size(8.0);
	pMarkerSymbol->put_Style(esriSMSCircle);
	pMarkerSymbol->put_Outline(VARIANT_TRUE);
	pMarkerSymbol->put_OutlineColor(pColorLine);
	pMarkerSymbol->put_OutlineSize(1.0);	

//	ISymbolPtr pSymbol = static_cast<ISymbolPtr>(pMarkerSymbol);
//	pSymbol->put_ROP2(esriROPXOrPen);
	
/*	ISimpleFillSymbolPtr	pFillSymbol(CLSID_SimpleFillSymbol);
	
	pFillSymbol->put_Color(pColor);
	pFillSymbol->put_Outline(pLineSymbol);
	pFillSymbol->put_Style(esriSFSNull);
*/	
	m_pSymbol = static_cast<ISymbolPtr>(pMarkerSymbol);
}

CSnapSketch::~CSnapSketch()
{
	m_pLayerCollection->RemoveAll();
	m_pLayerCollection=NULL;
}

void CSnapSketch::Start()
{
	CSnapMethodDlg	SnapDlg;
	
	SnapDlg.m_bSnapPoint=m_bPointSnap;
	SnapDlg.m_bSnapLine=m_bLineSnap;
	if(SnapDlg.DoModal()==IDOK)
	{
		m_bPointSnap=SnapDlg.m_bSnapPoint;
		m_bLineSnap=SnapDlg.m_bSnapLine;
	}
}

void CSnapSketch::AddLayer(IFeatureLayerPtr	pFeatureLayer)
{
	if(pFeatureLayer==NULL)		return;

	if(m_pLayerCollection!=NULL)
	{
		m_pLayerCollection->Add(pFeatureLayer);		
	}
}

void CSnapSketch::PutRef_Display(IScreenDisplayPtr	pScrD)
{
	if(pScrD!=NULL)
		m_pScrD=pScrD;
}
void CSnapSketch::PutRef_MapControl(IMapControl3Ptr	pMapControl)
{
	if(pMapControl!=NULL)
	{
		m_pMapControl=pMapControl;
		m_pMapControl->get_ActiveView(&m_pActiveView);
	}
}

void CSnapSketch::MoveTo(IPointPtr pPoint)
{
	HRESULT	hr;
	IGeometryPtr	pMouseGeo;
	IPointPtr		pGeoPoint;

	GetMouseCiecle(pPoint,&pMouseGeo);
	if (pMouseGeo==NULL)	return;

	if(m_bPointSnap==TRUE)
	{
		hr=CatchPt(pMouseGeo,pPoint);//得到鼠标圆捕获的点pGeoPoint
		if(m_bLineSnap==TRUE && FAILED(hr))
			hr=CatchLine(pMouseGeo,pPoint);
	}
	else if(m_bLineSnap==TRUE)
	{
		hr=CatchLine(pMouseGeo,pPoint);//得到鼠标圆捕获的点pGeoPoint
	}
}

HRESULT CSnapSketch::QueryFeature(IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry,
									esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur)
{
	HRESULT hr;
	ISpatialFilterPtr	pSpaFil(CLSID_SpatialFilter);
	hr=pSpaFil->putref_Geometry(pGeometry);
	if(FAILED(hr)) return hr;
	hr=pSpaFil->put_SpatialRel(esriSpaRel);//设置查询关系
	if(FAILED(hr)) return hr;
	
	IFeatureLayerPtr	pFeaLayer;
	
	pFeaLayer=pEditLayer;
	if(pFeaLayer!=NULL)
	{
		IFeatureClassPtr	pFeaCls;
		BSTR FieldName;
		hr=pFeaLayer->get_FeatureClass(&pFeaCls);
		if(FAILED(hr)) return hr;
		hr=pFeaCls->get_ShapeFieldName(&FieldName);
		if(FAILED(hr)) return hr;
		hr=pSpaFil->put_GeometryField(FieldName);
		if(FAILED(hr)) return hr;
		hr=pFeaLayer->Search(pSpaFil,VARIANT_TRUE,pFeaCur);//得到相关的要素指针
		if(FAILED(hr)) return hr;
	}
	if(*pFeaCur)
	{
		(*pFeaCur)->AddRef();
		return S_OK;
	}
	return E_FAIL;
}
HRESULT CSnapSketch::SnapQueryFeature(IFeatureLayerPtr pFeaLayer,IGeometryPtr pGeometry,
										esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur)
{
	HRESULT hr;
	ISpatialFilterPtr	pSpaFil(CLSID_SpatialFilter);
	hr=pSpaFil->putref_Geometry(pGeometry);
	if(FAILED(hr)) return hr;
	hr=pSpaFil->put_SpatialRel(esriSpaRel);//设置查询关系
	if(FAILED(hr)) return hr;
	
	if(pFeaLayer!=NULL)
	{
		IFeatureClassPtr	pFeaCls;
		BSTR FieldName;
		hr=pFeaLayer->get_FeatureClass(&pFeaCls);
		if(FAILED(hr)) return hr;
		hr=pFeaCls->get_ShapeFieldName(&FieldName);
		if(FAILED(hr)) return hr;
		hr=pSpaFil->put_GeometryField(FieldName);
		if(FAILED(hr)) return hr;
		hr=pFeaLayer->Search(pSpaFil,VARIANT_TRUE,pFeaCur);//得到相关的要素指针
		if(FAILED(hr)) return hr;
	}

	if(*pFeaCur)
	{
		(*pFeaCur)->AddRef();
		return S_OK;
	}
	return E_FAIL;
}

HRESULT	CSnapSketch::GetIntersectGeometry(IGeometryPtr pMouseGeo,IGeometry ** pResultGeo,long nIndex)
{
	HRESULT	 hr;
	IFeatureCursorPtr	pFeaCur;
	IFeatureLayerPtr	pFeatLayer;

	m_pLayerCollection->get_Element(nIndex,(IUnknown**) &pFeatLayer);
	hr=SnapQueryFeature(pFeatLayer,pMouseGeo,esriSpatialRelIntersects,&pFeaCur);
	if(FAILED(hr)) return hr;
	
	if(pFeaCur==NULL) return E_FAIL;
	IFeaturePtr	pFeature;
//	ASSERT(pFeaCur!=NULL);
	hr=pFeaCur->NextFeature(&pFeature);
	if(FAILED(hr)) return hr;
	if(pFeature==NULL)
	{
		return E_NOINTERFACE;
	}
	
	IGeometryPtr	pGeo;
	hr=pFeature->get_Shape(&pGeo);
	if(FAILED(hr)) return hr;
	*pResultGeo=pGeo;
	if(*pResultGeo)
		(*pResultGeo)->AddRef();
	return S_OK;
}

HRESULT	CSnapSketch::GetIntersectGeometrys(IGeometryPtr pMouseGeo,IFeatureCursor ** pFeaCur,long nIndex)
{
	HRESULT	 hr;
	IFeatureLayerPtr	pFeatLayer;

	m_pLayerCollection->get_Element(nIndex,(IUnknown**) &pFeatLayer);
	hr=SnapQueryFeature(pFeatLayer,pMouseGeo,esriSpatialRelIntersects,pFeaCur);
	
	if(FAILED(hr)) return hr;
	if(pFeaCur==NULL) return E_FAIL;
	
//	ASSERT(pFeaCur!=NULL);

	if(*pFeaCur)
	{
		(*pFeaCur)->AddRef();
		return S_OK;
	}
	return E_FAIL;
}

/*

HRESULT CSnapSketch::CatchPt(IGeometryPtr pMouseGeo,IPointPtr pPoint)
{
	HRESULT	hr;
	IActiveViewPtr	pAct;
	m_pMapControl->get_ActiveView(&pAct);
	
	IFeatureCursorPtr	pFeaCur=NULL;
	
	long	LayerCount;
	m_pLayerCollection->get_Count(&LayerCount);
	
	if(LayerCount==0 || LayerCount-1<0) return E_FAIL;
	IGeometryPtr	pLineGeo;
	
	if(m_i==0)
	{
		hr=GetIntersectGeometrys(pMouseGeo,&pFeaCur,m_i);
		if(SUCCEEDED(hr))
			m_i=0;
		else
			m_i=1;
	}
	else
	{
		hr=GetIntersectGeometrys(pMouseGeo,&pFeaCur,m_i);
		if(SUCCEEDED(hr))
			m_i=1;
		else
			m_i=0;
	}
	
	if(hr==E_NOINTERFACE && m_hr!=E_NOINTERFACE)
	{
		if (bCatched)
		{
			if (m_pCatchPoint != NULL)
			{
				DrawSmallCircle( m_pCatchPoint);
			}				
			m_pCatchPoint = NULL;
		}
		m_hr=hr;
		m_pCatchPoint=NULL;			
		return E_FAIL;
		
	}
	else if (bCatched)
	{
		if (m_pCatchPoint != NULL)
		{
			DrawSmallCircle( m_pCatchPoint);
		}			
		m_pCatchPoint = NULL;
	}
	if(FAILED(hr)) 
	{
		if (bCatched)
		{
			if (m_pCatchPoint != NULL)
			{
				DrawSmallCircle( m_pCatchPoint);
			}				
			m_pCatchPoint = NULL;
		}
		m_pCatchPoint=NULL;			
		return E_FAIL;
	}
	else if (bCatched)
	{
		if (m_pCatchPoint != NULL)
		{
			DrawSmallCircle( m_pCatchPoint);
		}			
		m_pCatchPoint = NULL;
	}
	
	VARIANT_BOOL bRightSide, bHit;
	long	 hitPartIndex=0, hitSegmentIndex=0;
	double	 hitDistance = 0;
	double	 fDistance=_GetMapDistance(4);
	IFeaturePtr	pFeature;

	pFeaCur->NextFeature(&pFeature);

	while (pFeature!=NULL) 
	{
		IGeometryPtr	pInetersectGeo;
		hr=pFeature->get_Shape(&pInetersectGeo);

		IHitTestPtr		pHitTest=static_cast<IHitTestPtr>(pInetersectGeo);
		IPointPtr pHitPoint(CLSID_Point);
		
		hr=pHitTest->HitTest(pPoint,fDistance,esriGeometryPartVertex,pHitPoint,&hitDistance,
								&hitPartIndex,&hitSegmentIndex,&bRightSide,&bHit);
		if(FAILED(hr)) return hr;
		
		if(bHit==VARIANT_TRUE )
		{
			DrawSmallCircle(pHitPoint);
			m_pCatchPoint=pHitPoint;
			m_hr=E_FAIL;
			return S_OK;	
		}		
		pFeaCur->NextFeature(&pFeature);		
	}

	return S_OK;	

}
*/
HRESULT CSnapSketch::CatchPt(IGeometryPtr pMouseGeo,IPointPtr pPoint)
{
	HRESULT	hr;
	IActiveViewPtr	pAct;
	m_pMapControl->get_ActiveView(&pAct);
	
	
	long	LayerCount;
	m_pLayerCollection->get_Count(&LayerCount);
	for(long i=0;i<LayerCount;i++)
	{
		IFeatureLayerPtr	pFeatLayer;
		IFeatureCursorPtr	pFeaCur;

		hr=m_pLayerCollection->get_Element(i,(IUnknown**) &pFeatLayer);
		hr=SnapQueryFeature(pFeatLayer,pMouseGeo,esriSpatialRelIntersects,&pFeaCur);
		if(FAILED(hr)) return hr;
		if(pFeaCur==NULL) return E_FAIL;

		if (bCatched)
		{
			if (m_pCatchPoint != NULL)
			{
				DrawSmallCircle( m_pCatchPoint);
			}				
			m_pCatchPoint = NULL;
		}
		m_pCatchPoint=NULL;			
		
		VARIANT_BOOL bRightSide, bHit;
		long	 hitPartIndex=0, hitSegmentIndex=0;
		double	 hitDistance = 0;
		double	 fDistance=_GetMapDistance(4);
		IFeaturePtr	pFeature;
		
		pFeaCur->NextFeature(&pFeature);
		
		while (pFeature!=NULL) 
		{
			IGeometryPtr	pInetersectGeo;
			hr=pFeature->get_Shape(&pInetersectGeo);
			
			IHitTestPtr		pHitTest=static_cast<IHitTestPtr>(pInetersectGeo);
			IPointPtr pHitPoint(CLSID_Point);
			
			hr=pHitTest->HitTest(pPoint,fDistance,esriGeometryPartVertex,pHitPoint,&hitDistance,
				&hitPartIndex,&hitSegmentIndex,&bRightSide,&bHit);
			if(FAILED(hr)) return hr;
			
			if(bHit==VARIANT_TRUE )
			{
				DrawSmallCircle(pHitPoint);
				m_pCatchPoint=pHitPoint;
				return S_OK;	
			}		
			pFeaCur->NextFeature(&pFeature);		
		}
	}
	return E_FAIL;
}


HRESULT CSnapSketch::CatchLine(IGeometryPtr pMouseGeo,IPointPtr pPoint)
{
	HRESULT	hr;
	IActiveViewPtr	pAct;
	m_pMapControl->get_ActiveView(&pAct);
	
	
	long	LayerCount;
	m_pLayerCollection->get_Count(&LayerCount);
	for(long i=0;i<LayerCount;i++)
	{
		IFeatureLayerPtr	pFeatLayer;
		IFeatureCursorPtr	pFeaCur;
		
		hr=m_pLayerCollection->get_Element(i,(IUnknown**) &pFeatLayer);
		hr=SnapQueryFeature(pFeatLayer,pMouseGeo,esriSpatialRelIntersects,&pFeaCur);
		if(FAILED(hr)) return hr;
		if(pFeaCur==NULL) return E_FAIL;
		
		if (bCatched)
		{
			if (m_pCatchPoint != NULL)
			{
				DrawSmallCircle( m_pCatchPoint);
			}				
			m_pCatchPoint = NULL;
		}
		m_pCatchPoint=NULL;			
		
		VARIANT_BOOL bRightSide, bHit;
		long	 hitPartIndex=0, hitSegmentIndex=0;
		double	 hitDistance = 0;
		double	 fDistance=_GetMapDistance(4);
		IFeaturePtr	pFeature;
		
		pFeaCur->NextFeature(&pFeature);
		
		while (pFeature!=NULL) 
		{
			IGeometryPtr	pInetersectGeo;
			hr=pFeature->get_Shape(&pInetersectGeo);
			
			IHitTestPtr		pHitTest=static_cast<IHitTestPtr>(pInetersectGeo);
			IPointPtr ptHit(CLSID_Point);
			
			hr=pHitTest->HitTest(pPoint, fDistance, esriGeometryPartBoundary, ptHit, 
				&hitDistance, &hitPartIndex, &hitSegmentIndex, &bRightSide, &bHit);
			
			double	X=0,Y=0;
			if (bHit == VARIANT_TRUE )
			{
				DrawSmallCircle(ptHit);
				m_pCatchPoint=ptHit;
				bCatched=TRUE;
				return S_OK;
			}
			
			pFeaCur->NextFeature(&pFeature);		
		}
	}
	return E_FAIL;		
}
void CSnapSketch::GetMouseCiecle(IPointPtr pMousePoint,IGeometry** pCirGeo)
{
	HRESULT	hr;
	ICircularArcPtr	pCircular(CLSID_CircularArc);
	long x,y;

	if(m_pMapControl==NULL)	return;
	hr=m_pMapControl->FromMapPoint(pMousePoint,&x,&y);
	x+=4;
	y+=4;
	IPointPtr	pRingPoint;
	hr=m_pMapControl->ToMapPoint(x,y,&pRingPoint);
	hr=pCircular->PutCoords(pMousePoint,pRingPoint,pRingPoint,esriArcClockwise);
	ISegmentPtr	pSegment(pCircular);
	ISegmentCollectionPtr	pSegmentCol(CLSID_Polygon);
	pSegmentCol->AddSegment(pSegment);
	IGeometryPtr	pGeometry(pSegmentCol);
	*pCirGeo=pGeometry;
	if(*pCirGeo)
		(*pCirGeo)->AddRef();
}

//////////****** 当鼠标接近几何图形的极点时，在此点处画圆**********///////////////////////
HRESULT CSnapSketch::DrawSmallCircle(IPointPtr	pPoint)
{

	m_pSymbol->put_ROP2(esriROPXOrPen);
	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(m_pSymbol);
	m_pScrD->DrawPoint(pPoint);
	m_pScrD->FinishDrawing();
	return S_OK;
}


double CSnapSketch::_GetMapDistance(long lDistance)
{
	IActiveViewPtr		pActiveView;
	m_pMapControl->get_ActiveView(&pActiveView);

	IScreenDisplayPtr pScreenDisplay;
	pActiveView->get_ScreenDisplay(&pScreenDisplay);
	
	IDisplayTransformationPtr pDisplayTransform;
	pScreenDisplay->get_DisplayTransformation(&pDisplayTransform);
	
	double fDistance = 0;
	
	pDisplayTransform->FromPoints(lDistance, &fDistance);
	
	return fDistance;
}



BOOL CSnapSketch::GetCatchPoint(IPoint ** pCatchPoint)
{
	if(m_pCatchPoint==NULL)
		return FALSE;
	else
	{
		*pCatchPoint=m_pCatchPoint;
		if(*pCatchPoint)
			(*pCatchPoint)->AddRef();
		return TRUE;
	}
}


BOOL CSnapSketch::IsCatch()
{
	if (m_bPointSnap || m_bLineSnap) 
		return TRUE;
	else
		return FALSE;
	
}

/////////////////////////////////////////////////////////////////////////////
// CSnapMethodDlg dialog


CSnapMethodDlg::CSnapMethodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnapMethodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnapMethodDlg)
	m_bSnapLine = FALSE;
	m_bSnapPoint = FALSE;
	//}}AFX_DATA_INIT
}


void CSnapMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapMethodDlg)
	DDX_Control(pDX, IDC_SNAP_POINT, m_ctrSnapPoint);
	DDX_Control(pDX, IDC_SNAP_LINE, m_ctrSnapLine);
	DDX_Check(pDX, IDC_SNAP_LINE, m_bSnapLine);
	DDX_Check(pDX, IDC_SNAP_POINT, m_bSnapPoint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnapMethodDlg, CDialog)
	//{{AFX_MSG_MAP(CSnapMethodDlg)
	ON_BN_CLICKED(IDC_SNAP_LINE, OnSnapLine)
	ON_BN_CLICKED(IDC_SNAP_POINT, OnSnapPoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapMethodDlg message handlers

void CSnapMethodDlg::OnSnapLine() 
{
	if(m_bSnapLine==FALSE)
	{
		m_bSnapLine=TRUE;
	}
	else
	{
		m_bSnapLine=FALSE;
	}	
}

void CSnapMethodDlg::OnSnapPoint() 
{
	if(m_bSnapPoint==FALSE)
	{
		m_bSnapPoint=TRUE;
	}
	else
	{
		m_bSnapPoint=FALSE;
	}	
}

void CSnapSketch::DeleteLayer(IFeatureLayerPtr pDelLayer)
{
	long	LayerCount;
	m_pLayerCollection->get_Count(&LayerCount);
	for(long i=0;i<LayerCount;i++)
	{
		IFeatureLayerPtr pFeatLayer;
		m_pLayerCollection->get_Element(i,(IUnknown**)&pFeatLayer);
		if(pFeatLayer==pDelLayer)
		{
			m_pLayerCollection->Remove(i);
			break;
		}		
	}
}


void CSnapSketch::LButtonDown(IPointPtr pPoint)
{
	DrawSmallCircle(pPoint);
}
