#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>

class loginButton : public QWidget
{
    Q_OBJECT
public:
    explicit loginButton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event); //窗口刷新时调用
signals:
    void clicked();
private:
    QString buttonText;
};

#endif // LOGIN_H
