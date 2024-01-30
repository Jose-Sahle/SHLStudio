/* @doc
 * @module ReplaceDlg.cpp | Implementation of a modeless search/replace dialog for use with the scintilla edit control
 */
//

#include "stdafx.h"
#include "ReplaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
// @mfunc constructor
// @rvalue void | not used
//
CReplaceDlg::CReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplaceDlg)
	m_bMatchcase = FALSE;
	m_bMatchregex = FALSE;
	m_bMatchwords = FALSE;
	m_bSelection = FALSE;
	//}}AFX_DATA_INIT
	m_bForwardSearch = TRUE;
}
/////////////////////////////////////
// @mfunc set/get data to/from controls in dialog
// @rvalue void | not used
//
void CReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceDlg)
	DDX_Control(pDX, IDC_SEARCHTEXT, m_ctrlSearchtext);
	DDX_Control(pDX, IDC_REPLACETEXT, m_ctrlReplacetext);
	DDX_Check(pDX, IDC_MATCHCASE, m_bMatchcase);
	DDX_Check(pDX, IDC_MATCHREGEX, m_bMatchregex);
	DDX_Check(pDX, IDC_MATCHWORDS, m_bMatchwords);
	DDX_Check(pDX, IDC_MATCHSELECTION, m_bSelection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceDlg, CDialog)
	//{{AFX_MSG_MAP(CReplaceDlg)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_REPLACE, OnReplace)
	ON_BN_CLICKED(IDC_REPLACEALL, OnReplaceall)
	ON_BN_CLICKED(IDC_MATCHSELECTION, OnMatchselection)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////
// @mfunc Last mesage called - delete myself because this dialog is modeless
// @rvalue void | not used
//
void CReplaceDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if (m_pEditor)
		m_pEditor->ReplaceDialog = NULL;

	delete this;
}
/////////////////////////////////////
// @mfunc init dialog members
// @rvalue void | not used
//
BOOL CReplaceDlg::InitDialog()
{

	if (m_pEditor != NULL)
	{
		m_ctrlSearchtext.ResetContent();

		int i;
		for (i = m_pEditor->Findstrings.GetSize() - 1; i >= 0; i--)
		{
			m_ctrlSearchtext.AddString(m_pEditor->Findstrings.GetAt(i));
		}
		m_ctrlReplacetext.ResetContent();

		for (i = m_pEditor->Replacestrings.GetSize() - 1; i >= 0; i--)
		{
			m_ctrlReplacetext.AddString(m_pEditor->Replacestrings.GetAt(i));
		}

		CString strFind = m_pEditor->GetCtrl().GetSelText();
		if (strFind.FindOneOf(_T("\r\n")) < 0)
		{
			m_ctrlSearchtext.SetWindowText(strFind);
			m_ctrlReplacetext.SetWindowText(strFind);
		}
	}

	m_ctrlSearchtext.SetFocus();

	return TRUE;
}
/////////////////////////////////////
// @mfunc store new searchstring to global array of searchstrings. Never store one twice.
// @rvalue void | not used
//
void CReplaceDlg::StoreSearchString(LPCTSTR szSearch)  //@parm text to store
{
	//    try to find string in old stringlist
	for (int i = 0; i < m_pEditor->Findstrings.GetSize(); i++)
	{
		if (_tcscmp(m_pEditor->Findstrings.GetAt(i), szSearch) == 0)
			return;
	}
	//    if we get here no match was found and we add the new string
	m_pEditor->Findstrings.Add(szSearch);
	m_ctrlSearchtext.InsertString(0, szSearch);
}
/////////////////////////////////////
// @mfunc store new searchstring to global array of searchstrings. Never store one twice.
// @rvalue void | not used
//
void CReplaceDlg::StoreReplaceString(LPCTSTR szReplace) //@parm text to store
{

	for (int i = 0; i < m_pEditor->Replacestrings.GetSize(); i++)
	{
		if (_tcscmp(m_pEditor->Replacestrings.GetAt(i), szReplace) == 0)
			return;
	}

	m_pEditor->Replacestrings.Add(szReplace);
	m_ctrlReplacetext.InsertString(0, szReplace);
}
/////////////////////////////////////
// @mfunc goto next occurance of searchstring
// @rvalue void | not used
//
void CReplaceDlg::OnNext()
{
	m_bForwardSearch = TRUE;
	UpdateData();

	CString strFind;
	m_ctrlSearchtext.GetWindowText(strFind);

	if (m_pEditor != NULL)
	{
		if (!m_bSelection)
		{
			StoreSearchString(strFind);

			if (!m_pEditor->FindText(strFind, TRUE, m_bMatchcase, m_bMatchcase, m_bMatchregex))
				m_pEditor->TextNotFound(strFind, TRUE, m_bMatchcase, m_bMatchcase, m_bMatchregex, FALSE);
		}
	}
}
/////////////////////////////////////
// @mfunc goto previous occurance of searchstring
// @rvalue void | not used
//
void CReplaceDlg::OnPrev()
{
	m_bForwardSearch = FALSE;
	UpdateData();

	if (m_pEditor != NULL)
	{
		CString strFind;
		m_ctrlSearchtext.GetWindowText(strFind);
		StoreSearchString(strFind);

		if (!m_pEditor->FindText(strFind, FALSE, m_bMatchcase, m_bMatchcase, m_bMatchregex))
			m_pEditor->TextNotFound(strFind, FALSE, m_bMatchcase, m_bMatchcase, m_bMatchregex, FALSE);
	}
}
/////////////////////////////////////
// @mfunc replace current searchstring
// @rvalue void | not used
//
void CReplaceDlg::OnReplace()
{
	ReplaceNext();
}

void CReplaceDlg::ReplaceNext()
{
	UpdateData(TRUE);

	if (m_pEditor != NULL)
	{
		CString strFind;
		m_ctrlSearchtext.GetWindowText(strFind);

		CString strReplace;
		m_ctrlReplacetext.GetWindowText(strReplace);

		m_pEditor->ReplaceAllSel(strFind, strReplace, TRUE, m_bMatchcase, m_bMatchwords, m_bMatchregex);
	}
}

void CReplaceDlg::ReplacePrevious()
{
	UpdateData(TRUE);

	if (m_pEditor != NULL)
	{
		CString strFind;
		m_ctrlSearchtext.GetWindowText(strFind);

		CString strReplace;
		m_ctrlReplacetext.GetWindowText(strReplace);

		m_pEditor->ReplaceAllSel(strFind, strReplace, FALSE, m_bMatchcase, m_bMatchwords, m_bMatchregex);
	}
}

/////////////////////////////////////
// @mfunc replace all occurences of the search string
// @rvalue void | not used
//
void CReplaceDlg::OnReplaceall()
{
	UpdateData(TRUE);

	if (m_pEditor != NULL)
	{
		CString strFind;
		m_ctrlSearchtext.GetWindowText(strFind);

		CString strReplace;
		m_ctrlReplacetext.GetWindowText(strReplace);

		m_pEditor->ReplaceAll(strFind, strReplace, m_bMatchcase, m_bMatchwords, m_bMatchregex);

		StoreSearchString(strFind);
		StoreReplaceString(strReplace);
	}
}

/////////////////////////////////////
// @mfunc Handle "selection only" state - disable/enable some controls
// @rvalue void | not used
//
void CReplaceDlg::OnMatchselection()
{
	UpdateData();
	// if we should operate on the selection disable next/prev/replace - only replace all works now
	if (m_bSelection)
	{
		CWnd *pWnd = GetDlgItem(IDC_NEXT);
		if (pWnd != NULL)
			pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem(IDC_PREV);
		if (pWnd != NULL)
			pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem(IDC_REPLACE);
		if (pWnd != NULL)
			pWnd->EnableWindow(FALSE);
	}
	else
	{
		CWnd *pWnd = GetDlgItem(IDC_NEXT);

		if (pWnd != NULL)
			pWnd->EnableWindow(TRUE);

		pWnd = GetDlgItem(IDC_PREV);

		if (pWnd != NULL)
			pWnd->EnableWindow(TRUE);

		pWnd = GetDlgItem(IDC_REPLACE);

		if (pWnd != NULL)
			pWnd->EnableWindow(TRUE);
	}
}


int CReplaceDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
