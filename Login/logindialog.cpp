#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QFocusEvent>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include "registerdialog.h"
#include "passworddialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    // 关闭最小化和最大化按钮
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(350,390);
    //加载css样式表
    QString qss;
    QFile file(":/css/login.css");
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
    connect(ui->closeBtn,&closeButton::clicked,this,&loginDialog::closeWindow);
    connect(ui->registeBtn,&registerButton::clicked,this,&loginDialog::openRegisterWindow);
    connect(ui->passwordBtn,&forgetPassword::clicked,this,&loginDialog::openPasswordWindow);
    ui->passwordEdit->setEchoMode(QLineEdit::Password); //设置密码输入显示为圆点（并不是加密）
    ui->userEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->passwordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0); //去掉lineEdit被选中时出现的默认蓝色边框
    connect(ui->loginPushButton,&QPushButton::clicked,this,&loginDialog::loginButton);

}

loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::initEdit(){

    ui->userEdit->setPlaceholderText(" 请输入用户名");
    ui->userEdit->setFocusPolicy(Qt::ClickFocus); // 设置焦点策略
//    ui->userEdit->setStyleSheet("color: #bfbfbf;");
    ui->passwordEdit->setPlaceholderText(" 请输入密码");
//    ui->passwordEdit->setStyleSheet("color: #bfbfbf;");
    ui->passwordEdit->setFocusPolicy(Qt::ClickFocus); // 设置焦点策略
}

void loginDialog::focusInEvent(QFocusEvent *event)
{
    if (event->reason() == Qt::MouseFocusReason) {
        ui->userEdit->clear();
        ui->passwordEdit->clear();
    }

}

void loginDialog::paintEvent(QPaintEvent *event)
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

void loginDialog::closeWindow()
{
    this->close();
}

void loginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->globalPos() - pos();
        // 将事件接受标记为真，防止其他操作干扰
        event->accept();
    }
}

void loginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - lastMousePos);
        event->accept();
    }
}

void loginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}
void loginDialog::openRegisterWindow()
{
    registerDialog *secondWindow = new registerDialog;
    close();
    secondWindow->exec();
}

void loginDialog::openPasswordWindow()
{
    passwordDialog *secondWindow = new passwordDialog;
    close();
    secondWindow->exec();
}

void loginDialog::loginButton() {
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");//127.0.0.1
    database.setPort(3306);
    database.setUserName("root");
    database.setPassword("rootpassword");

    database.setDatabaseName("UAV"); //这个库是存在的
    if (database.open()) {
        qDebug() << "连接MySQL数据库成功";
    } else {
        qDebug() << "连接MySQL数据库失败";
    }
    QSqlQuery query(database);
    QString username = ui->userEdit->text();
    QString password = ui->passwordEdit->text();
    query.prepare("SELECT * FROM user WHERE name = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        this->accept();
        qDebug() << "登录成功";
    } else {
       QMessageBox::information(this, "错误", "用户名或密码不对", QMessageBox::Ok);
    }
}



