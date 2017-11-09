/********************************************************************************
** Form generated from reading UI file 'comboboxdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBOBOXDIALOG_H
#define UI_COMBOBOXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComboBoxDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QComboBox *comboBox_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QListWidget *listWidget;

    void setupUi(QDialog *ComboBoxDialog)
    {
        if (ComboBoxDialog->objectName().isEmpty())
            ComboBoxDialog->setObjectName(QStringLiteral("ComboBoxDialog"));
        ComboBoxDialog->resize(519, 383);
        label = new QLabel(ComboBoxDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 30, 47, 13));
        pushButton = new QPushButton(ComboBoxDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 80, 75, 23));
        comboBox_2 = new QComboBox(ComboBoxDialog);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(8, 80, 111, 22));
        comboBox_2->setEditable(true);
        horizontalLayoutWidget = new QWidget(ComboBoxDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(190, 150, 281, 191));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(horizontalLayoutWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);


        horizontalLayout->addLayout(verticalLayout);

        listWidget = new QListWidget(ComboBoxDialog);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(220, 20, 141, 111));
        listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        pushButton->raise();
        comboBox_2->raise();
        horizontalLayoutWidget->raise();
        listWidget->raise();
        label->raise();

        retranslateUi(ComboBoxDialog);

        QMetaObject::connectSlotsByName(ComboBoxDialog);
    } // setupUi

    void retranslateUi(QDialog *ComboBoxDialog)
    {
        ComboBoxDialog->setWindowTitle(QApplication::translate("ComboBoxDialog", "ComboBoxDialog", Q_NULLPTR));
        label->setText(QApplication::translate("ComboBoxDialog", "Items:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ComboBoxDialog", "Which Item?", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("ComboBoxDialog", "ItemX", Q_NULLPTR)
        );

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("ComboBoxDialog", "New Item", Q_NULLPTR));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class ComboBoxDialog: public Ui_ComboBoxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBOBOXDIALOG_H
