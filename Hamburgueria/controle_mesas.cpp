#include "controle_mesas.h"
#include "ui_controle_mesas.h"
#include "gerente.h"
#include "initdb.hpp"
#include <QtSql>
#include <QtWidgets>

controle_mesas::controle_mesas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controle_mesas)
{
    ui->setupUi(this);
    int i = 0;
    QSqlQuery q;

    for(i = 0; i < 6; i++)
        mesas.push_back("0");

    if(!q.exec("select * from produtos where nome = 'Rodizio'"))
    {
        qDebug() << "falhou em achar tabela sql";
        return;
    }

    if(q.next())
        valor = q.value("custo").toDouble();

    set_valor_label();
}

controle_mesas::~controle_mesas()
{
    delete ui;
}

void controle_mesas::on_voltar_clicked()
{
    if(parentWidget() && qobject_cast<gerente*>(parentWidget()))
    {
        gerente *tela = new gerente(this);
        tela->show();
    }
}

void controle_mesas::set_valor_label()
{
    QVector<int> rodizios;
    QSqlQuery q;

    if(!q.exec("select * from mesas"))
    {
        qDebug() << "falhou em achar tabela sql";
        return;
    }
    while(q.next())
        rodizios.push_back(q.value("rodizios").toInt());

    mesas[0] = QString::number(valor * rodizios[0]);
    mesas[1] = QString::number(valor * rodizios[1]);
    mesas[2] = QString::number(valor * rodizios[2]);
    mesas[3] = QString::number(valor * rodizios[3]);
    mesas[4] = QString::number(valor * rodizios[4]);
    mesas[5] = QString::number(valor * rodizios[5]);

    ui->v_valor_conta_m1->setText(mesas[0]);
    ui->v_valor_conta_m2->setText(mesas[1]);
    ui->v_valor_conta_m3->setText(mesas[2]);
    ui->v_valor_conta_m4->setText(mesas[3]);
    ui->v_valor_conta_m5->setText(mesas[4]);
    ui->v_valor_conta_m6->setText(mesas[5]);
}

void controle_mesas::on_b_finalizar_conta_m1_clicked()
{
    fechar_mesa(1);
    set_valor_label();
}


void controle_mesas::on_b_finalizar_conta_m2_clicked()
{
    fechar_mesa(2);
    set_valor_label();
}


void controle_mesas::on_b_finalizar_conta_m3_clicked()
{
    fechar_mesa(3);
    set_valor_label();
}


void controle_mesas::on_b_finalizar_conta_m4_clicked()
{
    fechar_mesa(4);
    set_valor_label();
}


void controle_mesas::on_b_finalizar_conta_m5_clicked()
{
    fechar_mesa(5);
    set_valor_label();
}


void controle_mesas::on_b_finalizar_conta_m6_clicked()
{
    fechar_mesa(6);
    set_valor_label();
}

void controle_mesas::fechar_mesa(int mesa_id)
{
    QSqlQuery q;
    int rodizios = 0;
    QString garcom;

    q.exec("select * from mesas where status = 'livre' and id = " + QString::number(mesa_id));
    if(q.next())
        return;

    q.exec("select * from mesas where id = " + QString::number(mesa_id));
    q.next();
    rodizios = q.value("rodizios").toInt();
    garcom = q.value("garcom").toString();

    QMessageBox::StandardButton resposta = QMessageBox::question(this,"Encerrar", "Deseja encerrar a mesa?", QMessageBox::Yes | QMessageBox::No);
    if(resposta == QMessageBox::No)
        return;

    if(!q.prepare(INSERT_REGISTRO_MESAS_SQL))
    {
        QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
        return;
    }
    add_registro_mesas(q, mesa_id, rodizios, garcom);

    if(!q.prepare("update mesas set status = 'livre', garcom = 'vazio', rodizios = 0 where id = :value;"))
    {
        QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", mesa_id);
    q.exec();

    if(!q.prepare("delete from pedidos where mesa = :value;"))
    {
        QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", mesa_id);
    q.exec();
}
