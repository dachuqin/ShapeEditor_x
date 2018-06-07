// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__224852E1_2C41_4B09_9BBF_23AF3CB1D3FA__INCLUDED_)
#define AFX_STDAFX_H__224852E1_2C41_4B09_9BBF_23AF3CB1D3FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define WM_CHANGE_STATE			WM_USER+5
#define WM_FEATURE_PROPERTY		WM_USER+6
#include ".\src\sizecbar.h"
#include ".\src\scbarg.h"
#include ".\src\scbarcf.h"
#define baseCMyBar CSizingControlBarCF

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include "D:\Program Files\ArcGIS\Include\CPPAPI\SDK_Windows.h"

#pragma warning(push)
#pragma warning(disable: 4192)
#pragma warning(disable: 4146)


#import "esriSystem.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")
#import "esriSystemUI.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids exclude("IProgressDialog")
#import "esriGeometry.olb" raw_interfaces_only raw_native_types no_namespace named_guids
#import "esriDisplay.olb" raw_interfaces_only raw_native_types no_namespace named_guids
#import "esriGeoDatabase.olb" raw_interfaces_only raw_native_types no_namespace named_guids
#import "esriCarto.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
#import "esriDataSourcesFile.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriDataSourcesGDB.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriCatalog.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriArcCatalog.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriCatalogUI.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriGeoDatabaseUI.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriArcMapUI.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriEditor.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
#import "esriEditorExt.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
#import "esriDisplay.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")
#import "esriDisplayUI.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, exclude("OLE_COLOR", "OLE_HANDLE")

#import "ToolbarControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids
#import "TOCControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids
#import "MapControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids
#import "PageLayoutControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids
#import "ArcReaderControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__224852E1_2C41_4B09_9BBF_23AF3CB1D3FA__INCLUDED_)
