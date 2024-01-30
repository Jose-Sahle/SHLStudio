/*****************************************************************************
 * Arquivo: wdir.h                                                           *
 * Declara um tipo de dados tipo "cadeia de caracteres"                      *
 * Data:24/09/97                                                             *
 *****************************************************************************/
 
#if !defined(__DIR_H) // Garante que o arquivo � inclu�do somente uma vez.
 
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
	    
		/* Fun��o para posicionar nome com o primeiro diret�rio da lista */	
		void MoveFirst(void);
		
		/* Fun��o para posicionar o �ltimo diret�rio da lista */
		void MoveLast(void);
		
		/* Fun��o para posicionar no pr�ximo diret�rio da lista */
		void MoveNext(void);
		
		/* Fun��o para posicionar no diret�rio anterior da lista */
		void MovePrevious(void);
		
		/* Fun��o que retorna o nome do arquivo ou o nome do arquivo extendido */
		CString GetName(void);
		CString GetExName(void);
		
		/* Retorna verdadeiro se alcan�ou o inicio do lista */
		Boolean Bof(void);

		/* Retorna verdadeiro se alcan�ou o fim do lista */
		Boolean Eof(void);
		
		/* Fun��o que retorna a quantidade de elementos na lista de diret�rios */
		int GetQtd(void);
		int GetQtdDir(void);
		int GetQtdArq(void);
		
		/* Fun��o que refaz a lista de diret�rio de acordo com a propriedade mascara */
		void Refresh(void);
		void Add(void);
		
		/* Fun��o que retorna o elemento posicionado */
		int Position(void);
		
		/* Fun��o que adiciona um nome na lista */
		void PutDir(const CString& Diretorio);
		void PutDir(const CString& Diretorio, UINT Atributo, BYTE Moresub, int Tipo);
		void PutDir(const CString& Diretorio, UINT Atributo, BYTE Moresub, int Tipo, DWORD FileLength);
		/* Fun��o que retorna o tamanho da string do nome do arquivo e do nome do arquivo extendido */
		int GetLength(void);
		int GetExLength(void);

		BOOL IsFolder();

		/* Fun��o que retorna o tamanho do arquivo */
		DWORD GetFileLength(void);

		/* Fun��o que retorna verdadeiro se existem subdiret�rios ou false se n�o */
		Boolean HasMoreSub(void);

		/* Fun��o que retorna o atributo do arquivo ou diret�rio */
		int GetAttrib(void);

		/* Fun��o que retorna o nome o diret�rio pai */
		CString GetParent(void);
		CString GetExParent(void);

		/* Fun��o que limpa todo o conte�do da classe */
		void Clear(void);

		/* Configura a filtro de busca */
		void SetFilter(CString filter);

		/* Configura a m�scara de busca */
		void SetMask(CString mask);

		/* Determina se a busca incluir� sub-diret�rios */
		void SetSearchInSub(BOOL includeSubDir);

		/* Configura se a inclui o diret�rio contido na m�scara */
		void SetIncludeMask(BOOL includeMask);

		/* Configura o tipo de busca DIRET�RIO ou ARQUIVO */
		void SetType(int TipoBusca);

		/* Configura a vari�vel que determina se a consulta ter� como condi��o uma faixa de datas */
		void SetUseDate(BOOL selectByDate);

		/* Configura as faixas de datas para a consulta */
		void SetDate(COleDateTime mindate, COleDateTime maxdate);

		/* Retorna um ponteiro para a classe de N�s */
		CSHLTreeNode<FILEPATHINFO>* GetFilePathInfo();

		/* Excluir a instancia */
		void Release();

	private:                  
		/* Dados publicos da Classe */
	    CString m_Mask;          // M�scara ou caminho a ser utilizado para montar
	                             // a lista de diret�rios
		CString m_Filter;		 // Filtro de arquivo
        short m_TipoBusca;       // Tipo dos elementos "Dir" ou "ARCHIVE"
	    BOOL m_includeSubDir;    // Busca em sub-diret�rios
		BOOL m_IncludeMask;      // Se for TRUE o diret�rio contido na mascar� ser� incluso
		BOOL m_SelectByDate;	 // Determina que datas ser�o consideradas
		COleDateTime m_MinDate;	 // Data Inicial que ser� considerada
		COleDateTime m_MaxDate;	 // Data Final que ser� considerada

		void Subdiretorio(CSHLTreeNode<FILEPATHINFO>* parentnode, CString pict);
		Boolean DoRefresh(void);

		CStringArray caminho;     // Matriz de CString que guarda o nome do arquivo ou diret�rio
		CUIntArray atributo;      // Matriz de UINT para guardar o atributo do arquivo
		CByteArray moresub;       // Matriz que indentifica se h� mais subdiret�rios
		CDWordArray filelength;   // Matriz que indica o tamanho do arquivo

        Boolean _eof;             // Fim da lista de diret�rios
        Boolean _bof;             // Inicio da lista de diret�rios

    	int m_qtd;                // Guarda a quantidade todal de diret�rios e arquivos da lista
		int m_qtddir;             // Guarda a quantidade de diret�rios
		int m_qtdarq;             // Guarda a quantidade de arquivos
    	int m_Element;             // Elemento em que se est� posicionado na matriz de
    					          // Diret�rio		
		CSHLTreeNode<FILEPATHINFO> m_treeNode;
};

#endif
