// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "T42.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers


void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType==ODT_BUTTON);
CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
CRect rc(lpDrawItemStruct->rcItem);
	pDC->DrawFrameControl(
		&rc,
		DFC_BUTTON,
		DFCS_BUTTONPUSH|(
			(lpDrawItemStruct->itemState&ODS_DISABLED)
			? DFCS_INACTIVE
			: (
				(lpDrawItemStruct->itemState&ODS_SELECTED)
				? DFCS_PUSHED
				: 0
			)
		)|DFCS_ADJUSTRECT
	);
	if(!(lpDrawItemStruct->itemState&ODS_DISABLED)){
	CBrush b(m_Color);
		pDC->FillRect(rc,&b);
		if(lpDrawItemStruct->itemState&ODS_FOCUS)
			pDC->DrawFocusRect(rc);
	}
CString txt;
	GetWindowText(txt);
	if((lpDrawItemStruct->itemState&ODS_DISABLED)){
	CSize sz = pDC->GetOutputTextExtent(txt);
		if(txt.Find('&')>=0)
			sz.cx-=pDC->GetOutputTextExtent("&",1).cx;
	CRect rcc;
		rcc.top=rcc.bottom=rc.CenterPoint().y;
		rcc.left=rcc.right=rc.CenterPoint().x;
		rcc.InflateRect(sz.cx/2,sz.cy/2);
		pDC->DrawState(rcc.TopLeft(),rcc.Size(),(LPCTSTR)txt,DST_PREFIXTEXT|DSS_DISABLED,TRUE,0,(HBRUSH)NULL);
	}else{
	COLORREF ocol = pDC->SetTextColor(/*RGB(255,255,255)^*/~m_Color);
	int omo = pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(txt,&rc,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		pDC->SetBkMode(omo);
		pDC->SetTextColor(ocol);
	}
}

COLORREF CColorButton::SelectColor(COLORREF color)
{
CColorDialog cd(color,CC_RGBINIT,this);
	if(cd.DoModal()==IDOK)
		return cd.GetColor();
	else
		return color;
}

void CColorButton::SetColor()
{
	m_Color=SelectColor(m_Color);
	Invalidate();
}
