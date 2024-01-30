
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

