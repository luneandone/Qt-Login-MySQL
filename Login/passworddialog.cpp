#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QFile>
#include <QFocusEvent>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include "logindialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError> //获取SQL操作时错误信息
#include <QDebug>
#include <QMessageBox>
passwordDialog::passwordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwordDialog)
{
    ui->setupUi(this);
    // 关闭最小化和最大化按钮
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(350,390);
    //加载css样式表
    QString qss;
    QFile file(":/css/password.css");
    if (file.open(QFile::ReadOnly))
    {
        //用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
        qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }
    // 设置窗口背景为透明
    setAttribute(Qt::WA_TranslucentBackground);
    initEdit();
    connect(ui->closeBtn,&closeButton::clicked,this,&passwordDialog::closeWindow);
    connect(ui->loginBtn,&loginButton::clicked,this,&passwordDialog::openLoginWindow);
    ui->passwordEdit->setEchoMode(QLineEdit::Password); //设置密码输入显示为圆点（并不是加密）
    //去掉QLineEdit被选中时出现的默认蓝色边框
    ui->userEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->passwordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    connect(ui->passwordPushButton,&QPushButton::clicked,this,&passwordDialog::changePassword);

}

passwordDialog::~passwordDialog()
{
    delete ui;
}
void passwordDialog::initEdit(){

    ui->userEdit->setPlaceholderText(" 请输入账号");
    ui->userEdit->setFocusPolicy(Qt::ClickFocus); // 设置焦点策略
    //    ui->userEdit->setStyleSheet("color: #bfbfbf;");
    ui->passwordEdit->setPlaceholderText(" 请输入新密码");
    //    ui->passwordEdit->setStyleSheet("color: #bfbfbf;");
    ui->passwordEdit->setFocusPolicy(Qt::ClickFocus); // 设置焦点策略
}

void passwordDialog::focusInEvent(QFocusEvent *event)
{
    if (event->reason() == Qt::MouseFocusReason) {
        ui->userEdit->clear();
        ui->passwordEdit->clear();
    }

}

void passwordDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true); //抗锯齿
    QColor backgroundColor(Qt::white); // 设置背景颜色
    QColor borderColor(Qt::transparent); // 设置边框颜色
    painter.setBrush(backgroundColor);
    painter.setPen(QPen(borderColor, 2));
    painter.drawRoundedRect(rect(),10,10);

}



void passwordDialog::closeWindow()
{
    this->close();
}

void passwordDialog::openLoginWindow()
{
    loginDialog *secondWindow = new loginDialog;
    close();
    secondWindow->exec();

}

void passwordDialog::changePassword()
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");//127.0.0.1
    database.setPort(3306);
    database.setUserName("root");
    database.setPassword("Lune_one1028");

    database.setDatabaseName("UAV"); //这个库是存在的
    if (database.open()) {
        qDebug() << "连接MySQL数据库成功";
    } else {
        qDebug() << "连接MySQL数据库失败";
    }
    QSqlQuery query(database);
    QString username = ui->userEdit->text();
    QString newPassword = ui->passwordEdit->text();
    // 检查用户名是否存在
    QSqlQuery checkQuery(database);
    checkQuery.prepare("SELECT name FROM user WHERE name = :username");
    checkQuery.bindValue(":username", username);

    if (checkQuery.exec() && checkQuery.next()) {
        // 更新用户密码
        QSqlQuery updateQuery(database);
        updateQuery.prepare("UPDATE user SET password = :newPassword WHERE name = :username");
        updateQuery.bindValue(":newPassword", newPassword);
        updateQuery.bindValue(":username", username);

        if (updateQuery.exec()) {
            qDebug() << "密码修改成功";
            QMessageBox::information(this, "成功", "密码修改成功", QMessageBox::Ok);
        } else {
            qDebug() << "密码修改失败" << updateQuery.lastError().text();
            QMessageBox::information(this, "错误", "密码修改失败，请重试", QMessageBox::Ok);
        }
    } else {
        qDebug() << "用户名不存在";
        QMessageBox::information(this, "错误", "用户名不存在，请重新输入", QMessageBox::Ok);
    }

    database.close();
}

void passwordDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->globalPos() - pos();
        // 将事件接受标记为真，防止其他操作干扰
        event->accept();
    }
}

void passwordDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - lastMousePos);
        event->accept();
    }
}

void passwordDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}
