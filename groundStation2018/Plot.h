#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <qwt_polar_plot.h>
//#include <qwt_plot.h>

#include <qwt_polar_grid.h>
#include <qwt_polar_curve.h>
#include <qpen.h>
#include <qwt_series_data.h>
#include <qwt_symbol.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_polar_marker.h>
#include <qwt_scale_engine.h>

// Example has a Plotsettings class used to setup
// curves for plotting.
// not implemented at this stage ...

//class PlotSettings
//{

//};

class Plot : public QwtPolarPlot
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);

signals:

public slots:

private:
    QwtPolarGrid *m_grid;
//    QwtPolarCurve *m_curve[PlotSettings::NumCurves];
};

#endif // PLOT_H
