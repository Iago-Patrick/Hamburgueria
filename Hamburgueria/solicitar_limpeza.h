#ifndef SOLICITAR_LIMPEZA_H
#define SOLICITAR_LIMPEZA_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class solicitar_limpeza;
}

class solicitar_limpeza : public QDialog
{
    Q_OBJECT

public:
    explicit solicitar_limpeza(QWidget *parent = nullptr);
    ~solicitar_limpeza();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::solicitar_limpeza *ui;
};

#endif // SOLICITAR_LIMPEZA_H
