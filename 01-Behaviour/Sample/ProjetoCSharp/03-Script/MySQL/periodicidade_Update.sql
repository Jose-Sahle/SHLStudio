/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_periodicidade
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS periodicidade_Update
GO
CREATE PROCEDURE periodicidade_Update
(
    var_idPeriodicidade MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_Tipo MEDIUMINT,
    var_Parametro VARCHAR(100)
)
BEGIN
    UPDATE 
		gp_periodicidade 
	SET
		`idRotina` = COALESCE(var_idRotina, `idRotina`)
		,`Tipo` = COALESCE(var_Tipo, `Tipo`)
		,`Parametro` = COALESCE(var_Parametro, `Parametro`)
    WHERE 
		`idPeriodicidade` = var_idPeriodicidade;		
END
GO

