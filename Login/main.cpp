#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     loginDialog login;
    int ret = login.exec();
    if(QDialog::Accepted == ret) {
        MainWindow w;
        w.show();
        return a.exec();
    }
    return ret;
}
