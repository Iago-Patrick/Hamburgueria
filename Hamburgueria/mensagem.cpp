#include "mensagem.h"
#include "ui_mensagem.h"
#include "initdb.hpp"
#include <QtWidgets>

mensagem::mensagem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mensagem)
{
    ui->setupUi(this);
}

mensagem::~mensagem()
{
    delete ui;
}

void mensagem::on_b_enviar_clicked()
{
    QString mensagem =ui->textEdit->toPlainText();
    QSqlQuery q;
    q.prepare(INSERT_MENSAGENS_SQL);
    add_mensagens(q, mensagem);
    ui->textEdit->clear();
    QMessageBox::about(this,"Mensagem", "Mensagem Enviada.");
    this->hide();
}

void mensagem::on_pushButton_2_clicked()
{
    this->hide();
}
