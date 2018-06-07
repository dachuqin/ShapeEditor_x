////////////////////////////////////////////////////////////////////////////////////
//#include "INewCircleArc.h"

typedef enum tag_BS_DrawType{	//画几何图形的方法
		BS_Polygon=0,
		BS_Arc1,
		BS_Arc2
}BS_DrawType;


class CNewCircleArc 
{
public:
	int GetDrawArcState();		//画弧过程中当前点的状态
	BOOL IsStart();
	CNewCircleArc();
	virtual ~CNewCircleArc();
	void GetCurrentArc(IGeometry** pCurrentArc);// 得到当前完成的图形

    void  Initialization();
	void  Start(IPointPtr	pstart);
	void  AddPoint(IPointPtr		pPoint);
	void  AddRadius(IPointPtr pto,double dRadius,int IsClockwise,int nArcType);
	void  MoveTo(IPointPtr	pPoint);				
	void  Stop(IGeometry **	pCircleArc);			//完成画几何图形
	void  putref_Display(IScreenDisplayPtr pScrD);
	void  putref_Symbol(ISymbolPtr	pSymbol);		
	void  DrawPolygon();							//画当前完成的图形
	void  DeleteCurrentPoint();						//删除最后一次画的点和直线或弧
	void  SelectedDrawType(BS_DrawType DrawType);	//确定下一步是画弧还是直线
	void  ClearGarbage();							//清除当前所有点和线及，恢复所有的初始状态
public:
	BOOL	GetPolygonPointCount(long *count);
	BOOL	GetPolygonPoint(long nIndex,IPoint ** point);
	BOOL	bIsDeleted;			//是否执行了取消操作（这里指执行了DeleteCurrentPoint()函数，删除了一个点）
	BOOL	bDrawArcDel;		//是否执行了取消操作（这里指执行了DeleteCurrentPoint()函数，删除了一段弧）
	BOOL	bIsHitMenu;
	BOOL	bHasHitMenu;		//是否单击过菜单上的命令
	BOOL	bISMouseDown;
protected:
	typedef enum tag_BS_CurrentPoint{ //画弧过程中当前点的状态结构
		BS_StarPoint=0,
		BS_MiddlePoint,
		BS_EndPoint
	}BS_CurrentPoint;


protected:

	BS_CurrentPoint			m_BS_CurrentPoint;	//画弧过程中当前点的状态
	BS_DrawType				m_BS_DrawType;		//当前画的图形类型
	ISegmentCollectionPtr	m_pLineCol;			//保存当前已经完成的图形的线段
	IScreenDisplayPtr	m_pScrD;
	ISymbolPtr			m_pSymbol;
	IPointPtr	m_pStart;
	IPointPtr	m_pFrom;
	IPointPtr	m_pMiddle;
	IPointPtr	m_pEnd;
	IPointCollectionPtr	m_pPointCol;			//保存图形的极点

	BS_CurrentPoint			m_BS_PrePt;

protected:
	void MoveToLine(IPointPtr pPoint);					//画Polygon时的MoveTo()
	void MoveToArc(IPointPtr pto);						//画Arc1时的MoveTo()
	void CreateLine(IPointPtr pFrom,IPointPtr pTo);		//创建一条直线并加入到m_pLineCol中
	void AddPointArc(IPointPtr pto);					//画Arc1时的AddPoint()
	void AddPointPolygon(IPointPtr pto);				//画Polygon时的AddPoint()
	void Dump();										//清除内存
	
	void SetSymbol();
	void InvertArc(IPointPtr pfrom,IPointPtr pmiddle,IPointPtr pto);		//移动过程中显示的弧
	void CreateCurrentArc(IPointPtr pfrom,IPointPtr pmiddle, IPointPtr pto);//把当前完成的弧加入到m_pLineCol中
	void InvertLine(IPointPtr pfrom,IPointPtr pto);
	void InvertDoubleLine(IPointPtr pstar,IPointPtr pfrom,IPointPtr pto);

	void DrawLine(IPointPtr pfrom, IPointPtr pto);
	void SetArcRadius(IPointPtr pto,double dRadius,int IsClockwise,int nArcType);		//设置弧的绝对终点和半径		
	void SetArcRadius(double dRadius,int IsClockwise,int nArcType);  					//设置弧的绝对半径	
};