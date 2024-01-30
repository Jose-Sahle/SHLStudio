
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_DLLPARAMETROS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Update
(
	var_IDDLLPARAMETROS IN INTEGER,
	var_IDDLL IN INTEGER,
	var_NOME IN VARCHAR2,
	var_VALOR IN VARCHAR2,
	var_TIPO IN INTEGER,
	var_FORMATO IN VARCHAR2
)
IS 
BEGIN
	UPDATE 
		GP_DLLPARAMETROS 
	SET
		IDDLL = var_IDDLL
		,NOME = var_NOME
		,VALOR = var_VALOR
		,TIPO = var_TIPO
		,FORMATO = var_FORMATO
	WHERE 
		IDDLLPARAMETROS = var_IDDLLPARAMETROS;
		
END DLLPARAMETROS_Update;
GO

