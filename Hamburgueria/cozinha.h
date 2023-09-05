#ifndef COZINHA_H
#define COZINHA_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class cozinha;
}

class cozinha : public QMainWindow
{
    Q_OBJECT

public:
    explicit cozinha(QWidget *parent = nullptr);
    ~cozinha();

private slots:
    void on_b_voltar_clicked();

    void on_b_solicitar_limpeza_clicked();

    void on_pushButton_clicked();

    void on_check_tabela();

private:
    Ui::cozinha *ui;
    QSqlRelationalTableModel *model;
    void adicionar_botoes();
};

#endif // COZINHA_H
