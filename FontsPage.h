// FontsPage.h : header file
//

#include "ColorButton.h"

/////////////////////////////////////////////////////////////////////////////
// CFontsPage dialog

struct	CFontFormat	{
	CHARFORMAT	m_fmtChar;
	COLORREF	m_bgColor;
	enum	_flags	{
		flagBGColor = 1
	};
	int			m_Flags;
	CString		m_Tip;
};

class CFontsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFontsPage)

// Construction
public:
	CHARFORMAT m_fmtDefChar;
	CFontFormat* m_fmtLast;
	void AddFmt(UINT name,CFontFormat* cf,UINT flags=CFontFormat::flagBGColor);
	void FillInFormats();
	CFontFormat m_fmtT42System;
	CFontFormat m_fmtT42Remote;
	CFontFormat m_fmtT42Local;
	static int CALLBACK FillInCharsets(const ENUMLOGFONTEX* lpelfe,const TEXTMETRIC* lpntme,const int FontType,const LPARAM lParam);
	void FillCharsets();
	void UpdateSample();
	void UpdateFormat(BOOL bSave=FALSE);
	CHARFORMAT m_fmtChar;
	static int CALLBACK FillInFaces(const ENUMLOGFONTEX* lpelfe,const TEXTMETRIC* lpntme,const int FontType,const LPARAM lParam);
	CFontsPage();
	~CFontsPage();

// Dialog Data
	//{{AFX_DATA(CFontsPage)
	enum { IDD = IDD_OPTIONS_FONTS };
	CStatic	m_TipCtl;
	CColorButton	m_fgColorCtl;
	CColorButton	m_bgColorCtl;
	CComboBox	m_CharsetCtl;
	CButton	m_UnderlineCtl;
	CButton	m_StrikeoutCtl;
	CButton	m_ItalicCtl;
	CButton	m_BoldCtl;
	CComboBox	m_SizeCtl;
	CListBox	m_FormatsCtl;
	CComboBox	m_FacesCtl;
	CRichEditCtrl m_SampleCtl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFontsPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFontsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokFaces();
	afx_msg void OnBold();
	afx_msg void OnSelendokFontsize();
	afx_msg void OnEditchangeFontsize();
	afx_msg void OnItalic();
	afx_msg void OnStrikeout();
	afx_msg void OnUnderline();
	afx_msg void OnSelendokCharset();
	afx_msg void OnBackcolor();
	afx_msg void OnForecolor();
	afx_msg void OnSelchangeFormatname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
