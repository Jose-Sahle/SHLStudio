/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Insert a record in the table gp_rotina
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  rotina_Insert
(
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
    INSERT INTO gp_rotina
    (
		"nome"
		,"decricao"
		,"datacriacao"
		,"usuario"
		,"funcional"
		,"ativo"
		,"apelido"
    )
    VALUES
    (
		$1,
		$2,
		$3,
		$4,
		$5,
		$6,
		$7
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION rotina_Insert
(
    varchar(50),
    varchar(255),
    date,
    varchar(20),
    varchar(20),
    boolean,
    varchar(50)
) TO root;
