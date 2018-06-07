; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDrawArcDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "shpeditor.h"
LastPage=0
CDK=Y

ClassCount=23
Class1=CClipDlg
Class2=CCoordinate
Class3=CDistanceDlg
Class4=CDrawArcDlg
Class5=CEditorToolBar
Class6=CMenuButton
Class7=CFS_ModifyPolygon
Class8=CLayerManage
Class9=CMainFrame
Class10=CMapToolBar
Class11=CShpEditorApp
Class12=CAboutDlg
Class13=CShpEditorDoc
Class14=CShpEditorView
Class15=CSnapMethodDlg
Class16=CStarDlg
Class17=CTreeLayer

ResourceCount=22
Resource1=IDR_EDITOR
Resource2=IDR_MENU_SELECT
Resource3=IDD_ADD_FIELDS
Resource4=IDD_SNAPING
Resource5=IDD_DISTANCE
Resource6=IDD_FEATURE_PROPERTY
Resource7=IDD_MERGE_DLG
Resource8=IDR_MAP_TOOLS
Resource9=IDD_ABOUTBOX
Resource10=IDR_MENU_MODIFY_FEATURE
Resource11=IDR_LAYER_MENU
Resource12=IDD_SHPEDITOR_FORM
Resource13=IDR_MENU_DRAW_ARC
Resource14=IDR_MENU_DRAW_POLYGON
Resource15=IDD_DIALOG1
Resource16=IDR_MENU_EDITOR
Resource17=IDR_MENU_SKETCH
Resource18=IDD_COORDINATE
Class18=CFS_FieldsDlg
Resource19=IDD_WELLCOM_DLG
Class19=CFS_FeatureProperty
Class20=CFS_ListCtrl
Class21=CMergeDlg
Resource20=IDR_MAINFRAME
Class22=CFS_MergeDlg
Resource21=IDD_DRAW_ARC
Class23=CFS_SelectLabelDlg
Resource22=IDD_SELECT_LABEL

[CLS:CClipDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClipDlg.h
ImplementationFile=ClipDlg.cpp

[CLS:CCoordinate]
Type=0
BaseClass=CDialog
HeaderFile=Coordinate.h
ImplementationFile=Coordinate.cpp
Filter=D
VirtualFilter=dWC
LastObject=ID_FILE_SAVESHP

[CLS:CDistanceDlg]
Type=0
BaseClass=CDialog
HeaderFile=DistanceDlg.h
ImplementationFile=DistanceDlg.cpp

[CLS:CDrawArcDlg]
Type=0
BaseClass=CDialog
HeaderFile=DrawArcDlg.h
ImplementationFile=DrawArcDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BIG_ARC

[CLS:CEditorToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=EditorToolBar.h
ImplementationFile=EditorToolBar.cpp

[CLS:CMenuButton]
Type=0
BaseClass=CButton
HeaderFile=FS_MenuButton.h
ImplementationFile=MenuButton.cpp

[CLS:CFS_ModifyPolygon]
Type=0
BaseClass=CCmdTarget
HeaderFile=FS_ModifyPolygon1.h
ImplementationFile=FS_ModifyPolygon1.cpp
Filter=N
VirtualFilter=C
LastObject=ID_EDITOR_MODIFY_CANCEL

[CLS:CLayerManage]
Type=0
BaseClass=baseCMyBar
HeaderFile=LayerManage.h
ImplementationFile=LayerManage.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CMapToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=MapToolBar.h
ImplementationFile=MapToolBar.cpp

[CLS:CShpEditorApp]
Type=0
BaseClass=CWinApp
HeaderFile=ShpEditor.h
ImplementationFile=ShpEditor.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ShpEditor.cpp
ImplementationFile=ShpEditor.cpp
LastObject=CAboutDlg

[CLS:CShpEditorDoc]
Type=0
BaseClass=CDocument
HeaderFile=ShpEditorDoc.h
ImplementationFile=ShpEditorDoc.cpp

[CLS:CShpEditorView]
Type=0
BaseClass=CFormView
HeaderFile=ShpEditorView.h
ImplementationFile=ShpEditorView.cpp
LastObject=ID_LAYER_PROPERTY
Filter=D
VirtualFilter=VWC

[CLS:CSnapMethodDlg]
Type=0
BaseClass=CDialog
HeaderFile=SnapSketch.h
ImplementationFile=SnapSketch.cpp
LastObject=CSnapMethodDlg

[CLS:CStarDlg]
Type=0
BaseClass=CDialog
HeaderFile=StarDlg.h
ImplementationFile=StarDlg.cpp

[CLS:CTreeLayer]
Type=0
BaseClass=CTreeCtrl
HeaderFile=TreeLayer.h
ImplementationFile=TreeLayer.cpp
LastObject=CTreeLayer
Filter=W
VirtualFilter=GWC

[DLG:IDD_DIALOG1]
Type=1
Class=CClipDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DISTANCE,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342373897
Control7=IDC_RADIO2,button,1342242825

[DLG:IDD_COORDINATE]
Type=1
Class=CCoordinate
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_X,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_Y,edit,1350631552

[DLG:IDD_DISTANCE]
Type=1
Class=CDistanceDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DISTANCE,edit,1350631552

[DLG:IDD_DRAW_ARC]
Type=1
Class=CDrawArcDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FROM_X,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_FROM_Y,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_TO_X,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_TO_Y,edit,1350631552
Control13=IDC_STATIC,button,1342177287
Control14=IDC_RADIUS,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_CLOCKWISE,button,1342373897
Control17=IDC_CLOCKWISE2,button,1342242825
Control18=IDC_STATIC,button,1342308359
Control19=IDC_STATIC,button,1342308359
Control20=IDC_SMALL_ARC,button,1342373897
Control21=IDC_BIG_ARC,button,1342246665
Control22=IDC_STATIC,static,1342179342
Control23=IDC_STATIC,static,1342177294
Control24=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SHPEDITOR_FORM]
Type=1
Class=CShpEditorView
ControlCount=1
Control1=IDC_MAPCONTROL,{C552EA94-6FBB-11D5-A9C1-00104BB6FC1C},1342242816

[DLG:IDD_SNAPING]
Type=1
Class=CSnapMethodDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SNAP_POINT,button,1342242819
Control4=IDC_SNAP_LINE,button,1342242819
Control5=IDC_STATIC,button,1342177287

[DLG:IDD_WELLCOM_DLG]
Type=1
Class=CStarDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342177283

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEWSHP
Command2=ID_FILE_ADDSHP
Command3=ID_ADD_REFERENCE
Command4=ID_FILE_SAVESHP
Command5=ID_EDITOR_CUT
Command6=ID_EDITOR_COPY
Command7=ID_EDITOR_PASTE
Command8=ID_EDITOR_DELETE
Command9=ID_EDITOR_UNDO
Command10=ID_EDITOR_REDO
Command11=ID_EDITOR_VISIBLE
Command12=ID_LAYER_PROPERTY
CommandCount=12

[TB:IDR_EDITOR]
Type=1
Class=?
Command1=ID_EDITOR_MENU
Command2=ID_EDITOR_SELECT
Command3=ID_EDITOR_SNAPPING
Command4=ID_EDITOR_SKECTH_POLYGON
Command5=ID_EDITOR_SKETCH_ARC
Command6=ID_EDITOR_CUT_FEATURE
Command7=ID_EDITOR_DIVIDE
Command8=ID_EDITOR_MERGE
Command9=ID_EDITOR_CLIP
Command10=ID_EDITOR_BUFFER
Command11=ID_EDITOR_PROPERTY
Command12=ID_EDITOR_EXCHANGE_LAYER_INDEX
CommandCount=12

[TB:IDR_MAP_TOOLS]
Type=1
Class=?
Command1=ID_MAP_ZOOMIN
Command2=ID_MAP_ZOOMOUT
Command3=ID_MAP_PAN
Command4=ID_MAP_FULLEXTENT
Command5=ID_MAP_SELECT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEWSHP
Command2=ID_FILE_ADDSHP
Command3=ID_ADD_REFERENCE
Command4=ID_FILE_SAVESHP
Command5=ID_FILE_SAVESHP_AS
Command6=ID_APP_EXIT
Command7=ID_EDITOR_UNDO
Command8=ID_EDITOR_REDO
Command9=ID_EDITOR_CUT
Command10=ID_EDITOR_COPY
Command11=ID_EDITOR_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_TOOLS_VISIBLE
Command14=ID_EDITOR_VISIBLE
Command15=ID_VIEW_STATUS_BAR
Command16=ID_LAYER_MANAGE
Command17=ID_APP_ABOUT
CommandCount=17

[MNU:IDR_MENU_EDITOR]
Type=1
Class=?
Command1=ID_EDITOR_STAR
Command2=ID_EDITOR_STOP
Command3=ID_EDITOR_MOVE
Command4=ID_EDITOR_CUT_FEATURE
Command5=ID_EDITOR_CLIP
Command6=ID_EDITOR_DIVIDE
Command7=ID_EDITOR_BUFFER
Command8=ID_EDITOR_MERGE
Command9=ID_EDITOR_UNION
Command10=ID_EDITOR_INTERSECT
Command11=ID_EDITOR_CUT
Command12=ID_EDITOR_COPY
Command13=ID_EDITOR_PASTE
Command14=ID_EDITOR_DELETE
Command15=ID_EDITOR_SNAPPING
CommandCount=15

[MNU:IDR_LAYER_MENU]
Type=1
Class=?
Command1=ID_FILE_ADDSHP
Command2=ID_ADD_REFERENCE
Command3=ID_FILE_DELLAYER
Command4=ID_LAYER_SYMBOL
Command5=ID_LAYER_SHOW_LABEL
CommandCount=5

[MNU:IDR_MENU_DRAW_ARC]
Type=1
Class=?
Command1=ID_DRAW_COORDINATE
Command2=ID_DRAW_OFFSET
Command3=ID_DRAW_RADIUS
Command4=ID_DRAW_FINISH
Command5=ID_DRAW_DELETE_SKETCH
Command6=ID_DRAW_CONCEL_MENU
CommandCount=6

[MNU:IDR_MENU_DRAW_POLYGON]
Type=1
Class=?
Command1=ID_DRAW_COORDINATE
Command2=ID_DRAW_OFFSET
Command3=ID_DRAW_FINISH
Command4=ID_DRAW_DELETE_SKETCH
Command5=ID_DRAW_FINISH
CommandCount=5

[MNU:IDR_MENU_SKETCH]
Type=1
Class=?
Command1=ID_EDITOR_SKECTH_POLYGON
Command2=ID_EDITOR_SKETCH_ARC
CommandCount=2

[MNU:IDR_MENU_MODIFY_FEATURE]
Type=1
Class=?
Command1=ID_EDITOR_MODIFY_INSERT_VERTEX
Command2=ID_EDITOR_MODIFY_DELETE_VERTEX
Command3=ID_EDITOR_MODIFY_BACK
Command4=ID_EDITOR_MODIFY_CANCEL
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDITOR_COPY
Command2=ID_DRAW_DELETE_SKETCH
Command3=ID_FILE_NEWSHP
Command4=ID_DRAW_CONCEL_MENU
Command5=ID_FILE_SAVESHP
Command6=ID_EDITOR_PASTE
Command7=ID_EDITOR_DELETE
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_EDITOR_CUT
Command11=ID_EDITOR_UNDO
CommandCount=11

[MNU:IDR_MENU_SELECT]
Type=1
Class=?
Command1=ID_EDITOR_CUT
Command2=ID_EDITOR_COPY
Command3=ID_EDITOR_PASTE
Command4=ID_EDITOR_DELETE
Command5=ID_EDITOR_PROPERTY
CommandCount=5

[DLG:IDD_ADD_FIELDS]
Type=1
Class=CFS_FieldsDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FIELD,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_COMBO_FIELD_TYPE,combobox,1344340227
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUTTON_ADD,button,1342242816
Control9=IDC_LIST_FIELDS,SysListView32,1350631437
Control10=IDC_DLETE,button,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_MODIFY,button,1342242816

[CLS:CFS_FieldsDlg]
Type=0
HeaderFile=FS_FieldsDlg.h
ImplementationFile=FS_FieldsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFS_FieldsDlg

[DLG:IDD_FEATURE_PROPERTY]
Type=1
Class=CFS_FeatureProperty
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRID,MFCGridCtrl,1342242816
Control4=IDC_EXIT,button,1342242816

[CLS:CFS_FeatureProperty]
Type=0
HeaderFile=FS_FeatureProperty.h
ImplementationFile=FS_FeatureProperty.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CFS_ListCtrl]
Type=0
HeaderFile=FS_ListCtrl.h
ImplementationFile=FS_ListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CFS_ListCtrl

[CLS:CMergeDlg]
Type=0
HeaderFile=MergeDlg.h
ImplementationFile=MergeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_MERGE_DLG]
Type=1
Class=CFS_MergeDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,SysListView32,1350631437

[CLS:CFS_MergeDlg]
Type=0
HeaderFile=FS_MergeDlg.h
ImplementationFile=FS_MergeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFS_MergeDlg

[DLG:IDD_SELECT_LABEL]
Type=1
Class=CFS_SelectLabelDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTBOX,listbox,1352728835

[CLS:CFS_SelectLabelDlg]
Type=0
HeaderFile=FS_SelectLabelDlg.h
ImplementationFile=FS_SelectLabelDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFS_SelectLabelDlg

