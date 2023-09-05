#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#include <QMainWindow>

namespace Ui {
class financeiro;
}

class financeiro : public QMainWindow
{
    Q_OBJECT

public:
    explicit financeiro(QWidget *parent = nullptr);
    ~financeiro();

private slots:
    void on_pushButton_clicked();

private:
    Ui::financeiro *ui;
};

#endif // FINANCEIRO_H
