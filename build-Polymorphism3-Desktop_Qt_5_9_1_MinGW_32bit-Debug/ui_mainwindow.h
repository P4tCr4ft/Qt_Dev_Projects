/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSubSubSubMenu;
    QWidget *centralWidget;
    QPushButton *btnNinja;
    QPushButton *btnMonster;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QMenu *menuSomeMenu;
    QMenu *menuSubmenu;
    QMenu *menuSubSubMenu;
    QMenu *menuMenu2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(559, 347);
        actionSubSubSubMenu = new QAction(MainWindow);
        actionSubSubSubMenu->setObjectName(QStringLiteral("actionSubSubSubMenu"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnNinja = new QPushButton(centralWidget);
        btnNinja->setObjectName(QStringLiteral("btnNinja"));
        btnNinja->setGeometry(QRect(90, 100, 75, 23));
        btnMonster = new QPushButton(centralWidget);
        btnMonster->setObjectName(QStringLiteral("btnMonster"));
        btnMonster->setGeometry(QRect(230, 100, 75, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 158, 381, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(290, 210, 69, 22));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(60, 220, 70, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 559, 21));
        menuSomeMenu = new QMenu(menuBar);
        menuSomeMenu->setObjectName(QStringLiteral("menuSomeMenu"));
        menuSubmenu = new QMenu(menuSomeMenu);
        menuSubmenu->setObjectName(QStringLiteral("menuSubmenu"));
        menuSubSubMenu = new QMenu(menuSubmenu);
        menuSubSubMenu->setObjectName(QStringLiteral("menuSubSubMenu"));
        menuMenu2 = new QMenu(menuBar);
        menuMenu2->setObjectName(QStringLiteral("menuMenu2"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSomeMenu->menuAction());
        menuBar->addAction(menuMenu2->menuAction());
        menuSomeMenu->addAction(menuSubmenu->menuAction());
        menuSubmenu->addAction(menuSubSubMenu->menuAction());
        menuSubSubMenu->addAction(actionSubSubSubMenu);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSubSubSubMenu->setText(QApplication::translate("MainWindow", "SubSubSubMenu", Q_NULLPTR));
        btnNinja->setText(QApplication::translate("MainWindow", "Ninja", Q_NULLPTR));
        btnMonster->setText(QApplication::translate("MainWindow", "Monster", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Watch out!", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "CheckBox", Q_NULLPTR));
        menuSomeMenu->setTitle(QApplication::translate("MainWindow", "SomeMenu", Q_NULLPTR));
        menuSubmenu->setTitle(QApplication::translate("MainWindow", "Submenu", Q_NULLPTR));
        menuSubSubMenu->setTitle(QApplication::translate("MainWindow", "SubSubMenu", Q_NULLPTR));
        menuMenu2->setTitle(QApplication::translate("MainWindow", "Menu2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
