// StarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "StarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStarDlg dialog


CStarDlg::CStarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStarDlg)
	m_nState = -1;
	//}}AFX_DATA_INIT
}


void CStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStarDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_nState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStarDlg, CDialog)
	//{{AFX_MSG_MAP(CStarDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStarDlg message handlers
