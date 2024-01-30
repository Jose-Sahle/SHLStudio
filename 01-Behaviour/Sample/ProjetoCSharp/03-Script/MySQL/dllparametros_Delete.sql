/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Delete a record in the table gp_dllparametros
**********************************************************/
DROP PROCEDURE IF EXISTS dllparametros_Delete
GO
CREATE PROCEDURE dllparametros_Delete
(
	var_idDLLParametros MEDIUMINT
)
BEGIN
    DELETE FROM gp_dllparametros
    WHERE `idDLLParametros` = var_idDLLParametros;
	
END
GO


