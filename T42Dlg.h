// T42Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CT42Dlg dialog

class CTTable : public CObject {
public:
	TalkCtlMessage	m_RQ;
	CTime	m_Time;

	CTTable() {}
	CTTable(CTTable& src) { Copy(src); }

	void Copy(CTTable& src) {
		memmove(&m_RQ,&src.m_RQ,sizeof(m_RQ));
		m_Time = src.m_Time;
	}

	CTTable& operator=(CTTable& src) {
		Copy(src);
		return *this;
	}

	BOOL operator==(TalkCtlMessage& m) {
		return (
			strcmp(m_RQ.m_LName,m.m_LName)==0
			&& strcmp(m_RQ.m_RName,m.m_RName)==0
			&& m_RQ.m_Type == m.m_Type
			&& m_RQ.m_PID == m.m_PID
		);
	}

	BOOL Match(TalkCtlMessage& m) {
		return (
			strcmp(m_RQ.m_LName,m.m_RName)==0
			&& strcmp(m_RQ.m_RName,m.m_LName)==0
			&& m_RQ.m_Type == talkCtlReqLeaveInvite
		);
	}
};

typedef	CList<CTTable,CTTable&> CTRestaurant;

class CT42Dlg : public CDialog
{
// Construction
public:
	~CT42Dlg();
	void SaveSettings();
	void LoadSettings();
	UINT GetOnCtl(CComboBox& ctl);
	void SetOnCtl(UINT nAction,CComboBox& ctl);
	UINT m_onCall;
	UINT m_onCallAway;
	BOOL m_bAway;
	CSize m_sizeMin;
	UINT m_gapY;
	UINT m_marginY;
	UINT m_marginX;
	void RecalcLayout();
	void SetTheIcon(HICON hIcon);
	UINT m_newCalls;
	HICON m_hIconEmpty;
	HICON m_hIconFull;
	HWND m_hExFW;
	int m_iProcessed;
	int m_iNew;
	CImageList m_Images;
	static DWORD CALLBACK ESOUTProc(DWORD dwCookie,LPBYTE pbBuff,LONG cb,LONG FAR *pcb);
	void SetColumnWidths();
	void OnDelT42Call();
	void OnAddT42Call();
	enum	{
		subitemTime=0,
			subitemCaller, subitemCallee, subitemDuration,
			subitemTTY
	};
	void InitCalls();
	BOOL m_bShown;
	BOOL m_bExiting;
	void ToggleVisibility();
	BITMAP m_bitmapBack;
	CBitmap m_bmpBack;
	DWORD m_trackTalkID;
	CTimeSpan m_talkLifetime;
	CTRestaurant m_talks;
	CTRestaurant m_announcements;
	SOCKET m_daemonSocket;
	CT42Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CT42Dlg)
	enum { IDD = IDD_T42_DIALOG };
	CButton	m_ExitCtl;
	CButton	m_TeaCtl;
	CButton	m_AwayCtl;
	CButton	m_HelpCtl;
	CButton	m_OptionsCtl;
	CComboBox	m_OnCallAwayCtl;
	CComboBox	m_OnCallCtl;
	CListCtrl	m_CallsCtl;
	CRichEditCtrl m_PreviewCtl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT42Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CT42Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTalk();
	afx_msg LRESULT OnDaemon(WPARAM,LPARAM);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnTrayIcon(WPARAM,LPARAM);
	virtual void OnCancel();
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	virtual void OnOK();
	afx_msg void OnTrayExit();
	afx_msg void OnTrayOptions();
	afx_msg void OnTrayShowmainwindow();
	afx_msg void OnTrayT42();
	afx_msg void OnOptions();
	afx_msg void OnGetdispinfoCalls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedCalls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickCalls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCalllogCallback();
	afx_msg void OnCalllogDelete();
	afx_msg void OnCalllogSavetofile();
	afx_msg void OnCalllogEmptylog();
	afx_msg void OnDeleteitemCalls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnUpdatePreview(WPARAM,LPARAM);
	afx_msg void OnKeydownCalls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCalllogMarkasnew();
	afx_msg void OnCalllogMarkasprocessed();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnAway();
	afx_msg void OnSelendokOncall();
	afx_msg void OnSelendokOncallaway();
	afx_msg void OnTrayAway();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnQueryEndSession();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
