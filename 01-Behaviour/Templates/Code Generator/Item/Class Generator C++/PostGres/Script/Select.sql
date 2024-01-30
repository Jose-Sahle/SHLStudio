/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Select records from table #TABLE# filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE FUNCTION #TABLEWITHOUTPREFIXTABLE#_Select
(
    #TYPEPRIMARYKEYPOSTGRESQL#,
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
)RETURNS SETOF #TABLE#
AS
$$
DECLARE query record;
BEGIN
	FOR query in
		SELECT
			"#PRIMARYKEY#",
			<allfieldslessprimarykey>
			"#FIELD#"#COMMAAFTER#
			</allfieldslessprimarykey>
		FROM
			#TABLE#
		WHERE
			("#PRIMARYKEY#" = $1 or $1 is null)
			<allfieldslessprimarykey>2
  	    AND ("#FIELD#" = $#COUNT# OR $#COUNT# IS NULL)
			</allfieldslessprimarykey>       

		LOOP
		RETURN NEXT query;
	END LOOP;
END
$$
LANGUAGE 'plpgsql' VOLATILE;

GRANT EXECUTE ON FUNCTION #TABLEWITHOUTPREFIXTABLE#_Select
(
    #TYPEPRIMARYKEYPOSTGRESQL#,
    <allfieldslessprimarykey>
    #TYPEDBPOSTGRESQL##COMMAAFTER#
    </allfieldslessprimarykey>
) TO #GRANTUSER#;
