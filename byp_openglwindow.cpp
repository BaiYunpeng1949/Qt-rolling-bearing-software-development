#include "byp_openglwindow.h"
#include "ui_byp_openglwindow.h"

BYP_OpenGLWindow::BYP_OpenGLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BYP_OpenGLWindow)
{
    ui->setupUi(this);
}

BYP_OpenGLWindow::~BYP_OpenGLWindow()
{
    delete ui;
}
