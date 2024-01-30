#pragma once

#include <string.h>
#include <iostream>

class FILEPATHINFO
{
public:
		/* Informações de arquivos */
		CString				name;
		CString				path;
        unsigned			attrib;
        __time64_t			time_create;    /* -1 for FAT file systems */
        __time64_t			time_access;    /* -1 for FAT file systems */
        __time64_t			time_write;
        _fsize_t			filelength;
};

class ELEMENT
{
public:
		/* Informações de arquivos */
		CString				caminho;
		UINT				atributo;
        BOOL				moresub;
		DWORD				filelength;
};