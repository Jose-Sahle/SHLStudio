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

