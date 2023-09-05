#ifndef MESA_DISPONIVEL_H
#define MESA_DISPONIVEL_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class mesa_disponivel;
}

class mesa_disponivel : public QMainWindow
{
    Q_OBJECT

public:
    explicit mesa_disponivel(QWidget *parent = nullptr);
    ~mesa_disponivel();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void proxima_tela();

private:
    Ui::mesa_disponivel *ui;
    QTimer *checkTimer;
};

#endif // MESA_DISPONIVEL_H
