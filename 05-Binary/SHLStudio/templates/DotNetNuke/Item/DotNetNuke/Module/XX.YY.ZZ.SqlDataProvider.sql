<alltables>
/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  TABLE		: #TABLE#
  #DESCRIPTION#
**********************************************************/
/* INSERT */
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'{databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Insert]') AND OBJECTPROPERTY(id, N'IsProcedure') = 1)
	DROP PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Insert]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Insert]
(
	<allfieldslessprimarykey>
	@#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
	</allfieldslessprimarykey>
) 
AS
BEGIN
	INSERT INTO {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#]
	(
		<allfieldslessprimarykey>
		#COMMABEFORE#[#FIELD#]
		</allfieldslessprimarykey>
	)
	VALUES
	(
		<allfieldslessprimarykey>
		#COMMABEFORE#@#FIELD#
		</allfieldslessprimarykey>
	)
	
	SELECT SCOPE_IDENTITY()
END
GO


/* UPDATE */
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'{databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Update]') AND OBJECTPROPERTY(id, N'IsProcedure') = 1)
	DROP PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Update]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Update]
(
	 @#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER#,
	<allfieldslessprimarykey>
	@#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
	</allfieldslessprimarykey>
)
AS
BEGIN
	UPDATE 
		{databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#]
	SET
		<allfieldslessprimarykey>
		#COMMABEFORE#[#FIELD#] = @#FIELD#
		</allfieldslessprimarykey>
	WHERE 
		[#PRIMARYKEY#] = @#PRIMARYKEY#
END
GO

/* DELETE */
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'{databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Delete]') AND OBJECTPROPERTY(id, N'IsProcedure') = 1)
	DROP PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Delete]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Delete]
(
	@#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER#
)
AS
BEGIN
	DELETE FROM {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#]
	WHERE [#PRIMARYKEY#] = @#PRIMARYKEY#
END
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'{databaseOwner}.[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_DeleteList]') AND OBJECTPROPERTY(id, N'IsProcedure') = 1)
	DROP PROCEDURE{databaseOwner}.[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_DeleteList]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE {databaseOwner}.[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_DeleteList]
(
    @#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER# = NULL,
    <allfieldslessprimarykey>
    @#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
    </allfieldslessprimarykey>
)
AS
BEGIN
	DELETE FROM {databaseOwner}.[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#]
	WHERE 
		([#PRIMARYKEY#] = @#PRIMARYKEY# OR @#PRIMARYKEY# IS NULL)
		<allfieldslessprimarykey>
	  AND ([#FIELD#] = @#FIELD# OR @#FIELD# IS NULL)
		</allfieldslessprimarykey>       
END
GO

/* SELECT */
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'{databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Select]') AND OBJECTPROPERTY(id, N'IsProcedure') = 1)
	DROP PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Select]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE {databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#_Select]
(
    @#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER# = NULL,
    <allfieldslessprimarykey>
    @#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
    </allfieldslessprimarykey>
)
AS
BEGIN
    SELECT
		[#PRIMARYKEY#],
		<allfieldslessprimarykey>
		[#FIELD#]#COMMAAFTER#
		</allfieldslessprimarykey>
    FROM 
		{databaseOwner}[{objectQualifier}#TABLEWITHOUTPREFIXTABLE#] WITH (NOLOCK)
    WHERE 
		([#PRIMARYKEY#] = @#PRIMARYKEY# OR @#PRIMARYKEY# IS NULL)
		<allfieldslessprimarykey>
	  AND ([#FIELD#] = @#FIELD# OR @#FIELD# IS NULL)
		</allfieldslessprimarykey>       
END
GO
