/* @doc
 * @module FindDlg.cpp | Implementation of a modeless find dialog for use with the scintilla edit control
 */

#include "stdafx.h"
#include "FindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
// @mfunc constructor
// @rvalue void | not used
//
CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
	m_bMatchcase = FALSE;
	m_bMacthregex = FALSE;
	m_bMatchwords = FALSE;
	//}}AFX_DATA_INIT
}
/////////////////////////////////////
// @mfunc set/get data to/from controls in dialog
// @rvalue void | not used
//
void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
	DDX_Control(pDX, IDC_SEARCHTEXT, m_ctrlSearchtext);
	DDX_Check(pDX, IDC_MATCHCASE, m_bMatchcase);
	DDX_Check(pDX, IDC_MATCHREGEX, m_bMacthregex);
	DDX_Check(pDX, IDC_MATCHWORDS, m_bMatchwords);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFindDlg::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////
// @mfunc Last mesage called - delete myself because this dialog is modeless
// @rvalue void | not used
//
void CFindDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();

	if(m_pEditor)	
		m_pEditor->FindDialog = NULL;

   delete this;
}
/////////////////////////////////////
// @mfunc modeless handler for OK button - destroy myself and rely on PostNcDestroy to free memory
// @rvalue void | not used
//
void CFindDlg::OnOK() 
{
	DestroyWindow();
}
/////////////////////////////////////
// @mfunc init dialog members
// @rvalue void | not used
//
BOOL CFindDlg::InitDialog() 
{
// get app with old searchstrings
   
// set selected text to dropdown
	if (m_pEditor != NULL)
	{
		m_ctrlSearchtext.ResetContent();

		for (int i= m_pEditor->Findstrings.GetSize()-1;i>=0;i--)
		{
			m_ctrlSearchtext.AddString(m_pEditor->Findstrings.GetAt(i));
		}

		CString strFind = m_pEditor->GetCtrl().GetSelText();

		if (strFind.FindOneOf(_T("\r\n")) < 0)
			m_ctrlSearchtext.SetWindowText(strFind);
	}

	m_ctrlSearchtext.SetFocus();

	return TRUE;
}
/////////////////////////////////////
// @mfunc try to find string forward
// @rvalue void | not used
//
void CFindDlg::OnNext() 
{
	UpdateData();

	CString strFind;
	m_ctrlSearchtext.GetWindowText(strFind);

	if (m_pEditor != NULL)
	{
		StoreSearchString(strFind);

		if (!m_pEditor->FindText(strFind, TRUE, m_bMatchcase, m_bMatchcase, FALSE))
			m_pEditor->TextNotFound(strFind, TRUE, m_bMatchcase, m_bMatchcase, FALSE, FALSE);
	}
}
/////////////////////////////////////
// @mfunc try to find string backward
// @rvalue void | not used
//
void CFindDlg::OnPrev() 
{
	UpdateData();

	CString strFind;
	m_ctrlSearchtext.GetWindowText(strFind);

	if (m_pEditor != NULL)
	{
		StoreSearchString(strFind);

		if (!m_pEditor->FindText(strFind, FALSE, m_bMatchcase, m_bMatchcase, FALSE))
			m_pEditor->TextNotFound(strFind, TRUE, m_bMatchcase, m_bMatchcase, FALSE, FALSE);
	}
}
/////////////////////////////////////
// @mfunc store new searchstring to global array of searchstrings. Never store one twice.
// @rvalue void | not used
//
void CFindDlg::StoreSearchString(LPCTSTR szSearch)
{
//    try to find string in old stringlist
      for (int i=0; i < m_pEditor->Findstrings.GetSize();i++)
      {
         if (_tcscmp(m_pEditor->Findstrings.GetAt(i), szSearch) == 0)
            return;
      }

//    if we get here no match was found and we add the new string
      m_pEditor->Findstrings.Add(szSearch);
      m_ctrlSearchtext.InsertString(0, szSearch);
}


void CFindDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


int CFindDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
