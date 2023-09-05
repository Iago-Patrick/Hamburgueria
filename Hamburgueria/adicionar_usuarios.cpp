#include "adicionar_usuarios.h"
#include "ui_adicionar_usuarios.h"
#include "gerente.h"
#include <QMessageBox>
#include "initdb.hpp"
#include <QtSql>

adicionar_usuarios::adicionar_usuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adicionar_usuarios)
{
    ui->setupUi(this);
}

adicionar_usuarios::~adicionar_usuarios()
{
    delete ui;
}

void adicionar_usuarios::on_pushButton_clicked()
{
    int funcao = 0;
    QString user = ui->usuario->text();
    QString senha = ui->senha->text();
    QSqlQuery q;

    if(!q.prepare("select * from users where usuario = :value"))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", user);
    q.exec();

    while(q.next())
    {
        QMessageBox::critical(this,"Erro ao adicionar usuário", "Usuário já existe.");
        return;
    }

    if(!q.prepare("select * from funcoes where funcao = :value"))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", ui->funcao->currentText());
    q.exec();

    while(q.next())
        funcao = q.value("id").toInt();

    if (!q.prepare(INSERT_USER_SQL))
    {
        QMessageBox::critical(this,"Erro ao adicioanar usuário", "Usuário já existe.");
        return;
    }
    add_user(q, user, senha, funcao);

    QMessageBox::about(this,"Adicionar usuário", "Usuário adicionado ao sistema");
    ui->funcao->clear();
    ui->usuario->clear();
    ui->senha->clear();

    this->hide();
}

void adicionar_usuarios::on_pushButton_2_clicked()
{
    this->hide();
}
