/* **********************************************************************************
 * Arquivo: SHLChildScintillaFrm 												    *
 *																					*
 * Classe de Frame do Document/View para hospedar a classe SHLQueryScnintillaView.  *
 *																					*
 * Data:18/06/2013																	*
 * Auto: José Sahle Netto															*
 ********************************************************************************** */
#pragma once

#include <afxsplitterwndex.h>
#include <afxMDIChildWndEx.h>
#include "stdafx.h"
#include "resource.h"       // main symbols

#include "SHLQueryScintillaView.h"
#include "SHLQueryScintillaDoc.h"

#include "OleDBGenericConnection.h"
#include "OleDBGenericCommand.h"
#include "OleDBGenericTransaction.h"

typedef enum _shleditorstatementtype
{
	 SHLEDITORSTATEMENTTYPE_COMMANDS = 1
	,SHLEDITORSTATEMENTTYPE_FUNCTIONS = 2
	,SHLEDITORSTATEMENTTYPE_SPECIAL_FUNCTIONS = 3
	,SHLEDITORSTATEMENTTYPE_DATA_TYPE = 4
	,SHLEDITORSTATEMENTTYPE_DATABASE_ELEMENTS = 5
	,SHLEDITORSTATEMENTTYPE_OPERATORS = 6
} SHLEDITORSTATEMENTTYPE;

class CSHLChildScintillaFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSHLChildScintillaFrame)
public:
	CSHLChildScintillaFrame();

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
	virtual ~CSHLChildScintillaFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	LRESULT OnSetFilters(WPARAM wParam, LPARAM lParam);

	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

private:
	void SetFilters(WPARAM wParam, LPARAM lParam);

	void SetEditorFiltersCPP();
	void SetEditorFiltersSQL(INT IDBanco);
	void SetEditorFiltersXML();

	void LoadStatements(CStringArray& arStatments, SHLEDITORSTATEMENTTYPE statementType, INT IDBanco);
	CString GetConnectionStringSHLStudio();

private:
	HACCEL						m_hAccel;
};
	