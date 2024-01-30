#pragma once

#include "stdafx.h"
#include "afxpropertygridctrl.h"
#include "Property.h"
#include "Path.h"

class CMFCPropertyGridPropertyMask : public CMFCPropertyGridProperty
{
public:
	// Simple property
	CMFCPropertyGridPropertyMask(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL);

	virtual ~CMFCPropertyGridPropertyMask();

	// Properties
public:
 	PROPERTY(CString, Tag);
  	GET(Tag) 
 	{ 
 		return m_strTag; 
	}
 	SET(Tag)
 	{
 		m_strTag = value;
 	} 

 	PROPERTY(CString, PasswordChar);
  	GET(PasswordChar) 
 	{ 
 		return m_strPasswordChar; 
	}
 	SET(PasswordChar)
 	{
 		m_strPasswordChar = value;
 	} 

 	PROPERTY(BOOL, IsFolder);
  	GET(IsFolder) 
 	{ 
 		return m_bIsFolder; 
	}
 	SET(IsFolder)
 	{
 		m_bIsFolder = value;
 	} 

 	PROPERTY(BOOL, HASBUTTON);
  	GET(HASBUTTON) 
 	{ 
 		return m_bHasButton; 
	}
 	SET(HASBUTTON)
 	{
 		m_bHasButton = value;
 	} 

 	PROPERTY(BOOL, IsRelative);
  	GET(IsRelative) 
 	{ 
 		return m_bIsRelative; 
	}
 	SET(IsRelative)
 	{
 		m_bIsRelative = value;
 	} 

 	PROPERTY(CString, Relationship);
  	GET(Relationship) 
 	{ 
 		return m_strRelationshipProperty; 
	}
 	SET(Relationship)
 	{
 		m_strRelationshipProperty = value;
 	} 

 	PROPERTY(CString, BaseFolder);
  	GET(BaseFolder) 
 	{ 
 		return m_BaseFolder; 
	}
 	SET(BaseFolder)
 	{
 		m_BaseFolder = value;
 	} 

 	PROPERTY(CMFCPropertyGridProperty*, GroupParent);
  	GET(GroupParent) 
 	{ 
 		return m_pGroupParent; 
	}
 	SET(GroupParent)
 	{
 		m_pGroupParent = value;
 	} 

 	PROPERTY(CString, ValidChars);
  	GET(ValidChars) 
 	{ 
 		return m_strValidChars; 
	}
 	SET(ValidChars)
 	{
 		m_strValidChars = value;
 	} 

protected:
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual CString FormatProperty();
	virtual void OnClickButton(CPoint point);
	virtual BOOL OnUpdateValue();
	virtual BOOL HasButton() const;
	

	CString m_strPasswordChar;
	CString m_strTag;
	CString m_strRelationshipProperty;
	CString	m_BaseFolder;
	BOOL	m_bIsFolder;
	BOOL	m_bIsRelative;
	BOOL	m_bHasButton;
	CMFCPropertyGridProperty* m_pGroupParent;

	BOOL m_jump;
};

