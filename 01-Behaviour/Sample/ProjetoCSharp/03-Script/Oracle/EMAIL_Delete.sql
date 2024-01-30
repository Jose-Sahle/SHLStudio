/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_EMAIL
**********************************************************/
CREATE OR REPLACE PROCEDURE EMAIL_Delete
(
	var_IDEMAIL IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_EMAIL
    WHERE IDEMAIL = var_IDEMAIL;
END EMAIL_Delete;
GO

