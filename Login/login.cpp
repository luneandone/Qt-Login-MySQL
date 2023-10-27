#include "login.h"
#include <QPainter>
loginButton::loginButton(QWidget *parent)
    : QWidget{parent}
{
    buttonText = "登录账户"; // 设置按钮文字
}
void loginButton::mousePressEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    emit clicked();
}
void loginButton::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font;
    font.setPointSize(12);
    font.setUnderline(true);
    painter.setPen(QColor("#12bb37")); // 设置文本颜色为 #12bb37
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, buttonText);
}
