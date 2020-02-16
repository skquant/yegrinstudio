# Microsoft Developer Studio Project File - Name="YegrinStudio" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=YegrinStudio - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "YegrinStudio.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "YegrinStudio.mak" CFG="YegrinStudio - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "YegrinStudio - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "YegrinStudio - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "YegrinStudio - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "YegrinStudio - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "YegrinStudio - Win32 Release"
# Name "YegrinStudio - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AuxiliairyAddinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\CCheckSK.cpp
# End Source File
# Begin Source File

SOURCE=.\CommThread.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolButton.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashAddinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupSyncAddinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\InformationAddinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MatrixStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryAddinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Transparent.cpp
# End Source File
# Begin Source File

SOURCE=.\UpperAddinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\YegrinStudio.cpp
# End Source File
# Begin Source File

SOURCE=.\YegrinStudio.rc
# End Source File
# Begin Source File

SOURCE=.\YegrinStudioDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AuxiliairyAddinDialog.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\CCheckSK.h
# End Source File
# Begin Source File

SOURCE=.\CommThread.h
# End Source File
# Begin Source File

SOURCE=.\CoolButton.h
# End Source File
# Begin Source File

SOURCE=.\FlashAddinDialog.h
# End Source File
# Begin Source File

SOURCE=.\GroupSyncAddinDialog.h
# End Source File
# Begin Source File

SOURCE=.\ImageDialog.h
# End Source File
# Begin Source File

SOURCE=.\InformationAddinDialog.h
# End Source File
# Begin Source File

SOURCE=.\MatrixStatic.h
# End Source File
# Begin Source File

SOURCE=.\MemoryAddinDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetupDialog.h
# End Source File
# Begin Source File

SOURCE=.\StaticEx.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Transparent.h
# End Source File
# Begin Source File

SOURCE=.\UpperAddinDialog.h
# End Source File
# Begin Source File

SOURCE=.\XTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\YegrinStudio.h
# End Source File
# Begin Source File

SOURCE=.\YegrinStudioDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\YegrinResource\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bitmap_f.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00021.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00022.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_cha.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_hol.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_sam.ico
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\matrixsetblue.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\matrixsetsmallblue.bmp
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\matrixsettinyblue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minus_ic.ico
# End Source File
# Begin Source File

SOURCE=.\YegrinResource\yegrin_background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\YegrinStudio.ico
# End Source File
# Begin Source File

SOURCE=.\res\YegrinStudio.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
