// FontsPage.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "FontsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontsPage property page

IMPLEMENT_DYNCREATE(CFontsPage, CPropertyPage)

CFontsPage::CFontsPage() : CPropertyPage(CFontsPage::IDD)
{
	//{{AFX_DATA_INIT(CFontsPage)
	//}}AFX_DATA_INIT
CRichEditCtrl tmp;
	tmp.Create(WS_CHILD,CRect(0,0,0,0),AfxGetApp()->m_pMainWnd,0);
	memset(&m_fmtChar,0,sizeof(m_fmtChar));
	m_fmtLast=NULL;
}

CFontsPage::~CFontsPage()
{
}

void CFontsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontsPage)
	DDX_Control(pDX, IDC_TIP, m_TipCtl);
	DDX_Control(pDX, IDC_FORECOLOR, m_fgColorCtl);
	DDX_Control(pDX, IDC_BACKCOLOR, m_bgColorCtl);
	DDX_Control(pDX, IDC_CHARSET, m_CharsetCtl);
	DDX_Control(pDX, IDC_UNDERLINE, m_UnderlineCtl);
	DDX_Control(pDX, IDC_STRIKEOUT, m_StrikeoutCtl);
	DDX_Control(pDX, IDC_ITALIC, m_ItalicCtl);
	DDX_Control(pDX, IDC_BOLD, m_BoldCtl);
	DDX_Control(pDX, IDC_FONTSIZE, m_SizeCtl);
	DDX_Control(pDX, IDC_FORMATNAME, m_FormatsCtl);
	DDX_Control(pDX, IDC_FACES, m_FacesCtl);
	DDX_Control(pDX, IDC_SAMPLE, m_SampleCtl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFontsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFontsPage)
	ON_CBN_SELENDOK(IDC_FACES, OnSelendokFaces)
	ON_BN_CLICKED(IDC_BOLD, OnBold)
	ON_CBN_SELENDOK(IDC_FONTSIZE, OnSelendokFontsize)
	ON_CBN_EDITCHANGE(IDC_FONTSIZE, OnEditchangeFontsize)
	ON_BN_CLICKED(IDC_ITALIC, OnItalic)
	ON_BN_CLICKED(IDC_STRIKEOUT, OnStrikeout)
	ON_BN_CLICKED(IDC_UNDERLINE, OnUnderline)
	ON_CBN_SELENDOK(IDC_CHARSET, OnSelendokCharset)
	ON_BN_CLICKED(IDC_BACKCOLOR, OnBackcolor)
	ON_BN_CLICKED(IDC_FORECOLOR, OnForecolor)
	ON_LBN_SELCHANGE(IDC_FORMATNAME, OnSelchangeFormatname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontsPage message handlers

BOOL CFontsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_SampleCtl.GetDefaultCharFormat(m_fmtDefChar);

	// Fill in faces combo
	m_FacesCtl.ResetContent();
CClientDC dc(NULL);
LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	lf.lfCharSet = DEFAULT_CHARSET;
	EnumFontFamiliesEx(dc.m_hDC,&lf,(FONTENUMPROC)FillInFaces,(LPARAM)&m_FacesCtl,0);

	// Fill in formats list
	FillInFormats();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CALLBACK CFontsPage::FillInFaces(const ENUMLOGFONTEX* lpelfe,const TEXTMETRIC* lpntme,const int FontType,const LPARAM lParam)
{
//	if(FontType!=TRUETYPE_FONTTYPE)
//		return 1;
CComboBox* cb = (CComboBox*)lParam;
	ASSERT(cb);
	if(cb->FindString(0,lpelfe->elfLogFont.lfFaceName)>=0)
		return 1;
	cb->AddString(lpelfe->elfLogFont.lfFaceName);
	return 1;
}


void CFontsPage::UpdateFormat(BOOL bSave)
{
	if(bSave){
	CString tmp;
		m_FacesCtl.GetWindowText(tmp);
		strcpy(m_fmtChar.szFaceName,tmp); m_fmtChar.dwMask|=CFM_FACE;
		m_SizeCtl.GetWindowText(tmp);
		m_fmtChar.yHeight = atoi(tmp)?(atoi(tmp)*REFS2PTS):m_fmtChar.yHeight;
		m_fmtChar.dwMask|=CFM_SIZE;
		if(m_BoldCtl.GetCheck())
			m_fmtChar.dwEffects|=CFE_BOLD;
		else
			m_fmtChar.dwEffects&=~CFE_BOLD;
		m_fmtChar.dwMask|=CFM_BOLD;
		if(m_ItalicCtl.GetCheck())
			m_fmtChar.dwEffects|=CFE_ITALIC;
		else
			m_fmtChar.dwEffects&=~CFE_ITALIC;
		m_fmtChar.dwMask|=CFM_ITALIC;
		if(m_StrikeoutCtl.GetCheck())
			m_fmtChar.dwEffects|=CFE_STRIKEOUT;
		else
			m_fmtChar.dwEffects&=~CFE_STRIKEOUT;
		m_fmtChar.dwMask|=CFM_STRIKEOUT;
		if(m_UnderlineCtl.GetCheck())
			m_fmtChar.dwEffects|=CFE_UNDERLINE;
		else
			m_fmtChar.dwEffects&=~CFE_UNDERLINE;
		m_fmtChar.dwMask|=CFM_UNDERLINE;
		if(m_CharsetCtl.IsWindowEnabled())
			m_fmtChar.bCharSet=m_CharsetCtl.GetItemData(m_CharsetCtl.GetCurSel());
		else
			m_fmtChar.bCharSet=DEFAULT_CHARSET;
		m_fmtChar.crTextColor = m_fgColorCtl.m_Color;
		m_fmtChar.dwMask|=CFM_COLOR;
		m_fmtChar.dwEffects&=~CFE_AUTOCOLOR;
		UpdateSample();
	}else{
		if(m_fmtChar.cbSize!=sizeof(m_fmtChar))
			memmove(&m_fmtChar,&m_fmtDefChar,sizeof(m_fmtChar));
		if(m_fmtChar.dwMask&CFM_FACE)
			m_FacesCtl.SelectString(0,m_fmtChar.szFaceName);
	CString tmp;
		if(m_fmtChar.dwMask&CFM_SIZE){
			tmp.Format("%d",m_fmtChar.yHeight/REFS2PTS);
			m_SizeCtl.SetWindowText(tmp);
		}
		if(m_fmtChar.dwMask&CFM_BOLD)
			m_BoldCtl.SetCheck((m_fmtChar.dwEffects&CFE_BOLD)?1:0);
		if(m_fmtChar.dwMask&CFM_ITALIC)
			m_ItalicCtl.SetCheck((m_fmtChar.dwEffects&CFE_ITALIC)?1:0);
		if(m_fmtChar.dwMask&CFM_STRIKEOUT)
			m_StrikeoutCtl.SetCheck((m_fmtChar.dwEffects&CFE_STRIKEOUT)?1:0);
		if(m_fmtChar.dwMask&CFM_UNDERLINE)
			m_UnderlineCtl.SetCheck((m_fmtChar.dwEffects&CFE_UNDERLINE)?1:0);
		m_fgColorCtl.m_Color = (m_fmtChar.dwMask&CFM_COLOR)?m_fmtChar.crTextColor:0;
		m_fgColorCtl.Invalidate();
		FillCharsets();
	}
}

void CFontsPage::UpdateSample()
{
	m_SampleCtl.SetReadOnly(TRUE);
	m_SampleCtl.SetTargetDevice(NULL,0);
	m_SampleCtl.SetSel(0,-1);
	m_SampleCtl.ReplaceSel(
		(m_fmtChar.dwMask&CFM_FACE)
		? (
			(*m_fmtChar.szFaceName)
			? m_fmtChar.szFaceName
			: "Sample"
		)
		: "Sample"
	);
	m_SampleCtl.SetSel(0,-1);
	m_SampleCtl.SetSelectionCharFormat(m_fmtChar);
PARAFORMAT pf;
	memset(&pf,0,sizeof(pf));
	pf.cbSize = sizeof(pf);
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_CENTER;
	m_SampleCtl.SetParaFormat(pf);
	m_SampleCtl.HideSelection(TRUE,TRUE);
	if(m_bgColorCtl.IsWindowEnabled())
		m_SampleCtl.SetBackgroundColor(FALSE,m_bgColorCtl.m_Color);
}

void CFontsPage::OnSelendokFaces() 
{
	UpdateFormat(TRUE);
	FillCharsets();
}

void CFontsPage::OnSelendokFontsize() 
{
CString tmp;
	m_SizeCtl.GetLBText(m_SizeCtl.GetCurSel(),tmp);
	m_SizeCtl.SetWindowText(tmp);
	UpdateFormat(TRUE);
}
void CFontsPage::OnEditchangeFontsize() 
{
	UpdateFormat(TRUE);	
}

void CFontsPage::OnBold() 
{
	UpdateFormat(TRUE);
}
void CFontsPage::OnItalic() 
{
	UpdateFormat(TRUE);
}
void CFontsPage::OnStrikeout() 
{
	UpdateFormat(TRUE);
}
void CFontsPage::OnUnderline() 
{
	UpdateFormat(TRUE);
}

void CFontsPage::FillCharsets()
{
	m_CharsetCtl.EnableWindow(TRUE);
	m_CharsetCtl.ResetContent();
CString tmp;
	tmp.LoadString(IDS_CHARSET_AUTO);
	VERIFY(m_CharsetCtl.AddString(tmp)==0);
	VERIFY(m_CharsetCtl.SetItemData(0,DEFAULT_CHARSET)!=LB_ERR);
	if(m_fmtChar.dwMask&CFM_FACE && *m_fmtChar.szFaceName){
	CClientDC dc(NULL);
	LOGFONT lf;
		memset(&lf,0,sizeof(lf));
		lf.lfCharSet = DEFAULT_CHARSET;
		strcpy(lf.lfFaceName,m_fmtChar.szFaceName);
		EnumFontFamiliesEx(dc.m_hDC,&lf,(FONTENUMPROC)FillInCharsets,(LPARAM)&m_CharsetCtl,0);
	}
int ii = m_CharsetCtl.GetCount();
	for(int i=0;i<ii;i++){
		if(m_CharsetCtl.GetItemData(i)==m_fmtChar.bCharSet){
			m_CharsetCtl.SetCurSel(i);
			break;
		}
	}
	m_CharsetCtl.EnableWindow(m_CharsetCtl.GetCount()>1);
}

int CALLBACK CFontsPage::FillInCharsets(const ENUMLOGFONTEX* lpelfe,const TEXTMETRIC* lpntme,const int FontType,const LPARAM lParam)
{
//	if(FontType!=TRUETYPE_FONTTYPE)
//		return 1;
CComboBox* cb = (CComboBox*)lParam;
	ASSERT(cb);
	if(cb->FindString(0,(char*)lpelfe->elfScript)>=0)
		return 1;
int i = cb->AddString((char*)lpelfe->elfScript);
	ASSERT(i>=0);
	VERIFY(cb->SetItemData(i,lpelfe->elfLogFont.lfCharSet)!=LB_ERR);
	return 1;
}

void CFontsPage::OnSelendokCharset() 
{
	UpdateFormat(TRUE);
}

void CFontsPage::FillInFormats()
{
	AddFmt(IDS_FMT_T42LOCAL,&m_fmtT42Local);
	AddFmt(IDS_FMT_T42REMOTE,&m_fmtT42Remote);
	AddFmt(IDS_FMT_T42SYSTEM,&m_fmtT42System,0);
	m_FormatsCtl.SetCurSel(0);
	OnSelchangeFormatname();
}
void CFontsPage::AddFmt(UINT name,CFontFormat* cf,UINT flags)
{
CString f;
	VERIFY(f.LoadString(name));
int lf = f.Find('\n');
int i = m_FormatsCtl.AddString((lf<0)?f:f.Left(lf));
	ASSERT(i>=0);
	m_FormatsCtl.SetItemData(i,(LPARAM)cf);
	cf->m_Tip = (lf<0)?"":f.Mid(lf+1);
	cf->m_Flags = flags;
}
void CFontsPage::OnSelchangeFormatname() 
{
CFontFormat* fmt = (CFontFormat*)m_FormatsCtl.GetItemData(m_FormatsCtl.GetCurSel());
	if(m_fmtLast){
		memmove(&m_fmtLast->m_fmtChar,&m_fmtChar,sizeof(m_fmtLast->m_fmtChar));
		if(m_fmtLast->m_Flags&CFontFormat::flagBGColor)
			m_fmtLast->m_bgColor = m_bgColorCtl.m_Color;
	}
BOOL bBG = fmt->m_Flags&CFontFormat::flagBGColor;
	m_bgColorCtl.EnableWindow(bBG);
	m_TipCtl.SetWindowText(fmt->m_Tip);
	m_fmtLast = fmt;
	memmove(&m_fmtChar,&m_fmtLast->m_fmtChar,sizeof(m_fmtChar));
	if(bBG){
		m_bgColorCtl.m_Color = m_fmtLast->m_bgColor;
		m_bgColorCtl.Invalidate();
	}
	UpdateFormat(FALSE);
	UpdateSample();
}

void CFontsPage::OnBackcolor() 
{
	m_bgColorCtl.SetColor();
	UpdateFormat(TRUE);
}
void CFontsPage::OnForecolor() 
{
	m_fgColorCtl.SetColor();
	UpdateFormat(TRUE);
}

void CFontsPage::OnOK() 
{
	if(m_fmtLast){
		memmove(&m_fmtLast->m_fmtChar,&m_fmtChar,sizeof(m_fmtLast->m_fmtChar));
		if(m_fmtLast->m_Flags&CFontFormat::flagBGColor)
			m_fmtLast->m_bgColor = m_bgColorCtl.m_Color;
	}
	CPropertyPage::OnOK();
}
