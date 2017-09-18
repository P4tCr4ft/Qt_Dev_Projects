#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>


class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid };

    // now add setter and getter functions for active shape
    void setShape (ShapeType shape) {mShape = shape; } // setter
    ShapeType shape () const { return mShape; }

    // test func to look at QMdiSubWindow
    void testLayout();

signals:

public slots:

private:
    ShapeType mShape;
    QColor mBackgroundColor;
    QColor mShapeColor;
};

#endif // RENDERAREA_H
