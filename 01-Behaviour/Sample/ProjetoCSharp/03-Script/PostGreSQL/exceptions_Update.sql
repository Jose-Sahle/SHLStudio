
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_exceptions
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION exceptions_Update
(
    integer,
    integer,
    integer,
    integer,
    boolean,
    boolean
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_exceptions 
	SET
		"idrotina" = $2
		,"tentativa" = $3
		,"intervalo" = $4
		,"enviaremail" = $5
		,"enviarultimoemail" = $6
    WHERE 
		"idexceptions" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION exceptions_Update
(
    integer,
    integer,
    integer,
    integer,
    boolean,
    boolean
) TO root;

