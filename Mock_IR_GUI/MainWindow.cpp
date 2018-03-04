#include "MainWindow.h"
#include "ui_MainWindow.h"
//#include <qwt_plot.h>
#include <QPaintEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    some_widget(new QWidget)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Steve/Qt_Dev_Projects/Mock_IR_GUI/thermal_jet.jpg");
    ui->label_pic->setPixmap(pix);

    QPixmap pix2("C:/Users/Steve/Qt_Dev_Projects/Mock_IR_GUI/thermal_jet_greyscale.jpg");
    ui->label_greyscale->setPixmap(pix2);

    QPixmap pix3("C:/Users/Steve/Qt_Dev_Projects/Mock_IR_GUI/signal_graph_final.jpg");
    ui->label_signal->setPixmap(pix3);



//    ui->mdiArea->addSubWindow(some_widget);
    ui->subwindow->setFixedWidth(590);
    ui->subwindow->setFixedHeight(370);
    ui->subwindow->setWindowTitle("Video");

    ui->subwindow_2->setFixedWidth(470);
    ui->subwindow_2->setFixedHeight(370);
    ui->subwindow_2->setWindowTitle("Video out");

    ui->subwindow_3->setFixedWidth(500);
    ui->subwindow_3->setFixedHeight(250);
    ui->subwindow_3->setWindowTitle("IR Signal bracket");

    ui->subwindow_4->setFixedWidth(560);
    ui->subwindow_4->setFixedHeight(250);
    ui->subwindow_4->setWindowTitle("Hardware Status");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked()
{
//    ui->radioButton->setStyleSheet("background-color: red");
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked){
        ui->radioButton->setStyleSheet("background-color: green");
    }
    else
    {
        ui->radioButton->setStyleSheet("background-color: grey");
    }
}

void MainWindow::on_radioButton_2_toggled(bool checked2)
{
    if (checked2){
        ui->radioButton_2->setStyleSheet("background-color: green");
    }
    else
    {
        ui->radioButton_2->setStyleSheet("background-color: grey");
    }

}

void MainWindow::on_radioButton_2_clicked()
{

}
