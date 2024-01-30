/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_dll
**********************************************************/
DROP PROCEDURE IF EXISTS dll_Delete
GO
CREATE PROCEDURE dll_Delete
(
	var_idDLL MEDIUMINT
)
BEGIN
    DELETE FROM gp_dll
    WHERE `idDLL` = var_idDLL;
	
END
GO


