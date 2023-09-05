/***************************************************************************
 *   mainwin.cpp                              Version 20230621.000147      *
 *                                                                         *
 *   Brief description                                                     *
 *   Copyright (C) 2023         by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/* ---------------------------------------------------------------------- */
/* includes */
/* #include <iostream> */ /* (Input/output library) Several standard stream objects */
/* using namespace std; */
/* #include <cstdio> */ /* (Input/output library) C-style input-output functions */
/* #include <fstream> */ /* (Input/output library) std::basic_fstream, std::basic_ifstream, std::basic_ofstream class templates and several typedefs */
/* #include <iomanip> */ /* (Input/output library) Helper functions to control the format of input and output */
/* #include <ios> */ /* (Input/output library) std::ios_base class, std::basic_ios class template and several typedefs */
/* #include <iosfwd> */ /* (Input/output library) Forward declarations of all classes in the input/output library */
/* #include <istream> */ /* (Input/output library) std::basic_istream class template and several typedefs */
/* #include <ostream> */ /* (Input/output library) std::basic_ostream, std::basic_iostream class templates and several typedefs */
/* #include <spanstream> */ /* (C++23, Input/output library) std::basic_spanstream, std::basic_ispanstream, std::basic_ospanstream class templates and typedefs */
/* #include <sstream> */ /* (Input/output library) std::basic_stringstream, std::basic_istringstream, std::basic_ostringstream class templates and several typedefs */
/* #include <streambuf> */ /* (Input/output library) std::basic_streambuf class template */
/* #include <strstream> */ /* (deprecated in C++98, Input/output library) std::strstream, std::istrstream, std::ostrstream */
/* #include <syncstream> */ /* (C++20, Input/output library) std::basic_osyncstream, std::basic_syncbuf, and typedefs */

/* #include "libuser.hpp" */ /* your personal user library together with libuser.cpp */

#include "mainwin.hpp" /* To be created for this template if needed */
#include "mesa_disponivel.h"
#include "cozinha.h"
#include "estoque.h"
#include "initdb.hpp"
#include "garcom.h"
#include "gerente.h"
#include "limpeza.h"
#include "last_user.h"
#include <QtSql>
#include "adicionar_usuarios.h"

/* DEBUG */
#ifdef QT_DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

/* ---------------------------------------------------------------------- */
/* methods */

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical( this, "Unable to load database", "This demo needs the SQLITE driver");

    QSqlError err = initdb();
    if(err.type() != QSqlError::NoError)
    {
        showError(err);
        return;
    }

    // Cria o model
    model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("users");

    // Salva o Id das colunas
    funcoesIdx = model->fieldIndex("funcao");

    // Coloca a relacao entre tabelas
    model->setRelation(funcoesIdx, QSqlRelation("funcoes", "id", "funcao"));

    if(!model->select())
    {
        showError(model->lastError());
        return;
    }

    if(!DEBUG)
    {
        ui->b_cliente->setVisible(false);
        ui->b_cozinha->setVisible(false);
        ui->b_garcom->setVisible(false);
        ui->b_gerente->setVisible(false);
        ui->b_limpeza->setVisible(false);
    }

}

/* destrutor */
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    delete ui;
}


/* add more methods here */

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database", "Error initializing database: " + err.text());

    return;
}

void MainWindow::on_b_cliente_clicked()
{
    last_user::get().set_user("mesa1");
    mesa_disponivel *tela = new mesa_disponivel(this);
    tela->show();
}

void MainWindow::on_b_cozinha_clicked()
{
    cozinha *tela = new cozinha(this);
    tela->show();
}

void MainWindow::on_b_garcom_clicked()
{
    last_user::get().set_user("garcom");
    garcom *tela = new garcom(this);
    tela->show();
}

void MainWindow::on_b_gerente_clicked()
{
    gerente *tela = new gerente(this);
    tela->show();
}

void MainWindow::on_pushButton_clicked()
{
    QString senha = ui->senha->text();
    QString user = ui->usuario->text();
    int funcao = 0;
    QSqlQuery q = model->query();
    gerente *tela1 = nullptr;
    mesa_disponivel *tela2 = nullptr;
    limpeza *tela3 = nullptr;
    cozinha *tela4 =nullptr;
    garcom *tela5 =nullptr;

    ui->senha->clear();
    ui->usuario->clear();

    q.exec("select * from users where usuario = '"+ user +"' and senha = '" + senha + "'");

    while(q.next())
        funcao = q.value("funcao").toInt();

    last_user::get().set_user(user);

    switch(funcao)
    {
        case 1:
            MainWindow::close();
            tela1 = new gerente(this);
            tela1->show();
            break;

        case 2:
            MainWindow::close();
            tela2 = new mesa_disponivel(this);
            tela2->show();
            break;

        case 3:
            MainWindow::close();
            tela3 = new limpeza(this);
            tela3->show();
            break;

        case 4:
            MainWindow::close();
            tela4 = new cozinha(this);
            tela4->show();
            break;

        case 5:
            MainWindow::close();
            tela5 = new garcom(this);
            tela5 ->show();
            break;
        default:
            ui->label->setText("Usuario ou senha incorreto.");
            ui->usuario->setFocus();
            break;
    }
}

void MainWindow::on_b_limpeza_clicked()
{
    limpeza *tela = new limpeza(this);
    tela->show();
}

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : CPP config - Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20220718.172615      */
