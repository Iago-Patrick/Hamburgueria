#include "pedidos_gerente.h"
#include "ui_pedidos_gerente.h"
#include "gerente.h"
#include "initdb.hpp"
#include <QtWidgets>

pedidos_gerente::pedidos_gerente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pedidos_gerente)
{
    ui->setupUi(this);
    model = new QSqlTableModel(ui->pedidos_table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("pedidos");

    if(!model->select())
    {
        QMessageBox::critical(this, "Unable to populate the model", "Error populating the model: " + model->lastError().text());
        return;
    }

    ui->pedidos_table->setModel(model);
    ui->pedidos_table->setColumnHidden(model->fieldIndex("id"), true);
    ui->pedidos_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pedidos_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->pedidos_table->selectionModel(), &QItemSelectionModel::currentRowChanged, mapper, &QDataWidgetMapper::setCurrentModelIndex);

    ui->pedidos_table->setCurrentIndex(model->index(0, 0));
    adicionar_botoes();
}

void pedidos_gerente::on_botao_tabela_clicked()
{
    QSqlQuery q = model->query();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QModelIndex idIndex;

    if(!button)
        return;
    idIndex = model->index(button->property("row").toInt(), model->fieldIndex("id"));
    int id = model->data(idIndex).toInt();

    if(!q.prepare("delete from pedidos where id = :value"))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", id);
    q.exec();
    model->select();
    adicionar_botoes();
}

void pedidos_gerente::adicionar_botoes()
{
    model->insertColumn(model->columnCount());
    for(int row = 0; row < model->rowCount(); ++row)
    {
        QPushButton *botao = new QPushButton("Remover", ui->pedidos_table);
        connect(botao, &QPushButton::clicked, this, &pedidos_gerente::on_botao_tabela_clicked);
        botao->setProperty("row", row);

        QModelIndex index = model->index(row, model->columnCount() - 1, QModelIndex());
        ui->pedidos_table->setIndexWidget(index, botao);
    }
    model->setHeaderData(model->columnCount() - 1, Qt::Horizontal, tr("Ação"));
}

pedidos_gerente::~pedidos_gerente()
{
    delete ui;
}

void pedidos_gerente::on_b_voltar_clicked()
{
    gerente *tela= new gerente(this);
    tela->show();
}
