drop procedure agendamento_delete
go
drop procedure agendamento_insert
go
drop procedure agendamento_select
go
drop procedure agendamento_update
go
drop procedure dll_delete
go
drop procedure dll_insert
go
drop procedure dll_select
go
drop procedure dll_update
go
drop procedure dllparametros_delete
go
drop procedure dllparametros_insert
go
drop procedure dllparametros_select
go
drop procedure dllparametros_update
go
drop procedure email_delete
go
drop procedure email_insert
go
drop procedure email_select
go
drop procedure email_update
go
drop procedure exceptions_delete
go
drop procedure exceptions_insert
go
drop procedure exceptions_select
go
drop procedure exceptions_update
go
drop procedure periodicidade_delete
go
drop procedure periodicidade_insert
go
drop procedure periodicidade_select
go
drop procedure periodicidade_update
go
drop procedure rotina_delete
go
drop procedure rotina_inserto
go
drop procedure rotina_select
go
drop procedure rotina_update 
go 

DROP TRIGGER rotina_trigger
GO
DROP TRIGGER exceptions_trigger
GO

DROP TRIGGER periodicidade_trigger
GO

DROP TRIGGER email_trigger
GO

DROP TRIGGER agendamento_trigger
GO

DROP TRIGGER dll_trigger
GO

DROP TRIGGER dllparametros_trigger
GO

DROP SEQUENCE rotina_seq
GO

DROP SEQUENCE exceptions_seq
GO

DROP SEQUENCE periodicidade_seq
GO

DROP SEQUENCE email_seq
GO

DROP SEQUENCE agendamento_seq
GO

DROP SEQUENCE dll_seq
GO

DROP SEQUENCE dllparametros_seq
GO

DROP TABLE GP_DLLParametros
GO
DROP TABLE GP_DLL
GO

DROP TABLE GP_AGENDAMENTO
GO

DROP TABLE GP_EMAIL
GO

DROP TABLE GP_PERIODICIDADE
GO

DROP TABLE GP_EXCEPTIONS
GO

DROP TABLE GP_ROTINA
GO

CREATE TABLE GP_ROTINA 
(
    idRotina NUMBER(10) NOT NULL,
    Nome VARCHAR(50) NOT NULL,
    Decricao VARCHAR(255) NOT NULL,
    DataCriacao DATE NOT NULL,
    Usuario VARCHAR(20)  NULL,
    Funcional VARCHAR(20) NULL,
    Ativo INTEGER NOT NULL,
    Apelido VARCHAR(50) NULL,
    CONSTRAINT ROTINA_pk PRIMARY KEY (idRotina)
);
GO

CREATE SEQUENCE rotina_seq;
GO

CREATE OR REPLACE TRIGGER rotina_trigger
BEFORE INSERT ON GP_ROTINA 
FOR EACH ROW
WHEN (new.idRotina IS NULL)
BEGIN
  SELECT rotina_seq.NEXTVAL
  INTO   :new.idRotina
  FROM   dual;
END;
GO

CREATE TABLE GP_EXCEPTIONS 
(
	idExceptions NUMBER(10) NOT NULL,
	idRotina NUMBER(10) NULL,
	Tentativa INTEGER NOT NULL,
	Intervalo INTEGER NOT NULL,
	EnviarEmail INTEGER NOT NULL,
	EnviarUltimoEmail INTEGER NOT NULL,
	CONSTRAINT exceptions_pk PRIMARY KEY (idExceptions),
	CONSTRAINT exceptions_rotina_fk
		FOREIGN KEY (idRotina)
			REFERENCES GP_ROTINA(idRotina)
);
GO

CREATE SEQUENCE exceptions_seq;
GO

CREATE OR REPLACE TRIGGER exceptions_trigger
BEFORE INSERT ON GP_Exceptions  
FOR EACH ROW
WHEN (new.idExceptions IS NULL)
BEGIN
  SELECT exceptions_seq.NEXTVAL
  INTO   :new.idExceptions
  FROM   dual;
END;
GO

CREATE TABLE GP_PERIODICIDADE 
(
	idPeriodicidade NUMBER(10) NOT NULL,
	idRotina NUMBER(10) NULL,
	Tipo INTEGER NOT NULL,
	Parametro VARCHAR(100) NOT NULL,
	CONSTRAINT periodicidade_pk PRIMARY KEY (idPeriodicidade),
	CONSTRAINT periodicidade_rotina_fk
		FOREIGN KEY (idRotina)
			REFERENCES GP_ROTINA(idRotina)
);
GO

CREATE SEQUENCE periodicidade_seq;
GO

CREATE OR REPLACE TRIGGER periodicidade_trigger
BEFORE INSERT ON GP_PERIODICIDADE  
FOR EACH ROW
WHEN (new.idPeriodicidade IS NULL)
BEGIN
  SELECT periodicidade_seq.NEXTVAL
  INTO   :new.idPeriodicidade
  FROM   dual;
END;
GO

CREATE TABLE GP_EMAIL 
(
	idEMAIL NUMBER(10) NOT NULL,
	idRotina NUMBER(10) NULL,
	FROMEMAIL VARCHAR(4000) NULL,
	TOEMAIL VARCHAR(4000) NULL,
	SUBJECTEMAIL VARCHAR(500) NULL,
	TYPEEMAIL VARCHAR(5) NULL,
	BODYEMAIL VARCHAR(4000) NULL,
	Classificacao INTEGER NULL,
	Anexo VARCHAR(4000) NOT NULL,
	Ativo INTEGER NULL,
	CONSTRAINT email_pk PRIMARY KEY (idEMAIL),
	CONSTRAINT email_rotina_fk
		FOREIGN KEY (idRotina)
			REFERENCES GP_ROTINA(idRotina)
);
GO

CREATE SEQUENCE email_seq;
GO

CREATE OR REPLACE TRIGGER email_trigger
BEFORE INSERT ON GP_EMAIL  
FOR EACH ROW
WHEN (new.idEMAIL IS NULL)
BEGIN
  SELECT email_seq.NEXTVAL
  INTO   :new.idEMAIL
  FROM   dual;
END;
GO

CREATE TABLE GP_AGENDAMENTO 
(
	idAgendamento NUMBER(10) NOT NULL,
	idRotina NUMBER(10) NULL,
	DataInicio DATE NOT NULL,
	HoraInicio CHAR(8) NOT NULL,
	DataFim DATE  NULL,
	HoraFim CHAR(8) NULL,
	Intervalo INTEGER NOT NULL,
	Repeticao INTEGER NOT NULL,
	CONSTRAINT agendamento_pk PRIMARY KEY (idAgendamento),
	CONSTRAINT agendamento_rotina_fk
		FOREIGN KEY (idRotina)
			REFERENCES GP_ROTINA(idRotina)
);
GO

CREATE SEQUENCE agendamento_seq;
GO

CREATE OR REPLACE TRIGGER agendamento_trigger
BEFORE INSERT ON GP_AGENDAMENTO 
FOR EACH ROW
WHEN (new.idAgendamento IS NULL)
BEGIN
  SELECT agendamento_seq.NEXTVAL
  INTO   :new.idAgendamento
  FROM   dual;
END;
GO

CREATE TABLE GP_DLL 
(
	idDLL NUMBER(10) NOT NULL,
	idRotina NUMBER(10) NULL,
	Ordem INTEGER NOT NULL,
	Nome VARCHAR(100) NULL,
	Assembly VARCHAR(100) NOT NULL,
	Dependencia INTEGER NOT NULL,
	CONSTRAINT dll_pk PRIMARY KEY (idDLL),
	CONSTRAINT dll_rotina_fk
		FOREIGN KEY (idRotina)
			REFERENCES GP_ROTINA(idRotina)
);
GO

CREATE SEQUENCE dll_seq;
GO

CREATE OR REPLACE TRIGGER dll_trigger
BEFORE INSERT ON GP_DLL 
FOR EACH ROW
WHEN (new.idDLL IS NULL)
BEGIN
  SELECT dll_seq.NEXTVAL
  INTO   :new.idDLL
  FROM   dual;
END;
GO

CREATE TABLE GP_DLLParametros 
(
	idDLLParametros NUMBER(10) NOT NULL,
	idDLL NUMBER(10) NULL,
	Nome VARCHAR(50) NOT NULL,
	Valor VARCHAR(4000) NOT NULL,
	Tipo INTEGER NOT NULL,
	Formato VARCHAR(2) NOT NULL,
	CONSTRAINT dllparametros_pk PRIMARY KEY (idDLLParametros),
	CONSTRAINT dllparametros_dll_fk
		FOREIGN KEY (idDLL)
			REFERENCES GP_DLL(idDLL)
);
GO

CREATE SEQUENCE dllparametros_seq;
GO

CREATE OR REPLACE TRIGGER dllparametros_trigger
BEFORE INSERT ON GP_DLLParametros 
FOR EACH ROW
WHEN (new.idDLLParametros IS NULL)
BEGIN
  SELECT dllparametros_seq.NEXTVAL
  INTO   :new.idDLLParametros
  FROM   dual;
END;
GO
