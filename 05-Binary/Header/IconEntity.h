/* ***************************************************************************
 * Arquivo: IconEntity.h                                                     *
 *                                                                           *
 * Classe que mantém informações dos Icons dos projetos de SHLStudio.       *
 *                                                                           *
 * Data:08/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "Property.h"

class CIconEntity
{
public:
	CIconEntity(){Reset();}

	virtual ~CIconEntity(){Reset();};

// Propriedades
public:

	void Reset()
	{
	}
// Membros Privados
private:

};