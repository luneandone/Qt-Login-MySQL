#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();
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
    void registerButton();
private:
    Ui::registerDialog *ui;
    bool isDragging;
    QPoint lastMousePos;
};

#endif // REGISTERDIALOG_H
