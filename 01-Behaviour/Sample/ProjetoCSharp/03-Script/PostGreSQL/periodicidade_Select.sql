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

