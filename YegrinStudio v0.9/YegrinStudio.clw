; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CYegrinStudioDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "yegrinstudio.h"
LastPage=0

ClassCount=16
Class1=CAuxiliairyAddinDialog
Class2=CButtonST
Class3=CCheckSK
Class4=CCoolButton
Class5=CFlashAddinDialog
Class6=CGroupSyncAddinDialog
Class7=CImageDialog
Class8=CInformationAddinDialog
Class9=CMatrixStatic
Class10=CMemoryAddinDialog
Class11=CStaticEx
Class12=CUpperAddinDialog
Class13=CXTabCtrl
Class14=CYegrinStudioApp
Class15=CAboutDlg
Class16=CYegrinStudioDlg

ResourceCount=11
Resource1=IDD_LOWER_GROUP_SYNC_DIALOG
Resource2=IDD_UPPER_DIALOG
Resource3=IDD_SETUP_DIALOG
Resource4=IDD_LOWER_FLASH_DIALOG
Resource5=IDD_LOWER_MEMORY_DIALOG
Resource6=IDD_YEGRINSTUDIO_DIALOG
Resource7=IDD_LOWER_AUXILIARY_DIALOG
Resource8=IDD_DEBUG_DIALOG
Resource9=IDD_ABOUTBOX
Resource10=IDD_LOWER_INFORMATION_DIALOG
Resource11=IDR_MAIN_MENU

[CLS:CAuxiliairyAddinDialog]
Type=0
BaseClass=CDialog
HeaderFile=AuxiliairyAddinDialog.h
ImplementationFile=AuxiliairyAddinDialog.cpp

[CLS:CButtonST]
Type=0
BaseClass=CButton
HeaderFile=BtnST.h
ImplementationFile=BtnST.cpp

[CLS:CCheckSK]
Type=0
BaseClass=CButton
HeaderFile=CCheckSK.h
ImplementationFile=CCheckSK.cpp

[CLS:CCoolButton]
Type=0
BaseClass=CButton
HeaderFile=CoolButton.h
ImplementationFile=CoolButton.cpp
LastObject=ID_MENUITEM_CONNECT

[CLS:CFlashAddinDialog]
Type=0
BaseClass=CDialog
HeaderFile=FlashAddinDialog.h
ImplementationFile=FlashAddinDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=CFlashAddinDialog

[CLS:CGroupSyncAddinDialog]
Type=0
BaseClass=CDialog
HeaderFile=GroupSyncAddinDialog.h
ImplementationFile=GroupSyncAddinDialog.cpp

[CLS:CImageDialog]
Type=0
BaseClass=CDialog
HeaderFile=ImageDialog.h
ImplementationFile=ImageDialog.cpp

[CLS:CInformationAddinDialog]
Type=0
BaseClass=CDialog
HeaderFile=InformationAddinDialog.h
ImplementationFile=InformationAddinDialog.cpp

[CLS:CMatrixStatic]
Type=0
BaseClass=CStatic
HeaderFile=MatrixStatic.h
ImplementationFile=MatrixStatic.cpp

[CLS:CMemoryAddinDialog]
Type=0
BaseClass=CDialog
HeaderFile=MemoryAddinDialog.h
ImplementationFile=MemoryAddinDialog.cpp

[CLS:CStaticEx]
Type=0
BaseClass=CStatic
HeaderFile=StaticEx.h
ImplementationFile=StaticEx.cpp

[CLS:CUpperAddinDialog]
Type=0
BaseClass=CDialog
HeaderFile=UpperAddinDialog.h
ImplementationFile=UpperAddinDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_SPIN_DEVB2INFO

[CLS:CXTabCtrl]
Type=0
BaseClass=CTabCtrl
HeaderFile=XTabCtrl.h
ImplementationFile=XTabCtrl.cpp

[CLS:CYegrinStudioApp]
Type=0
BaseClass=CWinApp
HeaderFile=YegrinStudio.h
ImplementationFile=YegrinStudio.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=YegrinStudioDlg.cpp
ImplementationFile=YegrinStudioDlg.cpp
LastObject=CAboutDlg

[CLS:CYegrinStudioDlg]
Type=0
BaseClass=CImageDialog
HeaderFile=YegrinStudioDlg.h
ImplementationFile=YegrinStudioDlg.cpp
LastObject=CYegrinStudioDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_LOWER_AUXILIARY_DIALOG]
Type=1
Class=CAuxiliairyAddinDialog
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CHECK1,button,1342242819
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344340226
Control7=IDC_COMBO2,combobox,1344340226

[DLG:IDD_LOWER_FLASH_DIALOG]
Type=1
Class=CFlashAddinDialog
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_FLASH,edit,1350631552
Control3=IDC_SPIN_FLASH,msctls_updown32,1342177330
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_DELAY,edit,1350631552
Control6=IDC_SPIN_DELAY,msctls_updown32,1342177330
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUTTON1,button,1342242816
Control9=IDC_COMBO_BRACKETING,combobox,1344339970

[DLG:IDD_LOWER_FLASH_OPTION_DIALOG]
Type=1
Class=CFlashOptions

[DLG:IDD_LOWER_GROUP_SYNC_DIALOG]
Type=1
Class=CGroupSyncAddinDialog
ControlCount=3
Control1=IDC_CHECK1,button,1342242819
Control2=IDC_CHECK2,button,1342242819
Control3=IDC_CHECK3,button,1342242819

[DLG:IDD_LOWER_INFORMATION_DIALOG]
Type=1
Class=CInformationAddinDialog
ControlCount=1
Control1=IDC_EDIT1,edit,1342244992

[DLG:IDD_LOWER_MEMORY_DIALOG]
Type=1
Class=CMemoryAddinDialog
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352

[DLG:IDD_SETUP_DIALOG]
Type=1
Class=CSetupDialog
ControlCount=24
Control1=IDC_BTN_CONNECT,button,1208025088
Control2=IDC_COB_PORT,combobox,1344339970
Control3=IDC_COB_BAUD,combobox,1344339970
Control4=IDC_COB_DATA,combobox,1344339970
Control5=IDC_COB_PTY,combobox,1344339970
Control6=IDC_COB_STOP,combobox,1344339970
Control7=IDC_EDT_SENDDATA,edit,1350631552
Control8=IDC_BTN_SENDING,button,1342242816
Control9=IDC_BUTTON1,button,1342242816
Control10=IDC_BUTTON2,button,1342242816
Control11=IDC_EDT_RVCDATA,edit,1352730628
Control12=IDC_EDT_SENDHIS,edit,1352730628
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CMD_COMBO,combobox,1344340226
Control21=IDC_CHECK_HEXA,button,1342242819
Control22=IDOK,button,1342242816
Control23=IDC_READ_RADIO,button,1342308361
Control24=IDC_WRITE_RADIO,button,1342177289

[DLG:IDD_UPPER_DIALOG]
Type=1
Class=CUpperAddinDialog
ControlCount=46
Control1=IDC_MODL_BUTTON,button,1342242816
Control2=IDC_SOUND_BUTTON,button,1342242816
Control3=IDC_MODE_BUTTON,button,1342242816
Control4=IDC_HOLD_BUTTON,button,1342242816
Control5=IDC_UPPER_PLUS_BUTTON,button,1208025088
Control6=IDC_UPPWER_MINUS_BUTTON,button,1208025088
Control7=IDC_LOWER_PLUS_BUTTON,button,1208025088
Control8=IDC_LOWER_MINUS_BUTTON,button,1208025088
Control9=IDC_PCELL_BUTTON,button,1342242816
Control10=IDC_RF_BUTTON,button,1342242816
Control11=IDC_CHARGE_BUTTON,button,1342242816
Control12=IDC_TEST_BUTTON,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC_MODL1,static,1342177287
Control21=IDC_STATIC_MODL2,static,1342177287
Control22=IDC_STATIC_MODL3,static,1342177287
Control23=IDC_STATIC_MODL4,static,1342177287
Control24=IDC_STATIC_PCELL,static,1342177287
Control25=IDC_STATIC_RF,static,1342177287
Control26=IDC_STATIC_CHARGE1,static,1342177287
Control27=IDC_STATIC_SOUND,static,1342177287
Control28=IDC_STATIC_MODE,static,1342177287
Control29=IDC_STATIC_HOLD,static,1342177287
Control30=IDC_STATIC_CHARGE2,static,1342177287
Control31=IDC_STATIC_TEST,static,1342177287
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC_FUNCTIONS,static,1342177287
Control38=IDC_BUTTON_A,button,1342242816
Control39=IDC_BUTTON_B1,button,1342242816
Control40=IDC_BUTTON_B2,button,1342242816
Control41=IDC_STATIC_DEVAINFO,static,1350696960
Control42=IDC_STATIC_DEVB1INFO,static,1350696960
Control43=IDC_STATIC_DEVB2INFO,static,1350696960
Control44=IDC_SPIN_DEVAINFO,msctls_updown32,1342177314
Control45=IDC_SPIN_DEVB1INFO,msctls_updown32,1342177314
Control46=IDC_SPIN_DEVB2INFO,msctls_updown32,1342177314

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_YEGRINSTUDIO_DIALOG]
Type=1
Class=CYegrinStudioDlg
ControlCount=6
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_UPPER_TAB,SysTabControl32,1342177280
Control4=IDC_LOWER_TAB,SysTabControl32,1342177280
Control5=IDC_BUTTON_TEST,button,1342242816
Control6=IDC_EDIT_RCVTEST,edit,1352730628

[DLG:IDD_DEBUG_DIALOG]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DEBUG_EDIT,edit,1352730756

[MNU:IDR_MAIN_MENU]
Type=1
Class=?
Command1=ID_MENUITEM_CONNECT
Command2=ID_MENUITEM_EXTENSION
CommandCount=2

