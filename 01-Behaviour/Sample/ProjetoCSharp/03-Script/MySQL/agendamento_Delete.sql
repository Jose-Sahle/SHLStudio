/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_agendamento
**********************************************************/
DROP PROCEDURE IF EXISTS agendamento_Delete
GO
CREATE PROCEDURE agendamento_Delete
(
	var_idAgendamento MEDIUMINT
)
BEGIN
    DELETE FROM gp_agendamento
    WHERE `idAgendamento` = var_idAgendamento;
	
END
GO


