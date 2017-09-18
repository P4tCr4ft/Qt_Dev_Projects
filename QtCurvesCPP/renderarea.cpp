#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>

// constructor body
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent),
      mBackgoundColor (0, 0, 255),
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

void RenderArea::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing, true);
//    painter.drawRect(this->rect());


    // now depending on different mShape we want
    // to execute different code. For now we will
    // just change background color, but in future
    // will add code that actually draws the curves.
    // note, previously setBackgroundColor was called
    // in MainWindow functions, but now used in the
    // switch below, changing color directly

    switch (mShape) {
    case Astroid:
        mBackgoundColor = Qt::red;
        break;

    case Cycloid:
         mBackgoundColor = Qt::green;
        break;

    case HuygensCycloid:
        mBackgoundColor = Qt::blue;
        break;

    case HypoCycloid:
        mBackgoundColor = Qt::yellow;
        break;

    default:
        break;

    }

    painter.setBrush(mBackgoundColor);
    painter.setPen(mShapeColor);


    // drawing area
    painter.drawRect(this->rect());
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
}
