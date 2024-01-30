/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_PERIODICIDADE filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Select
(
    var_IDPERIODICIDADE IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_TIPO IN INTEGER  DEFAULT NULL,
    var_PARAMETRO IN VARCHAR2  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDPERIODICIDADE,
			IDROTINA,
			TIPO,
			PARAMETRO
		FROM
			GP_PERIODICIDADE
		WHERE
			(IDPERIODICIDADE = var_IDPERIODICIDADE or var_IDPERIODICIDADE is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (TIPO = var_TIPO OR var_TIPO IS NULL)
		AND (PARAMETRO = var_PARAMETRO OR var_PARAMETRO IS NULL)
		;
END PERIODICIDADE_Select;
GO

