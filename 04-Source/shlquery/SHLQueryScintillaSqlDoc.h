/* ***************************************************************************
 * Arquivo: SHLQueryScintillaSqlDoc                                          *
 *                                                                           *
 * Classe que gerencia os documentos do SHLQueryScintillaView.               *
 * Este arquivo foi alterado para meu projeto, porém pego na internet.       *
 *                                                                           *
 * Data:01/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ScintillaDocView.h"
#include "QueryDataConnectionEntity.h"

#ifdef SCI_NAMESPACE
class CSHLQueryScintillaSqlDoc : public Scintilla::CScintillaDoc
#else
class CSHLQueryScintillaSqlDoc : public CScintillaDoc
#endif
{
protected: //create from serialization only
	CSHLQueryScintillaSqlDoc();

	virtual BOOL CSHLQueryScintillaSqlDoc::OnSaveDocument(LPCTSTR lpszPathName);

	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();

	DECLARE_DYNCREATE(CSHLQueryScintillaSqlDoc)

public:
	virtual ~CSHLQueryScintillaSqlDoc();

	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	virtual void SetTitle(LPCTSTR lpszTitle);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
	void SetStyleDocument(int lexer, CQueryDataConnectionEntity* dataconnection, CString database);

	void OpenNewQuery();
	bool FileOpen();

private:
	bool FileSave(bool bSaveAs);

	bool CSHLQueryScintillaSqlDoc::Invalidate();

	void SetDataConnection(CQueryDataConnectionEntity* dataconnection, CString database);

private:
	bool m_bAutoSave;
	CString m_connectionstring;
	CString m_databaseidbanco;

};
