#include "MainWindow.h"
#include "ui_MainWindow.h"
//#include <qwt_plot.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    some_widget(new QWidget)
{
    ui->setupUi(this);
    ui->mdiArea->addSubWindow(some_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
