/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Select records from table #TABLE# filtered by 
		  parameters passed into the procedure
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS #TABLEWITHOUTPREFIXTABLE#_Select
GO
CREATE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Select
(
    var_#PRIMARYKEY# #TYPEPRIMARYKEYMYSQL#,
    <allfieldslessprimarykey>
    var_#FIELD# #TYPEDBMYSQL##COMMAAFTER#
    </allfieldslessprimarykey>
)
BEGIN
	SELECT
		`#PRIMARYKEY#`,
		<allfieldslessprimarykey>
		`#FIELD#`#COMMAAFTER#
		</allfieldslessprimarykey>
	FROM
		#TABLE#
	WHERE
		(`#PRIMARYKEY#` = var_#PRIMARYKEY# or var_#PRIMARYKEY# is null)
		<allfieldslessprimarykey>
	AND (`#FIELD#` = var_#FIELD# OR var_#FIELD# IS NULL)
		</allfieldslessprimarykey>
		;
END
GO
