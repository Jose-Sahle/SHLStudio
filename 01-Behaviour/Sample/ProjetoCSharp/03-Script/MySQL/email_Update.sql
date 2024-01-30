/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_email
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS email_Update
GO
CREATE PROCEDURE email_Update
(
    var_idEMAIL MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_FROM VARCHAR(8000),
    var_TO VARCHAR(8000),
    var_SUBJECT VARCHAR(500),
    var_TYPE VARCHAR(5),
    var_BODY VARCHAR(8000),
    var_Classificacao MEDIUMINT,
    var_Anexo VARCHAR(8000),
    var_Ativo BIT
)
BEGIN
    UPDATE 
		gp_email 
	SET
		`idRotina` = COALESCE(var_idRotina, `idRotina`)
		,`FROM` = COALESCE(var_FROM, `FROM`)
		,`TO` = COALESCE(var_TO, `TO`)
		,`SUBJECT` = COALESCE(var_SUBJECT, `SUBJECT`)
		,`TYPE` = COALESCE(var_TYPE, `TYPE`)
		,`BODY` = COALESCE(var_BODY, `BODY`)
		,`Classificacao` = COALESCE(var_Classificacao, `Classificacao`)
		,`Anexo` = COALESCE(var_Anexo, `Anexo`)
		,`Ativo` = COALESCE(var_Ativo, `Ativo`)
    WHERE 
		`idEMAIL` = var_idEMAIL;		
END
GO

