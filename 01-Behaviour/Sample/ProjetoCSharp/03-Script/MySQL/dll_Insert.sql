/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_dll
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS dll_Insert
GO
CREATE PROCEDURE dll_Insert
(
	var_idRotina MEDIUMINT
	,var_Ordem MEDIUMINT
	,var_Nome VARCHAR(100)
	,var_Assembly VARCHAR(100)
	,var_Dependencia MEDIUMINT
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_dll
	(
		`idRotina`
		,`Ordem`
		,`Nome`
		,`Assembly`
		,`Dependencia`
	)
	VALUES
	(
		var_idRotina,
		var_Ordem,
		var_Nome,
		var_Assembly,
		var_Dependencia
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

