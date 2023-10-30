#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QFile>
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
registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    // 关闭最小化和最大化按钮
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(350,390);
    //加载css样式表
    QString qss;
    QFile file(":/css/register.css");
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
    connect(ui->closeBtn,&closeButton::clicked,this,&registerDialog::closeWindow);
    connect(ui->loginBtn,&loginButton::clicked,this,&registerDialog::openLoginWindow);
     //去掉lineEdit被选中时出现的默认蓝色边框
    ui->userEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->passwordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    connect(ui->registerPushButton, &QPushButton::clicked,this,&registerDialog::registerButton);

}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::initEdit(){

    ui->userEdit->setPlaceholderText(" 请输入用户名");
    ui->userEdit->setFocusPolicy(Qt::ClickFocus); // 设置焦点策略
    ui->passwordEdit->setPlaceholderText(" 请输入密码");
    ui->passwordEdit->setFocusPolicy(Qt::ClickFocus); // 设置焦点策略
}

void registerDialog::focusInEvent(QFocusEvent *event)
{
    if (event->reason() == Qt::MouseFocusReason) {
        ui->userEdit->clear();
        ui->passwordEdit->clear();
    }

}

void registerDialog::paintEvent(QPaintEvent *event)
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

void registerDialog::closeWindow()
{
    this->close();
}

void registerDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->globalPos() - pos();
        // 将事件接受标记为真，防止其他操作干扰
        event->accept();
    }
}

void registerDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - lastMousePos);
        event->accept();
    }
}

void registerDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}
void registerDialog::openLoginWindow()
{
    loginDialog *secondWindow = new loginDialog;
    close();
    secondWindow->exec();
}
void registerDialog::registerButton()
{
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
    if(username == "" || password == ""){
        qDebug() <<"输入为空";
        QMessageBox::information(this, "错误", "输入为空", QMessageBox::Ok);
        return;
    }
    query.prepare("SELECT name FROM user WHERE name = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        qDebug() << "用户名已存在，请选择其他用户名";
        // 显示注册失败错误消息框
        QMessageBox::information(this, "错误", "用户名已存在，请重新输入", QMessageBox::Ok);
        return;
    }
    query.prepare("INSERT INTO user (name, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        qDebug() << "用户注册成功";
        QMessageBox::information(this, "欢迎", "注册账号成功，去登录", QMessageBox::Ok);
    } else {
        qDebug() << "用户注册失败" << query.lastError().text();

    }
    database.close();
}
