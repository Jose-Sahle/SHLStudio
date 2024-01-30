// GotoLineDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "GotoLineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CGotoLineDlg 


CGotoLineDlg::CGotoLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoLineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoLineDlg)
	m_nLine = 0;
	//}}AFX_DATA_INIT
}


void CGotoLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoLineDlg)
	DDX_Text(pDX, IDC_LINE, m_nLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoLineDlg, CDialog)
	//{{AFX_MSG_MAP(CGotoLineDlg)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGotoLineDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CGotoLineDlg 


void CGotoLineDlg::OnBnClickedOk()
{
	UpdateData();
	CDialog::OnOK();
}


BOOL CGotoLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_LINE)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
