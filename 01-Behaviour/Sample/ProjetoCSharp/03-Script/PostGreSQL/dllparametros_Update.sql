
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_dllparametros
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION dllparametros_Update
(
    integer,
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_dllparametros 
	SET
		"iddll" = $2
		,"nome" = $3
		,"valor" = $4
		,"tipo" = $5
		,"formato" = $6
    WHERE 
		"iddllparametros" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dllparametros_Update
(
    integer,
    integer,
    varchar(50),
    varchar(8000),
    integer,
    varchar(2)
) TO root;

