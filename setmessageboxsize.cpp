#include "setmessageboxsize.h"

SetMessageBoxSize::SetMessageBoxSize(QWidget *parent) : QMessageBox(parent)
  ,m_width(0)
  ,m_hight(0)
{

}

SetMessageBoxSize::~SetMessageBoxSize(){}

void SetMessageBoxSize::AutosetSize(int width, int hight)
{
    m_width = width;
    m_hight = hight;
}

void SetMessageBoxSize::resizeEvent(QResizeEvent *event)
{
    setFixedSize(m_width,m_hight);
}
