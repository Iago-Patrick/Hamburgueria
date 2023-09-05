#include "estoque.h"
#include "ui_estoque.h"
#include "gerente.h"
#include "initdb.hpp"
#include <QtWidgets>

estoque::estoque(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::estoque)
{
    ui->setupUi(this);

    model = new QSqlTableModel(ui->estoque_table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("ingredientes");

    model->setHeaderData(model->fieldIndex("tipo"), Qt::Horizontal, tr("Tipo"));
    model->setHeaderData(model->fieldIndex("quantidade"), Qt::Horizontal, tr("Quantidade"));

    if(!model->select())
    {
        QMessageBox::critical(this, "Unable to populate the model", "Error populating the model: " + model->lastError().text());
        return;
    }

    ui->estoque_table->setModel(model);
    ui->estoque_table->setColumnHidden(model->fieldIndex("id"), true);
    ui->estoque_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->estoque_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->lineEdit, model->fieldIndex("tipo"));
    mapper->addMapping(ui->spinBox, model->fieldIndex("quantidade"));
    mapper->addMapping(ui->spinBox_2, model->fieldIndex("quantidade"));
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->estoque_table->selectionModel(), &QItemSelectionModel::currentRowChanged, mapper, &QDataWidgetMapper::setCurrentModelIndex);

    ui->estoque_table->setCurrentIndex(model->index(0, 0));
}

estoque::~estoque()
{
    delete ui;
}

void estoque::on_b_voltar_clicked()
{
    gerente *tela = new gerente(this);

    tela->show();
}


void estoque::on_b_adicionar_clicked()
{
    QString item = ui->lineEdit->text();
    int valor = ui->spinBox->value();

    QSqlQuery q = model->query();

    q.exec("select * from ingredientes where tipo = '"+ item +"'");
    if(q.next())
    {
        QMessageBox::critical(this, "Erro", "Informação já existente");
        return;
    }

    if(!q.prepare(INSERT_INGREDIENTES_SQL))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
        return;
    }
    add_ingrediente(q, item, valor);

    model->select();
}

void estoque::on_b_remover_clicked()
{
    //adicionar logica para remover, corrigir e colocar a  parte de modificar a tabela em uma grupbox estilo booqt
    QString item = ui->lineEdit->text();
    QString valor = 0;
    QSqlQuery *q = new QSqlQuery(model->database());

    q->exec("select * from ingredientes where tipo = '"+item+"'");
    while(q->next())
        valor = q->value("id").toString();
    if(!q->prepare("delete from ingredientes where id = "+valor))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q->lastError().text());
        return;
    }
    q->exec();
    model->select();

    return;
}

void estoque::on_pushButton_clicked()
{
    QString item = ui->lineEdit->text();
    QString itemid;
    int valor = ui->spinBox_2->value();

    QSqlQuery q = model->query();

    q.exec("select * from ingredientes where tipo = '"+ item +"'");
    if(!q.next())
    {
        QMessageBox::critical(this, "Erro", "Contate o desenvolvedor");
        return;
    }
    itemid = q.value("id").toString();

    if(!q.prepare("UPDATE ingredientes SET quantidade = :valor WHERE id = :itemid"))
    {
        QMessageBox::critical(this, "Erro no banco de dados", "Erro ao inicializar o banco de dados: " + q.lastError().text());
        return;
    }
    q.bindValue(":valor", valor);
    q.bindValue(":itemid", itemid);
    q.exec();

    model->select();
}
