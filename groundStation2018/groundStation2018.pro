#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T12:51:57
#
#-------------------------------------------------

#CONFIG += qwt

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = groundStation2018
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    RenderArea.cpp \
    Plot.cpp

HEADERS += \
        MainWindow.h \
    RenderArea.h \
    Plot.h

FORMS += \
        MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../QwtPolar-1.1.1/lib/ -lqwtpolar
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../QwtPolar-1.1.1/lib/ -lqwtpolard
else:unix: LIBS += -L$$PWD/../../../../QwtPolar-1.1.1/lib/ -lqwtpolar

INCLUDEPATH += $$PWD/../../../../QwtPolar-1.1.1/include
DEPENDPATH += $$PWD/../../../../QwtPolar-1.1.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Qwt-6.1.3/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Qwt-6.1.3/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/../../../../Qwt-6.1.3/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../Qwt-6.1.3/include
DEPENDPATH += $$PWD/../../../../Qwt-6.1.3/include
