// T42AnnounceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T42AnnounceDlg dialog

class T42AnnounceDlg : public CDialog
{
// Construction
public:
	CFont m_Font;
	LPCSTR m_hSound;
	BOOL m_bLooped;
	CString m_ipCaller;
	UINT m_timeOut;
	HANDLE m_asyncRequest;
	CHAR m_ResolveBuffer[MAXGETHOSTSTRUCT];
	TalkCtlMessage m_RQ;
	T42AnnounceDlg(TalkCtlMessage& rq,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T42AnnounceDlg)
	enum { IDD = IDD_ANNOUNCE };
	CStatic	m_CalleeCtl;
	CStatic	m_TTYCtl;
	CButton	m_YesCtl;
	CButton	m_NotMeCtl;
	CButton	m_SecretaryCtl;
	CStatic	m_CallerCtl;
	CString	m_Callee;
	CString	m_Caller;
	CString	m_TTY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T42AnnounceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T42AnnounceDlg)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnSourceResolved(WPARAM,LPARAM);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSecretary();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
