/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Delete a record in the table #TABLE#
**********************************************************/
CREATE OR REPLACE FUNCTION #TABLEWITHOUTPREFIXTABLE#_Delete
(
	#TYPEPRIMARYKEYPOSTGRESQL#
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM #TABLE#
    WHERE #PRIMARYKEY# = $1;
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

GRANT EXECUTE ON FUNCTION #TABLEWITHOUTPREFIXTABLE#_Delete
(
	#TYPEPRIMARYKEYPOSTGRESQL#
) TO #GRANTUSER#;
go
