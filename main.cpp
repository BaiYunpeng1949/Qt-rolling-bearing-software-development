#include "rbevaluation.h"
#include "welcome_byp.h"

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QObject>
#include <QDebug>

//void

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册一下线程传递信号的时候需要使用的向量数组
    qRegisterMetaType<QVector<double>> ("QVector<double>"); //为了能使用QVector<double>
    qRegisterMetaType<QVector<QPointF>> ("QVector<QPointF>"); //为了能将刷新的数据添加进来

    //OpenGL全局format设置
    //QSurfaceFormat format;
    //format.setDepthBufferSize(24);
    //format.setStencilBufferSize(8);
    //format.setVersion(3, 2);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    //QSurfaceFormat::setDefaultFormat(format);



    RBEvaluation *w = new RBEvaluation();

    //初始化欢迎界面
    Welcome_BYP *WelcomeByp = new Welcome_BYP();
    WelcomeByp->move ((QApplication::desktop()->width() - WelcomeByp->width())/2,(QApplication::desktop()->height() - WelcomeByp->height())/2);
    WelcomeByp->show();
    //建立连接，信号与槽
    QObject::connect(WelcomeByp,&Welcome_BYP::IntToMain,w,&RBEvaluation::dealWelcometoMain);    //w->show();  一定要有
    QObject::connect(WelcomeByp,&Welcome_BYP::IntToMain,
            [=]()
            {
                w->show();    //欢迎界面后再显示
            }
            );
    return a.exec();
}
