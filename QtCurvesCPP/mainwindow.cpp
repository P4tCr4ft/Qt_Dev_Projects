#include "mainwindow.h"
#include "ui_mainwindow.h"



// constructor body
MainWindow::MainWindow(QWidget *parent) :
    // baseclass constructor is called
    QMainWindow(parent),
    // ui object is initialised with a new
    // instance of Ui::MainWindow
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAstroid_clicked()
{
    // now add some code to set an active shape
    // on the render area. Can do this in similar way
    // to setting background color.
    this->ui->renderArea->setShape(RenderArea::Astroid);

    // we want to change the background color
    // for the render area.
    // how do we do this?
    // we go to renderarea.h and in the public
    // section need to add a new function to change
    // the background color

    // use ui object to access our render area

    // started with setBackgroundColor call here,
    // but now moving it to paintEvent for all
    // buttons
//    this->ui->renderArea->setBackgroundColor(Qt::red);
    this->ui->renderArea->repaint();

}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
//    this->ui->renderArea->setBackgroundColor(Qt::green);
    this->ui->renderArea->repaint();


}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
//    this->ui->renderArea->setBackgroundColor(Qt::blue);
    this->ui->renderArea->repaint();


}

void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
//    this->ui->renderArea->setBackgroundColor(Qt::yellow);
    this->ui->renderArea->repaint();


}
