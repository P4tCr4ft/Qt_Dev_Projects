#include "renderarea.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

// looking at QMdiSubWindow
#include <QMdiSubWindow>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor (0, 0, 255),
    mShapeColor (255, 255, 255),
    mShape (Astroid)
{

}

// function bodies
QSize RenderArea::minimumSizeHint() const{

    return QSize(100, 100);

}
QSize RenderArea::sizeHint() const{

    return QSize(400, 200);
}

void RenderArea::testLayout(){
//    QMdiSubWindow *testViewWindow = new QMdiSubWindow();
//    testViewWindow->

//Ui::MainWindow *ui2;
//MainWindow::setUiObj(ui2);

//    QMdiArea mdiArea;
//    QMdiSubWindow *subWindow1 = new QMdiSubWindow;


}
