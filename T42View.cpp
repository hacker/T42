// T42View.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "T42View.h"

#include "T42Frame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T42View

IMPLEMENT_DYNCREATE(T42View, CFormView)

T42View::T42View()
	: CFormView(T42View::IDD)
{
	//{{AFX_DATA_INIT(T42View)
	//}}AFX_DATA_INIT
	m_localCtl.m_pView = m_remoteCtl.m_pView = this;
	m_pFrame = NULL;
	m_localSize = 50;
	m_remoteSize = 50;
	m_gapSize = 5;
	m_Ort = ortHorizontal;
	m_bShown = FALSE;
	m_bTracking = FALSE;
	m_hHorzCursor = AfxGetApp()->LoadStandardCursor(IDC_SIZENS);
	m_hVertCursor = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_bEnabled = FALSE;
}

T42View::~T42View()
{
}

void T42View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T42View)
	DDX_Control(pDX, IDC_SPLIT, m_splitCtl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T42View, CFormView)
	//{{AFX_MSG_MAP(T42View)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SPLITTERBDOWN, OnSplitterBDown)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_WINDOW_SPLITEQUALLY, OnWindowSplitequally)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_HORIZONTALSPLIT, OnUpdateWindowHorizontalsplit)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_VERTICALSPLIT, OnUpdateWindowVerticalsplit)
	ON_COMMAND(ID_WINDOW_HORIZONTALSPLIT, OnWindowHorizontalsplit)
	ON_COMMAND(ID_WINDOW_VERTICALSPLIT, OnWindowVerticalsplit)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_CANCELMODE()
	ON_UPDATE_COMMAND_UI(ID_TEA_SAVE, OnUpdateTeaSave)
	ON_COMMAND(ID_TEA_SAVE, OnTeaSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T42View diagnostics

#ifdef _DEBUG
void T42View::AssertValid() const
{
	CFormView::AssertValid();
}

void T42View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// T42View message handlers
/////////////////////////////////////////////////////////////////////////////
// CSplitBar

CSplitBar::CSplitBar()
{
}

CSplitBar::~CSplitBar()
{
}


BEGIN_MESSAGE_MAP(CSplitBar, CStatic)
	//{{AFX_MSG_MAP(CSplitBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitBar message handlers

void CSplitBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetParent()->PostMessage(WM_SPLITTERBDOWN);
}

void CSplitBar::OnPaint() 
{
CPaintDC dc(this); // device context for painting
CRect rc;
	GetWindowRect(rc);
	ScreenToClient(rc);
	dc.DrawEdge(rc,EDGE_RAISED,(m_Ort==T42View::ortVertical)?BF_LEFT|BF_RIGHT:BF_TOP|BF_BOTTOM);
}

void T42View::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_pFrame = (T42Frame*)GetParent();
	ASSERT_KINDOF(T42Frame,m_pFrame);
	SetScaleToFitSize(CSize(10,10));

	m_localCtl.Create(WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_LEFT|ES_MULTILINE|ES_WANTRETURN|WS_VSCROLL,
		CRect(0,0,0,0), this, 0);
	m_remoteCtl.Create(WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_LEFT|ES_MULTILINE|ES_WANTRETURN|WS_VSCROLL,
		CRect(0,0,0,0), this, 0);
	m_localCtl.SetFocus();
	m_localCtl.m_pInTEC = &m_pFrame->m_localEC;
	m_localCtl.m_pOuTEC = &m_pFrame->m_remoteEC;
	m_remoteCtl.m_pInTEC = &m_pFrame->m_remoteEC;
	m_remoteCtl.m_pOuTEC = &m_pFrame->m_localEC;


	LoadLayout();

	RecalcLayout();
	m_bShown=TRUE;
}

void T42View::RecalcLayout()
{
UINT lrs = m_localSize+m_remoteSize;
	m_splitCtl.m_Ort = m_Ort;
CRect crc;
	GetClientRect(crc);
CRect rc;
UINT ls = m_localSize, rs = m_remoteSize;
	if(m_Ort==ortHorizontal){
	UINT lr = crc.Height()-m_gapSize;
		rc.top = rc.left = 0;
		rc.right = crc.right;

		ls = lr*m_localSize/lrs;
		rc.bottom = ls;
		m_localCtl.MoveWindow(rc);

		rc.top=rc.bottom+1;
		rc.bottom=rc.top+m_gapSize-1;
		m_splitCtl.MoveWindow(rc);

		rc.top=rc.bottom+1;
		rc.bottom=crc.bottom;
		rs = rc.Height();
		m_remoteCtl.MoveWindow(rc);
	}else if(m_Ort==ortVertical){
	CRect crc;
		GetClientRect(crc);
	CRect rc;
	UINT lr = crc.Width()-m_gapSize;
		rc.top = rc.left = 0;
		rc.bottom = crc.bottom;

		ls = lr*m_localSize/lrs;
		rc.right = ls;
		m_localCtl.MoveWindow(rc);

		rc.left=rc.right+1;
		rc.right=rc.left+m_gapSize-1;
		m_splitCtl.MoveWindow(rc);

		rc.left=rc.right+1;
		rc.right=crc.right;
		rs = rc.Width();
		m_remoteCtl.MoveWindow(rc);
	}else
		ASSERT(FALSE);
	m_localSize = ls; m_remoteSize = rs;
}

void T42View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	if(m_bShown)
		RecalcLayout();
}

LRESULT T42View::OnSplitterBDown(WPARAM,LPARAM)
{
	SetCapture();
	m_bTracking = TRUE;
CRect rc;
	GetClientRect(rc);
	if(m_Ort==ortHorizontal){
		ASSERT(rc.Height()>25);
		rc.top+=10;
		rc.bottom-=10;
	}else{
		ASSERT(rc.Width()>25);
		rc.left+=10;
		rc.right-=10;
	}
	ClientToScreen(rc);
	ClipCursor(&rc);
	return 0;
}

void T42View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bTracking){
	CRect rc;
		GetClientRect(rc);
		if(m_Ort==ortHorizontal){
			m_localSize = point.y;
			m_remoteSize = rc.bottom-point.y;
		}else{
			m_localSize = point.x;
			m_remoteSize = rc.right-point.x;
		}
		RecalcLayout();
	}
	
	CFormView::OnMouseMove(nFlags, point);
}

void T42View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bTracking){
		ClipCursor(NULL);
		m_bTracking=FALSE;
		ReleaseCapture();
	}
	CFormView::OnLButtonUp(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// CLocalCtl

CLocalCtl::CLocalCtl()
{
CT42App* app = (CT42App*)AfxGetApp();
	m_bgColor = app->m_crT42LocalBG;
	memmove(&m_fmtUser,&app->m_fmtT42Local,sizeof(m_fmtUser));
	memmove(&m_fmtSystem,&app->m_fmtT42System,sizeof(m_fmtSystem));
}

CLocalCtl::~CLocalCtl()
{
}


BEGIN_MESSAGE_MAP(CLocalCtl, CRichTalkCtl)
	//{{AFX_MSG_MAP(CLocalCtl)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalCtl message handlers
/////////////////////////////////////////////////////////////////////////////
// CRemoteCtl

CRemoteCtl::CRemoteCtl()
{
CT42App* app = (CT42App*)AfxGetApp();
	m_bgColor = app->m_crT42RemoteBG;
	memmove(&m_fmtUser,&app->m_fmtT42Remote,sizeof(m_fmtUser));
	memmove(&m_fmtSystem,&app->m_fmtT42System,sizeof(m_fmtSystem));
}

CRemoteCtl::~CRemoteCtl()
{
}


BEGIN_MESSAGE_MAP(CRemoteCtl, CRichTalkCtl)
	//{{AFX_MSG_MAP(CRemoteCtl)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteCtl message handlers

void CRichTalkCtl::Setup()
{
	ModifyStyle(0,WS_VSCROLL);
	SetOptions(ECOOP_SET,ECO_AUTOWORDSELECTION|ECO_AUTOVSCROLL|ECO_READONLY|
		ECO_WANTRETURN|ECO_SAVESEL|ECO_SELECTIONBAR|ECO_NOHIDESEL);
	SetTargetDevice(NULL,0);
	SetSel(0,-1);
PARAFORMAT pf;
	memset(&pf,0,sizeof(pf));
	pf.cbSize = sizeof(pf);
	pf.dwMask = PFM_OFFSET;
	pf.dxOffset = 20;
	SetParaFormat(pf);
	SetDefaultCharFormat(m_fmtUser);
	SetSelectionCharFormat(m_fmtUser);
	SetSel(-1,-1);
	SetColor();
}

int CRemoteCtl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	Setup();
	return 0;
}

int CLocalCtl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	Setup();
	return 0;
}

void CLocalCtl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!m_pView->m_bEnabled)
		return;
	if(!(nFlags&0x8000)){
		ASSERT(m_pView && m_pView->m_pFrame);
		if(nChar=='\r')
			nChar='\n';
	UINT c = nChar;
		if(c=='\b')
			c=m_pOuTEC->m_cErase;
		m_pView->m_pFrame->PostMessage(WM_TALKCHAR,c);
		PutCharacter(nChar);
	}
}

void CRemoteCtl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!m_pView->m_bEnabled)
		return;
	if(!(nFlags&0x8000)){
		ASSERT(m_pView && m_pView->m_pFrame);
		if(nChar=='\r')
			nChar='\n';
	UINT c = nChar;
		if(c=='\b')
			c=m_pOuTEC->m_cErase;
		m_pView->m_pFrame->PostMessage(WM_TALKCHAR,c);
		m_pView->m_localCtl.SetFocus();
		m_pView->m_localCtl.PutCharacter(nChar);
	}
}

void CRichTalkCtl::PutString(LPCTSTR str)
{
CString s = str;
CHAR span[] = { '\r','\n','\a','\b',m_pInTEC->m_cErase,0 };
CString sss;
	while(!s.IsEmpty()){
		sss=s.SpanExcluding(span);
		if(!sss.IsEmpty()){
		BOOL bDo = !GetTextLength();
			SetSel(-1,-1);
		long ss,es;
			if(bDo)
				GetSel(ss,es);
			ReplaceSel(sss);
			if(bDo){
				SetSel(ss,-1);
				SetSelectionCharFormat(m_fmtUser);
				SetSel(-1,-1);
			}
			s = s.Mid(sss.GetLength());
		}
		if(!s.IsEmpty()){
			PutCharacter(s[0]);
			s=s.Mid(1);
		}
	}
	UnlockWindowUpdate();
}

void CRichTalkCtl::PutCharacter(CHAR c)
{
	if(c=='\r')
		return;
	if(c=='\a'){
	CT42App* app = (CT42App*)AfxGetApp();
		ASSERT(app);
		app->StartSound(app->m_sndT42Bell);
		return;
	}else if(c=='\b' || c==m_pInTEC->m_cErase){
		SetSel(-1,-1);
	CHARRANGE cr;
		GetSel(cr);
		if(cr.cpMin>0){
			cr.cpMin--;
			SetSel(cr);
			ReplaceSel("");
		}else
			MessageBeep(0xFFFFFFFF);
		return;
	}
BOOL bDo = !GetTextLength();
	SetSel(-1,-1);
char tmp[2] = {c,0};
long ss,es;
	if(bDo)
		GetSel(ss,es);
	ReplaceSel(tmp);
	if(bDo){
		SetSel(ss,-1);
		SetSelectionCharFormat(m_fmtUser);
		SetSel(-1,-1);
	}
	UnlockWindowUpdate();
}

void CRichTalkCtl::SystemMessage(LPCTSTR str)
{
	SetSel(-1,-1);

	if(
		GetTextLength()
		&& LineLength()
	)
		ReplaceSel("\n");

CString tmp = "[";
	tmp+=str;
	tmp+=']';
long ss,es;
	GetSel(ss,es);
	ReplaceSel(tmp);
	SetSel(ss,-1);
	SetSelectionCharFormat(m_fmtSystem);
	SetSel(-1,-1);
	GetSel(ss,es);
	ReplaceSel("\n");
	SetSel(ss,-1);
	SetSelectionCharFormat(m_fmtUser);
	SetSel(-1,-1);
	UnlockWindowUpdate();
}

BOOL T42View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
BOOL rv = CFormView::OnSetCursor(pWnd, nHitTest, message);
	if(rv)
		return rv;
	if(pWnd==&m_splitCtl){
		if(m_Ort==ortVertical){
			SetCursor(m_hVertCursor);
		}else{
			SetCursor(m_hHorzCursor);
		}
		return TRUE;
	}
	return FALSE;
}

void CLocalCtl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CRichTalkCtl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRichTalkCtl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar){
	case	VK_INSERT:
	case	VK_DELETE:
	case	VK_BACK:
	case	VK_ESCAPE:
		return;
	}
	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRemoteCtl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CRichTalkCtl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void T42View::OnWindowSplitequally() 
{
	m_localSize = m_remoteSize = 50;
	RecalcLayout();
}

void T42View::OnUpdateWindowHorizontalsplit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_Ort==ortHorizontal);
}

void T42View::OnUpdateWindowVerticalsplit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_Ort==ortVertical);
}

void T42View::OnWindowHorizontalsplit() 
{
	m_Ort = ortHorizontal;
	RecalcLayout();
}

void T42View::OnWindowVerticalsplit() 
{
	m_Ort = ortVertical;
	RecalcLayout();
}


void T42View::SetEnable(BOOL bEnable)
{
	m_bEnabled = bEnable;
	m_localCtl.SetColor();
	m_remoteCtl.SetColor();
}

void CRichTalkCtl::SetColor()
{
	if(m_pView->m_bEnabled)
		SetBackgroundColor(FALSE,m_bgColor);
	else{
		SetBackgroundColor(
			FALSE,
			RGB(
				GetRValue(m_bgColor)/2,
				GetGValue(m_bgColor)/2,
				GetBValue(m_bgColor)/2
			)
		);
	}
}

void T42View::OnEditCopy() 
{
CWnd* pWnd = GetFocus();
	if(pWnd==&m_localCtl)
		m_localCtl.Copy();
	else if(pWnd==&m_remoteCtl)
		m_remoteCtl.Copy();
	else
		MessageBeep(MB_OK);
}

void T42View::OnEditPaste() 
{
	ASSERT(m_pFrame);
	if(!m_bEnabled)
		return;
	if(!IsClipboardFormatAvailable(CF_TEXT))
		return;
	if(!OpenClipboard())
		return;
HANDLE h = GetClipboardData(CF_TEXT);
LPVOID gl = GlobalLock(h);
	ASSERT(gl);
	m_pFrame->SendMessage(WM_TALKCHAR,0,(LPARAM)gl);
	m_localCtl.PutString((LPCTSTR)gl);
	GlobalUnlock(h);
	CloseClipboard();
}

void T42View::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEnabled && IsClipboardFormatAvailable(CF_TEXT));
}

void T42View::SaveLayout()
{
CWinApp* app = AfxGetApp();
	app->WriteProfileInt("T42View","LocalSize",m_localSize);
	app->WriteProfileInt("T42View","RemoteSize",m_remoteSize);
	app->WriteProfileInt("T42View","Orientation",m_Ort);
}

void T42View::OnCancelMode() 
{
	CFormView::OnCancelMode();
	if(m_bTracking){
		ClipCursor(NULL);
		m_bTracking=FALSE;
		ReleaseCapture();
	}
}

void T42View::LoadLayout()
{
CWinApp* app = AfxGetApp();
	m_localSize = app->GetProfileInt("T42View","LocalSize",m_localSize);
	m_remoteSize = app->GetProfileInt("T42View","RemoteSize",m_remoteSize);
_orientation ortSave = m_Ort;
	m_Ort = (_orientation)app->GetProfileInt("T42View","Orientation",m_Ort);
	if(m_Ort!=ortHorizontal && m_Ort!=ortVertical)
		m_Ort=ortSave;
}

void T42View::SystemMessage(LPCTSTR str)
{
CT42App* app = (CT42App*)AfxGetApp();
	m_localCtl.SystemMessage(str);
	m_remoteCtl.SystemMessage(str);
}


void T42View::OnUpdateTeaSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_localCtl.GetTextLength() || m_remoteCtl.GetTextLength());
}

void T42View::OnTeaSave() 
{
CString dfn;
	dfn.Format(IDS_FILENAME_T42,	m_pFrame->m_LocalUser,m_pFrame->m_Target);
CString filter;
	VERIFY(filter.LoadString(IDS_FILTER_RTF));
CFileDialog fd(FALSE,".rtf",dfn,
			   OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER|
			   OFN_LONGNAMES|OFN_NOREADONLYRETURN|OFN_PATHMUSTEXIST,
			   filter,this
	);
	if(fd.DoModal()==IDOK){
		try{
		CStdioFile f(fd.GetPathName(),
				CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite|
				CFile::typeText);
		CString rtf;
			rtf.Format(IDS_RTF_HEAD,m_pFrame->m_LocalUser,m_pFrame->m_Target);
			f.WriteString(rtf);
		CMemFile mf(2048);
		EDITSTREAM es;
			memset(&es,0,sizeof(es));
			es.dwCookie = (DWORD)&mf;
			es.pfnCallback = ESINProc;
			m_localCtl.StreamOut(SF_RTF,es);
		UINT tmp=0;
			mf.Write(&tmp,1);
		LONG bytes = mf.GetLength();
		LPBYTE pd = mf.Detach();
		LPTSTR str;
			while(str = strstr((LPCTSTR)pd,"\\rtf1"))memmove(str,&str[5],strlen(str)-4);
			while(str = strstr((LPCTSTR)pd,"\\pard"))memmove(str,&str[5],strlen(str)-4);
			f.Write(pd,strlen((LPCTSTR)pd));
			rtf.LoadString(IDS_RTF_DELIMITER);
			f.WriteString(rtf);
			mf.Attach(pd,bytes,2048);
			memset(&es,0,sizeof(es));
			es.dwCookie = (DWORD)&mf;
			es.pfnCallback = ESINProc;
			m_remoteCtl.StreamOut(SF_RTF,es);
			mf.Write(&tmp,1);
			bytes = mf.GetLength();
			pd = mf.Detach();
			while(str = strstr((LPCTSTR)pd,"\\rtf1"))memmove(str,&str[5],strlen(str)-4);
			while(str = strstr((LPCTSTR)pd,"\\pard"))memmove(str,&str[5],strlen(str)-4);
			f.Write(pd,strlen((LPCTSTR)pd));
			rtf.LoadString(IDS_RTF_TAIL);
			f.WriteString(rtf);
			delete pd;
			f.Close();
		}catch(CException* e){
			TRACE0("Write exception\n");
			e->Delete();
		}
	}
}

DWORD CALLBACK T42View::ESINProc(DWORD dwCookie,LPBYTE pbBuff,LONG cb,LONG FAR *pcb)
{
CFile* f = (CFile*)dwCookie;
	try{
		f->Write(pbBuff,cb);
		(*pcb)=cb;
	}catch(CException* e){
		e->Delete();
		TRACE0("Save Exception\n");
		(*pcb)=0;
		return 1;
	}
	return 0;
}
