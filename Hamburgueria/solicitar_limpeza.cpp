#include "solicitar_limpeza.h"
#include "ui_solicitar_limpeza.h"
#include "garcom.h"
#include "limpeza.h"
#include "initdb.hpp"
#include <QMessageBox>

solicitar_limpeza::solicitar_limpeza(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::solicitar_limpeza)
{
    ui->setupUi(this);
}

solicitar_limpeza::~solicitar_limpeza()
{
    delete ui;
}

void solicitar_limpeza::on_pushButton_clicked()
{
    QMessageBox::about(this,"Solicitação de Limpeza", "Solicitação enviada para a equipe de limpeza.");
    QString local = ui->comboBox->currentText();

    QSqlQuery q;
    q.prepare(INSERT_LIMPEZA_SQL);
    add_limpeza(q, local);

    this->hide();
}



void solicitar_limpeza::on_pushButton_2_clicked()
{
    this->hide();
}
