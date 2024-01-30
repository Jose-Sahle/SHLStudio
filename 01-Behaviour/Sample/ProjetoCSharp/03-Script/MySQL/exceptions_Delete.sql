/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_exceptions
**********************************************************/
DROP PROCEDURE IF EXISTS exceptions_Delete
GO
CREATE PROCEDURE exceptions_Delete
(
	var_idExceptions MEDIUMINT
)
BEGIN
    DELETE FROM gp_exceptions
    WHERE `idExceptions` = var_idExceptions;
	
END
GO


