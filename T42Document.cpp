// T42Document.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "T42Document.h"

#include "T42View.h"
#include "T42Frame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T42Document

IMPLEMENT_DYNCREATE(T42Document, CDocument)

T42Document::T42Document()
{
	m_pView=NULL;
	m_pRobot = NULL;
	m_bHidden = FALSE;
}

BOOL T42Document::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

T42Document::~T42Document()
{
	if(m_pRobot)
		DetachRobot();
}


BEGIN_MESSAGE_MAP(T42Document, CDocument)
	//{{AFX_MSG_MAP(T42Document)
	ON_COMMAND(ID_WINDOW_SAVELAYOUT, OnWindowSavelayout)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_AUTOSAVELAYOUT, OnUpdateWindowAutosavelayout)
	ON_COMMAND(ID_WINDOW_AUTOSAVELAYOUT, OnWindowAutosavelayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T42Document diagnostics

#ifdef _DEBUG
void T42Document::AssertValid() const
{
	CDocument::AssertValid();
}

void T42Document::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// T42Document serialization

void T42Document::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// T42Document commands

void T42Document::Talk(LPCTSTR from,LPCTSTR to,LPCTSTR tty,BOOL bPrompt)
{
	ASSERT(m_pView);
	ASSERT(m_pView->m_pFrame);
	m_pView->m_pFrame->m_Target = to?to:"";
	m_pView->m_pFrame->m_LocalUser = from?from:"";
	m_pView->m_pFrame->m_TargetTTY = tty?tty:"";
	if(bPrompt || !(to && from))
		m_pView->m_pFrame->PostMessage(WM_COMMAND,MAKELONG(ID_TALK_REMOTEUSER,0),NULL);
	else
		m_pView->m_pFrame->PostMessage(WM_INITIATETALK);
}

void T42Document::OnChangedViewList() 
{
	CDocument::OnChangedViewList();
POSITION p = GetFirstViewPosition();
	m_pView=NULL;
	while(p){
	CView* pView = GetNextView(p);
		ASSERT_KINDOF(T42View,pView);
		ASSERT(!m_pView);
		m_pView=(T42View*)pView;
	}
}

void T42Document::SaveLayout()
{
	ASSERT(m_pView);
	m_pView->SaveLayout();
	ASSERT(m_pView->m_pFrame);
	m_pView->m_pFrame->SaveLayout();
}

void T42Document::OnWindowSavelayout() 
{
	SaveLayout();
}

void T42Document::OnUpdateWindowAutosavelayout(CCmdUI* pCmdUI) 
{
CT42App* app = (CT42App*)AfxGetApp();
	pCmdUI->SetCheck(app->m_bt42AutosaveLayout?1:0);
}

void T42Document::OnWindowAutosavelayout() 
{
CT42App* app = (CT42App*)AfxGetApp();
	app->m_bt42AutosaveLayout=!app->m_bt42AutosaveLayout;
}

void T42Document::AutosaveLayout()
{
CT42App* app = (CT42App*)AfxGetApp();
	if(app->m_bt42AutosaveLayout)
		SaveLayout();
}

BOOL T42Document::AttachRobot(CT42Robot* pRobot)
{
	if(m_pRobot)
		DetachRobot();
	m_pRobot = pRobot;
	return m_pRobot->OnAttach(this);
}

BOOL T42Document::DetachRobot()
{
	ASSERT(m_pRobot);
BOOL rv = m_pRobot->OnDetach();
	m_pRobot=NULL;
	return rv;
}

BOOL T42Document::SendOver(LPCTSTR str)
{
	// *** Or call T42View function?
	for(LPCTSTR ptr=str;*ptr;ptr++){
		m_pView->m_localCtl.PutCharacter(*ptr);
		m_pView->m_pFrame->PostMessage(WM_TALKCHAR,0xFF&((WORD)*ptr));
	}
	return TRUE;
}

BOOL T42Document::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;

	if(lpszPathName)
		m_bHidden = TRUE;
	
	return TRUE;
}

void T42Document::OnMinute()
{
	if(m_pRobot)
		m_pRobot->OnMinute();
}
