/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_rotina
**********************************************************/
DROP PROCEDURE IF EXISTS rotina_Delete
GO
CREATE PROCEDURE rotina_Delete
(
	var_idRotina MEDIUMINT
)
BEGIN
    DELETE FROM gp_rotina
    WHERE `idRotina` = var_idRotina;
	
END
GO


