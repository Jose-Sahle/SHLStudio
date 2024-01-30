
/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Update a record in the table #TABLE#
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION #TABLEWITHOUTPREFIXTABLE#_Update
(
    #TYPEPRIMARYKEYPOSTGRESQL#,
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
)RETURNS BIGINT
AS 
$$
BEGIN
    UPDATE 
		#TABLE# 
	SET
		<allfieldslessprimarykey>2
		#COMMABEFORE#"#FIELD#" = $#COUNT#
		</allfieldslessprimarykey>
    WHERE 
		"#PRIMARYKEY#" = $1;
		
	RETURN 0;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION #TABLEWITHOUTPREFIXTABLE#_Update
(
    #TYPEPRIMARYKEYPOSTGRESQL#,
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
) TO #GRANTUSER#;
