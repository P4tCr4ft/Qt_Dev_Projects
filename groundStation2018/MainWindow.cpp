#include "MainWindow.h"
#include "ui_MainWindow.h"
//#include <qwt_plot.h>
#include <QPainter>
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    some_widget(new RenderArea(this, QColor(0, 0, 255))),
    m_plot(new Plot(some_widget))

  // so need member initialise m_plot with a new Plot
  // and then create a layout, add plot to layout
  // add plot to widget, then add wiget to layout
  // or however ends up being done ...

{
    ui->setupUi(this);

//    not using mdiArea for plot widget at moment....

//    setCentralWidget(ui->mdiArea);
//    ui->mdiArea->addSubWindow(some_widget);


    QHBoxLayout *layout = new QHBoxLayout(some_widget);

//    2 lines below this comment acheive same result as 1 line above,
//    as far as appearance of output polar plot. But I would think
//    the better/safer option is to pass in a parent for the new layout
//    with regard to destruction ...

//    QHBoxLayout *layout = new QHBoxLayout();
//    some_widget->setLayout(layout);

    layout->addWidget(m_plot);

    setCentralWidget(some_widget);



// Below was wrong as layout needs association with widget,
// not mainWindow (which is what this-> is in this case)

//    this->setLayout(layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}
