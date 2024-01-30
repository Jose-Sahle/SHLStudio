/* @doc
 * @module ReplaceDlg.h | definition of a modeless search/replace dialog for use with the scintilla edit control
 */
#ifndef __REPLACEDLG_H__
#define __REPLACEDLG_H__

#include "SHLQueryScintillaSqlView.h"
#include "Resource.h"
#include "Property.h"
////////////////////////////////////
// @class CReplaceDlg | Class of a modeless search/replace dialog for use with the scintilla edit control
// @base public | CDialog
//
class CReplaceDlg : public CDialog
{
public:
// @access public constructor
// @cmember empty Constructor
	CReplaceDlg(CWnd* pParent = NULL);

public:
// @access public data members
// @cmember init dialog
   virtual BOOL InitDialog();
// @cmember store new search string to global strings
   void StoreSearchString(LPCTSTR szSearch);
// @cmember store new search string to global strings
   void StoreReplaceString(LPCTSTR szReplace);

public:
// @access public data members
// @cmember a pointer to the scintilla edit control
	PROPERTY(CSHLQueryScintillaSqlView*, Editor)
  	GET(Editor) 
 	{ 
 		return m_pEditor; 
	}
 	SET(Editor)
 	{
 		m_pEditor = value;
 	} 
// @cmember a flag for the default serach direction
	BOOL          m_bForwardSearch; 

private:
// @access public data members
// @cmember a pointer to the scintilla edit control
	CSHLQueryScintillaSqlView* m_pEditor;   // editcontrol to use

public:
// Dialogfelddaten
	//{{AFX_DATA(CReplaceDlg)
	enum { IDD = IDD_REPLACE };
	CComboBox	m_ctrlSearchtext;
	CComboBox	m_ctrlReplacetext;
	BOOL	m_bMatchcase;
	BOOL	m_bMatchregex;
	BOOL	m_bMatchwords;
	BOOL	m_bSelection;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CReplaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CReplaceDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnReplaceall();
	afx_msg void OnMatchselection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnReplace();

	void ReplaceNext();
	void ReplacePrevious();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_REPLACEDLG_H__31BB518C_B58B_498E_A338_FC992EB24B75__INCLUDED_
