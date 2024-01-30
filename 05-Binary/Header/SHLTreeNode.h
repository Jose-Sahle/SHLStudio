/*****************************************************************************
 * Arquivo: SHLTreeNode.h                                                    *
 *                                                                           *
 * Classe template na forma de TreeNodes onde cada Node pode conter          *
 * item ou outros nodes, assim sucessivamente.                               *
 * O tipo do ITEM é definido pelo template.                                  *
 * Será incluído ponteiros de objetos indicados no template que serão        *
 * liberados automaticamente pelo controle SHLTreeNode.                      *
 *                                                                           *
 * Data:29/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "Property.h"

template<typename T>
class CSHLTreeNode
{

public:
	CSHLTreeNode();
	CSHLTreeNode(CString name);
	CSHLTreeNode(CSHLTreeNode<T>* parent);
	virtual ~CSHLTreeNode();

	ULONGLONG AddNode(CSHLTreeNode<T>* node);
	//ULONGLONG InsertNodeBefore(ULONGLONG key, CSHLTreeNode<T>* node);
	//ULONGLONG InsertNodeAfter(ULONGLONG key, CSHLTreeNode<T>* node);

	ULONGLONG RemoveNodeAt(ULONGLONG key, bool freeit = true);
	void RemoveAllNodes(bool freeit = true);
	ULONGLONG  RemoveNode(CSHLTreeNode<T>* node, bool freeit = true);

	ULONGLONG GetNodeCount();
	CSHLTreeNode<T>* GetNodeAt(ULONGLONG key);

	ULONGLONG AddItem(T* item);
	//ULONGLONG InsertItemBefore(ULONGLONG key, T* item);
	//ULONGLONG InsertItemAfter(ULONGLONG key, T* item);

	ULONGLONG RemoveItemAt(ULONGLONG key, bool freeit = true);
	void RemoveAllItems(bool freeit = true);
	ULONGLONG  RemoveItem(T* item, bool freeit = true);

	ULONGLONG GetItemCount();
	T* GetItemAt(ULONGLONG key);

// Properties
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

 	PROPERTY(CSHLTreeNode<T>*, Parent)
  	GET(Parent) 
 	{ 
 		return m_parent; 
	}
 	SET(Parent)
 	{
 		m_parent = value;
 	} 

 	PROPERTY(CSHLTreeNode<T>**, Children)
  	GET(Children) 
 	{ 
 		return m_parent; 
	}
 	SET(Children)
 	{
 		m_parent = value;
 	} 

 	PROPERTY(T**, Items)
  	GET(Items) 
 	{ 
 		return m_items; 
	}
 	SET(Items)
 	{
 		m_items = value;
 	} 

 	READONLY_PROPERTY(BOOL, HasChild)
  	GET(HasChild) 
 	{ 
 		return m_countnode > 0; 
	}

// Private Member
private:
	ULONGLONG m_countitem;
	ULONGLONG m_countnode;

	CString m_name;
	CSHLTreeNode<T>* m_parent;
	CSHLTreeNode<T>** m_children;
	T** m_items;

	void MoveNode(CSHLTreeNode<T>** newNodeArray, CSHLTreeNode<T>** NodeArray, ULONGLONG keyNewStart, ULONGLONG keyActualStart, ULONGLONG keyActualEnd, ULONGLONG sizeNew, ULONGLONG sizaActual);
	void MoveItem(T** newItemArray, T** ItemArray, ULONGLONG keyNewStart, ULONGLONG keyActualStart, ULONGLONG keyActualEnd, ULONGLONG sizeNew, ULONGLONG sizaActual);

	void InvalidateNodeChildren(ULONGLONG size);
	void InvalidateItem(ULONGLONG size);
};

/* *********************************************************

	CSHLTree implementation

************************************************************ */
template<typename T>
CSHLTreeNode<T>::CSHLTreeNode()
{ 
	m_countitem		= 0;
	m_countnode		= 0;

	m_parent		= NULL;
	m_children		= NULL;
	m_items			= NULL;

	m_name			= _T("");
}

template<typename T>
CSHLTreeNode<T>::CSHLTreeNode(CString name)
{ 
	m_countitem		= 0;
	m_countnode		= 0;

	m_parent		= NULL;
	m_children		= NULL;
	m_items			= NULL;

	m_name			= name;
}

template<typename T>
CSHLTreeNode<T>::CSHLTreeNode(CSHLTreeNode<T>* parent)
{ 
	m_countitem		= 0;
	m_countnode		= 0;

	m_parent		= parent;
	m_children		= NULL;
	m_items			= NULL;
}

template<typename T>
CSHLTreeNode<T>::~CSHLTreeNode()
{ 
	RemoveAllItems();
	RemoveAllNodes();
}

#pragma region NODE
template<typename T>
ULONGLONG CSHLTreeNode<T>::AddNode(CSHLTreeNode<T>* node)
{
	for(ULONGLONG nIndex = 0; nIndex < m_countnode; nIndex++)
	{
		if(m_children[nIndex]->Name == node->Name)
			return -1;
	}

	m_countnode++;

	CSHLTreeNode<T>** newNodeArray = new CSHLTreeNode<T>*[m_countnode];

	if(m_children)
		MoveNode(newNodeArray, m_children, 0, 0, (m_countnode-2), m_countnode, (m_countnode-1) );

	InvalidateNodeChildren((m_countnode-1));
	newNodeArray[m_countnode-1] = node;

	node->Parent = this;

	m_children = newNodeArray;
	
	return (m_countnode-1);
}

template<typename T>
ULONGLONG CSHLTreeNode<T>::RemoveNodeAt(ULONGLONG key, bool freeit)
{
	CSHLTreeNode<T>* nodeToDelete;

	if(!m_children)
		return -1;

	CSHLTreeNode<T>** newNodeArray = NULL;
	m_countnode--;

	nodeToDelete = m_children[key];

	if(m_countnode)
	{
		newNodeArray = new CSHLTreeNode<T>*[m_countnode];

		MoveNode(newNodeArray, m_children,   0,     0,       key-1, m_countnode, (m_countnode+1)); 
		MoveNode(newNodeArray, m_children, key, key+1, m_countnode, m_countnode, (m_countnode+1)); 
	}

	if(freeit)
		delete nodeToDelete;

	InvalidateNodeChildren((m_countnode+1));

	m_children = newNodeArray;

	return m_countnode;
}

template<typename T>
ULONGLONG CSHLTreeNode<T>::RemoveNode(CSHLTreeNode<T>* nodeToDelete, bool freeit)
{
	INT key;

	if(!m_children)
		return -1;

	if(!m_countnode)
		return -1;

	for(ULONGLONG nindex = 0; nindex < m_countitem; nindex++)
	{
		if(dynamic_cast<const void*>(nodeToDelete) ==  dynamic_cast<const void*>(m_children[nindex]))
		{
			key = nindex;
			break;
		}
	}

	return RemoveNodeAt(key);
}

template<typename T>
void CSHLTreeNode<T>::RemoveAllNodes(bool freeit)
{
	if(!m_children)
		return;

	for(ULONGLONG nIndex = 0; nIndex < m_countnode; nIndex++)
	{
		if(freeit && m_children[nIndex])
			delete m_children[nIndex];
	}

	InvalidateNodeChildren((m_countnode));

	m_countnode = 0;
	m_children = NULL;
}

template<typename T>
ULONGLONG CSHLTreeNode<T>::GetNodeCount()
{
	return m_countnode;
}

template<typename T>
CSHLTreeNode<T>* CSHLTreeNode<T>::GetNodeAt(ULONGLONG key)
{
	return m_children[key];
}

template<typename T>
void CSHLTreeNode<T>::MoveNode(CSHLTreeNode<T>** newNodeArray, CSHLTreeNode<T>** NodeArray, ULONGLONG keyNewStart, ULONGLONG keyActualStart, ULONGLONG keyActualEnd, ULONGLONG sizeNew, ULONGLONG sizeActual)
{
	if((keyActualEnd - keyActualStart > sizeNew) || (keyActualEnd >= sizeActual) || (keyActualEnd == (ULONGLONG)-1))
		return;

	for(ULONGLONG nIndex = keyActualStart; nIndex <= keyActualEnd; nIndex++)
	{
		newNodeArray[keyNewStart] = NodeArray[nIndex];
		keyNewStart++;
	}
}

template<typename T>
void CSHLTreeNode<T>::InvalidateNodeChildren(ULONGLONG size)
{
	if(!m_children)
		return;

	for(ULONGLONG nIndex = 0; nIndex < size; nIndex++)
		m_children[nIndex] = NULL;

	delete[] m_children;

	m_children = NULL;
}
#pragma endregion NODE


#pragma region ITEMS
template<typename T>
ULONGLONG CSHLTreeNode<T>::AddItem(T* item)
{
	m_countitem++;

	T** newItemArray = new T*[m_countitem];

	if(m_items)
		MoveItem(newItemArray, m_items, 0, 0, (m_countitem-2), m_countitem, m_countitem-1);

	newItemArray[m_countitem-1] = item;

	InvalidateItem(m_countitem-1);

	m_items = newItemArray;

	return (m_countitem-1);
}

template<typename T>
ULONGLONG CSHLTreeNode<T>::RemoveItemAt(ULONGLONG key, bool freeit)
{
	T* itemToDelete;

	if(!m_items)
		return -1;

	T** newItemArray = NULL;
	m_countitem--;

	itemToDelete = m_items[key];

	if(m_countitem)
	{
		newItemArray = new T*[m_countitem];

		MoveItem(newItemArray, m_items,   0,     0,        key-1, m_countitem, (m_countitem+1)); 
		MoveItem(newItemArray, m_items, key, key+1,  m_countitem, m_countitem, (m_countitem+1)); 
	}

	if(freeit)
		delete itemToDelete;

	InvalidateItem(m_countitem+1);

	m_items = newItemArray;

	return m_countitem;
}

template<typename T>
ULONGLONG CSHLTreeNode<T>::RemoveItem(T* itemToDelete, bool freeit)
{
	ULONGLONG key;

	if(!m_items)
		return -1;

	if(!m_countitem)
		return -1;

	for(ULONGLONG nindex = 0; nindex < m_countitem; nindex++)
	{
		if(dynamic_cast<const void*>(itemToDelete) ==  dynamic_cast<const void*>(m_items[nindex]))
		{
			key = nindex;
			break;
		}
	}

	return RemoveItemAt(key);
}

template<typename T>
ULONGLONG CSHLTreeNode<T>::GetItemCount()
{
	return m_countitem;
}

template<typename T>
T* CSHLTreeNode<T>::GetItemAt(ULONGLONG key)
{
	return m_items[key];
}

template<typename T>
void CSHLTreeNode<T>::RemoveAllItems(bool freeit)
{
	if(!m_items)
		return;

	for(ULONGLONG nIndex = 0; nIndex < m_countitem; nIndex++)
	{
		if (freeit && m_items[nIndex])
			delete m_items[nIndex];
	}

	InvalidateItem(m_countitem);

	m_countitem = 0;
	m_items = NULL;
}

template<typename T>
void CSHLTreeNode<T>::MoveItem(T** newItemArray, T** ItemArray, ULONGLONG keyNewStart, ULONGLONG keyActualStart, ULONGLONG keyActualEnd, ULONGLONG sizeNew, ULONGLONG sizeActual)
{
	if((keyActualEnd - keyActualStart > sizeNew) || (keyActualEnd >= sizeActual) || (keyActualEnd == (ULONGLONG)-1))
		return;

	for(ULONGLONG nIndex = keyActualStart; nIndex <= keyActualEnd; nIndex++)
	{
		newItemArray[keyNewStart] = ItemArray[nIndex];
		keyNewStart++;
	}
}

template<typename T>
void CSHLTreeNode<T>::InvalidateItem(ULONGLONG size)
{
	if(!m_items)
		return;

	//for(ULONGLONG nIndex = 0; nIndex < size; nIndex++)
	//	m_items[nIndex] = NULL;

	delete[] m_items;

	m_items = NULL;
}

#pragma endregion ITEMS
