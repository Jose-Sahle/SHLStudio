/*****************************************************************************
 * Arquivo: ISHLEditor                                                       *
 *                                                                           *
 * Classe de interface para permitir que programas externos instanciem       *
 * a classe SHLEditor.DLL
 *                                                                           *
 * Data:26/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>			
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifdef SHLEDITOR_EXPORTS
	#define SHLSHLEDITOR_API __declspec(dllexport)
#else
	#define SHLSHLEDITOR_API __declspec(dllimport)
#endif

class ISHLEditor
{
public:
	virtual bool LoadDocumentView(CRuntimeClass*& view, CRuntimeClass*& docment) = 0;
	virtual bool SetDocument(CString documentname, CRuntimeClass*& docment) = 0;
	virtual bool SetStyleDocument(UINT lexer, CDocument* docment, CStringArray& arCommands) = 0;

	virtual CString GetLastError() = 0;

	/* Release this instance */
	virtual void Release() = 0;
};

typedef ISHLEditor*	SHLEDITORHANDLE;

#ifdef __cplusplus
#   define EXTERN_C     extern "C"
#else
#   define EXTERN_C
#endif // __cplusplus

EXTERN_C SHLSHLEDITOR_API SHLEDITORHANDLE WINAPI GetSHLEditorInstance();

#ifndef SHLEDITOR_EXPORTS
	#include "AutoClosePtr.h"
	typedef AutoClosePtr<ISHLEditor, void, &ISHLEditor::Release> ISHLEditorPtr;
	typedef SHLEDITORHANDLE(WINAPI* LPFNGETSHLEDITORINSTANCE)();
#endif
