// FS_NewPolygon.h: interface for the CFS_NewPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FS_NEWPOLYGON_H__D1A8023A_CD98_40C4_955D_7DC3CC1B7CC9__INCLUDED_)
#define AFX_FS_NEWPOLYGON_H__D1A8023A_CD98_40C4_955D_7DC3CC1B7CC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFS_NewPolygon  
{
public:

	CFS_NewPolygon();
	virtual ~CFS_NewPolygon();

	void  Start(IPointPtr	pstart);
	void  AddPoint(IPointPtr		pPoint);
	void  MoveTo(IPointPtr	pPoint);
	void  Stop(IGeometry **	pCircleArc);
	void  putref_Display(IScreenDisplayPtr pScrD);
	void  putref_Symbol(ISymbolPtr	pSymbol);
	void  DeleteCurrentPoint();		//ɾ����󻭵�һ����
	void  DrawPolygon();			//����ǰ�Ѿ����εĶ����
	
protected:
	IScreenDisplayPtr		m_pScrD;
	ISymbolPtr				m_pSymbol;
	ISimpleFillSymbolPtr 	m_pSFSymbol;
	ILineSymbolPtr			m_pLSymbol;
	
	IPointCollectionPtr		m_pPointCol;
	IPointPtr	m_pStart;
	IPointPtr	m_pFrom;
	IPointPtr	m_pPrevious;
	IPointPtr	m_pEnd;

	BOOL		m_bIsFirstPoint;
	
protected:
	void Dump();
	void ClearGarbage();
	void DrawLine(IPointPtr pFrom,IPointPtr pTo);
//	void DrawCurrentPoint(IPointPtr pPoint);//����ǰ�㣨��ɫ��
//	void DrawPreviousPoint(IPointPtr pPoint);//����һ�㣨��ɫ��
	
	void SetSymbol();
	void InvertLine(IPointPtr pfrom,IPointPtr pto);
	void InvertDoubleLine(IPointPtr pstar,IPointPtr pfrom,IPointPtr pto);
};

#endif // !defined(AFX_FS_NEWPOLYGON_H__D1A8023A_CD98_40C4_955D_7DC3CC1B7CC9__INCLUDED_)
