// T42View.h : header file
//

class T42View;
class T42Frame;
struct TalkEditChars;
class	CRichTalkCtl : public CRichEditCtrl	{
public:
	void SystemMessage(LPCTSTR str);
	TalkEditChars* m_pInTEC;
	TalkEditChars* m_pOuTEC;
	T42View* m_pView;
	COLORREF m_bgColor;
	CHARFORMAT m_fmtSystem;
	CHARFORMAT m_fmtUser;
	void SetColor();
	void Setup();
	void PutString(LPCTSTR str);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void PutCharacter(CHAR c);
};

/////////////////////////////////////////////////////////////////////////////
// CLocalCtl window

class CLocalCtl : public CRichTalkCtl
{
// Construction
public:
	CLocalCtl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalCtl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLocalCtl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLocalCtl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRemoteCtl window

class CRemoteCtl : public CRichTalkCtl
{
// Construction
public:
	CRemoteCtl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteCtl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRemoteCtl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRemoteCtl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSplitBar window

class CSplitBar : public CStatic
{
// Construction
public:
	CSplitBar();

// Attributes
public:
	int m_Ort;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplitBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// T42View form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class T42View : public CFormView
{
protected:
	T42View();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(T42View)

// Form Data
public:
	static DWORD CALLBACK ESINProc(DWORD dwCookie,LPBYTE pbBuff,LONG cb,LONG FAR *pcb);
	void SystemMessage(LPCTSTR str);
	void LoadLayout();
	void SaveLayout();
	void SetEnable(BOOL bEnable);
	BOOL m_bEnabled;
	HCURSOR m_hHorzCursor;
	HCURSOR m_hVertCursor;
	T42Frame* m_pFrame;
	BOOL m_bTracking;
	BOOL m_bShown;
	enum	_orientation	{
		ortHorizontal,
		ortVertical
	}	m_Ort;
	void RecalcLayout();
	UINT m_gapSize;
	UINT m_remoteSize;
	UINT m_localSize;
	CRemoteCtl m_remoteCtl;
	CLocalCtl m_localCtl;
	//{{AFX_DATA(T42View)
	enum { IDD = IDD_T42VIEW };
	CSplitBar	m_splitCtl;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T42View)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~T42View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(T42View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSplitterBDown(WPARAM,LPARAM);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnWindowSplitequally();
	afx_msg void OnUpdateWindowHorizontalsplit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowVerticalsplit(CCmdUI* pCmdUI);
	afx_msg void OnWindowHorizontalsplit();
	afx_msg void OnWindowVerticalsplit();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnCancelMode();
	afx_msg void OnUpdateTeaSave(CCmdUI* pCmdUI);
	afx_msg void OnTeaSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
