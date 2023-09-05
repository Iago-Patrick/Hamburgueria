#ifndef CLIENTE_H
#define CLIENTE_H

#include <QMainWindow>


namespace Ui {
class cliente;
}

class cliente : public QMainWindow
{
    Q_OBJECT

public:
    explicit cliente(QWidget *parent = nullptr);
    ~cliente();
    int rodizio = 0;
    int preco = 20;
    int conta = 0;

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void mudar_tela();

private:
    Ui::cliente *ui;
    QTimer *checkTimer;
};

#endif // CLIENTE_H
