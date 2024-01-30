/* ***************************************************************************
 * Arquivo: SHLQueryScintillaDoc                                             *
 *                                                                           *
 * Classe que gerencia os documentos do SHLQueryScintillaView.               *
 * Este arquivo foi alterado para meu projeto, porém pego na internet.       *
 *                                                                           *
 * Data:18/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ScintillaDocView.h"
#include "QueryDataConnectionEntity.h"

#ifdef SCI_NAMESPACE
class CSHLQueryScintillaDoc : public Scintilla::CScintillaDoc
#else
class CSHLQueryScintillaDoc : public CScintillaDoc
#endif
{
protected: //create from serialization only
	CSHLQueryScintillaDoc();

	virtual BOOL CSHLQueryScintillaDoc::OnSaveDocument(LPCTSTR lpszPathName);

	afx_msg void OnFileSave();

	DECLARE_DYNCREATE(CSHLQueryScintillaDoc)

public:
	virtual ~CSHLQueryScintillaDoc();

	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetXMLScript();
	void SetCPPScript();

	void SetAccessScript();
	void SetSQLServerScript();
	void SetMySQLScript();
	void SetPostGresScript();
	void SetOracleScript();
	void SetFocus();
	void SetChild();

private:
	bool FileSave(bool bSaveAs);
	void SetSqlFilters();

private:
	bool m_bAutoSave;
	CMDIChildWnd* m_pChild;
};
