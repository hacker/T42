// T42.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "T42.h"
#include "T42Dlg.h"

#include "T42Frame.h"
#include "T42Document.h"
#include "T42View.h"

#include "SoundsPage.h"
#include "FontsPage.h"
#include "SecretaryPage.h"
#include "GeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CT42App

BEGIN_MESSAGE_MAP(CT42App, CWinApp)
	//{{AFX_MSG_MAP(CT42App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT42App construction

CT42App::CT42App()
	: m_T42STimeLimit(0,0,2,0),
	 m_T42SBytesLimit(2048),
	 m_T42SWinLimit(10)
{
	m_maxT42Callees = 20;
	m_maxT42Callers = 20;
	m_bt42AutosaveLayout = FALSE;
	m_nT42Calls = m_t42Call = -1;
	m_pT42Dlg = NULL;
	memset(&m_fmtT42Local,0,sizeof(m_fmtT42Local));
	memset(&m_fmtT42Remote,0,sizeof(m_fmtT42Remote));
	memset(&m_fmtT42System,0,sizeof(m_fmtT42System));
	m_crT42LocalBG=RGB(255,255,255);
	m_crT42RemoteBG=RGB(255,255,192);
	m_bAwayOnScreenSaver = TRUE;
	m_T42LinesBusy = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CT42App object

CT42App theApp;

/////////////////////////////////////////////////////////////////////////////
// CT42App initialization

BOOL CT42App::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(IDS_REGISTRYKEY);
	m_HelpFile = m_pszHelpFilePath;
	m_HelpFile+=">Standard";
	m_pszHelpFilePath=(LPCTSTR)m_HelpFile;

	m_pTemplate = new CMultiDocTemplate(IDR_T42FRAME,
									   RUNTIME_CLASS(T42Document),
									   RUNTIME_CLASS(T42Frame),
									   RUNTIME_CLASS(T42View)
							);
	AddDocTemplate(m_pTemplate);

	Initialize();
	LoadSettings();

	if(!OpenT42CallsLog()){
		AfxMessageBox(IDS_CALLOG_OPEN_FAILED,MB_OK|MB_ICONSTOP);
		return FALSE;
	}

CT42Dlg dlg;
	m_pMainWnd = &dlg;
	m_pT42Dlg = &dlg;
	dlg.DoModal();
	m_pT42Dlg = NULL;

	SaveSettings();

	if(!CloseT42CallsLog())
		AfxMessageBox(IDS_CALLOG_CLOSE_FAILED,MB_OK|MB_ICONSTOP);


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CT42App::LastCallee(LPCTSTR callee)
{
POSITION p = m_t42Callees.Find(callee);
	if(p){
		m_t42Callees.RemoveAt(p);
		m_t42Callees.AddHead(callee);
		return FALSE;
	}
	m_t42Callees.AddHead(callee);
	while(m_t42Callees.GetCount()>m_maxT42Callees)
		m_t42Callees.RemoveTail();
	return TRUE;
}

void CT42App::SaveSettings()
{
	WriteProfileInt("Settings","AwayOnScreenSaver",m_bAwayOnScreenSaver);

	Klever::SaveStringList(m_t42Callees,"T42HotList");
	Klever::SaveStringList(m_t42Callers,"T42Callers");
	WriteProfileInt("T42Window","AutosaveLayout",m_bt42AutosaveLayout);
	WriteProfileInt("Settings","T42MaxCallers",m_maxT42Callers);
	WriteProfileInt("Settings","T42MaxCallees",m_maxT42Callees);
	WriteProfileString("Settings","T42CallsLog",m_t42CallsFile);
	WriteProfileInt("Settings","T42TalkPort",m_T42TalkPort);

	WriteProfileString("Sounds","T42Bell",m_sndT42Bell);
	WriteProfileString("Sounds","T42Prompt",m_sndT42Prompt);
	WriteProfileInt("Sounds","T42PromptLoop",m_bT42PromptLoop);
	WriteProfileString("Sounds","T42Wake",m_sndT42Wake);

	Klever::WriteProfileString("Secretary","T42Greeting",m_T42SGreeting);
	WriteProfileInt("Secretary","T42BytesLimit",m_T42SBytesLimit);
	WriteProfileInt("Secretary","T42TimeLimit",m_T42STimeLimit.GetTotalSeconds());
	WriteProfileInt("Secretary","T42WinLimit",m_T42SWinLimit);

	WriteProfileInt("Fonts","T42LocalBG",m_crT42LocalBG);
	WriteProfileInt("Fonts","T42RemoteBG",m_crT42RemoteBG);
	WriteProfileBinary("Fonts","T42Local",(LPBYTE)&m_fmtT42Local,sizeof(m_fmtT42Local));
	WriteProfileBinary("Fonts","T42Remote",(LPBYTE)&m_fmtT42Remote,sizeof(m_fmtT42Remote));
	WriteProfileBinary("Fonts","T42System",(LPBYTE)&m_fmtT42System,sizeof(m_fmtT42System));

	FlushT42CallsLog();
}

void CT42App::LoadSettings()
{
	m_bAwayOnScreenSaver = GetProfileInt("Settings","AwayOnScreenSaver",m_bAwayOnScreenSaver);

	Klever::LoadStringList(m_t42Callees,"T42HotList");
	Klever::LoadStringList(m_t42Callers,"T42Callers");
	m_bt42AutosaveLayout = GetProfileInt("T42Window","AutosaveLayout",m_bt42AutosaveLayout);
	m_maxT42Callers = GetProfileInt("Settings","T42MaxCallers",m_maxT42Callers);
	m_maxT42Callees = GetProfileInt("Settings","T42MaxCallees",m_maxT42Callees);
	m_t42CallsFile = GetProfileString("Settings","T42CallsLog",m_t42CallsFile);
	m_T42TalkPort = GetProfileInt("Settings","T42TalkPort",m_T42TalkPort);

	m_sndT42Bell = GetProfileString("Sounds","T42Bell",m_sndT42Bell);
	m_sndT42Prompt = GetProfileString("Sounds","T42Prompt",m_sndT42Prompt);
	m_bT42PromptLoop = GetProfileInt("Sounds","T42PromptLoop",m_bT42PromptLoop);
	m_sndT42Wake = GetProfileString("Sounds","T42Wake",m_sndT42Wake);

	m_T42SGreeting = Klever::GetProfileString("Secretary","T42Greeting",m_T42SGreeting);
	m_T42SBytesLimit = GetProfileInt("Secretary","T42BytesLimit",m_T42SBytesLimit);
	m_T42STimeLimit = CTimeSpan(GetProfileInt("Secretary","T42TimeLimit",m_T42STimeLimit.GetTotalSeconds()));
	m_T42SWinLimit = GetProfileInt("Secretary","T42WinLimit",m_T42SWinLimit);

	m_crT42LocalBG = GetProfileInt("Fonts","T42LocalBG",m_crT42LocalBG);
	m_crT42RemoteBG = GetProfileInt("Fonts","T42RemoteBG",m_crT42RemoteBG);
LPBYTE pdata;
UINT pbytes;
	if(GetProfileBinary("Fonts","T42Local",&pdata,&pbytes)){
		if(pbytes==sizeof(m_fmtT42Local))
			memmove(&m_fmtT42Local,pdata,sizeof(m_fmtT42Local));
		delete pdata;
	}
	if(GetProfileBinary("Fonts","T42Remote",&pdata,&pbytes)){
		if(pbytes==sizeof(m_fmtT42Remote))
			memmove(&m_fmtT42Remote,pdata,sizeof(m_fmtT42Remote));
		delete pdata;
	}
	if(GetProfileBinary("Fonts","T42System",&pdata,&pbytes)){
		if(pbytes==sizeof(m_fmtT42System))
			memmove(&m_fmtT42System,pdata,sizeof(m_fmtT42System));
		delete pdata;
	}
}

BOOL CT42App::LastCaller(LPCTSTR caller)
{
POSITION p = m_t42Callers.Find(caller);
	if(p){
		m_t42Callers.RemoveAt(p);
		m_t42Callers.AddHead(caller);
		return FALSE;
	}
	m_t42Callers.AddHead(caller);
	while(m_t42Callers.GetCount()>m_maxT42Callers)
		m_t42Callers.RemoveTail();
	return TRUE;
}

void CT42App::Initialize()
{
	VERIFY(m_T42SGreeting.LoadString(IDS_DEFAULTGREETING));

	VERIFY(
		m_sndTeaDrop.LoadString(IDS_SND_TEADROP)
		&& m_sndBoilingTeapot.LoadString(IDS_SND_BOILINGTEAPOT)
		&& m_sndTeapotWhistle.LoadString(IDS_SND_TEAPOTWHISTLE)
	);

	m_sndT42Bell = m_sndTeaDrop;
	m_sndT42Prompt = m_sndBoilingTeapot;
	m_bT42PromptLoop = TRUE;
	m_sndT42Wake = m_sndTeapotWhistle;

	VERIFY(m_t42CallsFile.LoadString(IDS_FILE_T42CALLS));
CString exepa;
	VERIFY(GetModuleFileName(m_hInstance,exepa.GetBuffer(_MAX_PATH),_MAX_PATH));
	exepa.ReleaseBuffer();
int bs = exepa.ReverseFind('\\');
	VERIFY(bs>=0);
	exepa = exepa.Left(bs);
	m_t42CallsFile = Klever::GluePathAndFile(exepa,m_t42CallsFile);

servent* se = getservbyname("ntalk","udp");
	if(se)
		m_T42TalkPort = ntohs(se->s_port);
	else
		m_T42TalkPort = 518;
}

BOOL CT42App::StartSound(LPCTSTR  snd,BOOL bLoop)
{
	// Return TRUE if looped sound started.
LPCSTR s = snd;
UINT flags = SND_ASYNC|SND_NODEFAULT|SND_NOWAIT|SND_RESOURCE;
	if(!m_sndTeaDrop.Compare(s)){
		s = MAKEINTRESOURCE(IDW_BEEP_DROP);
	}else if(!m_sndBoilingTeapot.Compare(s)){
		s = MAKEINTRESOURCE(IDW_ANNOUNCE_BOILING);
	}else if(!m_sndTeapotWhistle.Compare(s)){
		s = MAKEINTRESOURCE(IDW_WAKE_WHISTLE);
	}else{
		flags&=~SND_RESOURCE;
		flags|=SND_FILENAME;
	}
	if(bLoop)
		flags|=SND_LOOP;
	if(PlaySound(s,AfxGetInstanceHandle(),flags))
		return bLoop;
	MessageBeep(0xFFFFFFFF);
	return FALSE;
}

void CT42App::StopSound(LPCTSTR snd)
{
LPCSTR s = snd;
UINT flags = SND_ASYNC|SND_NODEFAULT|SND_NOWAIT|SND_RESOURCE|SND_PURGE;
	if(!m_sndTeaDrop.Compare(s)){
		s = MAKEINTRESOURCE(IDW_BEEP_DROP);
	}else if(!m_sndBoilingTeapot.Compare(s)){
		s = MAKEINTRESOURCE(IDW_ANNOUNCE_BOILING);
	}else if(!m_sndTeapotWhistle.Compare(s)){
		s = MAKEINTRESOURCE(IDW_WAKE_WHISTLE);
	}else{
		flags&=~SND_RESOURCE;
		flags|=SND_FILENAME;
	}
	PlaySound(s,AfxGetInstanceHandle(),flags);
}

void CT42App::Options(CWnd* pParent)
{
CSoundsPage sp;
CFontsPage fp;
CSecretaryPage sep;
CGeneralPage gp;
CPropertySheet ps(IDS_TITLE_OPTIONS,pParent);
	ps.AddPage(&gp);
	ps.AddPage(&fp);
	ps.AddPage(&sp);
	ps.AddPage(&sep);

	gp.m_ntalkPort = m_T42TalkPort;

	sp.m_T42Bell = m_sndT42Bell;
	sp.m_T42Prompt = m_sndT42Prompt;
	sp.m_bT42PromptLoop = m_bT42PromptLoop;
	sp.m_T42Wake = m_sndT42Wake;

	memmove(&fp.m_fmtT42Local.m_fmtChar,&m_fmtT42Local,sizeof(fp.m_fmtT42Local.m_fmtChar));
	memmove(&fp.m_fmtT42Remote.m_fmtChar,&m_fmtT42Remote,sizeof(fp.m_fmtT42Remote.m_fmtChar));
	memmove(&fp.m_fmtT42System.m_fmtChar,&m_fmtT42System,sizeof(fp.m_fmtT42System.m_fmtChar));
	fp.m_fmtT42Local.m_bgColor=m_crT42LocalBG;
	fp.m_fmtT42Remote.m_bgColor=m_crT42RemoteBG;

	sep.m_bLimitTime = m_T42STimeLimit.GetTotalSeconds()?TRUE:FALSE;
	sep.m_limitTime = m_T42STimeLimit.GetTotalSeconds()/60;
	sep.m_bLimitBytes = m_T42SBytesLimit?TRUE:FALSE;
	sep.m_limitBytes = m_T42SBytesLimit;
	sep.m_Greeting = m_T42SGreeting;
	sep.m_limitWin = m_T42SWinLimit;
	sep.m_bLimitWin = m_T42SWinLimit?TRUE:FALSE;

	if(ps.DoModal()==IDOK){
		m_T42TalkPort = gp.m_ntalkPort;

		m_sndT42Bell = sp.m_T42Bell;
		m_sndT42Prompt = sp.m_T42Prompt;
		m_bT42PromptLoop = sp.m_bT42PromptLoop;
		m_sndT42Wake = sp.m_T42Wake;

		memmove(&m_fmtT42Local,&fp.m_fmtT42Local.m_fmtChar,sizeof(m_fmtT42Local));
		memmove(&m_fmtT42Remote,&fp.m_fmtT42Remote.m_fmtChar,sizeof(m_fmtT42Remote));
		memmove(&m_fmtT42System,&fp.m_fmtT42System.m_fmtChar,sizeof(m_fmtT42System));
		m_crT42LocalBG=fp.m_fmtT42Local.m_bgColor;
		m_crT42RemoteBG=fp.m_fmtT42Remote.m_bgColor;

		m_T42STimeLimit = CTimeSpan(sep.m_bLimitTime?sep.m_limitTime*60:0);
		m_T42SBytesLimit = sep.m_bLimitBytes?sep.m_limitBytes:0;
		m_T42SWinLimit = sep.m_bLimitWin?sep.m_limitWin:0;
		m_T42SGreeting = sep.m_Greeting;
	}
}

BOOL CT42App::OpenT42CallsLog()
{
	if(!m_T42Calls.Open(m_t42CallsFile,FALSE)){
		if(!m_T42Calls.Create(m_t42CallsFile))
			return FALSE;
		FlushT42CallsLog();
	}
	return TRUE;
}

BOOL CT42App::CloseT42CallsLog()
{
	return m_T42Calls.Close();
}

LONG CT42App::GetT42Calls()
{
	if(m_nT42Calls<0){
		m_nT42Calls=0;
		m_t42Call = -1;
		if(!m_T42Calls.GoFirst())
			return 0;
		m_nT42Calls++;
		while(m_T42Calls.GoNext())
			m_nT42Calls++;
	}
	return m_nT42Calls;
}

BOOL CT42App::GetT42Call(LONG call,CT42CallLogEntry& entry)
{
LONG calls = GetT42Calls();
	if(calls<=0)
		return FALSE;
	call = calls-call-1;
	if(call<0 || calls<=call)
		return FALSE;
	if(m_t42Call<0){
		if(call<(calls/2)){
			VERIFY(m_T42Calls.GoFirst());
			m_t42Call=0;
		}else{
			VERIFY(m_T42Calls.GoLast());
			m_t42Call=calls-1;
		}
	}
	if(call<m_t42Call){
		while(call<m_t42Call){
			VERIFY(m_T42Calls.GoPrev());
			m_t42Call--;
		}
	}else if(call>m_t42Call){
		while(call>m_t42Call){
			VERIFY(m_T42Calls.GoNext());
			m_t42Call++;
		}
	}
	ASSERT(call==m_t42Call);
CTime ct;
	VERIFY(m_T42Calls.GetThis(ct,entry));
	ASSERT(ct==entry.m_Time);
	return TRUE;
}

BOOL CT42App::AddT42Call(CT42CallLogEntry& entry)
{
	m_t42Call=-1;
	if(GetT42Calls()<=0){
		if(m_T42Calls.Add(entry.m_Time,entry)){
			FlushT42CallsLog();
			ASSERT(!m_nT42Calls);
			m_nT42Calls++;
			ASSERT(m_pT42Dlg);
			m_pT42Dlg->OnAddT42Call();
			return TRUE;
		}
		return FALSE;
	}
CT42CallLogEntry cle;
CTimeSpan inc(0,0,0,1);
	while(m_T42Calls.Lookup(entry.m_Time,cle))
		entry.m_Time+=inc;
	if(m_T42Calls.Add(entry.m_Time,entry)){
		FlushT42CallsLog();
		m_nT42Calls++;
		ASSERT(m_pT42Dlg);
		m_pT42Dlg->OnAddT42Call();
		return TRUE;
	}
	return FALSE;
}


BOOL CT42App::DelT42Call(CTime& time)
{
	m_t42Call=-1;
	if(GetT42Calls()<=0)
		return FALSE;
	if(m_T42Calls.Delete(time)){
		FlushT42CallsLog();
		m_nT42Calls--;
		ASSERT(m_pT42Dlg);
		m_pT42Dlg->OnDelT42Call();
		return TRUE;
	}
	return FALSE;
}

BOOL CT42App::UpdateT42Call(CT42CallLogEntry& entry)
{
	m_t42Call=-1;
#ifdef	_DEBUG
CT42CallLogEntry cle;
	ASSERT(m_T42Calls.Lookup(entry.m_Time,cle));
#endif
	m_T42Calls.Add(entry.m_Time,entry);
	FlushT42CallsLog();
	return TRUE;
}

void CT42App::FlushT42CallsLog()
{
	m_T42Calls.m_BT.m_File->Flush();
}
