#ifndef OPENGL1_H
#define OPENGL1_H

#include <QWidget>
#include <QDebug>
//OpenGL接口
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QtOpenGL>
#include <GL/glu.h>
//按键事件接口
#include <QKeyEvent>

namespace Ui {
class OpenGL1;
}

class OpenGL1 : public QOpenGLWidget,protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    explicit OpenGL1(QWidget *parent = nullptr);
    ~OpenGL1();

private:
    Ui::OpenGL1 *ui;

    //印度教学
    QOpenGLContext *m_context;
    QOpenGLFunctions *m_function;

protected:
    virtual void paintGL() override;
    virtual void initializeGL() override;
    virtual  void resizeGL(int w, int h) override;

    void keyPressEvent(QKeyEvent *keyevent) override;

    //印度教学视频
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
};

#endif // OPENGL1_H
