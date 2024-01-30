/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Delete a record in the table #TABLE#
**********************************************************/
CREATE OR REPLACE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Delete
(
    var_#PRIMARYKEY# IN #TYPEPRIMARYKEYORACLE#  DEFAULT NULL,
    <allfieldslessprimarykey>
    var_#FIELD# IN #TYPEDBORACLE#  DEFAULT NULL#COMMAAFTER#
    </allfieldslessprimarykey>
)
IS
BEGIN
    DELETE FROM #TABLE#
    WHERE #PRIMARYKEY# = var_#PRIMARYKEY#;
END #TABLEWITHOUTPREFIXTABLE#_Delete;
GO

CREATE OR REPLACE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_DeleteList
(
	var_#PRIMARYKEY# IN #TYPEPRIMARYKEYORACLE#
)
IS
BEGIN
    DELETE FROM #TABLE#
	WHERE
		(#PRIMARYKEY# = var_#PRIMARYKEY# or var_#PRIMARYKEY# is null)
		<allfieldslessprimarykey>
	AND (#FIELD# = var_#FIELD# OR var_#FIELD# IS NULL)
		</allfieldslessprimarykey>       
	;
END #TABLEWITHOUTPREFIXTABLE#_DeleteList;
GO
