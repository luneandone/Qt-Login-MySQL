#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

class registerButton : public QWidget
{
    Q_OBJECT
public:
    explicit registerButton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event); //窗口刷新时调用
signals:
    void clicked();
private:
    QString buttonText;
};

#endif // REGISTER_H
