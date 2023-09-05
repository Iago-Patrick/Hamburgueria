#ifndef GARCOM_H
#define GARCOM_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class garcom;
}

class garcom : public QMainWindow
{
    Q_OBJECT

public:
    explicit garcom(QWidget *parent = nullptr);
    ~garcom();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_b_adicionar_clicked();

    void on_b_atender_clicked();

    void on_b_solicitar_limpeza_clicked();

private:
    Ui::garcom *ui;
    QSqlTableModel *model_disp;
    QSqlTableModel *model_ocup;
    void adicionar_botoes_abrir_mesa();
    void adicionar_botoes_fechar_mesa();

};

#endif // GARCOM_H
