/* ***************************************************************************
 * Arquivo: FolderEntity.h                                                   *
 *                                                                           *
 * Classe que mantém informações dos diretórios virtuais ou reais do         *
 * dos projetos de SHLStudio.                                                *
 *                                                                           *
 * Data:08/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "Property.h"

class CFolderEntity
{
public:
	CFolderEntity(){Reset();}

	virtual ~CFolderEntity(){Reset();};

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

 	PROPERTY(CString, ID)
  	GET(ID) 
 	{ 
 		return m_id; 
	}
 	SET(ID)
 	{
 		m_id = value;
 	} 

 	PROPERTY(CString, Type)
  	GET(Type) 
 	{ 
 		return m_type; 
	}
 	SET(Type)
 	{
 		m_type = value;
 	} 

 	PROPERTY(CString, Parent)
  	GET(Parent) 
 	{ 
 		return m_parent; 
	}
 	SET(Parent)
 	{
 		m_parent = value;
 	} 

 	PROPERTY(CString, Icon)
  	GET(Icon) 
 	{ 
 		return m_icon; 
	}
 	SET(Icon)
 	{
 		m_icon = value;
 	} 

 	PROPERTY(HTREEITEM, TreeItem)
  	GET(TreeItem) 
 	{ 
 		return m_treeitem; 
	}
 	SET(TreeItem)
 	{
 		m_treeitem = value;
 	} 

	void Reset()
	{
		m_name		= _T("");
		m_id		= _T("");
		m_type		= _T("");
		m_parent	= _T("");
		m_icon		= _T("");
		m_treeitem	= NULL;
	}

// Membros Privados
private:
	CString			m_name;
	CString			m_id;
	CString			m_type;
	CString			m_parent;
	CString			m_icon;
	HTREEITEM		m_treeitem;
};