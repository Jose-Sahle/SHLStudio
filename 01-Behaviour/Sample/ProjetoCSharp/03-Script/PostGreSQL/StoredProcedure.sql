/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_agendamento
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  agendamento_Insert
(
    integer,
    date,
    time without time zone,
    date,
    time without time zone,
    integer,
    integer
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_agendamento
    (
		"idrotina"
		,"datainicio"
		,"horainicio"
		,"datafim"
		,"horafim"
		,"intervalo"
		,"repeticao"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5,
		$6,
		$7
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION agendamento_Insert
(
    integer,
    date,
    time without time zone,
    date,
    time without time zone,
    integer,
    integer
) TO root;
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_dll
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  dll_Insert
(
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_dll
    (
		"idrotina"
		,"ordem"
		,"nome"
		,"assembly"
		,"dependencia"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dll_Insert
(
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
) TO root;
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_dllparametros
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  dllparametros_Insert
(
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_dllparametros
    (
		"iddll"
		,"nome"
		,"valor"
		,"tipo"
		,"formato"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dllparametros_Insert
(
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
) TO root;
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_email
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  email_Insert
(
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_email
    (
		"idrotina"
		,"from"
		,"to"
		,"subject"
		,"type"
		,"body"
		,"classificacao"
		,"anexo"
		,"ativo"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5,
		$6,
		$7,
		$8,
		$9
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION email_Insert
(
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
) TO root;
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_exceptions
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  exceptions_Insert
(
    integer,
    integer,
    integer,
    boolean,
    boolean
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_exceptions
    (
		"idrotina"
		,"tentativa"
		,"intervalo"
		,"enviaremail"
		,"enviarultimoemail"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION exceptions_Insert
(
    integer,
    integer,
    integer,
    boolean,
    boolean
) TO root;
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_periodicidade
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  periodicidade_Insert
(
    integer,
    integer,
    varchar(100)
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_periodicidade
    (
		"idrotina"
		,"tipo"
		,"parametro"
    )
    VALUES
    (
		$1,
		$2,
		$3
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION periodicidade_Insert
(
    integer,
    integer,
    varchar(100)
) TO root;
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_rotina
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  rotina_Insert
(
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_rotina
    (
		"nome"
		,"decricao"
		,"datacriacao"
		,"usuario"
		,"funcional"
		,"ativo"
		,"apelido"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5,
		$6,
		$7
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION rotina_Insert
(
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_agendamento
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION agendamento_Update
(
    integer,
    integer,
    date,
    time without time zone,
    date,
    time without time zone,
    integer,
    integer
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_agendamento 
	SET
		"idrotina" = $2
		,"datainicio" = $3
		,"horainicio" = $4
		,"datafim" = $5
		,"horafim" = $6
		,"intervalo" = $7
		,"repeticao" = $8
    WHERE 
		"idagendamento" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION agendamento_Update
(
    integer,
    integer,
    date,
    time without time zone,
    date,
    time without time zone,
    integer,
    integer
) TO root;


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_dll
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION dll_Update
(
    integer,
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_dll 
	SET
		"idrotina" = $2
		,"ordem" = $3
		,"nome" = $4
		,"assembly" = $5
		,"dependencia" = $6
    WHERE 
		"iddll" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dll_Update
(
    integer,
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
) TO root;


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_dllparametros
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION dllparametros_Update
(
    integer,
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_dllparametros 
	SET
		"iddll" = $2
		,"nome" = $3
		,"valor" = $4
		,"tipo" = $5
		,"formato" = $6
    WHERE 
		"iddllparametros" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dllparametros_Update
(
    integer,
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
) TO root;


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_email
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION email_Update
(
    integer,
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_email 
	SET
		"idrotina" = $2
		,"from" = $3
		,"to" = $4
		,"subject" = $5
		,"type" = $6
		,"body" = $7
		,"classificacao" = $8
		,"anexo" = $9
		,"ativo" = $10
    WHERE 
		"idemail" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION email_Update
(
    integer,
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
) TO root;


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_exceptions
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION exceptions_Update
(
    integer,
    integer,
    integer,
    integer,
    boolean,
    boolean
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_exceptions 
	SET
		"idrotina" = $2
		,"tentativa" = $3
		,"intervalo" = $4
		,"enviaremail" = $5
		,"enviarultimoemail" = $6
    WHERE 
		"idexceptions" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION exceptions_Update
(
    integer,
    integer,
    integer,
    integer,
    boolean,
    boolean
) TO root;


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_periodicidade
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION periodicidade_Update
(
    integer,
    integer,
    integer,
    varchar(100)
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_periodicidade 
	SET
		"idrotina" = $2
		,"tipo" = $3
		,"parametro" = $4
    WHERE 
		"idperiodicidade" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION periodicidade_Update
(
    integer,
    integer,
    integer,
    varchar(100)
) TO root;


/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_rotina
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION rotina_Update
(
    integer,
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_rotina 
	SET
		"nome" = $2
		,"decricao" = $3
		,"datacriacao" = $4
		,"usuario" = $5
		,"funcional" = $6
		,"ativo" = $7
		,"apelido" = $8
    WHERE 
		"idrotina" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION rotina_Update
(
    integer,
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_agendamento
**********************************************************/
CREATE OR REPLACE FUNCTION agendamento_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_agendamento
    WHERE idagendamento = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION agendamento_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_dll
**********************************************************/
CREATE OR REPLACE FUNCTION dll_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_dll
    WHERE iddll = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION dll_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_dllparametros
**********************************************************/
CREATE OR REPLACE FUNCTION dllparametros_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_dllparametros
    WHERE iddllparametros = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION dllparametros_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_email
**********************************************************/
CREATE OR REPLACE FUNCTION email_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_email
    WHERE idemail = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION email_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_exceptions
**********************************************************/
CREATE OR REPLACE FUNCTION exceptions_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_exceptions
    WHERE idexceptions = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION exceptions_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_periodicidade
**********************************************************/
CREATE OR REPLACE FUNCTION periodicidade_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_periodicidade
    WHERE idperiodicidade = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION periodicidade_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_rotina
**********************************************************/
CREATE OR REPLACE FUNCTION rotina_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_rotina
    WHERE idrotina = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION rotina_Delete
(
	integer
) TO root;
go

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_agendamento filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION agendamento_Select
(
    integer,
    integer,
    date,
    time without time zone,
    date,
    time without time zone,
    integer,
    integer
)RETURNS SETOF gp_agendamento
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"idagendamento",
			"idrotina",
			"datainicio",
			"horainicio",
			"datafim",
			"horafim",
			"intervalo",
			"repeticao"
		FROM
			gp_agendamento
		WHERE
			("idagendamento" = $1 or $1 is null)
  	    AND ("idrotina" = $2 OR $2 IS NULL)
  	    AND ("datainicio" = $3 OR $3 IS NULL)
  	    AND ("horainicio" = $4 OR $4 IS NULL)
  	    AND ("datafim" = $5 OR $5 IS NULL)
  	    AND ("horafim" = $6 OR $6 IS NULL)
  	    AND ("intervalo" = $7 OR $7 IS NULL)
  	    AND ("repeticao" = $8 OR $8 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION agendamento_Select
(
    integer,
    integer,
    date,
    time without time zone,
    date,
    time without time zone,
    integer,
    integer
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_dll filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION dll_Select
(
    integer,
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
)RETURNS SETOF gp_dll
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"iddll",
			"idrotina",
			"ordem",
			"nome",
			"assembly",
			"dependencia"
		FROM
			gp_dll
		WHERE
			("iddll" = $1 or $1 is null)
  	    AND ("idrotina" = $2 OR $2 IS NULL)
  	    AND ("ordem" = $3 OR $3 IS NULL)
  	    AND ("nome" = $4 OR $4 IS NULL)
  	    AND ("assembly" = $5 OR $5 IS NULL)
  	    AND ("dependencia" = $6 OR $6 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dll_Select
(
    integer,
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_dllparametros filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION dllparametros_Select
(
    integer,
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
)RETURNS SETOF gp_dllparametros
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"iddllparametros",
			"iddll",
			"nome",
			"valor",
			"tipo",
			"formato"
		FROM
			gp_dllparametros
		WHERE
			("iddllparametros" = $1 or $1 is null)
  	    AND ("iddll" = $2 OR $2 IS NULL)
  	    AND ("nome" = $3 OR $3 IS NULL)
  	    AND ("valor" = $4 OR $4 IS NULL)
  	    AND ("tipo" = $5 OR $5 IS NULL)
  	    AND ("formato" = $6 OR $6 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dllparametros_Select
(
    integer,
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_email filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION email_Select
(
    integer,
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
)RETURNS SETOF gp_email
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"idemail",
			"idrotina",
			"from",
			"to",
			"subject",
			"type",
			"body",
			"classificacao",
			"anexo",
			"ativo"
		FROM
			gp_email
		WHERE
			("idemail" = $1 or $1 is null)
  	    AND ("idrotina" = $2 OR $2 IS NULL)
  	    AND ("from" = $3 OR $3 IS NULL)
  	    AND ("to" = $4 OR $4 IS NULL)
  	    AND ("subject" = $5 OR $5 IS NULL)
  	    AND ("type" = $6 OR $6 IS NULL)
  	    AND ("body" = $7 OR $7 IS NULL)
  	    AND ("classificacao" = $8 OR $8 IS NULL)
  	    AND ("anexo" = $9 OR $9 IS NULL)
  	    AND ("ativo" = $10 OR $10 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION email_Select
(
    integer,
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_exceptions filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION exceptions_Select
(
    integer,
    integer,
    integer,
    integer,
    boolean,
    boolean
)RETURNS SETOF gp_exceptions
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"idexceptions",
			"idrotina",
			"tentativa",
			"intervalo",
			"enviaremail",
			"enviarultimoemail"
		FROM
			gp_exceptions
		WHERE
			("idexceptions" = $1 or $1 is null)
  	    AND ("idrotina" = $2 OR $2 IS NULL)
  	    AND ("tentativa" = $3 OR $3 IS NULL)
  	    AND ("intervalo" = $4 OR $4 IS NULL)
  	    AND ("enviaremail" = $5 OR $5 IS NULL)
  	    AND ("enviarultimoemail" = $6 OR $6 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION exceptions_Select
(
    integer,
    integer,
    integer,
    integer,
    boolean,
    boolean
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_periodicidade filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION periodicidade_Select
(
    integer,
    integer,
    integer,
    varchar(100)
)RETURNS SETOF gp_periodicidade
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"idperiodicidade",
			"idrotina",
			"tipo",
			"parametro"
		FROM
			gp_periodicidade
		WHERE
			("idperiodicidade" = $1 or $1 is null)
  	    AND ("idrotina" = $2 OR $2 IS NULL)
  	    AND ("tipo" = $3 OR $3 IS NULL)
  	    AND ("parametro" = $4 OR $4 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION periodicidade_Select
(
    integer,
    integer,
    integer,
    varchar(100)
) TO root;

/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Select records from table gp_rotina filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION rotina_Select
(
    integer,
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
)RETURNS SETOF gp_rotina
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"idrotina",
			"nome",
			"decricao",
			"datacriacao",
			"usuario",
			"funcional",
			"ativo",
			"apelido"
		FROM
			gp_rotina
		WHERE
			("idrotina" = $1 or $1 is null)
  	    AND ("nome" = $2 OR $2 IS NULL)
  	    AND ("decricao" = $3 OR $3 IS NULL)
  	    AND ("datacriacao" = $4 OR $4 IS NULL)
  	    AND ("usuario" = $5 OR $5 IS NULL)
  	    AND ("funcional" = $6 OR $6 IS NULL)
  	    AND ("ativo" = $7 OR $7 IS NULL)
  	    AND ("apelido" = $8 OR $8 IS NULL)

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION rotina_Select
(
    integer,
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
) TO root;

