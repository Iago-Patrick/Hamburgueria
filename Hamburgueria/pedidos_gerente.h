#ifndef PEDIDOS_GERENTE_H
#define PEDIDOS_GERENTE_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class pedidos_gerente;
}

class pedidos_gerente : public QMainWindow
{
    Q_OBJECT

public:
    explicit pedidos_gerente(QWidget *parent = nullptr);
    ~pedidos_gerente();

private slots:
    void on_b_voltar_clicked();
    void on_botao_tabela_clicked();

private:
    Ui::pedidos_gerente *ui;
    QSqlTableModel *model;
    void adicionar_botoes();
};

#endif // PEDIDOS_GERENTE_H
