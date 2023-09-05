#ifndef COMES_H
#define COMES_H

#include <QMainWindow>
#include <QSpinBox>

namespace Ui {
class comes;
}

class comes : public QMainWindow
{
    Q_OBJECT

public:
    explicit comes(QWidget *parent = nullptr);
    ~comes();

private slots:
    void on_pushButton_clicked();

    void on_pedir_item1_clicked();

    void on_pedir_item2_clicked();

    void on_pedir_item3_clicked();

    void on_pedir_item4_clicked();

    void on_pedir_item5_clicked();

    void on_pedir_item6_clicked();

    void on_pedir_item7_clicked();

    void on_pedir_item8_clicked();

    void on_pedir_item9_clicked();



private:
    Ui::comes *ui;
    void pedir(const QString nome, int quantidade);
};

#endif // COMES_H
