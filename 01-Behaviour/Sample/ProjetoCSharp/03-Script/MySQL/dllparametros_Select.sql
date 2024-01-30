/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Select records from table gp_dllparametros filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS dllparametros_Select
GO
CREATE PROCEDURE dllparametros_Select
(
    var_idDLLParametros MEDIUMINT,
    var_idDLL MEDIUMINT,
    var_Nome VARCHAR(50),
    var_Valor VARCHAR(8000),
    var_Tipo MEDIUMINT,
    var_Formato VARCHAR(2)
)
BEGIN
	SELECT
		`idDLLParametros`,
		`idDLL`,
		`Nome`,
		`Valor`,
		`Tipo`,
		`Formato`
	FROM
		gp_dllparametros
	WHERE
		(`idDLLParametros` = var_idDLLParametros or var_idDLLParametros is null)
	AND (`idDLL` = var_idDLL OR var_idDLL IS NULL)
	AND (`Nome` = var_Nome OR var_Nome IS NULL)
	AND (`Valor` = var_Valor OR var_Valor IS NULL)
	AND (`Tipo` = var_Tipo OR var_Tipo IS NULL)
	AND (`Formato` = var_Formato OR var_Formato IS NULL)
		;
END
GO

