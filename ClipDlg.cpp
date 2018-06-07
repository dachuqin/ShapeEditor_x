// ClipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "ClipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipDlg dialog


CClipDlg::CClipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClipDlg)
	m_method = -1;
	m_Distance = 0.0;
	//}}AFX_DATA_INIT
}


void CClipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipDlg)
	DDX_Control(pDX, IDC_RADIO1, m_Radio);
	DDX_Radio(pDX, IDC_RADIO1, m_method);
	DDX_Text(pDX, IDC_DISTANCE, m_Distance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClipDlg, CDialog)
	//{{AFX_MSG_MAP(CClipDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipDlg message handlers

BOOL CClipDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Radio.SetCheck(BST_CHECKED);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
