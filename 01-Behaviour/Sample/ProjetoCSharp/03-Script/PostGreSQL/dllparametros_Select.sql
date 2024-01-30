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

