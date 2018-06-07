// DistanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "DistanceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistanceDlg dialog


CDistanceDlg::CDistanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDistanceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDistanceDlg)
	m_dDistance = 0.0;
	//}}AFX_DATA_INIT
}


void CDistanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDistanceDlg)
	DDX_Text(pDX, IDC_DISTANCE, m_dDistance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDistanceDlg, CDialog)
	//{{AFX_MSG_MAP(CDistanceDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDistanceDlg message handlers
