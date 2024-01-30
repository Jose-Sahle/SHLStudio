/* ***************************************************************************
 * Arquivo: SHLQueryScintillaView                                            *
 *                                                                           *
 * Classe que gerencia os documentos do SHLQueryScintillaView.               *
 * Este arquivo foi alterado para meu projeto, por�m pego na internet.       *
 *                                                                           *
 * Data:18/06/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ScintillaDocView.h"
#include "SHLQueryScintillaDoc.h"
#include "Property.h"

typedef enum _shlfindreplace
{
	 SHLFINDREPLACE_FIND = 1
	,SHLFINDREPLACE_REPLACE = 2
} SHLFINDREPLACE;

#ifdef SCI_NAMESPACE
class CSHLQueryScintillaView : public Scintilla::CScintillaView
#else
class CSHLQueryScintillaView : public CScintillaView
#endif
{
protected: //create from serialization only
	CSHLQueryScintillaView();
	virtual ~CSHLQueryScintillaView();

	DECLARE_DYNCREATE(CSHLQueryScintillaView)

//Attributes
public:
	CSHLQueryScintillaDoc* GetDocument();

	virtual void OnDraw(CDC* pDC);  //overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnOptionsAddDeletemarker();
	afx_msg void OnOptionsFindNextmarker();
	afx_msg void OnOptionsFindPrevmarker();
	afx_msg void OnOptionsFoldMargin();
	afx_msg void OnOptionsSelectionMargin();
	afx_msg void OnOptionsViewLinenumbers();

	afx_msg void OnFindDialog();
	afx_msg void OnReplaceDialog();
	afx_msg void OnFindReplaceNext();
	afx_msg void OnFindReplacePrevious();
	afx_msg void OnGotoPos();
	afx_msg void OnGotoLine();
	afx_msg void OnShowMacro();
	afx_msg void OnShowSintaxe();

#ifdef SCI_NAMESPACE
	virtual void OnCharAdded(Scintilla::SCNotification* pSCNotification);
	virtual void OnDwellStart(Scintilla::SCNotification* pSCNotification);
	virtual void OnDwellEnd(Scintilla::SCNotification* pSCNotification);
	virtual void OnModifyAttemptRO(Scintilla::SCNotification* pSCNotification);
#else
	virtual void OnCharAdded(SCNotification* pSCNotification);
	virtual void OnDwellStart(SCNotification* pSCNotification);
	virtual void OnDwellEnd(SCNotification* pSCNotification);
	virtual void OnModifyAttemptRO(SCNotification* pSCNotification);
#endif

	virtual void OnChange();

	void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(0xff, 0xff, 0xff), int size=-1, const char *face=0);
	void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);
	
protected:
	HACCEL	m_hAccel;
	bool	m_bAnswerOnChangeMessages;
	SHLFINDREPLACE	m_findReplace;

public:
	void SetStyleDocument(int lexer, CStringArray& arStyleCommands, CStringArray& arStyleFunctions, CStringArray& arStyleSpecialFunctions, CStringArray& arStyleDataType, CStringArray& arStyleDatabaseElements, CStringArray& arStyleOperators);
	CString GetSqlSentence();
	BOOL FindText(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
	void TextNotFound(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression, BOOL bReplaced);
	void ReplaceAll(_In_z_ LPCTSTR lpszFind, _In_z_ LPCTSTR lpszReplace, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);
	void ReplaceAllSel(_In_z_ LPCTSTR szFind, _In_z_ LPCTSTR szReplace, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression);

private:
	CString GetWords(CStringArray& arStyleStatements);

public:
	READONLY_PROPERTY(CStringArray&,  Findstrings)
  	GET(Findstrings) 
 	{ 
 		return m_strFindstrings; 
	}

	READONLY_PROPERTY(CStringArray&,  Replacestrings)
  	GET(Replacestrings) 
 	{ 
 		return m_strReplacestrings; 
	}

	PROPERTY(CDialog*,  FindDialog)
  	GET(FindDialog) 
 	{ 
 		return m_dlgFind; 
	}
  	SET(FindDialog) 
 	{ 
 		m_dlgFind = value; 
	}

	PROPERTY(CDialog*,  ReplaceDialog)
  	GET(ReplaceDialog) 
 	{ 
 		return m_dlgReplace; 
	}
  	SET(ReplaceDialog) 
 	{ 
 		m_dlgReplace = value; 
	}
private:
	CStringArray	m_strFindstrings;
	CStringArray	m_strReplacestrings;
	CDialog*		m_dlgFind;
	CDialog*		m_dlgReplace;

};

