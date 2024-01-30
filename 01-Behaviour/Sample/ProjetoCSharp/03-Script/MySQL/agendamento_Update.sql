/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_agendamento
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS agendamento_Update
GO
CREATE PROCEDURE agendamento_Update
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
    UPDATE 
		gp_agendamento 
	SET
		`idRotina` = COALESCE(var_idRotina, `idRotina`)
		,`DataInicio` = COALESCE(var_DataInicio, `DataInicio`)
		,`HoraInicio` = COALESCE(var_HoraInicio, `HoraInicio`)
		,`DataFim` = COALESCE(var_DataFim, `DataFim`)
		,`HoraFim` = COALESCE(var_HoraFim, `HoraFim`)
		,`Intervalo` = COALESCE(var_Intervalo, `Intervalo`)
		,`Repeticao` = COALESCE(var_Repeticao, `Repeticao`)
    WHERE 
		`idAgendamento` = var_idAgendamento;		
END
GO

