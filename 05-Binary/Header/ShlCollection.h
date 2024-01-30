/*****************************************************************************
 * Arquivo: Collection.h                                                     *
 *                                                                           *
 *                                                                           *
 * Data:21/01/2017                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <list>
#include <iostream> 
#include "Property.h"

template<typename T>
class CSHLList
{

public:
	CSHLList();
	~CSHLList();

	ULONGLONG Add(T* item);

	ULONGLONG RemoveAt(ULONGLONG key, bool freeit = true);
	void RemoveAll(bool freeit = true);
	ULONGLONG  Remove(T* item, bool freeit = true);

	ULONGLONG GetCount();
	T* GetAt(ULONGLONG key);

// Private Member
private:
	std::list<T*>	m_list;
};

/* *********************************************************

	CSHLList implementation

************************************************************ */
template<typename T>
CSHLList<T>::CSHLList()
{ 
}

template<typename T>
CSHLList<T>::~CSHLList()
{ 
	RemoveAll();
}

#pragma region ITEMS
template<typename T>
ULONGLONG CSHLList<T>::Add(T* item)
{
	m_list.push_back(item);

	return (m_list.size()-1);
}

template<typename T>
ULONGLONG CSHLList<T>::RemoveAt(ULONGLONG key, bool freeit)
{
	T* itemToDelete;

	if (m_list.size() == 0)
		return -1;

	std::list<T*>::iterator ite = m_list.begin();
	std::advance(ite, key);
	itemToDelete = *ite;

	m_list.erase(ite);

	if(freeit)
		delete itemToDelete;

	return m_list.size();
}

template<typename T>
ULONGLONG CSHLList<T>::Remove(T* itemToDelete, bool freeit)
{
	ULONGLONG key;

	if (m_list.size() == 0)
		return -1;

	m_list.erase(itemToDelete);

	if (freeit)
		delete itemToDelete;

	return m_list.size();
}

template<typename T>
void CSHLList<T>::RemoveAll(bool freeit)
{
	if (m_list.size() == 0)
		return;

	if (freeit)
	{
		for (auto&& item : m_list)
			delete item;
	}
	m_list.clear();
}

template<typename T>
ULONGLONG CSHLList<T>::GetCount()
{
	return m_list.size();
}

template<typename T>
T* CSHLList<T>::GetAt(ULONGLONG key)
{
	T* item;

	if (m_list.size() == 0)
		return NULL;

	std::list<T*>::iterator ite = m_list.begin();
	std::advance(ite, key);
	item = *ite;

	return item;
}
#pragma endregion ITEMS
