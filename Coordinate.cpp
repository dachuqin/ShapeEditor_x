// Coordinate.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "Coordinate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoordinate dialog


CCoordinate::CCoordinate(CWnd* pParent /*=NULL*/)
	: CDialog(CCoordinate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoordinate)
	m_X = 0.0;
	m_Y = 0.0;
	
	//}}AFX_DATA_INIT
}


void CCoordinate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoordinate)
	DDX_Text(pDX, IDC_EDIT_X, m_X);
	DDX_Text(pDX, IDC_EDIT_Y, m_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoordinate, CDialog)
	//{{AFX_MSG_MAP(CCoordinate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoordinate message handlers


