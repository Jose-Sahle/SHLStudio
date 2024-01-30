/* ***************************************************************************
 * Arquivo: ISHLQuery                                                        *
 *                                                                           *
 * Classe abstrata para interfacear programas externos com esta DLL.         *
 *                                                                           *
 * Data:28/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>			
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include "ViewTree.h"
#include "QueryDataConnectionEntity.h"
#include "SHLTreeNode.h"
#include "ViewTree.h"
#include "SHLDataConnection.h"

#ifdef SHLQUERY_EXPORTS
	#define SHLQUERY_API __declspec(dllexport)
#else
	#define SHLQUERY_API __declspec(dllimport)
#endif

class ISHLQuery
{
public:
	virtual ~ISHLQuery() {};

	//Document & View
	virtual bool LoadDocumentView(CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment) = 0;
	virtual bool SetDocument(CString documentname, CRuntimeClass*& docment) = 0;
	virtual bool SetStyleDocument(UINT lexer, CDocument* docment, CStringArray& arCommands) = 0;

	//Connections
	virtual bool FillTreeViewConnections(CViewTree& wndServerView, CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection) = 0;
	virtual void LoadSelectQueries(CQueryDataConnectionEntity* queryData) = 0;
	virtual bool ConnectionDatabaseServer(CViewTree& wndServerView, CQueryDataConnectionEntity* dataconnection) = 0;

	virtual bool ShowElements(CString SelectElement, CString databasename, CString tablename, CString columnName, CString columnNameFind, SHLDATACONNECTION nodeValue, INT imageIndex, CViewTree& wndServerView, HTREEITEM phItem, CQueryDataConnectionEntity* pDataConnection, bool bIfNotAdded) = 0;

	virtual bool ShowSystemTableColumns(CViewTree& wndServerView, HTREEITEM phItemSysTable, CString strDatabasename, CString strTablename, CQueryDataConnectionEntity* pDataConnection) = 0;
	virtual bool ShowUserTableColumns(CViewTree& wndServerView, HTREEITEM phItemUserTable, CString strDatabasename, CString strTablename, CQueryDataConnectionEntity* pDataConnection) = 0;

	virtual bool AddConnection(CViewTree& wndServerView, CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection, HTREEITEM& hNewItem) = 0;
	virtual bool SaveConnections(CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection) = 0;

	virtual void NewQuery(CQueryDataConnectionEntity* dataconnection, CDocument* pDoc, CString database) = 0;

	virtual CString GetLastError() = 0;

	/* Release this instance */
	virtual void Release() = 0;

};

typedef ISHLQuery*	SHLQUERYHANDLE;

#ifdef __cplusplus
#   define EXTERN_C     extern "C"
#else
#   define EXTERN_C
#endif // __cplusplus

EXTERN_C SHLQUERY_API SHLQUERYHANDLE WINAPI GetSHLQueryInstance();

#ifndef SHLQUERY_EXPORTS
	#include "AutoClosePtr.h"
	typedef AutoClosePtr<ISHLQuery, void, &ISHLQuery::Release> ISHLQueryPtr;
	typedef SHLQUERYHANDLE(WINAPI* LPFNGETSHLQUERYINSTANCE)();
#endif
