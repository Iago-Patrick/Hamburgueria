#include "initdb.hpp"

QSqlError initdb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./database/ex14.db");
    QStringList tables;
    QVariant gerente;
    QVariant mesa;
    QVariant limpeza;
    QVariant cozinha;
    QVariant garcom;
    vector<QVariant> ingredientes;
    vector<QVariant> produtos;

    if(!db.open())
        return db.lastError();

    tables = db.tables();
    if(tables.contains("users", Qt::CaseInsensitive) && tables.contains("funcoes", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if(!q.exec("PRAGMA foreign_keys = ON;"))
        return q.lastError();
    if(!q.exec(FUNC_SQL))
        return q.lastError();
    if(!q.exec(USER_SQL))
        return q.lastError();
    if(!q.exec(INGREDIENTES_SQL))
        return q.lastError();
    if(!q.exec(MESAS_SQL))
        return q.lastError();
    if(!q.exec(LIMPEZA_SQL))
        return q.lastError();
    if(!q.exec(PRODUTOS_SQL))
        return q.lastError();
    if(!q.exec(RECEITAS_SQL))
        return q.lastError();
    if(!q.exec(PEDIDOS_SQL))
        return q.lastError();
    if(!q.exec(MENSAGENS_SQL))
        return q.lastError();

    if(!q.prepare(INSERT_FUNCOES_SQL))
        return q.lastError();
    gerente = add_funcoes(q, QLatin1String("gerente"));
    mesa = add_funcoes(q, QLatin1String("mesa"));
    limpeza = add_funcoes(q, QLatin1String("limpeza"));
    cozinha = add_funcoes(q, QLatin1String("cozinha"));
    garcom = add_funcoes(q, QLatin1String("garcom"));

    if(!q.prepare(INSERT_USER_SQL))
        return q.lastError();
    add_user(q, QLatin1String("gerente"), QLatin1String("1234"), gerente);
    add_user(q, QLatin1String("mesa1"), QLatin1String("1234"), mesa);
    add_user(q, QLatin1String("mesa2"), QLatin1String("1234"), mesa);
    add_user(q, QLatin1String("mesa3"), QLatin1String("1234"), mesa);
    add_user(q, QLatin1String("mesa4"), QLatin1String("1234"), mesa);
    add_user(q, QLatin1String("mesa5"), QLatin1String("1234"), mesa);
    add_user(q, QLatin1String("mesa6"), QLatin1String("1234"), mesa);
    add_user(q, QLatin1String("limpeza"), QLatin1String("1234"), limpeza);
    add_user(q, QLatin1String("cozinha"), QLatin1String("1234"), cozinha);
    add_user(q, QLatin1String("garcom1"), QLatin1String("1234"), garcom);
    add_user(q, QLatin1String("garcom2"), QLatin1String("1234"), garcom);

    if(!q.prepare(INSERT_LIMPEZA_SQL))
        return q.lastError();

    if(!q.prepare(INSERT_INGREDIENTES_SQL))
        return q.lastError();
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Pao"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Carne"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("frango"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Queijo"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Bacon"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Cebola"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Farinha"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Batata"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Pimenta"), 100));
    ingredientes.push_back(add_ingrediente(q, QLatin1String("Salada"), 100));

    if(!q.prepare(INSERT_PRODUTOS_SQL))
        return q.lastError();
    produtos.push_back(add_produtos(q, QLatin1String("Flof Burguer"), 5.50));

    if(!q.prepare(INSERT_RECEITAS_SQL))
        return q.lastError();
    add_receitas(q, produtos[0], ingredientes[0], 1); // flof burguer 1 Pao
    add_receitas(q, produtos[0], ingredientes[2], 1); // flof burguer 1 frango
    add_receitas(q, produtos[0], ingredientes[3], 2); // flof burguer 2 Queijos

    return QSqlError();
}

void add_user(QSqlQuery &q, const QString usuario, const QString senha, const QVariant funcao)
{
    q.addBindValue(usuario);
    q.addBindValue(senha);
    q.addBindValue(funcao);
    q.exec();
}

QVariant add_funcoes(QSqlQuery &q, const QString funcao)
{
    q.addBindValue(funcao);
    q.exec();

    return q.lastInsertId();
}

QVariant add_ingrediente(QSqlQuery &q, const QString tipo, int quantidade)
{
    q.addBindValue(tipo);
    q.addBindValue(quantidade);
    q.exec();

    return q.lastInsertId();
}

QVariant add_mesas(QSqlQuery &q, int mesa, int rodizios, const QString garcom, const QString status)
{
    q.addBindValue(mesa);
    q.addBindValue(rodizios);
    q.addBindValue(garcom);
    q.addBindValue(status);
    q.exec();

    return q.lastInsertId();
}

void add_mensagens(QSqlQuery &q, const QString texto)
{
    q.addBindValue(texto);
    q.exec();
}

void add_limpeza(QSqlQuery &q, const QString local)
{
    q.addBindValue(local);
    q.exec();
}

void add_receitas(QSqlQuery &q, const QVariant produto_id, const QVariant ingrediente_id, int quantidade)
{
    q.addBindValue(produto_id);
    q.addBindValue(ingrediente_id);
    q.addBindValue(quantidade);
    q.exec();
}

QVariant add_produtos(QSqlQuery &q, const QString nome, double custo)
{
    q.addBindValue(nome);
    q.addBindValue(custo);
    q.exec();

    return q.lastInsertId();
}

void add_pedidos(QSqlQuery &q, const QVariant mesa, const QVariant produto, int quantidade, const QString status)
{
    q.addBindValue(mesa);
    q.addBindValue(produto);
    q.addBindValue(quantidade);
    q.addBindValue(status);
    q.exec();
}

void add_registro_mesas(QSqlQuery &q, int mesa, int rodizios, const QString garcom)
{
    q.addBindValue(mesa);
    q.addBindValue(rodizios);
    q.addBindValue(garcom);
    q.exec();
}
