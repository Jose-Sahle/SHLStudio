/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_EMAIL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EMAIL_Insert
(
	var_IDROTINA IN INTEGER,
	var_FROMEMAIL IN VARCHAR2,
	var_TOEMAIL IN VARCHAR2,
	var_SUBJECTEMAIL IN VARCHAR2,
	var_TYPEEMAIL IN VARCHAR2,
	var_BODYEMAIL IN VARCHAR2,
	var_CLASSIFICACAO IN INTEGER,
	var_ANEXO IN VARCHAR2,
	var_ATIVO IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_EMAIL
	(
		IDROTINA
		,FROMEMAIL
		,TOEMAIL
		,SUBJECTEMAIL
		,TYPEEMAIL
		,BODYEMAIL
		,CLASSIFICACAO
		,ANEXO
		,ATIVO
	)
	VALUES
	(
		var_IDROTINA
		,var_FROMEMAIL
		,var_TOEMAIL
		,var_SUBJECTEMAIL
		,var_TYPEEMAIL
		,var_BODYEMAIL
		,var_CLASSIFICACAO
		,var_ANEXO
		,var_ATIVO
	)
	RETURNING IDEMAIL INTO var_IdReturn;	
END EMAIL_Insert;
GO

