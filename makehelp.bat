@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by T42.HPJ. >"help\T42.hm"
echo. >>"help\T42.hm"
echo // Commands (ID_* and IDM_*) >>"help\T42.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"help\T42.hm"
echo. >>"help\T42.hm"
echo // Prompts (IDP_*) >>"help\T42.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"help\T42.hm"
echo. >>"help\T42.hm"
echo // Resources (IDR_*) >>"help\T42.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"help\T42.hm"
echo. >>"help\T42.hm"
echo // Dialogs (IDD_*) >>"help\T42.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"help\T42.hm"
echo. >>"help\T42.hm"
echo // Frame Controls (IDW_*) >>"help\T42.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"help\T42.hm"
REM -- Make help for Project T42

echo Building RTF file
xsltproc -o help/T42.rtf shared-code/kinhelp.xsl help/T42.xml
echo Building Win32 Help files
start /wait hcrtf -x "help\T42.hpj"
echo.
if exist Debug\nul copy "help\T42.hlp" Debug
if exist Debug\nul copy "help\T42.cnt" Debug
if exist Release\nul copy "help\T42.hlp" Release
if exist Release\nul copy "help\T42.cnt" Release
if exist Releast\nul copy "help\T42.hlp" Releast
if exist Releast\nul copy "help\T42.cnt" Releast
echo.


