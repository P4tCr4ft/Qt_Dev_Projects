#include "widget.h"
#include "ui_widget.h"

FooWidget::FooWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
// ... I don't need to do it here using member syntax
//    name("Stevo...")
{
    ui->setupUi(this);
}

FooWidget::~FooWidget()
{
    delete ui;
}

void FooWidget::nameSetter(){
    ui->lineEdit->setText(name);
}
