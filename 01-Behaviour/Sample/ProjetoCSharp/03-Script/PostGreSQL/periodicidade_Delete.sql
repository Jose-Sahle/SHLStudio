/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
  FUNCTION	: Delete a record in the table gp_periodicidade
**********************************************************/
CREATE OR REPLACE FUNCTION periodicidade_Delete
(
	integer
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM gp_periodicidade
    WHERE idperiodicidade = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION periodicidade_Delete
(
	integer
) TO root;
go

