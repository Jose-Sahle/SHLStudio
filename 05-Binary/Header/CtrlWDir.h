/*****************************************************************************
 * Arquivo: wdir.h                                                           *
 * Declara um tipo de dados tipo "cadeia de caracteres"                      *
 * Data:24/09/97                                                             *
 *****************************************************************************/
 
#if !defined(__DIR_H) // Garante que o arquivo é incluído somente uma vez.
 
#define __DIR_H

#include <io.h>
#include <afx.h>
#include <errno.h>
#include <atlcomtime.h>
#include <library.h>
#include "SHLTreeNode.h"

const DWORD WM_ITEMADDED = WM_USER + 100;

class CDir : public ICtrlDir
{
    public:
	    // Construtores da Classe.
	    CDir();
	    //CDir(const CDir &dir);
	    
	    // Destrutor
	    virtual ~CDir();
	    
		/* Função para posicionar nome com o primeiro diretório da lista */	
		void MoveFirst(void);
		
		/* Função para posicionar o último diretório da lista */
		void MoveLast(void);
		
		/* Função para posicionar no próximo diretório da lista */
		void MoveNext(void);
		
		/* Função para posicionar no diretório anterior da lista */
		void MovePrevious(void);
		
		/* Função que retorna o nome do arquivo ou o nome do arquivo extendido */
		CString GetName(void);
		CString GetExName(void);
		
		/* Retorna verdadeiro se alcançou o inicio do lista */
		Boolean Bof(void);

		/* Retorna verdadeiro se alcançou o fim do lista */
		Boolean Eof(void);
		
		/* Função que retorna a quantidade de elementos na lista de diretórios */
		int GetQtd(void);
		int GetQtdDir(void);
		int GetQtdArq(void);
		
		/* Função que refaz a lista de diretório de acordo com a propriedade mascara */
		void Refresh(void);
		void Add(void);
		
		/* Função que retorna o elemento posicionado */
		int Position(void);
		
		/* Função que adiciona um nome na lista */
		void PutDir(const CString& Diretorio);
		void PutDir(const CString& Diretorio, UINT Atributo, BYTE Moresub, int Tipo);
		void PutDir(const CString& Diretorio, UINT Atributo, BYTE Moresub, int Tipo, DWORD FileLength);
		/* Função que retorna o tamanho da string do nome do arquivo e do nome do arquivo extendido */
		int GetLength(void);
		int GetExLength(void);

		BOOL IsFolder();

		/* Função que retorna o tamanho do arquivo */
		DWORD GetFileLength(void);

		/* Função que retorna verdadeiro se existem subdiretórios ou false se não */
		Boolean HasMoreSub(void);

		/* Função que retorna o atributo do arquivo ou diretório */
		int GetAttrib(void);

		/* Função que retorna o nome o diretório pai */
		CString GetParent(void);
		CString GetExParent(void);

		/* Função que limpa todo o conteúdo da classe */
		void Clear(void);

		/* Configura a filtro de busca */
		void SetFilter(CString filter);

		/* Configura a máscara de busca */
		void SetMask(CString mask);

		/* Determina se a busca incluirá sub-diretórios */
		void SetSearchInSub(BOOL includeSubDir);

		/* Configura se a inclui o diretório contido na máscara */
		void SetIncludeMask(BOOL includeMask);

		/* Configura o tipo de busca DIRETÓRIO ou ARQUIVO */
		void SetType(int TipoBusca);

		/* Configura a variável que determina se a consulta terá como condição uma faixa de datas */
		void SetUseDate(BOOL selectByDate);

		/* Configura as faixas de datas para a consulta */
		void SetDate(COleDateTime mindate, COleDateTime maxdate);

		/* Retorna um ponteiro para a classe de Nós */
		CSHLTreeNode<FILEPATHINFO>* GetFilePathInfo();

		/* Excluir a instancia */
		void Release();

	private:                  
		/* Dados publicos da Classe */
	    CString m_Mask;          // Máscara ou caminho a ser utilizado para montar
	                             // a lista de diretórios
		CString m_Filter;		 // Filtro de arquivo
        short m_TipoBusca;       // Tipo dos elementos "Dir" ou "ARCHIVE"
	    BOOL m_includeSubDir;    // Busca em sub-diretórios
		BOOL m_IncludeMask;      // Se for TRUE o diretório contido na mascará será incluso
		BOOL m_SelectByDate;	 // Determina que datas serão consideradas
		COleDateTime m_MinDate;	 // Data Inicial que será considerada
		COleDateTime m_MaxDate;	 // Data Final que será considerada

		void Subdiretorio(CSHLTreeNode<FILEPATHINFO>* parentnode, CString pict);
		Boolean DoRefresh(void);

		CStringArray caminho;     // Matriz de CString que guarda o nome do arquivo ou diretório
		CUIntArray atributo;      // Matriz de UINT para guardar o atributo do arquivo
		CByteArray moresub;       // Matriz que indentifica se há mais subdiretórios
		CDWordArray filelength;   // Matriz que indica o tamanho do arquivo

        Boolean _eof;             // Fim da lista de diretórios
        Boolean _bof;             // Inicio da lista de diretórios

    	int m_qtd;                // Guarda a quantidade todal de diretórios e arquivos da lista
		int m_qtddir;             // Guarda a quantidade de diretórios
		int m_qtdarq;             // Guarda a quantidade de arquivos
    	int m_Element;             // Elemento em que se está posicionado na matriz de
    					          // Diretório		
		CSHLTreeNode<FILEPATHINFO> m_treeNode;
};

#endif
