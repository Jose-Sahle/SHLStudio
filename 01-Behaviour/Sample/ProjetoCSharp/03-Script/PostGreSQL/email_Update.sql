
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_email
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION email_Update
(
    integer,
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_email 
	SET
		"idrotina" = $2
		,"from" = $3
		,"to" = $4
		,"subject" = $5
		,"type" = $6
		,"body" = $7
		,"classificacao" = $8
		,"anexo" = $9
		,"ativo" = $10
    WHERE 
		"idemail" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION email_Update
(
    integer,
    integer,
    varchar(8000),
    varchar(8000),
    varchar(500),
    varchar(5),
    varchar(8000),
    integer,
    varchar(8000),
    boolean
) TO root;

