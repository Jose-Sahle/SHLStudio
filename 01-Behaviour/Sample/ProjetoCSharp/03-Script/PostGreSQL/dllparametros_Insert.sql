/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_dllparametros
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  dllparametros_Insert
(
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO gp_dllparametros
    (
		"iddll"
		,"nome"
		,"valor"
		,"tipo"
		,"formato"
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

GRANT EXECUTE ON FUNCTION dllparametros_Insert
(
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
) TO root;
