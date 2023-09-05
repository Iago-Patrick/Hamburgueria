#include "cozinha.h"
#include "ui_cozinha.h"
#include "mainwin.hpp"
#include "garcom.h"
#include "gerente.h"
#include "solicitar_limpeza.h"
#include "mensagem.h"

cozinha::cozinha(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cozinha)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(ui->pedidos_table);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("pedidos");
    model->setRelation(model->fieldIndex("mesa"), QSqlRelation("mesas", "id", "id"));
    model->setRelation(model->fieldIndex("produto"), QSqlRelation("produtos", "id", "nome"));
    model->setFilter("status_p = 'preparando'");

    model->setHeaderData(model->fieldIndex("mesa"), Qt::Horizontal, tr("Mesa"));
    model->setHeaderData(model->fieldIndex("produto"), Qt::Horizontal, tr("Produto"));
    model->setHeaderData(model->fieldIndex("quantidade"), Qt::Horizontal, tr("Quantidade"));

    if(!model->select())
    {
        QMessageBox::critical(this, "Unable to populate the model", "Error populating the model: " + model->lastError().text());
        return;
    }

    ui->pedidos_table->setModel(model);
    ui->pedidos_table->setColumnHidden(model->fieldIndex("status_p"), true);
    ui->pedidos_table->verticalHeader()->setVisible(false);
    ui->pedidos_table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->pedidos_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    adicionar_botoes();
}

cozinha::~cozinha()
{
    delete ui;
}


void cozinha::on_b_voltar_clicked()
{
    if(parentWidget() && qobject_cast<MainWindow*>(parentWidget()))
    {
        MainWindow *tela = new MainWindow(this);
        tela->show();
    }
    if(parentWidget() && qobject_cast<garcom*>(parentWidget()))
    {
        garcom *tela = new garcom(this);
        tela->show();
    }
    if(parentWidget() && qobject_cast<gerente*>(parentWidget()))
    {
        gerente *tela1= new gerente(this);
        tela1->show();
    }
}

void cozinha::on_b_solicitar_limpeza_clicked()
{
    solicitar_limpeza limpeza;

    limpeza.exec();
}

void cozinha::on_pushButton_clicked()
{
    mensagem msg;
    msg.exec();
}

void cozinha::adicionar_botoes()
{
    int row = 0;

    for(row = 0; row < model->rowCount(); row++)
    {
        QPushButton *botao = new QPushButton("Finalizar", ui->pedidos_table);
        connect(botao, &QPushButton::clicked, this, &cozinha::on_check_tabela);
        botao->setProperty("row", row);

        QModelIndex index = model->index(row, 0, QModelIndex());
        ui->pedidos_table->setIndexWidget(index, botao);
    }
    model->setHeaderData(0, Qt::Horizontal, tr(""));
}

void cozinha::on_check_tabela()
{
    QSqlQuery q = model->query();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QModelIndex idIndex;
    int id = 0;

    if(!button)
        return;
    idIndex = model->index(button->property("row").toInt(), model->fieldIndex("id"));
    id = model->data(idIndex).toInt();

    if(!q.prepare("update pedidos set status_p = 'Pronto' where id = :value"))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", id);
    q.exec();
    model->select();
    adicionar_botoes();
}
