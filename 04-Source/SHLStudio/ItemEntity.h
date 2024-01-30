/* ***************************************************************************
 * Arquivo: ItemEntity.h                                                     *
 *                                                                           *
 * Classe que mantém informações dos itens dos projetos de SHLStudio.        *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "Property.h"

class CItemEntity
{
public:
	CItemEntity(){Reset();}

	virtual ~CItemEntity(){Reset();};

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

 	PROPERTY(CString, Version)
  	GET(Version) 
 	{ 
 		return m_version; 
	}
 	SET(Version)
 	{
 		m_version = value;
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

 	PROPERTY(CString, PathType)
  	GET(PathType) 
 	{ 
 		return m_pathtype; 
	}
 	SET(PathType)
 	{
 		m_pathtype = value;
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

 	PROPERTY(CString, ClassView)
  	GET(ClassView) 
 	{ 
 		return m_classview; 
	}
 	SET(ClassView)
 	{
 		m_classview = value;
 	} 

 	PROPERTY(CString, ClassViewPluginFile)
  	GET(ClassViewPluginFile) 
 	{ 
 		return m_classviewpluginfile; 
	}
 	SET(ClassViewPluginFile)
 	{
 		m_classviewpluginfile = value;
 	} 

 	PROPERTY(CString, ClassDoc)
  	GET(ClassDoc) 
 	{ 
 		return m_classdoc; 
	}
 	SET(ClassDoc)
 	{
 		m_classdoc = value;
 	} 

 	PROPERTY(CString, ClassDocFile)
  	GET(ClassDocFile) 
 	{ 
 		return m_classdocfile; 
	}
 	SET(ClassDocFile)
 	{
 		m_classdocfile = value;
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

 	PROPERTY(CString, PropertyFile)
  	GET(PropertyFile) 
 	{ 
 		return m_propertyfile; 
	}
 	SET(PropertyFile)
 	{
 		m_propertyfile = value;
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

 	PROPERTY(CString, FolderID)
  	GET(FolderID) 
 	{ 
 		return m_folderid; 
	}
 	SET(FolderID)
 	{
 		m_folderid = value;
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

	
 	PROPERTY(void*, Project)
  	GET(Project) 
 	{ 
 		return m_project; 
	}
 	SET(Project)
 	{
 		m_project = value;
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

 	PROPERTY(int, Numeric)
  	GET(Numeric) 
 	{ 
 		return m_numeric; 
	}
 	SET(Numeric)
 	{
 		m_numeric = value;
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

 	READONLY_PROPERTY(PROPERTYVALUE&, Properties)
  	GET(Properties) 
 	{ 
 		return m_properties; 
	}

 	READONLY_PROPERTY(CSHLTreeNode<CItemEntity>*, Dependencies)
  	GET(Dependencies) 
 	{ 
 		return &m_dependencies; 
	}

	void Reset()
	{
		m_name					= _T("");
		m_version				= _T("");
		m_filename				= _T("");
		m_path					= _T("");
		m_pathtype				= _T("");
		m_template				= _T("");
		m_templatefile			= _T("");
		m_templateproperties	= _T("");
		m_classview				= _T("");
		m_classviewpluginfile	= _T("");
		m_classdoc				= _T("");
		m_classdocfile			= _T("");
		m_propertyfile			= _T("");
		m_type					= _T("");
		m_folderid				= _T("");
		m_icon					= _T("");
		m_category				= _T("");
		m_description			= _T("");

		m_numeric				= -1;

		m_treenode				= NULL;
		m_changed				= false;
		m_project				= NULL;

		m_properties.RemoveAll();

		m_dependencies.RemoveAllItems();
		m_dependencies.RemoveAllNodes();
	}

private:
	CString							m_name;
	CString							m_version;
	CString							m_filename;
	CString							m_path;
	CString							m_pathtype;
	CString							m_type;
	CString							m_template;
	CString							m_templatefile;
	CString							m_templateproperties;
	CString							m_classview;
	CString							m_classviewpluginfile;
	CString							m_classdoc;
	CString							m_classdocfile;
	CString							m_propertyfile;
	CString							m_folderid;
	CString							m_icon;
	CString							m_category;
	CString							m_description;

	int								m_numeric;
	bool							m_changed;

	void*							m_project;

	CSHLTreeNode<CItemEntity>		m_dependencies;

	HTREEITEM						m_treenode;

	PROPERTYVALUE					m_properties;
};
