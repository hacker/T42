// T42Document.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T42Document document

class T42Document;
class T42View;

class CT42Robot	{
public:
	T42Document* m_pDocument;

	CT42Robot() : m_pDocument(NULL)	{}
	virtual ~CT42Robot() {}

	virtual BOOL OnAttach(T42Document* pDocument) {
		m_pDocument = pDocument;
		return TRUE;
	}
	virtual BOOL OnDetach() { return TRUE; }

	virtual BOOL OnConnect()			{ return TRUE; }
	virtual BOOL OnReceive(char*,int)	{ return TRUE; }
	virtual BOOL OnDisconnect()			{ return TRUE; }

	virtual	BOOL OnIPResolved()			{ return TRUE; }

	virtual BOOL OnMinute()				{ return TRUE; }
};

class T42Document : public CDocument
{
protected:
	T42Document();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(T42Document)

// Attributes
public:
	void OnMinute();
	BOOL m_bHidden;
	BOOL SendOver(LPCTSTR str);
	BOOL DetachRobot();
	BOOL AttachRobot(CT42Robot* pRobot);
	CT42Robot* m_pRobot;
	void AutosaveLayout();
	void SaveLayout();
	T42View* m_pView;
	void Talk(LPCTSTR from=NULL,LPCTSTR to=NULL,LPCTSTR tty=NULL,BOOL bPrompt=FALSE);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T42Document)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnChangedViewList();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~T42Document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(T42Document)
	afx_msg void OnWindowSavelayout();
	afx_msg void OnUpdateWindowAutosavelayout(CCmdUI* pCmdUI);
	afx_msg void OnWindowAutosavelayout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
