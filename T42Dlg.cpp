// T42Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "T42Dlg.h"

#include "T42Frame.h"
#include "T42AnnounceDlg.h"
#include "T42Document.h"
#include "T42Secretary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnKlevernet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_KLEVERNET, OnKlevernet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CAboutDlg::OnKlevernet() 
{
CString url;
	VERIFY(url.LoadString(IDS_KLEVERNET_URL));
	ShellExecute(::GetDesktopWindow(),"open",url,NULL,NULL,SW_SHOWMAXIMIZED);	
}

/////////////////////////////////////////////////////////////////////////////
// CT42Dlg dialog

CT42Dlg::CT42Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CT42Dlg::IDD, pParent),
	  m_sizeMin(0,0)
{
	//{{AFX_DATA_INIT(CT42Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIconEmpty = m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIconFull = AfxGetApp()->LoadIcon(IDI_FULLCUP);
	m_newCalls = 0;
	m_daemonSocket = INVALID_SOCKET;
	m_talkLifetime = CTimeSpan(0,0,3,0);	// 3 mins..
	m_trackTalkID = 1;
	m_bmpBack.LoadBitmap(IDB_BACK);
	m_bmpBack.GetBitmap(&m_bitmapBack);
	m_bExiting = m_bShown = FALSE;
	m_hExFW = NULL;
	m_marginX = m_marginY = m_gapY = 0;
	m_bAway = FALSE;
	m_onCall = 0;
	m_onCallAway = IDC_SECRETARY;
	LoadSettings();
}

CT42Dlg::~CT42Dlg()
{
	SaveSettings();
}

void CT42Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CT42Dlg)
	DDX_Control(pDX, IDOK, m_ExitCtl);
	DDX_Control(pDX, IDC_TALK, m_TeaCtl);
	DDX_Control(pDX, IDC_AWAY, m_AwayCtl);
	DDX_Control(pDX, ID_HELP, m_HelpCtl);
	DDX_Control(pDX, IDC_OPTIONS, m_OptionsCtl);
	DDX_Control(pDX, IDC_ONCALLAWAY, m_OnCallAwayCtl);
	DDX_Control(pDX, IDC_ONCALL, m_OnCallCtl);
	DDX_Control(pDX, IDC_CALLS, m_CallsCtl);
	DDX_Control(pDX, IDC_PREVIEW, m_PreviewCtl);
	//}}AFX_DATA_MAP
	if(pDX->m_bSaveAndValidate){
		m_onCall = GetOnCtl(m_OnCallCtl);
		m_onCallAway = GetOnCtl(m_OnCallAwayCtl);
	}else{
		SetOnCtl(m_onCall,m_OnCallCtl);
		SetOnCtl(m_onCallAway,m_OnCallAwayCtl);
	}
}

BEGIN_MESSAGE_MAP(CT42Dlg, CDialog)
	//{{AFX_MSG_MAP(CT42Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TALK, OnTalk)
	ON_MESSAGE(WM_DAEMON, OnDaemon)
	ON_WM_CREATE()
	ON_MESSAGE(WM_TRAYICON, OnTrayIcon)
	ON_WM_WINDOWPOSCHANGING()
	ON_COMMAND(ID_TRAY_EXIT, OnTrayExit)
	ON_COMMAND(ID_TRAY_OPTIONS, OnTrayOptions)
	ON_COMMAND(ID_TRAY_SHOWMAINWINDOW, OnTrayShowmainwindow)
	ON_COMMAND(ID_TRAY_T42, OnTrayT42)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_CALLS, OnGetdispinfoCalls)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CALLS, OnItemchangedCalls)
	ON_NOTIFY(NM_RCLICK, IDC_CALLS, OnRclickCalls)
	ON_COMMAND(ID_CALLLOG_CALLBACK, OnCalllogCallback)
	ON_COMMAND(ID_CALLLOG_DELETE, OnCalllogDelete)
	ON_COMMAND(ID_CALLLOG_SAVETOFILE, OnCalllogSavetofile)
	ON_COMMAND(ID_CALLLOG_EMPTYLOG, OnCalllogEmptylog)
	ON_NOTIFY(LVN_DELETEITEM, IDC_CALLS, OnDeleteitemCalls)
	ON_MESSAGE(WM_UPDATEPREVIEW, OnUpdatePreview)
	ON_NOTIFY(LVN_KEYDOWN, IDC_CALLS, OnKeydownCalls)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_CALLLOG_MARKASNEW, OnCalllogMarkasnew)
	ON_COMMAND(ID_CALLLOG_MARKASPROCESSED, OnCalllogMarkasprocessed)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_AWAY, OnAway)
	ON_CBN_SELENDOK(IDC_ONCALL, OnSelendokOncall)
	ON_CBN_SELENDOK(IDC_ONCALLAWAY, OnSelendokOncallaway)
	ON_COMMAND(ID_TRAY_AWAY, OnTrayAway)
	ON_WM_TIMER()
	ON_WM_QUERYENDSESSION()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT42Dlg message handlers

BOOL CT42Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

CT42App* app = (CT42App*)AfxGetApp();
{
int x = -1,y = -1,cx = -1,cy = -1;
	x = app->GetProfileInt("T42MainWindow","X",x);
	y = app->GetProfileInt("T42MainWindow","Y",y);
	cx = app->GetProfileInt("T42MainWindow","Width",cx);
	cy = app->GetProfileInt("T42MainWindow","Height",cy);
	if(cx>0 && cy>0)
		SetWindowPos(NULL,x,y,cx,cy,SWP_NOACTIVATE|SWP_NOZORDER);
}

	::SetForegroundWindow(m_hExFW);

	m_PreviewCtl.ModifyStyle(0,WS_VSCROLL);
	m_PreviewCtl.SetOptions(ECOOP_SET,ECO_AUTOWORDSELECTION|
		ECO_AUTOVSCROLL|ECO_AUTOHSCROLL|ECO_READONLY|ECO_SELECTIONBAR);
	m_PreviewCtl.SetReadOnly(TRUE);
	m_PreviewCtl.SetTargetDevice(NULL,0);
	m_PreviewCtl.SetBackgroundColor(FALSE,((CT42App*)AfxGetApp())->m_crT42RemoteBG);

	m_CallsCtl.SetBkColor(RGB(0,192,0));
	m_CallsCtl.SetTextColor(RGB(255,255,0));
	m_CallsCtl.SetTextBkColor(RGB(0,192,0));
	m_Images.Create(16,16,TRUE,2,1);
	m_iNew = m_Images.Add(AfxGetApp()->LoadIcon(IDI_T42CALLNEW));
	m_iProcessed = m_Images.Add(AfxGetApp()->LoadIcon(IDI_T42CALLPROCESSED));
	ASSERT( m_iNew>=0 && m_iProcessed>=0);
	m_CallsCtl.SetImageList(&m_Images,LVSIL_NORMAL);
	m_CallsCtl.SetImageList(&m_Images,LVSIL_SMALL);
	m_CallsCtl.SetImageList(&m_Images,LVSIL_STATE);
	InitCalls();

CRect wrci, wrco;
	GetWindowRect(&wrco);
	GetClientRect(&wrci);
	// Pull out margins
CRect crc;
	m_CallsCtl.GetWindowRect(crc); ScreenToClient(crc);
	m_marginX = crc.left;
CRect trc;
	m_TeaCtl.GetWindowRect(trc); ScreenToClient(trc);
	m_marginY = trc.top;
CRect prc;
	m_PreviewCtl.GetWindowRect(prc); ScreenToClient(prc);
	m_gapY = prc.top-crc.bottom;

	RecalcLayout();
	SetColumnWidths();

	// Calc minimum size
CRect arc;
	m_AwayCtl.GetWindowRect(arc); ScreenToClient(arc);
	m_sizeMin.cx = arc.right+m_marginX*2+trc.Width()+wrco.Width()-wrci.Width();
	m_sizeMin.cy = crc.top+m_marginY+m_gapY+40*2+wrco.Height()-wrci.Height();

	SetTimer(timerMinutes,60000,NULL);

	m_daemonSocket = socket(AF_INET,SOCK_DGRAM,0);
	if(m_daemonSocket == INVALID_SOCKET){
		TRACE0("Failed to initialize daemon\n");
		return TRUE;
	}
sockaddr_in da;
	da.sin_family = AF_INET;
	da.sin_port = htons(app->m_T42TalkPort);
	da.sin_addr.s_addr = INADDR_ANY;
	if(bind(m_daemonSocket,(sockaddr*)&da,sizeof(da))){
		AfxMessageBox(IDS_DAEMON_FAIL,MB_OK|MB_ICONSTOP);
		TRACE0("Failed to bind daemon socket\n");
		return TRUE;
	}
	if(WSAAsyncSelect(m_daemonSocket,m_hWnd,WM_DAEMON,FD_READ)){
		AfxMessageBox(IDS_DAEMON_FAIL,MB_OK|MB_ICONSTOP);
		TRACE0("AsyncSelect failed on daemon socket\n");
		return TRUE;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CT42Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX){
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}else{
		if(nID==SC_SCREENSAVE){
			TRACE0("SCRS\n");
		}else if(nID==SC_MONITORPOWER){
			TRACE0("MP\n");
		}else
			TRACE1("SYSCOM: 0x%04X\n",nID);
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CT42Dlg::OnDestroy()
{
CT42App* app = (CT42App*)AfxGetApp();
CDocTemplate* pTemplate = app->m_pTemplate;
	pTemplate->CloseAllDocuments(FALSE);
CRect rc;
	GetWindowRect(rc);
	app->WriteProfileInt("T42MainWindow","X",rc.left);
	app->WriteProfileInt("T42MainWindow","Y",rc.top);
	app->WriteProfileInt("T42MainWindow","Width",rc.Width());
	app->WriteProfileInt("T42MainWindow","Height",rc.Height());
	
NOTIFYICONDATA nid;
	memset(&nid,0,sizeof(nid));
	nid.cbSize=sizeof(nid);
	nid.hWnd=m_hWnd;
	nid.uID=IDC_TRAYICON;
	nid.uFlags=0;
	VERIFY(Shell_NotifyIcon(NIM_DELETE,&nid));

	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CT42Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	CPaintDC pDC(this);
	CDC bmpDC;
		bmpDC.CreateCompatibleDC(&pDC);
		bmpDC.SelectObject(&m_bmpBack);
	CRect rc;
		GetClientRect(&rc);
		for(int x=-m_bitmapBack.bmWidth*2/4;x<rc.Width();x+=m_bitmapBack.bmWidth)
			for(int y=-m_bitmapBack.bmHeight*2/4;y<rc.Height();y+=m_bitmapBack.bmHeight)
				pDC.BitBlt(x,y,m_bitmapBack.bmWidth,m_bitmapBack.bmHeight,&bmpDC,0,0,SRCCOPY);
		bmpDC.DeleteDC();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CT42Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CT42Dlg::OnTalk() 
{
CDocTemplate* pTemplate = ((CT42App*)AfxGetApp())->m_pTemplate;
T42Document* pDoc = (T42Document*)pTemplate->OpenDocumentFile(NULL);
	ASSERT_KINDOF(T42Document,pDoc);
	pDoc->Talk();
}

LRESULT CT42Dlg::OnDaemon(WPARAM wP,LPARAM lP)
{
	if(WSAGETSELECTERROR(lP)){
		TRACE1("Error on daemon socket: %ld\n", WSAGETSELECTERROR(lP));
		return -1;
	}
	ASSERT(WSAGETSELECTEVENT(lP)&FD_READ);
TalkCtlMessage rq;
	if(recv(m_daemonSocket,(char*)&rq,sizeof(rq),0)!=sizeof(rq)){
		TRACE("Bad packet size on daemon socket\n");
		return -1;
	}
TalkCtlResponse rp;
	TRACE3("*DAEMON-REQUEST*\nV: %d, T: %d, ID: %ld\n",
		(int)rq.m_Version, (int)rq.m_Type, ntohl(rq.m_ID)
	);
	TRACE2("ADDR: %s:%d\n",
		inet_ntoa(((sockaddr_in*)&rq.m_Addr)->sin_addr),
		ntohs(((sockaddr_in*)&rq.m_Addr)->sin_port)
	);
	TRACE2("CTL ADDR: %s:%d\n",
		inet_ntoa(((sockaddr_in*)&rq.m_ctlAddr)->sin_addr),
		ntohs(((sockaddr_in*)&rq.m_ctlAddr)->sin_port)
	);
	TRACE3("PID: %ld, LU: %s, RU: %s\n",
		rq.m_PID,rq.m_LName,rq.m_RName
	);
	TRACE1("TTY: %s\n---\n",rq.m_RTTY);

	rp.m_Version = talkCtlVersion;
	rp.m_Type = rq.m_Type;
	rp.m_ID = htonl(0);
	rp.m_Answer = talkCtlReserved;
sockaddr_in a;
	memmove(&a,&rq.m_ctlAddr,sizeof(a));
	a.sin_family = ntohs(a.sin_family);
	do{
		if(rq.m_Version!=talkCtlVersion){
			rp.m_Answer = talkCtlBadVersion;
			break;
		}
		if(rq.m_Addr.sa_family!=htons(AF_INET)){
			rp.m_Answer = talkCtlBadAddr;
			break;
		}
		if(rq.m_ctlAddr.sa_family!=htons(AF_INET)){
			rp.m_Answer = talkCtlBadCtlAddr;
			break;
		}
		switch(rq.m_Type){
		case talkCtlReqAnnounce:
			{
			CTime ct = CTime::GetCurrentTime();
			POSITION p = m_talks.GetHeadPosition();
			BOOL bFound = FALSE;
				while(p){
				POSITION dp = p;
				CTTable& t = m_talks.GetNext(p);
					if((ct-t.m_Time)>m_talkLifetime){
						TRACE0("Removing Expired request\n");
						m_talks.RemoveAt(dp);
					}else if(t==rq){
						t.m_Time = ct;
						rp.m_ID = t.m_RQ.m_ID;
						bFound = TRUE;
						break;
					}
				}
				if(bFound){
					// ** handle re-announces
					rp.m_Answer = talkCtlSuccess;
					break;
				}
			UINT nAction = m_bAway?m_onCallAway:m_onCall;
			T42AnnounceDlg ad(rq);
			CT42App* app = (CT42App*)AfxGetApp();
				if(
					nAction==IDC_SECRETARY
					&& app->m_T42SWinLimit
					&& app->m_T42LinesBusy>=app->m_T42SWinLimit
				)
					nAction = IDC_NOTHERE;	// ??
				if(nAction!=IDC_SECRETARY && nAction!=IDC_NOTHERE
					&& nAction!=IDC_REFUSE && nAction!=IDCANCEL
				){
				CTTable t;
					memmove(&t.m_RQ,&rq,sizeof(t.m_RQ));
					t.m_Time = ct;
					t.m_RQ.m_ID = rp.m_ID = htonl(m_trackTalkID++);
					m_talks.AddHead(t);
					rp.m_Answer = talkCtlSuccess;
					if(sendto(m_daemonSocket,(char*)&rp,sizeof(rp),0,(sockaddr*)&a,sizeof(a))!=sizeof(rp)){
						TRACE0("Failed to send daemon response\n");
						return -1;
					}
				HWND hFW = ::GetForegroundWindow();
					nAction = ad.DoModal();
					::SetForegroundWindow(hFW);
				}else{
					if(nAction==IDC_NOTHERE || nAction==IDC_REFUSE){
						rp.m_Answer=(nAction==IDC_NOTHERE)?talkCtlNotHere:talkCtlPermissionDenied;
						break;
					}
				CTTable t;
					memmove(&t.m_RQ,&rq,sizeof(t.m_RQ));
					t.m_Time = ct;
					t.m_RQ.m_ID = rp.m_ID = htonl(m_trackTalkID++);
					m_talks.AddHead(t);
					rp.m_Answer = talkCtlSuccess;
					if(sendto(m_daemonSocket,(char*)&rp,sizeof(rp),0,(sockaddr*)&a,sizeof(a))!=sizeof(rp)){
						TRACE0("Failed to send daemon response\n");
						return -1;
					}
				}
				rp.m_Answer=talkCtlReserved;
				switch(nAction){
				case IDOK:
					{
					CDocTemplate* pTemplate = ((CT42App*)AfxGetApp())->m_pTemplate;
					T42Document* pDoc = (T42Document*)pTemplate->OpenDocumentFile(NULL);
						ASSERT_KINDOF(T42Document,pDoc);
						pDoc->Talk(ad.m_Callee,ad.m_ipCaller,NULL);
					}
					break;
				case IDC_SECRETARY:
					{
					HWND hFW = ::GetForegroundWindow();
					CDocTemplate* pTemplate = ((CT42App*)AfxGetApp())->m_pTemplate;
					T42Document* pDoc = (T42Document*)pTemplate->OpenDocumentFile("hidden");
						ASSERT_KINDOF(T42Document,pDoc);
						pDoc->AttachRobot(new CT42Secretary);
						pDoc->Talk(ad.m_Callee,ad.m_ipCaller,NULL);
						::SetForegroundWindow(hFW);
					}
					break;
				case IDCANCEL:
					break;
				}
			}
			break;
		case talkCtlReqLeaveInvite:
			{
			CTime ct = CTime::GetCurrentTime();
			POSITION p = m_talks.GetHeadPosition();
				while(p){
				POSITION dp = p;
				CTTable& t = m_talks.GetNext(p);
					if((ct-t.m_Time)>m_talkLifetime){
						TRACE0("Removing Expired request\n");
						m_talks.RemoveAt(dp);
					}else if(t==rq){
						t.m_Time = ct;
						rp.m_ID = rq.m_ID;
						rp.m_Answer = talkCtlSuccess;
						break;
					}
				}
				if(rp.m_Answer!=talkCtlSuccess){
				CTTable t;
					memmove(&t.m_RQ,&rq,sizeof(t.m_RQ));
					t.m_Time = ct;
					t.m_RQ.m_ID = rp.m_ID = htonl(m_trackTalkID++);
					m_talks.AddHead(t);
					rp.m_Answer = talkCtlSuccess;
				}
			}
			break;
		case talkCtlReqLookUp:
			{
			CTime ct = CTime::GetCurrentTime();
			POSITION p = m_talks.GetHeadPosition();
				while(p){
				POSITION dp = p;
				CTTable& t = m_talks.GetNext(p);
					if((ct-t.m_Time)>m_talkLifetime){
						TRACE0("Removing Expired request\n");
						m_talks.RemoveAt(dp);
					}else if(t.Match(rq)){
						rp.m_ID = t.m_RQ.m_ID;
						memmove(&rp.m_Addr,&t.m_RQ.m_Addr,sizeof(rp.m_Addr));
						rp.m_Answer = talkCtlSuccess;
						break;
					}
				}
				if(rp.m_Answer!=talkCtlSuccess)
					rp.m_Answer = talkCtlNotHere;
			}
			break;
		case talkCtlReqDelete:
			{
			CTime ct = CTime::GetCurrentTime();
			POSITION p = m_talks.GetHeadPosition();
				while(p){
				POSITION dp = p;
				CTTable& t = m_talks.GetNext(p);
					if((ct-t.m_Time)>m_talkLifetime){
						TRACE0("Removing Expired request\n");
						m_talks.RemoveAt(dp);
					}else if(t.m_RQ.m_ID == rq.m_ID){
						m_talks.RemoveAt(dp);
						rp.m_Answer=talkCtlSuccess;
						break;
					}
				}
				if(rp.m_Answer!=talkCtlSuccess)
					rp.m_Answer = talkCtlNotHere;
				break;
			}
			break;
		default:
			TRACE0("Unknown request type\n");
			rp.m_Answer=talkCtlUnknownRequest;
			break;
		}
	}while(FALSE);
	if(rp.m_Answer==talkCtlReserved || rp.m_Answer==talkCtlBadCtlAddr)
		return -1;
	if(sendto(m_daemonSocket,(char*)&rp,sizeof(rp),0,(sockaddr*)&a,sizeof(a))!=sizeof(rp)){
		TRACE0("Failed to send daemon response\n");
		return -1;
	}
	return 0;
}

int CT42Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
CRichEditCtrl tmp;
	tmp.Create(WS_CHILD,CRect(0,0,0,0),this,0);
	
NOTIFYICONDATA nid;
	memset(&nid,0,sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDC_TRAYICON;
	nid.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	nid.uCallbackMessage=WM_TRAYICON;
	nid.hIcon = m_hIcon;
	// ***
	strcpy(nid.szTip,"Tea For Two");
	VERIFY(Shell_NotifyIcon(NIM_ADD,&nid));
	
	return 0;
}

LRESULT CT42Dlg::OnTrayIcon(WPARAM wP,LPARAM lP)
{
	ASSERT(wP==IDC_TRAYICON);
	switch(lP){
	case WM_LBUTTONDOWN:
		ToggleVisibility();
		break;
	case WM_RBUTTONDOWN:
		{
		CMenu popups;
			VERIFY(popups.LoadMenu(IDM_POPUPS));
		CMenu* popUp = popups.GetSubMenu(0);
			ASSERT(popUp);
		CPoint pt;
			VERIFY(::GetCursorPos(&pt));
			SetForegroundWindow();
			popUp->CheckMenuItem(ID_TRAY_SHOWMAINWINDOW,MF_BYCOMMAND|(IsWindowVisible()?MF_CHECKED:MF_UNCHECKED));
			popUp->CheckMenuItem(ID_TRAY_AWAY,MF_BYCOMMAND|(m_bAway?MF_CHECKED:MF_UNCHECKED));
			popUp->TrackPopupMenu(TPM_RIGHTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
				pt.x,pt.y,this);
			SendMessage(WM_NULL);
		}
		break;
	}
	return 0;
}

void CT42Dlg::ToggleVisibility()
{
	if(IsWindowVisible()){
		m_bShown=FALSE;
		ShowWindow(SW_HIDE);
	CWnd* pWnd = GetNextWindow();
		if(pWnd){
			pWnd->SetForegroundWindow();
			pWnd->SetFocus();
		}
	}else{
		m_bShown=TRUE;
		ShowWindow(SW_SHOW);
		SetForegroundWindow();
		SetFocus();
	}
}

void CT42Dlg::OnCancel() 
{
	ToggleVisibility();
}


void CT42Dlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CDialog::OnWindowPosChanging(lpwndpos);
	
	if(m_bExiting)
		return;
	if(m_bShown){
		lpwndpos->flags&=~SWP_HIDEWINDOW;
		lpwndpos->flags|=SWP_SHOWWINDOW;
	}else{
		lpwndpos->flags&=~SWP_SHOWWINDOW;
		lpwndpos->flags|=SWP_HIDEWINDOW;
	}	
}

void CT42Dlg::OnOK() 
{
	m_bExiting = TRUE;
	CDialog::OnOK();
}

void CT42Dlg::OnTrayExit() 
{
	OnOK();
}

void CT42Dlg::OnTrayOptions() 
{
	OnOptions();
}

void CT42Dlg::OnTrayShowmainwindow() 
{
	ToggleVisibility();
}

void CT42Dlg::OnTrayT42() 
{
	OnTalk();
}

void CT42Dlg::OnOptions() 
{
CT42App* app = (CT42App*)AfxGetApp();
	app->Options(this);
}

void CT42Dlg::InitCalls()
{
CT42App* app = (CT42App*)AfxGetApp();
	m_CallsCtl.InsertColumn(0,"Time",LVCFMT_LEFT,-1,subitemTime);
	m_CallsCtl.InsertColumn(1,"Caller",LVCFMT_LEFT,-1,subitemCaller);
	m_CallsCtl.InsertColumn(2,"Callee",LVCFMT_LEFT,-1,subitemCallee);
LONG calls = app->GetT42Calls();
	if(calls>0){
		m_CallsCtl.SetItemCount(calls);
		for(LONG tmp=0;tmp<calls;tmp++){
			m_CallsCtl.InsertItem(
				LVIF_TEXT,
				tmp,
				LPSTR_TEXTCALLBACK,
				0,0,	// state,statemask
				I_IMAGECALLBACK,
				0		// lParam
			);
		}
	}
	SetColumnWidths();
}

void CT42Dlg::OnGetdispinfoCalls(NMHDR* pNMHDR, LRESULT* pResult) 
{
CT42App* app = (CT42App*)AfxGetApp();
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
int iItem = pDispInfo->item.iItem;
CT42CallLogEntry entry;
	VERIFY(app->GetT42Call(iItem,entry));
CString tmp;
	switch(pDispInfo->item.iSubItem){
	case subitemTime:
		tmp = entry.m_Time.Format(IDS_FORMAT_CALLTIME);
		if(entry.m_Status==CT42CallLogEntry::statusProcessed)
			pDispInfo->item.iImage = m_iProcessed;
		else
			pDispInfo->item.iImage = m_iNew;
		break;
	case subitemCaller:
		tmp = entry.m_Caller;
		break;
	case subitemCallee:
		tmp = entry.m_Callee;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	if(tmp.GetLength()>=pDispInfo->item.cchTextMax)
		tmp = tmp.Left(pDispInfo->item.cchTextMax-4)+"..";
	strcpy(pDispInfo->item.pszText,tmp);
	pDispInfo->item.mask|=LVIF_IMAGE;
	pDispInfo->item.mask|=LVIF_TEXT;

	*pResult = 0;
}

void CT42Dlg::OnAddT42Call()
{
	m_CallsCtl.InsertItem(
		LVIF_TEXT,
		m_CallsCtl.GetItemCount(),
		LPSTR_TEXTCALLBACK,
		0,0,	// state,statemask
		I_IMAGECALLBACK,
		0		// lParam
	);
	m_CallsCtl.RedrawItems(0,m_CallsCtl.GetItemCount());
	m_CallsCtl.Invalidate();
	PostMessage(WM_UPDATEPREVIEW,(WPARAM)-1);
	if(!IsWindowVisible()){
		m_newCalls++;
		SetTheIcon(m_hIconFull);
	}
}

void CT42Dlg::OnDelT42Call()
{
	m_CallsCtl.DeleteItem(
		m_CallsCtl.GetItemCount()-1
	);
	m_CallsCtl.RedrawItems(0,m_CallsCtl.GetItemCount());
	m_CallsCtl.Invalidate();
	PostMessage(WM_UPDATEPREVIEW,(WPARAM)-1);
}

void CT42Dlg::SetColumnWidths()
{
CTime ct = CTime::GetCurrentTime();
CString t = ct.Format(IDS_FORMAT_CALLTIME);
CRect rc;
	m_CallsCtl.GetClientRect(rc);
INT tw = m_CallsCtl.GetStringWidth(t)+40;
INT cew = m_CallsCtl.GetStringWidth("wwwwwwww");
INT crw = rc.Width()-(tw+cew);
	m_CallsCtl.SetColumnWidth(subitemTime,tw);
	m_CallsCtl.SetColumnWidth(subitemCaller,crw);
	m_CallsCtl.SetColumnWidth(subitemCallee,cew);
}

void CT42Dlg::OnItemchangedCalls(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if(
		pNMListView->uChanged&LVIF_STATE
		&& pNMListView->uNewState&LVIS_FOCUSED
		&& !(pNMListView->uOldState&LVIS_FOCUSED)
	){
		PostMessage(WM_UPDATEPREVIEW,pNMListView->iItem);
	}
	*pResult = 0;
}

DWORD CALLBACK CT42Dlg::ESOUTProc(DWORD dwCookie,LPBYTE pbBuff,LONG cb,LONG FAR *pcb)
{
CString* str = (CString*)dwCookie;
	if(cb>str->GetLength())
		cb = str->GetLength();
	if(!cb){
		(*pcb)=0;
		return 0;
	}
	memmove(pbBuff,(LPCTSTR)*str,cb);
	(*str) = str->Mid(cb);
	(*pcb)=cb;
	return 0;
}

void CT42Dlg::OnRclickCalls(NMHDR* pNMHDR, LRESULT* pResult) 
{
CPoint pt;
	VERIFY(GetCursorPos(&pt));
CMenu popups;
	VERIFY(popups.LoadMenu(IDM_POPUPS));
CMenu* popup = popups.GetSubMenu(1);
	ASSERT(popup);
BOOL bYes = (
			 m_CallsCtl.GetNextItem(-1,LVNI_ALL|LVNI_FOCUSED)>=0
			 || m_CallsCtl.GetNextItem(-1,LVNI_ALL|LVNI_SELECTED)>=0
	);
	popup->EnableMenuItem(ID_CALLLOG_CALLBACK,MF_BYCOMMAND|(
		bYes?MF_ENABLED:MF_GRAYED
	));
	popup->EnableMenuItem(ID_CALLLOG_DELETE,MF_BYCOMMAND|(
		bYes?MF_ENABLED:MF_GRAYED
	));
	popup->EnableMenuItem(ID_CALLLOG_SAVETOFILE,MF_BYCOMMAND|(
		bYes?MF_ENABLED:MF_GRAYED
	));
	popup->EnableMenuItem(ID_CALLLOG_MARKASNEW,MF_BYCOMMAND|(
		bYes?MF_ENABLED:MF_GRAYED
	));
	popup->EnableMenuItem(ID_CALLLOG_MARKASPROCESSED,MF_BYCOMMAND|(
		bYes?MF_ENABLED:MF_GRAYED
	));
	popup->EnableMenuItem(ID_CALLLOG_EMPTYLOG,MF_BYCOMMAND|(
		(m_CallsCtl.GetItemCount())?MF_ENABLED:MF_GRAYED
	));
	popup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON,
		pt.x,pt.y,this);
	*pResult = 0;
}

void CT42Dlg::OnCalllogCallback() 
{
int item = m_CallsCtl.GetNextItem(-1,LVNI_ALL|LVNI_FOCUSED);
	if(item<0)
		return;
CT42App* app = (CT42App*)AfxGetApp();
CT42CallLogEntry entry;
	VERIFY(app->GetT42Call(item,entry));
CDocTemplate* pTemplate = app->m_pTemplate;
T42Document* pDoc = (T42Document*)pTemplate->OpenDocumentFile(NULL);
	ASSERT_KINDOF(T42Document,pDoc);
	pDoc->Talk(entry.m_Callee,entry.m_Caller,NULL);
	entry.m_Status=CT42CallLogEntry::statusProcessed;
	VERIFY(app->UpdateT42Call(entry));
	m_CallsCtl.Update(item);
}

void CT42Dlg::OnCalllogDelete() 
{
CT42App* app = (CT42App*)AfxGetApp();
int ii = m_CallsCtl.GetItemCount();
	if(ii<=0)
		return;
Klever::CBitSet bs(ii);
	for(int i=0;i<ii;i++)
		if(m_CallsCtl.GetItemState(i,LVIS_FOCUSED|LVIS_SELECTED))
			bs.BitSet(i);
	for(i = (ii-1);i>=0;i--){
		if(!bs.IsSet(i))
			continue;
	CT42CallLogEntry entry;
		VERIFY(app->GetT42Call(i,entry));
		VERIFY(app->DelT42Call(entry.m_Time));
	}
}

void CT42Dlg::OnCalllogSavetofile() 
{
CT42App* app = (CT42App*)AfxGetApp();
CT42CallLogEntry entry;
CString filter;
	VERIFY(filter.LoadString(IDS_FILTER_RTF));
CFileDialog fd(FALSE,".rtf",NULL,
			   OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER|
			   OFN_LONGNAMES|OFN_NOREADONLYRETURN|OFN_PATHMUSTEXIST,
			   filter,this
	);
	if(fd.DoModal()==IDOK){
	int ii = m_CallsCtl.GetItemCount();
		if(ii<=0)
			return;
	Klever::CBitSet bs(ii);
		for(int i=0;i<ii;i++)
			if(m_CallsCtl.GetItemState(i,LVIS_FOCUSED|LVIS_SELECTED))
				bs.BitSet(i);
		try{
		CStdioFile f(fd.GetPathName(),
				CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite|
				CFile::typeText);
				f.WriteString("{\\rtf1\\ansi\n");
			for(i = (ii-1);i>=0;i--){
				if(!bs.IsSet(i))
					continue;
			CT42CallLogEntry entry;
				VERIFY(app->GetT42Call(i,entry));
			CString tmp;
				tmp.Format(IDS_FORMAT_T42CALLHEADER,
					entry.m_Time.Format(IDS_FORMAT_CALLTIMELONG),
					entry.m_Caller, entry.m_Callee,
					entry.m_Duration.Format(IDS_FORMAT_CALLDURATION)
				);
				f.WriteString(tmp);
				f.WriteString(entry.m_Message);
			}
			f.WriteString("\n}\n");
		}catch(CException* e){
			TRACE0("Save exc\n");
			e->Delete();
		}
	}
}

void CT42Dlg::OnCalllogEmptylog() 
{
CT42App* app = (CT42App*)AfxGetApp();
int ii = m_CallsCtl.GetItemCount();
	if(ii<=0)
		return;
	for(int i = (ii-1);i>=0;i--){
	CT42CallLogEntry entry;
		VERIFY(app->GetT42Call(i,entry));
		VERIFY(app->DelT42Call(entry.m_Time));
	}
}

void CT42Dlg::OnDeleteitemCalls(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	PostMessage(WM_UPDATEPREVIEW,(WPARAM)-1);
	*pResult = 0;
}

LRESULT CT42Dlg::OnUpdatePreview(WPARAM wP,LPARAM)
{
int iItem = (int)wP;
	if(iItem<0)
		iItem = m_CallsCtl.GetNextItem(-1,LVNI_ALL|LVNI_FOCUSED);
CT42App* app = (CT42App*)AfxGetApp();
CT42CallLogEntry entry;
	if(iItem<0 ||!app->GetT42Call(iItem,entry)){
		m_PreviewCtl.SetWindowText("");
		return 0;
	}
EDITSTREAM es;
	memset(&es,0,sizeof(es));
	es.dwCookie = (DWORD)&entry.m_Message;
	es.pfnCallback = ESOUTProc;
	m_PreviewCtl.StreamIn(SF_RTF,es);
	return 0;
}

void CT42Dlg::OnKeydownCalls(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey){
	case 'R':
		if(GetKeyState(VK_CONTROL)&0x8000)
			OnCalllogCallback();
		break;
	case VK_DELETE:
		OnCalllogDelete();
		break;
	case 'D':
		if(GetKeyState(VK_CONTROL)&0x8000)
			OnCalllogDelete();
		break;
	}
	*pResult = 0;
}

BOOL CT42Dlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	m_hExFW = ::GetForegroundWindow();
	return CDialog::PreCreateWindow(cs);
}

void CT42Dlg::SetTheIcon(HICON hIcon)
{
	m_hIcon = hIcon;
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
NOTIFYICONDATA nid;
	memset(&nid,0,sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDC_TRAYICON;
	nid.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	nid.uCallbackMessage=WM_TRAYICON;
	nid.hIcon = hIcon;
	if(m_newCalls)
		_snprintf(nid.szTip,sizeof(nid.szTip)-1,"%d new calls waiting",m_newCalls);
	else
		strcpy(nid.szTip,"Tea For Two");
	VERIFY(Shell_NotifyIcon(NIM_MODIFY,&nid));
}

void CT42Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(bShow){
		m_newCalls=0;
		SetTheIcon(m_hIconEmpty);
	}
}

void CT42Dlg::OnCalllogMarkasnew() 
{
CT42App* app = (CT42App*)AfxGetApp();
int ii = m_CallsCtl.GetItemCount();
	if(ii<=0)
		return;
Klever::CBitSet bs(ii);
	for(int i=0;i<ii;i++)
		if(m_CallsCtl.GetItemState(i,LVIS_FOCUSED|LVIS_SELECTED))
			bs.BitSet(i);
int f = -1,t = -1;
	for(i = 0;i<ii;i++){
		if(!bs.IsSet(i))
			continue;
	CT42CallLogEntry entry;
		VERIFY(app->GetT42Call(i,entry));
		if(entry.m_Status==CT42CallLogEntry::statusProcessed){
			entry.m_Status=CT42CallLogEntry::statusOk;
			VERIFY(app->UpdateT42Call(entry));
			if(f<0)
				f=i;
			if(t<i)
				t=i;
		}
	}
	if(f<0 || t<0)
		return;
	m_CallsCtl.RedrawItems(f,t);
	m_CallsCtl.Invalidate();
}

void CT42Dlg::OnCalllogMarkasprocessed() 
{
CT42App* app = (CT42App*)AfxGetApp();
int ii = m_CallsCtl.GetItemCount();
	if(ii<=0)
		return;
Klever::CBitSet bs(ii);
	for(int i=0;i<ii;i++)
		if(m_CallsCtl.GetItemState(i,LVIS_FOCUSED|LVIS_SELECTED))
			bs.BitSet(i);
int f = -1,t = -1;
	for(i = 0;i<ii;i++){
		if(!bs.IsSet(i))
			continue;
	CT42CallLogEntry entry;
		VERIFY(app->GetT42Call(i,entry));
		if(entry.m_Status!=CT42CallLogEntry::statusProcessed){
			entry.m_Status=CT42CallLogEntry::statusProcessed;
			VERIFY(app->UpdateT42Call(entry));
			if(f<0)
				f=i;
			if(t<i)
				t=i;
		}
	}
	if(f<0 || t<0)
		return;
	m_CallsCtl.RedrawItems(f,t);
	m_CallsCtl.Invalidate();
}

void CT42Dlg::RecalcLayout()
{
CRect crc;
	GetClientRect(&crc);
CRect rcCalls;
	m_CallsCtl.GetWindowRect(&rcCalls);
	ScreenToClient(rcCalls);
	// Calculate windows height.
UINT wHeight = (crc.Height()-rcCalls.top-m_marginY-m_gapY)/2;
UINT wWidth = crc.Width()-(2*m_marginX);
	// Position windows
	m_CallsCtl.SetWindowPos(
		NULL,
		m_marginX,rcCalls.top-crc.top, wWidth,wHeight,
		SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOZORDER
	);
	m_PreviewCtl.SetWindowPos(
		NULL,
		m_marginX,rcCalls.top-crc.top+wHeight+m_gapY, wWidth,wHeight,
		SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOZORDER
	);

CRect brc;
	m_TeaCtl.GetWindowRect(brc); ScreenToClient(brc);
UINT bX = crc.Width()-m_marginX-brc.Width();
	m_TeaCtl.SetWindowPos(NULL,bX,brc.top, 0,0,SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER|SWP_NOCOPYBITS);
	m_OptionsCtl.GetWindowRect(brc); ScreenToClient(brc);
	m_OptionsCtl.SetWindowPos(NULL,bX,brc.top,0,0,SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER|SWP_NOCOPYBITS);
	m_ExitCtl.GetWindowRect(brc); ScreenToClient(brc);
	m_ExitCtl.SetWindowPos(NULL,bX,brc.top,0,0,SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER|SWP_NOCOPYBITS);
	m_HelpCtl.GetWindowRect(brc); ScreenToClient(brc);
	m_HelpCtl.SetWindowPos(NULL,bX,brc.top,0,0,SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER|SWP_NOCOPYBITS);
}

void CT42Dlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_marginX && m_marginY && m_gapY){
		RecalcLayout();
		SetColumnWidths();
	}
	
}

void CT42Dlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if(m_sizeMin.cx && m_sizeMin.cy){
		lpMMI->ptMinTrackSize.x = m_sizeMin.cx;
		lpMMI->ptMinTrackSize.y = m_sizeMin.cy;
	}
	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CT42Dlg::SetOnCtl(UINT nAction,CComboBox& ctl)
{
int n = 0;
	switch(nAction){
	case IDC_SECRETARY: n = 1; break;
	case IDC_NOTHERE: n = 2; break;
	case IDC_REFUSE: n = 3; break;
	case IDCANCEL: n = 4; break;
	}
	ctl.SetCurSel(n);
}

UINT CT42Dlg::GetOnCtl(CComboBox& ctl)
{
	switch(ctl.GetCurSel()){
	case 1: return IDC_SECRETARY;
	case 2: return IDC_NOTHERE;
	case 3: return IDC_REFUSE;
	case 4: return IDCANCEL;
	}
	return 0;
}

void CT42Dlg::OnAway() 
{
	m_bAway = m_AwayCtl.GetCheck();
}
void CT42Dlg::OnSelendokOncall() 
{
	m_onCall = GetOnCtl(m_OnCallCtl);
}
void CT42Dlg::OnSelendokOncallaway() 
{
	m_onCallAway = GetOnCtl(m_OnCallAwayCtl);
}

void CT42Dlg::LoadSettings()
{
CT42App* app = (CT42App*)AfxGetApp();
	m_onCall = app->GetProfileInt("Settings","T42OnCall",m_onCall);
	m_onCallAway = app->GetProfileInt("Settings","T42OnCallAway",m_onCallAway);
}

void CT42Dlg::SaveSettings()
{
CT42App* app = (CT42App*)AfxGetApp();
	app->WriteProfileInt("Settings","T42OnCall",m_onCall);
	app->WriteProfileInt("Settings","T42OnCallAway",m_onCallAway);
}

void CT42Dlg::OnTrayAway() 
{
	m_AwayCtl.SetCheck((m_bAway=!m_bAway)?1:0);
}

void CT42Dlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==timerMinutes){
		KillTimer(timerMinutes);
	CDocTemplate* pTemplate = ((CT42App*)AfxGetApp())->m_pTemplate;
	POSITION p = pTemplate->GetFirstDocPosition();
		while(p){
		T42Document* pDoc = (T42Document*)pTemplate->GetNextDoc(p);
			pDoc->OnMinute();
		}
		SetTimer(timerMinutes,60000,NULL);
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CT42Dlg::OnQueryEndSession() 
{
	if (!CDialog::OnQueryEndSession())
		return FALSE;
	
CT42App* app = (CT42App*)AfxGetApp();
	app->SaveSettings();
	
	return TRUE;
}
