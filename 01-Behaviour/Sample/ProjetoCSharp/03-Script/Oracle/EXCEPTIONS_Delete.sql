/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_EXCEPTIONS
**********************************************************/
CREATE OR REPLACE PROCEDURE EXCEPTIONS_Delete
(
	var_IDEXCEPTIONS IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_EXCEPTIONS
    WHERE IDEXCEPTIONS = var_IDEXCEPTIONS;
END EXCEPTIONS_Delete;
GO

