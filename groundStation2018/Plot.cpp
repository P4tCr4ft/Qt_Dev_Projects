#include "Plot.h"

Plot::Plot(QWidget *parent) :
    QwtPolarPlot(QwtText("Polar Plot"), parent)
{
    setAutoReplot(false);
    setPlotBackground(Qt::darkBlue);

    // scales
    setScale(QwtPolar::Azimuth,
             azimuthInterval.minValue(), azimuthInterval.maxValue(),
             azimuthInterval.width()/12);

    setScaleMaxMinor(QwtPolar::Azimuth, 2);
    setScale(QwtPolar::Radius,
             radialInterval.minValue(), radialInterval.maxValue());

    // grids, axes
    m_grid = new QwtPolarGrid();


}
