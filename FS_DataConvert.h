
//**********************************************************************************************//
//								FS_DataConvert.h												//
//		��ͷ�ļ���һ�������⡣��Ҫ������ͬ����֮���ת�������ͼ���ĳ�����Ƿ�Ϸ��ȡ�			//
//																								//
//**********************************************************************************************//

//�жϸ��ַ����Ƿ��ǺϷ�������

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

//�жϸ��ַ����Ƿ��ǺϷ��ĸ���������

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

	// �����ַ����ַ�����ֻ�ܳ���һ��
	if ((strTmp.ReverseFind('E') != nEPos) || (strTmp.ReverseFind('.') != nDPos))
	{
		return FALSE;
	}

	BOOL bSign = (strTmp[0] == char('-'));
	int  nNPos = strTmp.Find("-", 1);

	// ���ų��ֵ�λ���Ƿ����, 
	if (nNPos != -1)
	{	
		// ���û��E���ų���
		if (nEPos == -1)
		{
			return FALSE;
		}

		// ���ű��������E���ź���
		if ((nNPos - nEPos) != 1)	
		{
			return FALSE;
		}

		// ���Ų��������һ���ַ�
		if ((iSize - nNPos) == 1)
		{
			return FALSE;
		}

		// ���ų���λ�ò���
		if (!bSign)
		{
			return FALSE;
		}

		// ����һ�����ų���
		if (strTmp.Find("-", nNPos+1) != -1)
		{
			return FALSE;
		}
	}

	// E����������ַ�
	if ((iSize - nEPos) == 1)
	{
		return FALSE;
	}

	// С����λ���Ƿ����
	if (nDPos != -1)
	{
		// �����E���ų��֣�����С�����λ����E����֮��
		if ((nEPos != -1) && (nDPos > nEPos))
		{
			return FALSE;
		}

		// �������С����
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

//�жϸ��ַ����Ƿ��ǺϷ������������ݣ�����ʽ��ȷ�����ݲ��Ϸ����Զ�����
//����1����ʽ����ͺ��зǷ��ַ����᷵�� FALSE;
//����2�������Ϸ��������Զ�ת���������գ����磺2008-13-33���õ��Ľ���ǣ�2008-12-31������ TRUE;
//����2���ƶ��ڵ��µ���ǰ�ӡ�0�������磺2008-3-9���õ��Ľ���ǣ�2008-03-09������ TRUE;
//����4���ж��Ƿ�������

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
			::MessageBox(NULL,"�����к��зǷ����ţ�������Ϸ����ڣ�","��༭����",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}

	if(_Count!=2)
	{
		::MessageBox(NULL,"��ʽ����!��������ȷ��ʽ��","��༭����",MB_OK|MB_ICONSTOP);
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
//������
//     ��ArcGIS�е��ֶ�����ת���ɺ����ַ������ͱ�ʾ

CString esriToCString(esriFieldType fieldtype)
{
	CString strFieldType;
	
	switch(fieldtype)
	{
	case esriFieldTypeSmallInteger:
		strFieldType = _T("����");
		break;
	case esriFieldTypeInteger:
		strFieldType = _T("������"); 
		break;
	case esriFieldTypeSingle:
		strFieldType = _T("������(������)"); 
		break;
	case esriFieldTypeDouble:
		strFieldType = _T("������(˫����)"); 
		break;
	case esriFieldTypeString:
		strFieldType = _T("�ַ���"); 
		break;
	case esriFieldTypeDate:
		strFieldType = _T("����"); 
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
		strFieldType = _T("��֧������");
	}
	
	return strFieldType;
}

//������
//     ��ArcGIS�е��ֶ�����ת���ɺ����ַ������ͱ�ʾ

esriFieldType CStringToesriFieldType(CString	strFieldType)
{
	if(strFieldType== "����")
		return esriFieldTypeSmallInteger;
	if(strFieldType== "������")
		return esriFieldTypeInteger;
	if(strFieldType== "������(������)")
		return esriFieldTypeSingle;
	if(strFieldType== "������(˫����)")
		return esriFieldTypeDouble;
	if(strFieldType== "�ַ���")
		return esriFieldTypeString;
	if(strFieldType== "����")
		return esriFieldTypeDate;
	return esriFieldTypeGlobalID;
}
//���������ַ�����ʾ������ת����COleDateTime����
//���磺str="2008-04-24"
void GetDateFromStr(CString strTm, COleDateTime &vtDate)
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

//�������������ַ����е����֣���ָ��������ת����VARIANT����
VARIANT StrToVARIANT(CString strFieldValue, esriFieldType fieldtype)
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

//������������VARIANT����ת�����ַ��������е�����

CString vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype)
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