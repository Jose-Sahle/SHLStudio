/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_AGENDAMENTO
**********************************************************/
CREATE OR REPLACE PROCEDURE AGENDAMENTO_Delete
(
	var_IDAGENDAMENTO IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_AGENDAMENTO
    WHERE IDAGENDAMENTO = var_IDAGENDAMENTO;
END AGENDAMENTO_Delete;
GO

