// ShpEditorDoc.cpp : implementation of the CShpEditorDoc class
//

#include "stdAfx.h"
#include "ShpEditor.h"

#include "ShpEditorDoc.h"
#include "comutil.h"
#include "MainFrm.h"
#include "ShpEditorView.h"
#include "FS_MergeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShpEditorDoc

IMPLEMENT_DYNCREATE(CShpEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CShpEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CShpEditorDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShpEditorDoc construction/destruction

CShpEditorDoc::CShpEditorDoc()
{
	
}

CShpEditorDoc::~CShpEditorDoc()
{
}

BOOL CShpEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CShpEditorDoc serialization

void CShpEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShpEditorDoc diagnostics

#ifdef _DEBUG
void CShpEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShpEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShpEditorDoc commands

HRESULT CShpEditorDoc::AddShp(CString *strName)
{
	HRESULT	hr;
	IGxDialogPtr	pGxDialog(CLSID_GxDialog);
	IGxObjectFilterCollectionPtr	pGOFColl(pGxDialog);//得到GxDialog对象的IGxObjectFilterCollction接口以方便设置Filter
	IGxObjectFilterPtr		pGxObjFilter(CLSID_GxFilterDatasets);
	//将一个IGxObjectFilter对象添加到GxDialog
	pGOFColl->AddFilter(pGxObjFilter,TRUE);//设置为TRUE，表示pGXObjFilter为默认的Filter
	
	IGxObjectFilterPtr		pGOFilter(CLSID_GxFilterFiles);//添加另一个Filter对象
	pGOFColl->AddFilter(pGOFilter,FALSE);
	
	pGxDialog->put_AllowMultiSelect(VARIANT_TRUE);//设置为多选
	pGxDialog->put_Title(CComBSTR("加入图层"));
	
	IEnumGxObjectPtr	pEnumGXObject;
	VARIANT_BOOL		bResult;
	hr=pGxDialog->DoModalOpen(0,&pEnumGXObject,&bResult);//打开对话框
	if(FAILED(hr))	return hr;

	if(bResult==VARIANT_FALSE)	return E_FAIL;	
	
	IGxObjectPtr		pGxObjectPath;	
	hr=pGxDialog->get_FinalLocation(&pGxObjectPath);
	if(FAILED(hr))	return hr;
	
	BSTR	bShpPath,bShpName;
	hr=pGxObjectPath->get_FullName(&bShpPath);	//得到存储路径
	if(FAILED(hr))	return hr;
	
	hr=pEnumGXObject->Reset();
	if(FAILED(hr))	return hr;

	IFeatureLayerPtr	pFeaLayer(CLSID_FeatureLayer);
	IGxObjectPtr		pGxObject;
	IWorkspacePtr	pWorkspace;
	while (!pEnumGXObject->Next(&pGxObject))
	{		
		IGxDatasetPtr	pGxDataset(pGxObject);
		
		if(pGxDataset!=0)
		{
			IDatasetPtr	pDataset;
			hr=pGxDataset->get_Dataset(&pDataset);
			if(FAILED(hr))	return hr;
			m_pDataset=pDataset;//保存数据集

			hr=pDataset->get_Workspace(&pWorkspace);
			if(FAILED(hr))	return hr;
			m_pWorkspace=pWorkspace;// 保存工作区
			
			IFeatureClassPtr	pFeaClass(pDataset);
			pFeaClass->get_AliasName(&bShpName);//得到存储文件名

			CString stempName;
			stempName=(LPCWSTR)bShpName;
			*strName=stempName;
			
			hr=pFeaLayer->putref_FeatureClass(pFeaClass);
			if(FAILED(hr))	return hr;
			hr=pFeaLayer->put_Visible(VARIANT_TRUE);
			if(FAILED(hr))	return hr;
			m_pEditLayer=pFeaLayer;// 保存编辑层
		}
	}

	return S_OK;
}

///////////***********新建一个shpfile***************//////////////////////

HRESULT CShpEditorDoc::NewShpFile(CString *strName,IFeatureClass** pFeaClass) 
{
	HRESULT	hr;
	VARIANT_BOOL	vtResult;
	
	IGxDialogPtr	pGxDialog(CLSID_GxDialog);
	pGxDialog->put_Title(CComBSTR("新建图层"));
	
	hr=pGxDialog->DoModalSave(0,&vtResult);//打开存储对话框
	if(FAILED(hr))	return hr;
	if(vtResult==VARIANT_FALSE)	return E_FAIL;
	
	BSTR	BShpName,BshpPath;
	
	IGxObjectPtr	pGxObject;
	hr=pGxDialog->get_FinalLocation(&pGxObject);
	if(FAILED(hr))	return hr;
	hr=pGxObject->get_FullName(&BshpPath);	//得到存储路径
	if(FAILED(hr))	return hr;
	hr=pGxDialog->get_Name(&BShpName);			//得到存储文件名
	if(FAILED(hr))	return hr;
	CString stempName;
	stempName=(LPCWSTR)BShpName;
	*strName=stempName;
	
	//新建一个shpfile
	hr=CreateShapefile(BshpPath,BShpName,pFeaClass);
	return hr;
}

///////////***********另存为***************//////////////////////

HRESULT CShpEditorDoc::SaveASShp(IFeatureClass *pEditFeaClass,IFeatureClass** pFeaClass) 
{
	HRESULT	hr;
	VARIANT_BOOL	vtResult;
	
	IGxDialogPtr	pGxDialog(CLSID_GxDialog);
	pGxDialog->put_Title(CComBSTR("图层另存为"));
		
	hr=pGxDialog->DoModalSave(0,&vtResult);//打开存储对话框
	if(FAILED(hr))	return hr;
	if(vtResult==VARIANT_FALSE)	return E_NOINTERFACE;
	
	BSTR	BShpName,BshpPath;
	
	IGxObjectPtr	pGxObject;
	hr=pGxDialog->get_FinalLocation(&pGxObject);
	if(FAILED(hr))	return hr;
	hr=pGxObject->get_FullName(&BshpPath);	//得到存储路径
	if(FAILED(hr))	return hr;
	hr=pGxDialog->get_Name(&BShpName);			//得到存储文件名
	if(FAILED(hr))	return hr;
	CString stempName;
	stempName=(LPCWSTR)BShpName;
//	*strName=stempName;
	
	//新建一个shpfile
	hr=CreateShapefile(BshpPath,BShpName,pEditFeaClass,pFeaClass);
	return hr;
}

HRESULT CShpEditorDoc::AddReference(CString *strName) 
{
	HRESULT	hr;
	
	IGxDialogPtr	pGxDialog(CLSID_GxDialog);
	IGxObjectFilterCollectionPtr	pGOFColl(pGxDialog);//得到GxDialog对象的IGxObjectFilterCollction接口以方便设置Filter
	IGxObjectFilterPtr		pGxObjFilter(CLSID_GxFilterDatasets);
	//将一个IGxObjectFilter对象添加到GxDialog
	pGOFColl->AddFilter(pGxObjFilter,TRUE);//设置为TRUE，表示pGXObjFilter为默认的Filter
	
	IGxObjectFilterPtr		pGOFilter(CLSID_GxFilterFiles);//添加另一个Filter对象
	pGOFColl->AddFilter(pGOFilter,FALSE);
	
//	pGxDialog->put_AllowMultiSelect(VARIANT_TRUE);//设置为多选
	pGxDialog->put_Title(CComBSTR("加入参考图层"));
	
	IEnumGxObjectPtr	pEnumGXObject;
	VARIANT_BOOL		bResult;
	hr=pGxDialog->DoModalOpen(0,&pEnumGXObject,&bResult);//打开对话框
	if(FAILED(hr))	return hr;
	if(bResult==VARIANT_FALSE)	return E_FAIL;

	IGxObjectPtr		pGxObjectPath;	
	hr=pGxDialog->get_FinalLocation(&pGxObjectPath);
	if(FAILED(hr))	return hr;
	
	BSTR	bShpPath,bShpName;
	hr=pGxObjectPath->get_FullName(&bShpPath);	//得到存储路径
	if(FAILED(hr))	return hr;
	
	hr=pEnumGXObject->Reset();
	IFeatureLayerPtr	pFeaLayer(CLSID_FeatureLayer);
	IGxObjectPtr		pGxObject;
	IWorkspacePtr	pWorkspace;
	while (!pEnumGXObject->Next(&pGxObject))
	{
		IDatasetPtr	pDataset;

		IGxDatasetPtr	pGxDataset(pGxObject);
		if(pGxDataset!=0)
		{

			hr=pGxDataset->get_Dataset(&pDataset);
			if(FAILED(hr))	return hr;
			m_pDataset=pDataset;//保存数据集极口指针
			hr=pDataset->get_Workspace(&pWorkspace);
			if(FAILED(hr))	return hr;
			
			IFeatureClassPtr	pFeaClass(pDataset);
			pFeaClass->get_AliasName(&bShpName);//得到存储文件名
			
			CString stempName;
			stempName=(LPCWSTR)bShpName;
			*strName=stempName;

			hr=pFeaLayer->putref_FeatureClass(pFeaClass);
			if(FAILED(hr))	return hr;
			hr=pFeaLayer->put_Visible(VARIANT_TRUE);
			if(FAILED(hr))	return hr;
			ILayerPtr	pLayer(pFeaLayer);
			m_pRefLayer=pFeaLayer;//保存参考层
		}
	}
	return S_OK;
}

//在未打开参考图层是建立IFeatureClass的方法 
HRESULT CShpEditorDoc::CreateShapefile(	BSTR bstrPath, BSTR bstrName,IFeatureClass** ppFeatureClass)
{
	if (!ppFeatureClass)
		return E_POINTER;
	
	HRESULT hr;

	// Open the folder to contain the shapefile as a workspace
	IWorkspaceFactoryPtr ipWorkspaceFactory(CLSID_ShapefileWorkspaceFactory);
	IWorkspacePtr ipWS;
	hr = ipWorkspaceFactory->OpenFromFile(bstrPath, 0, &ipWS);
	IFeatureWorkspacePtr ipFWS(ipWS);

	m_pWorkspace=ipWS;

	// Set up a simple fields collection
	IFieldsPtr ipFields(CLSID_Fields);
	
	IFieldsEditPtr ipFieldsEdit(ipFields);
	
	// Make the shape field
	// it will need a geometry definition, with a spatial reference
	IFieldPtr ipField(CLSID_Field);
	IFieldEditPtr ipFieldEdit(ipField);
	hr = ipFieldEdit->put_Name(CComBSTR(L"Shape"));
	hr = ipFieldEdit->put_Type(esriFieldTypeGeometry);

	IGeometryDefPtr ipGeomDef(CLSID_GeometryDef);
	IGeometryDefEditPtr ipGeomDefEdit(ipGeomDef);
	
	hr = ipGeomDefEdit->put_GeometryType(esriGeometryPolygon);
	ISpatialReferencePtr ipSpatialRef(CLSID_UnknownCoordinateSystem);
	hr = ipGeomDefEdit->putref_SpatialReference(ipSpatialRef);
	hr = ipFieldEdit->putref_GeometryDef(ipGeomDef);
	hr = ipFieldsEdit->AddField(ipField);

/*	// Add another miscellaneous text field
	ipField.CreateInstance(CLSID_Field);
	ipFieldEdit = ipField;
	hr = ipFieldEdit->put_Length(30);
	hr = ipFieldEdit->put_Name(CComBSTR(L"Name"));
	hr = ipFieldEdit->put_Type(esriFieldTypeString);
	hr = ipFieldsEdit->AddField(ipField);
*/
	// Create the shapefile
	// (some parameters apply to geodatabase options and can be defaulted as Nothing)
	IFeatureClassPtr ipFeatClass;
	hr = ipFWS->CreateFeatureClass(bstrName, ipFields, 0, 0, esriFTSimple, 
									CComBSTR(L"Shape"), CComBSTR(L""), &ipFeatClass);
	
	*ppFeatureClass = ipFeatClass;
	if ((*ppFeatureClass)!=NULL)
		(*ppFeatureClass)->AddRef();
	else
		return E_FAIL;
	
	return S_OK;
}

HRESULT CShpEditorDoc::CreateShapefile(	BSTR bstrPath, BSTR bstrName,
									   IFeatureClassPtr pEditFeaClass,
									   IFeatureClass** pFeatureClass)
{
	if (!pFeatureClass)
		return E_POINTER;
	
	HRESULT hr;

	// Open the folder to contain the shapefile as a workspace
	IWorkspaceFactoryPtr ipWorkspaceFactory(CLSID_ShapefileWorkspaceFactory);
	IWorkspacePtr ipWS;
	hr = ipWorkspaceFactory->OpenFromFile(bstrPath, 0, &ipWS);
	IFeatureWorkspacePtr ipFWS(ipWS);

	m_pTempWorkspace=ipWS;
	
	// Set up a simple fields collection
	IFieldsPtr ipFields(CLSID_Fields);

	pEditFeaClass->get_Fields(&ipFields);

	IClonePtr ipClone(ipFields);
	IClonePtr ipCloned;
	ipClone->Clone(&ipCloned);

	// Create the shapefile
	// (some parameters apply to geodatabase options and can be defaulted as Nothing)
	IFeatureClassPtr ipFeatClass;
	hr = ipFWS->CreateFeatureClass(bstrName, (IFieldsPtr) ipCloned, 0, 0, esriFTSimple, 
									CComBSTR(L"Shape"), CComBSTR(L""), &ipFeatClass);
	
	*pFeatureClass = ipFeatClass;
	if ((*pFeatureClass)!=NULL)
		(*pFeatureClass)->AddRef();
	else
		return E_FAIL;
	
	return S_OK;
}
//////////**************得到选中的要素****************//////////////////////////////////////////
HRESULT	CShpEditorDoc::GetSelectedFeature(IMapPtr pMap,long *lSelectedCount,IGeometry ** pResultGeometry)
{
	HRESULT	hr;
	
	hr=pMap->get_SelectionCount(lSelectedCount);//选中要素的个数
	if(FAILED(hr))	return hr;
	if(*lSelectedCount==0)	return S_OK;
	IEnumFeaturePtr		ipEnumFeature;
	ISelectionPtr		ipSelection;
	hr=pMap->get_FeatureSelection(&ipSelection);
	if(FAILED(hr))	return hr;
	if(ipSelection==NULL)	return E_FAIL;
	ipEnumFeature=ipSelection;
	
	IGeometryPtr				ipGeometry(CLSID_Polygon);
	IGeometryCollectionPtr		ipGeometryBag(CLSID_GeometryBag);
	ITopologicalOperatorPtr		ipTopoOpt;
	
	IFeaturePtr		ipFeature;
	hr=ipEnumFeature->Next(&ipFeature);
	if(FAILED(hr))	return hr;
	
	if(ipFeature==NULL) return E_FAIL;
	
	if(*lSelectedCount==1)
	{		
		hr=ipFeature->get_Shape(pResultGeometry);
		return S_OK;	
	}

	while (!(ipFeature==0)) {
		
		IGeometryPtr	ipGeometry;
		ipFeature->get_Shape(&ipGeometry);
		
		hr=ipGeometryBag->AddGeometry(ipGeometry,&vtMissing,&vtMissing);
		if(FAILED(hr))	return hr;
		hr=ipEnumFeature->Next(&ipFeature);
		if(FAILED(hr))
			return hr;
	}
	IGeometryPtr	pTempGeo(CLSID_Polygon);
	ipTopoOpt=pTempGeo;
	
	IEnumGeometryPtr	ipEnumGeometry(ipGeometryBag);
	hr=ipTopoOpt->ConstructUnion(ipEnumGeometry);
	if(FAILED(hr))	return hr;
	*pResultGeometry=pTempGeo;
	(*pResultGeometry)->AddRef();//COM对象的计数器
	return S_OK;
}

HRESULT CShpEditorDoc::MoveSelectedFeature(IMapPtr	pMap,IFeatureLayerPtr pEditLayer,
										   IPointPtr  fromPoint,IPointPtr  toPoint)
{
	HRESULT hr;
	ISetPtr			pSet(CLSID_Set);
	IEnumFeaturePtr	pEnumFeature;
	IFeaturePtr		pFeature;
	IFeatureEditPtr	pFeatureEdit;
	ISelectionPtr	pSelection;

	pMap->get_FeatureSelection(&pSelection);
	pEnumFeature=pSelection;
	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	hr;

	while (!(pFeature==NULL)) 
	{
		//
		BOOL	bIsRefLayer;
		bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
		if(bIsRefLayer)
		{
			::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
			return E_FAIL;
			
		}
		
		pFeatureEdit=pFeature;
		pSet->Add(pFeature);
		pEnumFeature->Next(&pFeature);
	}
	ILinePtr pLine(CLSID_Line);
	pLine->PutCoords(fromPoint,toPoint);//设置移动路线
	
	hr=pFeatureEdit->BeginMoveSet(pSet,fromPoint,NULL);//移动图形
	hr=pFeatureEdit->MoveSet(pSet,pLine);
	if(FAILED(hr))	hr;

	return S_OK;
}

HRESULT CShpEditorDoc::DeleFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer)
{
	
	HRESULT		hr;
	ISetPtr				pDelSet(CLSID_Set);
	IEnumFeaturePtr		pEnumFeature;
	IFeaturePtr			pFeature;
	IFeatureEditPtr		pFeatureEdit;
	ISelectionPtr		pSelection;
	
	
	pMap->get_FeatureSelection(&pSelection);
	pEnumFeature=pSelection;
	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	return hr;
	if(pFeature==NULL)	return E_FAIL;
	while (!(pFeature==NULL)) 
	{
		//判断是否是参考层要素
		BOOL	bIsRefLayer;
		bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
		if(bIsRefLayer)
		{
			::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
			IActiveViewPtr	pAct(pMap);
			pAct->Refresh();
			return E_FAIL;
		}
		
		pFeatureEdit=pFeature;
		pDelSet->Add(pFeature);
		hr=pEnumFeature->Next(&pFeature);
		if(FAILED(hr))	return hr;
	}
	hr=pFeatureEdit->DeleteSet(pDelSet);
	return hr;
}

HRESULT	CShpEditorDoc::NewFeatures(IFeatureLayerPtr pEditLayer,IGeometryPtr	pGeometry)
{
	HRESULT		hr;
	ILayerPtr	pLayer;
	IFeatureLayerPtr	pFeaLayer;
	IFeatureClassPtr	pFeaClass;

	pFeaLayer=pEditLayer;
	pFeaLayer->get_FeatureClass(&pFeaClass);

	IFeatureCursorPtr	pFeaCur;
	IFeaturePtr	pFeature;

	ITopologicalOperatorPtr	pTopOpe;
	pTopOpe=pGeometry;
	pTopOpe->Simplify();

	hr=pFeaClass->Insert(VARIANT_TRUE,&pFeaCur);//得到要素指针
	if(FAILED(hr))	return hr;
	IFeatureBufferPtr	pFeaBuf;
	hr=pFeaClass->CreateFeatureBuffer(&pFeaBuf);//创建要素缓冲, ???如果用CreateFeature()创建要素会在要素类中加入两天纪录，
	if(FAILED(hr))	return hr;					//而CreateFeatureBuffer()是加了一条纪录（原因不明）。
	hr=pFeaBuf->putref_Shape(pGeometry);		//	
	if(FAILED(hr))	return hr;

	CComVariant ret;
	hr=pFeaCur->InsertFeature(pFeaBuf,&ret);//把新建的要素插入图层
	if(FAILED(hr))	return hr;


	hr=pFeaCur->Flush();
//	if(FAILED(hr))	return hr;

	return	S_OK;
}

HRESULT	CShpEditorDoc::NewFeatures(IFeatureLayerPtr pEditLayer,
								   IFeaturePtr	pOldFeature,
								   IGeometryPtr	pGeometry)
{
	HRESULT		hr;
	ILayerPtr	pLayer;
	IFeatureLayerPtr	pFeaLayer;
	IFeatureClassPtr	pFeaClass;

	pFeaLayer=pEditLayer;
	pFeaLayer->get_FeatureClass(&pFeaClass);

	IFeatureCursorPtr	pFeaCur;
	IFeaturePtr	pFeature;

	ITopologicalOperatorPtr	pTopOpe;
	pTopOpe=pGeometry;
	pTopOpe->Simplify();

	hr=pFeaClass->Insert(VARIANT_TRUE,&pFeaCur);//得到要素指针
	if(FAILED(hr))	return hr;
	IFeatureBufferPtr	pFeaBuf;
	hr=pFeaClass->CreateFeatureBuffer(&pFeaBuf);//创建要素缓冲, ???如果用CreateFeature()创建要素会在要素类中加入两天纪录，
	if(FAILED(hr))	return hr;					//而CreateFeatureBuffer()是加了一条纪录（原因不明）。
	hr=pFeaBuf->putref_Shape(pGeometry);		//	
	if(FAILED(hr))	return hr;
	IFieldsPtr	pFields;
	pOldFeature->get_Fields(&pFields);
	long nFieldCount;
	pFields->get_FieldCount(&nFieldCount);

	for(long i=0;i<nFieldCount;i++)
	{
		IFieldPtr	pField;
		pFields->get_Field(i,&pField);
		
		VARIANT_BOOL	vtb;
		pField->get_Required(&vtb);
		
		if(vtb==VARIANT_TRUE)
			continue;
		
		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);

		pOldFeature->get_Value(i,&vtFieldValue);
		pFeaBuf->put_Value(i,vtFieldValue);
	}

	CComVariant ret;
	hr=pFeaCur->InsertFeature(pFeaBuf,&ret);//把新建的要素插入图层
	if(FAILED(hr))	return hr;


	hr=pFeaCur->Flush();
//	if(FAILED(hr))	return hr;

	return	S_OK;
}

HRESULT	CShpEditorDoc::DocInsertFeature(IFeatureCursor* pInFeatCur, 
									 IFeatureBuffer* pInFeatBuf,
									 IFeature* pOrigFeat, IGeometry* pGeom)
{
	// Copy attributes of original feature to new feature
	IFieldsPtr ipFields;
	pOrigFeat->get_Fields(&ipFields);
	
	long fieldCount;
	ipFields->get_FieldCount(&fieldCount);
	
	IFieldPtr ipField;
	
	// Skip OID and geometry fields
	for (long i = 0; i <=  fieldCount - 1; i++)
	{
		ipFields->get_Field(i, &ipField);
		
		esriFieldType esriField;
		ipField->get_Type(&esriField);
		
		VARIANT_BOOL varboolEdit;
		ipField->get_Editable(&varboolEdit);
		
		// Skip OID and geometry fields
		if (!(esriField == esriFieldTypeGeometry) &&
			!(esriField == esriFieldTypeOID) && 
			(varboolEdit))
		{
			CComVariant origValue;  
			pOrigFeat->get_Value(i, &origValue);
			pInFeatBuf->put_Value(i, origValue);
		}
	}
	
	pInFeatBuf->putref_Shape(pGeom);

	CComVariant varID;
	pInFeatCur->InsertFeature(pInFeatBuf, &varID);
	
	return S_OK;
}



//////********设置缓冲区********////////////////
HRESULT	CShpEditorDoc::BufferFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer,double distance)
{
	HRESULT	hr;
	
	IEnumFeaturePtr		pEnumFeature;
	ISelectionPtr		pSelection;
	hr=pMap->get_FeatureSelection(&pSelection);
	if(FAILED(hr))	return hr;
	pEnumFeature=pSelection;
	
	IGeometryPtr	pReferenceGeo,pResultGeo;
	IFeaturePtr		pFeature;
	ITopologicalOperatorPtr	pTopOpe;
	
	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	return hr;
	while (pFeature!=NULL) //遍历所有选中的要素
	{
		//判断是否是参考层要素
		BOOL	bIsRefLayer;
		bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
		if(bIsRefLayer)
		{
			::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
			IActiveViewPtr	pAct(pMap);
			pAct->Refresh();
			return E_FAIL;
		}

		pFeature->get_Shape(&pReferenceGeo);
		pTopOpe=pReferenceGeo;
		pTopOpe->Buffer(distance,&pResultGeo);

		NewFeatures(pEditLayer,pFeature,pResultGeo);//把新建的要素插入图层
		if(FAILED(hr))	return hr;
		
		hr=pEnumFeature->Next(&pFeature);
		if(FAILED(hr))	return hr;
	}
	return S_OK;
}


HRESULT	CShpEditorDoc::ClipFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry,double distance,int method)
{
	HRESULT	 hr;

	ITopologicalOperatorPtr	pTopOpe;
	ITopologicalOperatorPtr	pTopBuf;
	IFeatureCursorPtr		pFeaCur;
	IFeaturePtr				pFeature;
	IGeometryPtr			pReferenceGeo;	//参考图形
	IGeometryPtr			pCompareGeo;	//比较图形
	IGeometryPtr			pResultGeo;		//结果图形
	IGeometryPtr			pBufferGeo;
	ISetPtr					pDeleteSet(CLSID_Set);//当前参与运算的图形集
	IFeatureEditPtr			pFeaEdit;
	VARIANT_BOOL			vb;
	
	IRelationalOperatorPtr	pRelOpe;
	pRelOpe=pGeometry;
	pReferenceGeo=pGeometry;
	
	hr=QueryFeature(pEditLayer,pReferenceGeo,esriSpatialRelIntersects,&pFeaCur);//得到与参考图形相交的比较图形
	if(FAILED(hr))	return hr;
	hr=pFeaCur->NextFeature(&pFeature);
	if(FAILED(hr))	return hr;
	
	while (pFeature!=NULL)
	{
		//判断是否是参考层要素
		BOOL	bIsRefLayer;
		bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
		if(bIsRefLayer)
		{
			::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
			return E_FAIL;
		}
		
		pFeature->get_Shape(&pCompareGeo);
		pRelOpe->Equals(pCompareGeo,&vb);//判断当前图形是否与选中的图形相等
		if(vb==VARIANT_FALSE)
		{
			pFeaEdit=pFeature;
			pDeleteSet->Add(pFeature);//加入参与运算的图形
			pTopOpe=pCompareGeo;
			if(method==1)//判断Clip的方式
			{
				hr=pTopOpe->Difference(pReferenceGeo,&pResultGeo);//差分运算
				if(FAILED(hr))	return hr;
			}
			else
			{
				hr=pTopOpe->Intersect(pReferenceGeo,esriGeometry2Dimension,&pResultGeo);//交集运算
				if(FAILED(hr))	return hr;
			}
			
			pTopBuf=pResultGeo;
			hr=pTopBuf->Buffer(distance,&pBufferGeo);//结果要素的缓冲设置
			if(FAILED(hr))	return hr;
			NewFeatures(pEditLayer,pFeature,pResultGeo);//把新建的要素插入图层
			if(FAILED(hr))	return hr;
			hr=pFeaEdit->DeleteSet(pDeleteSet);//删除当前参与运算的图形
			if(FAILED(hr))	return hr;
		}
		hr=pFeaCur->NextFeature(&pFeature);
		if(FAILED(hr))	return hr;
	}
	
	return S_OK;
}
///////////**********用空间查询获得要素指针****************/////////////////////////////

HRESULT CShpEditorDoc::QueryFeature(IFeatureLayerPtr pEditLayer,IGeometryPtr pGeometry,
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
		(*pFeaCur)->AddRef();
	return S_OK;
}
HRESULT CShpEditorDoc::SnapQueryFeature(IFeatureLayerPtr pRefLayer,IGeometryPtr pGeometry,
									esriSpatialRelEnum	esriSpaRel,IFeatureCursor ** pFeaCur)
{
	HRESULT hr;
	ISpatialFilterPtr	pSpaFil(CLSID_SpatialFilter);
	hr=pSpaFil->putref_Geometry(pGeometry);
	if(FAILED(hr)) return hr;
	hr=pSpaFil->put_SpatialRel(esriSpaRel);//设置查询关系
	if(FAILED(hr)) return hr;
	
	IFeatureLayerPtr	pFeaLayer;

	pFeaLayer=pRefLayer;
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
		(*pFeaCur)->AddRef();
	return S_OK;
}

HRESULT CShpEditorDoc::Merge(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometry **pNewGeo)
{
	HRESULT	hr;
	ISetPtr			pSet(CLSID_Set);
	IFeatureEditPtr	pFeaEdit;
	
	IEnumFeaturePtr		pEnumFeature;
	ISelectionPtr		pSelection;
	hr=pMap->get_FeatureSelection(&pSelection);
	if(FAILED(hr))	return hr;
	pEnumFeature=pSelection;
	
	IGeometryPtr	pReferenceGeo,pCompareGeo,pResultGeo;
	IFeaturePtr		pFeature;
	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	return hr;

	BOOL	bIsRefLayer;
	bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
	if(bIsRefLayer)
	{
		::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONSTOP);
		return E_FAIL;
	}

	pFeaEdit=pFeature;
	pSet->Add(pFeature);
	hr=pFeature->get_Shape(&pReferenceGeo);
	if(FAILED(hr))	return hr;
	ITopologicalOperatorPtr	pTopOpe;
	pTopOpe=pReferenceGeo;	

	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	return hr;
	while (pFeature!=NULL) //遍历所有选中的要素
	{	
		//判断是否是参考层要素
		bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
		if(bIsRefLayer)
		{
			::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
			return E_FAIL;
		}
		
		pSet->Add(pFeature);
		pFeature->get_Shape(&pCompareGeo);
		pTopOpe->Union(pCompareGeo,&pResultGeo);//合并所有选中的要素
		pTopOpe=pResultGeo;
		hr=pEnumFeature->Next(&pFeature);
		if(FAILED(hr))	return hr;
		
	}
	IFeaturePtr	pRefFeature;
	BOOL	bResult;	
	bResult=SelectReferenceFeature(pMap,&pRefFeature);
	
	if(bResult)
		NewFeatures(pEditLayer,pRefFeature,pResultGeo);//把新建的要素插入图层
	else
		return E_FAIL;

	*pNewGeo=pResultGeo;
	if(*pNewGeo)
		(*pNewGeo)->AddRef();
	
	hr=pFeaEdit->DeleteSet(pSet);//删除当前参与运算的图形
	if(FAILED(hr))	return hr;	
	return S_OK;
}

HRESULT CShpEditorDoc::UnionFeatures(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometry **pNewGeo)
{
	HRESULT	hr;
	IEnumFeaturePtr		pEnumFeature;
	ISelectionPtr		pSelection;

	hr=pMap->get_FeatureSelection(&pSelection);
	if(FAILED(hr))	return hr;
	pEnumFeature=pSelection;
	
	IGeometryPtr	pReferenceGeo,pCompareGeo,pResultGeo;
	IFeaturePtr		pFeature;
	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	return hr;
	hr=pFeature->get_Shape(&pReferenceGeo);
	if(FAILED(hr))	return hr;
	ITopologicalOperatorPtr	pTopOpe;
	pTopOpe=pReferenceGeo;
	
	hr=pEnumFeature->Next(&pFeature);
	if(FAILED(hr))	return hr;
	while (pFeature!=NULL) //遍历所有选中的要素
	{
		pFeature->get_Shape(&pCompareGeo);
		pTopOpe->Union(pCompareGeo,&pResultGeo);//合并所有选中的要素
		pTopOpe=pResultGeo;
		hr=pEnumFeature->Next(&pFeature);
		if(FAILED(hr))	return hr;
	}
	
	IFeaturePtr	pRefFeature;
	BOOL	bResult;
	bResult=SelectReferenceFeature(pMap,&pRefFeature);
	if(bResult)
		NewFeatures(pEditLayer,pRefFeature,pResultGeo);//把新建的要素插入图层
	else
		return E_FAIL;
	*pNewGeo=pResultGeo;
	if(*pNewGeo)
		(*pNewGeo)->AddRef();
	
	return hr;	
}


HRESULT CShpEditorDoc::Divide(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IGeometryPtr	pGeometry)
{
	HRESULT	hr;
	IGeometryCollectionPtr	pGeoCol(CLSID_GeometryBag);
	IEnumFeaturePtr	pEnumFeature;
	ISelectionPtr	pSelection;
	IFeatureEditPtr	pFeaEdit;
	IFeaturePtr		pFeature;
	ISetPtr			pDelSet(CLSID_Set);
	IGeometryPtr	pPolygon(CLSID_Polygon);
	long			lGeoCount;
	
	hr=pMap->get_FeatureSelection(&pSelection);
	if(FAILED(hr))	return hr;
	
	pEnumFeature=pSelection;
	pEnumFeature->Next(&pFeature);
	//判断是否是参考层要素
	BOOL	bIsRefLayer;
	bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
	if(bIsRefLayer)
	{
		::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
		return E_FAIL;
	}
	
//	hr=pFeature->putref_Shape(pGeometry);
//	if(FAILED(hr))	return hr;

	pFeaEdit=pFeature;
	hr=pDelSet->Add(pFeature);
	if(FAILED(hr))	return hr;

	hr=ConvertGeometry(pGeometry,&pGeoCol);//转换图形类型
	if(FAILED(hr))	return hr;

	hr=pGeoCol->get_GeometryCount(&lGeoCount);
	if(FAILED(hr))	return hr;

	for(long i=0;i<lGeoCount;i++)
	{
		hr=pGeoCol->get_Geometry(i,&pPolygon);
		if(FAILED(hr))		return hr;

		NewFeatures(pEditLayer,pFeature,pPolygon);//创建新的要素
		if(FAILED(hr))		return hr;
	}

	hr=pFeaEdit->DeleteSet(pDelSet);
	if(FAILED(hr))	return hr;

	return S_OK;
}

HRESULT	CShpEditorDoc::ConvertGeometry(IGeometryPtr pRingGeo,IGeometryCollection ** pOutCol)
{
	HRESULT		hr;
	
	IGeometryCollectionPtr	pRingCol(CLSID_Polygon);
	IGeometryCollectionPtr	pPolyCol(CLSID_GeometryBag);
	ITopologicalOperatorPtr	pTopOpe;
	IGeometryPtr			pRing;
	IGeometryPtr			pNextRing;
	IClonePtr				pClone;
	IClonePtr				pDuplicateClone;
	IRingPtr				pExRing;
	IRingPtr				pInRing;
	long	lGeoCount;
	VARIANT_BOOL			vtIsExterior;
	
	pRingCol=pRingGeo;
	pClone=pRingCol;
	hr=pClone->Clone(&pDuplicateClone);
	if(FAILED(hr))		return hr;
	pRingGeo=pDuplicateClone;

	//得到要素所包含几何图形个数

	hr=pRingCol->get_GeometryCount(&lGeoCount);
	if(FAILED(hr))		return hr;
	for(long i=0;i<lGeoCount;i++)
	{
		IGeometryCollectionPtr	pTempPolygon(CLSID_Polygon);
		hr=pRingCol->get_Geometry(i,&pRing);
		if(FAILED(hr))		return hr;
		pTopOpe=pTempPolygon;
		hr=pTempPolygon->AddGeometry(pRing,&vtMissing,&vtMissing);
		if(FAILED(hr))		return hr;
		if(i+1<lGeoCount)
		{
			hr=pRingCol->get_Geometry(i+1, &pNextRing);//的到下一环
			if(FAILED(hr))		return hr;
			pInRing=pNextRing;
			hr=pInRing->get_IsExterior(&vtIsExterior);
			if(FAILED(hr))		return hr;
			if(vtIsExterior==VARIANT_FALSE)//是否是内环
			{
				hr=pTempPolygon->AddGeometry(pNextRing,&vtMissing,&vtMissing);//把内外环合并
				if(FAILED(hr))		return hr;
				i++;
			}
		}
		hr=pTopOpe->Simplify();
		if(FAILED(hr))		return hr;
		hr=pPolyCol->AddGeometry((IGeometryPtr)pTempPolygon,&vtMissing,&vtMissing);
		if(FAILED(hr))		return hr;
	}
	*pOutCol=pPolyCol;
	(*pOutCol)->AddRef();
	return S_OK;
}
/*
HRESULT	CShpEditorDoc::ConvertGeometry(IGeometryPtr pCirCleGeo,IGeometryPtr** pOutGeo)
{
	HRESULT		hr;
	
	IGeometryCollectionPtr	pRingCol(CLSID_Polygon);
	IGeometryCollectionPtr	pPolyCol(CLSID_GeometryBag);
	ITopologicalOperatorPtr	pTopOpe;
	IGeometryPtr			pRing;
	IGeometryPtr			pNextRing;
	IClonePtr				pClone;
	IClonePtr				pDuplicateClone;
	IRingPtr				pExRing;
	IRingPtr				pInRing;
	long	lGeoCount;
	VARIANT_BOOL			vtIsExterior;
	
	pRingCol=pRingGeo;
	pClone=pRingCol;
	hr=pClone->Clone(&pDuplicateClone);
	if(FAILED(hr))		return hr;
	pRingGeo=pDuplicateClone;

	//得到要素所包含几何图形个数

	hr=pRingCol->get_GeometryCount(&lGeoCount);
	if(FAILED(hr))		return hr;
	for(long i=0;i<lGeoCount;i++)
	{
		IGeometryCollectionPtr	pTempPolygon(CLSID_Polygon);
		hr=pRingCol->get_Geometry(i,&pRing);
		if(FAILED(hr))		return hr;
		pTopOpe=pTempPolygon;
		hr=pTempPolygon->AddGeometry(pRing,&vtMissing,&vtMissing);
		if(FAILED(hr))		return hr;
		if(i+1<lGeoCount)
		{
			hr=pRingCol->get_Geometry(i+1, &pNextRing);//的到下一环
			if(FAILED(hr))		return hr;
			pInRing=pNextRing;
			hr=pInRing->get_IsExterior(&vtIsExterior);
			if(FAILED(hr))		return hr;
			if(vtIsExterior==VARIANT_FALSE)//是否是内环
			{
				hr=pTempPolygon->AddGeometry(pNextRing,&vtMissing,&vtMissing);//把内外环合并
				if(FAILED(hr))		return hr;
				i++;
			}
		}
		hr=pTopOpe->Simplify();
		if(FAILED(hr))		return hr;
		hr=pPolyCol->AddGeometry((IGeometryPtr)pTempPolygon,&vtMissing,&vtMissing);
		if(FAILED(hr))		return hr;
	}
	*pOutCol=pPolyCol;
	(*pOutCol)->AddRef();
	return S_OK;
}
*/
HRESULT CShpEditorDoc::CutFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer,IPolylinePtr pLine) 
{
	HRESULT	 hr;
	
	ITopologicalOperatorPtr	pTopOpe;
	ITopologicalOperatorPtr	pTopBuf;
	IFeatureCursorPtr		pFeaCur;
	IFeaturePtr				pFeature;
	IGeometryPtr			pLeftGeo;		//结果图形
	IGeometryPtr			pRightGeo;		//结果图形
	IGeometryPtr			pCompareGeo;	//比较图形
	ISetPtr					pDeleteSet(CLSID_Set);//当前参与运算的图形集
	IFeatureEditPtr			pFeaEdit;
	VARIANT_BOOL			vb;

	IRelationalOperatorPtr	pRelOpe;
	pRelOpe=pLine;

	hr=QueryFeature(pEditLayer,pLine,esriSpatialRelIntersects,&pFeaCur);//得到与参考图形相交的比较图形
	if(FAILED(hr))	return hr;
	hr=pFeaCur->NextFeature(&pFeature);
	if(FAILED(hr))	return hr;


	while (pFeature!=NULL)
	{
		//判断是否是参考层要素
		BOOL	bIsRefLayer;
		bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
		if(bIsRefLayer)
		{
			::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
			return E_FAIL;
		}
		
		pFeature->get_Shape(&pCompareGeo);
		pRelOpe->Equals(pCompareGeo,&vb);//判断当前图形是否与选中的图形相等
		if(vb==VARIANT_FALSE)
		{

			IGeometryPtr	pGeoLine;
			ISpatialReferencePtr	pSpaRef;

			pGeoLine=pLine;
			pCompareGeo->get_SpatialReference(&pSpaRef);
			pGeoLine->putref_SpatialReference(pSpaRef);

			pTopOpe=pCompareGeo;	
		//	pTopOpe->Simplify();
			hr=pTopOpe->Cut(pLine,&pLeftGeo,&pRightGeo);
			if(!FAILED(hr))//当剪切成功时创建着两个图形（即只有线穿越图形时才执行剪切）
			{
				pFeaEdit=pFeature;
				pDeleteSet->Add(pFeature);//加入参与运算的图形
				NewFeatures(pEditLayer,pFeature,pLeftGeo);//把新建的要素插入图层
				if(FAILED(hr))	return hr;
				NewFeatures(pEditLayer,pFeature,pRightGeo);//把新建的要素插入图层
				if(FAILED(hr))	return hr;

				hr=pFeaEdit->DeleteSet(pDeleteSet);//删除当前参与运算的图形
				if(FAILED(hr))	return hr;
			}			
		
			hr=pFeaCur->NextFeature(&pFeature);
			if(FAILED(hr))	return hr;
		}
	}
	IActiveViewPtr	pActiveView(pMap);	
	IGraphicsContainerPtr	pGraCon(pActiveView);
	hr=pGraCon->DeleteAllElements();//清除所有画线
	return S_OK;
}

HRESULT CShpEditorDoc::IntersectFeature(IMapPtr pMap,IFeatureLayerPtr pEditLayer) 
{
	HRESULT	hr;
	
	IEnumFeaturePtr		pEnumFeature;
	ISelectionPtr		pSelection;
	hr=pMap->get_FeatureSelection(&pSelection);
	if(FAILED(hr))	return hr;
	pEnumFeature=pSelection;

	IFeaturePtr		pFeature;
	IGeometryPtr	pFirstGeo,pSecondGeo,pResultGeo;
	
	hr=pEnumFeature->Next(&pFeature);//得到参考要素
	if(FAILED(hr))	return hr;
	BOOL	bIsRefLayer;
	bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
	if(bIsRefLayer)
	{
		::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
		return E_FAIL;
	}
	hr=pFeature->get_Shape(&pFirstGeo);
	if(FAILED(hr))	return hr;
	hr=pEnumFeature->Next(&pFeature);//得到比较要素
	if(FAILED(hr))	return hr;
	bIsRefLayer=IsReferenceLayer(pEditLayer,pFeature);
	if(bIsRefLayer)
	{
		::MessageBox(NULL,"参考层不能修改!","面编辑工具",MB_OK|MB_ICONWARNING);
		return E_FAIL;
	}
	hr=pFeature->get_Shape(&pSecondGeo);
	if(FAILED(hr))	return hr;
	
	ITopologicalOperatorPtr	pTopOpe;
	pTopOpe=pFirstGeo;
	hr=pTopOpe->Intersect(pSecondGeo,esriGeometry2Dimension,&pResultGeo);
	if(FAILED(hr))	return hr;
	
	NewFeatures(pEditLayer,pResultGeo);//把新建的要素插入图层
	return hr;
	
}

BOOL CShpEditorDoc::IsReferenceLayer(IFeatureLayerPtr pEditLayer,IFeaturePtr pRefFeature)
{
//	ASSERT(pFeature!=NULL);
	
	if(pEditLayer==NULL) TRUE;
	
	HRESULT hr;
	IQueryFilterPtr	pQueryFilter(CLSID_QueryFilter);

	IFeatureCursorPtr	pFeaCur;
	pEditLayer->Search(pQueryFilter,VARIANT_TRUE,&pFeaCur);


	long RefOID;
	
	pRefFeature->get_OID(&RefOID);

	IGeometryPtr	pRefGeo;
	pRefFeature->get_Shape(&pRefGeo);

	IRelationalOperatorPtr	pRelOper;
	pRelOper=pRefGeo;
	
	IFeaturePtr	pFeature;
	pFeaCur->NextFeature(&pFeature);
	while (pFeature!=NULL)
	{
		long EditOID;

		pFeature->get_OID(&EditOID);
		IGeometryPtr	pEditGeo;
		pFeature->get_Shape(&pEditGeo);

		VARIANT_BOOL	vtEqual;
		pRelOper->Equals(pEditGeo,&vtEqual);

		if(vtEqual==VARIANT_TRUE && EditOID==RefOID)
			return FALSE;

		hr=pFeaCur->NextFeature(&pFeature);
	}
	return TRUE;
}

BOOL CShpEditorDoc::SelectReferenceFeature(IMapPtr pMap,IFeature ** pRefFeature)
{
	CFS_MergeDlg	MergeDlg;

	if(MergeDlg.DoModal()==IDOK)
	{
		long nSelectedOID;
		nSelectedOID=MergeDlg.m_OID;
		
		ISelectionPtr	pSelection;
		pMap->get_FeatureSelection(&pSelection);

		IEnumFeaturePtr	pEnumFeature;
		pEnumFeature=pSelection;
		IFeaturePtr	pFeature;
		pEnumFeature->Next(&pFeature);
		while (pFeature!=NULL)
		{
			long nOID;
			pFeature->get_OID(&nOID);
			if(nOID==nSelectedOID)
			{
				*pRefFeature=pFeature;
				if(*pRefFeature)
				{
					(*pRefFeature)->AddRef();
					return TRUE;
				}
			}
			pEnumFeature->Next(&pFeature);
		}		
	}
	return FALSE;
}


