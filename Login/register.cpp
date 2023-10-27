#include "register.h"
#include <QPainter>
registerButton::registerButton(QWidget *parent)
    : QWidget{parent}
{
    buttonText = "注册账户"; // 设置按钮文字
}
void registerButton::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
void registerButton::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);

    QFont font;
    font.setPointSize(12);
    font.setUnderline(true);
    painter.setPen(QColor("#12bb37")); // 设置文本颜色为 #12bb37
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, buttonText);
}
