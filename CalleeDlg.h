// CalleeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalleeDlg dialog

class CCalleeDlg : public CDialog
{
// Construction
public:
	CCalleeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalleeDlg)
	enum { IDD = IDD_REMOTE };
	CComboBox	m_CallerCtl;
	CComboBox	m_CalleeCtl;
	CString	m_Callee;
	CString	m_Caller;
	CString	m_TTY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalleeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalleeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
