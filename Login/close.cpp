#include "close.h"
#include <QPainter>
closeButton::closeButton(QWidget *parent)
    : QWidget{parent}
{
    m_pixmap.load(":/image/close.png");
    update();

}


void closeButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}


void closeButton::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter pen(this); //通过画家这个对象将图片画在不同的类中
    pen.drawPixmap(rect(), m_pixmap);
}

