# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Install - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Install - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "T42 - Win32 Debug" && "$(CFG)" != "T42 - Win32 Pure" &&\
 "$(CFG)" != "T42 - Win32 Static" && "$(CFG)" != "Install - Win32 Debug" &&\
 "$(CFG)" != "Install - Win32 Pure" && "$(CFG)" != "Install - Win32 Static" &&\
 "$(CFG)" != "Install - Win32 Canned"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "T42.mak" CFG="Install - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "T42 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "T42 - Win32 Pure" (based on "Win32 (x86) Application")
!MESSAGE "T42 - Win32 Static" (based on "Win32 (x86) Application")
!MESSAGE "Install - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Install - Win32 Pure" (based on "Win32 (x86) Application")
!MESSAGE "Install - Win32 Static" (based on "Win32 (x86) Application")
!MESSAGE "Install - Win32 Canned" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Install - Win32 Canned"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "T42 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
TargetName=T42
# End Custom Macros

ALL : "$(OUTDIR)\T42.exe" "$(OUTDIR)\T42.ex_" "$(OUTDIR)\T42.hlp"\
 "$(OUTDIR)\T42.cnt" "$(OUTDIR)\T42.hl_" "$(OUTDIR)\T42.cn_"

CLEAN : 
	-@erase "$(INTDIR)\CalleeDlg.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\FontsPage.obj"
	-@erase "$(INTDIR)\GeneralPage.obj"
	-@erase "$(INTDIR)\RegEx.obj"
	-@erase "$(INTDIR)\SecretaryPage.obj"
	-@erase "$(INTDIR)\SoundsPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\T42.cn_"
	-@erase "$(INTDIR)\T42.cnt"
	-@erase "$(INTDIR)\T42.hl_"
	-@erase "$(INTDIR)\T42.hlp"
	-@erase "$(INTDIR)\T42.obj"
	-@erase "$(INTDIR)\T42.pch"
	-@erase "$(INTDIR)\T42.res"
	-@erase "$(INTDIR)\T42AnnounceDlg.obj"
	-@erase "$(INTDIR)\T42Dlg.obj"
	-@erase "$(INTDIR)\T42Document.obj"
	-@erase "$(INTDIR)\T42Frame.obj"
	-@erase "$(INTDIR)\T42Secretary.obj"
	-@erase "$(INTDIR)\T42View.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\T42.ex_"
	-@erase "$(OUTDIR)\T42.exe"
	-@erase "$(OUTDIR)\T42.ilk"
	-@erase "$(OUTDIR)\T42.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/T42.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/T42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/T42.pdb" /debug /machine:I386 /out:"$(OUTDIR)/T42.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CalleeDlg.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\FontsPage.obj" \
	"$(INTDIR)\GeneralPage.obj" \
	"$(INTDIR)\RegEx.obj" \
	"$(INTDIR)\SecretaryPage.obj" \
	"$(INTDIR)\SoundsPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\T42.obj" \
	"$(INTDIR)\T42.res" \
	"$(INTDIR)\T42AnnounceDlg.obj" \
	"$(INTDIR)\T42Dlg.obj" \
	"$(INTDIR)\T42Document.obj" \
	"$(INTDIR)\T42Frame.obj" \
	"$(INTDIR)\T42Secretary.obj" \
	"$(INTDIR)\T42View.obj"

"$(OUTDIR)\T42.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Debug
TargetName=T42
InputPath=.\Debug\T42.exe
SOURCE=$(InputPath)

"$(OutDir)\$(TargetName).ex_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   compress $(OutDir)\$(TargetName).exe $(OutDir)\$(TargetName).ex_

# End Custom Build

!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "T42___Wi"
# PROP BASE Intermediate_Dir "T42___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEASE"
# PROP Intermediate_Dir "RELEASE"
# PROP Target_Dir ""
OUTDIR=.\RELEASE
INTDIR=.\RELEASE
# Begin Custom Macros
OutDir=.\RELEASE
TargetName=T42
# End Custom Macros

ALL : "$(OUTDIR)\T42.exe" "$(OUTDIR)\T42.ex_" "$(OUTDIR)\T42.hlp"\
 "$(OUTDIR)\T42.cnt" "$(OUTDIR)\T42.hl_" "$(OUTDIR)\T42.cn_"

CLEAN : 
	-@erase "$(INTDIR)\CalleeDlg.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\FontsPage.obj"
	-@erase "$(INTDIR)\GeneralPage.obj"
	-@erase "$(INTDIR)\RegEx.obj"
	-@erase "$(INTDIR)\SecretaryPage.obj"
	-@erase "$(INTDIR)\SoundsPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\T42.cn_"
	-@erase "$(INTDIR)\T42.cnt"
	-@erase "$(INTDIR)\T42.hl_"
	-@erase "$(INTDIR)\T42.hlp"
	-@erase "$(INTDIR)\T42.obj"
	-@erase "$(INTDIR)\T42.pch"
	-@erase "$(INTDIR)\T42.res"
	-@erase "$(INTDIR)\T42AnnounceDlg.obj"
	-@erase "$(INTDIR)\T42Dlg.obj"
	-@erase "$(INTDIR)\T42Document.obj"
	-@erase "$(INTDIR)\T42Frame.obj"
	-@erase "$(INTDIR)\T42Secretary.obj"
	-@erase "$(INTDIR)\T42View.obj"
	-@erase "$(OUTDIR)\T42.ex_"
	-@erase "$(OUTDIR)\T42.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RELEASE/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/T42.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/T42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/T42.pdb" /machine:I386 /out:"$(OUTDIR)/T42.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CalleeDlg.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\FontsPage.obj" \
	"$(INTDIR)\GeneralPage.obj" \
	"$(INTDIR)\RegEx.obj" \
	"$(INTDIR)\SecretaryPage.obj" \
	"$(INTDIR)\SoundsPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\T42.obj" \
	"$(INTDIR)\T42.res" \
	"$(INTDIR)\T42AnnounceDlg.obj" \
	"$(INTDIR)\T42Dlg.obj" \
	"$(INTDIR)\T42Document.obj" \
	"$(INTDIR)\T42Frame.obj" \
	"$(INTDIR)\T42Secretary.obj" \
	"$(INTDIR)\T42View.obj"

"$(OUTDIR)\T42.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\RELEASE
TargetName=T42
InputPath=.\RELEASE\T42.exe
SOURCE=$(InputPath)

"$(OutDir)\$(TargetName).ex_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   compress $(OutDir)\$(TargetName).exe $(OutDir)\$(TargetName).ex_

# End Custom Build

!ELSEIF  "$(CFG)" == "T42 - Win32 Static"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "T42___W0"
# PROP BASE Intermediate_Dir "T42___W0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RELEAST"
# PROP Intermediate_Dir "RELEAST"
# PROP Target_Dir ""
OUTDIR=.\RELEAST
INTDIR=.\RELEAST
# Begin Custom Macros
OutDir=.\RELEAST
TargetName=T42
# End Custom Macros

ALL : "$(OUTDIR)\T42.exe" "$(OUTDIR)\T42.ex_" "$(OUTDIR)\T42.hlp"\
 "$(OUTDIR)\T42.cnt" "$(OUTDIR)\T42.hl_" "$(OUTDIR)\T42.cn_"

CLEAN : 
	-@erase "$(INTDIR)\CalleeDlg.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\FontsPage.obj"
	-@erase "$(INTDIR)\GeneralPage.obj"
	-@erase "$(INTDIR)\RegEx.obj"
	-@erase "$(INTDIR)\SecretaryPage.obj"
	-@erase "$(INTDIR)\SoundsPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\T42.cn_"
	-@erase "$(INTDIR)\T42.cnt"
	-@erase "$(INTDIR)\T42.hl_"
	-@erase "$(INTDIR)\T42.hlp"
	-@erase "$(INTDIR)\T42.obj"
	-@erase "$(INTDIR)\T42.pch"
	-@erase "$(INTDIR)\T42.res"
	-@erase "$(INTDIR)\T42AnnounceDlg.obj"
	-@erase "$(INTDIR)\T42Dlg.obj"
	-@erase "$(INTDIR)\T42Document.obj"
	-@erase "$(INTDIR)\T42Frame.obj"
	-@erase "$(INTDIR)\T42Secretary.obj"
	-@erase "$(INTDIR)\T42View.obj"
	-@erase "$(OUTDIR)\T42.ex_"
	-@erase "$(OUTDIR)\T42.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RELEAST/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/T42.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/T42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/T42.pdb" /machine:I386 /out:"$(OUTDIR)/T42.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CalleeDlg.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\FontsPage.obj" \
	"$(INTDIR)\GeneralPage.obj" \
	"$(INTDIR)\RegEx.obj" \
	"$(INTDIR)\SecretaryPage.obj" \
	"$(INTDIR)\SoundsPage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\T42.obj" \
	"$(INTDIR)\T42.res" \
	"$(INTDIR)\T42AnnounceDlg.obj" \
	"$(INTDIR)\T42Dlg.obj" \
	"$(INTDIR)\T42Document.obj" \
	"$(INTDIR)\T42Frame.obj" \
	"$(INTDIR)\T42Secretary.obj" \
	"$(INTDIR)\T42View.obj"

"$(OUTDIR)\T42.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\RELEAST
TargetName=T42
InputPath=.\RELEAST\T42.exe
SOURCE=$(InputPath)

"$(OutDir)\$(TargetName).ex_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   compress $(OutDir)\$(TargetName).exe $(OutDir)\$(TargetName).ex_

# End Custom Build

!ELSEIF  "$(CFG)" == "Install - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Install\Debug"
# PROP BASE Intermediate_Dir "Install\Debug"
# PROP BASE Target_Dir "Install"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Install\Debug"
# PROP Intermediate_Dir "Install\Debug"
# PROP Target_Dir "Install"
OUTDIR=.\Install\Debug
INTDIR=.\Install\Debug

ALL : "T42 - Win32 Debug" "$(OUTDIR)\Install.exe"

CLEAN : 
	-@erase "$(INTDIR)\install.obj"
	-@erase "$(INTDIR)\Install.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Install.exe"
	-@erase "$(OUTDIR)\Install.ilk"
	-@erase "$(OUTDIR)\Install.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Install.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Install\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Install.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Install.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=version.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Install.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Install.exe" 
LINK32_OBJS= \
	"$(INTDIR)\install.obj" \
	"$(INTDIR)\Install.res"

"$(OUTDIR)\Install.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Install - Win32 Pure"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Install\Pure"
# PROP BASE Intermediate_Dir "Install\Pure"
# PROP BASE Target_Dir "Install"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Install\Pure"
# PROP Intermediate_Dir "Install\Pure"
# PROP Target_Dir "Install"
OUTDIR=.\Install\Pure
INTDIR=.\Install\Pure

ALL : "T42 - Win32 Pure" "$(OUTDIR)\Install.exe"

CLEAN : 
	-@erase "$(INTDIR)\install.obj"
	-@erase "$(INTDIR)\Install.res"
	-@erase "$(OUTDIR)\Install.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Install.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Install\Pure/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Install.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Install.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Install.pdb" /machine:I386 /out:"$(OUTDIR)/Install.exe" 
LINK32_OBJS= \
	"$(INTDIR)\install.obj" \
	"$(INTDIR)\Install.res"

"$(OUTDIR)\Install.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Install - Win32 Static"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Install\Static"
# PROP BASE Intermediate_Dir "Install\Static"
# PROP BASE Target_Dir "Install"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Install\Static"
# PROP Intermediate_Dir "Install\Static"
# PROP Target_Dir "Install"
OUTDIR=.\Install\Static
INTDIR=.\Install\Static

ALL : "T42 - Win32 Static" "$(OUTDIR)\Install.exe"

CLEAN : 
	-@erase "$(INTDIR)\install.obj"
	-@erase "$(INTDIR)\Install.res"
	-@erase "$(OUTDIR)\Install.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "STATI_K" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "STATI_K" /Fp"$(INTDIR)/Install.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Install\Static/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "STATI_K"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Install.res" /d "NDEBUG" /d "STATI_K" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Install.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Install.pdb" /machine:I386 /out:"$(OUTDIR)/Install.exe" 
LINK32_OBJS= \
	"$(INTDIR)\install.obj" \
	"$(INTDIR)\Install.res"

"$(OUTDIR)\Install.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Install - Win32 Canned"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Install\Canned"
# PROP BASE Intermediate_Dir "Install\Canned"
# PROP BASE Target_Dir "Install"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Install\Canned"
# PROP Intermediate_Dir "Install\Canned"
# PROP Target_Dir "Install"
OUTDIR=.\Install\Canned
INTDIR=.\Install\Canned

ALL : "$(OUTDIR)\Install.exe"

CLEAN : 
	-@erase "$(INTDIR)\install.obj"
	-@erase "$(INTDIR)\Install.res"
	-@erase "$(OUTDIR)\Install.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "K_ANNED" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "K_ANNED" /Fp"$(INTDIR)/Install.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Install\Canned/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "K_ANNED"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Install.res" /d "NDEBUG" /d "K_ANNED" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Install.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Install.pdb" /machine:I386 /out:"$(OUTDIR)/Install.exe" 
LINK32_OBJS= \
	"$(INTDIR)\install.obj" \
	"$(INTDIR)\Install.res"

"$(OUTDIR)\Install.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "T42 - Win32 Debug"
# Name "T42 - Win32 Pure"
# Name "T42 - Win32 Static"

!IF  "$(CFG)" == "T42 - Win32 Debug"

!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"

!ELSEIF  "$(CFG)" == "T42 - Win32 Static"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\T42.cpp

!IF  "$(CFG)" == "T42 - Win32 Debug"

DEP_CPP_T42_C=\
	".\ColorButton.h"\
	".\FontsPage.h"\
	".\GeneralPage.h"\
	".\SecretaryPage.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\SoundsPage.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Dlg.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42View.h"\
	".\talkd.h"\
	

"$(INTDIR)\T42.obj" : $(SOURCE) $(DEP_CPP_T42_C) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"

DEP_CPP_T42_C=\
	".\ColorButton.h"\
	".\FontsPage.h"\
	".\GeneralPage.h"\
	".\SecretaryPage.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\SoundsPage.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Dlg.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42View.h"\
	".\talkd.h"\
	

"$(INTDIR)\T42.obj" : $(SOURCE) $(DEP_CPP_T42_C) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"

DEP_CPP_T42_C=\
	".\ColorButton.h"\
	".\FontsPage.h"\
	".\GeneralPage.h"\
	".\SecretaryPage.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\SoundsPage.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Dlg.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42View.h"\
	".\talkd.h"\
	

"$(INTDIR)\T42.obj" : $(SOURCE) $(DEP_CPP_T42_C) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42Dlg.cpp
DEP_CPP_T42DL=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42AnnounceDlg.h"\
	".\T42CallLog.h"\
	".\T42Dlg.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42Secretary.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42Dlg.obj" : $(SOURCE) $(DEP_CPP_T42DL) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42Dlg.obj" : $(SOURCE) $(DEP_CPP_T42DL) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42Dlg.obj" : $(SOURCE) $(DEP_CPP_T42DL) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\T42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\T42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "T42 - Win32 Static"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/T42.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\T42.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42.rc
DEP_RSC_T42_R=\
	".\res\fullcup.ico"\
	".\res\idr_flip.ico"\
	".\res\idr_full.ico"\
	".\res\idr_t42f.ico"\
	".\res\T42-Beep.wav"\
	".\res\T42-Boiling.wav"\
	".\res\T42-Whistle.wav"\
	".\res\T42.ico"\
	".\res\T42.rc2"\
	".\res\t42calln.ico"\
	".\res\t42callp.ico"\
	".\shared-data\browse-icon.ico"\
	".\shared-data\klever-background.bmp"\
	".\shared-data\play-icon.ico"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42.res" : $(SOURCE) $(DEP_RSC_T42_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42.res" : $(SOURCE) $(DEP_RSC_T42_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42.res" : $(SOURCE) $(DEP_RSC_T42_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\help\T42.hpj

!IF  "$(CFG)" == "T42 - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=T42
InputPath=.\help\T42.hpj

BuildCmds= \
	"$(ProjDir)\makehelp.bat" \
	compress $(OutDir)\$(TargetName).hlp $(OutDir)\$(TargetName).hl_ \
	compress $(OutDir)\$(TargetName).cnt $(OutDir)\$(TargetName).cn_ \
	

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).hl_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).cn_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"

# Begin Custom Build - Making help file...
OutDir=.\RELEASE
ProjDir=.
TargetName=T42
InputPath=.\help\T42.hpj

BuildCmds= \
	"$(ProjDir)\makehelp.bat" \
	compress $(OutDir)\$(TargetName).hlp $(OutDir)\$(TargetName).hl_ \
	compress $(OutDir)\$(TargetName).cnt $(OutDir)\$(TargetName).cn_ \
	

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).hl_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).cn_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "T42 - Win32 Static"

# Begin Custom Build - Making help file...
OutDir=.\RELEAST
ProjDir=.
TargetName=T42
InputPath=.\help\T42.hpj

BuildCmds= \
	"$(ProjDir)\makehelp.bat" \
	compress $(OutDir)\$(TargetName).hlp $(OutDir)\$(TargetName).hl_ \
	compress $(OutDir)\$(TargetName).cnt $(OutDir)\$(TargetName).cn_ \
	

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).hl_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(TargetName).cn_" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42Frame.cpp
DEP_CPP_T42FR=\
	".\CalleeDlg.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\RegEx.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42View.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42Frame.obj" : $(SOURCE) $(DEP_CPP_T42FR) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42Frame.obj" : $(SOURCE) $(DEP_CPP_T42FR) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42Frame.obj" : $(SOURCE) $(DEP_CPP_T42FR) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42View.cpp
DEP_CPP_T42VI=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Frame.h"\
	".\T42View.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42View.obj" : $(SOURCE) $(DEP_CPP_T42VI) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42View.obj" : $(SOURCE) $(DEP_CPP_T42VI) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42View.obj" : $(SOURCE) $(DEP_CPP_T42VI) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CalleeDlg.cpp
DEP_CPP_CALLE=\
	".\CalleeDlg.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\CalleeDlg.obj" : $(SOURCE) $(DEP_CPP_CALLE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\CalleeDlg.obj" : $(SOURCE) $(DEP_CPP_CALLE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\CalleeDlg.obj" : $(SOURCE) $(DEP_CPP_CALLE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42Document.cpp
DEP_CPP_T42DO=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42View.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42Document.obj" : $(SOURCE) $(DEP_CPP_T42DO) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42Document.obj" : $(SOURCE) $(DEP_CPP_T42DO) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42Document.obj" : $(SOURCE) $(DEP_CPP_T42DO) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42AnnounceDlg.cpp
DEP_CPP_T42AN=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42AnnounceDlg.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42AnnounceDlg.obj" : $(SOURCE) $(DEP_CPP_T42AN) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42AnnounceDlg.obj" : $(SOURCE) $(DEP_CPP_T42AN) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42AnnounceDlg.obj" : $(SOURCE) $(DEP_CPP_T42AN) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SoundsPage.cpp
DEP_CPP_SOUND=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\SoundsPage.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\SoundsPage.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\SoundsPage.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\SoundsPage.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FontsPage.cpp
DEP_CPP_FONTS=\
	".\ColorButton.h"\
	".\FontsPage.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\FontsPage.obj" : $(SOURCE) $(DEP_CPP_FONTS) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\FontsPage.obj" : $(SOURCE) $(DEP_CPP_FONTS) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\FontsPage.obj" : $(SOURCE) $(DEP_CPP_FONTS) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorButton.cpp
DEP_CPP_COLOR=\
	".\ColorButton.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\ColorButton.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\ColorButton.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\ColorButton.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SecretaryPage.cpp
DEP_CPP_SECRE=\
	".\SecretaryPage.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\SecretaryPage.obj" : $(SOURCE) $(DEP_CPP_SECRE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\SecretaryPage.obj" : $(SOURCE) $(DEP_CPP_SECRE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\SecretaryPage.obj" : $(SOURCE) $(DEP_CPP_SECRE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\T42Secretary.cpp
DEP_CPP_T42SE=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\T42Document.h"\
	".\T42Frame.h"\
	".\T42Secretary.h"\
	".\T42View.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\T42Secretary.obj" : $(SOURCE) $(DEP_CPP_T42SE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\T42Secretary.obj" : $(SOURCE) $(DEP_CPP_T42SE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\T42Secretary.obj" : $(SOURCE) $(DEP_CPP_T42SE) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeneralPage.cpp
DEP_CPP_GENER=\
	".\GeneralPage.h"\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"


"$(INTDIR)\GeneralPage.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"


"$(INTDIR)\GeneralPage.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"


"$(INTDIR)\GeneralPage.obj" : $(SOURCE) $(DEP_CPP_GENER) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\shared-code\RegEx.cpp"
DEP_CPP_REGEX=\
	".\shared-code\BitSet.h"\
	".\shared-code\BTreendex.h"\
	".\shared-code\Dynamide.h"\
	".\shared-code\FindIFace.h"\
	".\shared-code\kHelpers.h"\
	".\shared-code\LRUCache.h"\
	".\shared-code\RegEx.h"\
	".\shared-code\SNMPeer.h"\
	".\shared-code\SNMPExtDll.h"\
	".\shared-code\SNMPOIDs.h"\
	".\stdafx.h"\
	".\T42CallLog.h"\
	".\talkd.h"\
	

!IF  "$(CFG)" == "T42 - Win32 Debug"

# ADD CPP /Yu"../stdafx.h"

"$(INTDIR)\RegEx.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"
   $(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yu"../stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "T42 - Win32 Pure"

# ADD CPP /Yu"../stdafx.h"

"$(INTDIR)\RegEx.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yu"../stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "T42 - Win32 Static"

# ADD CPP /Yu"../stdafx.h"

"$(INTDIR)\RegEx.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\T42.pch"
   $(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/T42.pch" /Yu"../stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "Install - Win32 Debug"
# Name "Install - Win32 Pure"
# Name "Install - Win32 Static"
# Name "Install - Win32 Canned"

!IF  "$(CFG)" == "Install - Win32 Debug"

!ELSEIF  "$(CFG)" == "Install - Win32 Pure"

!ELSEIF  "$(CFG)" == "Install - Win32 Static"

!ELSEIF  "$(CFG)" == "Install - Win32 Canned"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Install\Install.rc
DEP_RSC_INSTA=\
	".\Install\Custom.rch"\
	".\shared-data\install-icon.ico"\
	

!IF  "$(CFG)" == "Install - Win32 Debug"


"$(INTDIR)\Install.res" : $(SOURCE) $(DEP_RSC_INSTA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Install.res" /i "Install" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Install - Win32 Pure"


"$(INTDIR)\Install.res" : $(SOURCE) $(DEP_RSC_INSTA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Install.res" /i "Install" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Install - Win32 Static"


"$(INTDIR)\Install.res" : $(SOURCE) $(DEP_RSC_INSTA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Install.res" /i "Install" /d "NDEBUG" /d\
 "STATI_K" $(SOURCE)


!ELSEIF  "$(CFG)" == "Install - Win32 Canned"


"$(INTDIR)\Install.res" : $(SOURCE) $(DEP_RSC_INSTA) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Install.res" /i "Install" /d "NDEBUG" /d\
 "K_ANNED" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Install\install.cpp
DEP_CPP_INSTAL=\
	".\shared-code\install.h"\
	

!IF  "$(CFG)" == "Install - Win32 Debug"


"$(INTDIR)\install.obj" : $(SOURCE) $(DEP_CPP_INSTAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Install - Win32 Pure"


"$(INTDIR)\install.obj" : $(SOURCE) $(DEP_CPP_INSTAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Install - Win32 Static"


"$(INTDIR)\install.obj" : $(SOURCE) $(DEP_CPP_INSTAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Install - Win32 Canned"


"$(INTDIR)\install.obj" : $(SOURCE) $(DEP_CPP_INSTAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "T42"

!IF  "$(CFG)" == "Install - Win32 Debug"

"T42 - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\T42.mak" CFG="T42 - Win32 Debug" 

!ELSEIF  "$(CFG)" == "Install - Win32 Pure"

"T42 - Win32 Pure" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\T42.mak" CFG="T42 - Win32 Pure" 

!ELSEIF  "$(CFG)" == "Install - Win32 Static"

"T42 - Win32 Static" : 
   $(MAKE) /$(MAKEFLAGS) /F ".\T42.mak" CFG="T42 - Win32 Static" 

!ELSEIF  "$(CFG)" == "Install - Win32 Canned"

!ENDIF 

# End Project Dependency
# End Target
# End Project
################################################################################
