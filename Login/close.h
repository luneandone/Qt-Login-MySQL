#ifndef CLOSE_H
#define CLOSE_H

#include <QWidget>

class closeButton: public QWidget
{
    Q_OBJECT
public:
    explicit closeButton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event); //窗口刷新时调用
signals:
    void clicked();
private:
     QPixmap m_pixmap;
};

#endif // CLOSE_H
