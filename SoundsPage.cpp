// SoundsPage.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "SoundsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundsPage property page

IMPLEMENT_DYNCREATE(CSoundsPage, CPropertyPage)

CSoundsPage::CSoundsPage() : CPropertyPage(CSoundsPage::IDD)
{
	//{{AFX_DATA_INIT(CSoundsPage)
	m_T42Bell = _T("");
	m_T42Prompt = _T("");
	m_bT42PromptLoop = FALSE;
	m_T42Wake = _T("");
	//}}AFX_DATA_INIT
}

CSoundsPage::~CSoundsPage()
{
}

void CSoundsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundsPage)
	DDX_Control(pDX, IDC_T42WAKE_PLAY, m_T42WakePlayCtl);
	DDX_Control(pDX, IDC_T42PROMPT_PLAY, m_T42PromptPlayCtl);
	DDX_Control(pDX, IDC_T42BELL_PLAY, m_T42BellPlayCtl);
	DDX_Control(pDX, IDC_T42WAKE_BROWSE, m_T42WakeBrowseCtl);
	DDX_Control(pDX, IDC_T42WAKE, m_T42WakeCtl);
	DDX_Control(pDX, IDC_T42PROMPT_BROWSE, m_T42PromptBrowseCtl);
	DDX_Control(pDX, IDC_T42PROMPT, m_T42PromptCtl);
	DDX_Control(pDX, IDC_T42BELL_BROWSE, m_T42BellBrowseCtl);
	DDX_Control(pDX, IDC_T42BELL, m_T42BellCtl);
	DDX_CBString(pDX, IDC_T42BELL, m_T42Bell);
	DDX_CBString(pDX, IDC_T42PROMPT, m_T42Prompt);
	DDX_Check(pDX, IDC_T42PROMPT_LOOP, m_bT42PromptLoop);
	DDX_CBString(pDX, IDC_T42WAKE, m_T42Wake);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSoundsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSoundsPage)
	ON_BN_CLICKED(IDC_T42BELL_BROWSE, OnT42bellBrowse)
	ON_BN_CLICKED(IDC_T42PROMPT_BROWSE, OnT42promptBrowse)
	ON_BN_CLICKED(IDC_T42WAKE_BROWSE, OnT42wakeBrowse)
	ON_BN_CLICKED(IDC_T42BELL_PLAY, OnT42bellPlay)
	ON_BN_CLICKED(IDC_T42PROMPT_PLAY, OnT42promptPlay)
	ON_BN_CLICKED(IDC_T42WAKE_PLAY, OnT42wakePlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundsPage message handlers

BOOL CSoundsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
CT42App* app = (CT42App*)AfxGetApp();
	ASSERT(app);
	m_T42BellCtl.ResetContent();
	m_T42BellCtl.AddString(app->m_sndTeaDrop);
	m_T42PromptCtl.ResetContent();
	m_T42PromptCtl.AddString(app->m_sndBoilingTeapot);
	m_T42WakeCtl.ResetContent();
	m_T42WakeCtl.AddString(app->m_sndTeapotWhistle);

HICON i = app->LoadIcon(IDI_BROWSE);
	m_T42BellBrowseCtl.SetIcon(i);
	m_T42PromptBrowseCtl.SetIcon(i);
	m_T42WakeBrowseCtl.SetIcon(i);
	i = app->LoadIcon(IDI_PREPLAY);
	m_T42BellPlayCtl.SetIcon(i);
	m_T42PromptPlayCtl.SetIcon(i);
	m_T42WakePlayCtl.SetIcon(i);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSoundsPage::OnT42bellBrowse() 
{
	BrowseForSound(m_T42BellCtl);
}

void CSoundsPage::OnT42promptBrowse() 
{
	BrowseForSound(m_T42PromptCtl);
}

void CSoundsPage::OnT42wakeBrowse() 
{
	BrowseForSound(m_T42WakeCtl);
}

void CSoundsPage::BrowseForSound(CComboBox& ctl)
{
CString f;
	ctl.GetWindowText(f);
CString filter;
	filter.LoadString(IDS_FILTER_WAV);
CFileDialog fd(TRUE,NULL,(LPCTSTR)f,
			   OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY
			   |OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST,
			   filter,this);
CString title;
	title.LoadString(IDS_TITLE_WAV);
	fd.m_ofn.lpstrTitle=(LPCTSTR)title;
	if(fd.DoModal()==IDOK)
		ctl.SetWindowText(fd.GetPathName());
}

void CSoundsPage::OnT42bellPlay() 
{
	PlayIt(m_T42BellCtl);
}
void CSoundsPage::OnT42promptPlay() 
{
	PlayIt(m_T42PromptCtl);
}
void CSoundsPage::OnT42wakePlay() 
{
	PlayIt(m_T42WakeCtl);
}

void CSoundsPage::PlayIt(CComboBox& ctl,BOOL bLoop)
{
CString s;
	ctl.GetWindowText(s);
CT42App* app = (CT42App*)AfxGetApp();
	ASSERT(app);
	app->StartSound(s,bLoop);
}
