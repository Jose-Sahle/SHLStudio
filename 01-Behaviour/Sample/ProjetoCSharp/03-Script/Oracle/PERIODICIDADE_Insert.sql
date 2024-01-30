/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_PERIODICIDADE
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Insert
(
	var_IDROTINA IN INTEGER,
	var_TIPO IN INTEGER,
	var_PARAMETRO IN VARCHAR2
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_PERIODICIDADE
	(
		IDROTINA
		,TIPO
		,PARAMETRO
	)
	VALUES
	(
		var_IDROTINA
		,var_TIPO
		,var_PARAMETRO
	)
	RETURNING IDPERIODICIDADE INTO var_IdReturn;	
END PERIODICIDADE_Insert;
GO

