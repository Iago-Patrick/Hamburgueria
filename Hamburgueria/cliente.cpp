#include "cliente.h"
#include "ui_cliente.h"
#include "mainwin.hpp"
#include "comes.h"
#include "mesa_disponivel.h"
#include "finalizacao.h"
#include "last_user.h"
#include <QMessageBox>
#include <QtDebug>

/* DEBUG */
#ifdef QT_DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

cliente::cliente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cliente)
{
    ui->setupUi(this);
    QSqlQuery q;
    QString mesa = last_user::get().get_user();

    mesa.remove("mesa");
    checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, &cliente::mudar_tela);
    checkTimer->start(1000);

    q.prepare("select * from mesas where id = :value");
    q.bindValue(":value", mesa);
    q.exec();

    while(q.next())
        rodizio = q.value("rodizios").toInt();
    ui->num_rodizios->setNum(rodizio);

    if(DEBUG)
        ui->pushButton_4->setVisible(true);
    else
        ui->pushButton_4->setVisible(false);
}

cliente::~cliente()
{
    delete ui;
    checkTimer->stop();
}

void cliente::on_pushButton_4_clicked()
{
    mesa_disponivel *tela = new mesa_disponivel(this);
    checkTimer->stop();

    tela->show();
}

void cliente::on_pushButton_clicked()
{
    comes *tela = new comes(this);
    checkTimer->stop();
    tela->show();
}

void cliente::on_pushButton_5_clicked()
{
    QString mesa = last_user::get().get_user();
    QSqlQuery q;

    mesa.remove("mesa");
    QMessageBox::StandardButton resposta = QMessageBox::question(this,"Rodizio", "Deseja adicionar mais um rodizio?", QMessageBox::Yes | QMessageBox::No);
    if(resposta == QMessageBox::Yes)
    {
        QMessageBox::about(this, "Rodizio", "Rodizio adicionado");
        q.prepare("update mesas set rodizios = rodizios + 1 where id = :value");
        q.bindValue(":value", mesa);
        q.exec();

        q.prepare("select * from mesas where id = :value");
        q.bindValue(":value", mesa);
        q.exec();

        while(q.next())
            rodizio = q.value("rodizios").toInt();
        ui->num_rodizios->setNum(rodizio);
    }
    else
    {
        qDebug() << "Rodizio não foi adicionado";
    }
}


void cliente::on_pushButton_3_clicked()
{
    QSqlQuery q;
    QString mesa = last_user::get().get_user();

    mesa.remove("mesa");
    QMessageBox::StandardButton resposta = QMessageBox::question(this,"Conta", "Deseja pedir a conta?", QMessageBox::Yes | QMessageBox::No);
    if(resposta == QMessageBox::Yes)
    {
        q.prepare("update mesas set status = 'pagando' where id = :value");
        q.bindValue(":value", mesa);
        q.exec();
    }
}

void cliente::on_pushButton_2_clicked()
{
    QString mesa = last_user::get().get_user();
    QSqlQuery q;

    mesa.remove("mesa");
    if(!q.prepare("update mesas set status = 'chamando' where id = :value;"))
    {
        QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", mesa);
    q.exec();
    QMessageBox::about(this, "Chamar Garçom", "O garçom foi chamado. Aguarde-o em sua mesa");
}

void cliente::mudar_tela()
{
    QSqlQuery q;
    QString mesa = last_user::get().get_user();

    mesa.remove("mesa");
    q.prepare("select * from mesas where id = :value and status = 'livre'");
    q.bindValue(":value", mesa);
    q.exec();
    if(q.next())
    {
        close();

        mesa_disponivel *tela = new mesa_disponivel(this);
        tela->show();
        checkTimer->stop();
        return;
    }

    q.prepare("select * from mesas where id = :value and status = 'pagando'");
    q.bindValue(":value", mesa);
    q.exec();
    if(q.next())
    {
        close();

        finalizacao *tela = new finalizacao(this);
        tela->show();
        checkTimer->stop();
        return;
    }
}
