/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_ROTINA
**********************************************************/
CREATE OR REPLACE PROCEDURE ROTINA_Delete
(
	var_IDROTINA IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_ROTINA
    WHERE IDROTINA = var_IDROTINA;
END ROTINA_Delete;
GO

