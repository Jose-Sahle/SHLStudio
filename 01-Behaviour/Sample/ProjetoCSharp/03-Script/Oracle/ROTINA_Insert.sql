/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_ROTINA
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE ROTINA_Insert
(
	var_NOME IN VARCHAR2,
	var_DECRICAO IN VARCHAR2,
	var_DATACRIACAO IN DATE,
	var_USUARIO IN VARCHAR2,
	var_FUNCIONAL IN VARCHAR2,
	var_ATIVO IN INTEGER,
	var_APELIDO IN VARCHAR2
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_ROTINA
	(
		NOME
		,DECRICAO
		,DATACRIACAO
		,USUARIO
		,FUNCIONAL
		,ATIVO
		,APELIDO
	)
	VALUES
	(
		var_NOME
		,var_DECRICAO
		,var_DATACRIACAO
		,var_USUARIO
		,var_FUNCIONAL
		,var_ATIVO
		,var_APELIDO
	)
	RETURNING IDROTINA INTO var_IdReturn;	
END ROTINA_Insert;
GO

