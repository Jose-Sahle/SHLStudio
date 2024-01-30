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

