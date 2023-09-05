#include "finalizacao.h"
#include "ui_finalizacao.h"
#include "mesa_disponivel.h"
#include "last_user.h"
#include "cliente.h"

/* DEBUG */
#ifdef QT_DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

finalizacao::finalizacao(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::finalizacao)
{
    ui->setupUi(this);

    checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, &finalizacao::voltar_tela);
    checkTimer->start(1000);

    if(!DEBUG)
        ui->temp_fechar->setVisible(false);
}

finalizacao::~finalizacao()
{
    delete ui;
}

void finalizacao::on_temp_fechar_clicked()
{
    QString mesa = last_user::get().get_user();
    QSqlQuery q;

    mesa.remove("mesa");
    q.prepare("update mesas set garcom = 'vazio', status = 'livre', rodizios = 0 where id = :value");
    q.bindValue(":value", mesa);
    q.exec();
}

void finalizacao::voltar_tela()
{
    QSqlQuery q;
    QString mesa = last_user::get().get_user();

    mesa.remove("mesa");
    q.prepare("select * from mesas where id = :value and status = 'livre'");
    q.bindValue(":value", mesa);
    q.exec();
    if(q.next())
    {
        this->close();

        mesa_disponivel *tela = new mesa_disponivel(this);
        tela->show();
        checkTimer->stop();
    }

    q.prepare("select * from mesas where id = :value and status = 'ocupado'");
    q.bindValue(":value", mesa);
    q.exec();
    if(q.next())
    {
        this->close();

        cliente *tela = new cliente(this);
        tela->show();
        checkTimer->stop();
    }
}
