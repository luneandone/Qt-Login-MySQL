QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    close.cpp \
    forgetpassword.cpp \
    login.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    passworddialog.cpp \
    register.cpp \
    registerdialog.cpp

HEADERS += \
    close.h \
    forgetpassword.h \
    login.h \
    logindialog.h \
    mainwindow.h \
    passworddialog.h \
    register.h \
    registerdialog.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    passworddialog.ui \
    registerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
