/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:42
  FUNCTION	: Insert a record in the table GP_AGENDAMENTO
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE AGENDAMENTO_Insert
(
	var_IDROTINA IN INTEGER,
	var_DATAINICIO IN DATE,
	var_HORAINICIO IN VARCHAR2,
	var_DATAFIM IN DATE,
	var_HORAFIM IN VARCHAR2,
	var_INTERVALO IN INTEGER,
	var_REPETICAO IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_AGENDAMENTO
	(
		IDROTINA
		,DATAINICIO
		,HORAINICIO
		,DATAFIM
		,HORAFIM
		,INTERVALO
		,REPETICAO
	)
	VALUES
	(
		var_IDROTINA
		,var_DATAINICIO
		,var_HORAINICIO
		,var_DATAFIM
		,var_HORAFIM
		,var_INTERVALO
		,var_REPETICAO
	)
	RETURNING IDAGENDAMENTO INTO var_IdReturn;	
END AGENDAMENTO_Insert;
GO

