/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_DLL
**********************************************************/
CREATE OR REPLACE PROCEDURE DLL_Delete
(
	var_IDDLL IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_DLL
    WHERE IDDLL = var_IDDLL;
END DLL_Delete;
GO

