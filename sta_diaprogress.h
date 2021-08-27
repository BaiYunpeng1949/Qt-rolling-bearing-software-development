#ifndef STA_DIAPROGRESS_H
#define STA_DIAPROGRESS_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Sta_DiaProgress;
}

class Sta_DiaProgress : public QDialog
{
    Q_OBJECT

public:
    explicit Sta_DiaProgress(QWidget *parent = nullptr);
    ~Sta_DiaProgress();
    //定义一个槽函数，负责引出对话框告诉大家计算sta结束了
    void dealstaprogress();


private slots:
    void on_pushButton_clicked();

private:
    Ui::Sta_DiaProgress *ui;
};

#endif // STA_DIAPROGRESS_H
