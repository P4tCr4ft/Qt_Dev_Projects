#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class FooWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FooWidget(QWidget *parent = 0);
    ~FooWidget();

    void nameSetter();


// note this is a basic way of hardcoding name
// and doesn't use setter or getter, which it
// probably should

private:
    Ui::Widget *ui;

    // note if I initialise name here ...
    QString name = "Stevo...";
};

#endif // WIDGET_H
