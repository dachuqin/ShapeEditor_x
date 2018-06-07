
//**********************************************************************************************//
//								FS_DataConvert.h												//
//		该头文件是一个函数库。主要包含不同类型之间的转换函数和检验某类型是否合法等。			//
//																								//
//**********************************************************************************************//

//判断该字符串是否是合法的整型

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

//判断该字符串是否是合法的浮点型数据

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

//判断该字符串是否是合法的日期型数据，若格式正确，数据不合法会自动纠正
//功能1：格式错误和含有非法字符都会返回 FALSE;
//功能2：超过合法的月日自动转成最后的月日；例如：2008-13-33；得到的结果是：2008-12-31；返回 TRUE;
//功能2：制动在单月单日前加“0”；例如：2008-3-9；得到的结果是：2008-03-09；返回 TRUE;
//功能4：判断是否是闰年

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
//描述：
//     把ArcGIS中的字段类型转换成汉字字符串类型表示

CString esriToCString(esriFieldType fieldtype)
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

//描述：
//     把ArcGIS中的字段类型转换成汉字字符串类型表示

esriFieldType CStringToesriFieldType(CString	strFieldType)
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
//描述：把字符串表示的日期转换成COleDateTime类型
//例如：str="2008-04-24"
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

//功能描述：把字符串中的数字，按指定的类型转换成VARIANT类型
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

//功能描述：把VARIANT类型转换成字符串类型中的数字

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