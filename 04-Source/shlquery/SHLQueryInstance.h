/* ***************************************************************************
 * Arquivo: SHLQueryInstance                                                 *
 *                                                                           *
 * Classe que implementa ISHLQuery.                                          *
 *                                                                           *
 * Data:28/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ISHLQuery.h"
#include "OleDBGenericConnection.h"
#include "OleDBGenericCommand.h"
#include "OleDBGenericTransaction.h"
#include "SHLDataConnection.h"

class CSHLQueryInstance : public ISHLQuery
{
public:
	CSHLQueryInstance();
	virtual ~CSHLQueryInstance();

	//Document & View
	virtual bool LoadDocumentView(CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment);
	virtual bool SetDocument(CString documentname, CRuntimeClass*& docment);
	virtual bool SetStyleDocument(UINT lexer, CDocument* docment, CStringArray& arCommands);

	//Connections
	virtual bool FillTreeViewConnections(CViewTree& wndServerView, CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection);
	virtual void LoadSelectQueries(CQueryDataConnectionEntity* queryData);
	virtual bool ConnectionDatabaseServer(CViewTree& wndServerView, CQueryDataConnectionEntity* dataconnection);

	virtual bool ShowElements(CString SelectElement, CString databasename, CString tablename, CString columnName, CString columnNameFind, SHLDATACONNECTION nodeValue, INT imageIndex, CViewTree& wndServerView, HTREEITEM phItem, CQueryDataConnectionEntity* pDataConnection, bool bIfNotAdded);

	virtual bool ShowSystemTableColumns(CViewTree& wndServerView, HTREEITEM phItemSysTable, CString strDatabasename, CString strTablename, CQueryDataConnectionEntity* pDataConnection);
	virtual bool ShowUserTableColumns(CViewTree& wndServerView, HTREEITEM phItemUserTable, CString strDatabasename, CString strTablename, CQueryDataConnectionEntity* pDataConnection);

	virtual bool AddConnection(CViewTree& wndServerView, CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection, HTREEITEM& hNewItem);
	virtual bool SaveConnections(CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection);

	virtual void NewQuery(CQueryDataConnectionEntity* dataconnection, CDocument* pDoc, CString database);

	virtual CString GetLastError();

	/* Release this instance */
	virtual void Release();

private:
	CString m_error;
	HINSTANCE m_hSciDLL;
	COleDBGenericConnection m_conn;

private:
	void BuildSelectCommands(CString& commandSelectConnections, CString& commandSelectDatabaseQueries);
	bool CSHLQueryInstance::DeleteChildItemTreeView(CViewTree& wndServerView, HTREEITEM phItem);
	void LoadStatements(CStringArray& arStatements, CString statementType, CQueryDataConnectionEntity* dataconnection);
	ULONG GetIDBanco(CString dbmsname);
};