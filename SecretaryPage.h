// SecretaryPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecretaryPage dialog

class CSecretaryPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSecretaryPage)

// Construction
public:
	void SetWinLimit();
	void SetBytesLimit();
	void SetTimeLimit();
	CSecretaryPage();
	~CSecretaryPage();

// Dialog Data
	//{{AFX_DATA(CSecretaryPage)
	enum { IDD = IDD_OPTIONS_SECRETARY };
	CButton	m_bLimitWinCtl;
	CSpinButtonCtrl	m_WinSpinCtl;
	CSpinButtonCtrl	m_TimeSpinCtl;
	CEdit	m_limitWinCtl;
	CSpinButtonCtrl	m_CharSpinCtl;
	CEdit	m_limitTimeCtl;
	CButton	m_bLimitTimeCtl;
	CButton	m_bLimitBytesCtl;
	CEdit	m_limitBytesCtl;
	UINT	m_limitBytes;
	BOOL	m_bLimitBytes;
	BOOL	m_bLimitTime;
	CString	m_Greeting;
	UINT	m_limitTime;
	BOOL	m_bLimitWin;
	UINT	m_limitWin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSecretaryPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSecretaryPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDobytelimit();
	afx_msg void OnDotimelimit();
	afx_msg void OnDowinlimit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
