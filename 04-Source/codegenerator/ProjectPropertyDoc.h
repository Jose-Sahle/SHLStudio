/* ***************************************************************************
 * Arquivo: ProjectPropertyDoc.h                                             *
 *                                                                           *
 * Classe da estrutura Doc/View do MFC que trata as propriedades do projeto  *
 * Gerador Classes C#.                                                       *
 *                                                                           *
 * Data:29/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "Property.h"
#include "ProjectEntity.h"

// CProjectPropertyDoc document

class CProjectPropertyDoc : public CDocument
{
	DECLARE_DYNCREATE(CProjectPropertyDoc)

public:
	CProjectPropertyDoc();
	virtual ~CProjectPropertyDoc();
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL SaveModified();
	virtual void OnCloseDocument();

	DECLARE_MESSAGE_MAP()

	// Properties
public:
 	PROPERTY(CProjectEntity*&, Project)
  	GET(Project) 
 	{ 
 		return m_project; 
	}
 	SET(Project)
 	{
 		m_project = value;
 	} 

 	READONLY_PROPERTY(CString, Error)
  	GET(Error) 
 	{ 
 		return m_Error; 
	}

	// Private Members
private:
	CProjectEntity* m_project;
	CString			m_Error;

	// Private Methods
private:
	BOOL LoadPropertyDocument(LPCTSTR lpszPathName);
	BOOL SetViewProperties();

public:
		BOOL SavePropertyDocument();

};
