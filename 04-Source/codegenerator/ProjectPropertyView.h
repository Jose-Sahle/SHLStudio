/* ***************************************************************************
 * Arquivo: ProjectPropertyView.h                                            *
 *                                                                           *
 * Classe da estrutura Doc/View do MFC que trata as propriedades do projeto  *
 * Gerador Classes C#.                                                       *
 *                                                                           *
 * Data:29/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "bpctrlanchormap.h"

// CProjectPropertyView form view

class CProjectPropertyView : public CFormView
{
	DECLARE_DYNCREATE(CProjectPropertyView)
	DECLARE_ANCHOR_MAP();

protected:
	CProjectPropertyView();           // protected constructor used by dynamic creation
	virtual ~CProjectPropertyView();

public:
	enum { IDD = IDD_DIALOG_PROPERTY_PROJECT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual void OnInitialUpdate();
	afx_msg void OnEnChangeProperties();
	afx_msg void OnBnClickedButtonApply();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

	// Private Members
private:
	CEdit m_txtVersion;
	CEdit m_txtAuthor;
	bool  m_bFirstAtivated;

public:
	void FillProperties();
	void SaveProperties();

};


