// T42AnnounceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "T42AnnounceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T42AnnounceDlg dialog


T42AnnounceDlg::T42AnnounceDlg(TalkCtlMessage& rq,CWnd* pParent /*=NULL*/)
	: CDialog(T42AnnounceDlg::IDD, pParent), m_RQ(rq)
{
	//{{AFX_DATA_INIT(T42AnnounceDlg)
	m_Callee = _T("");
	m_Caller = _T("");
	m_TTY = _T("");
	//}}AFX_DATA_INIT
	m_Callee = rq.m_RName;
	m_Caller = rq.m_LName;
	m_Caller+= '@';
	m_Caller+= inet_ntoa(((sockaddr_in*)&rq.m_Addr)->sin_addr);
	m_TTY = rq.m_RTTY;
	m_asyncRequest=NULL;
	m_timeOut = 30;
	m_ipCaller = m_Caller;
	m_bLooped=FALSE;
}


void T42AnnounceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T42AnnounceDlg)
	DDX_Control(pDX, IDC_CALLEE, m_CalleeCtl);
	DDX_Control(pDX, IDC_TTY, m_TTYCtl);
	DDX_Control(pDX, IDOK, m_YesCtl);
	DDX_Control(pDX, IDCANCEL, m_NotMeCtl);
	DDX_Control(pDX, IDC_SECRETARY, m_SecretaryCtl);
	DDX_Control(pDX, IDC_CALLER, m_CallerCtl);
	DDX_Text(pDX, IDC_CALLEE, m_Callee);
	DDX_Text(pDX, IDC_CALLER, m_Caller);
	DDX_Text(pDX, IDC_TTY, m_TTY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T42AnnounceDlg, CDialog)
	//{{AFX_MSG_MAP(T42AnnounceDlg)
	ON_MESSAGE(WM_SOURCERESOLVED, OnSourceResolved)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SECRETARY, OnSecretary)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T42AnnounceDlg message handlers

BOOL T42AnnounceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_asyncRequest = WSAAsyncGetHostByAddr(m_hWnd,WM_SOURCERESOLVED,
		(CHAR*)&((sockaddr_in*)&m_RQ.m_Addr)->sin_addr,
		4,AF_INET,
		m_ResolveBuffer,sizeof(m_ResolveBuffer)
	);

CT42App* app = (CT42App*)AfxGetApp();
	ASSERT(app);
	m_bLooped = app->StartSound(app->m_sndT42Prompt,app->m_bT42PromptLoop);
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	SetTimer(timerTimeout,m_timeOut*1000,NULL);
CFont* f = GetFont();
LOGFONT lf;
	if(f->GetLogFont(&lf)){
		if(lf.lfWeight)
			lf.lfWeight = 1000-lf.lfWeight;
		else
			lf.lfWeight = 700;
		if(m_Font.CreateFontIndirect(&lf)){
			m_CalleeCtl.SetFont(&m_Font);
			m_CallerCtl.SetFont(&m_Font);
			m_TTYCtl.SetFont(&m_Font);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT T42AnnounceDlg::OnSourceResolved(WPARAM,LPARAM lP)
{
	if(WSAGETASYNCERROR(lP)){
		TRACE1("Failed to resolve callee's host: %ld\n",WSAGETASYNCERROR(lP));
		return -1;
	}
hostent* he = (hostent*)m_ResolveBuffer;
	m_Caller = m_RQ.m_LName;
	m_Caller+= '@';
	m_Caller+= he->h_name;
	m_CallerCtl.SetWindowText(m_Caller);
	m_asyncRequest=NULL;
	return 0;
}

void T42AnnounceDlg::OnDestroy() 
{
	if(m_bLooped){
	CT42App* app = (CT42App*)AfxGetApp();
		ASSERT(app);
		app->StopSound(app->m_sndT42Prompt);
	}
	m_bLooped=FALSE;
	if(m_asyncRequest){
		WSACancelAsyncRequest(m_asyncRequest);
		m_asyncRequest=NULL;
	}
	CDialog::OnDestroy();
}

void T42AnnounceDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==timerTimeout){
		KillTimer(timerTimeout);
		UpdateData(TRUE);
		// *** OnPromptTimeout?
		EndDialog(IDC_SECRETARY);
	}else
		CDialog::OnTimer(nIDEvent);
}

void T42AnnounceDlg::OnSecretary() 
{
	UpdateData(TRUE);
	EndDialog(IDC_SECRETARY);
}
