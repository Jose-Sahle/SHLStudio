/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_ROTINA filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE ROTINA_Select
(
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_NOME IN VARCHAR2  DEFAULT NULL,
    var_DECRICAO IN VARCHAR2  DEFAULT NULL,
    var_DATACRIACAO IN DATE  DEFAULT NULL,
    var_USUARIO IN VARCHAR2  DEFAULT NULL,
    var_FUNCIONAL IN VARCHAR2  DEFAULT NULL,
    var_ATIVO IN INTEGER  DEFAULT NULL,
    var_APELIDO IN VARCHAR2  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDROTINA,
			NOME,
			DECRICAO,
			DATACRIACAO,
			USUARIO,
			FUNCIONAL,
			ATIVO,
			APELIDO
		FROM
			GP_ROTINA
		WHERE
			(IDROTINA = var_IDROTINA or var_IDROTINA is null)
		AND (NOME = var_NOME OR var_NOME IS NULL)
		AND (DECRICAO = var_DECRICAO OR var_DECRICAO IS NULL)
		AND (DATACRIACAO = var_DATACRIACAO OR var_DATACRIACAO IS NULL)
		AND (USUARIO = var_USUARIO OR var_USUARIO IS NULL)
		AND (FUNCIONAL = var_FUNCIONAL OR var_FUNCIONAL IS NULL)
		AND (ATIVO = var_ATIVO OR var_ATIVO IS NULL)
		AND (APELIDO = var_APELIDO OR var_APELIDO IS NULL)
		;
END ROTINA_Select;
GO

