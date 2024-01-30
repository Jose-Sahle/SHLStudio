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
		CFread(const CFread &filecopy); //Construtor de Cópia

		// Destrutor
		~CFread();
		
		/* Definições das funções membros da classe */
		// Função usada para abrir um arquivo.
		bool Open(const CString filename, SHLOPENTYPE type = SHLOPENTYPE_TEXT, int maxlinelegth = 0); 

		// Função que cria e abre um arquivo.
		bool Create(const CString filename, SHLOPENTYPE type = SHLOPENTYPE_TEXT, int maxlinelegth = 0);

		// Função usada para ler uma m_line.
		void Read(void);

		// Função que lê apenas um byte do arquivo;
		BOOL ReadByte(TCHAR &cBuffer);
		
		// Função usada para escrever em um arquivo.
		void Write(void);

		// Função que escreve
		void WriteByte(TCHAR &cBuffer);

		// Função usada para fechar um arquivo.
		bool Close(void);
		
		// Função para verificar se a última operacao foi bem sucedida.
		BOOL IsSuccessfull(void);

		// Função que retorna verdadeiro se o arquivo foi aberto e false se não.
		BOOL IsOpen(void);
		
		// Copia um arquivo de um local origem para outro destino;
		BOOL CopyFile(CString source, CString target, BOOL overwrite);
		// Função para posicionar no inicio do arquivo.
		//void first(void);
		
		// Função para posicionar no final do arquivo.
		//void last(void);
		
		// Função para posicionar na próxima m_line do arquivo.
		//void next(void);
		
		// Função para posicionar na m_line anterior do arquivo.
		//void previous(void);
		
		// Função que retorna True se o final do arquivo foi encontrado.
		BOOL Eof(void);
		
		// Função que retorna True se o inicio do arquivo foi encontrado.
		//BOOL bof(void);
		
		//Função que retorna o valor do erro da ultima operação.
		long GetLastError(void);
		CString GetLastErrorMessage(void);

		//Função que retorna o número máximo de caracteres para leitura.
		long GetMaxLineLength(void);
		
		//Função que retorna o conteúdo da m_line lida.
		CString GetContent(void);
		TCHAR   GetContent(int ponteiro);
		
		//Função que preenche o buffer de m_line com o valor do parâmetro.
		void SetContent(const CString& line);
		void SetContent(const TCHAR& line);
		
		//Função usada para truncar o arquivo, ou seja, deixá-lo com m_size zero.
		void Truncate(void);
		
		//Função que devolve o m_size da m_line.
		int GetLength(void);

		//Função que retorna o m_size do arquivo em bytes.
		double GetFileLength(void);

		//Função que zera o conteúdo da m_line.
		void ResetLine(void);
		
		//Função que substitui o primeiro elemento pelo segundo.
		void Replace(const CString& exp1, const CString& exp2);
		
		//Função para salvar um arquivo inteiro
		bool SaveFile(CString fileName, CString fileContent);
	protected:
		
		/* Variáveis protegidas para configurar o objeto CFread. */
		TCHAR *m_line;				// Conteúdo da última m_line lida.
		long m_size;				// m_size da m_line;
		int m_growbuffer;			// Usado para não ser necessário criar muitas vezes o ponteiro.
		BOOL _issuccessfull;		// Variável que retorna qual o status da última operacao.
		HANDLE file_pointer;		// Ponteiro do arquivo.
		TCHAR m_type;				// m_type da leitura. Pode ser "b" binária ou "t"texto.
		long m_maxlinelegth;		// m_size máximo de uma m_line.
		CString m_filename;			// Aguarda o nome do arquivo;
		long m_error;				// Retorna o erro da ultima operacão;
		BOOL _open;					// Verifica se ha um arquivo aberto.
		BOOL _eof;					// Verifica se é fim de arquivo
};  

#endif
