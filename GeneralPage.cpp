// GeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "GeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralPage property page

IMPLEMENT_DYNCREATE(CGeneralPage, CPropertyPage)

CGeneralPage::CGeneralPage() : CPropertyPage(CGeneralPage::IDD)
{
	//{{AFX_DATA_INIT(CGeneralPage)
	//}}AFX_DATA_INIT
	m_ntalkPort = 518;
}

CGeneralPage::~CGeneralPage()
{
}

void CGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralPage)
	DDX_Control(pDX, IDC_NTALKPORTSPIN, m_ntalkSpinCtl);
	DDX_Control(pDX, IDC_NTALKPORT, m_ntalkPortCtl);
	//}}AFX_DATA_MAP
	if(pDX->m_bSaveAndValidate){
		pDX->PrepareEditCtrl(IDC_NTALKPORT);
	CString ntp;
		m_ntalkPortCtl.GetWindowText(ntp);
	UINT p = atoi(ntp);
		if(!p){
		servent* se = getservbyname((LPCTSTR)ntp,"udp");
			if(se)
				p = ntohs(se->s_port);
			else{
				AfxMessageBox(IDS_FAILVALIDATE_NTALKPORT,MB_OK|MB_ICONSTOP);
				pDX->Fail();
				return;
			}
		}
		m_ntalkPort = p;
	}
}


BEGIN_MESSAGE_MAP(CGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGeneralPage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NTALKPORTSPIN, OnDeltaposNtalkportspin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralPage message handlers

BOOL CGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_ntalkSpinCtl.SetRange(1,min(UD_MAXVAL,65535));
	m_ntalkSpinCtl.SetPos(m_ntalkPort);
	SetPortCtl();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGeneralPage::SetPortCtl()
{
servent* se = getservbyport(htons(m_ntalkPort),"udp");
	if(se)
		m_ntalkPortCtl.SetWindowText(se->s_name);
	else{
	CString tmp;
		tmp.Format("%u",m_ntalkPort);
		m_ntalkPortCtl.SetWindowText(tmp);
	}
}

void CGeneralPage::OnDeltaposNtalkportspin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	TRACE3("UD iP %d, iD %d, p %d\n",pNMUpDown->iPos,
		pNMUpDown->iDelta, m_ntalkSpinCtl.GetPos());
	m_ntalkPort = pNMUpDown->iPos+pNMUpDown->iDelta;
	SetPortCtl();
	
	*pResult = 0;
}
