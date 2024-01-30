/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_email
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  email_Insert
(
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
    INSERT INTO gp_email
    (
		"idrotina"
		,"from"
		,"to"
		,"subject"
		,"type"
		,"body"
		,"classificacao"
		,"anexo"
		,"ativo"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5,
		$6,
		$7,
		$8,
		$9
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION email_Insert
(
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
