#include "limpeza.h"
#include "garcom.h"
#include "gerente.h"
#include "ui_limpeza.h"
#include "mainwin.hpp"

limpeza::limpeza(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::limpeza)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(ui->limpeza_table);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("limpeza");

    model->setHeaderData(model->fieldIndex("local"), Qt::Horizontal, tr("Local"));

    if(!model->select())
    {
        QMessageBox::critical(this, "Unable to populate the model", "Error populating the model: " + model->lastError().text());
        return;
    }

    ui->limpeza_table->setModel(model);
    ui->limpeza_table->setColumnHidden(model->fieldIndex("id"), true);
    ui->limpeza_table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->limpeza_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    adicionar_botoes();
}

limpeza::~limpeza()
{
    delete ui;
}

void limpeza::on_pushButton_4_clicked()
{
    if(parentWidget() && qobject_cast<MainWindow*>(parentWidget()))
    {
        MainWindow *tela = new MainWindow(this);
        tela->show();
    }
    if(parentWidget() && qobject_cast<gerente*>(parentWidget()))
    {
        gerente *tela1= new gerente(this);
        tela1->show();
    }
}

void limpeza::on_botao_tabela_clicked()
{
    QSqlQuery q = model->query();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QModelIndex idIndex;

    if(!button)
        return;
    idIndex = model->index(button->property("row").toInt(), model->fieldIndex("id"));
    int id = model->data(idIndex).toInt();

    if(!q.prepare("delete from limpeza where id = :value"))
    {
        QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", id);
    q.exec();
    model->select();
    adicionar_botoes();
}

void limpeza::adicionar_botoes()
{
    model->insertColumn(model->columnCount());
    for(int row = 0; row < model->rowCount(); ++row)
    {
        QPushButton *botao = new QPushButton("Limpar", ui->limpeza_table);
        connect(botao, &QPushButton::clicked, this, &limpeza::on_botao_tabela_clicked);
        botao->setProperty("row", row);

        QModelIndex index = model->index(row, model->columnCount() - 1, QModelIndex());
        ui->limpeza_table->setIndexWidget(index, botao);
    }
    model->setHeaderData(model->columnCount() - 1, Qt::Horizontal, tr("Ação"));
}
