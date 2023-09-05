#include "gerente.h"
#include "ui_gerente.h"
#include "mainwin.hpp"
#include "estoque.h"
#include "cozinha.h"
#include "controle_mesas.h"
#include "limpeza.h"
#include "garcom.h"
#include "financeiro.h"
#include "solicitar_limpeza.h"
#include "adicionar_usuarios.h"
#include "pedidos_gerente.h"

gerente::gerente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gerente)
{

    ui->setupUi(this);
}

gerente::~gerente()
{
    delete ui;
}

void gerente::on_pushButton_4_clicked()
{
    MainWindow *tela = new MainWindow(this);
    tela->show();
}


void gerente::on_pushButton_6_clicked()
{
    estoque *tela = new estoque(this);
    tela->show();
}


void gerente::on_pushButton_5_clicked()
{
    pedidos_gerente *tela = new pedidos_gerente(this);
    tela->show();
}

void gerente::on_pushButton_7_clicked()
{
    controle_mesas *tela = new controle_mesas(this);
    tela->show();
}

void gerente::on_pushButton_clicked()
{
    limpeza *tela = new limpeza(this);
    tela->show();
}

void gerente::on_pushButton_2_clicked()
{
    solicitar_limpeza limpeza;
    limpeza.exec();
}


void gerente::on_pushButton_3_clicked()
{
    financeiro *tela = new financeiro(this);
    tela->show();
}

void gerente::on_pushButton_8_clicked()
{
    adicionar_usuarios gerente;
    gerente.exec();
}
