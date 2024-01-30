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

