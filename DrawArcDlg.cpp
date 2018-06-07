// DrawArcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShpEditor.h"
#include "DrawArcDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawArcDlg dialog


CDrawArcDlg::CDrawArcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawArcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawArcDlg)
	m_StarX = 0.0;
	m_Radius = 0.0;
	m_StarY = 0.0;
	m_EndX = 0.0;
	m_EndY = 0.0;
	m_nArcType=-1;
	m_nClockwise=-1;
	//}}AFX_DATA_INIT
}


void CDrawArcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawArcDlg)
	DDX_Control(pDX, IDC_SMALL_ARC, m_ctrArcType);
	DDX_Control(pDX, IDC_FROM_Y, m_ctrFromY);
	DDX_Control(pDX, IDC_FROM_X, m_ctrFromX);
	DDX_Control(pDX, IDC_CLOCKWISE, m_ctrClockwise);
	DDX_Text(pDX, IDC_FROM_X, m_StarX);
	DDX_Text(pDX, IDC_RADIUS, m_Radius);
	DDX_Text(pDX, IDC_FROM_Y, m_StarY);
	DDX_Text(pDX, IDC_TO_X, m_EndX);
	DDX_Text(pDX, IDC_TO_Y, m_EndY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrawArcDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawArcDlg)
	ON_BN_CLICKED(IDC_SMALL_ARC, OnSmallArc)
	ON_BN_CLICKED(IDC_CLOCKWISE, OnClockwise)
	ON_BN_CLICKED(IDC_CLOCKWISE2, OnClockwise2)
	ON_BN_CLICKED(IDC_BIG_ARC, OnBigArc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawArcDlg message handlers

BOOL CDrawArcDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrFromX.EnableWindow(FALSE);
	m_ctrFromY.EnableWindow(FALSE);

	m_nArcType=0;
	m_nClockwise=0;
	m_ctrClockwise.SetCheck(BST_CHECKED);
	m_ctrArcType.SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDrawArcDlg::OnOK() 
{
	UpdateData(TRUE);

	double distance=sqrt(pow(m_EndX-m_StarX,2)+pow(m_EndY-m_StarY,2));
	if(m_Radius<distance/2)
	{
		AfxMessageBox("半径值不能小于两点之间距离的二分之一!", MB_ICONINFORMATION);
		return;
	}
	
	CDialog::OnOK();
}


void CDrawArcDlg::OnClockwise() 
{
	m_nClockwise=0;
	
}

void CDrawArcDlg::OnClockwise2() 
{
	m_nClockwise=1;
}

void CDrawArcDlg::OnSmallArc() 
{
	m_nArcType=0;
	
}

void CDrawArcDlg::OnBigArc() 
{
	m_nArcType=1;
	
}
