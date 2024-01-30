// Utils.h

#pragma once

#define PI 3.14

#define DT_STRING	0x00
#define DT_NUMBER	0x01
#define DT_DATETIME	0x02
#define DT_DATE		0x03
#define DT_TIME		0x04
#define DT_IMAGE	0x05

#define ST_ASC			1
#define ST_DESC		   -1

#define WITHSECOND TRUE
#define WITHOUTSECOND FALSE

const int _A_ARQ = 1;
const int _A_DIR = 2;
const int _A_PAI = 3;
const int _A_DIR_ARQ = 4;


namespace Utils
{
	void DisplayWinError(LPTSTR szAPI, DWORD dwError);
	CString EscapeXml(const CString &str);
	CString ErrorMessage(DWORD err);
	HMODULE LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName, LPCTSTR lpAdditionalSubPath);
	CString GetApplicationDirectory();
	CString GetPartOf(const CString cadeia, int tipo);

	void Copychar(TCHAR *origem, TCHAR *destino, int qtd);
	void CopycharA(char *origem, char *destino, int qtd);

	inline CString GetSettingsXmlPath()
	{
		return GetApplicationDirectory() + _T("settings.xml");
	}

	inline CString GetServerIpPath()
	{
		return GetApplicationDirectory() + _T("server_ip.txt");
	}

	//CArray<BYTE> FromBase64Crypto(CString pSrc);
	CString ToBase64Crypto(CString pSrc);

	CString GenerateRandomString();
	CString GetFileVersion(const TCHAR *pszFilePath);
	CString GetProcessPath(DWORD pid);
	CString GetProcessName(DWORD dwProcessId);
	CString GetProcessPath(DWORD pid);
	void NormalizeNTPath(TCHAR * pszPath, size_t nMax);

	void RunProcess(const TCHAR *cmd);

	BOOL GetLogonFromToken(HANDLE hToken, CString& strUser, CString& strdomain);
	HRESULT GetUserFromProcess(const DWORD procId, CString& strUser, CString& strdomain);
	DWORD GetExplorerPID();
	BOOL LaunchAppIntoDifferentSession(LPCTSTR szProcessPath);
	CString PathTo(const TCHAR *file);
	CString ToStr(int code);
	CString Split(CString word, int position, CString separator = _T(""), CString delimitator = _T(""));
	BOOL ExistFile(const CString& strFileName);

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

	CString TimeConv(double dwSec, BOOL bSecond = TRUE);
	void DToC(const CTime& tm, CString &strData, int nOption);

	void Val(CString strCadeia, short &pValor);
	void Val(CString strCadeia, int &pValor);
	void Val(CString strCadeia, WORD &pValor);
	void Val(CString strCadeia, long &pValor);
	void Val(CString strCadeia, unsigned long &pValor);
	void Val(CString strCadeia, float &pValor);
	void Val(CString strCadeia, double &pValor);
};

