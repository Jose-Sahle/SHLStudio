/*****************************************************************************
 * Arquivo: GUID.h                                                           *
 *                                                                           *
 * Classe que cria um número do tipo GUID.                                   *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "stdafx.h"
#include <afxwin.h>         // MFC core and standard components
#include <afxcmn.h>
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
#include "Property.h"
#include "Library.h"

class CGUID
{
public:
	CGUID(){ Reset(); };

	GUID NewGuid()
	{
		GUID guid;
		#if UNICODE
			RPC_WSTR guidStr;
		#else
			RPC_CSTR guidStr;
		#endif
		HRESULT hr = NULL;

		try
		{
			m_strError = _T("");
			hr = CoCreateGuid(&guid);
			if (hr == S_OK)
			{
				if(UuidToString(&guid, &guidStr) == RPC_S_OK)
				{
					m_guidstr = (LPTSTR)guidStr;
					RpcStringFree(&guidStr);
				}
			}
		}
		catch(CException* ex)
		{
			TCHAR szMessage[4000];

			BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

			m_strError =  szMessage;
		}
		catch(...)
		{
			m_strError.Format(_T("%s"), ErrorMessage(::GetLastError()));
		}
		return guid;
	}

	void Reset()
	{
		m_guid.Data1 = 0;
		m_guid.Data2 = 0;
		m_guid.Data3 = 0;
		memset(m_guid.Data4, 0, 8);
		m_strError = _T("");
	}

public:
 	PROPERTY(GUID, Guid);
  	GET(Guid) 
 	{ 
 		return m_guid; 
	}
 	SET(Guid)
 	{
 		m_guid = value;
 	} 

 	READONLY_PROPERTY(CString, GuidString);
  	GET(GuidString) 
 	{ 
 		return m_guidstr; 
	}

 	READONLY_PROPERTY(CString, Error);
  	GET(Error) 
 	{ 
 		return m_strError; 
	}
 	SET(Error)
 	{
 		m_strError = value;
 	} 

private:
	GUID		m_guid;
	CString		m_guidstr;
	CString		m_strError;
};