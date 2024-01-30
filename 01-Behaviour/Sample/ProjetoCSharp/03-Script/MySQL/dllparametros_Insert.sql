/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_dllparametros
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS dllparametros_Insert
GO
CREATE PROCEDURE dllparametros_Insert
(
	var_idDLL MEDIUMINT
	,var_Nome VARCHAR(50)
	,var_Valor VARCHAR(8000)
	,var_Tipo MEDIUMINT
	,var_Formato VARCHAR(2)
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_dllparametros
	(
		`idDLL`
		,`Nome`
		,`Valor`
		,`Tipo`
		,`Formato`
	)
	VALUES
	(
		var_idDLL,
		var_Nome,
		var_Valor,
		var_Tipo,
		var_Formato
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

