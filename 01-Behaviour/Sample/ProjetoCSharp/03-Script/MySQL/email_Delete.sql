/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_email
**********************************************************/
DROP PROCEDURE IF EXISTS email_Delete
GO
CREATE PROCEDURE email_Delete
(
	var_idEMAIL MEDIUMINT
)
BEGIN
    DELETE FROM gp_email
    WHERE `idEMAIL` = var_idEMAIL;
	
END
GO


