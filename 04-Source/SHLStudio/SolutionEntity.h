/* ***************************************************************************
 * Arquivo: SolutionEntity.h                                                 *
 *                                                                           *
 * Classe que mantém informações da solução gerenciada pelo SHLStudio.       *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "Property.h"
#include "SHLTreeNode.h"
#include "ProjectEntity.h"

class CSolutionEntity
{
public:
	CSolutionEntity(){Reset();}
	virtual ~CSolutionEntity(){Reset();}

// Propriedades
public:	
 	PROPERTY(CString, Name)
  	GET(Name) 
 	{ 
 		return m_name; 
	}
 	SET(Name)
 	{
 		m_name = value;
 	} 

 	PROPERTY(CString, Description)
  	GET(Description) 
 	{ 
 		return m_description; 
	}
 	SET(Description)
 	{
 		m_description = value;
 	} 

 	PROPERTY(CString, Version)
  	GET(Version) 
 	{ 
 		return m_version; 
	}
 	SET(Version)
 	{
 		m_version = value;
 	} 

 	PROPERTY(CString, Path)
  	GET(Path) 
 	{ 
 		return m_path; 
	}
 	SET(Path)
 	{
 		m_path = value;
 	} 

 	PROPERTY(CString, FileName)
  	GET(FileName) 
 	{ 
 		return m_filename; 
	}
 	SET(FileName)
 	{
 		m_filename = value;
 	} 

 	PROPERTY(bool, Changed)
  	GET(Changed) 
 	{ 
 		return m_changed; 
	}
 	SET(Changed)
 	{
 		m_changed = value;
 	} 

 	READONLY_PROPERTY(CSHLTreeNode<CProjectEntity>*, Projects)
  	GET(Projects) 
 	{ 
 		return &m_projects; 
	}

	void Reset()
	{
		m_name			= _T("");
		m_version		= _T("");
		m_path			= _T("");
		m_filename		= _T("");
		m_description	= _T("");
		m_changed		= false;

		m_projects.RemoveAllItems();
		m_projects.RemoveAllNodes();
	}

// Membros Privados
private:
	CString							m_name;
	CString							m_description;
	CString							m_version;
	CString							m_path;
	CString							m_filename;
	CSHLTreeNode<CProjectEntity>	m_projects;
	bool							m_changed;
};
