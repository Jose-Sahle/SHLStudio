// AES_Encryption.h

#pragma once

#include <string>
using std::string;

string ToBase64Crypto( LPCSTR pSrc );
string FromBase64Crypto( LPCSTR pSrc );

string EncryptAES(const string &buf);
string DecryptAES(string base64cipher);
void EncryptAESFile(const char *infile, const char *outfile);
bool DecryptAESFile(const char *infile, const char *outfile);

