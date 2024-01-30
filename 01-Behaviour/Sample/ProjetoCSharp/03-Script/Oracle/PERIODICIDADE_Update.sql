
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_PERIODICIDADE
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Update
(
	var_IDPERIODICIDADE IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_TIPO IN INTEGER,
	var_PARAMETRO IN VARCHAR2
)
IS 
BEGIN
	UPDATE 
		GP_PERIODICIDADE 
	SET
		IDROTINA = var_IDROTINA
		,TIPO = var_TIPO
		,PARAMETRO = var_PARAMETRO
	WHERE 
		IDPERIODICIDADE = var_IDPERIODICIDADE;
		
END PERIODICIDADE_Update;
GO

