; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CT42Dlg
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "T42.h"

ClassCount=16
Class1=CT42App
Class2=CT42Dlg
Class3=CAboutDlg

ResourceCount=11
Resource1=IDD_OPTIONS_FONTS
Resource2=IDM_POPUPS
Resource3=IDD_OPTIONS_SOUNDS
Class4=T42Frame
Class5=CCalleeDlg
Resource4=IDD_T42VIEW
Resource5=IDD_OPTIONS_GENERAL
Class6=T42View
Class7=T42Document
Class8=CSplitBar
Class9=CLocalCtl
Class10=CRemoteCtl
Resource6=IDD_REMOTE
Class11=T42AnnounceDlg
Resource7=IDD_OPTIONS_SECRETARY
Resource8=IDD_T42_DIALOG
Class12=CSoundsPage
Resource9=IDD_ANNOUNCE
Class13=CFontsPage
Class14=CColorButton
Class15=CSecretaryPage
Resource10=IDD_ABOUTBOX
Class16=CGeneralPage
Resource11=IDR_T42FRAME

[CLS:CT42App]
Type=0
HeaderFile=T42.h
ImplementationFile=T42.cpp
Filter=N
LastObject=CT42App

[CLS:CT42Dlg]
Type=0
HeaderFile=T42Dlg.h
ImplementationFile=T42Dlg.cpp
Filter=W
LastObject=CT42Dlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=T42Dlg.h
ImplementationFile=T42Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_KLEVERNET

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342177283
Control5=IDOK,button,1342373889
Control6=IDC_KLEVERNET,button,1342242816

[DLG:IDD_T42_DIALOG]
Type=1
Class=CT42Dlg
ControlCount=12
Control1=IDC_STATIC,static,1342308353
Control2=IDC_ONCALL,combobox,1344339971
Control3=IDC_STATIC,static,1342308353
Control4=IDC_ONCALLAWAY,combobox,1344339971
Control5=IDC_CALLS,SysListView32,1350631425
Control6=IDC_PREVIEW,RICHEDIT,1344389508
Control7=IDC_TALK,button,1342242816
Control8=IDC_OPTIONS,button,1342242816
Control9=IDOK,button,1342242816
Control10=ID_HELP,button,1342242816
Control11=IDCANCEL,button,1073807361
Control12=IDC_AWAY,button,1342255107

[CLS:T42Frame]
Type=0
HeaderFile=T42Frame.h
ImplementationFile=T42Frame.cpp
BaseClass=CFrameWnd
Filter=W
LastObject=ID_CALLLOG_CALLBACK
VirtualFilter=fWC

[MNU:IDR_T42FRAME]
Type=1
Class=?
Command1=ID_TALK_REMOTEUSER
Command2=ID_TALK_ABORT
Command3=ID_TALK_RECONNECT
Command4=ID_TEA_SAVE
Command5=ID_TALK_CLOSE
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_SLEEP_SLEEP
Command9=ID_SLEEP_SLEEPONMINIMIZE
Command10=ID_SLEEP_MINIMIZEONSLEEP
Command11=ID_SLEEP_WAKEUPACTION_MAKESOUND
Command12=ID_SLEEP_WAKEUPACTION_POPUP
Command13=ID_WINDOW_SPLITEQUALLY
Command14=ID_WINDOW_SAVELAYOUT
Command15=ID_WINDOW_AUTOSAVELAYOUT
Command16=ID_WINDOW_HORIZONTALSPLIT
Command17=ID_WINDOW_VERTICALSPLIT
Command18=ID_WINDOW_HIDEINTRAYONMINIMIZE
CommandCount=18

[DLG:IDD_REMOTE]
Type=1
Class=CCalleeDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CALLEE,combobox,1344340034
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TTY,combobox,1344340034
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CALLER,combobox,1344340034
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[CLS:CCalleeDlg]
Type=0
HeaderFile=CalleeDlg.h
ImplementationFile=CalleeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCalleeDlg
VirtualFilter=dWC

[DLG:IDD_T42VIEW]
Type=1
Class=T42View
ControlCount=1
Control1=IDC_SPLIT,static,1342177547

[CLS:T42View]
Type=0
HeaderFile=T42View.h
ImplementationFile=T42View.cpp
BaseClass=CFormView
Filter=W
LastObject=ID_CALLLOG_CALLBACK
VirtualFilter=VWC

[CLS:T42Document]
Type=0
HeaderFile=T42Document.h
ImplementationFile=T42Document.cpp
BaseClass=CDocument
Filter=N
VirtualFilter=DC
LastObject=ID_WINDOW_AUTOSAVELAYOUT

[CLS:CSplitBar]
Type=0
HeaderFile=t42view.h
ImplementationFile=t42view.cpp
BaseClass=CStatic
Filter=W
LastObject=CSplitBar
VirtualFilter=WC

[CLS:CLocalCtl]
Type=0
HeaderFile=t42view.h
ImplementationFile=t42view.cpp
BaseClass=CRichTalkCtl
Filter=W
LastObject=CLocalCtl
VirtualFilter=WC

[CLS:CRemoteCtl]
Type=0
HeaderFile=t42view.h
ImplementationFile=t42view.cpp
BaseClass=CRichTalkCtl
Filter=W
LastObject=CRemoteCtl
VirtualFilter=WC

[ACL:IDR_T42FRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_SLEEP_SLEEP
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
CommandCount=5

[DLG:IDD_ANNOUNCE]
Type=1
Class=T42AnnounceDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_SECRETARY,button,1342251008
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CALLEE,static,1342308480
Control6=IDC_TTY,static,1342308354
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CALLER,static,1342308482
Control10=IDC_NOTHERE,button,1073741824
Control11=IDC_REFUSE,button,1073741824

[CLS:T42AnnounceDlg]
Type=0
HeaderFile=T42AnnounceDlg.h
ImplementationFile=T42AnnounceDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CALLEE
VirtualFilter=dWC

[MNU:IDM_POPUPS]
Type=1
Class=CT42Dlg
Command1=ID_TRAY_T42
Command2=ID_TRAY_AWAY
Command3=ID_TRAY_SHOWMAINWINDOW
Command4=ID_TRAY_OPTIONS
Command5=ID_TRAY_EXIT
Command6=ID_CALLLOG_CALLBACK
Command7=ID_CALLLOG_DELETE
Command8=ID_CALLLOG_SAVETOFILE
Command9=ID_CALLLOG_MARKASNEW
Command10=ID_CALLLOG_MARKASPROCESSED
Command11=ID_CALLLOG_EMPTYLOG
CommandCount=11

[DLG:IDD_OPTIONS_SOUNDS]
Type=1
Class=CSoundsPage
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_T42BELL,combobox,1344340290
Control3=IDC_T42BELL_BROWSE,button,1342246720
Control4=IDC_STATIC,static,1342177296
Control5=IDC_STATIC,static,1342308352
Control6=IDC_T42PROMPT,combobox,1344340290
Control7=IDC_T42PROMPT_BROWSE,button,1342246720
Control8=IDC_T42PROMPT_LOOP,button,1342242819
Control9=IDC_STATIC,static,1342177296
Control10=IDC_STATIC,static,1342308352
Control11=IDC_T42WAKE,combobox,1344340290
Control12=IDC_T42WAKE_BROWSE,button,1342246720
Control13=IDC_STATIC,static,1342177296
Control14=IDC_T42BELL_PLAY,button,1342246720
Control15=IDC_T42PROMPT_PLAY,button,1342246720
Control16=IDC_T42WAKE_PLAY,button,1342246720

[CLS:CSoundsPage]
Type=0
HeaderFile=SoundsPage.h
ImplementationFile=SoundsPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CSoundsPage

[DLG:IDD_OPTIONS_FONTS]
Type=1
Class=CFontsPage
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FORMATNAME,listbox,1352728833
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FACES,combobox,1344340227
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FONTSIZE,combobox,1344340034
Control7=IDC_BOLD,button,1342242819
Control8=IDC_ITALIC,button,1342242819
Control9=IDC_UNDERLINE,button,1342242819
Control10=IDC_STRIKEOUT,button,1342242819
Control11=IDC_CHARSET,combobox,1344340227
Control12=IDC_FORECOLOR,button,1342242827
Control13=IDC_BACKCOLOR,button,1342242827
Control14=IDC_SAMPLE,RICHEDIT,1476510084
Control15=IDC_STATIC,static,1342177296
Control16=IDC_TIP,static,1342308352

[CLS:CFontsPage]
Type=0
HeaderFile=FontsPage.h
ImplementationFile=FontsPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CFontsPage
VirtualFilter=idWC

[CLS:CColorButton]
Type=0
HeaderFile=ColorButton.h
ImplementationFile=ColorButton.cpp
BaseClass=CButton
Filter=W
LastObject=CColorButton
VirtualFilter=BWC

[DLG:IDD_OPTIONS_SECRETARY]
Type=1
Class=CSecretaryPage
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GREETING,edit,1352732868
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DOBYTELIMIT,button,1342242819
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BYTELIMIT,edit,1350639744
Control7=IDC_CHARSPIN,msctls_updown32,1342177463
Control8=IDC_DOTIMELIMIT,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_TIMELIMIT,edit,1350639744
Control11=IDC_TIMESPIN,msctls_updown32,1342177463
Control12=IDC_DOWINLIMIT,button,1342242819
Control13=IDC_STATIC,static,1342308352
Control14=IDC_WINLIMIT,edit,1350639744
Control15=IDC_WINSPIN,msctls_updown32,1342177463
Control16=IDC_STATIC,static,1342177296

[CLS:CSecretaryPage]
Type=0
HeaderFile=SecretaryPage.h
ImplementationFile=SecretaryPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CSecretaryPage
VirtualFilter=idWC

[DLG:IDD_OPTIONS_GENERAL]
Type=1
Class=CGeneralPage
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NTALKPORT,edit,1350631568
Control3=IDC_NTALKPORTSPIN,msctls_updown32,1342177332
Control4=IDC_STATIC,static,1342308352

[CLS:CGeneralPage]
Type=0
HeaderFile=GeneralPage.h
ImplementationFile=GeneralPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_NTALKPORTSPIN
VirtualFilter=idWC

