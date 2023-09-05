#ifndef ADICIONAR_USUARIOS_H
#define ADICIONAR_USUARIOS_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class adicionar_usuarios;
}

class adicionar_usuarios : public QDialog
{
    Q_OBJECT

public:
    explicit adicionar_usuarios(QWidget *parent = nullptr);
    ~adicionar_usuarios();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::adicionar_usuarios *ui;
    QSqlTableModel *model;
};

#endif // ADICIONAR_USUARIOS_H
