/*****************************************************************************
 * Arquivo: WFread.h                                                         *
 * Define classe para entrada e saida em arquivo.                            *
 * Data:24/09/97                                                             *
 *****************************************************************************/

#if !defined(__CFread_H)

#define __CFread_H

#include <stdio.h>
#include "Library.h"

const int RATEGROW = 256;

typedef enum _shlopentype
{
	SHLOPENTYPE_BINARY,
	SHLOPENTYPE_TEXT,
	SHLOPENTYPE_LENGTH
}SHLOPENTYPE;

class CFread
{
	public:
		// Construtores
		CFread(void);
		CFread(const CString filename, SHLOPENTYPE type = SHLOPENTYPE_TEXT, INT maxlinelegth = 0);
		CFread(const CFread &filecopy); //Construtor de C�pia

		// Destrutor
		~CFread();
		
		/* Defini��es das fun��es membros da classe */
		// Fun��o usada para abrir um arquivo.
		bool Open(const CString filename, SHLOPENTYPE type = SHLOPENTYPE_TEXT, int maxlinelegth = 0); 

		// Fun��o que cria e abre um arquivo.
		bool Create(const CString filename, SHLOPENTYPE type = SHLOPENTYPE_TEXT, int maxlinelegth = 0);

		// Fun��o usada para ler uma m_line.
		void Read(void);

		// Fun��o que l� apenas um byte do arquivo;
		BOOL ReadByte(TCHAR &cBuffer);
		
		// Fun��o usada para escrever em um arquivo.
		void Write(void);

		// Fun��o que escreve
		void WriteByte(TCHAR &cBuffer);

		// Fun��o usada para fechar um arquivo.
		bool Close(void);
		
		// Fun��o para verificar se a �ltima operacao foi bem sucedida.
		BOOL IsSuccessfull(void);

		// Fun��o que retorna verdadeiro se o arquivo foi aberto e false se n�o.
		BOOL IsOpen(void);
		
		// Copia um arquivo de um local origem para outro destino;
		BOOL CopyFile(CString source, CString target, BOOL overwrite);
		// Fun��o para posicionar no inicio do arquivo.
		//void first(void);
		
		// Fun��o para posicionar no final do arquivo.
		//void last(void);
		
		// Fun��o para posicionar na pr�xima m_line do arquivo.
		//void next(void);
		
		// Fun��o para posicionar na m_line anterior do arquivo.
		//void previous(void);
		
		// Fun��o que retorna True se o final do arquivo foi encontrado.
		BOOL Eof(void);
		
		// Fun��o que retorna True se o inicio do arquivo foi encontrado.
		//BOOL bof(void);
		
		//Fun��o que retorna o valor do erro da ultima opera��o.
		long GetLastError(void);
		CString GetLastErrorMessage(void);

		//Fun��o que retorna o n�mero m�ximo de caracteres para leitura.
		long GetMaxLineLength(void);
		
		//Fun��o que retorna o conte�do da m_line lida.
		CString GetContent(void);
		TCHAR   GetContent(int ponteiro);
		
		//Fun��o que preenche o buffer de m_line com o valor do par�metro.
		void SetContent(const CString& line);
		void SetContent(const TCHAR& line);
		
		//Fun��o usada para truncar o arquivo, ou seja, deix�-lo com m_size zero.
		void Truncate(void);
		
		//Fun��o que devolve o m_size da m_line.
		int GetLength(void);

		//Fun��o que retorna o m_size do arquivo em bytes.
		double GetFileLength(void);

		//Fun��o que zera o conte�do da m_line.
		void ResetLine(void);
		
		//Fun��o que substitui o primeiro elemento pelo segundo.
		void Replace(const CString& exp1, const CString& exp2);
		
		//Fun��o para salvar um arquivo inteiro
		bool SaveFile(CString fileName, CString fileContent);
	protected:
		
		/* Vari�veis protegidas para configurar o objeto CFread. */
		TCHAR *m_line;				// Conte�do da �ltima m_line lida.
		long m_size;				// m_size da m_line;
		int m_growbuffer;			// Usado para n�o ser necess�rio criar muitas vezes o ponteiro.
		BOOL _issuccessfull;		// Vari�vel que retorna qual o status da �ltima operacao.
		HANDLE file_pointer;		// Ponteiro do arquivo.
		TCHAR m_type;				// m_type da leitura. Pode ser "b" bin�ria ou "t"texto.
		long m_maxlinelegth;		// m_size m�ximo de uma m_line.
		CString m_filename;			// Aguarda o nome do arquivo;
		long m_error;				// Retorna o erro da ultima operac�o;
		BOOL _open;					// Verifica se ha um arquivo aberto.
		BOOL _eof;					// Verifica se � fim de arquivo
};  

#endif
