#pragma once

#pragma once

#include "stdafx.h"
#include "Property.h"

class CDependencyEntity
{
public:
	CDependencyEntity(){Reset();}

	virtual ~CDependencyEntity(){Reset();};

// Propriedades
public:
 	PROPERTY(CString, Name);
  	GET(Name) 
 	{ 
 		return m_name; 
	}
 	SET(Name)
 	{
 		m_name = value;
 	} 

 	PROPERTY(CString, Icon);
  	GET(Icon) 
 	{ 
 		return m_icon; 
	}
 	SET(Icon)
 	{
 		m_icon = value;
 	} 

 	PROPERTY(HTREEITEM, TreeItem);
  	GET(TreeItem) 
 	{ 
 		return m_treeitem; 
	}
 	SET(TreeItem)
 	{
 		m_treeitem = value;
 	} 

 	PROPERTY(bool, Changed);
  	GET(Changed) 
 	{ 
 		return m_changed; 
	}
 	SET(Changed)
 	{
 		m_changed = value;
 	} 

 	READONLY_PROPERTY(PROPERTYVALUE&, Properties);
  	GET(Properties) 
 	{ 
 		return m_properties; 
	}

	void Reset()
	{
		m_name		= _T("");
		m_icon		= _T("");
		m_treeitem	= NULL;
		m_changed	= false;
		m_properties.RemoveAll();
	}

// Membros Privados
private:
	CString			m_name;
	CString			m_id;
	CString			m_type;
	CString			m_parent;
	CString			m_icon;
	HTREEITEM		m_treeitem;
	bool			m_changed;
	PROPERTYVALUE	m_properties;
};