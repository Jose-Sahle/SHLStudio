/* ***************************************************************************
 * Arquivo: SHLTreeCtrl                                                      *
 *                                                                           *
 * Extende as funcionalidade do CTreeCtrl.                                   *
 *                                                                           *
 * Data:30/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>			
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>

class CSHLTreeView : public CTreeCtrl
{
public:
	HTREEITEM InsertTreeItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent)
	{
		TVINSERTSTRUCT tvis;
		ZeroMemory(&tvis, sizeof(TVINSERTSTRUCT));

		tvis.hParent = hParent;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
		tvis.item.pszText = (LPTSTR) lpszItem;
		tvis.item.iImage = nImage;
		tvis.item.iSelectedImage = nSelectedImage;
		tvis.item.state = 0;
		tvis.item.stateMask = 0;
		tvis.item.lParam = 0;
		tvis.item.cChildren = 1;

		return InsertItem(&tvis);
	}
};
