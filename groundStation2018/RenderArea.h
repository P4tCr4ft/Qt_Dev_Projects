#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
//    explicit RenderArea(QWidget *parent = nullptr, QColor backgroundColor = nullptr);
    explicit RenderArea(QWidget *parent = nullptr, QColor backgroundColor = QColor(0, 0, 100));

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *paintEvent) Q_DECL_OVERRIDE;


signals:

public slots:

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
};

#endif // RENDERAREA_H
