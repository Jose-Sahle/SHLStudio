/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_DLLPARAMETROS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Insert
(
	var_IDDLL IN INTEGER,
	var_NOME IN VARCHAR2,
	var_VALOR IN VARCHAR2,
	var_TIPO IN INTEGER,
	var_FORMATO IN VARCHAR2
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_DLLPARAMETROS
	(
		IDDLL
		,NOME
		,VALOR
		,TIPO
		,FORMATO
	)
	VALUES
	(
		var_IDDLL
		,var_NOME
		,var_VALOR
		,var_TIPO
		,var_FORMATO
	)
	RETURNING IDDLLPARAMETROS INTO var_IdReturn;	
END DLLPARAMETROS_Insert;
GO

