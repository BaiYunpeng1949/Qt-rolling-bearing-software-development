#ifndef CLOUDTEST_H
#define CLOUDTEST_H

#include <QMainWindow>
#include <QWidget>
#include <QOpenGLWindow>
#include <QGLWidget>
#include <QScreen>
#include <QPixmap>
#include <QImage>

//OpenGL补充库，接口
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QtOpenGL>
#include <GL/glu.h>


//Excel 文件读取库
#include <QFileDialog>
#include <QAxObject>

#include <QDebug>
#include <QProcess>
#include <QPushButton>
#include <math.h>   //为了使用max函数

//定义一个空间使得定义数组的时候没有自由数
#define MAX_BUFFER 2048

class CloudTest : public QOpenGLWidget//QOpenGLWindow
{
    Q_OBJECT
public:
    explicit CloudTest(QWidget *parent = nullptr);
    ~CloudTest();
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    //建立槽函数接收需要读取的文件名
    void dealCloudSentFilename(QString filename);

signals:
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    //印度教学,我后来才发现这个老师是西班牙人。。。
    QOpenGLContext *m_context;
    QOpenGLFunctions *m_function;

    QStringList m_list;
    QStringList m_list_y;
    QString m_line;

    QPoint m_lastpos;

    int m_xrotation;
    int m_yrotation;
    int m_zrotation;

};

#endif // CLOUDTEST_H
