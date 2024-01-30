/* ***************************************************************************
 * Arquivo: DeclarationType.h                                                *
 *                                                                           *
 * Declarações e enumerações genéricas                                       *
 *                                                                           *
 * Data:03/08/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#define WM_NEW_QUERY					(WM_USER + 0x100D)
#define WM_GET_RIBBONBAR				(WM_USER + 0x100F)
#define WM_ADD_STRING_OUTPUT			(WM_USER + 0x1010)
#define WM_CLEAR_STRING_OUTPUT			(WM_USER + 0x1011)
#define WM_SETBUILDPROJECTRESULT		(WM_USER + 0x1012)
#define WM_SETNEXTBUILDPROJECTRESULT	(WM_USER + 0x1013)

typedef CMap<CString, LPCTSTR, CString, LPCTSTR> MAPTYPEICONS;
typedef CMap<CString, LPCTSTR, int, int&> MAPICONS;
typedef CMap<CString, LPCTSTR, CMultiDocTemplate*, CMultiDocTemplate*&> MULTIDOCTEMPLATELIST;
typedef CMap<CString, LPCTSTR, HMODULE, HMODULE&> LIBRARYLIST;
typedef CMap<CString, LPCTSTR, CString, LPCTSTR> PROPERTYVALUE;
typedef CMap<int, int&, BOOL, BOOL&> CArrayIntBoolean;

typedef enum _shltypedlgprojectandfile
{
	SHLTYPEDLGPROJECTANDFILE_PROJECT,
	SHLTYPEDLGPROJECTANDFILE_ITEM,
	SHLTYPEDLGPROJECTANDFILE_DEPENDENCY,
	SHLTYPEDLGPROJECTANDFILE_LENGTH
}SHLTYPEDLGPROJECTANDFILE;

#define IMAGEMASKSOLUTIONEXPLORER RGB(0, 0, 0)
#define IMAGELISTSIZESOLUTIONEXPLORER 16


class PROJECTITEMINFO
{
public:
	HTREEITEM TreeNode;
	CString Path;
	CString Name;
	CString Description;
};
