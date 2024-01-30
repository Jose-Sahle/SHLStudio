/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:42
  FUNCTION	: Insert a record in the table GP_AGENDAMENTO
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE AGENDAMENTO_Insert
(
	var_IDROTINA IN INTEGER,
	var_DATAINICIO IN DATE,
	var_HORAINICIO IN VARCHAR2,
	var_DATAFIM IN DATE,
	var_HORAFIM IN VARCHAR2,
	var_INTERVALO IN INTEGER,
	var_REPETICAO IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_AGENDAMENTO
	(
		IDROTINA
		,DATAINICIO
		,HORAINICIO
		,DATAFIM
		,HORAFIM
		,INTERVALO
		,REPETICAO
	)
	VALUES
	(
		var_IDROTINA
		,var_DATAINICIO
		,var_HORAINICIO
		,var_DATAFIM
		,var_HORAFIM
		,var_INTERVALO
		,var_REPETICAO
	)
	RETURNING IDAGENDAMENTO INTO var_IdReturn;	
END AGENDAMENTO_Insert;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_DLL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLL_Insert
(
	var_IDROTINA IN INTEGER,
	var_ORDEM IN INTEGER,
	var_NOME IN VARCHAR2,
	var_ASSEMBLY IN VARCHAR2,
	var_DEPENDENCIA IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_DLL
	(
		IDROTINA
		,ORDEM
		,NOME
		,ASSEMBLY
		,DEPENDENCIA
	)
	VALUES
	(
		var_IDROTINA
		,var_ORDEM
		,var_NOME
		,var_ASSEMBLY
		,var_DEPENDENCIA
	)
	RETURNING IDDLL INTO var_IdReturn;	
END DLL_Insert;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_DLLPARAMETROS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Insert
(
	var_IDDLL IN INTEGER,
	var_NOME IN VARCHAR2,
	var_VALOR IN VARCHAR2,
	var_TIPO IN INTEGER,
	var_FORMATO IN VARCHAR2
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_DLLPARAMETROS
	(
		IDDLL
		,NOME
		,VALOR
		,TIPO
		,FORMATO
	)
	VALUES
	(
		var_IDDLL
		,var_NOME
		,var_VALOR
		,var_TIPO
		,var_FORMATO
	)
	RETURNING IDDLLPARAMETROS INTO var_IdReturn;	
END DLLPARAMETROS_Insert;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_EMAIL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EMAIL_Insert
(
	var_IDROTINA IN INTEGER,
	var_FROMEMAIL IN VARCHAR2,
	var_TOEMAIL IN VARCHAR2,
	var_SUBJECTEMAIL IN VARCHAR2,
	var_TYPEEMAIL IN VARCHAR2,
	var_BODYEMAIL IN VARCHAR2,
	var_CLASSIFICACAO IN INTEGER,
	var_ANEXO IN VARCHAR2,
	var_ATIVO IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_EMAIL
	(
		IDROTINA
		,FROMEMAIL
		,TOEMAIL
		,SUBJECTEMAIL
		,TYPEEMAIL
		,BODYEMAIL
		,CLASSIFICACAO
		,ANEXO
		,ATIVO
	)
	VALUES
	(
		var_IDROTINA
		,var_FROMEMAIL
		,var_TOEMAIL
		,var_SUBJECTEMAIL
		,var_TYPEEMAIL
		,var_BODYEMAIL
		,var_CLASSIFICACAO
		,var_ANEXO
		,var_ATIVO
	)
	RETURNING IDEMAIL INTO var_IdReturn;	
END EMAIL_Insert;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_EXCEPTIONS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EXCEPTIONS_Insert
(
	var_IDROTINA IN INTEGER,
	var_TENTATIVA IN INTEGER,
	var_INTERVALO IN INTEGER,
	var_ENVIAREMAIL IN INTEGER,
	var_ENVIARULTIMOEMAIL IN INTEGER
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_EXCEPTIONS
	(
		IDROTINA
		,TENTATIVA
		,INTERVALO
		,ENVIAREMAIL
		,ENVIARULTIMOEMAIL
	)
	VALUES
	(
		var_IDROTINA
		,var_TENTATIVA
		,var_INTERVALO
		,var_ENVIAREMAIL
		,var_ENVIARULTIMOEMAIL
	)
	RETURNING IDEXCEPTIONS INTO var_IdReturn;	
END EXCEPTIONS_Insert;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:43
  FUNCTION	: Insert a record in the table GP_PERIODICIDADE
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Insert
(
	var_IDROTINA IN INTEGER,
	var_TIPO IN INTEGER,
	var_PARAMETRO IN VARCHAR2
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO GP_PERIODICIDADE
	(
		IDROTINA
		,TIPO
		,PARAMETRO
	)
	VALUES
	(
		var_IDROTINA
		,var_TIPO
		,var_PARAMETRO
	)
	RETURNING IDPERIODICIDADE INTO var_IdReturn;	
END PERIODICIDADE_Insert;
GO

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


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_AGENDAMENTO
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE AGENDAMENTO_Update
(
	var_IDAGENDAMENTO IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_DATAINICIO IN DATE,
	var_HORAINICIO IN VARCHAR2,
	var_DATAFIM IN DATE,
	var_HORAFIM IN VARCHAR2,
	var_INTERVALO IN INTEGER,
	var_REPETICAO IN INTEGER
)
IS 
BEGIN
	UPDATE 
		GP_AGENDAMENTO 
	SET
		IDROTINA = var_IDROTINA
		,DATAINICIO = var_DATAINICIO
		,HORAINICIO = var_HORAINICIO
		,DATAFIM = var_DATAFIM
		,HORAFIM = var_HORAFIM
		,INTERVALO = var_INTERVALO
		,REPETICAO = var_REPETICAO
	WHERE 
		IDAGENDAMENTO = var_IDAGENDAMENTO;
		
END AGENDAMENTO_Update;
GO


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_DLL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLL_Update
(
	var_IDDLL IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_ORDEM IN INTEGER,
	var_NOME IN VARCHAR2,
	var_ASSEMBLY IN VARCHAR2,
	var_DEPENDENCIA IN INTEGER
)
IS 
BEGIN
	UPDATE 
		GP_DLL 
	SET
		IDROTINA = var_IDROTINA
		,ORDEM = var_ORDEM
		,NOME = var_NOME
		,ASSEMBLY = var_ASSEMBLY
		,DEPENDENCIA = var_DEPENDENCIA
	WHERE 
		IDDLL = var_IDDLL;
		
END DLL_Update;
GO


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_DLLPARAMETROS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Update
(
	var_IDDLLPARAMETROS IN INTEGER,
	var_IDDLL IN INTEGER,
	var_NOME IN VARCHAR2,
	var_VALOR IN VARCHAR2,
	var_TIPO IN INTEGER,
	var_FORMATO IN VARCHAR2
)
IS 
BEGIN
	UPDATE 
		GP_DLLPARAMETROS 
	SET
		IDDLL = var_IDDLL
		,NOME = var_NOME
		,VALOR = var_VALOR
		,TIPO = var_TIPO
		,FORMATO = var_FORMATO
	WHERE 
		IDDLLPARAMETROS = var_IDDLLPARAMETROS;
		
END DLLPARAMETROS_Update;
GO


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_EMAIL
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EMAIL_Update
(
	var_IDEMAIL IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_FROMEMAIL IN VARCHAR2,
	var_TOEMAIL IN VARCHAR2,
	var_SUBJECTEMAIL IN VARCHAR2,
	var_TYPEEMAIL IN VARCHAR2,
	var_BODYEMAIL IN VARCHAR2,
	var_CLASSIFICACAO IN INTEGER,
	var_ANEXO IN VARCHAR2,
	var_ATIVO IN INTEGER
)
IS 
BEGIN
	UPDATE 
		GP_EMAIL 
	SET
		IDROTINA = var_IDROTINA
		,FROMEMAIL = var_FROMEMAIL
		,TOEMAIL = var_TOEMAIL
		,SUBJECTEMAIL = var_SUBJECTEMAIL
		,TYPEEMAIL = var_TYPEEMAIL
		,BODYEMAIL = var_BODYEMAIL
		,CLASSIFICACAO = var_CLASSIFICACAO
		,ANEXO = var_ANEXO
		,ATIVO = var_ATIVO
	WHERE 
		IDEMAIL = var_IDEMAIL;
		
END EMAIL_Update;
GO


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_EXCEPTIONS
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EXCEPTIONS_Update
(
	var_IDEXCEPTIONS IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_TENTATIVA IN INTEGER,
	var_INTERVALO IN INTEGER,
	var_ENVIAREMAIL IN INTEGER,
	var_ENVIARULTIMOEMAIL IN INTEGER
)
IS 
BEGIN
	UPDATE 
		GP_EXCEPTIONS 
	SET
		IDROTINA = var_IDROTINA
		,TENTATIVA = var_TENTATIVA
		,INTERVALO = var_INTERVALO
		,ENVIAREMAIL = var_ENVIAREMAIL
		,ENVIARULTIMOEMAIL = var_ENVIARULTIMOEMAIL
	WHERE 
		IDEXCEPTIONS = var_IDEXCEPTIONS;
		
END EXCEPTIONS_Update;
GO


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Update a record in the table GP_PERIODICIDADE
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Update
(
	var_IDPERIODICIDADE IN INTEGER,
	var_IDROTINA IN INTEGER,
	var_TIPO IN INTEGER,
	var_PARAMETRO IN VARCHAR2
)
IS 
BEGIN
	UPDATE 
		GP_PERIODICIDADE 
	SET
		IDROTINA = var_IDROTINA
		,TIPO = var_TIPO
		,PARAMETRO = var_PARAMETRO
	WHERE 
		IDPERIODICIDADE = var_IDPERIODICIDADE;
		
END PERIODICIDADE_Update;
GO


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

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_AGENDAMENTO
**********************************************************/
CREATE OR REPLACE PROCEDURE AGENDAMENTO_Delete
(
	var_IDAGENDAMENTO IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_AGENDAMENTO
    WHERE IDAGENDAMENTO = var_IDAGENDAMENTO;
END AGENDAMENTO_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_DLL
**********************************************************/
CREATE OR REPLACE PROCEDURE DLL_Delete
(
	var_IDDLL IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_DLL
    WHERE IDDLL = var_IDDLL;
END DLL_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_DLLPARAMETROS
**********************************************************/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Delete
(
	var_IDDLLPARAMETROS IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_DLLPARAMETROS
    WHERE IDDLLPARAMETROS = var_IDDLLPARAMETROS;
END DLLPARAMETROS_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_EMAIL
**********************************************************/
CREATE OR REPLACE PROCEDURE EMAIL_Delete
(
	var_IDEMAIL IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_EMAIL
    WHERE IDEMAIL = var_IDEMAIL;
END EMAIL_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_EXCEPTIONS
**********************************************************/
CREATE OR REPLACE PROCEDURE EXCEPTIONS_Delete
(
	var_IDEXCEPTIONS IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_EXCEPTIONS
    WHERE IDEXCEPTIONS = var_IDEXCEPTIONS;
END EXCEPTIONS_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_PERIODICIDADE
**********************************************************/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Delete
(
	var_IDPERIODICIDADE IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_PERIODICIDADE
    WHERE IDPERIODICIDADE = var_IDPERIODICIDADE;
END PERIODICIDADE_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Delete a record in the table GP_ROTINA
**********************************************************/
CREATE OR REPLACE PROCEDURE ROTINA_Delete
(
	var_IDROTINA IN INTEGER
)
IS
BEGIN
    DELETE FROM GP_ROTINA
    WHERE IDROTINA = var_IDROTINA;
END ROTINA_Delete;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_AGENDAMENTO filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE AGENDAMENTO_Select
(
    var_IDAGENDAMENTO IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_DATAINICIO IN DATE  DEFAULT NULL,
    var_HORAINICIO IN VARCHAR2  DEFAULT NULL,
    var_DATAFIM IN DATE  DEFAULT NULL,
    var_HORAFIM IN VARCHAR2  DEFAULT NULL,
    var_INTERVALO IN INTEGER  DEFAULT NULL,
    var_REPETICAO IN INTEGER  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDAGENDAMENTO,
			IDROTINA,
			DATAINICIO,
			HORAINICIO,
			DATAFIM,
			HORAFIM,
			INTERVALO,
			REPETICAO
		FROM
			GP_AGENDAMENTO
		WHERE
			(IDAGENDAMENTO = var_IDAGENDAMENTO or var_IDAGENDAMENTO is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (DATAINICIO = var_DATAINICIO OR var_DATAINICIO IS NULL)
		AND (HORAINICIO = var_HORAINICIO OR var_HORAINICIO IS NULL)
		AND (DATAFIM = var_DATAFIM OR var_DATAFIM IS NULL)
		AND (HORAFIM = var_HORAFIM OR var_HORAFIM IS NULL)
		AND (INTERVALO = var_INTERVALO OR var_INTERVALO IS NULL)
		AND (REPETICAO = var_REPETICAO OR var_REPETICAO IS NULL)
		;
END AGENDAMENTO_Select;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_DLL filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLL_Select
(
    var_IDDLL IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_ORDEM IN INTEGER  DEFAULT NULL,
    var_NOME IN VARCHAR2  DEFAULT NULL,
    var_ASSEMBLY IN VARCHAR2  DEFAULT NULL,
    var_DEPENDENCIA IN INTEGER  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDDLL,
			IDROTINA,
			ORDEM,
			NOME,
			ASSEMBLY,
			DEPENDENCIA
		FROM
			GP_DLL
		WHERE
			(IDDLL = var_IDDLL or var_IDDLL is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (ORDEM = var_ORDEM OR var_ORDEM IS NULL)
		AND (NOME = var_NOME OR var_NOME IS NULL)
		AND (ASSEMBLY = var_ASSEMBLY OR var_ASSEMBLY IS NULL)
		AND (DEPENDENCIA = var_DEPENDENCIA OR var_DEPENDENCIA IS NULL)
		;
END DLL_Select;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_DLLPARAMETROS filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE DLLPARAMETROS_Select
(
    var_IDDLLPARAMETROS IN INTEGER  DEFAULT NULL,
    var_IDDLL IN INTEGER  DEFAULT NULL,
    var_NOME IN VARCHAR2  DEFAULT NULL,
    var_VALOR IN VARCHAR2  DEFAULT NULL,
    var_TIPO IN INTEGER  DEFAULT NULL,
    var_FORMATO IN VARCHAR2  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDDLLPARAMETROS,
			IDDLL,
			NOME,
			VALOR,
			TIPO,
			FORMATO
		FROM
			GP_DLLPARAMETROS
		WHERE
			(IDDLLPARAMETROS = var_IDDLLPARAMETROS or var_IDDLLPARAMETROS is null)
		AND (IDDLL = var_IDDLL OR var_IDDLL IS NULL)
		AND (NOME = var_NOME OR var_NOME IS NULL)
		AND (VALOR = var_VALOR OR var_VALOR IS NULL)
		AND (TIPO = var_TIPO OR var_TIPO IS NULL)
		AND (FORMATO = var_FORMATO OR var_FORMATO IS NULL)
		;
END DLLPARAMETROS_Select;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_EMAIL filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EMAIL_Select
(
    var_IDEMAIL IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_FROMEMAIL IN VARCHAR2  DEFAULT NULL,
    var_TOEMAIL IN VARCHAR2  DEFAULT NULL,
    var_SUBJECTEMAIL IN VARCHAR2  DEFAULT NULL,
    var_TYPEEMAIL IN VARCHAR2  DEFAULT NULL,
    var_BODYEMAIL IN VARCHAR2  DEFAULT NULL,
    var_CLASSIFICACAO IN INTEGER  DEFAULT NULL,
    var_ANEXO IN VARCHAR2  DEFAULT NULL,
    var_ATIVO IN INTEGER  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDEMAIL,
			IDROTINA,
			FROMEMAIL,
			TOEMAIL,
			SUBJECTEMAIL,
			TYPEEMAIL,
			BODYEMAIL,
			CLASSIFICACAO,
			ANEXO,
			ATIVO
		FROM
			GP_EMAIL
		WHERE
			(IDEMAIL = var_IDEMAIL or var_IDEMAIL is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (FROMEMAIL = var_FROMEMAIL OR var_FROMEMAIL IS NULL)
		AND (TOEMAIL = var_TOEMAIL OR var_TOEMAIL IS NULL)
		AND (SUBJECTEMAIL = var_SUBJECTEMAIL OR var_SUBJECTEMAIL IS NULL)
		AND (TYPEEMAIL = var_TYPEEMAIL OR var_TYPEEMAIL IS NULL)
		AND (BODYEMAIL = var_BODYEMAIL OR var_BODYEMAIL IS NULL)
		AND (CLASSIFICACAO = var_CLASSIFICACAO OR var_CLASSIFICACAO IS NULL)
		AND (ANEXO = var_ANEXO OR var_ANEXO IS NULL)
		AND (ATIVO = var_ATIVO OR var_ATIVO IS NULL)
		;
END EMAIL_Select;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_EXCEPTIONS filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE EXCEPTIONS_Select
(
    var_IDEXCEPTIONS IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_TENTATIVA IN INTEGER  DEFAULT NULL,
    var_INTERVALO IN INTEGER  DEFAULT NULL,
    var_ENVIAREMAIL IN INTEGER  DEFAULT NULL,
    var_ENVIARULTIMOEMAIL IN INTEGER  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDEXCEPTIONS,
			IDROTINA,
			TENTATIVA,
			INTERVALO,
			ENVIAREMAIL,
			ENVIARULTIMOEMAIL
		FROM
			GP_EXCEPTIONS
		WHERE
			(IDEXCEPTIONS = var_IDEXCEPTIONS or var_IDEXCEPTIONS is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (TENTATIVA = var_TENTATIVA OR var_TENTATIVA IS NULL)
		AND (INTERVALO = var_INTERVALO OR var_INTERVALO IS NULL)
		AND (ENVIAREMAIL = var_ENVIAREMAIL OR var_ENVIAREMAIL IS NULL)
		AND (ENVIARULTIMOEMAIL = var_ENVIARULTIMOEMAIL OR var_ENVIARULTIMOEMAIL IS NULL)
		;
END EXCEPTIONS_Select;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_PERIODICIDADE filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE PERIODICIDADE_Select
(
    var_IDPERIODICIDADE IN INTEGER  DEFAULT NULL,
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_TIPO IN INTEGER  DEFAULT NULL,
    var_PARAMETRO IN VARCHAR2  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDPERIODICIDADE,
			IDROTINA,
			TIPO,
			PARAMETRO
		FROM
			GP_PERIODICIDADE
		WHERE
			(IDPERIODICIDADE = var_IDPERIODICIDADE or var_IDPERIODICIDADE is null)
		AND (IDROTINA = var_IDROTINA OR var_IDROTINA IS NULL)
		AND (TIPO = var_TIPO OR var_TIPO IS NULL)
		AND (PARAMETRO = var_PARAMETRO OR var_PARAMETRO IS NULL)
		;
END PERIODICIDADE_Select;
GO

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:44
  FUNCTION	: Select records from table GP_ROTINA filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE ROTINA_Select
(
    var_IDROTINA IN INTEGER  DEFAULT NULL,
    var_NOME IN VARCHAR2  DEFAULT NULL,
    var_DECRICAO IN VARCHAR2  DEFAULT NULL,
    var_DATACRIACAO IN DATE  DEFAULT NULL,
    var_USUARIO IN VARCHAR2  DEFAULT NULL,
    var_FUNCIONAL IN VARCHAR2  DEFAULT NULL,
    var_ATIVO IN INTEGER  DEFAULT NULL,
    var_APELIDO IN VARCHAR2  DEFAULT NULL
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			IDROTINA,
			NOME,
			DECRICAO,
			DATACRIACAO,
			USUARIO,
			FUNCIONAL,
			ATIVO,
			APELIDO
		FROM
			GP_ROTINA
		WHERE
			(IDROTINA = var_IDROTINA or var_IDROTINA is null)
		AND (NOME = var_NOME OR var_NOME IS NULL)
		AND (DECRICAO = var_DECRICAO OR var_DECRICAO IS NULL)
		AND (DATACRIACAO = var_DATACRIACAO OR var_DATACRIACAO IS NULL)
		AND (USUARIO = var_USUARIO OR var_USUARIO IS NULL)
		AND (FUNCIONAL = var_FUNCIONAL OR var_FUNCIONAL IS NULL)
		AND (ATIVO = var_ATIVO OR var_ATIVO IS NULL)
		AND (APELIDO = var_APELIDO OR var_APELIDO IS NULL)
		;
END ROTINA_Select;
GO

