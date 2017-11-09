#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testLayout(){
//    QMdiSubWindow *testViewWindow = new QMdiSubWindow();
//    testViewWindow->


//    QMdiArea mdiArea;
//    QMdiSubWindow *subWindow1 = new QMdiSubWindow;




void MainWindow::on_btnTest_clicked()
{
// QWidget does not have a member setShape. ui is a MainWindow object. The problem
// is that renderArea is still inheriting from QWidget and not new RenderArea
// class, RenderArea being the class that has setShape function. In the tutorial
// RenderArea class was promoted so renderArea object inherited from that, instead
// of QWidget, but I don't know how to do this without editing the design (.ui).

//this->ui->renderArea->setShape();
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{

}
