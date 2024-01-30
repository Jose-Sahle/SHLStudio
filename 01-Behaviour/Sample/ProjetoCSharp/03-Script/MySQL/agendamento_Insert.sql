/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_agendamento
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS agendamento_Insert
GO
CREATE PROCEDURE agendamento_Insert
(
	var_idRotina MEDIUMINT
	,var_DataInicio DATE
	,var_HoraInicio VARCHAR(8)
	,var_DataFim DATE
	,var_HoraFim VARCHAR(8)
	,var_Intervalo MEDIUMINT
	,var_Repeticao MEDIUMINT
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_agendamento
	(
		`idRotina`
		,`DataInicio`
		,`HoraInicio`
		,`DataFim`
		,`HoraFim`
		,`Intervalo`
		,`Repeticao`
	)
	VALUES
	(
		var_idRotina,
		var_DataInicio,
		var_HoraInicio,
		var_DataFim,
		var_HoraFim,
		var_Intervalo,
		var_Repeticao
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

