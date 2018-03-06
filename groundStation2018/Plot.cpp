#include "Plot.h"

const QwtInterval radialInterval(0.0, 100.0);
const QwtInterval azimuthInterval(0.0, 360.0);

Plot::Plot(QWidget *parent) :
    QwtPolarPlot(QwtText("Polar Plot"), parent)
{
    setAutoReplot(false);
    setPlotBackground(Qt::darkBlue);

    // scales
    setScale(QwtPolar::Azimuth,
             azimuthInterval.minValue(), azimuthInterval.maxValue(),
             azimuthInterval.width()/24);

    setScaleMaxMinor(QwtPolar::Azimuth, 2);
    setScale(QwtPolar::Radius,
             radialInterval.minValue(), radialInterval.maxValue(),
             radialInterval.width()/5);

// below achieves same scale for Azimuth and Radius more simply
//    setScale( QwtPolar::Azimuth, 0, 360, 15);
//    setScale(QwtPolar::Radius, 0, 100, 20);

    // grids, axes
    m_grid = new QwtPolarGrid();
    m_grid->setPen( QPen( Qt::white ) );

    for ( int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++ )
    {
        m_grid->showGrid( scaleId );
//            m_grid->showMinorGrid( scaleId );

        QPen minorPen( Qt::gray );
#if 0
        minorPen.setStyle( Qt::DotLine );
#endif
        m_grid->setMinorGridPen( scaleId, minorPen );
    }

    m_grid->setAxisPen( QwtPolar::AxisAzimuth, QPen( Qt::black ) );

    m_grid->showAxis( QwtPolar::AxisAzimuth, true );
    m_grid->showAxis( QwtPolar::AxisLeft, false );
    m_grid->showAxis( QwtPolar::AxisRight, true );
    m_grid->showAxis( QwtPolar::AxisTop, true );
    m_grid->showAxis( QwtPolar::AxisBottom, false );
    m_grid->showGrid( QwtPolar::Azimuth, true );
    m_grid->showGrid( QwtPolar::Radius, true );

    m_grid->attach( this );

    // curves, none for now

    // markers
    m_marker = new QwtPolarMarker();
    m_marker->setPosition( QwtPointPolar( 57.3, 54.72 ) );
    m_marker->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::white ), QPen( Qt::green ), QSize( 9, 9 ) ) );
    m_marker->setLabelAlignment( Qt::AlignHCenter | Qt::AlignTop );

    QwtText text( "Marker" );
    text.setColor( Qt::black );
    QColor bg( Qt::white );
    bg.setAlpha( 200 );
    text.setBackgroundBrush( QBrush( bg ) );

    m_marker->setLabel( text );
    m_marker->attach( this );

    QwtLegend *legend = new QwtLegend;
    insertLegend( legend,  QwtPolarPlot::BottomLegend );

}
