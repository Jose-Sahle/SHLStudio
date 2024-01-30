/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_DLLPARAMETROS filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Select
(
    var_IDDLLPARAMETROS IN INTEGER  DEFAULT NULL,
    var_IDDLL IN INTEGER  DEFAULT NULL,
    var_NOME IN VARCHAR2  DEFAULT NULL,
    var_VALOR IN VARCHAR2  DEFAULT NULL,
    var_TIPO IN INTEGER  DEFAULT NULL,
    var_FORMATO IN VARCHAR2  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDDLLPARAMETROS,
			IDDLL,
			NOME,
			VALOR,
			TIPO,
			FORMATO
		FROM
			GP_DLLPARAMETROS
		WHERE
			(IDDLLPARAMETROS = var_IDDLLPARAMETROS or var_IDDLLPARAMETROS is null)
		AND (IDDLL = var_IDDLL OR var_IDDLL IS NULL)
		AND (NOME = var_NOME OR var_NOME IS NULL)
		AND (VALOR = var_VALOR OR var_VALOR IS NULL)
		AND (TIPO = var_TIPO OR var_TIPO IS NULL)
		AND (FORMATO = var_FORMATO OR var_FORMATO IS NULL)
		;
END DLLPARAMETROS_Select;
GO

