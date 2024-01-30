/* ***************************************************************************
 * Arquivo: ProjectEntity.h                                                  *
 *                                                                           *
 * Classe que mantém informações dos projetos de uma solução do SHLStudio.   *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "SHLTreeNode.h"
#include "Property.h"
#include "ItemEntity.h"
#include "FolderEntity.h"
#include "Library.h"

class CProjectEntity
{
public:
	CProjectEntity(void){Reset();}
	virtual ~CProjectEntity(){Reset();}

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

 	PROPERTY(CString, FileName)
  	GET(FileName) 
 	{ 
 		return m_filename; 
	}
 	SET(FileName)
 	{
 		m_filename = value;
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

 	PROPERTY(CString, Version)
  	GET(Version) 
 	{ 
 		return m_version; 
	}
 	SET(Version)
 	{
 		m_version = value;
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

 	PROPERTY(CString, Plugin)
  	GET(Plugin) 
 	{ 
 		return m_plugin; 
	}
 	SET(Plugin)
 	{
 		m_plugin = value;
 	} 

 	PROPERTY(CString, ClassDll)
  	GET(ClassDll) 
 	{ 
 		return m_classdll; 
	}
 	SET(ClassDll)
 	{
 		m_classdll = value;
 	} 

 	PROPERTY(CString, Template)
  	GET(Template) 
 	{ 
 		return m_template; 
	}
 	SET(Template)
 	{
 		m_template = value;
 	} 

 	PROPERTY(CString, TemplateFile)
  	GET(TemplateFile) 
 	{ 
 		return m_templatefile; 
	}
 	SET(TemplateFile)
 	{
 		m_templatefile = value;
 	} 

 	PROPERTY(CString, TemplateProperties)
  	GET(TemplateProperties) 
 	{ 
 		return m_templateproperties; 
	}
 	SET(TemplateProperties)
 	{
 		m_templateproperties = value;
 	} 

 	PROPERTY(CString, PropertyFile)
  	GET(PropertyFile) 
 	{ 
 		return m_propertyfile; 
	}
 	SET(PropertyFile)
 	{
 		m_propertyfile = value;
 	} 

 	PROPERTY(HTREEITEM, TreeNode)
  	GET(TreeNode) 
 	{ 
 		return m_treenode; 
	}
 	SET(TreeNode)
 	{
 		m_treenode = value;
 	} 

 	PROPERTY(int, Numeric)
  	GET(Numeric) 
 	{ 
 		return m_numeric; 
	}
 	SET(Numeric)
 	{
 		m_numeric = value;
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

 	PROPERTY(bool, Changed)
  	GET(Changed) 
 	{ 
 		return m_changed; 
	}
 	SET(Changed)
 	{
 		m_changed = value;
 	} 

 	PROPERTY(CString, Category)
  	GET(Category) 
 	{ 
 		return m_category; 
	}
 	SET(Category)
 	{
 		m_category = value;
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

 	PROPERTY(bool, CanBuild)
  	GET(CanBuild) 
 	{ 
 		return m_canbuild;
	}
 	SET(CanBuild)
 	{
 		m_canbuild = value;
 	} 

 	READONLY_PROPERTY(CSHLTreeNode<CItemEntity>*, Items)
  	GET(Items) 
 	{ 
 		return &m_items; 
	}

 	READONLY_PROPERTY(CSHLTreeNode<CFolderEntity>*, Folders)
  	GET(Folders) 
 	{ 
 		return &m_folders; 
	}

 	READONLY_PROPERTY(PROPERTYVALUE&, Properties)
  	GET(Properties) 
 	{ 
 		return m_properties; 
	}

 	READONLY_PROPERTY(CString, Error)
  	GET(Error) 
 	{ 
 		return m_error; 
	}

	void Reset()
	{
		m_version				= _T("");
		m_name					= _T("");
		m_filename				= _T("");
		m_path					= _T("");
		m_type					= _T("");
		m_plugin				= _T("");
		m_classdll				= _T("");
		m_propertyfile			= _T("");
		m_template				= _T("");
		m_templatefile			= _T("");
		m_templateproperties	= _T("");
		m_icon					= _T("");
		m_error					= _T("");
		m_category				= _T("");
		m_description			= _T("");

		m_numeric				= -1;

		m_changed				= false;
		m_canbuild				= false;
		m_treenode				= NULL;

		m_items.RemoveAllItems();
		m_items.RemoveAllNodes();

		m_properties.RemoveAll();

		m_folders.RemoveAllItems();
		m_folders.RemoveAllNodes();
	}
//
private:
	CString						m_version;
	CString						m_name;
	CString						m_filename;
	CString						m_path;
	CString						m_type;
	CString						m_plugin;
	CString						m_classdll;
	CString						m_propertyfile;
	CString						m_template;
	CString						m_templatefile;
	CString						m_templateproperties;
	CString						m_error;
	CString						m_category;
	CString						m_description;
	CString						m_icon;

	int							m_numeric;

	HTREEITEM					m_treenode;

	CSHLTreeNode<CItemEntity>	m_items;
	CSHLTreeNode<CFolderEntity>	m_folders;
	PROPERTYVALUE				m_properties;

	bool						m_changed;
	bool						m_canbuild;
};
