// FS_NewPolygon.cpp: implementation of the CFS_NewPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShpEditor.h"
#include "FS_NewPolygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFS_NewPolygon::CFS_NewPolygon()
{
	m_bIsFirstPoint=TRUE;
	SetSymbol();
}

CFS_NewPolygon::~CFS_NewPolygon()
{
}

void CFS_NewPolygon::Start(IPointPtr pstart)
{
	m_pPointCol.CreateInstance(CLSID_Multipoint);
	
	m_pStart=pstart;
	m_pFrom=pstart;
	m_pPrevious=pstart;
	m_pEnd=pstart;
//	DrawCurrentPoint(pstart);
	m_pPointCol->AddPoint(pstart,&vtMissing,&vtMissing);
}

void CFS_NewPolygon::AddPoint(IPointPtr pto)
{

	if(m_pStart==NULL)
	{
		Start(pto);
		return;
	}
	m_pPointCol->AddPoint(pto,&vtMissing,&vtMissing);
	m_pPrevious=pto;
	m_bIsFirstPoint=FALSE;
}

void CFS_NewPolygon::MoveTo(IPointPtr	pPoint)
{
	if(m_pStart==NULL)	return;
	if(m_pScrD==NULL)	return;
	
	if(m_bIsFirstPoint==TRUE)
	{
		InvertLine(m_pStart,m_pPrevious);
		InvertLine(m_pStart,pPoint);
		m_pPrevious=pPoint;
	}
	else
	{
		InvertDoubleLine(m_pStart,m_pPrevious,m_pEnd);
		InvertDoubleLine(m_pStart,m_pPrevious,pPoint);
		m_pEnd=pPoint;
	}
}

void CFS_NewPolygon::Stop(IGeometry **	pPolygon)
{

	long	ptCount;

	m_pPointCol->get_PointCount(&ptCount);

	ISegmentCollectionPtr	pSegCol(CLSID_Polygon);
	for(long i=0;i<ptCount;i++)
	{
		IPointPtr	pPoint,pNextPoint;
		m_pPointCol->get_Point(i,&pPoint);
		if(i+1<ptCount)
		{
			m_pPointCol->get_Point(i+1,&pNextPoint);
			ILinePtr	pLine(CLSID_Line);
			pLine->PutCoords(pPoint,pNextPoint);
			ISegmentPtr	pSegment(pLine);
			pSegCol->AddSegment(pSegment,&vtMissing,&vtMissing);
		}
	}
	IPointPtr	pEndPoint;
	m_pPointCol->get_Point(ptCount-1,&pEndPoint);

	ILinePtr	pLine(CLSID_Line);
	pLine->put_FromPoint(pEndPoint);
	pLine->put_ToPoint(m_pStart);
	
	ISegmentPtr	pSegment(pLine);
	pSegCol->AddSegment(pSegment,&vtMissing,&vtMissing);

	IPolygonPtr	pNewPolygon(pSegCol);

	pNewPolygon->SimplifyPreserveFromTo();
	pNewPolygon->Close();

	IGeometryPtr	pGeometry(pNewPolygon);
	
	(*pPolygon)=pGeometry;
	if(*pPolygon)
		(*pPolygon)->AddRef();
	Dump();

}

void CFS_NewPolygon::putref_Display(IScreenDisplayPtr pScrD)
{
	m_pScrD=pScrD;
}

void CFS_NewPolygon::putref_Symbol(ISymbolPtr pSymbol)
{
	m_pSymbol=pSymbol;
}

void CFS_NewPolygon::InvertLine(IPointPtr pfrom, IPointPtr pto)
{
	IPolylinePtr	pTempLine(CLSID_Polyline);
	pTempLine->put_FromPoint(pfrom);
	pTempLine->put_ToPoint(pto);

	m_pSymbol=m_pLSymbol;	
	m_pSymbol->put_ROP2(esriROPNot);

	m_pScrD->StartDrawing(0,esriNoScreenCache);
	m_pScrD->SetSymbol(m_pSymbol);
	m_pScrD->DrawPolyline(pTempLine);	
	m_pScrD->FinishDrawing();
}

void CFS_NewPolygon::InvertDoubleLine(IPointPtr pstart,IPointPtr pend,IPointPtr pto)
{
	IPolylinePtr	pFirstLine(CLSID_Polyline);
	IPolylinePtr	pSecondLine(CLSID_Polyline);
	
	pFirstLine->put_FromPoint(pstart);
	pFirstLine->put_ToPoint(pto);
	
	pSecondLine->put_FromPoint(pend);
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

void CFS_NewPolygon::SetSymbol()
{
	IRgbColorPtr	pColor(CLSID_RgbColor);
	pColor->put_Blue(0);
	pColor->put_Green(0);
	pColor->put_Red(0);
	
	m_pLSymbol.CreateInstance(CLSID_SimpleLineSymbol);
	m_pSFSymbol.CreateInstance(CLSID_SimpleFillSymbol);
	
	m_pLSymbol->put_Color(pColor);
	m_pSFSymbol->put_Outline(m_pLSymbol);	

	m_pSymbol= static_cast<ISymbolPtr>(m_pSFSymbol);
}


void CFS_NewPolygon::DrawLine(IPointPtr pFrom, IPointPtr pTo)
{
	ILinePtr	pLine(CLSID_Line);
	pLine->PutCoords(pFrom,pTo);

	ISegmentPtr	pSegment(pLine);
	IGeometryPtr	pGeometry(CLSID_Polyline);
	pGeometry=pLine;
}

void CFS_NewPolygon::DeleteCurrentPoint()
{
	if(m_pPointCol==NULL)	return;
	long ptCount;
	m_pPointCol->get_PointCount(&ptCount);
	if(ptCount>=1)
		m_pPointCol->RemovePoints(ptCount-1,1);
	if(ptCount>=2)
		m_pPointCol->get_Point(ptCount-2,&m_pPrevious);
	if(ptCount-2==0)
		m_bIsFirstPoint=TRUE;
	if(ptCount-1==0)
		ClearGarbage();		
}

void CFS_NewPolygon::DrawPolygon()
{
	if(m_pPointCol==NULL)	return;
	IRgbColorPtr	pColor(CLSID_RgbColor);
	pColor->put_Green(200);
	ISimpleLineSymbolPtr	pSLSymbol(CLSID_SimpleLineSymbol);
	
	pSLSymbol->put_Color(pColor);
	ISymbolPtr	 pSymbol;
	pSymbol=pSLSymbol;
	
	IRgbColorPtr	pEndLineColor(CLSID_RgbColor);
	pEndLineColor->put_Red(200);
	pEndLineColor->put_Blue(200);
	pEndLineColor->put_Green(55);

	ISimpleLineSymbolPtr	pEndSLSymbol(CLSID_SimpleLineSymbol);
	
	pEndSLSymbol->put_Color(pEndLineColor);
	ISymbolPtr	 pEndSymbol;
	pEndSymbol=pEndSLSymbol;
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
			
			
			m_pScrD->SetSymbol(pSymbol);
			if(1)
			{
				m_pPointCol->get_Point(i+1,&pToPoint);

				IPolylinePtr	pLine(CLSID_Polyline);
				pLine->put_FromPoint(pFromPoint);
				pLine->put_ToPoint(pToPoint);

				m_pScrD->DrawPolyline(pLine);
			}
		}
		else
		{
			m_pScrD->SetSymbol(pEndPointSymbol);

			IPointPtr	pEndPoint;
			m_pPointCol->get_Point(PointCount-1,&pEndPoint);
			m_pScrD->DrawPoint(pEndPoint);

			if(i>=2)
			{
				IPolylinePtr	pLine(CLSID_Polyline);
				pLine->put_FromPoint(pEndPoint);
				pLine->put_ToPoint(m_pStart);
				m_pScrD->SetSymbol(pEndSymbol);
				m_pScrD->DrawPolyline(pLine);
			}
		}
	}
	m_pScrD->FinishDrawing();
}

void CFS_NewPolygon::ClearGarbage()
{
	m_pStart=NULL;
	m_pEnd=NULL;
	m_pPrevious=NULL;
	
	m_pPointCol=NULL;
}


void CFS_NewPolygon::Dump()
{
	m_pStart=NULL;
	m_pEnd=NULL;
	m_pPrevious=NULL;
	
	m_pScrD=NULL;
	m_pPointCol=NULL;
	m_pSymbol=NULL;

}
