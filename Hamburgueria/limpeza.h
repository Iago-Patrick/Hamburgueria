#ifndef LIMPEZA_H
#define LIMPEZA_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class limpeza;
}

class limpeza : public QMainWindow
{
    Q_OBJECT

public:
    explicit limpeza(QWidget *parent = nullptr);
    ~limpeza();

private slots:
    void on_botao_tabela_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::limpeza *ui;
    QSqlTableModel *model;
    void adicionar_botoes();
};

#endif // LIMPEZA_H
