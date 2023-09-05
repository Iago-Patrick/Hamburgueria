#ifndef CONTROLE_MESAS_H
#define CONTROLE_MESAS_H

#include <QMainWindow>

namespace Ui {
class controle_mesas;
}

class controle_mesas : public QMainWindow
{
    Q_OBJECT

public:
    explicit controle_mesas(QWidget *parent = nullptr);
    ~controle_mesas();

private slots:
    void on_voltar_clicked();

    void fechar_mesa(int mesa_id);

    void set_valor_label();

    void on_b_finalizar_conta_m1_clicked();

    void on_b_finalizar_conta_m2_clicked();

    void on_b_finalizar_conta_m3_clicked();

    void on_b_finalizar_conta_m4_clicked();

    void on_b_finalizar_conta_m5_clicked();

    void on_b_finalizar_conta_m6_clicked();

private:
    Ui::controle_mesas *ui;
    QVector<QString> mesas;
    double valor;
};

#endif // CONTROLE_MESAS_H
