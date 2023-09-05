#ifndef FINALIZACAO_H
#define FINALIZACAO_H

#include <QMainWindow>

namespace Ui {
class finalizacao;
}

class finalizacao : public QMainWindow
{
    Q_OBJECT

public:
    explicit finalizacao(QWidget *parent = nullptr);
    ~finalizacao();

private slots:
    void on_temp_fechar_clicked();
    void voltar_tela();

private:
    Ui::finalizacao *ui;
    QTimer *checkTimer;
};

#endif // FINALIZACAO_H
