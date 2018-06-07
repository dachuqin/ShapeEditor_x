// FS_FieldsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shpeditor.h"
#include "FS_FieldsDlg.h"
#include "MainFrm.h"
#include "ShpEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_FieldsDlg dialog


CFS_FieldsDlg::CFS_FieldsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFS_FieldsDlg::IDD, pParent)
{
	m_nIndex=0;
	m_strFieldType="整型";
//	m_ListCtrl.InsertColumn(0,"序号",LVCFMT_LEFT,20);

}


void CFS_FieldsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFS_FieldsDlg)
	DDX_Control(pDX, IDC_LIST_FIELDS, m_ListCtrl);
	DDX_Control(pDX, IDC_MODIFY, m_btModify);
	DDX_Control(pDX, IDC_DLETE, m_btDelete);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btAdd);
	DDX_Control(pDX, IDC_COMBO_FIELD_TYPE, m_ctrFieldType);
	DDX_Text(pDX, IDC_EDIT_FIELD, m_strField);
	DDV_MaxChars(pDX, m_strField, 28);
	DDX_CBString(pDX, IDC_COMBO_FIELD_TYPE, m_strFieldType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFS_FieldsDlg, CDialog)
	//{{AFX_MSG_MAP(CFS_FieldsDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_DLETE, OnDlete)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_FIELDS, OnItemchangingListFields)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_FieldsDlg message handlers

void CFS_FieldsDlg::OnButtonAdd()
{
	UpdateData(TRUE);

	if(!CheckRepeat(m_strField))
	{
		MessageBox("不能输入相同的字段!","面编辑工具",MB_OK|MB_ICONWARNING);
		return;
	}
	
	int ctIndex;
	ctIndex=m_ListCtrl.GetItemCount();
	CString	strIndex;
	strIndex.Format("%d",ctIndex+1);

	m_ListCtrl.InsertItem(ctIndex,strIndex);
	m_ListCtrl.SetItemText(ctIndex,1,m_strField);
	m_ListCtrl.SetItemText(ctIndex,2,m_strFieldType);
	m_ListCtrl.UpdateData(FALSE);

	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	IFieldPtr	pField(CLSID_Field);
	IFieldEditPtr	pFieldEdit(pField);
	
	BSTR	BFieldName;
	esriFieldType	FieldType;

	BFieldName=m_strField.AllocSysString();
	FieldType=GetFieldType(m_strFieldType);

	pFieldEdit->put_Name(BFieldName);
	pFieldEdit->put_Type(FieldType);
	
	pTable->AddField(pField);
	InitNewField(BFieldName,FieldType);
}

esriFieldType CFS_FieldsDlg::GetFieldType(CString	strFieldType)
{
	if(strFieldType== "整型")
		return esriFieldTypeSmallInteger;
	if(strFieldType== "长整型")
		return esriFieldTypeInteger;
	if(strFieldType== "浮点型(单精度)")
		return esriFieldTypeSingle;
	if(strFieldType== "浮点型(双精度)")
		return esriFieldTypeDouble;
	if(strFieldType== "字符串")
		return esriFieldTypeString;
	if(strFieldType== "日期")
		return esriFieldTypeDate;
	return esriFieldTypeGlobalID;
}

BOOL CFS_FieldsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ListCtrl.InsertColumn(0,"序号",LVCFMT_LEFT,40);
	m_ListCtrl.InsertColumn(1,"字段",LVCFMT_LEFT,80);
	m_ListCtrl.InsertColumn(2,"类型",LVCFMT_LEFT,80);
	
	m_ctrFieldType.InsertString(0,"整型");
	m_ctrFieldType.InsertString(1,"长整型");
	m_ctrFieldType.InsertString(2,"浮点型(单精度)");
	m_ctrFieldType.InsertString(3,"浮点型(双精度)");
	m_ctrFieldType.InsertString(4,"字符串");
	m_ctrFieldType.InsertString(5,"日期");
	
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();

	UpdateData(FALSE);
	BOOL b=pView->GetEditLayer(&m_pEditLayer);
	if(b!=TRUE)
		return FALSE;	

	ShowFields();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFS_FieldsDlg::OnOK() 
{
	// TODO: Add extra validation here
//	UpdateData(TRUE);
//	AddFieldsToLayer();

	CDialog::OnOK();
}

void CFS_FieldsDlg::AddFieldsToLayer()
{
	HRESULT hr;
	if(m_pEditLayer==NULL) return;

	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	IFieldsPtr	pFields;
	pTable->get_Fields(&pFields);
	long ctField;
	pFields->get_FieldCount(&ctField);
	while (--ctField)
	{
		if(ctField<2)
			break;
		IFieldPtr	pField;
		hr=pFields->get_Field(ctField,&pField);
		hr=pTable->DeleteField(pField);
	}

	int nFieldsCount=0;
	nFieldsCount=m_ListCtrl.GetItemCount();
	if(nFieldsCount==0) return;

	for(int i=0;i<nFieldsCount;i++)
	{
		CString	strFieldName,strFieldType;
		strFieldName=m_ListCtrl.GetItemText(i,1);
		strFieldType=m_ListCtrl.GetItemText(i,2);

		esriFieldType  FieldType;
		FieldType=GetFieldType(strFieldType);
		
		IFieldPtr		pField(CLSID_Field);
		IFieldEditPtr	pFieldEdit;
		pFieldEdit=pField;

		BSTR	BFieldName;
		BFieldName=strFieldName.AllocSysString();
		
		hr=pFieldEdit->put_Name(BFieldName);
		hr=pFieldEdit->put_Type(FieldType);
				
		hr=pTable->AddField(pField);		
	}
}

void CFS_FieldsDlg::ShowFields()
{
	if(m_pEditLayer==NULL) return;
	
	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	IFieldsPtr	pFields;
	pTable->get_Fields(&pFields);
	
	long ctField;
	pFields->get_FieldCount(&ctField);
	
	int nIndex=0;
	for(long i=0;i<ctField;i++)
	{
		IFieldPtr	pField;
		pFields->get_Field(i,&pField);

		VARIANT_BOOL	vtb;
		pField->get_Required(&vtb);

		if(vtb==VARIANT_TRUE)
			continue;
		
		BSTR	BFieldName;
		esriFieldType fieldType;

		pField->get_Name(&BFieldName);
		pField->get_Type(&fieldType);

		CString	strFieldType;		
		strFieldType=esriToCString(fieldType);
		
		CString	strIndex;
		strIndex.Format("%ld",nIndex+1);

		CString	strFieldName;
		strFieldName=(LPCWSTR)BFieldName;

		m_ListCtrl.InsertItem(nIndex,strIndex);
		m_ListCtrl.SetItemText(nIndex,1,(LPCTSTR)strFieldName);
		m_ListCtrl.SetItemText(nIndex,2,(LPCTSTR)strFieldType);
		nIndex++;
	}
	m_ListCtrl.UpdateData(FALSE);
	UpdateData(FALSE);
}

CString CFS_FieldsDlg::esriToCString(esriFieldType fieldtype)
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

CString CFS_FieldsDlg::vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype)
{
	CString	strFieldValue;
	
	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:	
		int nFieldVal;
		nFieldVal=(int)vtFieldValue.iVal;
		strFieldValue.Format("%d",1);
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
		DATE dtFieldVal;
		dtFieldVal=(DATE)vtFieldValue.date;
		strFieldValue.Format("%lf",dtFieldVal);
		break;
	}
	return strFieldValue;
}

void CFS_FieldsDlg::OnDlete() 
{
	int i,iState;
	int nSelectedCount=m_ListCtrl.GetSelectedCount();
	int nItemCount=m_ListCtrl.GetItemCount();
	if(nSelectedCount<1)
		return;
	CString	strFieldName;
	for(i=nItemCount-1;i>=0;i--)
	{
		iState=m_ListCtrl.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
		{
			strFieldName=m_ListCtrl.GetItemText(i,1);
			m_ListCtrl.DeleteItem(i);
		}
	}
	m_ListCtrl.UpdateData(FALSE);

	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	IFieldsPtr	pFields;
	pTable->get_Fields(&pFields);

	BSTR	BFieldName;
	BFieldName=strFieldName.AllocSysString();
	long nIndex;
	pFields->FindFieldByAliasName(BFieldName,&nIndex);
	
	IFieldsEditPtr	pFieldsEdit;
	pFieldsEdit=pFields;
	IFieldPtr	pField;
	pFieldsEdit->get_Field(nIndex,&pField);

	pTable->DeleteField(pField);	
}

void CFS_FieldsDlg::OnModify() 
{
	UpdateData(TRUE);
	POSITION   pos;   
	pos=m_ListCtrl.GetFirstSelectedItemPosition();   
	int   n=m_ListCtrl.GetNextSelectedItem(pos);
	
	CString	strFieldName;
	strFieldName=m_ListCtrl.GetItemText(n,1);

	m_ListCtrl.SetItemText(n,1,m_strField);
	m_ListCtrl.SetItemText(n,2,m_strFieldType);
	m_ListCtrl.UpdateData(FALSE);

	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;
	
	IFieldsPtr	pFields;
	pTable->get_Fields(&pFields);
	
	BSTR	BFieldName;
	BFieldName=strFieldName.AllocSysString();
	long nIndex;
	pFields->FindFieldByAliasName(BFieldName,&nIndex);
	
	IFieldsEditPtr	pFieldsEdit;
	
	IFieldPtr	pDelField;
	pFields->get_Field(nIndex,&pDelField);

	IFieldPtr		pField(CLSID_Field);
	IFieldEditPtr	pFieldEdit(pField);

	BFieldName=m_strField.AllocSysString();
	esriFieldType	FieldType;
	FieldType=GetFieldType(m_strFieldType);

	pFieldEdit->put_Name(BFieldName);
	pFieldEdit->put_Type(FieldType);

	pTable->DeleteField(pDelField);
	pTable->AddField(pField);
}



void CFS_FieldsDlg::OnItemchangingListFields(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nIndex=pNMListView->iItem;
	if(nIndex < 0)
		return;
	
//	POSITION   pos;   
//	pos=m_ListCtrl.GetFirstSelectedItemPosition();   
//	int   n=m_ListCtrl.GetNextSelectedItem(pos);
	m_strField=m_ListCtrl.GetItemText(nIndex,1);
	m_strFieldType=m_ListCtrl.GetItemText(nIndex,2);

	UpdateData(FALSE);
	
	*pResult = 0;
}


void CFS_FieldsDlg::AddFields()
{
	HRESULT hr;
	if(m_pEditLayer==NULL) return;

	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;

	CString strWhereCom;
	strWhereCom="like All";
	BSTR BWhereClause;
	BWhereClause=strWhereCom.AllocSysString();
	
	IQueryFilterPtr	pQueryFilter(CLSID_QueryFilter);
	pQueryFilter->put_WhereClause(BWhereClause);
	
	int nFieldsCount=0;
	nFieldsCount=m_ListCtrl.GetItemCount();
	if(nFieldsCount==0) return;

	for(int i=0;i<nFieldsCount;i++)
	{
		CString	strFieldName,strFieldType;
		strFieldName=m_ListCtrl.GetItemText(i,1);
		strFieldType=m_ListCtrl.GetItemText(i,2);

		esriFieldType  FieldType;
		FieldType=GetFieldType(strFieldType);
		
		IFieldPtr		pField(CLSID_Field);
		IFieldEditPtr	pFieldEdit;
		pFieldEdit=pField;

		BSTR	BFieldName;
		BFieldName=strFieldName.AllocSysString();
		
		hr=pFieldEdit->put_Name(BFieldName);
		hr=pFieldEdit->put_Type(FieldType);
		
//		m_pCursor->UpdateRow();
		hr=pTable->AddField(pField);		
	}
	pTable->Update(pQueryFilter,VARIANT_FALSE,&m_pCursor);
}

BOOL CFS_FieldsDlg::IsHasExist(CString strFieldName)
{
	int nIndex;
	nIndex=m_ListCtrl.GetItemCount();
	for(int i=1;i<nIndex;i++)
	{
		CString	str;
		str=m_ListCtrl.GetItemText(i,1);
		if(str==strFieldName)
			return TRUE;
	}
	return FALSE;
}

void CFS_FieldsDlg::_GetCurrentDate(CString &strDate)
{
	int nYear,nMonth,nDay;
	CTime	time;
	time=CTime::GetCurrentTime();
	nYear=time.GetYear();
	nMonth=time.GetMonth();
	nDay=time.GetDay();
	
	strDate.Format("%d-%d-%d",nYear,nMonth,nDay);	
}

BOOL CFS_FieldsDlg::CheckRepeat(CString strFieldName)
{
	int nIndex;
	nIndex=m_ListCtrl.GetItemCount();
	while (nIndex--) 
	{
		CString		str;
		str=m_ListCtrl.GetItemText(nIndex,1);
		if(str==strFieldName)
			return FALSE;
	}
	return TRUE;
}

void CFS_FieldsDlg::InitNewField(BSTR BFieldName, esriFieldType fieldtype)
{
	HRESULT	hr;
	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=m_pEditLayer;
	ITablePtr	pTable;
	pTable=pGeoLayer;
	
	long nIndex;
	pTable->FindField(BFieldName,&nIndex);

	IQueryFilterPtr	pQueryFilter(CLSID_QueryFilter);

	long RowCount;
	pTable->RowCount(pQueryFilter,&RowCount);
	for(long i=0;i<RowCount;i++)
	{
		IRowPtr		pRow;
		pTable->GetRow(i,&pRow);

		VARIANT vtFieldValue;
		VariantInit(&vtFieldValue);
		
		InitFieldValue(vtFieldValue,fieldtype);

		hr=pRow->put_Value(nIndex,vtFieldValue);
		hr=pRow->Store();
	}
}

void CFS_FieldsDlg::InitFieldValue(VARIANT &vtFieldValue, esriFieldType fieldtype)
{
	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:
		{
			vtFieldValue.vt=VT_I2;
			vtFieldValue.iVal=0;
		}
		break;
	case esriFieldTypeInteger:
		{
			vtFieldValue.vt=VT_I4;
			vtFieldValue.lVal=0;
		}
		break;
	case esriFieldTypeSingle:
		{
			vtFieldValue.vt=VT_R4;
			vtFieldValue.fltVal=0.0;
		}
		break;
	case esriFieldTypeDouble:
		{
			vtFieldValue.vt=VT_R8;
			vtFieldValue.dblVal=0.0;
		}
		break;
	case esriFieldTypeString:
		{
		}
		break;
	case esriFieldTypeDate:
		{
			CTime time;
			time=CTime::GetCurrentTime();
			int nYear,nMonth,nDay;
			nYear=time.GetYear();
			nMonth=time.GetMonth();
			nDay=time.GetDay();

			COleDateTime	vtDate;
			vtDate.SetDate(nYear,nMonth,nDay);

			vtFieldValue.vt=VT_DATE;
			vtFieldValue.date=vtDate;
		}
		break;
	default:
		break;
	}
}
