#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPaintEvent>
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
    void initEdit();
protected:
    void focusInEvent(QFocusEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void closeWindow();
    void openRegisterWindow();
    void openPasswordWindow();
    void loginButton();
private:
    Ui::loginDialog *ui;
    bool isDragging;
    QPoint lastMousePos;
};

#endif // LOGINDIALOG_H
