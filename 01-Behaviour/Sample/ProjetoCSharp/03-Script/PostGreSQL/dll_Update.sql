
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_dll
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION dll_Update
(
    integer,
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_dll 
	SET
		"idrotina" = $2
		,"ordem" = $3
		,"nome" = $4
		,"assembly" = $5
		,"dependencia" = $6
    WHERE 
		"iddll" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION dll_Update
(
    integer,
    integer,
    integer,
    varchar(100),
    varchar(100),
    integer
) TO root;

