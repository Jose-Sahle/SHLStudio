/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_periodicidade
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS periodicidade_Insert
GO
CREATE PROCEDURE periodicidade_Insert
(
	var_idRotina MEDIUMINT
	,var_Tipo MEDIUMINT
	,var_Parametro VARCHAR(100)
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_periodicidade
	(
		`idRotina`
		,`Tipo`
		,`Parametro`
	)
	VALUES
	(
		var_idRotina,
		var_Tipo,
		var_Parametro
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

