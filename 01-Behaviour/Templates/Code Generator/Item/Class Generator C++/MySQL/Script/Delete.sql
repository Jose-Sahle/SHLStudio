/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Delete a record in the table #TABLE#
**********************************************************/
DROP PROCEDURE IF EXISTS #TABLEWITHOUTPREFIXTABLE#_Delete
GO
CREATE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Delete
(
    var_#PRIMARYKEY# #TYPEPRIMARYKEYMYSQL#,
    <allfieldslessprimarykey>
    var_#FIELD# #TYPEDBMYSQL##COMMAAFTER#
    </allfieldslessprimarykey>
)
BEGIN
    DELETE FROM #TABLE#
    WHERE `#PRIMARYKEY#` = var_#PRIMARYKEY#;
	
END
GO

DROP PROCEDURE IF EXISTS #TABLEWITHOUTPREFIXTABLE#_DeleteList
GO
CREATE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_DeleteList
(
	var_#PRIMARYKEY# #TYPEPRIMARYKEYMYSQL#
)
BEGIN
    DELETE FROM #TABLE#
	WHERE
		(`#PRIMARYKEY#` = var_#PRIMARYKEY# or var_#PRIMARYKEY# is null)
		<allfieldslessprimarykey>
	AND (`#FIELD#` = var_#FIELD# OR var_#FIELD# IS NULL)
		</allfieldslessprimarykey>
		;	
END
GO
