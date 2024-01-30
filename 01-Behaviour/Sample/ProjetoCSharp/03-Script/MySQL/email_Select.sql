/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:18
  FUNCTION	: Select records from table gp_email filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS email_Select
GO
CREATE PROCEDURE email_Select
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
	SELECT
		`idEMAIL`,
		`idRotina`,
		`FROM`,
		`TO`,
		`SUBJECT`,
		`TYPE`,
		`BODY`,
		`Classificacao`,
		`Anexo`,
		`Ativo`
	FROM
		gp_email
	WHERE
		(`idEMAIL` = var_idEMAIL or var_idEMAIL is null)
	AND (`idRotina` = var_idRotina OR var_idRotina IS NULL)
	AND (`FROM` = var_FROM OR var_FROM IS NULL)
	AND (`TO` = var_TO OR var_TO IS NULL)
	AND (`SUBJECT` = var_SUBJECT OR var_SUBJECT IS NULL)
	AND (`TYPE` = var_TYPE OR var_TYPE IS NULL)
	AND (`BODY` = var_BODY OR var_BODY IS NULL)
	AND (`Classificacao` = var_Classificacao OR var_Classificacao IS NULL)
	AND (`Anexo` = var_Anexo OR var_Anexo IS NULL)
	AND (`Ativo` = var_Ativo OR var_Ativo IS NULL)
		;
END
GO

