#include "forgetpassword.h"
#include <QPainter>
forgetPassword::forgetPassword(QWidget *parent)
    : QWidget{parent}
{
    buttonText = "忘记密码";
}

void forgetPassword::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked();
}

void forgetPassword::paintEvent(QPaintEvent *event)
{
     Q_UNUSED(event);
     QPainter painter(this);
     QFont font;
     font.setPointSize(14);
     painter.setPen(QColor("#9b9b9b")); // 设置文本颜色为 #12bb37
     painter.setFont(font);
     painter.drawText(rect(), Qt::AlignCenter, buttonText);

}
