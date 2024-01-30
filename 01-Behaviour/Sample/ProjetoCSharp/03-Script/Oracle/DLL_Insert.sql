/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_DLL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLL_Insert
(
	var_IDROTINA IN INTEGER,
	var_ORDEM IN INTEGER,
	var_NOME IN VARCHAR2,
	var_ASSEMBLY IN VARCHAR2,
	var_DEPENDENCIA IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_DLL
	(
		IDROTINA
		,ORDEM
		,NOME
		,ASSEMBLY
		,DEPENDENCIA
	)
	VALUES
	(
		var_IDROTINA
		,var_ORDEM
		,var_NOME
		,var_ASSEMBLY
		,var_DEPENDENCIA
	)
	RETURNING IDDLL INTO var_IdReturn;	
END DLL_Insert;
GO

