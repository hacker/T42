// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxrich.h>
#include <afxtempl.h>

#include <afxsock.h>		// MFC socket extensions

#pragma warning(disable: 4786) 

#include "shared-code/FindIFace.h"
#include "shared-code/kHelpers.h"
#include "shared-code/BTreendex.h"
#include "shared-code/BitSet.h"

#define	REFS2PTS	16

struct	osockaddr	{
	u_short	sa_family;	// Address family
	char	sa_data[14];// Up to 14 bytes of direct address

	osockaddr& operator=(sockaddr_in& src) { Copy(src); return *this; }
	void Copy(sockaddr_in& src) {
		sa_family = htons(src.sin_family);
		memmove(sa_data,((sockaddr*)&src)->sa_data,sizeof(((sockaddr*)&src)->sa_data));
	}
};

#include "talkd.h"

#include "T42CallLog.h"

enum	{
	WM_INITIATETALK  = WM_USER+16,
	WM_TARGETRESOLVED,
	WM_SOURCERESOLVED,
	WM_LOOKUP_SUCCESS, WM_LOOKUP_FAILURE,
	WM_ANNOUNCE_SUCCESS, WM_ANNOUNCE_FAILURE,
	WM_LEAVEINVITE_SUCCESS, WM_LEAVEINVITE_FAILURE,
	WM_LOCAL_REMOVE_SUCCESS, WM_LOCAL_REMOVE_FAILURE,
	WM_REMOTE_REMOVE_SUCCESS, WM_REMOTE_REMOVE_FAILURE,
	WM_TALKACCEPT,
	WM_CTLTRANSACT,
	WM_TALK,
	WM_TALKCHAR,
	WM_SPLITTERBDOWN,
	WM_TALKCONNECT,
	WM_NAMERESOLVED, WM_IPRESOLVED,

	WM_TRAYICON,
	WM_DAEMON,
	WM_UPDATEPREVIEW,

	timerTransact = 1,
	timerTimeout,
	timerMinutes
};
#include <MMSystem.h>
// CG: The following line was added by the Windows Multimedia component.
#pragma comment(lib, "winmm.lib")
