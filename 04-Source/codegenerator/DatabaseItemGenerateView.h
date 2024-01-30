/* ***************************************************************************
 * Arquivo: DatabaseItemGenerateView                                         *
 *                                                                           *
 * Classe utilizada para gerar o XML do Database                             *
 *                                                                           *
 * Data:21/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include "ProjectEntity.h"
#include "ItemEntity.h"

#include "ISHLOleDBConnection.h"
#include "SHLDataConnection.h"


#include "OleDBGenericConnection.h"
#include "OleDBGenericCommand.h"

#include "OleDBSqlServerConnection.h"
#include "OleDBSqlServerCommand.h"

#include "OleDBMySQLConnection.h"
#include "OleDBMySQLCommand.h"

#include "OleDBPostGreSQLConnection.h"
#include "OleDBPostGreSQLCommand.h"

#include "OleDBOracleConnection.h"
#include "OleDBOracleCommand.h"

#include "SHLOleDBParameter.h"
#include "SHLOleDBParameters.h"
#include "SHLOleDBReader.h"
#include "SHLOleDBTable.h"

class CDatabaseItemGenerateView : public CFormView
{
	DECLARE_DYNCREATE(CDatabaseItemGenerateView)

protected:
	CDatabaseItemGenerateView();           // protected constructor used by dynamic creation
	virtual ~CDatabaseItemGenerateView();

public:
	enum { IDD = IDD_DIALOG_DATABASE_GENERATE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();

	afx_msg void OnBnClickedButtonSelectAll();
	afx_msg void OnBnClickedButtonUnselectAll();
	afx_msg void OnCbnSelchangeComboDatabase();
	afx_msg LRESULT OnSetProjectItem(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonGenerateDatabaseFileXml();

	DECLARE_MESSAGE_MAP()

private:
	CComboBox m_cmbDatabase;
	CCheckListBox m_chklstTable;
	CRichEditCtrl m_txtInformation;

	CProjectEntity* m_pProject;
	CItemEntity* m_pItem;

	ISHLOleDBConnection* m_conn;

	CString m_databasequery;
	CString m_tablequery;
	CString m_columnquery;

	BOOL	m_noexecuteevents;

private:
	void InsertText(CString text, COLORREF color, bool bold, bool italic, INT size);
	void SetInfomartionText();
	void SetProjectItem(WPARAM wParam, LPARAM lParam);
	void SetQueries();
	void SetDatabaseCombo();
	void SetTableList(CString database);
	CString ReadFullFile(CString filename);

	SHLOleDBReader* SelectSqlServerDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype);
	SHLOleDBReader* SelectAccessDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype);
	SHLOleDBReader* SelectMySQLDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype);
	SHLOleDBReader* SelectPostGreSQLDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype);
	SHLOleDBReader* SelectOracleDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype);

	SHLOleDBReader* SelectSqlServer(CString database, CString tablename, CString query);
	SHLOleDBReader* SelectAccess(CString database, CString tablename, CString query);
	SHLOleDBReader* SelectMySQL(CString database, CString tablename, CString query);
	SHLOleDBReader* SelectPostGreSQL(CString database, CString tablename, CString query);
	SHLOleDBReader* SelectOracle(CString database, CString tablename, CString query);

	SHLOleDBReader* SelectFieldAccess(CString database, CString tablename, CString query);
	SHLOleDBReader* SelectField(CString databasename, CString tablename);

	void FillCombo(SHLOleDBReader* reader, CString database);
	void FillTable(SHLOleDBReader* reader);

	CString GetSHLOleDBType(SHLDBTYPE dbtype);

	void SetSelectAll(BOOL checkTo);

	void GenerateXML();
};


