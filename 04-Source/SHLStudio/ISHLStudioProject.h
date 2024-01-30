/* ***************************************************************************
 * Arquivo: ISHLStudioProject.h                                              *
 *                                                                           *
 * Interface para a criação de plugins para o SHLStudio.                     *
 *                                                                           *
 * Data:22/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "SHLTreeNode.h"
#include "SolutionEntity.h"
#include "ProjectEntity.h"
#include "ItemEntity.h"
#include "Library.h"
#include "SHLTreeNode.h"


#ifdef SHLSTUDIOPROJECT_EXPORTS
	#define SHLSTUDIOPROJECT_API __declspec(dllexport)
#else
	#define SHLSTUDIOPROJECT_API __declspec(dllimport)
#endif

typedef enum _shlstudiomethods
{
	/*GetDocumentTemplate*/
	SHLSTUDIOMETHODS_LOADPROJECTPROPERTIES,
	SHLSTUDIOMETHODS_LOAGENERATEITEM,
	SHLSTUDIOMETHODS_LOADEDITITEM,

	/*RunMethods*/
	SHLSTUDIOMETHODS_SETPROJECTROPERTIES,
	SHLSTUDIOMETHODS_SETITEMPROPERTIES,
	SHLSTUDIOMETHODS_SETGENERATEITEM,
	SHLSTUDIOMETHODS_GENERATEITEM,
	SHLSTUDIOMETHODS_LOADPROPERTYPROJECT,
	SHLSTUDIOMETHODS_LOADPROPERTIESITEM,
	SHLSTUDIOMETHODS_LOADPROPERTYFILE,
	SHLSTUDIOMETHODS_SAVEPROPERTIESITEM,
	SHLSTUDIOMETHODS_BUILDPROJECT,
	SHLSTUDIOMETHODS_ADDEXISTINGITEMFROMPROJECT,
	SHLSTUDIOMETHODS_ADDEXISTINGITEMFROMFOLDER
}SHLSTUDIOMETHODS;

/*typedef struct _shlstudioarg
{
	VOID* pArgument;
}SHLSTUDIOARG;*/
typedef CSHLTreeNode<VOID> SHLSTUDIOARGLIST;
typedef SHLSTUDIOARGLIST* PSHLSTUDIOARGLIST;

class ISHLStudioProject
{
public:
	virtual ~ISHLStudioProject() {};

	/* Set Template Document */
	virtual bool GetDocumentTemplate(SHLSTUDIOMETHODS Method, PSHLSTUDIOARGLIST Arguments, CSolutionEntity *solution, CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment) = 0;

	/* Comunication Methosd */
	virtual bool RunMethods(SHLSTUDIOMETHODS Method, PSHLSTUDIOARGLIST Arguments) = 0;

	/* Return the last error */
	virtual CString GetLastError() = 0;

	/* Release this instance */
	virtual void Release() = 0;
};

typedef ISHLStudioProject*	SHLSTUDIOPROJECTHANDLE;

#ifdef __cplusplus
#   define EXTERN_C     extern "C"
#else
#   define EXTERN_C
#endif // __cplusplus

EXTERN_C SHLSTUDIOPROJECT_API SHLSTUDIOPROJECTHANDLE WINAPI GetSHLStudioProjectInstance();

#ifndef SHLSTUDIOPROJECT_EXPORTS
	#include "AutoClosePtr.h"
	typedef AutoClosePtr<ISHLStudioProject, void, &ISHLStudioProject::Release> ISHLStudioProjectPtr;
	typedef SHLSTUDIOPROJECTHANDLE (WINAPI* LPFNGETSHLSTUDIOPROJECTINSTANCE)();
#endif
