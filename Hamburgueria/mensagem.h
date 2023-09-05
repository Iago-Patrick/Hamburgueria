#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <QDialog>

namespace Ui {
class mensagem;
}

class mensagem : public QDialog
{
    Q_OBJECT

public:
    explicit mensagem(QWidget *parent = nullptr);
    ~mensagem();

private slots:
    void on_b_enviar_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mensagem *ui;
};

#endif // MENSAGEM_H
