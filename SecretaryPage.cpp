// SecretaryPage.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "SecretaryPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecretaryPage property page

IMPLEMENT_DYNCREATE(CSecretaryPage, CPropertyPage)

CSecretaryPage::CSecretaryPage() : CPropertyPage(CSecretaryPage::IDD)
{
	//{{AFX_DATA_INIT(CSecretaryPage)
	m_limitBytes = 0;
	m_bLimitBytes = FALSE;
	m_bLimitTime = FALSE;
	m_Greeting = _T("");
	m_limitTime = 0;
	m_bLimitWin = FALSE;
	m_limitWin = 0;
	//}}AFX_DATA_INIT
}

CSecretaryPage::~CSecretaryPage()
{
}

void CSecretaryPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSecretaryPage)
	DDX_Control(pDX, IDC_DOWINLIMIT, m_bLimitWinCtl);
	DDX_Control(pDX, IDC_WINSPIN, m_WinSpinCtl);
	DDX_Control(pDX, IDC_TIMESPIN, m_TimeSpinCtl);
	DDX_Control(pDX, IDC_WINLIMIT, m_limitWinCtl);
	DDX_Control(pDX, IDC_CHARSPIN, m_CharSpinCtl);
	DDX_Control(pDX, IDC_TIMELIMIT, m_limitTimeCtl);
	DDX_Control(pDX, IDC_DOTIMELIMIT, m_bLimitTimeCtl);
	DDX_Control(pDX, IDC_DOBYTELIMIT, m_bLimitBytesCtl);
	DDX_Control(pDX, IDC_BYTELIMIT, m_limitBytesCtl);
	DDX_Text(pDX, IDC_BYTELIMIT, m_limitBytes);
	DDX_Check(pDX, IDC_DOBYTELIMIT, m_bLimitBytes);
	DDX_Check(pDX, IDC_DOTIMELIMIT, m_bLimitTime);
	DDX_Text(pDX, IDC_GREETING, m_Greeting);
	DDX_Text(pDX, IDC_TIMELIMIT, m_limitTime);
	DDX_Check(pDX, IDC_DOWINLIMIT, m_bLimitWin);
	DDX_Text(pDX, IDC_WINLIMIT, m_limitWin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSecretaryPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSecretaryPage)
	ON_BN_CLICKED(IDC_DOBYTELIMIT, OnDobytelimit)
	ON_BN_CLICKED(IDC_DOTIMELIMIT, OnDotimelimit)
	ON_BN_CLICKED(IDC_DOWINLIMIT, OnDowinlimit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecretaryPage message handlers

BOOL CSecretaryPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	SetTimeLimit();
	SetBytesLimit();
	SetWinLimit();
	m_TimeSpinCtl.SetRange(0,60);
	m_WinSpinCtl.SetRange(0,100);
	m_CharSpinCtl.SetRange(0,UD_MAXVAL);
UDACCEL uda = {0,512};                  
	m_CharSpinCtl.SetAccel(1,&uda);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSecretaryPage::SetTimeLimit()
{
	m_limitTimeCtl.EnableWindow(m_bLimitTimeCtl.GetCheck());
}

void CSecretaryPage::SetBytesLimit()
{
	m_limitBytesCtl.EnableWindow(m_bLimitBytesCtl.GetCheck());
}

void CSecretaryPage::SetWinLimit()
{
	m_limitWinCtl.EnableWindow(m_bLimitWinCtl.GetCheck());
}

void CSecretaryPage::OnDobytelimit() 
{
	SetBytesLimit();
}

void CSecretaryPage::OnDotimelimit() 
{
	SetTimeLimit();
}

void CSecretaryPage::OnDowinlimit() 
{
	SetWinLimit();
}

