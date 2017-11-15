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

    // note the arg name in prototype doens't even
    // have to match that in source .... weird
    // but type matters, ie have to both be ref
    void nameSetter(QString &name);
//    void nameSetter(QString name);

    QString nameGetter();


private:
    Ui::Widget *ui;

    // note if I declare name here, I can use
    // it anywhere in functions .cpp source code
    QString name;
};

#endif // WIDGET_H
