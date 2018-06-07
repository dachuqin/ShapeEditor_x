#include "StdAfx.h"
#include "BS_NewCircleArc.h"
#include "math.h"



//////////////////////////////////////////////////////////////////////////

CNewCircleArc::CNewCircleArc()
{
	m_pFrom=NULL;
	m_pStart=NULL;
	m_pEnd=NULL;
	bIsDeleted=FALSE;
	bDrawArcDel=FALSE;
	bIsHitMenu=FALSE;
	bHasHitMenu=FALSE;
	bISMouseDown=FALSE;
}

CNewCircleArc::~CNewCircleArc()
{
	m_pLineCol=NULL;
}

void CNewCircleArc::Initialization()
{
	m_pLineCol.CreateInstance(CLSID_Polygon);
	m_pPointCol.CreateInstance(CLSID_Multipoint);
	m_BS_CurrentPoint=BS_StarPoint;
	SetSymbol();
}

void CNewCircleArc::Start(IPointPtr pstart)
{
	Initialization();

	m_pStart=pstart;
	m_pFrom=pstart;
	m_pEnd=pstart;
	m_BS_CurrentPoint=BS_StarPoint;	
	m_pPointCol->AddPoint(pstart,&vtMissing,&vtMissing);
}

void CNewCircleArc::AddPoint(IPointPtr pto)
{
	if(m_pStart==NULL)
	{
		Start(pto);
		return;
	}
	switch(m_BS_DrawType) {
	case BS_Polygon:
		{
			AddPointPolygon(pto);
		}
		break;
	case BS_Arc1:
		{
			AddPointArc(pto);
		}
		break;
	case BS_Arc2:
		{
		}
		break;
	}
	bISMouseDown=TRUE;
}

void CNewCircleArc::AddPointPolygon(IPointPtr pPoint)
{

	m_BS_CurrentPoint=BS_EndPoint;
		
	long ptCount;
	m_pPointCol->get_PointCount(&ptCount);
	IPointPtr pfrom;
	if(ptCount>=1)
	{
		m_pPointCol->get_Point(ptCount-1,&pfrom);
	}	
	m_pPointCol->AddPoint(pPoint,&vtMissing,&vtMissing);
	CreateLine(pfrom,pPoint);

	m_pEnd=pPoint;

//	m_bIsFirstPoint=FALSE;
	
}

void CNewCircleArc::AddPointArc(IPointPtr pPoint)
{
	switch(m_BS_CurrentPoint) {
	case BS_StarPoint:
	case BS_EndPoint:
		{
			m_pPointCol->AddPoint(pPoint,&vtMissing,&vtMissing);
			m_pEnd=pPoint;
			m_BS_CurrentPoint=BS_MiddlePoint;
		}
		break;
	case BS_MiddlePoint:
		{
			m_pMiddle=pPoint;
			long ptCount;
			m_pPointCol->get_PointCount(&ptCount);
			IPointPtr pfrom,pto;
			if(ptCount>=2)
			{
				m_pPointCol->get_Point(ptCount-2,&pfrom);
				m_pPointCol->get_Point(ptCount-1,&pto);
			}
			else
				return;
			CreateCurrentArc(pfrom,m_pMiddle,pto);
			m_pFrom=m_pEnd;
			m_pMiddle=NULL;
			m_BS_CurrentPoint=BS_EndPoint;
		}
		break;
	}
}

void CNewCircleArc::AddRadius(IPointPtr pto,double dRadius,int IsClockwise,int nArcType)
{
	switch(m_BS_CurrentPoint) {
	case BS_StarPoint:
	case BS_EndPoint:
		{
			m_pMiddle=pto;
			SetArcRadius(pto,dRadius, IsClockwise,nArcType);
			m_pFrom=m_pEnd;
			m_pMiddle=NULL;
			m_BS_CurrentPoint=BS_EndPoint;
			
			m_pPointCol->AddPoint(pto);
		}
		break;
	case BS_MiddlePoint:
		{
			SetArcRadius(dRadius, IsClockwise,nArcType);
			m_BS_CurrentPoint=BS_EndPoint;			
		}
		break;
	}
	bISMouseDown=TRUE;
				
}

void CNewCircleArc::MoveTo(IPointPtr pPoint)
{
	if(m_pStart==NULL)	return;
	if(m_pScrD==NULL)	return;
	
	switch(m_BS_DrawType) {
	case BS_Polygon:
		{
			MoveToLine(pPoint);
		}
		break;
	case BS_Arc1:
		{
			MoveToArc(pPoint);
		}
		break;
	case BS_Arc2:
		{
		}
		break;
	}
}

void CNewCircleArc::MoveToLine(IPointPtr pPoint)
{
	if(m_BS_CurrentPoint==BS_StarPoint)
	{
		if(bIsDeleted)
		{
			InvertLine(m_pStart,m_pEnd);
			bIsDeleted=FALSE;
			bDrawArcDel=TRUE;
		}
		if (bHasHitMenu) {
			InvertLine(m_pStart,m_pEnd);
			bHasHitMenu=FALSE;
		}
		if(!bIsHitMenu)
		{
			InvertLine(m_pStart,m_pEnd);//1
		}
		else
		{
			bIsHitMenu=FALSE;
			bHasHitMenu=TRUE;
		}			
		InvertLine(m_pStart,pPoint);
		m_pEnd=pPoint;
	}
	else
	{
		long ptCount;
		m_pPointCol->get_PointCount(&ptCount);
		IPointPtr pfrom,pto;
		if(ptCount>=1)
		{
			m_pPointCol->get_Point(ptCount-1,&pto);
		}
		else
			return;

		if(bIsDeleted)
		{
			InvertDoubleLine(m_pStart,pto,m_pEnd);			
			bIsDeleted=FALSE;

		}
		if (bHasHitMenu) 
		{
			InvertDoubleLine(m_pStart,pto,m_pEnd);
			InvertLine(m_pStart,m_pEnd);
			bHasHitMenu=FALSE;
		}
		if(!bIsHitMenu )
		{
			if(bISMouseDown)
			{
				InvertLine(m_pStart,m_pEnd);
				bISMouseDown=FALSE;
			}
			InvertDoubleLine(m_pStart,pto,m_pEnd);
		}
		else
		{
			bIsHitMenu=FALSE;
			bHasHitMenu=TRUE;
		}
		InvertDoubleLine(m_pStart,pto,pPoint);
		m_pEnd=pPoint;
	}
}

void CNewCircleArc::MoveToArc(IPointPtr pPoint)
{
	if(m_pStart==NULL) return;
	switch(m_BS_CurrentPoint) {
	case BS_StarPoint:
		{
			if(bIsDeleted)
			{
				if(m_BS_PrePt==BS_MiddlePoint)
					InvertLine(m_pStart,m_pEnd);					

				InvertLine(m_pStart,m_pEnd);
				bIsDeleted=FALSE;
				bDrawArcDel=TRUE;
			}
			if (bHasHitMenu) {
				InvertLine(m_pStart,m_pEnd);
				bHasHitMenu=FALSE;
			}
			if(!bIsHitMenu)
			{
				if(bISMouseDown)
				{
					InvertLine(m_pStart,m_pEnd);//1
					bISMouseDown=FALSE;			
				}				
				InvertLine(m_pStart,m_pEnd);
			}
			else
			{
				bIsHitMenu=FALSE;
				bHasHitMenu=TRUE;
			}			
			InvertLine(m_pStart,pPoint);
			m_pEnd=pPoint;
		}
		break;
	case BS_MiddlePoint:
		{
			long ptCount;
			m_pPointCol->get_PointCount(&ptCount);
			IPointPtr pfrom,pto;
			if(ptCount>=2)
			{
				m_pPointCol->get_Point(ptCount-2,&pfrom);
				m_pPointCol->get_Point(ptCount-1,&pto);
			}
			else
				break;
			
			if(bDrawArcDel)
			{
				//InvertLine(m_pStart,m_pEnd);
				InvertArc(pfrom,m_pMiddle,pto);
				bIsDeleted=FALSE;
				bDrawArcDel=FALSE;
				
			}

			if (bHasHitMenu) 
			{
				InvertArc(pfrom,m_pMiddle,pto);
				bHasHitMenu=FALSE;
			}
			
			if(!bIsHitMenu)
			{
				if(bISMouseDown)
				{
					DrawLine(m_pStart,m_pEnd);
				}
				
				InvertArc(pfrom,m_pMiddle,pto);
			}
			else
			{
				bIsHitMenu=FALSE;
				bHasHitMenu=TRUE;
			}
			InvertArc(pfrom,pPoint,pto);
			m_pMiddle=pPoint;
		}
		break;
	case BS_EndPoint:
		{
			long ptCount;
			m_pPointCol->get_PointCount(&ptCount);
			IPointPtr pfrom,pto;
			if(ptCount>=1)
			{
				m_pPointCol->get_Point(ptCount-1,&pto);
			}

			if(bIsDeleted)
			{
				if(m_BS_PrePt==BS_MiddlePoint)
					InvertLine(m_pStart,m_pEnd);					
				InvertDoubleLine(m_pStart,pto,m_pEnd);
				bIsDeleted=FALSE;
				bDrawArcDel=TRUE;
			}
			if (bHasHitMenu) 
			{
				InvertLine(m_pStart,m_pEnd);
				InvertDoubleLine(m_pStart,pto,m_pEnd);
				bHasHitMenu=FALSE;
			}
			if(!bIsHitMenu)
			{
				if(bISMouseDown)
				{
					InvertLine(m_pStart,m_pEnd);
					bISMouseDown=FALSE;
				}
				
				InvertDoubleLine(m_pStart,pto,m_pEnd);
			}
			else
			{
				bIsHitMenu=FALSE;
				bHasHitMenu=TRUE;
			}
			InvertDoubleLine(m_pStart,pto,pPoint);
			m_pEnd=pPoint;			
		}
		break;
	}	
}

void CNewCircleArc::Stop(IGeometry **	pCircleArc)
{
	m_pStart=NULL;
	m_pScrD=NULL;
	IGeometryPtr	pGeometry(m_pLineCol);
	long	cGeo;
	m_pLineCol->get_SegmentCount(&cGeo);

	long ptCount;
	m_pPointCol->get_PointCount(&ptCount);

	ITopologicalOperatorPtr	pTopPer;
	pTopPer=pGeometry;
	pTopPer->Simplify();
	
	(*pCircleArc)=pGeometry;
	if(*pCircleArc)
		(*pCircleArc)->AddRef();
	Dump();
}

void CNewCircleArc::putref_Display(IScreenDisplayPtr pScrD)
{
	m_pScrD=pScrD;
}

void CNewCircleArc::putref_Symbol(ISymbolPtr	pSymbol)
{
	m_pSymbol=pSymbol;
}

void CNewCircleArc::InvertLine(IPointPtr pfrom, IPointPtr pto)
{
	IPolylinePtr	pTempLine(CLSID_Polyline);
	pTempLine->put_FromPoint(pfrom);
	pTempLine->put_ToPoint(pto);

	m_pSymbol->put_ROP2(esriROPXOrPen);

	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(m_pSymbol);
	m_pScrD->DrawPolyline(pTempLine);	
	m_pScrD->FinishDrawing();
}

void CNewCircleArc::DrawLine(IPointPtr pfrom, IPointPtr pto)
{
	IPolylinePtr	pTempLine(CLSID_Polyline);
	pTempLine->put_FromPoint(pfrom);
	pTempLine->put_ToPoint(pto);
	
	IRgbColorPtr	pColor(CLSID_RgbColor);
	
	pColor->put_Green(200);
	ISimpleLineSymbolPtr	pSLSymbol(CLSID_SimpleLineSymbol);
	
	pSLSymbol->put_Color(pColor);
	ISymbolPtr	 pSymbol;
	pSymbol=pSLSymbol;
	
	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(pSymbol);
	m_pScrD->DrawPolyline(pTempLine);	
	m_pScrD->FinishDrawing();
}

void CNewCircleArc::CreateCurrentArc(IPointPtr pfrom, IPointPtr pmiddle, IPointPtr pto)
{
//	HRESULT hr;
	ICircularArcPtr	pArc(CLSID_CircularArc);
	IConstructCircularArcPtr	pConCirArc(CLSID_CircularArc);

	pConCirArc->ConstructThreePoints(pfrom,pmiddle,pto,VARIANT_TRUE);
	pArc=pConCirArc;

	ISegmentPtr	pSegment(pArc);	
	m_pLineCol->AddSegment(pSegment,&vtMissing,&vtMissing);
//	m_pPointCol->AddPoint(pto);
}

void CNewCircleArc::CreateLine(IPointPtr pFrom, IPointPtr pTo)
{
	ILinePtr	pLine(CLSID_Line);
	pLine->PutCoords(pFrom,pTo);
	ISegmentPtr	pSegment(pLine);

	m_pLineCol->AddSegment(pSegment,&vtMissing,&vtMissing);	
}

void CNewCircleArc::SetArcRadius(IPointPtr pto,double dRadius,int IsClockwise,int nArcType)
{
	HRESULT hr;
	if(m_pPointCol==NULL) return;

	long	ptCount;
	IPointPtr pfrom;

	hr=m_pPointCol->get_PointCount(&ptCount);
	hr=m_pPointCol->get_Point(ptCount-1,&pfrom);

	ICircularArcPtr	pArc(CLSID_CircularArc);
	IConstructCircularArcPtr	pConCirArc(CLSID_CircularArc);
	if(IsClockwise==1)
	{
		if(nArcType==1)
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_TRUE,dRadius,VARIANT_FALSE);
		else
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_TRUE,dRadius,VARIANT_TRUE);
	}
	else
	{
		if(nArcType==1)
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_FALSE,dRadius,VARIANT_FALSE);
		else
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_FALSE,dRadius,VARIANT_TRUE);
	}	pArc=pConCirArc;
	
	ISegmentPtr	pSegment(pArc);
	
	hr=m_pLineCol->AddSegment(pSegment,&vtMissing,&vtMissing);
}


void CNewCircleArc::SetArcRadius(double dRadius, int IsClockwise,int nArcType)
{
	HRESULT hr;
	if(m_pPointCol==NULL) return;
	
	long	ptCount;
	IPointPtr pfrom,pto;
	
	hr=m_pPointCol->get_PointCount(&ptCount);
	hr=m_pPointCol->get_Point(ptCount-2,&pfrom);
	hr=m_pPointCol->get_Point(ptCount-1,&pto);

	ICircularArcPtr	pArc(CLSID_CircularArc);
	IConstructCircularArcPtr	pConCirArc(CLSID_CircularArc);
	if(IsClockwise==1)
	{
		if(nArcType==1)
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_TRUE,dRadius,VARIANT_FALSE);
		else
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_TRUE,dRadius,VARIANT_TRUE);
	}
	else
	{
		if(nArcType==1)
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_FALSE,dRadius,VARIANT_FALSE);
		else
			hr=pConCirArc->ConstructEndPointsRadius(pfrom,pto,VARIANT_FALSE,dRadius,VARIANT_TRUE);
	}

	pArc=pConCirArc;
	
	ISegmentPtr	pSegment(pArc);
	
	hr=m_pLineCol->AddSegment(pSegment,&vtMissing,&vtMissing);
}

void CNewCircleArc::InvertArc(IPointPtr pfrom, IPointPtr pmiddle, IPointPtr pto)
{
	ICircularArcPtr	pArc(CLSID_CircularArc);
	IConstructCircularArcPtr	pConCirArc(CLSID_CircularArc);
	
	pConCirArc->ConstructThreePoints(pfrom,pmiddle,pto,VARIANT_TRUE);
	pArc=pConCirArc;

	ISegmentPtr	pSegment(pArc);
	ISegmentCollectionPtr	pSegmentCol(CLSID_Polyline);
	pSegmentCol->AddSegment(pSegment);
	IGeometryPtr	pGeometry(pSegmentCol);

	m_pSymbol->put_ROP2(esriROPXOrPen);
	
	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(m_pSymbol);
	m_pScrD->DrawPolyline(pGeometry);	
	m_pScrD->FinishDrawing();
	m_pScrD->RemoveAllCaches();
}

void CNewCircleArc::InvertDoubleLine(IPointPtr pstar,IPointPtr pend,IPointPtr pto)
{
	IPolylinePtr	pFirstLine(CLSID_Polyline);
	IPolylinePtr	pSecondLine(CLSID_Polyline);

	pFirstLine->put_FromPoint(pstar);
	pFirstLine->put_ToPoint(pto);
	
	pSecondLine->put_FromPoint(pend);
	pSecondLine->put_ToPoint(pto);

	m_pSymbol->put_ROP2(esriROPXOrPen);
	
	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(m_pSymbol);
	m_pScrD->DrawPolyline(pFirstLine);	
	m_pScrD->DrawPolyline(pSecondLine);	
	m_pScrD->FinishDrawing();	
}

void CNewCircleArc::SetSymbol()
{
	IRgbColorPtr	pColor(CLSID_RgbColor);
	pColor->put_Blue(255);
	pColor->put_Green(55);
	pColor->put_Red(255);

	ISimpleLineSymbolPtr	pSLSymbol(CLSID_SimpleLineSymbol);
	pSLSymbol->put_Color(pColor);

	m_pSymbol=pSLSymbol;	
}

void CNewCircleArc::GetCurrentArc(IGeometry **pCurrentArc)
{
	IGeometryPtr	pGeo(m_pLineCol);
	(*pCurrentArc)=pGeo;
	if(*pCurrentArc)
		(*pCurrentArc)->AddRef();
}

void CNewCircleArc::DeleteCurrentPoint()
{

	if(m_pPointCol==NULL)	return;
	switch(m_BS_DrawType) {
	case BS_Polygon:
		{
			long ptCount;
			m_pPointCol->get_PointCount(&ptCount);
			if(ptCount>=1)
			{
				m_pPointCol->RemovePoints(ptCount-1,1);
				if(ptCount-2>=0)
					m_pPointCol->get_Point(ptCount-2,&m_pEnd);
				long	SegmentCount;
				m_pLineCol->get_SegmentCount(&SegmentCount);						
				if(SegmentCount>=1)
				{
					m_pLineCol->RemoveSegments(SegmentCount-1,1,VARIANT_TRUE);
				}
			}
			m_pPointCol->get_PointCount(&ptCount);
			if(ptCount==0)
			{
				ClearGarbage();
				return;
			}
			if(ptCount==1)
			{
				m_BS_CurrentPoint=BS_StarPoint;
				bIsDeleted=TRUE;
				
				return;
			}
			
			m_BS_CurrentPoint=BS_EndPoint;

		}
		break;
	case BS_Arc1:
		{
			m_BS_PrePt=m_BS_CurrentPoint;
			switch(m_BS_CurrentPoint) {
			case BS_StarPoint:
				{
					ClearGarbage();
				}
				break;
			case BS_EndPoint:
				{
					long ptCount;
					m_pPointCol->get_PointCount(&ptCount);
					if(ptCount>=1)
					{
						m_pPointCol->RemovePoints(ptCount-1,1);
						
						long	SegmentCount;
						m_pLineCol->get_SegmentCount(&SegmentCount);						
						if(SegmentCount>=1)
						{
							m_pLineCol->RemoveSegments(SegmentCount-1,1,VARIANT_FALSE);
						}
					}
					m_pPointCol->get_PointCount(&ptCount);
					if(ptCount==0)
					{
						ClearGarbage();
						return;
					}
					if(ptCount==1)
					{
						m_BS_CurrentPoint=BS_StarPoint;
						bIsDeleted=TRUE;
						
						return;
					}
					m_BS_CurrentPoint=BS_EndPoint;
				}
				break;
			case BS_MiddlePoint:
				{
					long ptCount;
					m_pPointCol->get_PointCount(&ptCount);
					if(ptCount>=1)
					{
						m_pPointCol->RemovePoints(ptCount-1,1);
						
						long	SegmentCount;
						m_pLineCol->get_SegmentCount(&SegmentCount);						
					//	if(SegmentCount>=1)
					//	{
					//		m_pLineCol->RemoveSegments(SegmentCount-1,1,VARIANT_FALSE);
					//	}
					}
					m_pPointCol->get_PointCount(&ptCount);
					if(ptCount==0)
					{
						ClearGarbage();
						return;
					}
					if(ptCount==1)
					{
						m_BS_CurrentPoint=BS_StarPoint;
						bIsDeleted=TRUE;
						
						return;
					}
					
					m_BS_CurrentPoint=BS_EndPoint;
					
				}
				break;
			}	
			
		}
		break;
	}
	bIsDeleted=TRUE;
}

void CNewCircleArc::DrawPolygon()
{
	if(m_pPointCol==NULL)	return;
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
	
	//最后一点
	IRgbColorPtr	pEndPointColor(CLSID_RgbColor);
	pEndPointColor->put_Red(255);
	ISimpleMarkerSymbolPtr  pEndPointMarkerSymbol(CLSID_SimpleMarkerSymbol);
	pEndPointMarkerSymbol->put_Color(pEndPointColor);
	pEndPointMarkerSymbol->put_Style(esriSMSSquare);
	pEndPointMarkerSymbol->put_Size(4.0);
	ISymbolPtr pEndPointSymbol = static_cast<ISymbolPtr>(pEndPointMarkerSymbol);
	
	m_pScrD->StartDrawing(0,esriNoScreenCache);
	
	long PointCount;
	m_pPointCol->get_PointCount(&PointCount);
	for(long i=0;i<PointCount;i++)
	{
		IPointPtr	pFromPoint,pToPoint;
		if(i<PointCount-1 )
		{
			m_pPointCol->get_Point(i,&pFromPoint);
			
			m_pScrD->SetSymbol(pPointSymbol);
			m_pScrD->DrawPoint(pFromPoint);				
		}
		else
		{
			m_pScrD->SetSymbol(pEndPointSymbol);
			
			IPointPtr	pEndPoint;
			m_pPointCol->get_Point(PointCount-1,&pEndPoint);
			m_pScrD->DrawPoint(pEndPoint);		
		}
	}
	IPolygonPtr	pPolygon(m_pLineCol);

	IClonePtr	pClone,pCloneBack;
	IPolygonPtr pPolygonBack;

	pClone=pPolygon;
	pClone->Clone(&pCloneBack);
	pPolygonBack=pCloneBack;

	pPolygonBack->Close();

	IGeometryPtr	pGeo;
	pGeo=pPolygonBack;

	m_pScrD->SetSymbol(pSymbol);
	
	m_pScrD->DrawPolyline(pGeo);
	
/*	IPointPtr	pFirstPoint;
	IPointPtr	pFinishPoint;
	
	if(PointCount>0)
		m_pPointCol->get_Point(0,&pFirstPoint);
	if(PointCount-2=0)
		m_pPointCol->get_Point(PointCount-1,&pFinishPoint);

	ILinePtr	pLine(CLSID_Line);
	pLine->PutCoords(pFirstPoint,pFinishPoint);
	m_pScrD->DrawPolyline(pLine);
*/	
	m_pScrD->FinishDrawing();
}

void CNewCircleArc::ClearGarbage()
{
	m_BS_CurrentPoint=BS_StarPoint;
	m_pStart=NULL;
	m_pEnd=NULL;
	m_pMiddle=NULL;
	if(m_pPointCol!=NULL)
	{
		long	ptCount;
		m_pPointCol->get_PointCount(&ptCount);
		m_pPointCol->RemovePoints(0,ptCount);
	}
	m_pPointCol=NULL;

	if(m_pLineCol!=NULL)
	{
		long	SegmentCount;
		m_pLineCol->get_SegmentCount(&SegmentCount);
		m_pLineCol->RemoveSegments(0,SegmentCount-1,VARIANT_FALSE);
	}
	m_pLineCol=NULL;
	bIsDeleted=FALSE;
	bDrawArcDel=FALSE;
	bIsHitMenu=FALSE;
	bHasHitMenu=FALSE;
	bISMouseDown=FALSE;
}

void CNewCircleArc::Dump()
{
	m_pStart=NULL;
	m_pEnd=NULL;
	m_pMiddle=NULL;
	m_pPointCol=NULL;
	m_pLineCol=NULL;
	m_pSymbol=NULL;
	m_pScrD=NULL;
	bIsDeleted=FALSE;
	bDrawArcDel=FALSE;
	bIsHitMenu=FALSE;
	bHasHitMenu=FALSE;
}

void CNewCircleArc::SelectedDrawType(BS_DrawType DrawType)
{
	m_BS_DrawType=DrawType;
}

BOOL CNewCircleArc::IsStart()
{
	if(m_pStart==NULL)
		return FALSE;
	else
		return TRUE;
}


int CNewCircleArc::GetDrawArcState()
{
	int nState=0;
	switch(m_BS_CurrentPoint) {
	case BS_StarPoint:
	case BS_EndPoint:
		nState=1;
		break;
	case BS_MiddlePoint:
		nState=2;
		break;
	}
	return nState;
}

BOOL CNewCircleArc::GetPolygonPoint(long nIndex,IPoint ** point)
{
	if(m_pPointCol==NULL) return FALSE;
	long count;
	m_pPointCol->get_PointCount(&count);
	if(nIndex>count-1)
	{
		AfxMessageBox("超出了点集的范围");
		return FALSE;
	}
	m_pPointCol->get_Point(nIndex,point);
	if(*point)
	{
		(*point)->AddRef();
		return TRUE;
	}
	return FALSE;
}

BOOL CNewCircleArc::GetPolygonPointCount(long *count)
{
	if(m_pPointCol==NULL) return FALSE;
	m_pPointCol->get_PointCount(count);
	return TRUE;
}
