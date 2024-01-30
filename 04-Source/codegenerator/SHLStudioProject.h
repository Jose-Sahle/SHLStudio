/* ***************************************************************************
 * Arquivo: SHLStudioProject.h                                               *
 *                                                                           *
 * Classe plugin de funcionalidade para o SHLStudio                          *
 *                                                                           *
 * Data:29/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ISHLSTUDIOPROJECT.h"
#include "SHLOleDBReader.h"
#include "WFRead.h"

class CSHLStudioProject : public ISHLStudioProject
{
public:
	CSHLStudioProject(void);
	virtual ~CSHLStudioProject(void);

	/* Set Template Document */
	virtual bool GetDocumentTemplate(SHLSTUDIOMETHODS Method, PSHLSTUDIOARGLIST Arguments, CSolutionEntity *solution, CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment);

	/* Comunication Methosd */
	virtual bool RunMethods(SHLSTUDIOMETHODS Method, PSHLSTUDIOARGLIST Arguments);

	/* Return the last error */
	CString GetLastError();

	/* Release this instance */
	void Release();

private:
	CString m_Error;
	HINSTANCE m_hSciDLL;

private:
	bool AddExistingItem(CProjectEntity* Project, CTreeCtrl& ctrlTreeView, MAPICONS& mapIcons, CImageList& solutionViewImages, CString folderID, HTREEITEM hParent);
	bool AddExistingItemFromProject(CProjectEntity* Project, CTreeCtrl& ctrlTreeView, MAPICONS& mapIcons, CImageList& solutionViewImages);
	bool AddExistingItemFromFolder(CProjectEntity* Project, CFolderEntity* folder, CTreeCtrl& ctrlTreeView, MAPICONS& mapIcons, CImageList& solutionViewImages);
	bool LoadProjectProperties(CProjectEntity* Project, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment);
	bool SetProjectProperties(CProjectEntity* Project, CDocument* document);

	bool LoadGenerateItem(CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment);
	bool LoadEditItem(CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment);
	bool SetItemProperties(CProjectEntity* Project, CItemEntity* Item, CDocument* document, bool newWindow);
	bool SetGenerateItem(CProjectEntity* Project, CItemEntity* Item, CDocument* document);
	bool GenerateItem(CProjectEntity* Project, CItemEntity* Item, HWND  hwndOutput);

	bool LoadPropertiesItem(CProjectEntity* Project, CItemEntity* Item, CMFCPropertyGridCtrl& wndPropList);
	bool SavePropertiesItem(CItemEntity* Item);

	bool BuildProject(CProjectEntity* Project, HWND hwndOutput);

	bool GenerateItemAllTypes(CProjectEntity* Project, CItemEntity* Item, HWND  hwndOutput);
	bool LoadPropertyFile(CString propertyfile, PROPERTYVALUE& Properties, HWND  hwndOutput);
	bool LoadPropertyProject(CString  propertyfile, PROPERTYVALUE& Properties, HWND  hwndOutput);

	CItemEntity* FindDatabaseProviderItem(CString DatabaseProvider, CProjectEntity* Project);
	SHLOleDBReader* LoadDTFileToReader(CItemEntity* DatabaseProviderItem);

	UINT GetInitCount(CString line);

	BOOL ChangeShareTags(CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString contentline, CString &sourcecode);
	BOOL ChangeTableTags(CProjectEntity* Project, CItemEntity* Item, SHLOleDBTable* table, INT prefixTable, HWND  hwndOutput, CString contentline, CString &sourcecode);
	BOOL ChangePrimarykeyTags(CProjectEntity* Project, CItemEntity* Item, SHLOleDBTable* table, HWND  hwndOutput, CString contentline, CString &sourcecode);
	BOOL ChangeFieldsTags(CProjectEntity* Project, CItemEntity* Item, SHLOleDBTable* table, INT prefixTable, SHLDBROW *row, UINT nIndex, UINT nCount, HWND  hwndOutput, CString contentline, CString &sourcecode, UINT fieldcount);

	BOOL ChangeSpecialTags(HWND  hwndOutput, CString &sourcecode);

	BOOL ReadUserAreaFromTarget(CString targetfile, HWND  hwndOutput, CString &sourcecode);

	CString GetTableName(CString tableName, INT prefixTable, BOOL firtUpperCase);

	BOOL GenerateSourceCodePerTable(SHLOleDBTable* table, CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode);
	BOOL GenerateSourceCodeStandAlone(CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode);
	BOOL RepeatCodeToAllTables(CFread& fread, CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode);
	BOOL ReadToAllTables(CStringArray& arLines, SHLOleDBTable* table, CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode);
	BOOL HasTableForeignkey(SHLOleDBTable* table);

	CString GetTypeCS(CString type, bool nullable);
	CString GetTypePlusPlus(CString type, bool nullable);

	CString GetAccessType(CString type, CString size);
	CString GetSQLServerType(CString type, CString size);
	CString GetOracleType(CString type, CString size);
	CString GetPostGreSQLType(CString type, CString size);
	CString GetMySQLType(CString type, CString size);

	void SendOutPutMessage(HWND hwndOutput, CString message);
	CString SelectFile(CString strFileName, CString strDefaultExt, CString strFilter);
};


