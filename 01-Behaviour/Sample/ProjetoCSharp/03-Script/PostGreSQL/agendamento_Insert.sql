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
