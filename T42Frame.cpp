// T42Frame.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "T42Frame.h"

#include "T42View.h"
#include "CalleeDlg.h"
#include "shared-code/RegEx.h"
#include "T42Document.h"

#include <snmp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T42Frame

IMPLEMENT_DYNCREATE(T42Frame, CFrameWnd)

T42Frame::T42Frame()
{
	VERIFY(m_hNormal=AfxGetApp()->LoadIcon(IDR_T42FRAME));
	VERIFY(m_hFullCup=AfxGetApp()->LoadIcon(IDR_FULLT42));

	m_bTrayMinimize = TRUE;
	m_bSleepMinimize = TRUE;
	m_bMinimizeSleep = TRUE;
	m_onWake = wakeSound|wakePopup;
	LoadLayout();

	m_bHaveFocus = FALSE;
	m_bTrayed = FALSE;
	m_bSleep = FALSE;

	m_asyncHandle = NULL;
	m_resolveHandle = NULL;
	m_ctlSocket = INVALID_SOCKET;
	m_Socket = INVALID_SOCKET;
	m_localEC.m_cErase = 0177;
	m_localEC.m_kill = 025;		// ^U
	m_localEC.m_wErase = 027;	// ^W
	m_bEstablished = FALSE;

	CleanUp();
}

T42Frame::~T42Frame()
{
}

BEGIN_MESSAGE_MAP(T42Frame, CFrameWnd)
	//{{AFX_MSG_MAP(T42Frame)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TALK_REMOTEUSER, OnTalkRemoteuser)
	ON_MESSAGE(WM_INITIATETALK, OnInitiateTalk)
	ON_MESSAGE(WM_TARGETRESOLVED, OnTargetResolved)
	ON_MESSAGE(WM_SOURCERESOLVED, OnSourceResolved)
	ON_WM_TIMER()
	ON_MESSAGE(WM_CTLTRANSACT, OnCTLTransact)
	ON_MESSAGE(WM_LOOKUP_SUCCESS, OnLookupSuccess)
	ON_MESSAGE(WM_LOOKUP_FAILURE, OnLookupFailure)
	ON_MESSAGE(WM_ANNOUNCE_SUCCESS, OnAnnounceSuccess)
	ON_MESSAGE(WM_ANNOUNCE_FAILURE, OnAnnounceFailure)
	ON_MESSAGE(WM_LEAVEINVITE_SUCCESS, OnLeaveInviteSuccess)
	ON_MESSAGE(WM_LEAVEINVITE_FAILURE, OnLeaveInviteFailure)
	ON_MESSAGE(WM_TALKACCEPT, OnTalkAccept)
	ON_MESSAGE(WM_LOCAL_REMOVE_SUCCESS, OnLocalRemoveSuccess)
	ON_MESSAGE(WM_LOCAL_REMOVE_FAILURE, OnLocalRemoveFailure)
	ON_MESSAGE(WM_REMOTE_REMOVE_SUCCESS, OnRemoteRemoveSuccess)
	ON_MESSAGE(WM_REMOTE_REMOVE_FAILURE, OnRemoteRemoveFailure)
	ON_MESSAGE(WM_TALK, OnTalk)
	ON_MESSAGE(WM_TALKCHAR, OnTalkChar)
	ON_MESSAGE(WM_TALKCONNECT, OnTalkConnect)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
	ON_MESSAGE(WM_EXITMENULOOP, OnExitMenuLoop)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_NAMERESOLVED, OnNameResolved)
	ON_MESSAGE(WM_IPRESOLVED, OnIPResolved)
	ON_WM_ACTIVATE()
	ON_MESSAGE(WM_TRAYICON, OnTrayIcon)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_HIDEINTRAYONMINIMIZE, OnUpdateWindowHideintrayonminimize)
	ON_COMMAND(ID_WINDOW_HIDEINTRAYONMINIMIZE, OnWindowHideintrayonminimize)
	ON_COMMAND(ID_TALK_ABORT, OnTalkAbort)
	ON_UPDATE_COMMAND_UI(ID_TALK_ABORT, OnUpdateTalkAbort)
	ON_COMMAND(ID_TALK_RECONNECT, OnTalkReconnect)
	ON_UPDATE_COMMAND_UI(ID_TALK_RECONNECT, OnUpdateTalkReconnect)
	ON_UPDATE_COMMAND_UI(ID_TALK_REMOTEUSER, OnUpdateTalkRemoteuser)
	ON_UPDATE_COMMAND_UI(ID_SLEEP_SLEEP, OnUpdateSleepSleep)
	ON_COMMAND(ID_SLEEP_SLEEP, OnSleepSleep)
	ON_UPDATE_COMMAND_UI(ID_SLEEP_SLEEPONMINIMIZE, OnUpdateSleepSleeponminimize)
	ON_COMMAND(ID_SLEEP_SLEEPONMINIMIZE, OnSleepSleeponminimize)
	ON_UPDATE_COMMAND_UI(ID_SLEEP_WAKEUPACTION_MAKESOUND, OnUpdateSleepWakeupactionMakesound)
	ON_COMMAND(ID_SLEEP_WAKEUPACTION_MAKESOUND, OnSleepWakeupactionMakesound)
	ON_UPDATE_COMMAND_UI(ID_SLEEP_WAKEUPACTION_POPUP, OnUpdateSleepWakeupactionPopup)
	ON_COMMAND(ID_SLEEP_WAKEUPACTION_POPUP, OnSleepWakeupactionPopup)
	ON_UPDATE_COMMAND_UI(ID_SLEEP_MINIMIZEONSLEEP, OnUpdateSleepMinimizeonsleep)
	ON_COMMAND(ID_SLEEP_MINIMIZEONSLEEP, OnSleepMinimizeonsleep)
	ON_COMMAND(ID_TALK_CLOSE, OnTalkClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T42Frame message handlers

void T42Frame::OnClose() 
{
	if(GetKeyState(VK_SHIFT)&0x8000){
	T42Document* pDoc = (T42Document*)GetActiveDocument();
		ASSERT_KINDOF(T42Document,pDoc);
		pDoc->AutosaveLayout();
	}
	CFrameWnd::OnClose();
}

BOOL T42Frame::PreCreateWindow(CREATESTRUCT& cs) 
{
CWinApp* app = AfxGetApp();
	ASSERT(app);
	cs.x = app->GetProfileInt("T42Window","X",cs.x);
	cs.y = app->GetProfileInt("T42Window","Y",cs.y);
	cs.cx = app->GetProfileInt("T42Window","Width",cs.cx);
	cs.cy = app->GetProfileInt("T42Window","Height",cs.cy);

BOOL rv = CFrameWnd::PreCreateWindow(cs);

//	cs.style&=~FWS_PREFIXTITLE;
//	cs.style|=FWS_ADDTOTITLE;
	
	return rv;
}

void T42Frame::OnTalkRemoteuser() 
{
CCalleeDlg callee(this);
	callee.m_Callee = m_Target;
	callee.m_Caller = m_LocalUser;
	callee.m_TTY = m_TargetTTY;
	if(callee.DoModal() == IDOK){
		m_Target = callee.m_Callee;
		m_LocalUser = callee.m_Caller;
		m_TargetTTY = callee.m_TTY;
		PostMessage(WM_INITIATETALK);
	}
}

LRESULT T42Frame::OnInitiateTalk(WPARAM,LPARAM)
{
	if(
		(!((T42Document*)GetActiveDocument())->m_bHidden)
		&& !m_bTrayed
	)
		SetForegroundWindow();
CRegEx atRE, bangRE;
	VERIFY(atRE.Compile("([-Р-пр-џ[:alnum:]_.]+)@([-[:alnum:].]+)",CRegEx::regExtended));	// u, h
	VERIFY(bangRE.Compile("([-[:alnum:].]+)[!:]([-Р-пр-џ[:alnum:]._]+)",CRegEx::regExtended));	// h, u
	if(atRE.Match(m_Target,CRegEx::regExtended)){
		m_TargetUser = atRE.GetMatch(1);
		m_TargetHost = atRE.GetMatch(2);
	}else if(bangRE.Match(m_Target,CRegEx::regExtended)){
		m_TargetUser = bangRE.GetMatch(2);
		m_TargetHost = bangRE.GetMatch(1);
	}else{
		ShowMessage(IDS_ERR_MALFORMEDREMOTE,MB_ICONSTOP|MB_OK);
		return -1;
	}
	SetPeerName();
	memset(&m_TargetAddr,0,sizeof(m_TargetAddr));
	m_TargetAddr.sin_addr.s_addr = inet_addr(m_TargetHost);
	if(m_TargetAddr.sin_addr.s_addr == INADDR_NONE){
		StatusLine(IDS_STATUS_RESOLVING);
		m_asyncHandle = WSAAsyncGetHostByName(
			m_hWnd,WM_TARGETRESOLVED,
			(LPCTSTR)m_TargetHost,
			(char*)m_gethostData,sizeof(m_gethostData)
		);
		if(!m_asyncHandle){
			WSSystemMessage(IDS_ERR_REMOTERESOLVEFAILED,WSAGetLastError());
			return -1;
		}
		// Here we're trying to establish connection using hostname (as opposed
		// to ip address) - no further investigation needed.
		AddToHotList();
	}else{
		if(!Klever::FindIFace(m_TargetAddr.sin_addr,m_SourceAddr.sin_addr))
			m_SourceAddr.sin_addr.s_addr = INADDR_ANY;
		PostMessage(WM_SOURCERESOLVED);
		// Try to resolve hostname if it resolves back to the same IP - this
		// is the canonical name we need. If not - leave it as IP.
		m_resolveHandle = WSAAsyncGetHostByAddr(
			m_hWnd,WM_NAMERESOLVED,
			(char*)&m_TargetAddr.sin_addr,sizeof(m_TargetAddr.sin_addr),AF_INET,
			(char*)m_ghResolve,sizeof(m_ghResolve)
		);
		if(!m_resolveHandle){
			// We've failed to resolve hostname - leave IP - do nothing.
			TRACE0("Failed to initiate IP resolve\n");
			AddToHotList();
		}
	}
	return 0;
}

LRESULT T42Frame::OnNameResolved(WPARAM,LPARAM lP)
{
	m_resolveHandle=NULL;
	if(WSAGETASYNCERROR(lP)){
		// We've failed to resolve hostname - leave IP - do nothing.
		TRACE0("Failed to resolve name by ip\n");
		AddToHotList();
	}else{
	hostent* he = (hostent*)m_ghResolve;
		m_nameFromIP = he->h_name;
		m_resolveHandle = WSAAsyncGetHostByName(
			m_hWnd,WM_IPRESOLVED,
			(LPCTSTR)m_nameFromIP,
			(char*)m_ghResolve,sizeof(m_ghResolve)
		);
		if(!m_resolveHandle){
			// We've failed to resolve hostname - leave IP - do nothing.
			TRACE0("Failed to initiate name resolve\n");
			AddToHotList();
		}
	}
	return 0;
}

LRESULT T42Frame::OnIPResolved(WPARAM,LPARAM lP)
{
	m_resolveHandle=NULL;
	if(WSAGETASYNCERROR(lP)){
		// We've failed to resolve hostname - leave IP - do nothing.
		TRACE0("Failed to resolve name by ip\n");
		AddToHotList();
	}else{
	hostent* he = (hostent*)m_ghResolve;
		if(
			he->h_length!=sizeof(m_TargetAddr.sin_addr)
			|| he->h_addrtype!=m_TargetAddr.sin_family
			|| memcmp(*he->h_addr_list,&m_TargetAddr.sin_addr,he->h_length)
		){
			// The host resolved to different IP address..
			// maybe we should warn user about it?
			TRACE0("IP/NAME investigations sucked in result\n");
			AddToHotList();
		}else{
			// We got new hostname!! Hurray! What do we do?
			// Yes, we set new Target..
			m_TargetHost = m_nameFromIP;
			m_Target = m_TargetUser + '@' + m_TargetHost;
			SetPeerName();
			AddToHotList();
		T42Document* pDoc = (T42Document*)GetActiveDocument();
			ASSERT_KINDOF(T42Document,pDoc);	
			if(pDoc->m_pRobot)
				pDoc->m_pRobot->OnIPResolved();
			TRACE0("IP/NAME investigations succeeded\n");
		}
	}
	return 0;
}

LRESULT T42Frame::OnTargetResolved(WPARAM,LPARAM lP)
{
	m_asyncHandle=NULL;
	if(WSAGETASYNCERROR(lP)){
		WSSystemMessage(IDS_ERR_REMOTERESOLVEFAILED,WSAGetLastError());
		return 0;
	}
	ASSERT(((hostent*)m_gethostData)->h_length==4);
	memmove(&m_TargetAddr.sin_addr,*((hostent*)m_gethostData)->h_addr_list,sizeof(m_TargetAddr.sin_addr));
	if(!Klever::FindIFace(m_TargetAddr.sin_addr,m_SourceAddr.sin_addr))
		m_SourceAddr.sin_addr.s_addr = INADDR_ANY;
	PostMessage(WM_SOURCERESOLVED);
	return 0;
}

LRESULT T42Frame::OnSourceResolved(WPARAM,LPARAM)
{
	// Open ctl socket
	m_SourceAddr.sin_port = 0;
	m_SourceAddr.sin_family = AF_INET;
	m_ctlSocket = socket(AF_INET,SOCK_DGRAM,0);
	if(m_ctlSocket==INVALID_SOCKET){
		WSSystemMessage(IDS_ERR_CTLCREATEFAILED,WSAGetLastError());
		return -1;
	}
	if(bind(m_ctlSocket,(sockaddr*)&m_SourceAddr,sizeof(m_SourceAddr))){
		WSSystemMessage(IDS_ERR_CTLBINDFAILED,WSAGetLastError());
		return -1;
	}
int length = sizeof(m_ctlAddr);
	if(getsockname(m_ctlSocket,(sockaddr*)&m_ctlAddr,&length)){
		WSSystemMessage(IDS_ERR_CTLGETFAILED,WSAGetLastError());
		return -1;
	}
	// Open socket for connection
	m_SourceAddr.sin_port = 0;
	m_SourceAddr.sin_family = AF_INET;
	m_Socket = socket(AF_INET,SOCK_STREAM,0);
	if(m_Socket==INVALID_SOCKET){
		WSSystemMessage(IDS_ERR_TCPCREATEFAILED,WSAGetLastError());
		return -1;
	}
	if(bind(m_Socket,(sockaddr*)&m_SourceAddr,sizeof(m_SourceAddr))){
		WSSystemMessage(IDS_ERR_TCPBINDFAILED,WSAGetLastError());
		return -1;
	}
	length = sizeof(m_SourceAddr);
	if(getsockname(m_Socket,(sockaddr*)&m_SourceAddr,&length)){
		WSSystemMessage(IDS_ERR_TCPGETFAILED,WSAGetLastError());
		return -1;
	}
	StatusLine(IDS_STATUS_LOOKUPINVITE);
TalkCtlMessage rq;
	FillInMessage(rq);
	rq.m_Type = talkCtlReqLookUp;
	m_TargetAddr.sin_family = AF_INET;
CT42App* app = (CT42App*)AfxGetApp();
	m_TargetAddr.sin_port = htons(app->m_T42TalkPort);
	VERIFY(AsyncCtlTransact(rq,m_TargetAddr,WM_LOOKUP_SUCCESS,WM_LOOKUP_FAILURE));
	return 0;
}

BOOL T42Frame::FillInMessage(TalkCtlMessage& msg)
{
	memset(&msg,0,sizeof(msg));
	msg.m_Version = talkCtlVersion;
	msg.m_Addr = m_SourceAddr;
	msg.m_ctlAddr = m_ctlAddr;
	msg.m_ID = htonl(0);
	msg.m_PID = htonl((LONG)m_hWnd);
	ASSERT(m_LocalUser.GetLength()>0 && m_LocalUser.GetLength()<sizeof(msg.m_LName));
	strcpy(msg.m_LName,m_LocalUser);
	ASSERT(m_TargetUser.GetLength()>0 && m_TargetUser.GetLength()<sizeof(msg.m_RName));
	strcpy(msg.m_RName,m_TargetUser);
	ASSERT(m_TargetTTY.GetLength()>=0 && m_TargetTTY.GetLength()<sizeof(msg.m_RTTY));
	strcpy(msg.m_RTTY,m_TargetTTY);
	return TRUE;
}

BOOL T42Frame::AsyncCtlTransact(TalkCtlMessage& msg,sockaddr_in& target, UINT wmSuccess,UINT wmFailure)
{
	if(m_ctlSuccess || m_ctlFailure)
		return FALSE;
	memmove(&m_ctlTarget,&target,sizeof(m_ctlTarget));
	memmove(&m_ctlRequest,&msg,sizeof(m_ctlRequest));
	m_ctlSuccess = wmSuccess;
	m_ctlFailure = wmFailure;
	TRACE2("Initiating CTL Transaction to %s:%d\n",
		inet_ntoa(m_ctlTarget.sin_addr),ntohs(m_ctlTarget.sin_port)
	);
	TRACE3("V: %d, T: %d, ID: %ld\n",
		(int)m_ctlRequest.m_Version, (int)m_ctlRequest.m_Type,
		ntohl(m_ctlRequest.m_ID)
	);
	TRACE("ADDR: %s:%d\n",
		inet_ntoa(((sockaddr_in*)&m_ctlRequest.m_Addr)->sin_addr),
		ntohs(((sockaddr_in*)&m_ctlRequest.m_Addr)->sin_port)
	);
	TRACE("CTL ADDR: %s:%d\n",
		inet_ntoa(((sockaddr_in*)&m_ctlRequest.m_ctlAddr)->sin_addr),
		ntohs(((sockaddr_in*)&m_ctlRequest.m_ctlAddr)->sin_port)
	);
	if(sendto(m_ctlSocket,(char*)&m_ctlRequest,sizeof(m_ctlRequest),0,
		(sockaddr*)&m_ctlTarget,sizeof(m_ctlTarget))!=sizeof(m_ctlRequest)
	){
		AsyncCtlTransactFailed(ctlFailSendto,WSAGetLastError());
		return TRUE;
	}
	if(WSAAsyncSelect(m_ctlSocket,m_hWnd,WM_CTLTRANSACT,FD_READ)){
		AsyncCtlTransactFailed(ctlFailSelect,WSAGetLastError());
		return TRUE;
	}
	SetTimer(timerTransact,2000,NULL);
	return TRUE;
}

LRESULT T42Frame::OnCTLTransact(WPARAM,LPARAM lP)
{
	KillTimer(timerTransact);
	if(!(m_ctlSuccess && m_ctlFailure))
		return -1;
	if(WSAGETSELECTERROR(lP)){
		AsyncCtlTransactFailed(ctlFailError,WSAGETSELECTERROR(lP));
		return -1;
	}
	ASSERT(WSAGETSELECTEVENT(lP)&FD_READ);
long length;
	do{
		if(ioctlsocket(m_ctlSocket,FIONREAD,(u_long*)&length) || length<=0)
			break;
		if(recv(m_ctlSocket,(char*)&m_ctlResponse,sizeof(m_ctlResponse),0)!=sizeof(m_ctlResponse))
			continue;
		if(
			m_ctlResponse.m_Version != talkCtlVersion
			|| m_ctlResponse.m_Type!=m_ctlRequest.m_Type
		)
			continue;
		// We got the datagram we need here
		AsyncCtlTransactSucceeded(m_ctlResponse);
	}while(1);
	if(WSAAsyncSelect(m_ctlSocket,m_hWnd,WM_CTLTRANSACT,FD_READ)){
		AsyncCtlTransactFailed(ctlFailSelect,WSAGetLastError());
		return -1;
	}
	SetTimer(timerTransact,2000,NULL);
	return 0;
}

void T42Frame::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent){
	case timerTransact:
		KillTimer(timerTransact);
		if(!(m_ctlSuccess && m_ctlFailure)){
			TRACE0("VERY STRANGE\n");
			break;
		}
		TRACE0("Transact timed out\n");
		if(sendto(m_ctlSocket,(char*)&m_ctlRequest,sizeof(m_ctlRequest),0,
			(sockaddr*)&m_ctlTarget,sizeof(m_ctlTarget))!=sizeof(m_ctlRequest)
		){
			AsyncCtlTransactFailed(ctlFailSendto,WSAGetLastError());
			break;
		}
		if(WSAAsyncSelect(m_ctlSocket,m_hWnd,WM_CTLTRANSACT,FD_READ)){
			AsyncCtlTransactFailed(ctlFailSelect,WSAGetLastError());
			break;
		}
		SetTimer(timerTransact,2000,NULL);
		break;
	}
	
	CFrameWnd::OnTimer(nIDEvent);
}


void T42Frame::AsyncCtlTransactFailed(UINT code,LONG error)
{
	ASSERT(m_ctlSuccess && m_ctlFailure);
UINT m = m_ctlFailure;
	m_ctlFailure = m_ctlSuccess = 0;
	WSAAsyncSelect(m_ctlSocket,NULL,0,0);
	TRACE2("CTL Transact failed %d (%ld)\n",(int)code,error);
	PostMessage(m,code,error);
}

void T42Frame::AsyncCtlTransactSucceeded(TalkCtlResponse& response)
{
	ASSERT(m_ctlSuccess && m_ctlFailure);
UINT m = m_ctlSuccess;
	m_ctlFailure = m_ctlSuccess = 0;
	WSAAsyncSelect(m_ctlSocket,NULL,0,0);
	TRACE2("CTL Transaction succeeded - A: %d, ID: %ld\n",
		(int)response.m_Answer, ntohl(response.m_ID)
	);
	TRACE2("ADDR: %s:%d\n",
		inet_ntoa(((sockaddr_in*)&response.m_Addr)->sin_addr),
		ntohs(((sockaddr_in*)&response.m_Addr)->sin_port)
	);
	PostMessage(m,0,(LPARAM)&response);
}

LRESULT T42Frame::OnLookupSuccess(WPARAM,LPARAM lP)
{
TalkCtlResponse& rp = *(TalkCtlResponse*)lP;
	if(rp.m_Answer==talkCtlSuccess){
		TRACE0("Found an invitation\n");
		if(WSAAsyncSelect(m_Socket,m_hWnd,WM_TALKCONNECT,FD_CONNECT)){
			WSSystemMessage(IDS_ERR_TCPASELFAILED,WSAGetLastError());
			return -1;
		}
	SOCKADDR_IN sin;
		memmove(&sin,&rp.m_Addr,sizeof(sin));
		sin.sin_family = ntohs(sin.sin_family);
		StatusLine(IDS_STATUS_WAITINGTOCONNECT);
		if(connect(m_Socket,(sockaddr*)&sin,sizeof(sin))){
			if(WSAGetLastError()!=WSAEWOULDBLOCK){
				WSSystemMessage(IDS_ERR_TCPCONNECTFAILED,WSAGetLastError());
				return -1;
			}
		}else
			PostMessage(WM_TALKCONNECT,0,WSAMAKESELECTREPLY(FD_CONNECT,0));
	}else{
		if(listen(m_Socket,5)){
			WSSystemMessage(IDS_ERR_TCPLISTENFAILED,WSAGetLastError());
			return -1;
		}
		if(WSAAsyncSelect(m_Socket,m_hWnd,WM_TALKACCEPT,FD_ACCEPT)){
			WSSystemMessage(IDS_ERR_LTNASELFAILED,WSAGetLastError());
			return -1;
		}
	TalkCtlMessage rq;
		FillInMessage(rq);
		rq.m_Type = talkCtlReqLeaveInvite;
		rq.m_ID = htonl(-1);
	SOCKADDR_IN tgt;
		memmove(&tgt,&m_SourceAddr,sizeof(tgt));
CT42App* app = (CT42App*)AfxGetApp();
		tgt.sin_port = htons(app->m_T42TalkPort);
		VERIFY(AsyncCtlTransact(rq,tgt,WM_LEAVEINVITE_SUCCESS,WM_LEAVEINVITE_FAILURE));
	}
	return 0;
}
LRESULT	T42Frame::OnLookupFailure(WPARAM wP,LPARAM lP)
{
	SystemMessage(IDS_ERR_CTLLOOKUPFAILED);
	TRACE2("Lookup failed %d, %ld",(int)wP,lP);
	return -1;
}

LRESULT T42Frame::OnAnnounceSuccess(WPARAM,LPARAM lP)
{
TalkCtlResponse& rp = *(TalkCtlResponse*)lP;
	if(rp.m_Answer != talkCtlSuccess){
	static
	UINT nReasons[] = {0,IDS_CTL_NOTHERE,IDS_CTL_FAILED,IDS_CTL_MACHUNKNOWN,
		IDS_CTL_PERMISSIONDENIED, IDS_CTL_BADREQUEST, IDS_CTL_BADVERSION,
		IDS_CTL_BADADDR, IDS_CTL_BADCTL};
	CString reason;
		if(rp.m_Answer<(sizeof(nReasons)/sizeof(*nReasons)))
			SystemMessage(IDS_ERR_ANNOUNCEFAILURE,nReasons[rp.m_Answer]);
		else
			SystemMessage(IDS_ERR_ANNOUNCEFAILURE,IDS_CTL_UNKNOWNERROR);
		return -1;
	}
	m_remoteID = rp.m_ID;
	return 0;
}
LRESULT T42Frame::OnAnnounceFailure(WPARAM wP,LPARAM lP)
{
	SystemMessage(IDS_ERR_ANNOUNCEFAILED);
	return -1;
}

LRESULT T42Frame::OnLeaveInviteSuccess(WPARAM,LPARAM lP)
{
TalkCtlResponse& rp = *(TalkCtlResponse*)lP;
	m_localID = rp.m_ID;
TalkCtlMessage rq;
	FillInMessage(rq);
	rq.m_ID = htonl(-1);
	StatusLine(IDS_STATUS_ANNOUNCING);
	rq.m_Type = talkCtlReqAnnounce;
	m_TargetAddr.sin_family = AF_INET;
CT42App* app = (CT42App*)AfxGetApp();
	m_TargetAddr.sin_port = htons(app->m_T42TalkPort);
	VERIFY(AsyncCtlTransact(rq,m_TargetAddr,WM_ANNOUNCE_SUCCESS,WM_ANNOUNCE_FAILURE));
	return 0;	// Or?
}
LRESULT T42Frame::OnLeaveInviteFailure(WPARAM wP,LPARAM lP)
{
	SystemMessage(IDS_ERR_LEAVINVITEFAILED);
	TRACE2("LeaveInvite failed %d, %ld",(int)wP,lP);
	return -1;
}

LRESULT T42Frame::OnTalkAccept(WPARAM,LPARAM lP)
{
	if(WSAGETSELECTERROR(lP)){
		WSSystemMessage(IDS_ERR_TCPACCEPTFAILED,WSAGETSELECTERROR(lP));
		return -1;
	}
	ASSERT(WSAGETSELECTEVENT(lP)&FD_ACCEPT);
SOCKET s = accept(m_Socket,NULL,NULL);
	ASSERT(s!=INVALID_SOCKET);
	VERIFY(!closesocket(m_Socket));
	m_Socket = s;
	m_bConnected=TRUE;
	SelectTalkSocket();
	StatusLine(IDS_STATUS_WAITINGTOCONNECT);
TalkCtlMessage rq;
	FillInMessage(rq);
	rq.m_Type = talkCtlReqDelete;
	rq.m_ID = m_localID;
SOCKADDR_IN t;
	memmove(&t,&m_SourceAddr,sizeof(t));
CT42App* app = (CT42App*)AfxGetApp();
	t.sin_port = htons(app->m_T42TalkPort);
	AsyncCtlTransact(rq,t,WM_LOCAL_REMOVE_SUCCESS,WM_LOCAL_REMOVE_FAILURE);
	return 0;
}

LRESULT T42Frame::OnTalkConnect(WPARAM,LPARAM lP)
{
	if(WSAGETSELECTERROR(lP)){
		WSSystemMessage(IDS_ERR_TCPCONNECTFAILED,WSAGETSELECTERROR(lP));
		return -1;
	}
	m_bConnected=TRUE;
	ASSERT(WSAGETSELECTEVENT(lP)&FD_CONNECT);
	SelectTalkSocket();
	StatusLine(IDS_STATUS_WAITINGTOCONNECT);
	return 0;
}

LRESULT T42Frame::OnLocalRemoveSuccess(WPARAM,LPARAM lP)
{
TalkCtlResponse& rp = *(TalkCtlResponse*)lP;
	ASSERT(rp.m_Answer==talkCtlSuccess);
TalkCtlMessage rq;
	FillInMessage(rq);
	rq.m_Type = talkCtlReqDelete;
	rq.m_ID = m_remoteID;
SOCKADDR_IN t;
	memmove(&t,&m_TargetAddr,sizeof(t));
CT42App* app = (CT42App*)AfxGetApp();
	t.sin_port = htons(app->m_T42TalkPort);
	AsyncCtlTransact(rq,t,WM_REMOTE_REMOVE_SUCCESS,WM_REMOTE_REMOVE_FAILURE);
	return 0;
}
LRESULT T42Frame::OnLocalRemoveFailure(WPARAM wP,LPARAM lP)
{
//	SystemMessage(IDS_ERR_CTLLDELETEFAILED);
	TRACE2("Local delete failed %d, %ld",(int)wP,lP);
	return -1;
}

LRESULT T42Frame::OnRemoteRemoveSuccess(WPARAM,LPARAM lP)
{
TalkCtlResponse& rp = *(TalkCtlResponse*)lP;
//	ASSERT(rp.m_Answer==talkCtlSuccess);	// ???
	return 0;
}
LRESULT T42Frame::OnRemoteRemoveFailure(WPARAM wP,LPARAM lP)
{
//	SystemMessage(IDS_ERR_CTLRDELETEFAILED);
	TRACE2("Local delete failed %d, %ld",(int)wP,lP);
	return -1;
}

LRESULT T42Frame::OnTalk(WPARAM wP,LPARAM lP)
{
	if(WSAGETSELECTEVENT(lP)&FD_CLOSE){
		StatusLine(IDS_STATUS_CONNECTIONCLOSED);
		if(WSAGETSELECTERROR(lP))
			WSSystemMessage(IDS_ERR_CONNECTIONCLOSED,WSAGETSELECTERROR(lP));
		else
			SystemMessage(IDS_CONNECTIONCLOSED);
		Established(FALSE);
		return 0;
	}
	if(WSAGETSELECTERROR(lP)){
		WSSystemMessage(IDS_ERR_TCPERROR,WSAGETSELECTERROR(lP));
		Established(FALSE);
		TRACE1("Error on conversation socket: %ld\n",WSAGETSELECTERROR(lP));
		return -1;
	}
	if(WSAGETSELECTEVENT(lP)&FD_READ){
	CHAR rb[512+1];
	int rbytes = recv(m_Socket,rb,sizeof(rb)-1,0);
		if(rbytes>0){
			if(m_receivedEC<sizeof(m_remoteEC)){
			int ms = min(sizeof(m_remoteEC)-m_receivedEC,rbytes);
				memmove(
					&((CHAR*)&m_remoteEC)[m_receivedEC],rb,ms
				);
				memmove(rb,&rb[ms],sizeof(rb)-ms);
				rbytes-=ms;
				m_receivedEC+=ms;
				// Under some circumstances we can claim connection
				// establishment here.
				if(m_receivedEC==sizeof(m_remoteEC)){
					StatusLine(IDS_STATUS_ESTABLISHED);
					Established(TRUE);
				}
			}
			if(rbytes){
				rb[rbytes]=0;
			T42Document* pDoc = (T42Document*)GetActiveDocument();
				ASSERT_KINDOF(T42Document,pDoc);
				if(pDoc->m_pRobot)
					pDoc->m_pRobot->OnReceive(rb,rbytes);
				PutRemote(rb);
				if(!m_bHaveFocus){
					SetTheIcon(m_hFullCup);
					if(m_bSleep)
						WakeUp();
				}
			}
		}
	}
	if(WSAGETSELECTEVENT(lP)&FD_WRITE){
		if(!m_bSentEC){
			if(send(m_Socket,(char*)&m_localEC,sizeof(m_localEC),0)!=sizeof(m_localEC)){
				WSSystemMessage(IDS_ERR_TCPERROR,WSAGetLastError());
				Established(FALSE);
			}else
				m_bSentEC = TRUE;
		}else{
		int sb = send(m_Socket,(char*)(LPCTSTR)m_sendBuffer,m_sendBuffer.GetLength(),0);
			if(sb<0){
				WSSystemMessage(IDS_ERR_TCPERROR,WSAGetLastError());
				Established(FALSE);
			}else
				m_sendBuffer = m_sendBuffer.Mid(sb);
		}
	}
	SelectTalkSocket();
	return 0;
}

void T42Frame::SelectTalkSocket()
{
	if(!m_bConnected)
		return;
UINT mask = FD_READ|FD_CLOSE;
	if(!(m_bSentEC && m_sendBuffer.IsEmpty()))
		mask|=FD_WRITE;
	if(WSAAsyncSelect(m_Socket,m_hWnd,WM_TALK,mask)){
		WSSystemMessage(IDS_ERR_TCPERROR,WSAGetLastError());
		Established(FALSE);
	}
}

BOOL T42Frame::PutRemote(LPCTSTR str)
{
T42View* pView = (T42View*)GetActiveView();
	ASSERT_KINDOF(T42View,pView);
	pView->m_remoteCtl.PutString(str);
	return TRUE;
}

LRESULT T42Frame::OnTalkChar(WPARAM wP,LPARAM lP)
{
	if(wP){
	CHAR c=(CHAR)(wP&0xFF);
//		if(c=='\r')
//??		c='\n';
		m_sendBuffer+=c;
	}else{
	CString str = (LPCTSTR)lP;
	int cr;
		while((cr=str.Find('\r'))>=0)
			str = str.Left(cr)+str.Mid(cr+1);
		m_sendBuffer+=str;
	}
	SelectTalkSocket();
	return 0;
}

int T42Frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CFrameWnd::OnCreate(lpCreateStruct)==-1)
		return -1;
	// CG: The following block was inserted by 'Status Bar' component.
	{	
		// Create an array for status bar indicators
		UINT pIndicators[3] = { ID_SEPARATOR };
		if (!m_wndStatusBar.Create(this) ||
			!InitStatusBar(pIndicators, 1, 60))
		{
			TRACE0("Failed to create Status Bar\n");
			return -1;
		}
	}

	m_wndFake.CreateEx(
		0,AfxRegisterWndClass(0,0,0,0),"",WS_OVERLAPPED,
		0,0,0,0,
		NULL,NULL,NULL
	);

	return 0;
}

void T42Frame::OnUpdateDate(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strDate = time.Format(_T("%A, %B %d, %y "));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strDate);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current date
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nDatePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nDatePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strDate);
	pCmdUI->Enable(TRUE);

}

BOOL T42Frame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Create an index for the DATE pane
	m_nDatePaneNo = nSize++;
	pIndicators[m_nDatePaneNo] = ID_INDICATOR_DATE;

	m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

	return m_wndStatusBar.SetIndicators(pIndicators, nSize);

}

void T42Frame::StatusLine(LPCTSTR str)
{
	m_wndStatusBar.SetPaneText(0,m_Status=str);
}

void T42Frame::StatusLine(UINT nID)
{
	VERIFY(m_Status.LoadString(nID));
	m_wndStatusBar.SetPaneText(0,m_Status);
}

LRESULT T42Frame::OnExitMenuLoop(WPARAM,LPARAM)
{
	m_wndStatusBar.SetPaneText(0,m_Status);
	return 0;
}

void T42Frame::OnDestroy() 
{
	if(m_bTrayed){
	NOTIFYICONDATA nid;
		memset(&nid,0,sizeof(nid));
		nid.cbSize=sizeof(nid);
		nid.hWnd = m_hWnd;
		nid.uID = IDC_TRAYICON;
		nid.uFlags = 0;
		VERIFY(Shell_NotifyIcon(NIM_DELETE,&nid));
	}
	m_wndFake.DestroyWindow();
	CFrameWnd::OnDestroy();

	CleanUp();
}

void T42Frame::ShowMessage(UINT nID,UINT flags)
{
CString msg;
	VERIFY(msg.LoadString(nID));
	ShowMessage(msg,flags);
}
void T42Frame::ShowMessage(LPCTSTR msg,UINT flags)
{
	MessageBox(msg,NULL,flags);
}

void T42Frame::Established(BOOL bEstablished)
{
	if(!bEstablished)
		CleanUp();
	else{
		if(
			(!((T42Document*)GetActiveDocument())->m_bHidden)
			&& !m_bTrayed
		)
			SetForegroundWindow();
	}
T42View* pView = (T42View*)GetActiveView();
	ASSERT_KINDOF(T42View,pView);
	pView->SetEnable(bEstablished);

BOOL bRobot = (m_bEstablished && !bEstablished) || (bEstablished && !m_bEstablished);
	m_bEstablished = bEstablished;

	SetPeerName();
	if(bRobot){
	T42Document* pDoc = (T42Document*)pView->GetDocument();
		ASSERT_KINDOF(T42Document,pDoc);	
		if(pDoc->m_pRobot){
			if(bEstablished)
				pDoc->m_pRobot->OnConnect();
			else
				pDoc->m_pRobot->OnDisconnect();
		}
	}
}

void T42Frame::CleanUp()
{
	if(m_resolveHandle){
		WSACancelAsyncRequest(m_resolveHandle);
		m_resolveHandle=NULL;
	}
	if(m_asyncHandle){
		WSACancelAsyncRequest(m_asyncHandle);
		m_asyncHandle=NULL;
	}
	if(m_ctlSocket!=INVALID_SOCKET){
		closesocket(m_ctlSocket);
		m_ctlSocket = INVALID_SOCKET;
	}
	if(m_Socket!=INVALID_SOCKET){
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}

	m_Status.LoadString(AFX_IDS_IDLEMESSAGE);
	m_localID = m_remoteID = 0;
	m_sendBuffer.Empty();
	m_ctlSuccess = 0;
	m_ctlFailure = 0;
	m_bSentEC = FALSE;
	m_receivedEC = 0;
	m_bConnected=FALSE;
}

void T42Frame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if(nID==SC_MINIMIZE){
		if(m_bTrayMinimize){
		NOTIFYICONDATA nid;
			memset(&nid,0,sizeof(nid));
			nid.cbSize=sizeof(nid);
			nid.hWnd = m_hWnd;
			nid.uID = IDC_TRAYICON;
			nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
			nid.uCallbackMessage = WM_TRAYICON;
			nid.hIcon =	m_hNormal;
		CString tip;
			GetWindowText(tip);
			if(tip.GetLength()>=sizeof(nid.szTip))
				tip = tip.Left(sizeof(nid.szTip)-3)+"..";
			strcpy(nid.szTip,(LPCTSTR)tip);
			VERIFY(Shell_NotifyIcon(NIM_ADD,&nid));
		CWnd* pWnd = GetNextWindow();
			ShowWindow(SW_HIDE);
			pWnd->SetForegroundWindow();
			m_bTrayed=TRUE;
		}else
			CFrameWnd::OnSysCommand(nID, lParam);
		if(m_bSleepMinimize)
			m_bSleep=TRUE;
	}else
		CFrameWnd::OnSysCommand(nID, lParam);
}

void T42Frame::SaveLayout()
{
CWinApp* app = AfxGetApp();
CRect rc;
	GetWindowRect(rc);
	app->WriteProfileInt("T42Window","X",rc.left);
	app->WriteProfileInt("T42Window","Y",rc.top);
	app->WriteProfileInt("T42Window","Width",rc.Width());
	app->WriteProfileInt("T42Window","Height",rc.Height());
	app->WriteProfileInt("T42Window","TrayMinimize",m_bTrayMinimize);
	app->WriteProfileInt("T42Window","SleepMinimize",m_bSleepMinimize);
	app->WriteProfileInt("T42Window","OnWake",m_onWake);
	app->WriteProfileInt("T42Window","MinimizeSleep",m_bMinimizeSleep);
}
void T42Frame::LoadLayout()
{
CWinApp* app = AfxGetApp();
	m_bTrayMinimize = app->GetProfileInt("T42Window","TrayMinimize",m_bTrayMinimize);
	m_bSleepMinimize = app->GetProfileInt("T42Window","SleepMinimize",m_bSleepMinimize);
	m_onWake = app->GetProfileInt("T42Window","OnWake",m_onWake);
	m_bMinimizeSleep = app->GetProfileInt("T42Window","MinimizeSleep",m_bMinimizeSleep);
}

void T42Frame::SetPeerName(LPCTSTR str)
{
T42Document* pDoc = (T42Document*)GetActiveDocument();
	ASSERT_KINDOF(T42Document,pDoc);
CString n = str?str:m_Target;
	pDoc->SetTitle(n);
	m_wndFake.SetWindowText("Talk with "+n);
}

void T42Frame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
T42Document* pDoc = (T42Document*)GetActiveDocument();
	ASSERT_KINDOF(T42Document,pDoc);
CString title;
	if(bAddToTitle && pDoc && m_bEstablished)
		title.Format(IDS_TITLE_TEAWITH,pDoc->GetTitle());
	else
		title.LoadString(IDS_TITLE_TEAFORTWO);
	SetWindowText(title);
}

void T42Frame::AddToHotList(LPCTSTR str)
{
CT42App* app = (CT42App*)AfxGetApp();
	app->LastCallee(str?str:m_Target);
}

void T42Frame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	if(nState==WA_INACTIVE){
		m_bHaveFocus=FALSE;
	}else{
		DeTray();
		SetTheIcon(m_hNormal);
		m_bHaveFocus=TRUE;
	}
}

LRESULT T42Frame::OnTrayIcon(WPARAM wP,LPARAM lP)
{
	ASSERT(wP==IDC_TRAYICON);
	if(lP==WM_LBUTTONDOWN)
		SetForegroundWindow();
	return 0;
}

void T42Frame::SetTheIcon(HICON hicon)
{
	SetIcon(hicon,TRUE); SetIcon(hicon,FALSE);
	if(m_bTrayed){
	NOTIFYICONDATA nid;
		memset(&nid,0,sizeof(nid));
		nid.cbSize=sizeof(nid);
		nid.hWnd = m_hWnd;
		nid.uID = IDC_TRAYICON;
		nid.uFlags = NIF_ICON;
		nid.hIcon =	hicon;
		VERIFY(Shell_NotifyIcon(NIM_MODIFY,&nid));
	}
}

void T42Frame::OnUpdateWindowHideintrayonminimize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bTrayMinimize?1:0);
}
void T42Frame::OnWindowHideintrayonminimize() 
{
	m_bTrayMinimize=!m_bTrayMinimize;
}

void T42Frame::OnTalkAbort() 
{
	ASSERT(m_Socket);
	closesocket(m_Socket);
	StatusLine(IDS_STATUS_CONNECTIONCLOSED);
	SystemMessage(IDS_CONNECTIONCLOSED);
	Established(FALSE);
}
void T42Frame::OnUpdateTalkAbort(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEstablished);
}
void T42Frame::OnTalkReconnect() 
{
	PostMessage(WM_INITIATETALK);
}
void T42Frame::OnUpdateTalkReconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((!m_bEstablished) && (!m_Target.IsEmpty()));
}
void T42Frame::OnUpdateTalkRemoteuser(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bEstablished);
}

void T42Frame::WakeUp()
{
	if(m_onWake&wakeSound){
	CT42App* app = (CT42App*)AfxGetApp();
		ASSERT(app);
		app->StartSound(app->m_sndT42Wake);
	}
	if(m_onWake&wakePopup)
		SetForegroundWindow();
	m_bSleep=FALSE;
}

void T42Frame::OnUpdateSleepSleep(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bSleep?1:0);
}
void T42Frame::OnSleepSleep() 
{
	m_bSleep=!m_bSleep;
	if(m_bSleep && m_bMinimizeSleep)
		PostMessage(WM_SYSCOMMAND,SC_MINIMIZE);
}

void T42Frame::OnUpdateSleepSleeponminimize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bSleepMinimize?1:0);
}
void T42Frame::OnSleepSleeponminimize() 
{
	m_bSleepMinimize=!m_bSleepMinimize;
}

void T42Frame::OnUpdateSleepWakeupactionMakesound(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_onWake&wakeSound)?1:0);
}
void T42Frame::OnSleepWakeupactionMakesound() 
{
	m_onWake^=wakeSound;
}

void T42Frame::OnUpdateSleepWakeupactionPopup(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_onWake&wakePopup)?1:0);
}
void T42Frame::OnSleepWakeupactionPopup() 
{
	m_onWake^=wakePopup;
}

void T42Frame::DeTray()
{
	if(!m_bTrayed)
		return;
NOTIFYICONDATA nid;
	memset(&nid,0,sizeof(nid));
	nid.cbSize=sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDC_TRAYICON;
	nid.uFlags = 0;
	VERIFY(Shell_NotifyIcon(NIM_DELETE,&nid));
	m_bTrayed=FALSE;
	ShowWindow(SW_SHOW);
}

void T42Frame::OnUpdateSleepMinimizeonsleep(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bMinimizeSleep?1:0);
}
void T42Frame::OnSleepMinimizeonsleep() 
{
	m_bMinimizeSleep=!m_bMinimizeSleep;	
}

void T42Frame::OnTalkClose() 
{
	PostMessage(WM_CLOSE);
}

void T42Frame::SystemMessage(UINT nID)
{
CString tmp;
	VERIFY(tmp.LoadString(nID));
	SystemMessage(tmp);
}

void T42Frame::SystemMessage(LPCTSTR str)
{
T42View* pView = (T42View*)GetActiveView();
	ASSERT_KINDOF(T42View,pView);
	pView->SystemMessage(str);
}

void T42Frame::SystemMessage(UINT nID,UINT nIDi)
{
CString idi;
	VERIFY(idi.LoadString(nIDi));
CString tmp;
	tmp.Format(nID,idi);
	SystemMessage(tmp);
}

void T42Frame::WSSystemMessage(UINT nID,LONG wsaError)
{
UINT wsid = 0;
	switch(wsaError){
	case WSAENETDOWN: wsid = IDS_WSA_ENETDOWN; break;
	case WSAECONNRESET: wsid = IDS_WSA_ECONNRESET; break;
	case WSAECONNABORTED: wsid = IDS_WSA_ECONNABORTED; break;
	case WSAECONNREFUSED: wsid = IDS_WSA_ECONNREFUSED; break;
	case WSAENETUNREACH: wsid = IDS_WSA_ENETUNREACH; break;
	case WSAETIMEDOUT: wsid = IDS_WSA_ETIMEDOUT; break;
	case WSAHOST_NOT_FOUND: wsid = IDS_WSA_HOSTNOTFOUND; break;
	case WSANO_DATA: wsid = IDS_WSA_NODATA; break;
	}
	if(wsid)
		SystemMessage(nID,wsid);
	else{
	CString tmp;
	tmp.Format("#%ld",wsaError);
		SystemMessage(nID,tmp);
	}
}

void T42Frame::SystemMessage(UINT nID,LPCTSTR str)
{
CString tmp;
	tmp.Format(nID,str);
	SystemMessage(tmp);
}

void T42Frame::ActivateFrame(int nCmdShow) 
{
T42Document* pDoc = (T42Document*)GetActiveDocument();
	ASSERT_KINDOF(T42Document,pDoc);
	if(pDoc->m_bHidden)
		nCmdShow=SW_HIDE;
	CFrameWnd::ActivateFrame(nCmdShow);
}
