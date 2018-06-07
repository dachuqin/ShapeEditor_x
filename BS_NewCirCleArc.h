////////////////////////////////////////////////////////////////////////////////////
//#include "INewCircleArc.h"

typedef enum tag_BS_DrawType{	//������ͼ�εķ���
		BS_Polygon=0,
		BS_Arc1,
		BS_Arc2
}BS_DrawType;


class CNewCircleArc 
{
public:
	int GetDrawArcState();		//���������е�ǰ���״̬
	BOOL IsStart();
	CNewCircleArc();
	virtual ~CNewCircleArc();
	void GetCurrentArc(IGeometry** pCurrentArc);// �õ���ǰ��ɵ�ͼ��

    void  Initialization();
	void  Start(IPointPtr	pstart);
	void  AddPoint(IPointPtr		pPoint);
	void  AddRadius(IPointPtr pto,double dRadius,int IsClockwise,int nArcType);
	void  MoveTo(IPointPtr	pPoint);				
	void  Stop(IGeometry **	pCircleArc);			//��ɻ�����ͼ��
	void  putref_Display(IScreenDisplayPtr pScrD);
	void  putref_Symbol(ISymbolPtr	pSymbol);		
	void  DrawPolygon();							//����ǰ��ɵ�ͼ��
	void  DeleteCurrentPoint();						//ɾ�����һ�λ��ĵ��ֱ�߻�
	void  SelectedDrawType(BS_DrawType DrawType);	//ȷ����һ���ǻ�������ֱ��
	void  ClearGarbage();							//�����ǰ���е���߼����ָ����еĳ�ʼ״̬
public:
	BOOL	GetPolygonPointCount(long *count);
	BOOL	GetPolygonPoint(long nIndex,IPoint ** point);
	BOOL	bIsDeleted;			//�Ƿ�ִ����ȡ������������ִָ����DeleteCurrentPoint()������ɾ����һ���㣩
	BOOL	bDrawArcDel;		//�Ƿ�ִ����ȡ������������ִָ����DeleteCurrentPoint()������ɾ����һ�λ���
	BOOL	bIsHitMenu;
	BOOL	bHasHitMenu;		//�Ƿ񵥻����˵��ϵ�����
	BOOL	bISMouseDown;
protected:
	typedef enum tag_BS_CurrentPoint{ //���������е�ǰ���״̬�ṹ
		BS_StarPoint=0,
		BS_MiddlePoint,
		BS_EndPoint
	}BS_CurrentPoint;


protected:

	BS_CurrentPoint			m_BS_CurrentPoint;	//���������е�ǰ���״̬
	BS_DrawType				m_BS_DrawType;		//��ǰ����ͼ������
	ISegmentCollectionPtr	m_pLineCol;			//���浱ǰ�Ѿ���ɵ�ͼ�ε��߶�
	IScreenDisplayPtr	m_pScrD;
	ISymbolPtr			m_pSymbol;
	IPointPtr	m_pStart;
	IPointPtr	m_pFrom;
	IPointPtr	m_pMiddle;
	IPointPtr	m_pEnd;
	IPointCollectionPtr	m_pPointCol;			//����ͼ�εļ���

	BS_CurrentPoint			m_BS_PrePt;

protected:
	void MoveToLine(IPointPtr pPoint);					//��Polygonʱ��MoveTo()
	void MoveToArc(IPointPtr pto);						//��Arc1ʱ��MoveTo()
	void CreateLine(IPointPtr pFrom,IPointPtr pTo);		//����һ��ֱ�߲����뵽m_pLineCol��
	void AddPointArc(IPointPtr pto);					//��Arc1ʱ��AddPoint()
	void AddPointPolygon(IPointPtr pto);				//��Polygonʱ��AddPoint()
	void Dump();										//����ڴ�
	
	void SetSymbol();
	void InvertArc(IPointPtr pfrom,IPointPtr pmiddle,IPointPtr pto);		//�ƶ���������ʾ�Ļ�
	void CreateCurrentArc(IPointPtr pfrom,IPointPtr pmiddle, IPointPtr pto);//�ѵ�ǰ��ɵĻ����뵽m_pLineCol��
	void InvertLine(IPointPtr pfrom,IPointPtr pto);
	void InvertDoubleLine(IPointPtr pstar,IPointPtr pfrom,IPointPtr pto);

	void DrawLine(IPointPtr pfrom, IPointPtr pto);
	void SetArcRadius(IPointPtr pto,double dRadius,int IsClockwise,int nArcType);		//���û��ľ����յ�Ͱ뾶		
	void SetArcRadius(double dRadius,int IsClockwise,int nArcType);  					//���û��ľ��԰뾶	
};