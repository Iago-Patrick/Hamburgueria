#include "mesa_disponivel.h"
#include "ui_mesa_disponivel.h"
#include "finalizacao.h"
#include "mainwin.hpp"
#include "cliente.h"
#include "last_user.h"
#include "initdb.hpp"

#ifdef QT_DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

mesa_disponivel::mesa_disponivel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mesa_disponivel)
{
    ui->setupUi(this);
    QSqlQuery q;
    QString mesa = last_user::get().get_user();

    mesa.remove("mesa");
    q.exec("select * from mesas where id = "+ mesa);
    if(!q.next())
    {
        if(!q.prepare(INSERT_MESAS_SQL))
        {
            QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
            return;
        }
        add_mesas(q, mesa.toInt(), 0, "vazio", "livre");
    }

    checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, &mesa_disponivel::proxima_tela);
    checkTimer->start(1000);

    if(!DEBUG)
    {
        ui->pushButton_4->setVisible(false);
        ui->pushButton->setVisible(false);
    }
}

mesa_disponivel::~mesa_disponivel()
{
    delete ui;
}

void mesa_disponivel::on_pushButton_clicked()
{
    QString mesa = last_user::get().get_user();
    QSqlQuery q;

    mesa.remove("mesa");
    q.prepare("update mesas set garcom = 'garcom', status = 'ocupado' where id = :value");
    q.bindValue(":value", mesa);
    q.exec();
}
void mesa_disponivel::on_pushButton_4_clicked()
{
    MainWindow *tela = new MainWindow(this);
    close();
    tela->show();
    checkTimer->stop();
}

void mesa_disponivel::proxima_tela()
{
    QSqlQuery q;
    QString mesa = last_user::get().get_user();

    mesa.remove("mesa");
    q.prepare("select * from mesas where id = :value and status = 'ocupado'");
    q.bindValue(":value", mesa);
    q.exec();
    if(q.next())
    {
        close();

        cliente *tela = new cliente(this);

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
