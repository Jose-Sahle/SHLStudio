
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_ROTINA
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE ROTINA_Update
(
	var_IDROTINA IN INTEGER,
	var_NOME IN VARCHAR2,
	var_DECRICAO IN VARCHAR2,
	var_DATACRIACAO IN DATE,
	var_USUARIO IN VARCHAR2,
	var_FUNCIONAL IN VARCHAR2,
	var_ATIVO IN INTEGER,
	var_APELIDO IN VARCHAR2
)
IS 
BEGIN
	UPDATE 
		GP_ROTINA 
	SET
		NOME = var_NOME
		,DECRICAO = var_DECRICAO
		,DATACRIACAO = var_DATACRIACAO
		,USUARIO = var_USUARIO
		,FUNCIONAL = var_FUNCIONAL
		,ATIVO = var_ATIVO
		,APELIDO = var_APELIDO
	WHERE 
		IDROTINA = var_IDROTINA;
		
END ROTINA_Update;
GO

