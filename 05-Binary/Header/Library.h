/*****************************************************************************
 * Arquivo: Library.h                                                        *
 * Define fun��es usadas na vers�o Pascal.                                   *
 * Data:24/09/1997                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 * Data:28/05/2013                                                           *
 *   - LoadLibraryFromApplicationDirectory                                   *
 *   - GetApplicationDirectory                                               *
 *****************************************************************************/

#ifndef _BIBLIOT_H

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxcmn.h>

#define _BIBLIOT_H

#define PI 3.14

#define DT_STRING	0x00
#define DT_NUMBER	0x01
#define DT_DATETIME	0x02
#define DT_DATE		0x03
#define DT_TIME		0x04
#define DT_IMAGE	0x05

#include <stdio.h>
#include <math.h>
#include <atlbase.h>
#include <wtypes.h>
#ifndef _WIN32_WCE
#include <mq.h>
#endif
 
#define ST_ASC			1
#define ST_DESC		   -1

typedef struct _SortListInfo
{
	CListCtrl *	pctrlList;
	short		nColumn;
	short		nColumnDataType;
	short		nSortType;
} SortListInfo;
	
#define WITHSECOND TRUE
#define WITHOUTSECOND FALSE

typedef enum Logico {False = 0, True = 1, OFF = 0, ON = 1};

typedef int Boolean;   // Para tipo de retorno de operadores

const int dOUBLE=True;
const int sIMPLE=False;

const int _A_ARQ     = 1;
const int _A_DIR     = 2;
const int _A_PAI     = 3;
const int _A_DIR_ARQ = 4;


HRESULT __fastcall AnsiToUnicode(CHAR *pszA, LPOLESTR* ppszW);
HRESULT __fastcall UnicodeToAnsi(LPCOLESTR pszW, LPSTR* ppszA);

BOOL	ArquivoExiste(CString txtArquivo);
CString Alltrim(CString cadeia);

#ifndef _WIN32_WCE
	void    Cls(HANDLE hConsole);
	void    Clear(HANDLE hConsole,int xa, int ya,int xb, int yb);
	void    GotoXY(HANDLE hConsole, int x, int y);
	double  IniciaAreaGaussian(double nMedia, double nDesvio, double nVezesDesvio);
	void    Perr( BOOL bSucess , char *api  );
	BOOL    SetConsoleSizeScreen(HANDLE hConsole, int nRows, int nCols);
#endif

void    CToD(const CString& strValor, CTime &tmRet, int nOption = DT_DATE);
void	CToD(const CString& strValor, DATE &dtRet, int nOption = DT_DATE);
void    DToC(const CTime& tm, CString &strData, int nOption = DT_DATE);
void    DToC(const DATE& dtData, CString &strData, int nOption = DT_DATE);
void	DToCR(const DATE& dtDate, CString& strDate);
void	DToCR(const CTime& dtDate, CString& strDate);
void DataSemHora(COleDateTime dtAux1, COleDateTime &dtAux2);

int		CALLBACK	CompareFunctionList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
void    Copychar(TCHAR *origem, TCHAR *destino, int qtd);

CString ErrorMessage(DWORD err);

void	DispErrDesc(DWORD err, CString strAplicacao);

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);

BOOL	ExecutaPrograma(CString strPrograma, CString strArgumentos, BOOL bAguardar = FALSE);
double  Expoente( double base, double resultado);
CString GetPartOf(const CString cadeia,int tipo,int DOBRO = sIMPLE);
int		CountWord(CString strText, char cSeparator, char cDelimiter);
#ifndef _WIN32_WCE
CString GetMQErrDescription(ULONG hError);
#endif
CString GetWord(CString strText, char cSeparator, char cDelimiter, int nPosition);
CString GetWordSeparatedBy(CString strPalavra, int nPosicao, CString strSeparador = _T(","), CString strDelimitador = _T("|"));
int		GetWordSeparatedByCount(CString strPalavra, CString strSeparador = _T(","), CString strDelimitador = _T("|"));
BOOL	IsLetter(CString strLetter);
BOOL	IsNumeric(CString strLetter);
BOOL    KillFocusComboBox(UINT iID, CWnd* pParentWnd);
#ifndef _WIN32_WCE
	void	LogEvent(CString strMensagem, WORD wType, CString strAplicacao);
#endif
CString Nomearq(CString arquivo);
CString Padl(const CString& cadeia,int tamanho);
CString Padr(const CString& cadeia,int tamanho);
int     Pat(const CString& cadeia1, const CString& cadeia2);
double  Potencia( double x, double y );
double  Raiz(double expoente, double nValor);
double  Random(int nMax, int nLimite = 1);
CString Repeat(CString strCaracter, int niRepeticao);
int     Round(double nValor);
CString Space(int tamanho);
CString Str(int valor);
CString Str(unsigned int valor);
CString Str(long valor);
CString Str(unsigned long valor);
CString Str(float valor);
CString Str(double valor);
CString Str(int valor, int tamanho);
CString Str(unsigned int valor, int tamanho);
CString Str(WORD valor);
CString Str(LONGLONG valor);
CString Str(ULONGLONG valor);
CString Str(long valor, int tamanho);
CString Str(float valor, int tamanho);
CString Str(double valor, int tamanho);
CString StrVal(long valor);
CString StrVal(double valor);
CString StrVal(float valor);
CString StrVal(double valor, int niDecimal);
CString StrVal(float valor, int niDecimal);
CString Strzero(int valor, int tamanho);
CString Strzero(unsigned int valor, int tamanho);
CString Strzero(long valor, int tamanho);
CString Strzero(unsigned long valor, int tamanho);
CString Strzero(float valor, int tamanho);
CString Strzero(double valor, int tamanho);
CString Upper(CString& cadeia);
CString TimeConv( double dwSec, BOOL bSecond = TRUE );
void Val(CString strCadeia, short &pValor);
void Val(CString strCadeia, int &pValor);
void Val(CString strCadeia, WORD &pValor);
void Val(CString strCadeia, long &pValor);
void Val(CString strCadeia, unsigned long &pValor);
void Val(CString strCadeia, float &pValor);
void Val(CString strCadeia, double &pValor);

double round(const double dVal, const int nDecs);

int DeleteFiles(CString strFileName, CString strDirectory, BOOL bSubDirectories = FALSE);
int MoveFiles(CString strFileName, CString strDirectoryFrom, CString strDirectoryTo);
int CopyFiles(CString strFileName, CString strDirectoryFrom, CString strDirectoryTo);

BOOL ExistFile(const CString& strFileName);
BOOL WACreateDirectory(const CString& strDirectory);

CString RemoveSpecialCharacter(CString strString);

inline void Warn(const CString& strMessage)
{::MessageBox(NULL, strMessage, _T("Warning"), MB_ICONWARNING);}

inline void Inform(const CString& strMessage)
{::MessageBox(NULL, strMessage, _T("Information"), MB_ICONINFORMATION);}

BOOL Yes(const CString& strMessage, CString strCaptioin = _T("Confirmation"));

HMODULE LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName, LPCTSTR lpAdditionalSubPath);
CString GetApplicationDirectory();

#ifdef _WIN32_WCE
int LoadHtml(CString strFile);

BOOL InfraVermelhoSend(CString strFile);
BOOL InfraVermelhoReceive();
#endif

BOOL SpecialYes(const CString& strMessage,int nCount);

BOOL AddBS(CString& strPath);

CString SearchKey(CString strText, CString strKey, CString strDelimiter);

void Register(TCHAR * pszFileName);
BOOL IsRegistered(TCHAR * pszProgID);
BOOL TestObject(TCHAR * pszObjeto);

#endif

void DoEvents();
