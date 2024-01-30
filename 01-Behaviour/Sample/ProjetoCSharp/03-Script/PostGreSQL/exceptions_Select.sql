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

