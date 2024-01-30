/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Select records from table gp_dll filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS dll_Select
GO
CREATE PROCEDURE dll_Select
(
    var_idDLL MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_Ordem MEDIUMINT,
    var_Nome VARCHAR(100),
    var_Assembly VARCHAR(100),
    var_Dependencia MEDIUMINT
)
BEGIN
	SELECT
		`idDLL`,
		`idRotina`,
		`Ordem`,
		`Nome`,
		`Assembly`,
		`Dependencia`
	FROM
		gp_dll
	WHERE
		(`idDLL` = var_idDLL or var_idDLL is null)
	AND (`idRotina` = var_idRotina OR var_idRotina IS NULL)
	AND (`Ordem` = var_Ordem OR var_Ordem IS NULL)
	AND (`Nome` = var_Nome OR var_Nome IS NULL)
	AND (`Assembly` = var_Assembly OR var_Assembly IS NULL)
	AND (`Dependencia` = var_Dependencia OR var_Dependencia IS NULL)
		;
END
GO

