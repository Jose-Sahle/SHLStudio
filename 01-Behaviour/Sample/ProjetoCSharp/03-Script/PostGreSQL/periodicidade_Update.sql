
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

