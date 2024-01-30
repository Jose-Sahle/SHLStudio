/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Select records from table gp_agendamento filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS agendamento_Select
GO
CREATE PROCEDURE agendamento_Select
(
    var_idAgendamento MEDIUMINT,
    var_idRotina MEDIUMINT,
    var_DataInicio DATE,
    var_HoraInicio VARCHAR(8),
    var_DataFim DATE,
    var_HoraFim VARCHAR(8),
    var_Intervalo MEDIUMINT,
    var_Repeticao MEDIUMINT
)
BEGIN
	SELECT
		`idAgendamento`,
		`idRotina`,
		`DataInicio`,
		`HoraInicio`,
		`DataFim`,
		`HoraFim`,
		`Intervalo`,
		`Repeticao`
	FROM
		gp_agendamento
	WHERE
		(`idAgendamento` = var_idAgendamento or var_idAgendamento is null)
	AND (`idRotina` = var_idRotina OR var_idRotina IS NULL)
	AND (`DataInicio` = var_DataInicio OR var_DataInicio IS NULL)
	AND (`HoraInicio` = var_HoraInicio OR var_HoraInicio IS NULL)
	AND (`DataFim` = var_DataFim OR var_DataFim IS NULL)
	AND (`HoraFim` = var_HoraFim OR var_HoraFim IS NULL)
	AND (`Intervalo` = var_Intervalo OR var_Intervalo IS NULL)
	AND (`Repeticao` = var_Repeticao OR var_Repeticao IS NULL)
		;
END
GO

