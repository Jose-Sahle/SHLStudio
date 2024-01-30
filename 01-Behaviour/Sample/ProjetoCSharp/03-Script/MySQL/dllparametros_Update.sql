/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_dllparametros
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS dllparametros_Update
GO
CREATE PROCEDURE dllparametros_Update
(
    var_idDLLParametros MEDIUMINT,
    var_idDLL MEDIUMINT,
    var_Nome VARCHAR(50),
    var_Valor VARCHAR(8000),
    var_Tipo MEDIUMINT,
    var_Formato VARCHAR(2)
)
BEGIN
    UPDATE 
		gp_dllparametros 
	SET
		`idDLL` = COALESCE(var_idDLL, `idDLL`)
		,`Nome` = COALESCE(var_Nome, `Nome`)
		,`Valor` = COALESCE(var_Valor, `Valor`)
		,`Tipo` = COALESCE(var_Tipo, `Tipo`)
		,`Formato` = COALESCE(var_Formato, `Formato`)
    WHERE 
		`idDLLParametros` = var_idDLLParametros;		
END
GO

