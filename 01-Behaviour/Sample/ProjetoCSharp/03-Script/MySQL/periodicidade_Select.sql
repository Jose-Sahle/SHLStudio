/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:18
  FUNCTION	: Select records from table gp_periodicidade filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS periodicidade_Select
GO
CREATE PROCEDURE periodicidade_Select
(
    var_idPeriodicidade MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_Tipo MEDIUMINT,
    var_Parametro VARCHAR(100)
)
BEGIN
	SELECT
		`idPeriodicidade`,
		`idRotina`,
		`Tipo`,
		`Parametro`
	FROM
		gp_periodicidade
	WHERE
		(`idPeriodicidade` = var_idPeriodicidade or var_idPeriodicidade is null)
	AND (`idRotina` = var_idRotina OR var_idRotina IS NULL)
	AND (`Tipo` = var_Tipo OR var_Tipo IS NULL)
	AND (`Parametro` = var_Parametro OR var_Parametro IS NULL)
		;
END
GO

