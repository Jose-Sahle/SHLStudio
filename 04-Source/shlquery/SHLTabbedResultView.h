/* ***************************************************************************
 * Arquivo: SHLTabbedResult                                                  *
 *                                                                           *
 * Classe para mostrar vários resultados em tab.                             *
 *                                                                           *
 * Data:02/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */

#pragma once

#include "SHLUltimateGridView.h"
#include "SHLOleDBReader.h"
#include "SHLOleDBTable.h"
#include "SHLEditView.h"

class CSHLTabbedResultView : public CTabView
{
	DECLARE_DYNCREATE(CSHLTabbedResultView)

protected:
	CSHLTabbedResultView();           // protected constructor used by dynamic creation
	virtual ~CSHLTabbedResultView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()


protected:
	CSHLEditView*			m_wndResultText;
	CSHLUltimateGridView*	m_wndGridView;

	CString m_error;

	UINT m_lastID;


	// Public Methods
public:
	void DeleteAllResults();
	void SetResultText(CString content);
	void ResetContent();
	void SetCurrentTab(INT tab);
	void SetNewDataGrid(SHLOleDBTable* table, TCHAR* szQuery);

private:
	bool InitControls();

};


