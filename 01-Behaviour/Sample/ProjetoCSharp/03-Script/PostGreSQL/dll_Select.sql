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

