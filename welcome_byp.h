#ifndef WELCOME_BYP_H
#define WELCOME_BYP_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Welcome_BYP;
}

class Welcome_BYP : public QWidget
{
    Q_OBJECT

public:
    explicit Welcome_BYP(QWidget *parent = nullptr);
    ~Welcome_BYP();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Welcome_BYP *ui;

signals:
    void IntToMain(int main_mode);
};

#endif // WELCOME_BYP_H
