#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <iostream>
#include <vector>
#include "mainwin.hpp"

const auto USER_SQL = QLatin1String(R"(
        create table if not exists users(id integer primary key autoincrement, usuario varchar,
             senha varchar, funcao integer, foreign key(funcao) references funcoes(id))
      )");

const auto FUNC_SQL = QLatin1String(R"(
      create table if not exists funcoes(id integer primary key autoincrement, funcao varchar)
      )");

const auto INGREDIENTES_SQL = QLatin1String(R"(
      create table if not exists ingredientes(id integer primary key autoincrement, tipo varchar, quantidade integer)
      )");
//avisos para gerente
const auto MENSAGENS_SQL = QLatin1String(R"(
      create table if not exists mensagens(id integer primary key autoincrement, texto text)
      )");

const auto PEDIDOS_SQL = QLatin1String(R"(
      create table if not exists pedidos(id integer primary key autoincrement, mesa integer, produto integer, quantidade integer, status_p varchar,
                foreign key(mesa) references mesas(id), foreign key(produto) references produtos(id))
      )");

const auto LIMPEZA_SQL = QLatin1String(R"(
      create table if not exists limpeza(id integer primary key autoincrement, local varchar)
      )");

const auto MESAS_SQL = QLatin1String(R"(
      create table if not exists mesas(id integer primary key, rodizios integer, garcom varchar, status varchar)
      )");

const auto PRODUTOS_SQL = QLatin1String(R"(
      create table if not exists produtos(id integer primary key autoincrement, nome varchar, custo real)
      )");

const auto RECEITAS_SQL = QLatin1String(R"(
      create table if not exists receitas(id integer primary key autoincrement, produto_id integer, ingrediente_id interger, quantidade integer,
                foreign key(produto_id) references produtos(id), foreign key(ingrediente_id) references ingredientes(id))
      )");

const auto RGISTRO_MESAS_SQL = QLatin1String(R"(
      create table if not exists registro_mesas(id integer primary key autoincrement, mesa integer, rodizios integer, garcom varchar)
      )");

const auto INSERT_USER_SQL = QLatin1String(R"(
      insert into users(usuario, senha, funcao) values(?, ?, ?)
      )");

const auto INSERT_FUNCOES_SQL = QLatin1String(R"(
      insert into funcoes(funcao) values(?)
      )");

const auto INSERT_INGREDIENTES_SQL = QLatin1String(R"(
      insert into ingredientes(tipo, quantidade) values(?, ?)
      )");
const auto INSERT_MENSAGENS_SQL = QLatin1String(R"(
      insert into mensagens(texto) values(?)
      )");

const auto INSERT_LIMPEZA_SQL = QLatin1String(R"(
      insert into limpeza(local) values(?)
      )");

const auto INSERT_MESAS_SQL = QLatin1String(R"(
      insert into mesas(id, rodizios, garcom, status) values(?, ?, ?, ?)
      )");

const auto INSERT_RECEITAS_SQL = QLatin1String(R"(
      insert into receitas(produto_id, ingrediente_id, quantidade) values(?, ?, ?)
      )");

const auto INSERT_PRODUTOS_SQL = QLatin1String(R"(
      insert into produtos(nome, custo) values(?, ?)
      )");

const auto INSERT_PEDIDOS_SQL = QLatin1String(R"(
      insert into pedidos(mesa, produto, quantidade, status_p) values(?, ?, ?, ?)
      )");

const auto INSERT_REGISTRO_MESAS_SQL = QLatin1String(R"(
      insert into registro_mesas(mesa, rodizios, garcom) values(?, ?, ?)
      )");

QSqlError initdb();
void add_user(QSqlQuery &q, const QString usuario, const QString senha, const QVariant funcao);
QVariant add_funcoes(QSqlQuery &q, const QString funcao);
QVariant add_ingrediente(QSqlQuery &q, const QString tipo, int quantidade);
QVariant add_mesas(QSqlQuery &q, int mesa, int rodizios, const QString garcom, const QString status);
void add_mensagens(QSqlQuery &q, const QString texto);
void add_limpeza(QSqlQuery &q, const QString local);
void add_receitas(QSqlQuery &q, const QVariant produto_id, const QVariant ingrediente_id, int quantidade);
QVariant add_produtos(QSqlQuery &q, const QString nome, double custo);
void add_pedidos(QSqlQuery &q, const QVariant mesa, const QVariant produto, int quantidade, const QString status);
void add_registro_mesas(QSqlQuery &q, int mesa, int rodizios, const QString garcom);

#endif // INITDB_H
