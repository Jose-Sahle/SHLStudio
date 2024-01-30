/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_dll
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS dll_Update
GO
CREATE PROCEDURE dll_Update
(
    var_idDLL MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_Ordem MEDIUMINT,
    var_Nome VARCHAR(100),
    var_Assembly VARCHAR(100),
    var_Dependencia MEDIUMINT
)
BEGIN
    UPDATE 
		gp_dll 
	SET
		`idRotina` = COALESCE(var_idRotina, `idRotina`)
		,`Ordem` = COALESCE(var_Ordem, `Ordem`)
		,`Nome` = COALESCE(var_Nome, `Nome`)
		,`Assembly` = COALESCE(var_Assembly, `Assembly`)
		,`Dependencia` = COALESCE(var_Dependencia, `Dependencia`)
    WHERE 
		`idDLL` = var_idDLL;		
END
GO

