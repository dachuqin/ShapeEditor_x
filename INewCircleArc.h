interface INewCircleArc :public IDisplayFeedback 
{	
    virtual HRESULT __stdcall Start(IPointPtr	pPoint)=0;
	virtual HRESULT __stdcall Add(IPointPtr		pPoint)=0;
	virtual HRESULT __stdcall Stop(IGeometry **	pCircleArc)=0;
};