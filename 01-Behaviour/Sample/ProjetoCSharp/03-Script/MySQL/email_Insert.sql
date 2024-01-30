/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_email
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS email_Insert
GO
CREATE PROCEDURE email_Insert
(
	var_idRotina MEDIUMINT
	,var_FROM VARCHAR(8000)
	,var_TO VARCHAR(8000)
	,var_SUBJECT VARCHAR(500)
	,var_TYPE VARCHAR(5)
	,var_BODY VARCHAR(8000)
	,var_Classificacao MEDIUMINT
	,var_Anexo VARCHAR(8000)
	,var_Ativo BIT
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_email
	(
		`idRotina`
		,`FROM`
		,`TO`
		,`SUBJECT`
		,`TYPE`
		,`BODY`
		,`Classificacao`
		,`Anexo`
		,`Ativo`
	)
	VALUES
	(
		var_idRotina,
		var_FROM,
		var_TO,
		var_SUBJECT,
		var_TYPE,
		var_BODY,
		var_Classificacao,
		var_Anexo,
		var_Ativo
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

