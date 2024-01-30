/*****************************************************************************
 * Arquivo: wdir.h                                                           *
 * Declara um tipo de dados tipo "cadeia de caracteres"                      *
 * Data:24/09/97                                                             *
 *****************************************************************************/
#pragma once

#include <library.h>
#include "SHLTreeNode.h"
#include "FileDirectoryInfo.h"

#ifdef SHLDIR_EXPORTS
	#define SHLDIR_API __declspec(dllexport)
#else
	#define SHLDIR_API __declspec(dllimport)
#endif

using namespace std;

class ICtrlDir
{
    public:    
		typedef void(*CALLBACK_CTRLDIR_ROUTINE)(char *name, void* object, BOOL isFolder);
		typedef CALLBACK_CTRLDIR_ROUTINE LPCALLBACK_CTRLDIR_ROUTINE;

		/* Fun��o para posicionar nome com o primeiro diret�rio da lista */
		virtual void MoveFirst(void)=0;
		
		/* Fun��o para posicionar o �ltimo diret�rio da lista */
		virtual void MoveLast(void)=0;
		
		/* Fun��o para posicionar no pr�ximo diret�rio da lista */
		virtual void MoveNext(void)=0;
		
		/* Fun��o para posicionar no diret�rio anterior da lista */
		virtual void MovePrevious(void)=0;

		/* Fun��o para posicionar um elemento da lista */
		virtual int MoveAt(int pos) = 0;

		/* Fun��o que retorna o nome do arquivo ou o nome do arquivo extendido */
		virtual CString GetName(void)=0;
		virtual CString GetExName(void)=0;

		virtual BOOL IsFolder()=0;
		
		/* Retorna verdadeiro se alcan�ou o inicio do lista */
		virtual Boolean Bof(void)=0;

		/* Retorna verdadeiro se alcan�ou o fim do lista */
		virtual Boolean Eof(void)=0;
		
		/* Fun��o que retorna a quantidade de elementos na lista de diret�rios */
		virtual int GetQtd(void)=0;
		virtual int GetQtdDir(void)=0;
		virtual int GetQtdArq(void)=0;
		
		/* Fun��o que refaz a lista de diret�rio de acordo com a propriedade mascara */
		virtual void Refresh(void)=0;
		virtual void Add(void)=0;
		
		/* Fun��o que retorna o elemento posicionado */
		virtual int Position(void)=0;
		
		/* Fun��o que adiciona um nome na lista */
		virtual void PutDir(const CString& Diretorio)=0;
		virtual void PutDir(const CString& Diretorio, UINT Atributo, BYTE Moresub, int Tipo)=0;
		virtual void PutDir(const CString& Diretorio, UINT Atributo, BYTE Moresub, int Tipo, DWORD FileLength)=0;
		
		/* Fun��o que retorna o tamanho da string do nome do arquivo e do nome do arquivo extendido */
		virtual int GetLength(void)=0;
		virtual int GetExLength(void)=0;

		/* Fun��o que retorna o tamanho do arquivo */
		virtual DWORD GetFileLength(void)=0;

		/* Fun��o que retorna verdadeiro se existem subdiret�rios ou false se n�o */
		virtual Boolean HasMoreSub(void)=0;

		/* Fun��o que retorna o atributo do arquivo ou diret�rio */
		virtual int GetAttrib(void)=0;

		/* Fun��o que retorna o nome o diret�rio pai */
		virtual CString GetParent(void)=0;
		virtual CString GetExParent(void)=0;

		/* Fun��o que limpa todo o conte�do da classe */
		virtual void Clear(void)=0;

		/* Configura a filtro de busca */
		virtual void SetFilter(CString filter)=0;

		/* Configura a m�scara de busca */
		virtual void SetMask(CString mask)=0;

		/* Determina se a busca incluir� sub-diret�rios */
		virtual void SetSearchInSub(BOOL includeSubDir)=0;

		/* Configura se a inclui o diret�rio contido na m�scara */
		virtual void SetIncludeMask(BOOL includeMask)=0;

		/* Configura o tipo de busca DIRET�RIO ou ARQUIVO */
		virtual void SetType(int TipoBusca)=0;

		/* Configura a vari�vel que determina se a consulta ter� como condi��o uma faixa de datas */
		virtual void SetUseDate(BOOL selectByDate)=0;

		/* Configura as faixas de datas para a consulta */
		virtual void SetDate(COleDateTime mindate, COleDateTime maxdate)=0;

		/* Retorna um ponteiro para a classe de N�s */
		virtual CSHLTreeNode<FILEPATHINFO>* GetFilePathInfo()=0;

		/* Release this instance */
		virtual void Release() = 0;

		virtual void SetSignal(int pos, BOOL signal) = 0;
		virtual BOOL IsSignaled(int pos) = 0;
		virtual void SetSignal(BOOL signal) = 0;
		virtual BOOL IsSignaled() = 0;
		virtual void SetClearBeforeResult(BOOL value)=0;
		virtual void AddTag(CString text) = 0;
		virtual void AddTag(int pos, CString text) = 0;
		virtual CString GetTag() = 0;
		virtual CString GetTag(int pos) = 0;
		virtual int GetCurrentPos() = 0;

		void SetCallBack(void* lpCallbackRoutine, void* lpObject)
		{
			LPCallbackRoutine = (LPCALLBACK_CTRLDIR_ROUTINE)lpCallbackRoutine;
			object = lpObject;
		}

		LPCALLBACK_CTRLDIR_ROUTINE LPCallbackRoutine;
		void* object;
};

typedef ICtrlDir*	CTRLDIRHANDLE;

#ifdef __cplusplus
#   define EXTERN_C     extern "C"
#else
#   define EXTERN_C
#endif // __cplusplus

EXTERN_C SHLDIR_API CTRLDIRHANDLE WINAPI GetCtrlDirInstance();

#ifndef SHLSTUDIOPROJECT_EXPORTS
	#include "AutoClosePtr.h"
	typedef AutoClosePtr<ICtrlDir, void, &ICtrlDir::Release> ICtrlDirPtr;
	typedef CTRLDIRHANDLE (WINAPI* LPFNGETCTRLDIRINSTANCE)();	                               
#endif
