DROP TABLE gp_dllparametros 
DROP TABLE gp_dll 
DROP TABLE gp_agendamento 
DROP TABLE gp_email 
DROP TABLE gp_periodicidade 
DROP TABLE gp_exceptions
DROP TABLE gp_rotina 
GO

create table gp_rotina 
(
    idrotina serial not null,
    nome varchar(50) not null,
    decricao varchar(255) not null,
    datacriacao date not null,
    usuario varchar(20)  null,
    funcional varchar(20) null,
    ativo boolean not null,
    apelido varchar(50) null,
    CONSTRAINT gp_rotina_pk PRIMARY KEY (idrotina)
)
go

create table gp_exceptions 
(
  idexceptions serial not null,
  idrotina integer null references gp_rotina(idrotina),
  tentativa integer not null,
  intervalo integer not null,
  enviaremail boolean not null,
  enviarultimoemail boolean not null,
  CONSTRAINT gp_exceptions_pk PRIMARY KEY (idexceptions)
)
go

create table gp_periodicidade 
(
  idperiodicidade serial not null,
  idrotina integer null references gp_rotina(idrotina),
  tipo integer not null,
  parametro varchar(100) not null,
  CONSTRAINT gp_periodicidade_pk PRIMARY KEY (idperiodicidade)
)
go

create table gp_email 
(
  idemail serial not null,
  idrotina integer null references gp_rotina(idrotina),
  "from" varchar(8000) null,
  "to" varchar(8000) null,
  subject varchar(500) null,
  "type" varchar(5) null,
  body varchar(8000) null,
  classificacao integer null,
  anexo varchar(8000) not null,
  ativo boolean null,
  CONSTRAINT gp_email_pk PRIMARY KEY (idemail)
)
go

create table gp_agendamento 
(
  idagendamento serial not null,
  idrotina integer null references gp_rotina(idrotina),
  datainicio date not null,
  horainicio time not null,
  datafim date null,
  horafim time  null,
  intervalo integer not null,
  repeticao integer not null,
  CONSTRAINT gp_agendamento_pk PRIMARY KEY (idagendamento)
)
go

create table gp_dll 
(
  iddll serial not null,
  idrotina integer null references gp_rotina(idrotina),
  ordem integer not null,
  nome varchar(100) null,
  assembly varchar(100) not null,
  dependencia integer not null,
  CONSTRAINT gp_dll_pk PRIMARY KEY (iddll)
)
go

create table gp_dllparametros 
(
  iddllparametros serial not null,
  iddll integer null references gp_dll(iddll),
  nome varchar(50) not null,
  valor varchar(8000) not null,
  tipo integer not null,
  formato varchar(2) not null,
  CONSTRAINT gp_dllparametros_pk PRIMARY KEY (iddllparametros)
)
go

