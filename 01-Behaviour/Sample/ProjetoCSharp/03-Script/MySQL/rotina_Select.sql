/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:18
  FUNCTION	: Select records from table gp_rotina filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS rotina_Select
GO
CREATE PROCEDURE rotina_Select
(
    var_idRotina MEDIUMINT,
    var_Nome VARCHAR(50),
    var_Decricao VARCHAR(255),
    var_DataCriacao DATE,
    var_Usuario VARCHAR(20),
    var_Funcional VARCHAR(20),
    var_Ativo BIT,
    var_Apelido VARCHAR(50)
)
BEGIN
	SELECT
		`idRotina`,
		`Nome`,
		`Decricao`,
		`DataCriacao`,
		`Usuario`,
		`Funcional`,
		`Ativo`,
		`Apelido`
	FROM
		gp_rotina
	WHERE
		(`idRotina` = var_idRotina or var_idRotina is null)
	AND (`Nome` = var_Nome OR var_Nome IS NULL)
	AND (`Decricao` = var_Decricao OR var_Decricao IS NULL)
	AND (`DataCriacao` = var_DataCriacao OR var_DataCriacao IS NULL)
	AND (`Usuario` = var_Usuario OR var_Usuario IS NULL)
	AND (`Funcional` = var_Funcional OR var_Funcional IS NULL)
	AND (`Ativo` = var_Ativo OR var_Ativo IS NULL)
	AND (`Apelido` = var_Apelido OR var_Apelido IS NULL)
		;
END
GO

