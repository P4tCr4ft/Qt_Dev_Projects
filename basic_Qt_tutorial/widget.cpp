#include "widget.h"
#include "ui_widget.h"

FooWidget::FooWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
// ... I could initialise it here using member syntax
// if I wanted to ...
    name("Stevo...")
// or initialise it in function below, which would
// re-assign name if initialised above ...
{
    ui->setupUi(this);
}

FooWidget::~FooWidget()
{
    delete ui;
}

// note can just use name here without using nameGetter
void FooWidget::nameSetter(QString &_name){
    name = _name;
    ui->lineEdit->setText(nameGetter());
//    ui->lineEdit->setText(name);
}

QString FooWidget::nameGetter(){
    return name;
}
