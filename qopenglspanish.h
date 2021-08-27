#ifndef QOPENGLSPANISH_H
#define QOPENGLSPANISH_H

#include <QWidget>

#include <QColor>
//OpenGL使用
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace Ui {
class QOpenGLSpanish;
}

class QOpenGLSpanish : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit QOpenGLSpanish(QWidget *parent = nullptr);
    ~QOpenGLSpanish();

private:
    Ui::QOpenGLSpanish *ui;
    void QColorToRGB(const QColor &C,float &r,float &g,float &b)const;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private slots:
    void on_pushButton_2_clicked();
};

#endif // QOPENGLSPANISH_H
