#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <qwt_polar_plot.h>
//#include <qwt_plot.h>


//class Plot : public QWidget
class Plot : public QwtPolarPlot
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PLOT_H
