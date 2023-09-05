#ifndef GERENTE_H
#define GERENTE_H

#include <QMainWindow>

namespace Ui {
class gerente;
}

class gerente : public QMainWindow
{
    Q_OBJECT

public:
    explicit gerente(QWidget *parent = nullptr);
    ~gerente();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::gerente *ui;
};

#endif // GERENTE_H
