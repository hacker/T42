// T42.h : main header file for the T42 application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CT42App:
// See T42.cpp for the implementation of this class
//

class CT42Dlg;
class CT42App : public CWinApp
{
public:
	void FlushT42CallsLog();
	CString m_HelpFile;
	UINT m_T42TalkPort;
	UINT m_T42LinesBusy;
	BOOL m_bAwayOnScreenSaver;
	BOOL UpdateT42Call(CT42CallLogEntry& entry);
	CT42Dlg* m_pT42Dlg;
	BOOL DelT42Call(CTime& time);
	BOOL AddT42Call(CT42CallLogEntry& entry);
	LONG m_nT42Calls;
	LONG GetT42Calls();
	BOOL GetT42Call(LONG call,CT42CallLogEntry& entry);
	LONG m_t42Call;
	BOOL CloseT42CallsLog();
	BOOL OpenT42CallsLog();
	CString m_t42CallsFile;
	CT42CallLog	m_T42Calls;
	CString	m_T42SGreeting;
	CTimeSpan m_T42STimeLimit;
	UINT m_T42SWinLimit;
	UINT m_T42SBytesLimit;
	COLORREF m_crT42LocalBG;
	COLORREF m_crT42RemoteBG;
	CHARFORMAT m_fmtT42System;
	CHARFORMAT m_fmtT42Remote;
	CHARFORMAT m_fmtT42Local;
	void Options(CWnd* pParent=NULL);
	void StopSound(LPCTSTR snd);
	BOOL StartSound(LPCTSTR  snd,BOOL bLoop = FALSE);
	void Initialize();
	CString m_sndTeapotWhistle;
	CString m_sndBoilingTeapot;
	CString m_sndTeaDrop;
	CString m_sndT42Wake;
	BOOL m_bT42PromptLoop;
	CString m_sndT42Prompt;
	CString m_sndT42Bell;
	BOOL m_bt42AutosaveLayout;
	UINT m_maxT42Callers;
	CStringList m_t42Callers;
	BOOL LastCaller(LPCTSTR caller);
	void LoadSettings();
	void SaveSettings();
	UINT m_maxT42Callees;
	BOOL LastCallee(LPCTSTR callee);
	CStringList m_t42Callees;
	CDocTemplate* m_pTemplate;
	CT42App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT42App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CT42App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
