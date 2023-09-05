#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class estoque;
}

class estoque : public QMainWindow
{
    Q_OBJECT

public:
    explicit estoque(QWidget *parent = nullptr);
    ~estoque();

private slots:
    void on_b_voltar_clicked();
    void on_b_adicionar_clicked();

    void on_b_remover_clicked();

    void on_pushButton_clicked();

private:
    Ui::estoque *ui;
    QSqlTableModel *model;
};

#endif // ESTOQUE_H
