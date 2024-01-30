// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#include <SciLexer.h>
#include <path.h>

#define WM_INVALIDATE_VIEW		(WM_USER + 0x1001)
#define WM_SETFILTERS			(WM_USER + 0x1002)
#define WM_GET_VIEW				(WM_USER + 0x1003)
#define WM_SET_PROJECT_ITEM		(WM_USER + 0x1004)

#define WM_ADD_STRING_OUTPUT	(WM_USER + 0x1010)
#define WM_CLEAR_STRING_OUTPUT	(WM_USER + 0x1011)

#define ID_TREE_VIEW_TAB_SOLUTION       311
#define ID_TREE_VIEW_TAB_PROJECT        312
#define ID_TREE_VIEW_TAB_FOLDER         313
#define ID_TREE_VIEW_TAB_ITEM           314
#define ID_TREE_VIEW_TAB_DEPENDENCY     315

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>
#include <afxdlgs.h>

typedef CMap<CString, LPCTSTR, int, int&> MAPICONS;
typedef CMap<CString, LPCTSTR, CMultiDocTemplate*, CMultiDocTemplate*&> MULTIDOCTEMPLATELIST;
typedef CMap<CString, LPCTSTR, HMODULE, HMODULE&> LIBRARYLIST;
typedef CMap<CString, LPCTSTR, CString, LPCTSTR> PROPERTYVALUE;
