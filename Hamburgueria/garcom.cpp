#include "garcom.h"
#include "ui_garcom.h"
#include "limpeza.h"
#include "cozinha.h"
#include "mainwin.hpp"
#include "controle_mesas.h"
#include "last_user.h"
#include "solicitar_limpeza.h"
#include "initdb.hpp"

garcom::garcom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::garcom)
{
    ui->setupUi(this);
    QString user = last_user::get().get_user().trimmed();
    QString filtro = "garcom = '"+ user +"'";

    model_disp = new QSqlTableModel(ui->tableView_2);
    model_disp->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_disp->setTable("mesas");

    model_disp->setHeaderData(model_disp->fieldIndex("id"), Qt::Horizontal, tr("Mesa"));
    model_disp->setHeaderData(model_disp->fieldIndex("status"), Qt::Horizontal, tr("Status"));
    model_disp->setFilter("status = 'livre'");

    if(!model_disp->select())
    {
        QMessageBox::critical(this, "Unable to populate the model", "Error populating the model: " + model_disp->lastError().text());
        return;
    }

    ui->tableView_2->setModel(model_disp);
    ui->tableView_2->setColumnHidden(model_disp->fieldIndex("garcom"), true);
    ui->tableView_2->setColumnHidden(model_disp->fieldIndex("rodizios"), true);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    adicionar_botoes_abrir_mesa();

    model_ocup = new QSqlTableModel(ui->tableView);
    model_ocup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_ocup->setTable("mesas");

    model_ocup->setHeaderData(model_ocup->fieldIndex("id"), Qt::Horizontal, tr("Mesa"));
    model_ocup->setHeaderData(model_ocup->fieldIndex("rodizios"), Qt::Horizontal, tr("Rodizios"));
    model_ocup->setHeaderData(model_ocup->fieldIndex("garcom"), Qt::Horizontal, tr("Garçom"));
        model_ocup->setHeaderData(model_ocup->fieldIndex("status"), Qt::Horizontal, tr("Status"));
    model_ocup->setFilter(filtro);

    if(!model_ocup->select())
    {
        QMessageBox::critical(this, "Unable to populate the model", "Error populating the model: " + model_ocup->lastError().text());
        return;
    }

    ui->tableView->setModel(model_ocup);
    ui->tableView->setColumnHidden(model_ocup->fieldIndex("garcom"), true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    adicionar_botoes_fechar_mesa();
}

garcom::~garcom()
{
    delete ui;
}

void garcom::on_pushButton_4_clicked()
{
    MainWindow *tela = new MainWindow(this);

    tela->show();
}

void garcom::on_pushButton_2_clicked()
{
    cozinha *tela = new cozinha(this);

    tela->show();
}

void garcom::adicionar_botoes_abrir_mesa()
{
    model_disp->insertColumn(model_disp->columnCount());
    for(int row = 0; row < model_disp->rowCount(); ++row)
    {
        QPushButton *botao = new QPushButton("Ativar mesa", ui->tableView_2);
        connect(botao, &QPushButton::clicked, this, &garcom::on_b_adicionar_clicked);
        botao->setProperty("row", row);

        QModelIndex index = model_disp->index(row, model_disp->columnCount() - 1, QModelIndex());
        ui->tableView_2->setIndexWidget(index, botao);
    }
    model_disp->setHeaderData(model_disp->columnCount() - 1, Qt::Horizontal, tr("Ação"));
}

void garcom::on_b_adicionar_clicked()
{
    QSqlQuery q = model_disp->query();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QModelIndex idIndex;

    if(!button)
        return;
    idIndex = model_disp->index(button->property("row").toInt(), model_disp->fieldIndex("id"));
    int id = model_disp->data(idIndex).toInt();

    if(!q.prepare("update mesas set status = 'ocupado', garcom = :user where id = :value;"))
    {
        QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
        return;
    }
    q.bindValue(":value", id);
    q.bindValue(":user", last_user::get().get_user());
    q.exec();

    model_disp->select();
    model_ocup->select();
    adicionar_botoes_abrir_mesa();
    adicionar_botoes_fechar_mesa();
}

void garcom::adicionar_botoes_fechar_mesa()
{
    model_ocup->insertColumn(model_ocup->columnCount());
    for(int row = 0; row < model_ocup->rowCount(); ++row)
    {
        QPushButton *botao = new QPushButton("Atender", ui->tableView);
        connect(botao, &QPushButton::clicked, this, &garcom::on_b_atender_clicked);
        botao->setProperty("row", row);

        QModelIndex index = model_ocup->index(row, model_ocup->columnCount() - 1, QModelIndex());
        ui->tableView->setIndexWidget(index, botao);
    }
    model_ocup->setHeaderData(model_ocup->columnCount() - 1, Qt::Horizontal, tr(""));
}

void garcom::on_b_atender_clicked()
{
    QSqlQuery q = model_ocup->query();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QModelIndex idIndex;
    int id = 0;
    int rodizios = 0;
    QString garcom;
    QString chamado = "chamando";

    if(!button)
        return;
    idIndex = model_ocup->index(button->property("row").toInt(), model_ocup->fieldIndex("id"));
    id = model_ocup->data(idIndex).toInt();

    q.exec("select * from mesas where id = " + QString::number(id));
    q.next();
    rodizios = q.value("rodizios").toInt();
    garcom = q.value("garcom").toString();

    if(!chamado.compare(q.value("status").toString()))
    {
        if(!q.prepare("update mesas set status = 'ocupado' where id = :value;"))
        {
            QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
            return;
        }
        q.bindValue(":value", id);
        q.exec();
    }

    else
    {
        QMessageBox::StandardButton resposta = QMessageBox::question(this,"Encerrar", "Deseja encerrar a mesa?", QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::No)
            return;

        if(!q.prepare(INSERT_REGISTRO_MESAS_SQL))
        {
            QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
            return;
        }
        add_registro_mesas(q, id, rodizios, garcom);

        if(!q.prepare("update mesas set status = 'livre', garcom = 'vazio', rodizios = 0 where id = :value;"))
        {
            QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
            return;
        }
        q.bindValue(":value", id);
        q.exec();

        if(!q.prepare("delete from pedidos where mesa = :value;"))
        {
            QMessageBox::critical(this, "Unable to prepare Database", "Error preparing database: " + q.lastError().text());
            return;
        }
        q.bindValue(":value", id);
        q.exec();
    }

    model_disp->select();
    model_ocup->select();
    adicionar_botoes_fechar_mesa();
    adicionar_botoes_abrir_mesa();
}

void garcom::on_b_solicitar_limpeza_clicked()
{
    solicitar_limpeza limpeza;
    limpeza.exec();
}
