/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_exceptions
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS exceptions_Insert
GO
CREATE PROCEDURE exceptions_Insert
(
	var_idRotina MEDIUMINT
	,var_Tentativa MEDIUMINT
	,var_Intervalo MEDIUMINT
	,var_EnviarEmail BIT
	,var_EnviarUltimoEmail BIT
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_exceptions
	(
		`idRotina`
		,`Tentativa`
		,`Intervalo`
		,`EnviarEmail`
		,`EnviarUltimoEmail`
	)
	VALUES
	(
		var_idRotina,
		var_Tentativa,
		var_Intervalo,
		var_EnviarEmail,
		var_EnviarUltimoEmail
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

