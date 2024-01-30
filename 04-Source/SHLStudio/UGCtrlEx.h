// MyCUG.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "SHLOleDBTable.h"
#include <UGCtrl.h>
#include <ugctexpand.h>

#define ID_UG_USER					(3000)

#define ID_UG_COPY					(ID_UG_USER + 1)
#define ID_UG_COPY_WITH_HEADERS		(ID_UG_USER + 2)
#define ID_UG_SELECT_ALL			(ID_UG_USER + 3)
#define ID_UG_SAVE_RESULT_AS		(ID_UG_USER + 4)
#define ID_UG_PAGE_SETUP			(ID_UG_USER + 5)
#define ID_UG_PRINT					(ID_UG_USER + 6)
#define ID_UG_SEPARATOR				(ID_UG_USER + 7)

#define UG_COPY_WITH_HEADERS 

const COLORREF backColorHeaders		= RGB(190, 190, 190);
const COLORREF textColorHeaders		= RGB(255, 255,255);
const COLORREF backColorExpand		= RGB(185, 211, 238);
const COLORREF textColorExpand		= RGB(0, 0, 0);
const COLORREF backColorValues1		= RGB(185, 211, 238);
const COLORREF textColorValues1		= RGB(0, 0, 0);;
const COLORREF backColorValues2		= RGB(211, 211, 211);
const COLORREF textColorValues2		= RGB(0, 0, 0);;
const COLORREF backColorSeparate	= RGB(191, 191, 191);
const COLORREF backColorSelected	= RGB(58, 95, 205);
const COLORREF textColorSelected	= RGB(142, 35, 35);

const INT MAX_COL_SIZE = 800;

class CUGCtrlEx : public CUGCtrl
{
public:
	CUGCtrlEx();
	~CUGCtrlEx();

protected:
	CUGExpandType m_expand; 
	int m_nExpandIndex; 

private:

	DECLARE_MESSAGE_MAP()

public:
	virtual void AddColumn(CString columnName, INT columnSize, CUGCell* cell = NULL, BOOL canEdit = FALSE);
	virtual void SetResultTable(SHLOleDBTable& table, INT initRow = 0);

	//***** Over-ridable Notify Functions *****
	virtual void OnSetFocus(CWnd* pOldWnd);
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);

	//movement and sizing
	virtual int  OnCanMove(int oldcol,long oldrow,int newcol,long newrow);
	virtual int  OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow);
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	virtual void OnHitTop(long numrows,long rowspast);
	
	virtual int  OnCanSizeCol(int col);
	virtual void OnColSizing(int col,int *width);
	virtual void OnColSized(int col,int *width);
	virtual int  OnCanSizeRow(long row);
	virtual void OnRowSizing(long row,int *height);
	virtual void OnRowSized(long row,int *height);

	virtual int  OnCanSizeTopHdg();
	virtual int  OnCanSizeSideHdg();
	virtual int  OnTopHdgSizing(int *height);
	virtual int  OnSideHdgSizing(int *width);
	virtual int  OnTopHdgSized(int *height);
	virtual int  OnSideHdgSized(int *width);
		
	virtual void OnColChange(int oldcol,int newcol);
	virtual void OnRowChange(long oldrow,long newrow);
	virtual void OnCellChange(int oldcol,int newcol,long oldrow,long newrow);
	virtual void OnLeftColChange(int oldcol,int newcol);
	virtual void OnTopRowChange(long oldrow,long newrow);
	virtual void OnViewMoved( int nScrolDir, long oldPos, long newPos );
	virtual void OnSelectionChanged(int startCol,long startRow,int endCol,long endRow,int blockNum);

	//mouse and key strokes
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed=0);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed=0);
	
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
	virtual void OnKeyUp(UINT *vcKey,BOOL processed);
	virtual void OnCharDown(UINT *vcKey,BOOL processed);
	
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	//SetCell notification
	virtual void OnSetCell(int col,long row,CUGCell *cell);
	
	//data source notifications
	virtual void OnDataSourceNotify(int ID,long msg,long param);

	//cell type notifications
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);

	//editing
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);

	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	// Context help 
	virtual DWORD OnGetContextHelpID( int col, long row, int section );

	//hints
	virtual int OnHint(int col,long row,int section,CString *string);
	virtual int OnVScrollHint(long row,CString *string);
	virtual int OnHScrollHint(int col,CString *string);


	#ifdef __AFXOLE_H__  //OLE must be included

	////drag and drop
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,int col,long row);
	virtual DROPEFFECT OnDragDrop(COleDataObject* pDataObject,int col,long row);

	#endif

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	//DC setup
	virtual void OnScreenDCSetup(CDC *dc,int section);
	
	virtual void OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,RECT *cnrBtn,
		RECT *vScroll,RECT *hScroll,RECT *tabs);

	virtual void OnTabSelected(int ID);
	
	virtual COLORREF OnGetDefBackColor(int section);

	//focus rect setup
	virtual void OnDrawFocusRect(CDC *dc,RECT *rect);
	virtual void OnSetFocus(int section);
	virtual void OnKillFocus(int section, CWnd *pNewWnd);

	//column swapping
	virtual BOOL OnColSwapStart(int col);
	virtual BOOL OnCanColSwap(int fromCol,int toCol);
	virtual void OnColSwapped(int fromCol,int toCol);

	//trackig window
	virtual void OnTrackingWindowMoved(RECT *origRect,RECT *newRect);

	virtual void ShowRowHeader(BOOL show);
	virtual void ShowColHeader(BOOL show);

	void Copy();
	void SelectAll();
	void CopyWithHeaders();
	void SaveAs();
	void PageSetup();
	void Print();

private:
	void SelectRow(INT row);
	void SelectCol(INT col);

private:
	CSHLTreeNode<CUGCell> m_cellType;
	CArrayIntBoolean      m_canEdit;
	INT					  m_rowheadersize;
	INT					  m_colheadersize;
};
