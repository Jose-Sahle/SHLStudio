/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Select records from table #TABLE# filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Select
(
    var_#PRIMARYKEY# IN #TYPEPRIMARYKEYORACLE#  DEFAULT NULL,
    <allfieldslessprimarykey>
    var_#FIELD# IN #TYPEDBORACLE#  DEFAULT NULL#COMMAAFTER#
    </allfieldslessprimarykey>
    ,returnset    OUT SYS_REFCURSOR
) 
IS
BEGIN
	OPEN returnset FOR
		SELECT
			#PRIMARYKEY#,
			<allfieldslessprimarykey>
			#FIELD##COMMAAFTER#
			</allfieldslessprimarykey>
		FROM
			#TABLE#
		WHERE
			(#PRIMARYKEY# = var_#PRIMARYKEY# or var_#PRIMARYKEY# is null)
			<allfieldslessprimarykey>
		AND (#FIELD# = var_#FIELD# OR var_#FIELD# IS NULL)
			</allfieldslessprimarykey>       
		;
END #TABLEWITHOUTPREFIXTABLE#_Select;
GO
