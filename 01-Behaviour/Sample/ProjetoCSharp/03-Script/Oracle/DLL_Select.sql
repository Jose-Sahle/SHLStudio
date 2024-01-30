/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_DLL filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLL_Select
(
    var_IDDLL IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_ORDEM IN INTEGER  DEFAULT NULL,
    var_NOME IN VARCHAR2  DEFAULT NULL,
    var_ASSEMBLY IN VARCHAR2  DEFAULT NULL,
    var_DEPENDENCIA IN INTEGER  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDDLL,
			IDROTINA,
			ORDEM,
			NOME,
			ASSEMBLY,
			DEPENDENCIA
		FROM
			GP_DLL
		WHERE
			(IDDLL = var_IDDLL or var_IDDLL is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (ORDEM = var_ORDEM OR var_ORDEM IS NULL)
		AND (NOME = var_NOME OR var_NOME IS NULL)
		AND (ASSEMBLY = var_ASSEMBLY OR var_ASSEMBLY IS NULL)
		AND (DEPENDENCIA = var_DEPENDENCIA OR var_DEPENDENCIA IS NULL)
		;
END DLL_Select;
GO

