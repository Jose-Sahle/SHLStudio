/* ***************************************************************************
 * Arquivo: GenericChildFrame                                                *
 *                                                                           *
 * Classe ChildFrame genérica                                                *
 *                                                                           *
 * Data:21/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#ifdef _WIN32_WCE
#error "CMDIChildWnd is not supported for Windows CE."
#endif 

// CGenericChildFrame frame with splitter

class CGenericChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CGenericChildFrame)
protected:
	CGenericChildFrame();           // protected constructor used by dynamic creation
	virtual ~CGenericChildFrame();

	CSplitterWnd m_wndSplitter;

protected:
	afx_msg LRESULT OnGetView(WPARAM wParam, LPARAM lParam);

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


