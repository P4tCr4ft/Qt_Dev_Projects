#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    // putting objects in public makes them
    //accessible outside the class

    // constructor prototype (signature?)
    explicit RenderArea(QWidget *parent = nullptr);

    // overriding 2 functions from baseclass QWidget
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    // another prototype
    // declaring some kind of list?
    // will have to look up enum sometime
    // the elements are just ints I think
    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid };

    // function to set background color
    // note: very short function so contain entire function here
    // using setter/getter pair to fetch or update class member variables
    void setBackgroundColor (QColor color) {mBackgoundColor = color; } // setter
//    QColor backgroundColor () const { return mBackgoundColor; } // getter

    // now add setter and getter functions for active shape
    void setShape (ShapeType shape) {mShape = shape; } // setter
    ShapeType shape () const { return mShape; }


    // also need to override custom paint event
    // needs to be protected
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    // declare variables in private
    QColor mBackgoundColor;
    QColor mShapeColor;
    ShapeType mShape;
};

#endif // RENDERAREA_H
