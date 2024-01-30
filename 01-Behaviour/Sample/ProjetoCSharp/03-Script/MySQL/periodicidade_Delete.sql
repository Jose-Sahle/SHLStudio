/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_periodicidade
**********************************************************/
DROP PROCEDURE IF EXISTS periodicidade_Delete
GO
CREATE PROCEDURE periodicidade_Delete
(
	var_idPeriodicidade MEDIUMINT
)
BEGIN
    DELETE FROM gp_periodicidade
    WHERE `idPeriodicidade` = var_idPeriodicidade;
	
END
GO


