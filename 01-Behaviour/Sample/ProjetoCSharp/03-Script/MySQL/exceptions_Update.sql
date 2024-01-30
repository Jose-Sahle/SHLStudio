/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_exceptions
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS exceptions_Update
GO
CREATE PROCEDURE exceptions_Update
(
    var_idExceptions MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_Tentativa MEDIUMINT,
    var_Intervalo MEDIUMINT,
    var_EnviarEmail BIT,
    var_EnviarUltimoEmail BIT
)
BEGIN
    UPDATE 
		gp_exceptions 
	SET
		`idRotina` = COALESCE(var_idRotina, `idRotina`)
		,`Tentativa` = COALESCE(var_Tentativa, `Tentativa`)
		,`Intervalo` = COALESCE(var_Intervalo, `Intervalo`)
		,`EnviarEmail` = COALESCE(var_EnviarEmail, `EnviarEmail`)
		,`EnviarUltimoEmail` = COALESCE(var_EnviarUltimoEmail, `EnviarUltimoEmail`)
    WHERE 
		`idExceptions` = var_idExceptions;		
END
GO

