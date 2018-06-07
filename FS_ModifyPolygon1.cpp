// FS_ModifyPolygon1.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "FS_ModifyPolygon1.h"
#include "ShpEditorView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_ModifyPolygon

IMPLEMENT_DYNCREATE(CFS_ModifyPolygon, CCmdTarget)

CFS_ModifyPolygon::CFS_ModifyPolygon()
{
	m_hitSegmentIndex=-1;
	m_hitLineIndex=-1;
	m_pPrePoint=NULL;
	m_pLayer=NULL;
	m_bIsStart=FALSE;
	m_bIsCatch=FALSE;
	m_bIsCatchLine=FALSE;
	m_bIsHasModify=FALSE;
	
	m_pGeoTracker.CreateInstance(CLSID_GeometryBag);
	m_ptColArray.CreateInstance(CLSID_Array);
	m_pSegCol.CreateInstance(CLSID_Polygon);
}

CFS_ModifyPolygon::~CFS_ModifyPolygon()
{
	m_pPrePoint=NULL;
	m_pLayer=NULL;
	m_bIsStart=FALSE;
	m_bIsCatch=FALSE;
	m_bIsCatchLine=FALSE;
	m_pGeoTracker=NULL;
	m_pSegCol=NULL;
}


BEGIN_MESSAGE_MAP(CFS_ModifyPolygon, CCmdTarget)
	//{{AFX_MSG_MAP(CFS_ModifyPolygon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_ModifyPolygon message handlers



void	CFS_ModifyPolygon::Put_Display(IScreenDisplayPtr	pScrD)
{
	m_pScrD=pScrD;
}

void	CFS_ModifyPolygon::Put_Layer(IFeatureLayerPtr	pLayer)
{
	if(pLayer!=NULL)
		m_pLayer=pLayer;
}

void	CFS_ModifyPolygon::DoubleClick(IPointPtr pPoint)
{
	HRESULT	 hr;
	IGeometryPtr	pGeometry;
	hr=GetGeomtery((IGeometryPtr)pPoint,&pGeometry);
	if(FAILED(hr))	return;

	m_bIsStart=TRUE;

	if(pGeometry!=NULL)
	{
		GetFeaturePoint(pGeometry);	
		CreatePolygon(pGeometry);
	}
}

BOOL CFS_ModifyPolygon::MouseMove(long button,IPointPtr	pPoint)
{
//	BOOL	bIsCatch;

	HRESULT hr;
	
	if(button!=1)
	{
		hr=IsCatch(pPoint);
		if(FAILED(hr))
		{
			m_bIsCatch=FALSE;
		}		
		else
			m_bIsCatch=TRUE;
	}

	hr=CatchLine(pPoint);
	if(FAILED(hr) && m_bIsCatch==FALSE)	
	{
		return FALSE;
	}

	if(button!=1)
	{
		if(m_bIsCatch || (m_ptCatch!=NULL))
		{

//			DrawPolygon();
			return TRUE;
		}
		else
			return FALSE;
	}
	else
	{
		if(m_bIsCatch)
		{
			InvertDoubleLine(m_pPrePoint);
			InvertDoubleLine(pPoint);
			m_pPrePoint=pPoint;
			return TRUE;
		}
		else
			return FALSE;
	}
}

BOOL CFS_ModifyPolygon::MouseDown(IPointPtr pPoint)
{
		if(m_bIsCatch)
		{
			m_ptCatch=pPoint;
			m_pPrePoint=pPoint;
			return TRUE;
		}
		else
			return FALSE;
}

BOOL CFS_ModifyPolygon::MouseUp(long button,IPointPtr	pPoint)
{
	if(button==1)
	{
		if(m_bIsCatch==TRUE)
		{
			AddPointToPolygon(pPoint);
			m_bIsCatch=FALSE;
			return TRUE;
		}
		return FALSE;
	}
	else
		return FALSE;
}

void CFS_ModifyPolygon::RightClick(IPointPtr pPoint)
{
	
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
		
	CMenu menu;
	menu.LoadMenu(IDR_MENU_MODIFY_FEATURE);
	CPoint	point;
	::GetCursorPos(&point);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
}

void CFS_ModifyPolygon::Stop(IGeometry ** pPolygon)
{
	long	cParts;
	if(m_pGeoTracker==NULL) return;

	m_pGeoTracker->get_GeometryCount(&cParts);
	m_pGeoTracker->get_Geometry(cParts-1,pPolygon);
	if(*pPolygon)
		(*pPolygon)->AddRef();
	Dump();
}

void CFS_ModifyPolygon::Back()
{
	HRESULT	hr;
	if(m_pGeoTracker!=NULL)
	{
		long GeoCount;

		m_pGeoTracker->get_GeometryCount(&GeoCount);
		if(GeoCount>1)
		{
			IGeometryPtr	pPreGeo(CLSID_Polygon);

			m_pGeoTracker->RemoveGeometries(GeoCount-1,1);
			hr=m_pGeoTracker->get_GeometryCount(&GeoCount);
			if(GeoCount-1>=0)
			{
				m_pGeoTracker->get_Geometry(GeoCount-1,&pPreGeo);
				GetFeaturePoint(pPreGeo);
			}			
		}
		if(GeoCount<=1)
			m_bIsHasModify=FALSE;
	}
	else
	{
		m_bIsHasModify=FALSE;
	}

}

HRESULT CFS_ModifyPolygon::GetGeomtery(IGeometryPtr pPoint,IGeometry **pGeometry)
{
	if(m_pLayer==NULL) return E_FAIL;

		HRESULT	 hr;
		IFeatureLayerPtr	pFeatLayer;
		
		ISpatialFilterPtr	pSpaFil(CLSID_SpatialFilter);
		hr=pSpaFil->putref_Geometry(pPoint);
		if(FAILED(hr)) return hr;
		
		hr=pSpaFil->put_SpatialRel(esriSpatialRelIntersects);//设置查询关系
		if(FAILED(hr)) return hr;

		IFeatureCursorPtr	pFeaCur;
		hr=m_pLayer->Search(pSpaFil,VARIANT_TRUE,&pFeaCur);//得到相关的要素指针
		if(FAILED(hr)) return hr;
		if(pFeaCur==NULL) return E_FAIL;

		IFeaturePtr	pFeature;
		hr=pFeaCur->NextFeature(&pFeature);
		if(FAILED(hr)) return hr;
		if(pFeature==NULL)	return E_FAIL;

		IGeometryPtr	pGeo;
		hr=pFeature->get_Shape(&pGeo);
		pFeature->get_ShapeCopy(&pGeo);
		if(FAILED(hr)) return hr;

		*pGeometry=pGeo;
		if(*pGeometry)
			(*pGeometry)->AddRef();
		return S_OK;
}

void	CFS_ModifyPolygon::InvertDoubleLine(IPointPtr pto)
{
	IPointPtr pfrom1, pfrom2;
	if(m_hitSegmentIndex==-1) 
		AfxMessageBox("未捕获顶点");

	long nPartCount;
	m_ptColArray->get_Count(&nPartCount);
	
	IPointCollectionPtr	ptCol;
	m_ptColArray->get_Element(m_nPartIndex,(IUnknown**)&ptCol);

	long ptCount;
	ptCol->get_PointCount(&ptCount);

	if(m_hitSegmentIndex>0)
		ptCol->get_Point(m_hitSegmentIndex-1,&pfrom1);
	else
		ptCol->get_Point(ptCount-2,&pfrom1);

	if(m_hitSegmentIndex+1 < ptCount)
		ptCol->get_Point(m_hitSegmentIndex+1,&pfrom2);
	else
		ptCol->get_Point(0,&pfrom2);

	IPolylinePtr	pFirstLine(CLSID_Polyline);
	IPolylinePtr	pSecondLine(CLSID_Polyline);
	
	pFirstLine->put_FromPoint(pfrom1);
	pFirstLine->put_ToPoint(pto);
	
	pSecondLine->put_FromPoint(pfrom2);
	pSecondLine->put_ToPoint(pto);
	
	IRgbColorPtr	pColor(CLSID_RgbColor);
	pColor->put_Blue(255);
	pColor->put_Green(255);
	pColor->put_Red(255);
	
	ISimpleLineSymbolPtr	pSLSymbol(CLSID_SimpleLineSymbol);
	pSLSymbol->put_Color(pColor);
	
	ISymbolPtr	pSymbol;
	pSymbol=pSLSymbol;
	
	pSymbol->put_ROP2(esriROPNot);
	
	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(pSymbol);
	m_pScrD->DrawPolyline(pFirstLine);
	m_pScrD->DrawPolyline(pSecondLine);
	m_pScrD->FinishDrawing();

	
}
void	CFS_ModifyPolygon::Dump()
{
	m_pScrD=NULL;
//	m_ptCol=NULL;
	m_pGeoTracker=NULL;
	m_ptCatch=NULL;
	m_bIsCatch=NULL;
}

HRESULT CFS_ModifyPolygon::IsCatch(IPointPtr pPoint)
{
	HRESULT		hr;
	
	IGeometryPtr	pGeometry=NULL;
	if( m_bIsStart==TRUE)
	{
		long GeoCount;
		m_pGeoTracker->get_GeometryCount(&GeoCount);
		m_pGeoTracker->get_Geometry(GeoCount-1,&pGeometry);
	}
	else
	{
		IGeometryPtr	pMouseGeo;
		GetMouseCiecle(pPoint,& pMouseGeo);
		
		hr=GetGeomtery(pPoint,&pGeometry);
		if(FAILED(hr)) return hr;
	}
	if(pGeometry==NULL) return E_FAIL;

	VARIANT_BOOL bRightSide, bHit;
	long	 hitPartIndex=0, hitSegmentIndex=0;
	double	 hitDistance = 0;
	double	 fDistance=_GetMapDistance(4);

	IHitTestPtr		pHitTest;
	pHitTest=(IHitTestPtr)pGeometry;
	IPointPtr pHitPoint(CLSID_Point);
	
	hr=pHitTest->HitTest(pPoint,fDistance,esriGeometryPartVertex,pHitPoint,&hitDistance,&hitPartIndex,
								&hitSegmentIndex,&bRightSide,&bHit);
	if(FAILED(hr)) return hr;
	
	if(bHit==VARIANT_TRUE )
	{
		m_nPartIndex=hitPartIndex;
		m_hitSegmentIndex=hitSegmentIndex;
//		m_ptCatch=pHitPoint;
		return S_OK;
	}
	m_hitSegmentIndex=-1;
	return E_FAIL;
}

void CFS_ModifyPolygon::DrawPolygon()
{
	HRESULT	hr;
	if(m_ptColArray==NULL)	return;
	IRgbColorPtr	pColor(CLSID_RgbColor);
	pColor->put_Green(200);
	ISimpleLineSymbolPtr	pSLSymbol(CLSID_SimpleLineSymbol);
	
	pSLSymbol->put_Color(pColor);
	ISymbolPtr	 pSymbol;
	pSymbol=pSLSymbol;
	
	//点设置
	
	IRgbColorPtr	pPointColor(CLSID_RgbColor);
	pPointColor->put_Green(200);
	ISimpleMarkerSymbolPtr  pMarkerSymbol(CLSID_SimpleMarkerSymbol);
	pMarkerSymbol->put_Color(pPointColor);
	pMarkerSymbol->put_Style(esriSMSSquare);
	pMarkerSymbol->put_Size(4.0);
	
	ISymbolPtr pPointSymbol = static_cast<ISymbolPtr>(pMarkerSymbol);
	
	//第一点
	IRgbColorPtr	pEndPointColor(CLSID_RgbColor);
	pEndPointColor->put_Red(255);
	ISimpleMarkerSymbolPtr  pEndPointMarkerSymbol(CLSID_SimpleMarkerSymbol);
	pEndPointMarkerSymbol->put_Color(pEndPointColor);
	pEndPointMarkerSymbol->put_Style(esriSMSSquare);
	pEndPointMarkerSymbol->put_Size(4.0);
	ISymbolPtr pEndPointSymbol = static_cast<ISymbolPtr>(pEndPointMarkerSymbol);
	


	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(pPointSymbol);

/*	IGeometryCollectionPtr	pGeoCol(CLSID_GeometryBag);
	long nGeoConut;
	m_pGeoTracker->get_GeometryCount(&nGeoConut);
	IGeometryPtr	pTempGeo;
	m_pGeoTracker->get_Geometry(nGeoConut-1,&pTempGeo);

	pGeoCol=pTempGeo;
*/
	long nPartCount;
	m_ptColArray->get_Count(&nPartCount);

	for(long l=0;l<nPartCount;l++)
	{
		IPointCollectionPtr	ptCol;
		
		m_ptColArray->get_Element(l,(IUnknown**)&ptCol);

		long ptCount;
		hr=ptCol->get_PointCount(&ptCount);
		for(long i=0;i<ptCount-1;i++)
		{
			IPointPtr	pPoint;
			hr=ptCol->get_Point(i,&pPoint);
			m_pScrD->SetSymbol(pPointSymbol);
			m_pScrD->DrawPoint(pPoint);


			IPointPtr	pNextPoint;
			ptCol->get_Point(i+1,&pNextPoint);

			IPolylinePtr	pLine(CLSID_Polyline);
			pLine->put_FromPoint(pPoint);
			pLine->put_ToPoint(pNextPoint);

			m_pScrD->SetSymbol(pSymbol);
			m_pScrD->DrawPolyline(pLine);	
		}
		
		m_pScrD->SetSymbol(pEndPointSymbol);
		IPointPtr	pEndPoint;
		ptCol->get_Point(ptCount-1,&pEndPoint);
		m_pScrD->DrawPoint(pEndPoint);
		
		IPointPtr		pStartPoint;
		ptCol->get_Point(0,&pStartPoint);
		
		IPolylinePtr	pLine(CLSID_Polyline);
		pLine->put_FromPoint(pEndPoint);
		pLine->put_ToPoint(pStartPoint);
		
		m_pScrD->SetSymbol(pSymbol);
		m_pScrD->DrawPolyline(pLine);		
	}


/*
	long Index;
	m_pGeoTracker->get_GeometryCount(&Index);

	IGeometryPtr	pGeometry;
	m_pGeoTracker->get_Geometry(Index,&pGeometry);

	IGeometryPtr	pPolyline(CLSID_Polyline);
	pPolyline=pGeometry;

	
	m_pScrD->SetSymbol(pSymbol);
	m_pScrD->DrawPolyline(pPolyline);
	*/
	m_pScrD->FinishDrawing();

}
//把捕获的点更改为拖放后的点
void CFS_ModifyPolygon::AddPointToPolygon(IPointPtr pPoint)
{
	if(m_hitSegmentIndex==-1)	return;
	IPointCollectionPtr	ptCol;

	m_ptColArray->get_Element(m_nPartIndex,(IUnknown**)&ptCol);
	ptCol->UpdatePoint(m_hitSegmentIndex,pPoint);
	
	m_ptColArray->Remove(m_nPartIndex);
	m_ptColArray->Insert(m_nPartIndex,(IUnknown*)ptCol);
	
	CreatePolygon();
	m_bIsHasModify=TRUE;
}

void CFS_ModifyPolygon::GetMouseCiecle(IPointPtr pMousePoint,IGeometry** pCirGeo)
{
	HRESULT	hr;
	ICircularArcPtr	pCircular(CLSID_CircularArc);
	
	double x,y;
	double	ldistance;
	
	ldistance=_GetMapDistance(3);
	pMousePoint->QueryCoords(&x,&y);

	IPointPtr	pRingPoint(CLSID_Point);
	pRingPoint->PutCoords(x+ldistance,y+ldistance);

	hr=pCircular->PutCoords(pMousePoint,pRingPoint,pRingPoint,esriArcClockwise);
	
	ISegmentPtr	pSegment(pCircular);
	ISegmentCollectionPtr	pSegmentCol(CLSID_Polygon);
	pSegmentCol->AddSegment(pSegment);
	IGeometryPtr	pGeometry(pSegmentCol);
	*pCirGeo=pGeometry;
	if(*pCirGeo)
		(*pCirGeo)->AddRef();
}

double CFS_ModifyPolygon::_GetMapDistance(long lDistance)
{	
	IDisplayTransformationPtr pDisplayTransform;
	m_pScrD->get_DisplayTransformation(&pDisplayTransform);
	
	double fDistance = 0;
	
	pDisplayTransform->FromPoints(lDistance, &fDistance);
	
	return fDistance;
}

void CFS_ModifyPolygon::CreatePolygon(IGeometryPtr pGeometry)
{
	HRESULT hr;
	IGeometryPtr	pTempGeo;
	IClonePtr		pClone,pDuplicateClone;

	pClone=pGeometry;
	hr=pClone->Clone(&pDuplicateClone);
	if(FAILED(hr))		return;
	pTempGeo=pDuplicateClone;

	m_pGeoArray.CreateInstance(CLSID_Array);
	m_pGeoArray->Add((IUnknown*)pTempGeo);

	pTempGeo->AddRef();
	
	hr=m_pGeoTracker->AddGeometry(pTempGeo,&vtMissing,&vtMissing);	
	hr=m_pGeoTracker->GeometriesChanged();
}

void CFS_ModifyPolygon::CreatePolygon()
{
	HRESULT hr;
	long nPartCount;
	m_ptColArray->get_Count(&nPartCount);
	
	IGeometryPtr	pNewGeo(CLSID_Polygon);
	IGeometryPtr	pTempGeo(CLSID_Polygon);

	ITopologicalOperatorPtr	pTopOpe;
	pTopOpe=pTempGeo;
	
	for(long l=0;l<nPartCount;l++)
	{
		ISegmentCollectionPtr	pSegCol(CLSID_Polygon);

		IPointCollectionPtr	ptCol;
		m_ptColArray->get_Element(l,(IUnknown**)&ptCol);
		
		long	ptCount;
		ptCol->get_PointCount(&ptCount);
		
		for(long i=0;i<ptCount;i++)
		{
			IPointPtr	pPoint,pNextPoint;
			ptCol->get_Point(i,&pPoint);
			if(i+1<ptCount)
			{
				ptCol->get_Point(i+1,&pNextPoint);
				ILinePtr	pLine(CLSID_Line);
				pLine->PutCoords(pPoint,pNextPoint);
				ISegmentPtr	pSegment(pLine);
				pSegCol->AddSegment(pSegment,&vtMissing,&vtMissing);
			}
		}
		IPointPtr	pEndPoint;
		ptCol->get_Point(ptCount-1,&pEndPoint);
		
		IPointPtr	pfrom;
		ptCol->get_Point(0,&pfrom);
		
		ILinePtr	pLine(CLSID_Line);
		pLine->put_FromPoint(pEndPoint);
		pLine->put_ToPoint(pfrom);
		
		ISegmentPtr	pSegment(pLine);
		pSegCol->AddSegment(pSegment,&vtMissing,&vtMissing);

		IPolygonPtr	pNewPolygon(pSegCol);
		
		pNewPolygon->SimplifyPreserveFromTo();
		pNewPolygon->Close();
		
		IGeometryPtr	pGeometry(CLSID_Polygon);
		pGeometry=pNewPolygon;
		
		pTopOpe->Union(pGeometry,&pNewGeo);
		pTopOpe=pNewGeo;
	}

	IGeometryPtr	pCloneGeo;
	IClonePtr		pClone,pDuplicateClone;
	
	pClone=pNewGeo;
	hr=pClone->Clone(&pDuplicateClone);
	if(FAILED(hr))		return;
	pCloneGeo=pDuplicateClone;

	hr=m_pGeoTracker->AddGeometry(pCloneGeo,&vtMissing,&vtMissing);
	hr=m_pGeoTracker->GeometriesChanged();
	m_pGeoArray->Add((IUnknown*)pCloneGeo);

	GetFeaturePoint(pNewGeo);
}

HRESULT CFS_ModifyPolygon::CatchLine(IPointPtr pPoint)
{
	HRESULT		hr;

	IGeometryPtr	pGeometry=NULL;
	if( m_bIsStart==TRUE)
	{
		long GeoCount;
		m_pGeoTracker->get_GeometryCount(&GeoCount);
		m_pGeoTracker->get_Geometry(GeoCount-1,&pGeometry);
	}
	else
	{
		IGeometryPtr	pMouseGeo;
		GetMouseCiecle(pPoint,& pMouseGeo);
		
		hr=GetGeomtery(pPoint,&pGeometry);
		if(FAILED(hr)) return hr;
	}
	if(pGeometry==NULL) return E_FAIL;
	
	VARIANT_BOOL bRightSide, bHit;
	long	 hitPartIndex=0,hitSegmentIndex=0;
	double	 hitDistance = 0;
	double	 fDistance=_GetMapDistance(4);
	
	IHitTestPtr		pHitTest=static_cast<IHitTestPtr>(pGeometry);
	IPointPtr pHitPoint(CLSID_Point);
	
	hr=pHitTest->HitTest(pPoint,fDistance,esriGeometryPartBoundary,pHitPoint,&hitDistance,&hitPartIndex,
								&hitSegmentIndex,&bRightSide,&bHit);
	if(FAILED(hr)) return hr;
	
	if(bHit==VARIANT_TRUE )
	{
		m_nPartIndex=hitPartIndex;
		m_ptCatch=pHitPoint;
		m_hitLineIndex=hitSegmentIndex;
		
		m_bIsCatchLine=TRUE;
		return S_OK;
	}
	m_ptCatch=NULL;
	m_hitLineIndex=-1;	
	m_bIsCatchLine=FALSE;
	return E_FAIL;
}

BOOL CFS_ModifyPolygon::IsModify()
{
	long cGeo;
	m_pGeoTracker->get_GeometryCount(&cGeo);
	if(cGeo!=0 && m_bIsHasModify==TRUE)
		return TRUE;
	else
		return FALSE;
}

void CFS_ModifyPolygon::OnInsertVertex()
{
	if(m_hitLineIndex==-1) return;
	HRESULT hr;
	IPointCollectionPtr	ptCol;
	hr=m_ptColArray->get_Element(m_nPartIndex,(IUnknown**)&ptCol);
	
	IPointCollectionPtr	ptNewCol(CLSID_Polygon);
	
	long ptCount;
	ptCol->get_PointCount(&ptCount);
	for(long i=0;i<ptCount;i++)
	{
		IPointPtr	pPoint;
		hr=ptCol->get_Point(i,&pPoint);
		hr=ptNewCol->AddPoint(pPoint);
		if(FAILED(hr)) return;
		if(m_hitLineIndex==i)
			ptNewCol->AddPoint(m_ptCatch);		
	}
	
	m_ptColArray->Remove(m_nPartIndex);
	m_ptColArray->Insert(m_nPartIndex,(IUnknown*)ptNewCol);
	
	CreatePolygon();
	m_bIsHasModify=TRUE;
	
}

void CFS_ModifyPolygon::OnUpdateInsertVertex(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bIsCatchLine);	
}

void CFS_ModifyPolygon::OnDeleteVertex() 
{
	IPointCollectionPtr	ptCol;
	m_ptColArray->get_Element(m_nPartIndex,(IUnknown**)&ptCol);
	
	long ptCount;
	ptCol->get_PointCount(&ptCount);
	
	if(ptCount<=4)
	{
		::MessageBox(NULL,"少于3个点不能构成图形！","图形编辑工具",MB_ICONSTOP);
		return;
	}
	if(m_hitSegmentIndex==0)
		ptCol->RemovePoints(ptCount-1,1);
	ptCol->RemovePoints(m_hitSegmentIndex,1);
	
	m_ptColArray->Remove(m_nPartIndex);
	m_ptColArray->Insert(m_nPartIndex,(IUnknown*)ptCol);

	CreatePolygon();
	m_bIsHasModify=TRUE;

	CMainFrame *pWnd=(CMainFrame*)AfxGetMainWnd();
	CShpEditorView *pView=(CShpEditorView*)pWnd->GetActiveView();
	
	pView->FS_Refresh();
	
}

void CFS_ModifyPolygon::OnUpdateDeleteVertex(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bIsCatch);	
}

void CFS_ModifyPolygon::OnBack() 
{
	Back();

}

void CFS_ModifyPolygon::OnUpdateBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bIsHasModify);
}

int CFS_ModifyPolygon::GetCatchType()
{
	if(m_hitSegmentIndex!=-1)
		return 1;
	if(m_hitLineIndex!=-1)
		return 2;
	return 0;
}

void CFS_ModifyPolygon::GetFeaturePoint(IGeometryPtr pGeometry)
{
	HRESULT	hr;
	IGeometryPtr	pTempGeo;
	IClonePtr		pClone,pDuplicateClone;
	
	pClone=pGeometry;
	hr=pClone->Clone(&pDuplicateClone);
	if(FAILED(hr))		return;
	pTempGeo=pDuplicateClone;

	IGeometryCollectionPtr	pGeoCol(CLSID_Polygon);
	pGeoCol=pTempGeo;

	long nArrayCount;

	m_ptColArray->get_Count(&nArrayCount);
	if(nArrayCount!=0)
	{
		m_ptColArray->RemoveAll();
	}

	long nCount;

	pGeoCol->get_GeometryCount(&nCount);
	for(long i=0;i<nCount;i++)
	{
		IGeometryPtr pPart;
		pGeoCol->get_Geometry(i,&pPart);
		

		IPointCollectionPtr	ptCol;
		ptCol=pPart;

		long ll;
		ptCol->get_PointCount(&ll);

		m_ptColArray->Add((IUnknown*)ptCol);
	}
}
