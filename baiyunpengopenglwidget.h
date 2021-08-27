#ifndef BAIYUNPENGOPENGLWIDGET_H
#define BAIYUNPENGOPENGLWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QPainter>
#include <QScreen>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QProcess>
#include <QPushButton>
#include <QTimer>
#include <math.h>   //为了使用max函数

//OpenGL补充库，接口
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QtOpenGL>
#include <GL/glu.h>

#define MAX_BUFFER 2048

class BaiYunpengOpenGLWidget : public QOpenGLWidget,protected QOpenGLFunctions//QWidget
{
    Q_OBJECT
public:
    explicit BaiYunpengOpenGLWidget(QWidget *parent = nullptr);
    ~BaiYunpengOpenGLWidget();

    //槽函数
    void dealCloudviewport(int integer);
    void UpdateAnimation();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
private:
    QOpenGLContext *m_context;
    QOpenGLFunctions *m_function;

    QString m_line_0;
    QStringList m_list_0;
    int m_whichview;
    QTimer *m_timer;
    qreal m_rotation;

};

#endif // BAIYUNPENGOPENGLWIDGET_H
