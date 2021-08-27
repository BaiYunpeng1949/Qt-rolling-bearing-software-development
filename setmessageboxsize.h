#ifndef SETMESSAGEBOXSIZE_H
#define SETMESSAGEBOXSIZE_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QResizeEvent>

class SetMessageBoxSize : public QMessageBox
{
    Q_OBJECT
public:
    explicit SetMessageBoxSize(QWidget *parent = nullptr);
    ~SetMessageBoxSize();
signals:

public:
    void AutosetSize(int width,int hight);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    int m_width;
    int m_hight;

};

#endif // SETMESSAGEBOXSIZE_H
