// T42Secretary.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "T42Document.h"
#include "T42Secretary.h"

#include "T42View.h"
#include "T42Frame.h"

CT42Secretary::CT42Secretary()
{
	m_logEntry.m_Time = CTime::GetCurrentTime();
CT42App* app = (CT42App*)AfxGetApp();
	app->m_T42LinesBusy++;
	m_limitTime = app->m_T42STimeLimit;
	m_limitBytes = app->m_T42SBytesLimit;
	TRACE0("Secretary++\n");
}

CT42Secretary::~CT42Secretary()
{
CT42App* app = (CT42App*)AfxGetApp();
	app->m_T42LinesBusy--;
	TRACE0("Secretary--\n");
}


BOOL CT42Secretary::OnAttach(T42Document* pDocument)
{
	TRACE0("T42S - OnAttach\n");
	return CT42Robot::OnAttach(pDocument);
}

BOOL CT42Secretary::OnConnect()
{
	m_logEntry.m_Caller = m_pDocument->m_pView->m_pFrame->m_Target;
	m_logEntry.m_Callee = m_pDocument->m_pView->m_pFrame->m_LocalUser;
	m_logEntry.m_Message.Empty();
	m_logEntry.m_Time = CTime::GetCurrentTime();

CT42App* app = (CT42App*)AfxGetApp();
CString greet = app->m_T42SGreeting;
int ix;
	while((ix=greet.Find("%t"))>=0){
	CString tmp;
		tmp.Format("%lu",app->m_T42STimeLimit.GetTotalSeconds()/60);
		greet = greet.Left(ix)+tmp+greet.Mid(ix+2);
	}
	while((ix=greet.Find("%c"))>=0){
	CString tmp;
		tmp.Format("%u",app->m_T42SBytesLimit);
		greet = greet.Left(ix)+tmp+greet.Mid(ix+2);
	}
	m_pDocument->SendOver(greet);
	return TRUE;
}

BOOL CT42Secretary::OnReceive(char* pData,int nBytes)
{
	if(m_limitBytes && m_pDocument->m_pView->m_remoteCtl.GetTextLength()>=m_limitBytes)
		OnDisconnect();
	return TRUE;
}

BOOL CT42Secretary::OnDisconnect()
{
	m_logEntry.m_Duration = CTime::GetCurrentTime()-m_logEntry.m_Time;
EDITSTREAM es;
	memset(&es,0,sizeof(es));
	es.dwCookie = (DWORD)&m_logEntry.m_Message;
	es.pfnCallback = ESINProc;
	m_pDocument->m_pView->m_remoteCtl.StreamOut(SF_RTF,es);
	m_logEntry.m_Status = CT42CallLogEntry::statusOk;
CT42App* app = (CT42App*)AfxGetApp();
	VERIFY(app->AddT42Call(m_logEntry));
	m_pDocument->m_pView->m_pFrame->OnTalkClose();
	return TRUE;
}

BOOL CT42Secretary::OnDetach()
{
	TRACE0("T42S - OnDetach\n");
	delete this;
	return TRUE;
}


BOOL CT42Secretary::OnIPResolved()
{
	m_logEntry.m_Caller = m_pDocument->m_pView->m_pFrame->m_Target;
	return TRUE;
}

DWORD CALLBACK CT42Secretary::ESINProc(DWORD dwCookie,LPBYTE pbBuff,LONG cb,LONG FAR *pcb)
{
CString* str = (CString*)dwCookie;
	if(memchr(pbBuff,0,cb-1)){
		(*pcb) = 0;
		return 1;
	}
UINT p = str->GetLength();
CHAR* s = str->GetBuffer(p+cb+1);
	memmove(&s[p],pbBuff,cb);
	s[p+cb]=0;
	str->ReleaseBuffer();
	(*pcb)=cb;
	return 0;
}

BOOL CT42Secretary::OnMinute()
{
	if(
		m_limitTime.GetTotalSeconds() &&
		(CTime::GetCurrentTime()-m_logEntry.m_Time)>=m_limitTime
	)
		OnDisconnect();
	return TRUE;
}

