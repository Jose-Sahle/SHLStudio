// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#define WM_EXECUTION_COMPLETE	(WM_USER + 0x1001)
#define WM_EXEC_PROC_COMPLETE	(WM_USER + 0x1002)
#define WM_CANCEL_COMPLETE		(WM_USER + 0x1003)
#define WM_GET_GRID_CTRL		(WM_USER + 0x1004)
#define WM_SET_GRID_ROWS		(WM_USER + 0x1005)
#define WM_SHOW_HIDE_SPLITTER	(WM_USER + 0x1006)
#define WM_EXECUTE_QUERY		(WM_USER + 0x1007)
#define WM_INVALIDATE_VIEW		(WM_USER + 0x1008)
#define WM_FILL_GRID			(WM_USER + 0x1009)
#define WM_SETDATACONNECTION	(WM_USER + 0x100A)
#define WM_SET_EDITOR_FOCUS		(WM_USER + 0x100B)
#define WM_SET_PERCENT_PANE		(WM_USER + 0x100C)
#define WM_NEW_QUERY			(WM_USER + 0x100D)
#define WM_FILL_COMBO_DATABASES	(WM_USER + 0x100E)
#define WM_GET_RIBBONBAR		(WM_USER + 0x100F)

#define ID_BUTTON_DATABASE_CONNECT      32802
#define ID_BUTTON_DATABASE_DISCONNECT   32803
#define ID_COMBO_SQL_DATABASES          32804
#define ID_BUTTON_SQL_EXECUTE           32805
#define ID_BUTTON_SQL_STOP              32806
#define ID_BUTTON_RESULT_GRID           32807
#define ID_BUTTON_RESULT_TEXT           32808
#define ID_BUTTON_NEW_QUERY             32810
#define ID_CHECK_KEEP_TAB_RESULT        32811
#define ID_CHECK_DDL_IN_TEXT_RESULT     32812
#define ID_BUTTON_DATABASE_RECONNECT    32814
#define ID_BUTTON_NEW_SOLUTION          32818
#define ID_BUTTON_OPEN_SCRIPT_FILE      32820
#define ID_BUTTON_OPEN_SOLUTION         32821

#define ID_SHL_USER   2000

#define ID_DATAGRIDVIEW				(ID_SHL_USER + 1)
#define ID_DATAGRIDVIEWPLACEHOLDER  (ID_SHL_USER + 2)

#include "targetver.h"

#include <SciLexer.h>
#include <path.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

//#ifndef _AFX_NO_DB_SUPPORT
//#include <afxdb.h>                      // MFC ODBC database classes
//#endif // _AFX_NO_DB_SUPPORT

//#ifndef _AFX_NO_DAO_SUPPORT
//#include <afxdao.h>                     // MFC DAO database classes
//#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>

