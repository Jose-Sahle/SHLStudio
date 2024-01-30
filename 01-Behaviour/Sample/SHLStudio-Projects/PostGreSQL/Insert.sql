/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Insert a record in the table #TABLE#
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION  #TABLEWITHOUTPREFIXTABLE#_Insert
(
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
)RETURNS BIGINT 
AS
$$
BEGIN
    INSERT INTO #TABLE#
    (
		<allfieldslessprimarykey>
		#COMMABEFORE#"#FIELD#"
		</allfieldslessprimarykey>
    )
    VALUES
    (
		<allfieldslessprimarykey>
		$#COUNT##COMMAAFTER#
		</allfieldslessprimarykey>
    );
	
    RETURN LASTVAL(); 
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION #TABLEWITHOUTPREFIXTABLE#_Insert
(
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
) TO #GRANTUSER#;