/* ***************************************************************************
 * Arquivo: SHLUltimateGridView                                              *
 *                                                                           *
 * Encapsula o control Ultimate Grid Control                                 *
 *                                                                           *
 * Data:02/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */

#pragma once
#include "SHLOleDBTable.h"
#include "UGCtrlEx.h"

class CSHLUltimateGridView : public CView
{
	DECLARE_DYNCREATE(CSHLUltimateGridView)


protected:
	CSHLUltimateGridView();
	virtual ~CSHLUltimateGridView();

protected:
	CUGCtrlEx m_grid;
	HACCEL m_hAccel;

protected:
	afx_msg void CopySelected();
	afx_msg void SelectAll();
	afx_msg void OnExecuteQuery();
	afx_msg void OnShowHideSplitterCmd();

	afx_msg LRESULT OnCopySelected(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDraw(CDC* /*pDC*/);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()

public:
	void SetTableResult(SHLOleDBTable* table, TCHAR* szQuery);

private:
	void AdjustLayout(int cx, int cy);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

