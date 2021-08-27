#ifndef BYP_OPENGLWINDOW_H
#define BYP_OPENGLWINDOW_H

#include <QMainWindow>

namespace Ui {
class BYP_OpenGLWindow;
}

class BYP_OpenGLWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BYP_OpenGLWindow(QWidget *parent = nullptr);
    ~BYP_OpenGLWindow();

private:
    Ui::BYP_OpenGLWindow *ui;
};

#endif // BYP_OPENGLWINDOW_H
