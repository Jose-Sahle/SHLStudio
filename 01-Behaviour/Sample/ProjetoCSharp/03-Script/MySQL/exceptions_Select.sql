/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:18
  FUNCTION	: Select records from table gp_exceptions filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS exceptions_Select
GO
CREATE PROCEDURE exceptions_Select
(
    var_idExceptions MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_Tentativa MEDIUMINT,
    var_Intervalo MEDIUMINT,
    var_EnviarEmail BIT,
    var_EnviarUltimoEmail BIT
)
BEGIN
	SELECT
		`idExceptions`,
		`idRotina`,
		`Tentativa`,
		`Intervalo`,
		`EnviarEmail`,
		`EnviarUltimoEmail`
	FROM
		gp_exceptions
	WHERE
		(`idExceptions` = var_idExceptions or var_idExceptions is null)
	AND (`idRotina` = var_idRotina OR var_idRotina IS NULL)
	AND (`Tentativa` = var_Tentativa OR var_Tentativa IS NULL)
	AND (`Intervalo` = var_Intervalo OR var_Intervalo IS NULL)
	AND (`EnviarEmail` = var_EnviarEmail OR var_EnviarEmail IS NULL)
	AND (`EnviarUltimoEmail` = var_EnviarUltimoEmail OR var_EnviarUltimoEmail IS NULL)
		;
END
GO

