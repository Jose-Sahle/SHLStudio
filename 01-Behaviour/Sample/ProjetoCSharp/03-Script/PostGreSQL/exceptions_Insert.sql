/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_exceptions
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  exceptions_Insert
(
    integer,
    integer,
    integer,
    boolean,
    boolean
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_exceptions
    (
		"idrotina"
		,"tentativa"
		,"intervalo"
		,"enviaremail"
		,"enviarultimoemail"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION exceptions_Insert
(
    integer,
    integer,
    integer,
    boolean,
    boolean
) TO root;
