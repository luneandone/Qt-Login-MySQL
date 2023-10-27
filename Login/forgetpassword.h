#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>

class forgetPassword : public QWidget
{
    Q_OBJECT
public:
    explicit forgetPassword(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event); //窗口刷新时调用
signals:
    void clicked();
private:
    QString buttonText;

};

#endif // FORGETPASSWORD_H
