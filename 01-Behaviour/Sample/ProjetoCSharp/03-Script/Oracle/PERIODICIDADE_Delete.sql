/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_PERIODICIDADE
**********************************************************/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Delete
(
	var_IDPERIODICIDADE IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_PERIODICIDADE
    WHERE IDPERIODICIDADE = var_IDPERIODICIDADE;
END PERIODICIDADE_Delete;
GO

