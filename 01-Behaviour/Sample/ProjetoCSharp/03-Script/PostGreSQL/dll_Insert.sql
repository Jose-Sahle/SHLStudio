/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_dll
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  dll_Insert
(
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_dll
    (
		"idrotina"
		,"ordem"
		,"nome"
		,"assembly"
		,"dependencia"
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

GRANT EXECUTE ON FUNCTION dll_Insert
(
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
) TO root;
