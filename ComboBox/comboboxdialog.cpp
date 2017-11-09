#include "comboboxdialog.h"
#include "ui_comboboxdialog.h"
#include <QListWidgetItem>

ComboBoxDialog::ComboBoxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComboBoxDialog)
{
    ui->setupUi(this);

    for(int i = 0; i <= 10; i++){
        ui->comboBox_2->addItem("Item " + QString::number(i));
        ui->listWidget->addItem("Item " + QString::number(i));
//        new QListWidgetItem("Hello", ui->listWidget);
//        ui->listWidget->sortItems(Qt::AscendingOrder);

    }
}

ComboBoxDialog::~ComboBoxDialog()
{
    delete ui;
}

void ComboBoxDialog::on_pushButton_clicked()
{
    QMessageBox::information(this, "Item selection", ui->comboBox->currentText());
}

void ComboBoxDialog::on_comboBox_2_activated(const QString &arg1)
{
    QMessageBox *resultBox = new QMessageBox;
    resultBox->setFixedWidth(100);
    resultBox->information(this, arg1, arg1);
//    QMessageBox::information(this, arg1, ui->comboBox->currentText());
//    QMessageBox::setFixedWidth(100);


}
