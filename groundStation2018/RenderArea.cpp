#include "RenderArea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent, QColor backgroundColor) :
    QWidget(parent),
    mBackgroundColor(backgroundColor)
//    mBackgroundColor(0, 0, 255)

{

}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(200, 100);
}

void RenderArea::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setBrush(mBackgroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawRect(this->rect());
}
