// CalleeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "CalleeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalleeDlg dialog


CCalleeDlg::CCalleeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalleeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalleeDlg)
	m_Callee = _T("");
	m_Caller = _T("");
	m_TTY = _T("");
	//}}AFX_DATA_INIT
}


void CCalleeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalleeDlg)
	DDX_Control(pDX, IDC_CALLER, m_CallerCtl);
	DDX_Control(pDX, IDC_CALLEE, m_CalleeCtl);
	DDX_Text(pDX, IDC_CALLEE, m_Callee);
	DDX_CBString(pDX, IDC_CALLER, m_Caller);
	DDV_MaxChars(pDX, m_Caller, 11);
	DDX_CBString(pDX, IDC_TTY, m_TTY);
	DDV_MaxChars(pDX, m_TTY, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalleeDlg, CDialog)
	//{{AFX_MSG_MAP(CCalleeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalleeDlg message handlers

BOOL CCalleeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

CT42App* app = (CT42App*)AfxGetApp();
	ASSERT(app);
POSITION p = app->m_t42Callees.GetHeadPosition();
	m_CalleeCtl.ResetContent();
	while(p){
	CString callee = app->m_t42Callees.GetNext(p);
		m_CalleeCtl.AddString(callee);
		if(m_Callee.IsEmpty())
			m_Callee = callee;
	}
	m_CallerCtl.ResetContent();
	p = app->m_t42Callers.GetHeadPosition();
	while(p){
	CString caller = app->m_t42Callers.GetNext(p);
		m_CallerCtl.AddString(caller);
		if(m_Caller.IsEmpty())
			m_Caller = caller;
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalleeDlg::OnOK() 
{
	UpdateData(TRUE);
	if(m_Caller.IsEmpty())
		VERIFY(m_Caller.LoadString(IDS_DEFAULTCALLER));
CT42App* app = (CT42App*)AfxGetApp();
	ASSERT(app);
	app->LastCaller(m_Caller);
	CDialog::OnOK();
}
