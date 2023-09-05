#include "comes.h"
#include "ui_comes.h"
#include "cliente.h"
#include "initdb.hpp"
#include "last_user.h"
#include <QPixmap>

comes::comes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::comes)
{
    ui->setupUi(this);

    QPixmap akernaak("C:/Qt/akernaak");
    ui->label->setPixmap(akernaak);

    QPixmap flof("C:/Qt/flof");
    ui->label->setPixmap(flof);

    QPixmap hydra("C:/Qt/hydra");
    ui->label->setPixmap(hydra);

}

comes::~comes()
{

    delete ui;
}

void comes::on_pushButton_clicked()
{
    cliente *tela = new cliente(this);

    tela->show();
}

void comes::on_pedir_item1_clicked()
{
    pedir("Akernaak", ui->spinBox->value());

    ui->spinBox->setValue(1);
}


void comes::on_pedir_item2_clicked()
{
    pedir("Flof Burguer", ui->spinBox_2->value());

    ui->spinBox_2->setValue(1);
}

void comes::on_pedir_item3_clicked()
{
    pedir("Hydra Raivosa", ui->spinBox_3->value());

    ui->spinBox_3->setValue(1);
}

void comes::on_pedir_item4_clicked()
{
    pedir("Beco Especial", ui->spinBox_4->value());

    ui->spinBox_4->setValue(1);
}

void comes::on_pedir_item5_clicked()
{
    pedir("Vegano", ui->spinBox_5->value());

    ui->spinBox_5->setValue(1);
}

void comes::on_pedir_item6_clicked()
{
    pedir("Batata frita", ui->spinBox_6->value());

    ui->spinBox_6->setValue(1);
}

void comes::on_pedir_item7_clicked()
{
    pedir("Onion Ring", ui->spinBox_7->value());

    ui->spinBox_7->setValue(1);
}

void comes::on_pedir_item8_clicked()
{
    pedir("Molho da Casa", ui->spinBox_8->value());

    ui->spinBox_8->setValue(1);
}

void comes::on_pedir_item9_clicked()
{
    pedir("Barbecue", ui->spinBox_9->value());

    ui->spinBox_9->setValue(1);
}

void comes::pedir(const QString nome, int quantidade)
{
    QSqlQuery q;
    QString mesa = last_user::get().get_user();
    int produto = 0;

    mesa.remove("mesa");
    q.exec("select * from produtos where nome  = '"+ nome +"'");
    while(q.next())
        produto = q.value("id").toInt();
    if(!q.prepare(INSERT_PEDIDOS_SQL))
    {
        QMessageBox::critical(this, "Unable to connect to Database", "Error database: " + q.lastError().text());
        return;
    }
    add_pedidos(q, mesa.toInt(), produto, quantidade, "preparando");
}
