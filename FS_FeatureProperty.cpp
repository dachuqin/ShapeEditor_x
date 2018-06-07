// FS_FeatureProperty.cpp : implementation file
//

#include "stdafx.h"
#include "shpeditor.h"
#include "FS_FeatureProperty.h"

#include "MainFrm.h"
#include "ShpEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_FeatureProperty dialog


CFS_FeatureProperty::CFS_FeatureProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CFS_FeatureProperty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFS_FeatureProperty)
	//}}AFX_DATA_INIT
	m_bIsRef=FALSE;
	m_pFeature=NULL;
	
}


void CFS_FeatureProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFS_FeatureProperty)
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX, IDC_GRID, m_Grid);	
}


BEGIN_MESSAGE_MAP(CFS_FeatureProperty, CDialog)
	//{{AFX_MSG_MAP(CFS_FeatureProperty)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndInPlaceEdit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_FeatureProperty message handlers

void CFS_FeatureProperty::OnOK() 
{

//	HTREEITEM	hItem;
//	hItem=m_ctrTree.GetSelectedItem();
//	CString	strFieldName;
//	strFieldName=m_ctrTree.GetItemText(hItem);

	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	
	BOOL	bIsShowLabel;
	bIsShowLabel=pView->GetEditLayerLableVisible();
	if(bIsShowLabel)
		pView->ShowFeatureLabel();
	
	if(m_bIsRef==FALSE)
	{
		UpdateData(TRUE);
		m_Grid.UpdateData(TRUE);
		SaveModify();
	}	
}

BOOL CFS_FeatureProperty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_ctrTree.
	m_Grid.EnableDragAndDrop(FALSE);
//	m_Grid.EnableSelection(FALSE);
	m_Grid.SetEditable(TRUE);
	m_Grid.SetSingleRowSelection(TRUE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	
	GetSelectedFeature();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFS_FeatureProperty::GetSelectedFeature()
{
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	
	HRESULT	hr;
	/*
//	IEnumFeaturePtr pSelectedFeature;
	hr=pView->GetSelectedFeatures(&m_pSelectedFeature);
	if(FAILED(hr)) return;
	if(m_pSelectedFeature==NULL) return;

	m_pSelectedFeature->Reset();

	IFeaturePtr	pFeature;
	m_pSelectedFeature->Next(&pFeature);
	int	nFieldIndex=0;
	while (pFeature!=NULL) 
	{
		IFieldsPtr	pFields;
		pFeature->get_Fields(&pFields);


		BSTR	bFieldName;
		IFieldPtr	pField;
		pFields->get_Field(nFieldIndex,&pField);
		pField->get_Name(&bFieldName);

		m_ctrTree.InsertItem((LPCTSTR)bFieldName,0,nFieldIndex++);
		m_pSelectedFeature->Next(&pFeature);
	}

	HTREEITEM hItem;
	hItem=m_ctrTree.GetRootItem();
	m_ctrTree.SetCheck(hItem,TRUE);

	m_Grid.InsertColumn(0,"字段名",LVCFMT_LEFT,80);
	m_Grid.InsertColumn(1,"字段值",LVCFMT_LEFT,80);

	m_pSelectedFeature->Reset();
	
	m_pSelectedFeature->Next(&pFeature);

	IFieldsPtr	pFields;
	pFeature->get_Fields(&pFields);
	
	long nFieldCount;
	pFields->get_FieldCount(&nFieldCount);

	for(long i=0;i<nFieldCount;i++)
	{
		BSTR			bFieldName;
		CString			strFieldValue;
		esriFieldType	fieldtype;

		IFieldPtr	pField;
		pFields->get_Field(i,&pField);
		pField->get_Name(&bFieldName);
		pField->get_Type(&fieldtype);

		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);
		pFeature->get_Value(i,&vtFieldValue);

		strFieldValue=vtToCString(vtFieldValue,fieldtype);

		CString	strIndex;
		strIndex.Format("%d",i);
		m_Grid.InsertItem(0,strIndex);
		m_Grid.SetItemText(i,0,(LPCTSTR)bFieldName);
		m_Grid.SetItemText(i,0,(LPCTSTR)strFieldValue);
	}
	
	m_Grid.InsertColumn(0,"序号",LVCFMT_LEFT,50);
	m_Grid.InsertColumn(1,"字段名",LVCFMT_LEFT,80);
	m_Grid.InsertColumn(2,"字段值",LVCFMT_LEFT,100);
*/	
	m_pFeature=NULL;

	hr=pView->GetSelectedFeatures(&m_pFeature,m_bIsRef);
	if(FAILED(hr)) return;
	if(m_pFeature==NULL) return;

	IFieldsPtr	pFields;
	m_pFeature->get_Fields(&pFields);

	long nFieldCount;
	pFields->get_FieldCount(&nFieldCount);


	m_Grid.SetRowCount(nFieldCount-1);
	m_Grid.SetColumnCount(4);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetFixedColumnCount(0);

	char gridHeader[4][10] = {"序号","字段名","字段值","字段类型"};
	//填充表格的表头，并且设置列宽
	for (int col = 0; col < 4; col++)
	{ 
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = 0;
		Item.col = col;
		
		Item.nFormat = DT_LEFT|DT_WORDBREAK|DT_NOPREFIX;
		Item.strText = gridHeader[col];
		
		BOOL	br;
		
		br=m_Grid.SetItem(&Item);
		br=m_Grid.SetColumnWidth(col,78);
	}

	if(m_bIsRef==TRUE)
		m_Grid.EnableWindow(FALSE);
	
	for (int row = 0; row < nFieldCount-1; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if(col!=2)
				m_Grid.SetItemState(row,col,m_Grid.GetItemState(row,col) | GVIS_READONLY);
		}
	}
	int	nIndex=1;
	for(long i=0;i<nFieldCount;i++)
	{
		BSTR			bFieldName;
		CString			strFieldValue;
		esriFieldType	fieldtype;
		
		IFieldPtr	pField;
		pFields->get_Field(i,&pField);

		VARIANT_BOOL	vtb;
		pField->get_Required(&vtb);
		
		if(vtb==VARIANT_TRUE)
			continue;
		
		pField->get_Name(&bFieldName);
		pField->get_Type(&fieldtype);

		CString	strFieldType;
		strFieldType=esriToCString(fieldtype);
		
		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);
		hr=m_pFeature->get_Value(i,&vtFieldValue);
		if(vtFieldValue.vt==VT_EMPTY)
			continue;
		strFieldValue=vtToCString(vtFieldValue,fieldtype);

		CString	strFieldName;
		strFieldName=(LPCWSTR)bFieldName;

		CString	strIndex;
		strIndex.Format("%d",nIndex);
//		m_Grid.InsertRow()
		m_Grid.SetItemText(nIndex,0,(LPCTSTR)strIndex);
		m_Grid.SetItemText(nIndex,1,(LPCTSTR)strFieldName);
		m_Grid.SetItemText(nIndex,2,(LPCTSTR)strFieldValue);
		m_Grid.SetItemText(nIndex,3,(LPCTSTR)strFieldType);
		nIndex++;
	}
//	m_Grid.UpdateData(FALSE);
	m_Grid.Refresh();
	m_Grid.UpdateData(FALSE);
	UpdateData(FALSE);
}

/*
void CFS_FeatureProperty::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM	hItem;
	hItem=m_ctrTree.GetSelectedItem();
	CString	strFieldName;
	strFieldName=m_ctrTree.GetItemText(hItem);

	SaveModify(strFieldName);


	*pResult = 0;
}
*/
HRESULT CFS_FeatureProperty::GetIndexByName(CString strName,IFeature **pSelectedFeature)
{
	BSTR	BName;
	BName=strName.AllocSysString();

	m_pSelectedFeature->Reset();

	IFeaturePtr	pFeature;
	m_pSelectedFeature->Next(&pFeature);
	int	nFeatureIndex=0;
	while (pFeature!=NULL) 
	{
		IFieldsPtr	pFields;
		pFeature->get_Fields(&pFields);
		
		HRESULT		hr;
		long lFieldIndex;
		hr=pFields->FindFieldByAliasName(BName,&lFieldIndex);
		if(SUCCEEDED(hr))
		{
			(*pSelectedFeature)=pFeature;
			if(*pSelectedFeature)
			{
				(*pSelectedFeature)->AddRef();
				return S_OK;
			}
		}
		m_pSelectedFeature->Next(&pFeature);
	}
	return E_FAIL;	
}



void CFS_FeatureProperty::SaveModify()
{
	HRESULT hr;
	IFieldsPtr		pFields;

	m_pFeature->get_Fields(&pFields);
	IFieldsEditPtr	pFieldsEdit(pFields);

	long nFieldCount;
	long nStartIndex=-1;

	pFields->get_FieldCount(&nFieldCount);
	for(long l=0;l<nFieldCount;l++)
	{
		IFieldPtr	pField;
		pFields->get_Field(l,&pField);
		
		VARIANT_BOOL vtb;
		pField->get_Required(&vtb);
		if(vtb==VARIANT_FALSE)
		{
			nStartIndex=l;
			break;
		}
	}

	if(nStartIndex==-1)	return;

	int nItemCount;
	nItemCount=m_Grid.GetRowCount();

	for(long i=0;i<nItemCount;i++)
	{
		CString	strFieldName,strFieldValue;
		strFieldName=m_Grid.GetItemText(i+1,1);
		strFieldValue=m_Grid.GetItemText(i+1,2);
		
		BSTR			bFieldName;
		bFieldName=strFieldName.AllocSysString();

		IFieldPtr		pField(CLSID_Field);
		IFieldEditPtr	pFieldEdit(pField);

		pFieldEdit->put_Name(bFieldName);

		IFieldPtr	pTempField;
		hr=pFieldsEdit->get_Field(i+nStartIndex,&pTempField);
		if(FAILED(hr)) return;
		
		esriFieldType	fieldType;
		pTempField->get_Type(&fieldType);

		VARIANT	vtFieldValue;
		VariantInit(&vtFieldValue);
		vtFieldValue=ConvertType(strFieldValue,fieldType);
		
		hr=m_pFeature->put_Value(i+nStartIndex,vtFieldValue);
	
	}
	hr=m_pFeature->Store();
}

VARIANT CFS_FeatureProperty::ConvertType(CString strFieldValue, esriFieldType fieldtype)
{
	VARIANT	vtFieldValue;
	VariantInit(&vtFieldValue);
	
	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:
		{
			short nFieldVal;
			nFieldVal =atoi(strFieldValue);
			vtFieldValue.vt=VT_I2;
			vtFieldValue.iVal=(short)nFieldVal;
		}
		break;
	case esriFieldTypeInteger:
		{
			long dFieldVal;
			dFieldVal =atol(strFieldValue);
			vtFieldValue.vt=VT_I4;
			vtFieldValue.lVal=dFieldVal;
		}
		break;
	case esriFieldTypeSingle:
		{
			float dFieldVal;
			dFieldVal =(float)atof(strFieldValue);
			vtFieldValue.vt=VT_R4;
			vtFieldValue.fltVal=dFieldVal;
		}
		break;
	case esriFieldTypeDouble:
		{
			double		dFieldVal;
			dFieldVal =atof(strFieldValue);
			vtFieldValue.vt=VT_R8;
			vtFieldValue.dblVal=dFieldVal;
		}
		break;
	case esriFieldTypeString:
		{
			BSTR	BFieldValue;
			BFieldValue=strFieldValue.AllocSysString();
			
			vtFieldValue.vt=VT_BSTR;
			vtFieldValue.bstrVal=BFieldValue;
		}
		break;
	case esriFieldTypeDate:
		{
			COleDateTime	vtDate;
			GetDateFromStr(strFieldValue,vtDate);
			vtFieldValue.vt=VT_DATE;
			vtFieldValue.date=vtDate;
		}
		break;
	default:
		break;
	}
	return vtFieldValue;
}


CString CFS_FeatureProperty::vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype)
{
	CString	strFieldValue;

	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:	
		short nFieldVal;
		nFieldVal=(short)vtFieldValue.iVal;
		strFieldValue.Format("%d",nFieldVal);
		break;
	case esriFieldTypeInteger:
		long lFieldVal;
		lFieldVal=(long)vtFieldValue.lVal;
		strFieldValue.Format("%ld",lFieldVal);
		break;
	case esriFieldTypeSingle:
		float fFieldVal;
		fFieldVal=(float)vtFieldValue.fltVal;
		strFieldValue.Format("%f",fFieldVal);
		break;
	case esriFieldTypeDouble:
		double dFieldVal;
		dFieldVal=(double)vtFieldValue.dblVal;
		strFieldValue.Format("%lf",dFieldVal);
		break;
	case esriFieldTypeString:
		strFieldValue=(LPCWSTR)vtFieldValue.bstrVal;
		break;
	case esriFieldTypeDate:
		{
			COleDateTime dtFieldVal;
			dtFieldVal=(COleDateTime) vtFieldValue.date;
			int nYear,nMonth,nDay;
			nYear=dtFieldVal.GetYear();
			nMonth=dtFieldVal.GetMonth();
			nDay=dtFieldVal.GetDay();
			
			strFieldValue.Format("%d-%d-%d",nYear,nMonth,nDay);
		}		
		break;
	default:
		strFieldValue="0";
		break;
	}
	return strFieldValue;
}

void CFS_FeatureProperty::OnGridEndInPlaceEdit(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	//判断位置的有效性
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	if(pItem->iRow < 0)
		return;
	
	//处理数量或单价列
	if(pItem->iColumn == 2)
	{
		CString strFieldValue = m_Grid.GetItemText(pItem->iRow,2);
		CString strFieldType =m_Grid.GetItemText(pItem->iRow,3);
		
		BOOL bIsLegal;
		bIsLegal = IsLegal(strFieldValue,strFieldType);
		if(!bIsLegal)
		{
			m_Grid.SetFocusCell(pItem->iRow,2);
			return;
		}
		
		m_Grid.SetItemText(pItem->iRow,2,strFieldValue);
		m_Grid.Refresh();
	}
}

CString CFS_FeatureProperty::esriToCString(esriFieldType fieldtype)
{
	CString strFieldType;
	
	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:
		strFieldType = _T("整型");
		break;
	case esriFieldTypeInteger:
		strFieldType = _T("长整型"); 
		break;
	case esriFieldTypeSingle:
		strFieldType = _T("浮点型(单精度)"); 
		break;
	case esriFieldTypeDouble:
		strFieldType = _T("浮点型(双精度)"); 
		break;
	case esriFieldTypeString:
		strFieldType = _T("字符串"); 
		break;
	case esriFieldTypeDate:
		strFieldType = _T("日期"); 
		break;
	case esriFieldTypeOID:
		strFieldType = _T("Object Identifer"); 
		break;
	case esriFieldTypeGeometry:
		strFieldType = _T("Geometry"); 
		break;
	case esriFieldTypeBlob:
		strFieldType = _T("Blob Storage"); 
		break;
	default:
		strFieldType = _T("不支持类型");
	}
	
	return strFieldType;
}

void CFS_FeatureProperty::GetDateFromStr(CString strTm, COleDateTime &vtDate)
{
	int nPos = strTm.Find("-");
	CString strYear = strTm.Left(nPos);
	CString strRight = strTm.Right(strTm.GetLength()-nPos-1);
	nPos = strRight.Find("-");
	CString strMonth = strRight.Left(nPos);
	CString strDay = strRight.Right(strRight.GetLength()-nPos-1);
	
	int nYear,nMonth,nDay;
	nYear = atoi(strYear.GetBuffer(0));
	if(nYear < 100)
		nYear += 2000;
	nMonth = atoi(strMonth.GetBuffer(0));
	nDay = atoi(strDay.GetBuffer(0));

	vtDate.SetDate(nYear,nMonth,nDay);
}

void CFS_FeatureProperty::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_pFeature=NULL;
}

BOOL CFS_FeatureProperty::IsLegal(CString &strFieldValue, CString strFieldType)
{
	if(strFieldType== "整型")
	{
		if(!IsInteger(strFieldValue))
		{
			::MessageBox(NULL,"非法数字！请输入合法值！","面编辑工具",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}

	if(strFieldType== "长整型")
	{
		if(!IsInteger(strFieldValue))
		{
			::MessageBox(NULL,"非法数字！请输入合法值！","面编辑工具",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}
	
	if(strFieldType== "浮点型(单精度)")
	{
		float nValue=0.0;
		if(	_IsFloat(strFieldValue))
		{
			if(strFieldType!="")
			{
				nValue=(float)atof(strFieldValue.GetBuffer(0));
			}
		}
		else
		{
			::MessageBox(NULL,"非法数字！请输入合法值！","面编辑工具",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}
	if(strFieldType== "浮点型(双精度)")
	{
		double nValue=0.0;
		if(	_IsFloat(strFieldValue))
		{
			if(strFieldType!="")
			{
				nValue=atof(strFieldValue.GetBuffer(0));
			}
		}
		else
		{
			::MessageBox(NULL,"非法数字！请输入合法值！","面编辑工具",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}

	if(strFieldType== "日期")
	{
		if(!_IsDate(strFieldValue))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CFS_FeatureProperty::IsInteger(CString strInteger)
{
	int nLength;
	nLength=strInteger.GetAllocLength();

	if(strInteger=="") return FALSE;
	if(nLength==0) return FALSE;
	for(int i=0;i<nLength;i++)
	{
		char chr;
		chr=strInteger.GetAt(i);
		if(chr<48 || chr >57)
			return FALSE;
	}
	return TRUE;
}

BOOL CFS_FeatureProperty::_IsFloat(CString& strText)
{
	CString strTmp(strText);

	strTmp.MakeUpper();

	int iSize = strTmp.GetLength();
	if (iSize == 0)
	{
		return FALSE;
	}
	
	int nEPos = strTmp.Find("E");
	int nDPos = strTmp.Find(".");

	// 以上字符在字符串中只能出现一次
	if ((strTmp.ReverseFind('E') != nEPos) || (strTmp.ReverseFind('.') != nDPos))
	{
		return FALSE;
	}

	BOOL bSign = (strTmp[0] == char('-'));
	int  nNPos = strTmp.Find("-", 1);

	// 负号出现的位置是否合理, 
	if (nNPos != -1)
	{	
		// 如果没有E符号出现
		if (nEPos == -1)
		{
			return FALSE;
		}

		// 负号必须紧跟在E符号后面
		if ((nNPos - nEPos) != 1)	
		{
			return FALSE;
		}

		// 负号不能是最后一个字符
		if ((iSize - nNPos) == 1)
		{
			return FALSE;
		}

		// 负号出现位置不对
		if (!bSign)
		{
			return FALSE;
		}

		// 还有一个负号出现
		if (strTmp.Find("-", nNPos+1) != -1)
		{
			return FALSE;
		}
	}

	// E后面必须有字符
	if ((iSize - nEPos) == 1)
	{
		return FALSE;
	}

	// 小数点位置是否合理
	if (nDPos != -1)
	{
		// 如果有E符号出现，并且小数点的位置在E符号之后
		if ((nEPos != -1) && (nDPos > nEPos))
		{
			return FALSE;
		}

		// 如果还有小数点
		if (strTmp.Find(".", nDPos+1) != -1)
		{
			return FALSE;
		}
	}
	
	char cText = 0;

	for (int i=0; i<strText.GetLength(); i++)
	{
		cText = strText[i];

		if ((cText == char('-')) || (cText == char('.')) 
			|| (cText == char('e')) || (cText == char('E')))
		{
			continue;
		}

		if ((cText >= char('0')) && (cText <= char('9')))
		{
			continue;
		}

		return FALSE;
	}

	return TRUE;
}

BOOL CFS_FeatureProperty::_IsDate(CString &str)
{
	if(str=="") return FALSE;
	int charCount;
	charCount=str.GetLength();
	if(charCount==0) return FALSE;
	
	int _Count=0;
	for(int i=0;i<charCount;i++)
	{
		char chr;
		chr=str.GetAt(i);
		if(chr=='-')
		{
			_Count++;
			i++;
		}
		chr=str.GetAt(i);
		if((chr<48 || chr>57))
		{
			::MessageBox(NULL,"日期中含有非法符号！请输入合法日期！","面编辑工具",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}

	if(_Count!=2)
	{
		::MessageBox(NULL,"格式错误!请输入正确格式。","面编辑工具",MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	
	int nPos = str.Find("-");
	CString strYear  = str.Left(nPos);
	CString strRight = str.Right(str.GetLength()-nPos-1);

	nPos	 = strRight.Find("-");
	CString strMonth = strRight.Left(nPos);
	CString strDay	 = strRight.Right(strRight.GetLength()-nPos-1);
	
	int nYear,nMonth,nDay;
	nYear	= atoi(strYear.GetBuffer(0));
	nMonth	= atoi(strMonth.GetBuffer(0));
	nDay	= atoi(strDay.GetBuffer(0));

	if(!(nMonth<=12 && nMonth>0))
		nMonth=12;
	switch(nMonth) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		{
			if (!(nDay<=31 && nDay>0)) 
				nDay=31;
		}
		break;
	case 2:
		{
			BOOL bLeapYear;
			if((nYear%4==0 && nYear %100 !=0)||(nYear%400 ==0))
				bLeapYear=TRUE;
			else
				bLeapYear=FALSE;
				
			if(!(nDay<=29 && nDay>0) && bLeapYear)
				nDay=29;
			if(!(nDay<=28 && nDay>0) && bLeapYear==FALSE)
				nDay=28;
		}
		break;
	default:
		{
			if (!(nDay<=30 && nDay>0)) 
				nDay=30;
		}
	}
	if(nMonth>=10)
	{
		if(nDay<10)
			str.Format("%d-%d-0%d",nYear,nMonth,nDay);
		else
			str.Format("%d-%d-%d",nYear,nMonth,nDay);
	}
	else
	{
		if(nDay<10)
			str.Format("%d-0%d-0%d",nYear,nMonth,nDay);
		else
			str.Format("%d-0%d-%d",nYear,nMonth,nDay);
	}

	return TRUE;
}

void CFS_FeatureProperty::_GetCurrentDate(CString &strDate)
{
	int nYear,nMonth,nDay;
	CTime	time;
	time   =CTime::GetCurrentTime();
	nYear  =time.GetYear();
	nMonth =time.GetMonth();
	nDay   =time.GetDay();

	if(nMonth>=10)
	{
		if(nDay<10)
			strDate.Format("%d-%d-0%d",nYear,nMonth,nDay);
		else
			strDate.Format("%d-%d-%d",nYear,nMonth,nDay);
	}
	else
	{
		if(nDay<10)
			strDate.Format("%d-0%d-0%d",nYear,nMonth,nDay);
		else
			strDate.Format("%d-0%d-%d",nYear,nMonth,nDay);
	}
}

void CFS_FeatureProperty::OnCancel() 
{
	DestroyWindow ();
}

void CFS_FeatureProperty::PostNcDestroy() 
{	
	CDialog::PostNcDestroy();
	AfxGetMainWnd ()->SendMessage (WM_FEATURE_PROPERTY, 0, 0);
	
	delete this;	
}

void CFS_FeatureProperty::OnExit() 
{
	CDialog::PostNcDestroy();
	AfxGetMainWnd ()->SendMessage (WM_FEATURE_PROPERTY, 0, 0);	
	delete this;	
}

