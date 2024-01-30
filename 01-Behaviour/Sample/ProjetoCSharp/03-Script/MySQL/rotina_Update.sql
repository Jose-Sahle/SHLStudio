/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Update a record in the table gp_rotina
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS rotina_Update
GO
CREATE PROCEDURE rotina_Update
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
    UPDATE 
		gp_rotina 
	SET
		`Nome` = COALESCE(var_Nome, `Nome`)
		,`Decricao` = COALESCE(var_Decricao, `Decricao`)
		,`DataCriacao` = COALESCE(var_DataCriacao, `DataCriacao`)
		,`Usuario` = COALESCE(var_Usuario, `Usuario`)
		,`Funcional` = COALESCE(var_Funcional, `Funcional`)
		,`Ativo` = COALESCE(var_Ativo, `Ativo`)
		,`Apelido` = COALESCE(var_Apelido, `Apelido`)
    WHERE 
		`idRotina` = var_idRotina;		
END
GO

