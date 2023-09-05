#include "financeiro.h"
#include "ui_financeiro.h"
#include "gerente.h"

financeiro::financeiro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::financeiro)
{
    ui->setupUi(this);
}

financeiro::~financeiro()
{
    delete ui;
}

void financeiro::on_pushButton_clicked()
{
    gerente *tela = new gerente(this);
    close();
    tela->show();
}
