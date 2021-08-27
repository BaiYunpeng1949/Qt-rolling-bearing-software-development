#include "sta_diaprogress.h"
#include "ui_sta_diaprogress.h"

Sta_DiaProgress::Sta_DiaProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sta_DiaProgress)
{
    ui->setupUi(this);
}

Sta_DiaProgress::~Sta_DiaProgress()
{
    delete ui;
}

void Sta_DiaProgress::dealstaprogress()
{
    this->show();
}

//关闭对话框
void Sta_DiaProgress::on_pushButton_clicked()
{
    this->hide();
}
