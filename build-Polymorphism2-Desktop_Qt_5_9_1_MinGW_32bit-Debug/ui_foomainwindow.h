/********************************************************************************
** Form generated from reading UI file 'foomainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOOMAINWINDOW_H
#define UI_FOOMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FooMainWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FooMainWindow)
    {
        if (FooMainWindow->objectName().isEmpty())
            FooMainWindow->setObjectName(QStringLiteral("FooMainWindow"));
        FooMainWindow->resize(400, 300);
        menuBar = new QMenuBar(FooMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        FooMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FooMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FooMainWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(FooMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FooMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FooMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FooMainWindow->setStatusBar(statusBar);

        retranslateUi(FooMainWindow);

        QMetaObject::connectSlotsByName(FooMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FooMainWindow)
    {
        FooMainWindow->setWindowTitle(QApplication::translate("FooMainWindow", "FooMainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FooMainWindow: public Ui_FooMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOOMAINWINDOW_H
