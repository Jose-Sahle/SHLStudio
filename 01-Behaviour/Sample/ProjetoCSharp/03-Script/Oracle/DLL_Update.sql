
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_DLL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLL_Update
(
	var_IDDLL IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_ORDEM IN INTEGER,
	var_NOME IN VARCHAR2,
	var_ASSEMBLY IN VARCHAR2,
	var_DEPENDENCIA IN INTEGER
)
IS 
BEGIN
	UPDATE 
		GP_DLL 
	SET
		IDROTINA = var_IDROTINA
		,ORDEM = var_ORDEM
		,NOME = var_NOME
		,ASSEMBLY = var_ASSEMBLY
		,DEPENDENCIA = var_DEPENDENCIA
	WHERE 
		IDDLL = var_IDDLL;
		
END DLL_Update;
GO

