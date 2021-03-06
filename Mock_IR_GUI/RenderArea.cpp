#include "RenderArea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(180, 180, 200)

{

}

//QSize RenderArea::sizeHint() const
//{
//    return QSize(400, 200);
//    return QSize(600, 400);

//}

//QSize RenderArea::minimumSizeHint() const
//{
//    return QSize(200, 100);
//}

void RenderArea::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setBrush(mBackgroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawRect(this->rect());
}
