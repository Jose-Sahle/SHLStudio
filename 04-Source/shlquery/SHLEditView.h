/* **********************************************************************************
 * Arquivo: SHLEditView.h												            *
 *																					*
 * Classe que receberá informações diversão (Texto).                                *
 *																					*
 * Data:08/06/2013																	*
 * Auto: José Sahle Netto															*
 ********************************************************************************** */
#pragma once


// CSHLEditView view

class CSHLEditView : public CEditView
{
	DECLARE_DYNCREATE(CSHLEditView)

protected:
	CSHLEditView();           // protected constructor used by dynamic creation
	virtual ~CSHLEditView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	afx_msg void OnExecuteQuery();
	afx_msg void OnShowHideSplitterCmd();

	DECLARE_MESSAGE_MAP()
};


