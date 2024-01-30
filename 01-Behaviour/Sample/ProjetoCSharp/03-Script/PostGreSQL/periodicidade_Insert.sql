/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_periodicidade
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  periodicidade_Insert
(
    integer,
    integer,
    varchar(100)
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_periodicidade
    (
		"idrotina"
		,"tipo"
		,"parametro"
    )
    VALUES
    (
		$1,
		$2,
		$3
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION periodicidade_Insert
(
    integer,
    integer,
    varchar(100)
) TO root;
