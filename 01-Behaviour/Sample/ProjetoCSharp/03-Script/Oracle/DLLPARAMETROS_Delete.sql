/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_DLLPARAMETROS
**********************************************************/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Delete
(
	var_IDDLLPARAMETROS IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_DLLPARAMETROS
    WHERE IDDLLPARAMETROS = var_IDDLLPARAMETROS;
END DLLPARAMETROS_Delete;
GO

