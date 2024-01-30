/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Delete a record in the table #TABLE#
**********************************************************/
CREATE OR REPLACE FUNCTION #TABLEWITHOUTPREFIXTABLE#_DeleteList
(
    #TYPEPRIMARYKEYPOSTGRESQL#,
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
)RETURNS BIGINT
AS 
$$
BEGIN
    DELETE FROM #TABLE#
	WHERE
		("#PRIMARYKEY#" = $1 or $1 is null)
		<allfieldslessprimarykey>2
	AND ("#FIELD#" = $#COUNT# OR $#COUNT# IS NULL)
		</allfieldslessprimarykey>       
    
    RETURN 0;
END;
$$
LANGUAGE 'plpgsql' VOLATILE;
go

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

GRANT EXECUTE ON FUNCTION #TABLEWITHOUTPREFIXTABLE#_DeleteList
(
	#TYPEPRIMARYKEYPOSTGRESQL#
) TO #GRANTUSER#;
go
