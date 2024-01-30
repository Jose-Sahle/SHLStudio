/* **********************************************************************************
 * Arquivo: SHLChildScintillaSqlFrm.h												*
 *																					*
 * Classe de Frame do Document/View para hospedar a classe SHLQueryScnintillaView.  *
 *																					*
 * Data:01/06/2013																	*
 * Auto: José Sahle Netto															*
 ********************************************************************************** */
#pragma once

#include <afxsplitterwndex.h>
#include <afxMDIChildWndEx.h>
#include "stdafx.h"
#include "resource.h"       // main symbols

#include "SHLQueryScintillaSqlView.h"
#include "SHLQueryScintillaSqlDoc.h"
#include "SHLTabbedResultView.h"

#include "OleDBGenericConnection.h"
#include "OleDBGenericCommand.h"
#include "OleDBGenericTransaction.h"

typedef enum _shltargetresult
{
	 SHLTARGETRESULT_NONE = 0
	,SHLTARGETRESULT_GRID = 1
	,SHLTARGETRESULT_TEXT = 2
} SHLTARGETRESULT;


typedef enum _shleditorstatementtype
{
	 SHLEDITORSTATEMENTTYPE_COMMANDS = 1
	,SHLEDITORSTATEMENTTYPE_FUNCTIONS = 2
	,SHLEDITORSTATEMENTTYPE_SPECIAL_FUNCTIONS = 3
	,SHLEDITORSTATEMENTTYPE_DATA_TYPE = 4
	,SHLEDITORSTATEMENTTYPE_DATABASE_ELEMENTS = 5
	,SHLEDITORSTATEMENTTYPE_OPERATORS = 6
} SHLEDITORSTATEMENTTYPE;

class CSHLChildScintillaSqlFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSHLChildScintillaSqlFrame)

	friend HRESULT ExecuteSQLThread(CSHLChildScintillaSqlFrame *queryFrame);

public:
	CSHLChildScintillaSqlFrame();

// Attributes
protected:
	CSplitterWndEx m_wndSplitter;


public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
public:
	virtual ~CSHLChildScintillaSqlFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	afx_msg void OnInTextResult();
	afx_msg void OnUpdateInTextResult(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseConnect();
	afx_msg void OnUpdateDatabaseConnect(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseReconnect();
	afx_msg void OnUpdateDatabaseReconnect(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseDisconnect();
	afx_msg void OnUpdateDatabaseDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateComboDatabase(CCmdUI* pCmdUI);

	afx_msg LRESULT OnDropDownDatabase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetEditorFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetDataConnectoin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnExecuteQuery(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInvalidateView(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFillGrid(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnShowHideSplitter(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetPercentPane(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewQuery(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnExecuteQuery();
	afx_msg void OnUpdateExecuteQuery(CCmdUI* pCmdUI);
	afx_msg void OnStopExecutingQuery();
	afx_msg void OnUpdateStopExecutingQuery(CCmdUI* pCmdUI);
	afx_msg void OnShowHideSplitterCmd();

	afx_msg void OnTargetResultGrid();
	afx_msg void OnUpdateTargetResultGrid(CCmdUI* pCmdUI);
	afx_msg void OnTargetResultText();
	afx_msg void OnUpdateTargetResultText(CCmdUI* pCmdUI);
	afx_msg void OnKeepTabResult();
	afx_msg void OnUpdateKeepTabResult(CCmdUI* pCmdUI);
	afx_msg void OnNewQuery();
	afx_msg void OnUpdateNewQuery(CCmdUI* pCmdUI);
	afx_msg void OnOpenQuery();
	afx_msg void OnUpdateOpenQuery(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

protected:
	bool						m_bFirstSplitter;
	bool						m_bHideSplitter;

	HACCEL						m_hAccel;
	INT							m_ExecutingQuery;
	bool						m_CancelQuery;

	CString						m_strSQL;

	CSHLTabbedResultView*		m_lpResultView;
	CSHLQueryScintillaSqlView*	m_lpQueryView;

	CQueryDataConnectionEntity	m_dataconnection;

	HANDLE						m_hThreadStarter;
	DWORD						m_dwThreadStarter;

	BOOL						m_bCanCancel;
	BOOL						m_bStopQuery;
	UINT						m_nTimerID;

	BOOL						m_offline;

	DOUBLE						m_cy2;

	BOOL						m_bresizesplitter;

	SHLTARGETRESULT				m_targetResult;

	BOOL						m_keepingtabresults;

	BOOL						m_intextresult;

	BOOL						m_First;

	BOOL						m_DroppingList;

public:
	TCHAR GetSQLQuery(int pos);
	void ClearQuery();

private:
	void NewQuery();
	void OpenQuery();
	void ExecuteSQLQuery();
	void FillGrid(SHLOleDBReader*	reader, TCHAR* szQuery);
	void ResizeSplitters();
	void LoadStatements(CStringArray& arStatments, SHLEDITORSTATEMENTTYPE statementType, INT);
	void SetEditorFilters(INT IDBanco);
	void DatabaseConnect();
	void DatabaseReconnect();
	void DatabaseDisconnect();
	CString GetConnectionStringSHLStudio();
	CString GetDatabaseSelectQueries(ULONG IDBanco);
	ULONG GetIDBanco(CString dbmsname);
	void SetDatabaseProperties(ULONG IDBanco);
	void  DropDownDatabase();
	BOOL UpdateComboDatabase();
	void ChangeDatabase();
};
