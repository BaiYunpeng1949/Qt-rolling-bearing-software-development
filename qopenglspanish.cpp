#include "qopenglspanish.h"
#include "ui_qopenglspanish.h"

QOpenGLSpanish::QOpenGLSpanish(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::QOpenGLSpanish)
{
    ui->setupUi(this);
}

QOpenGLSpanish::~QOpenGLSpanish()
{
    delete ui;
}

void QOpenGLSpanish::QColorToRGB(const QColor &C, float &r, float &g, float &b) const
{

}

void QOpenGLSpanish::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void QOpenGLSpanish::resizeGL(int w, int h)
{

}

void QOpenGLSpanish::paintGL()
{

}

void QOpenGLSpanish::on_pushButton_2_clicked()
{
    close();
}
