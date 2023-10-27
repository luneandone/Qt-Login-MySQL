#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class passwordDialog;
}

class passwordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit passwordDialog(QWidget *parent = nullptr);
    ~passwordDialog();
    void initEdit();
protected:
    void focusInEvent(QFocusEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public slots:
    void closeWindow();
    void openLoginWindow();
    void changePassword();
private:
    Ui::passwordDialog *ui;
    bool isDragging;
    QPoint lastMousePos;
};

#endif // PASSWORDDIALOG_H
