// SoundsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSoundsPage dialog

class CSoundsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSoundsPage)

// Construction
public:
	void PlayIt(CComboBox& ctl,BOOL bLoop=FALSE);
	void BrowseForSound(CComboBox& ctl);
	CSoundsPage();
	~CSoundsPage();

// Dialog Data
	//{{AFX_DATA(CSoundsPage)
	enum { IDD = IDD_OPTIONS_SOUNDS };
	CButton	m_T42WakePlayCtl;
	CButton	m_T42PromptPlayCtl;
	CButton	m_T42BellPlayCtl;
	CButton	m_T42WakeBrowseCtl;
	CComboBox	m_T42WakeCtl;
	CButton	m_T42PromptBrowseCtl;
	CComboBox	m_T42PromptCtl;
	CButton	m_T42BellBrowseCtl;
	CComboBox	m_T42BellCtl;
	CString	m_T42Bell;
	CString	m_T42Prompt;
	BOOL	m_bT42PromptLoop;
	CString	m_T42Wake;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSoundsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSoundsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnT42bellBrowse();
	afx_msg void OnT42promptBrowse();
	afx_msg void OnT42wakeBrowse();
	afx_msg void OnT42bellPlay();
	afx_msg void OnT42promptPlay();
	afx_msg void OnT42wakePlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
