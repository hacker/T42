// T42Frame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T42Frame frame

struct	TalkEditChars	{
	CHAR	m_cErase;
	CHAR	m_kill;
	CHAR	m_wErase;
};

class T42View;
class T42Frame : public CFrameWnd
{
	DECLARE_DYNCREATE(T42Frame)

// Attributes
public:
	BOOL m_bConnected;
	void SystemMessage(UINT nID,LPCTSTR str);
	void WSSystemMessage(UINT nID,LONG wsaError);
	void SystemMessage(UINT nID,UINT nIDi);
	void SystemMessage(LPCTSTR str);
	void SystemMessage(UINT nID);
	BOOL m_bMinimizeSleep;
	void DeTray();
	void WakeUp();
	enum	_wakeAction	{
		wakePopup = 1,
		wakeSound = 2
	};
	UINT m_onWake;
	BOOL m_bSleep;
	BOOL m_bSleepMinimize;
	BOOL m_bTrayed;
	void SetTheIcon(HICON hicon);
	BOOL m_bTrayMinimize;
	void LoadLayout();
	BOOL m_bHaveFocus;
	HICON m_hFullCup;
	HICON m_hNormal;
	void AddToHotList(LPCTSTR str=NULL);
	BOOL m_bEstablished;
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	void SetPeerName(LPCTSTR str=NULL);
	void SaveLayout();
	CString m_nameFromIP;
	BYTE m_ghResolve[MAXGETHOSTSTRUCT];
	HANDLE m_resolveHandle;
	void CleanUp();
	CWnd m_wndFake;
	void Established(BOOL bEstablished);
	void ShowMessage(LPCTSTR msg,UINT flags);
	void ShowMessage(UINT nID,UINT flags);
	void StatusLine(UINT nID);
	CString m_Status;
	void StatusLine(LPCTSTR str);
	int m_nDatePaneNo;
	CString m_sendBuffer;
	BOOL m_bSentEC;
	UINT m_receivedEC;
	TalkEditChars m_localEC;
	TalkEditChars m_remoteEC;
	BOOL PutRemote(LPCTSTR str);
	void SelectTalkSocket();
	LONG m_remoteID;
	LONG m_localID;
	void AsyncCtlTransactSucceeded(TalkCtlResponse& response);
	void AsyncCtlTransactFailed(UINT code,LONG error);
	enum	{
		ctlFailSendto = 1,
		ctlFailSelect, ctlFailError
	};
	UINT	m_ctlSuccess;
	UINT	m_ctlFailure;
	sockaddr_in m_ctlTarget;
	BOOL AsyncCtlTransact(TalkCtlMessage& msg,sockaddr_in& target, UINT wmSuccess,UINT wmFailure);
	TalkCtlMessage m_ctlRequest;
	TalkCtlResponse m_ctlResponse;
	CString m_TargetTTY;
	CString m_LocalUser;
	BOOL FillInMessage(TalkCtlMessage& msg);
	SOCKET m_Socket;
	SOCKADDR_IN m_ctlAddr;
	SOCKET m_ctlSocket;
	SOCKADDR_IN m_SourceAddr;
	SOCKADDR_IN m_TargetAddr;
	BYTE m_gethostData[MAXGETHOSTSTRUCT];
	HANDLE m_asyncHandle;
	CString m_TargetHost;
	CString m_TargetUser;
	CString m_Target;

// Operations
public:
	T42Frame();           // protected constructor used by dynamic creation

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T42Frame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStatusBar  m_wndStatusBar;
	virtual ~T42Frame();
public:
	// Generated message map functions
	//{{AFX_MSG(T42Frame)
	afx_msg void OnClose();
	afx_msg void OnTalkRemoteuser();
	afx_msg LRESULT OnInitiateTalk(WPARAM,LPARAM);
	afx_msg LRESULT OnTargetResolved(WPARAM,LPARAM);
	afx_msg LRESULT OnSourceResolved(WPARAM,LPARAM);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnCTLTransact(WPARAM,LPARAM);
	afx_msg LRESULT OnLookupSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnLookupFailure(WPARAM,LPARAM);
	afx_msg LRESULT OnAnnounceSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnAnnounceFailure(WPARAM,LPARAM);
	afx_msg LRESULT OnLeaveInviteSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnLeaveInviteFailure(WPARAM,LPARAM);
	afx_msg LRESULT OnTalkAccept(WPARAM,LPARAM);
	afx_msg LRESULT OnLocalRemoveSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnLocalRemoveFailure(WPARAM,LPARAM);
	afx_msg LRESULT OnRemoteRemoveSuccess(WPARAM,LPARAM);
	afx_msg LRESULT OnRemoteRemoveFailure(WPARAM,LPARAM);
	afx_msg LRESULT OnTalk(WPARAM,LPARAM);
	afx_msg LRESULT OnTalkChar(WPARAM,LPARAM);
	afx_msg LRESULT OnTalkConnect(WPARAM,LPARAM);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
	afx_msg LRESULT OnExitMenuLoop(WPARAM,LPARAM);
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnNameResolved(WPARAM,LPARAM);
	afx_msg LRESULT OnIPResolved(WPARAM,LPARAM);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnTrayIcon(WPARAM,LPARAM);
	afx_msg void OnUpdateWindowHideintrayonminimize(CCmdUI* pCmdUI);
	afx_msg void OnWindowHideintrayonminimize();
	afx_msg void OnTalkAbort();
	afx_msg void OnUpdateTalkAbort(CCmdUI* pCmdUI);
	afx_msg void OnTalkReconnect();
	afx_msg void OnUpdateTalkReconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTalkRemoteuser(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSleepSleep(CCmdUI* pCmdUI);
	afx_msg void OnSleepSleep();
	afx_msg void OnUpdateSleepSleeponminimize(CCmdUI* pCmdUI);
	afx_msg void OnSleepSleeponminimize();
	afx_msg void OnUpdateSleepWakeupactionMakesound(CCmdUI* pCmdUI);
	afx_msg void OnSleepWakeupactionMakesound();
	afx_msg void OnUpdateSleepWakeupactionPopup(CCmdUI* pCmdUI);
	afx_msg void OnSleepWakeupactionPopup();
	afx_msg void OnUpdateSleepMinimizeonsleep(CCmdUI* pCmdUI);
	afx_msg void OnSleepMinimizeonsleep();
	afx_msg void OnTalkClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
};

/////////////////////////////////////////////////////////////////////////////
