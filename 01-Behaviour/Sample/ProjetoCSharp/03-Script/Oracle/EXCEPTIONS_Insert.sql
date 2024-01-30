/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_EXCEPTIONS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EXCEPTIONS_Insert
(
	var_IDROTINA IN INTEGER,
	var_TENTATIVA IN INTEGER,
	var_INTERVALO IN INTEGER,
	var_ENVIAREMAIL IN INTEGER,
	var_ENVIARULTIMOEMAIL IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_EXCEPTIONS
	(
		IDROTINA
		,TENTATIVA
		,INTERVALO
		,ENVIAREMAIL
		,ENVIARULTIMOEMAIL
	)
	VALUES
	(
		var_IDROTINA
		,var_TENTATIVA
		,var_INTERVALO
		,var_ENVIAREMAIL
		,var_ENVIARULTIMOEMAIL
	)
	RETURNING IDEXCEPTIONS INTO var_IdReturn;	
END EXCEPTIONS_Insert;
GO

