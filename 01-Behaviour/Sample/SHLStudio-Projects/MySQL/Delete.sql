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
	var_#PRIMARYKEY# #TYPEPRIMARYKEYMYSQL#
)
BEGIN
    DELETE FROM #TABLE#
    WHERE `#PRIMARYKEY#` = var_#PRIMARYKEY#;
	
END
GO

