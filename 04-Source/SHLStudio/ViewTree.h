// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree window

class CViewTree : public CTreeCtrl
{
// Construction
public:
	CViewTree();
	virtual ~CViewTree();


// Overrides
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	virtual HTREEITEM InsertTreeItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent);
	
	void SetDefaultCursor();
	void SetCursorHand();
	void SetCursorArr();
	void SetCursorNo();

	HCURSOR GetCursorHand();
	HCURSOR GetCursorArr();
	HCURSOR GetCursorNo();

	BOOL ReleaseCapt();
	
protected:
	DECLARE_MESSAGE_MAP()

protected:
//*********** CURSORS  *********************
	HCURSOR cursor_hand ;
	HCURSOR cursor_arr	;
	HCURSOR cursor_no	;
//******************************************

};
