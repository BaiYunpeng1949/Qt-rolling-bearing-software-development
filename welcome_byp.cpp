#include "welcome_byp.h"
#include "ui_welcome_byp.h"

Welcome_BYP::Welcome_BYP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcome_BYP)
{
    ui->setupUi(this);
    //设置为无边框效果
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Welcome_BYP::~Welcome_BYP()
{
    delete ui;
}

////三个按钮进入功能
void Welcome_BYP::on_pushButton_clicked()
{
    emit IntToMain(1); //rb_mode
    this->close();
}

void Welcome_BYP::on_pushButton_2_clicked()
{
    emit IntToMain(2); //tb_mode
    this->close();
}

void Welcome_BYP::on_pushButton_3_clicked()
{
    emit IntToMain(3); //cb_mode
    this->close();
}
