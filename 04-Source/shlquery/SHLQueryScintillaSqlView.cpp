#include "stdafx.h"
#include "Resource.h"
#include "FindDlg.h"
#include "ReplaceDlg.h"
#include "GotoPosDlg.h"
#include "GotoLineDlg.h"
#include "SHLQueryScintillaSqlDoc.h"
#include "SHLQueryScintillaSqlView.h"
#include "Library.h"

#define SQL_STATEMENTS			0  //KW_MSSQL_STATEMENTS       
#define SQL_DATA_TYPES			1  //KW_MSSQL_DATA_TYPES       
#define SQL_DATABASE_ELEMENTS	2  //KW_MSSQL_SYSTEM_TABLES    
#define SQL_GLOBAL_VARIABLES	3  //KW_MSSQL_GLOBAL_VARIABLES 
#define SQL_SPECIAL_FUNCTIONS	4  //KW_MSSQL_FUNCTIONS        
#define SQL_FUNCTIONS			5  //KW_MSSQL_STORED_PROCEDURES
#define SQL_OPERATORS			6  //KW_MSSQL_OPERATORS        

#define SQL_WORD_LIST_1			0  
#define SQL_WORD_LIST_2			1  
#define SQL_WORD_LIST_3			2  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

extern HINSTANCE g_hDLLInstance;


IMPLEMENT_DYNCREATE(CSHLQueryScintillaSqlView, CScintillaView)

BEGIN_MESSAGE_MAP(CSHLQueryScintillaSqlView, CScintillaView)
	ON_COMMAND(ID_EDIT_TOGGLE_BOOKMARK, OnOptionsAddDeletemarker)
	ON_COMMAND(ID_EDIT_GOTO_NEXT_BOOKMARK, OnOptionsFindNextmarker)
	ON_COMMAND(ID_EDIT_GOTO_PREV_BOOKMARK, OnOptionsFindPrevmarker)

	ON_COMMAND(ID_DATACONNECTION_NEWQUERY, OnNewQuery)
	ON_COMMAND(ID_DATACONNECTION_OPEN, OnOpenQuery)

	ON_COMMAND(ID_EDIT_FIND_DIALOG, OnFindDialog)
	ON_COMMAND(ID_EDIT_REPLACE_DIALOG, OnReplaceDialog)

	ON_COMMAND(ID_EDIT_FIND_REPLACE_NEXT, OnFindReplaceNext)
	ON_COMMAND(ID_EDIT_FIND_REPLACE_PREVIOUS, OnFindReplacePrevious)

	ON_COMMAND(ID_EDIT_GOTO_POSITION, OnGotoPos)
	ON_COMMAND(ID_EDIT_GOTO_LINE, OnGotoLine)

	ON_WM_ACTIVATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


CSHLQueryScintillaSqlView::CSHLQueryScintillaSqlView()
{
	LoadMarginSettings();
	m_hAccel = NULL;
	m_bAnswerOnChangeMessages = false;
	m_dlgFind = NULL;
	m_dlgReplace = NULL;
	m_findReplace = SHLFINDREPLACE::SHLFINDREPLACE_FIND;
}

CSHLQueryScintillaSqlView::~CSHLQueryScintillaSqlView()
{
	if (m_hAccel)
		DestroyAcceleratorTable(m_hAccel);

	if (m_dlgFind)
	{
		m_dlgFind->DestroyWindow();
	}

	if (m_dlgReplace)
	{
		m_dlgReplace->DestroyWindow();
	}
}

void CSHLQueryScintillaSqlView::OnDraw(CDC* /*pDC*/)
{
	CSHLQueryScintillaSqlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc; //To get rid of unused variable compiler warning
}

#ifdef _DEBUG
void CSHLQueryScintillaSqlView::AssertValid() const
{
	CScintillaView::AssertValid();
}

void CSHLQueryScintillaSqlView::Dump(CDumpContext& dc) const
{
	CScintillaView::Dump(dc);
}

CSHLQueryScintillaSqlDoc* CSHLQueryScintillaSqlView::GetDocument() //non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSHLQueryScintillaSqlDoc)));
	return static_cast<CSHLQueryScintillaSqlDoc*>(m_pDocument);
}
#else
inline CSHLQueryScintillaSqlDoc* CSHLQueryScintillaSqlView::GetDocument()
{
	return static_cast<CSHLQueryScintillaSqlDoc*>(m_pDocument);
}
#endif //_DEBUG
void CSHLQueryScintillaSqlView::ReplaceAllSel(_In_z_ LPCTSTR szFind, _In_z_ LPCTSTR szReplace, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression)
{
	CScintillaView::ReplaceAllSel(szFind, szReplace, bNext, bCase, bWord, bRegularExpression);
}

void CSHLQueryScintillaSqlView::ReplaceAll(_In_z_ LPCTSTR lpszFind, _In_z_ LPCTSTR lpszReplace, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression)
{
	OnReplaceAll(lpszFind, lpszReplace, bCase, bWord, bRegularExpression);
}

BOOL CSHLQueryScintillaSqlView::FindText(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression)
{
	CWaitCursor wait;

	return FindTextSimple(lpszFind, bNext, bCase, bWord, bRegularExpression);
}

void CSHLQueryScintillaSqlView::TextNotFound(_In_z_ LPCTSTR lpszFind, _In_ BOOL bNext, _In_ BOOL bCase, _In_ BOOL bWord, _In_ BOOL bRegularExpression, BOOL bReplaced)
{
	CWaitCursor wait;

	CScintillaView::TextNotFound(lpszFind, bNext, bCase, bWord, bRegularExpression, bReplaced);
}

void CSHLQueryScintillaSqlView::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	rCtrl.StyleSetFore(style, fore);
	rCtrl.StyleSetBack(style, back);
	if (size >= 1)
		rCtrl.StyleSetSize(style, size);
	if (face)
		rCtrl.StyleSetFont(style, face);
}

void CSHLQueryScintillaSqlView::DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	rCtrl.MarkerDefine(marker, markerType);
	rCtrl.MarkerSetFore(marker, fore);
	rCtrl.MarkerSetBack(marker, back);
}

int CSHLQueryScintillaSqlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScintillaView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ASSERT(m_hAccel == NULL);
	m_hAccel = ::LoadAccelerators(g_hDLLInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_EDITOR));
	ASSERT(m_hAccel != NULL);

	return 1;
}

BOOL CSHLQueryScintillaSqlView::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (m_hAccel != NULL)
		{
			if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
				return TRUE;
		}
	}

	return CScintillaView::PreTranslateMessage(pMsg);
}

void CSHLQueryScintillaSqlView::OnInitialUpdate()
{
	//Let the base class do its thing
	CScintillaView::OnInitialUpdate();
	//CStringArray arrWords;

	//SetStyleDocument(SCLEX_NULL, arrWords, arrWords, arrWords, arrWords, arrWords, arrWords);

#ifdef _DEBUG
	AfxDump(this);
#endif
}

void CSHLQueryScintillaSqlView::OnOptionsAddDeletemarker()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nPos = rCtrl.GetCurrentPos();
	int nLine = rCtrl.LineFromPosition(nPos);
	int nBits = rCtrl.MarkerGet(nLine);

	if ((nBits & 0x1))
		rCtrl.MarkerDelete(nLine, 0);
	else
		rCtrl.MarkerAdd(nLine, 0);

}

void CSHLQueryScintillaSqlView::OnOptionsFindNextmarker()
{
	Sci_Position nPos = GetCtrl().GetCurrentPos();
	long nLine = GetCtrl().LineFromPosition(nPos);

	long nFoundLine = GetCtrl().MarkerNext(nLine + 1, 0x1);

	if (nFoundLine >= 0)
		GetCtrl().GotoLine(nFoundLine);
	else
		MessageBeep(MB_ICONHAND);
}

void CSHLQueryScintillaSqlView::OnOptionsFindPrevmarker()
{
	Sci_Position nPos = GetCtrl().GetCurrentPos();
	long nLine = GetCtrl().LineFromPosition(nPos);
	long nFoundLine = GetCtrl().MarkerPrevious(nLine - 1, 0x1);

	if (nFoundLine >= 0)
		GetCtrl().GotoLine(nFoundLine);
	else
		MessageBeep(MB_ICONHAND);
}

void CSHLQueryScintillaSqlView::OnOptionsFoldMargin()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nMarginWidth = rCtrl.GetMarginWidthN(2);
	if (nMarginWidth)
		rCtrl.SetMarginWidthN(2, 0);
	else
		rCtrl.SetMarginWidthN(2, 16);
}

void CSHLQueryScintillaSqlView::OnOptionsSelectionMargin()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nMarginWidth = rCtrl.GetMarginWidthN(1);
	if (nMarginWidth)
		rCtrl.SetMarginWidthN(1, 0);
	else
		rCtrl.SetMarginWidthN(1, 16);
}

void CSHLQueryScintillaSqlView::OnOptionsViewLinenumbers()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nMarginWidth = rCtrl.GetMarginWidthN(0);

	if (nMarginWidth)
		rCtrl.SetMarginWidthN(0, 0);
	else
		rCtrl.SetMarginWidthN(0, 32);
}

//Some simple examples of implementing auto completion
void CSHLQueryScintillaSqlView::OnCharAdded(SCNotification* /*pSCNotification*/)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	//Get the previous 13 characters and if it is "scintilla is " case insensitive
	//then display a list which allows "very cool", "easy" or the "way cool!!"
	int nStartSel = rCtrl.GetSelectionStart();
	int nEndSel = rCtrl.GetSelectionEnd();

	if (nStartSel == nEndSel)
	{
		Sci_TextRange tr;
		tr.chrg.cpMin = nStartSel - 1;
		tr.chrg.cpMax = nEndSel;
		char sText[14];
		sText[0] = '\0';
		tr.lpstrText = sText;
		rCtrl.GetTextRange(&tr);

		//Display the auto completion list
		if ((_strcmpi(sText, "\r") == 0) || (_strcmpi(sText, "\n") == 0))
		{
			char  linebuf[1000];
			Sci_Position nPos = GetCtrl().GetCurrentPos();
			long curLine = GetCtrl().LineFromPosition(nPos);

			int  lineLength = rCtrl.LineLength(curLine);

			//Platform::DebugPrintf("[CR] %d len = %d\n", curLine, lineLength);
			if (curLine > 0 && lineLength <= 2)
			{
				int  prevLineLength = rCtrl.LineLength(curLine - 1);

				if (prevLineLength < sizeof(linebuf))
				{
					WORD  buflen = sizeof(linebuf);
					memcpy(linebuf, &buflen, sizeof(buflen));

					rCtrl.GetLine(curLine - 1, linebuf);

					linebuf[prevLineLength] = '\0';

					for (int pos = 0; linebuf[pos]; pos++)
					{
						if (linebuf[pos] != ' '  &&   linebuf[pos] != '\t')
							linebuf[pos] = '\0';
					}
					CString strlinebuf = CString(linebuf);
					rCtrl.InsertText(nEndSel, linebuf);
					rCtrl.SetSelectionStart(nEndSel + strlinebuf.GetLength());
					rCtrl.SetCurrentPos(nEndSel + strlinebuf.GetLength());
				}
			}
		}
	}
}

//A simple example of call tips
void CSHLQueryScintillaSqlView::OnDwellStart(SCNotification* pSCNotification)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	//Only display the call tip if the scintilla window has focus
	CWnd* pFocusWnd = GetFocus();
	if (pFocusWnd)
	{
		if (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd())
		{
			//Get the previous 7 characters and next 7 characters arround
			//the current dwell position and if it is "author " case insensitive
			//then display "PJ Naughter" as a call tip
			Sci_TextRange tr;
			tr.chrg.cpMin = max(0, pSCNotification->position - 7);
			tr.chrg.cpMax = min(pSCNotification->position + 7, rCtrl.GetLength());
			char sText[15];
			sText[0] = '\0';
			tr.lpstrText = sText;
			rCtrl.GetTextRange(&tr);

			//Display the call tip
			_strupr_s(sText, sizeof(sText));
			if (strstr(sText, "AUTHOR "))
				rCtrl.CallTipShow(pSCNotification->position, _T("José Sahle Netto"));
		}
	}
}

void CSHLQueryScintillaSqlView::OnDwellEnd(SCNotification* /*pSCNotification*/)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	//Cancel any outstanding call tip
	if (rCtrl.CallTipActive())
		rCtrl.CallTipCancel();
}

void CSHLQueryScintillaSqlView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//Let the base class do its thing
	CScintillaView::OnActivate(nState, pWndOther, bMinimized);

	CScintillaCtrl& rCtrl = GetCtrl();

	//Cancel any outstanding call tip
	if (nState == WA_INACTIVE && rCtrl.CallTipActive())
		rCtrl.CallTipCancel();
}

void CSHLQueryScintillaSqlView::OnModifyAttemptRO(SCNotification* pSCNotification)
{
	if (AfxMessageBox(_T("This file is readonly. Do you want change it to overwrite?"), MB_YESNO) == IDYES)
		GetCtrl().SetReadOnly(FALSE);
}

void CSHLQueryScintillaSqlView::OnChange()
{
	/*m_bAnswerOnChangeMessages*/
	GetDocument()->SetModifiedFlag(GetCtrl().GetModify());
}

void CSHLQueryScintillaSqlView::SetStyleDocument(int lexer, CStringArray& arStyleCommands, CStringArray& arStyleFunctions, CStringArray& arStyleSpecialFunctions, CStringArray& arStyleDataType, CStringArray& arStyleDatabaseElements, CStringArray& arStyleOperators)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString strStatements;

	//Setup the Lexer
	rCtrl.SetLexer(lexer /*SCLEX_SQL*/);

	rCtrl.SetUseTabs(TRUE);
	rCtrl.SetTabIndents(TRUE);
	rCtrl.SetBackSpaceUnIndents(TRUE);
	rCtrl.SetIndentationGuides(SC_IV_LOOKFORWARD);
	rCtrl.SetTabWidth(4);
	rCtrl.SetIndent(0);
	rCtrl.SetCodePage(SC_CP_UTF8);

	//Setup styles
	if (lexer == SCLEX_MSSQL)
	{
		rCtrl.StyleClearAll();

		if ((strStatements = GetWords(arStyleCommands)) != _T(""))
			rCtrl.SetKeyWords(SQL_STATEMENTS, strStatements);

		if ((strStatements = GetWords(arStyleFunctions)) != _T(""))
			rCtrl.SetKeyWords(SQL_FUNCTIONS, strStatements);

		if ((strStatements = GetWords(arStyleSpecialFunctions)) != _T(""))
			rCtrl.SetKeyWords(SQL_SPECIAL_FUNCTIONS, strStatements);

		if ((strStatements = GetWords(arStyleDataType)) != _T(""))
			rCtrl.SetKeyWords(SQL_DATA_TYPES, strStatements);

		if ((strStatements = GetWords(arStyleDatabaseElements)) != _T(""))
			rCtrl.SetKeyWords(SQL_DATABASE_ELEMENTS, strStatements);

		if ((strStatements = GetWords(arStyleOperators)) != _T(""))
			rCtrl.SetKeyWords(SQL_OPERATORS, strStatements);

		SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(0xff, 0xff, 0xff), 9, "Courier New");

		SetAStyle(SCE_MSSQL_DEFAULT, RGB(0, 0, 0));
		SetAStyle(SCE_MSSQL_COMMENT, RGB(0, 128, 0));
		SetAStyle(SCE_MSSQL_LINE_COMMENT, RGB(0, 128, 0));
		SetAStyle(SCE_MSSQL_NUMBER, RGB(0, 80, 128));
		SetAStyle(SCE_MSSQL_STRING, RGB(255, 0, 0));
		SetAStyle(SCE_MSSQL_IDENTIFIER, RGB(0, 0, 0));
		SetAStyle(SCE_MSSQL_OPERATOR, RGB(128, 128, 0));

		SetAStyle(SCE_MSSQL_VARIABLE, RGB(123, 104, 238));

		SetAStyle(SCE_MSSQL_STATEMENT, RGB(0, 0, 205));
		SetAStyle(SCE_MSSQL_DATATYPE, RGB(39, 64, 139));
		SetAStyle(SCE_MSSQL_STORED_PROCEDURE, RGB(255, 130, 171));
		SetAStyle(SCE_MSSQL_SYSTABLE, RGB(0, 250, 154));
		SetAStyle(SCE_MSSQL_FUNCTION, RGB(0, 245, 255));

		rCtrl.StyleSetBold(SCE_MSSQL_STATEMENT, TRUE);
		rCtrl.StyleSetItalic(SCE_MSSQL_LINE_COMMENT, TRUE);

		//Setup folding
		rCtrl.SetMarginWidthN(2, 16);
		rCtrl.SetMarginSensitiveN(2, TRUE);
		rCtrl.SetMarginTypeN(2, SC_MARGIN_SYMBOL);
		rCtrl.SetMarginMaskN(2, SC_MASK_FOLDERS);
		rCtrl.SetScintillaProperty(_T("fold"), _T("1"));

		//Setup markers
		DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
		DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_PLUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
		DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));

		//Setup auto completion
		rCtrl.AutoCSetSeparator(10); //Use a separator of line feed

		//Setup call tips
		rCtrl.SetMouseDwellTime(1000);

		//Enable Multiple selection
		rCtrl.SetMultipleSelection(TRUE);

	}

	//Setup markers
	DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
	DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));

	rCtrl.SetScintillaProperty(_T("fold.compact"), _T("0"));

	//Setup auto completion
	rCtrl.AutoCSetSeparator(10); //Use a separator of line feed

	//Setup call tips
	rCtrl.SetMouseDwellTime(1000);

	rCtrl.SetMarginWidthN(0, 32);
	rCtrl.SetMarginRight(32);
}

CString CSHLQueryScintillaSqlView::GetWords(CStringArray& arStyleStatements)
{
	CString strStatements;

	if (arStyleStatements.GetCount() > 0)
	{
		for (INT nIndex = 0; nIndex < arStyleStatements.GetCount(); nIndex++)
			strStatements += arStyleStatements.GetAt(nIndex);

		strStatements.MakeLower();
	}

	return strStatements;
}

void CSHLQueryScintillaSqlView::GetSqlSentence()
{
	CScintillaCtrl& rCtrl = GetCtrl();

	m_strSentence = rCtrl.GetSelText();

	if (m_strSentence.IsEmpty())
	{
		int nTextLength = rCtrl.GetTextLength() + 1;
		m_strSentence = rCtrl.GetText(nTextLength);
	}
}

TCHAR CSHLQueryScintillaSqlView::GetSentenceAt(int pos)
{
	if (pos > m_strSentence.GetLength() - 1)
		return '\0';

	return m_strSentence.GetAt(pos);
}

void CSHLQueryScintillaSqlView::OnNewQuery()
{
	::PostMessage(this->GetParentFrame()->GetSafeHwnd(), WM_NEW_QUERY, 0, 0);
}

void CSHLQueryScintillaSqlView::OnOpenQuery()
{
	GetDocument()->FileOpen();
}

void CSHLQueryScintillaSqlView::OnFindDialog()
{
	CFindDlg* findDlg = NULL;

	try
	{
		m_findReplace = SHLFINDREPLACE::SHLFINDREPLACE_FIND;

		if (m_dlgFind == NULL)
		{
			findDlg = new CFindDlg;
			if (!findDlg->Create(IDD_FIND, this))
			{
				AfxMessageBox(_T("Error creating Find Dialog"));
				return;
			}

			findDlg->Editor = this;
			findDlg->InitDialog();
			m_dlgFind = findDlg;
			m_dlgFind->ShowWindow(SW_SHOW);
		}
		else
		{
			((CFindDlg*)m_dlgFind)->InitDialog();
			m_dlgFind->ShowWindow(SW_SHOW);
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}

void CSHLQueryScintillaSqlView::OnReplaceDialog()
{
	CReplaceDlg* replaceDlg = NULL;

	try
	{
		m_findReplace = SHLFINDREPLACE::SHLFINDREPLACE_REPLACE;

		if (m_dlgReplace == NULL)
		{
			replaceDlg = new CReplaceDlg;
			if (!replaceDlg->Create(IDD_REPLACE, this))
			{
				AfxMessageBox(_T("Error creating Replace Dialog"));
				return;
			}

			replaceDlg->Editor = this;
			replaceDlg->InitDialog();
			m_dlgReplace = replaceDlg;
			m_dlgReplace->ShowWindow(SW_SHOW);
		}
		else
		{
			((CReplaceDlg*)m_dlgReplace)->InitDialog();
			m_dlgReplace->ShowWindow(SW_SHOW);
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}

void CSHLQueryScintillaSqlView::OnGotoPos()
{
	CGotoPosDlg dlgGotPos;

	try
	{
		dlgGotPos.m_nPos = GetCtrl().GetCurrentPos();

		if (dlgGotPos.DoModal() == IDOK)
		{
			GetCtrl().GotoPos(dlgGotPos.m_nPos);
			GetCtrl().SetFocus();
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}

void CSHLQueryScintillaSqlView::OnGotoLine()
{
	CGotoLineDlg dlgGotoLine;

	try
	{
		Sci_Position nPos = GetCtrl().GetCurrentPos();
		dlgGotoLine.m_nLine = GetCtrl().LineFromPosition(nPos);

		if (dlgGotoLine.DoModal() == IDOK)
		{
			GetCtrl().GotoLine(dlgGotoLine.m_nLine - 1);
			GetCtrl().SetFocus();
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}

void CSHLQueryScintillaSqlView::OnFindReplaceNext()
{
	try
	{
		if (m_findReplace == SHLFINDREPLACE::SHLFINDREPLACE_FIND)
		{
			if (m_dlgFind == NULL)
			{
				OnFindDialog();
				return;
			}

			((CFindDlg*)m_dlgFind)->OnNext();
		}
		else
		{
			if (m_dlgReplace == NULL)
			{
				OnReplaceDialog();
				return;
			}

			((CReplaceDlg*)m_dlgReplace)->ReplaceNext();
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}

void CSHLQueryScintillaSqlView::OnFindReplacePrevious()
{
	try
	{
		if (m_findReplace == SHLFINDREPLACE::SHLFINDREPLACE_FIND)
		{
			if (m_dlgFind == NULL)
			{
				OnFindDialog();
				return;
			}

			((CFindDlg*)m_dlgFind)->OnPrev();
		}
		else
		{
			if (m_dlgReplace == NULL)
			{
				OnReplaceDialog();
				return;
			}

			((CReplaceDlg*)m_dlgReplace)->ReplacePrevious();
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}