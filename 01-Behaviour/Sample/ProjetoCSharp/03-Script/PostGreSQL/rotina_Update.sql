
/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Update a record in the table gp_rotina
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION rotina_Update
(
    integer,
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		gp_rotina 
	SET
		"nome" = $2
		,"decricao" = $3
		,"datacriacao" = $4
		,"usuario" = $5
		,"funcional" = $6
		,"ativo" = $7
		,"apelido" = $8
    WHERE 
		"idrotina" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION rotina_Update
(
    integer,
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
) TO root;

