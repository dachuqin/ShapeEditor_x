# Microsoft Developer Studio Project File - Name="ShpEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ShpEditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ShpEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ShpEditor.mak" CFG="ShpEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ShpEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ShpEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ShpEditor - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ShpEditor - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ShpEditor - Win32 Release"
# Name "ShpEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BS_NewCircleArc.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\columnheader.cpp
# End Source File
# Begin Source File

SOURCE=.\columnheaders.cpp
# End Source File
# Begin Source File

SOURCE=.\Coordinate.cpp
# End Source File
# Begin Source File

SOURCE=.\DistanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawArcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_FeatureProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_FieldsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_MenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_MergeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_ModifyPolygon1.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_NewPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\FS_SelectLabelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=".\gridctrl_src\Experimental Upgrades\InPlaceList.cpp"
# End Source File
# Begin Source File

SOURCE=.\LayerManage.cpp
# End Source File
# Begin Source File

SOURCE=.\listitem.cpp
# End Source File
# Begin Source File

SOURCE=.\listitems.cpp
# End Source File
# Begin Source File

SOURCE=.\listsubitem.cpp
# End Source File
# Begin Source File

SOURCE=.\listsubitems.cpp
# End Source File
# Begin Source File

SOURCE=.\listview.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MaskedBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureDisp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\scbarcf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShpEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ShpEditor.rc
# End Source File
# Begin Source File

SOURCE=.\ShpEditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ShpEditorView.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapSketch.cpp
# End Source File
# Begin Source File

SOURCE=.\StarDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\toolbarcontroldefault.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeLayer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BS_NewCirCleArc.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\ClipDlg.h
# End Source File
# Begin Source File

SOURCE=.\columnheader.h
# End Source File
# Begin Source File

SOURCE=.\columnheaders.h
# End Source File
# Begin Source File

SOURCE=.\Coordinate.h
# End Source File
# Begin Source File

SOURCE=.\DistanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\DrawArcDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\FS_FeatureProperty.h
# End Source File
# Begin Source File

SOURCE=.\FS_FieldsDlg.h
# End Source File
# Begin Source File

SOURCE=.\FS_MenuButton.h
# End Source File
# Begin Source File

SOURCE=.\FS_MergeDlg.h
# End Source File
# Begin Source File

SOURCE=.\FS_ModifyPolygon1.h
# End Source File
# Begin Source File

SOURCE=.\FS_NewPolygon.h
# End Source File
# Begin Source File

SOURCE=.\FS_SelectLabelDlg.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridCell.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\INewCircleArc.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=".\gridctrl_src\Experimental Upgrades\InPlaceList.h"
# End Source File
# Begin Source File

SOURCE=.\LayerManage.h
# End Source File
# Begin Source File

SOURCE=.\listitem.h
# End Source File
# Begin Source File

SOURCE=.\listitems.h
# End Source File
# Begin Source File

SOURCE=.\listsubitem.h
# End Source File
# Begin Source File

SOURCE=.\listsubitems.h
# End Source File
# Begin Source File

SOURCE=.\listview.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapToolBar.h
# End Source File
# Begin Source File

SOURCE=.\MaskedBitmap.h
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\MenuButton.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PictureDisp.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\src\scbarcf.h
# End Source File
# Begin Source File

SOURCE=.\src\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\ShpEditor.h
# End Source File
# Begin Source File

SOURCE=.\ShpEditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\ShpEditorView.h
# End Source File
# Begin Source File

SOURCE=.\src\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\SnapSketch.h
# End Source File
# Begin Source File

SOURCE=.\StarDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=".\gridctrl_src\Experimental Upgrades\TitleTip.h"
# End Source File
# Begin Source File

SOURCE=.\gridctrl_src\TitleTip.h
# End Source File
# Begin Source File

SOURCE=.\toolbarcontroldefault.h
# End Source File
# Begin Source File

SOURCE=.\TreeLayer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Function Kit"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\res\ArcView_theme_properties.bmp
# End Source File
# Begin Source File

SOURCE=.\res\big_arc.ico
# End Source File
# Begin Source File

SOURCE=.\res\BigArc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigArc.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cross.bin
# End Source File
# Begin Source File

SOURCE=.\res\cur1.bin
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.bin
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\edit_tool.bin
# End Source File
# Begin Source File

SOURCE=.\res\edit_tool_move.bin
# End Source File
# Begin Source File

SOURCE=.\res\edit_vertex.bin
# End Source File
# Begin Source File

SOURCE=.\res\file_web.ico
# End Source File
# Begin Source File

SOURCE=.\res\folder_new.ico
# End Source File
# Begin Source File

SOURCE=.\res\GLOBE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\globe_6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_pol.ico
# End Source File
# Begin Source File

SOURCE=.\res\layers_2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Mac OS X Modern Icon 3.ico"
# End Source File
# Begin Source File

SOURCE=.\res\map_tool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Modify.bin
# End Source File
# Begin Source File

SOURCE=.\res\Move.bin
# End Source File
# Begin Source File

SOURCE=.\res\network.ico
# End Source File
# Begin Source File

SOURCE=.\res\Normal.bin
# End Source File
# Begin Source File

SOURCE=".\res\Paint App.ico"
# End Source File
# Begin Source File

SOURCE=.\res\pan_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pencil.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pencil2.ico
# End Source File
# Begin Source File

SOURCE=.\res\pointer_large.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pointer_with_selection.bmp
# End Source File
# Begin Source File

SOURCE=.\res\preferences.ico
# End Source File
# Begin Source File

SOURCE=.\res\save.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShpEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShpEditor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ShpEditorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\small_ar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallArc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallArc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UNDO.BMP
# End Source File
# Begin Source File

SOURCE=.\res\undo.ico
# End Source File
# Begin Source File

SOURCE=.\res\user_mov.bin
# End Source File
# Begin Source File

SOURCE=.\res\web_server.ico
# End Source File
# Begin Source File

SOURCE=".\res\zoom in.ico"
# End Source File
# Begin Source File

SOURCE=".\res\zoom out.ico"
# End Source File
# Begin Source File

SOURCE=.\res\zoom_in_tool_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zoom_out_tool_1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\十字加小圆圈.bin"
# End Source File
# Begin Source File

SOURCE=".\res\十字加小圆圈.cur"
# End Source File
# End Group
# Begin Group "Function Kit No. 1"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\FS_DataConvert.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ShpEditor : {BDD1F04E-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListItem
# 	2:10:HeaderFile:listitem.h
# 	2:8:ImplFile:listitem.cpp
# End Section
# Section ShpEditor : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section ShpEditor : {BDD1F051-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CColumnHeader
# 	2:10:HeaderFile:columnheader.h
# 	2:8:ImplFile:columnheader.cpp
# End Section
# Section ShpEditor : {BDD1F055-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListSubItem
# 	2:10:HeaderFile:listsubitem.h
# 	2:8:ImplFile:listsubitem.cpp
# End Section
# Section ShpEditor : {BDD1F050-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CColumnHeaders
# 	2:10:HeaderFile:columnheaders.h
# 	2:8:ImplFile:columnheaders.cpp
# End Section
# Section ShpEditor : {BDD1F04C-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListItems
# 	2:10:HeaderFile:listitems.h
# 	2:8:ImplFile:listitems.cpp
# End Section
# Section ShpEditor : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section ShpEditor : {D959783F-B033-4A0C-966B-DB90FE45BEE5}
# 	2:5:Class:CToolbarControlDefault
# 	2:10:HeaderFile:toolbarcontroldefault.h
# 	2:8:ImplFile:toolbarcontroldefault.cpp
# End Section
# Section ShpEditor : {BDD1F049-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListView1
# 	2:10:HeaderFile:listview.h
# 	2:8:ImplFile:listview.cpp
# End Section
# Section ShpEditor : {B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}
# 	2:21:DefaultSinkHeaderFile:toolbarcontroldefault.h
# 	2:16:DefaultSinkClass:CToolbarControlDefault
# End Section
# Section ShpEditor : {BDD1F04B-858B-11D1-B16A-00C0F0283628}
# 	2:21:DefaultSinkHeaderFile:listview.h
# 	2:16:DefaultSinkClass:CListView1
# End Section
# Section ShpEditor : {BDD1F053-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListSubItems
# 	2:10:HeaderFile:listsubitems.h
# 	2:8:ImplFile:listsubitems.cpp
# End Section
