#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <qwt_plot.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QwtPlot *plot = new QwtPlot(this);
    setCentralWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
