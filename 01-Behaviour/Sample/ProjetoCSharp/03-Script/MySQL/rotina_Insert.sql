/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
  FUNCTION	: Insert a record in the table gp_rotina
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS rotina_Insert
GO
CREATE PROCEDURE rotina_Insert
(
	var_Nome VARCHAR(50)
	,var_Decricao VARCHAR(255)
	,var_DataCriacao DATE
	,var_Usuario VARCHAR(20)
	,var_Funcional VARCHAR(20)
	,var_Ativo BIT
	,var_Apelido VARCHAR(50)
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO gp_rotina
	(
		`Nome`
		,`Decricao`
		,`DataCriacao`
		,`Usuario`
		,`Funcional`
		,`Ativo`
		,`Apelido`
	)
	VALUES
	(
		var_Nome,
		var_Decricao,
		var_DataCriacao,
		var_Usuario,
		var_Funcional,
		var_Ativo,
		var_Apelido
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO

