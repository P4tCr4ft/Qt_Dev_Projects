//------------------------------------------------------------------------------
// Copyright (c) DST, 2017
//
// Project:                 EA EP Testbed
// Classification:          Unclassified
// Intellectual Property:   DST
//
//------------------------------------------------------------------------------
// $Id: RadarBurstRangeDopplerView.cpp 4504 2017-11-21 04:19:01Z triplets $
//------------------------------------------------------------------------------
//
/**
 *@file RadarBurstRangeDopplerView.cpp
 * View for RadarBurstModelData
*/

#include "RadarBurstRangeDopplerView.h"
#include "RadarBurstRangeDopplerViewInfo.h"

#include "model/RangeDopplerDataReader.h"

#include <qimage.h>
#include <qpixmap.h>
#include <qlayout.h>
#include <complex>
#include <qwt_scale_engine.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_rasteritem.h>
#include <qwt_matrix_raster_data.h>

namespace trex {


class RangeDopplerSpectrogram : public QwtPlotSpectrogram {

    size_t doppler_bins, range_bins;
    QVector<double> *m_values;
    QwtMatrixRasterData *m_data;
    QwtColorMap *m_color_map;

public:
    static QwtColorMap *makeColorMap() {
        double pos;
        auto *color_map = new QwtLinearColorMap(QColor(0,0,189), QColor(132,0,0));
        pos = 1.0/13.0*1.0;  color_map->addColorStop(pos, QColor(0,0,255));
        pos = 1.0/13.0*2.0;  color_map->addColorStop(pos, QColor(0,66,255));
        pos = 1.0/13.0*3.0;  color_map->addColorStop(pos, QColor(0,132,255));
        pos = 1.0/13.0*4.0;  color_map->addColorStop(pos, QColor(0,189,255));
        pos = 1.0/13.0*5.0;  color_map->addColorStop(pos, QColor(0,255,255));
        pos = 1.0/13.0*6.0;  color_map->addColorStop(pos, QColor(66,255,189));
        pos = 1.0/13.0*7.0;  color_map->addColorStop(pos, QColor(132,255,132));
        pos = 1.0/13.0*8.0;  color_map->addColorStop(pos, QColor(189,255,66));
        pos = 1.0/13.0*9.0;  color_map->addColorStop(pos, QColor(255,255,0));
        pos = 1.0/13.0*10.0; color_map->addColorStop(pos, QColor(255,189,0));
        pos = 1.0/13.0*12.0; color_map->addColorStop(pos, QColor(255,66,0));
        pos = 1.0/13.0*13.0; color_map->addColorStop(pos, QColor(189,0,0));
        return color_map;
    }

    explicit RangeDopplerSpectrogram(RangeDopplerMap* rangeDopplerMap) : QwtPlotSpectrogram() {

        range_bins    = rangeDopplerMap->rangeBins;
        doppler_bins  = rangeDopplerMap->dopplerBins;
        size_t size = doppler_bins*range_bins;
        m_values = new QVector<double>(size);

        double min_value=1e9, max_value=1e-9;
        for (size_t range = 0; range < range_bins; range++)
        {
            size_t r_range = (range_bins-range-1);
            for (size_t doppler = 0; doppler < doppler_bins; doppler++)
            {
                size_t data_idx = doppler + r_range * doppler_bins;
                size_t map_idx  = range   + doppler * range_bins;
                double val = (*m_values)[data_idx] = rangeDopplerMap->data[map_idx];
                max_value = std::max(max_value, val);
                min_value = std::min(min_value, val);
            }
        }

        m_data = new QwtMatrixRasterData();
        m_data->setValueMatrix(*m_values, doppler_bins);
        double width_m_one = doppler_bins-1;
        double height_m_one = range_bins-1;
        m_data->setResampleMode(QwtMatrixRasterData::NearestNeighbour);
        m_data->setInterval(Qt::XAxis, QwtInterval(-width_m_one/2.0, width_m_one/2.0));
        m_data->setInterval(Qt::YAxis, QwtInterval(0.0, height_m_one));
        m_data->setInterval(Qt::ZAxis, QwtInterval(min_value, max_value));

        m_color_map = makeColorMap();

        this->setData(m_data);
        this->setColorMap(m_color_map);
        this->setDisplayMode(QwtPlotSpectrogram::ImageMode, true);
        this->setDisplayMode(QwtPlotSpectrogram::ContourMode, false);
    }

    virtual ~RangeDopplerSpectrogram() {
        delete m_values;
    }
};


RadarBurstRangeDopplerView::RadarBurstRangeDopplerView():
    dcap::AbstractView(std::shared_ptr<dcap::IViewInfo>(new RadarBurstRangeDopplerViewInfo()))
{
    if(this->layout() != NULL){
        delete this->layout();
    }
    dataConsumer = NULL;

    m_layout = new QHBoxLayout();
    selectListGroupBox = new QGroupBox("Select List Layout");
    m_plot = new QwtPlot(this->getInfo()->getName(), this);
    m_plot->setAxisTitle(QwtPlot::xBottom, "Doppler bins");
    m_plot->setAxisTitle(QwtPlot::yLeft, "Range bins");

    m_magnifier = new QwtPlotMagnifier(m_plot->canvas());
//    m_magnifier->setAxisEnabled(QwtPlot::yLeft, false);
    double wheelFactor = 1.1;
    m_magnifier->setWheelFactor(wheelFactor);
    m_zoomer = new QwtPlotZoomer(m_plot->canvas());
    m_panner = new QwtPlotPanner(m_plot->canvas());
    m_panner->setMouseButton(Qt::MiddleButton);


    // construct objects for spectrogram
    m_spectrogram = NULL;
    m_plot->plotLayout()->setAlignCanvasToScales(true);

    m_layout->addWidget(m_plot);
    m_layout->addWidget(selectListGroupBox);
    m_layout->setStretch(0,100);
    this->setLayout(m_layout);

}

RadarBurstRangeDopplerView::~RadarBurstRangeDopplerView()
{

    if (dataConsumer != NULL && dataConsumerThread.isRunning()) {
        dataConsumerThread.quit();
        dataConsumerThread.wait();
    }

    delete m_plot;

}

QSize RadarBurstRangeDopplerView::sizeHint() const
{
    return QSize(300,100);
}

void RadarBurstRangeDopplerView::writeConfiguration(QSettings &/*settings*/)
{
    // TODO
}

void RadarBurstRangeDopplerView::readConfiguration(QSettings &/*settings*/)
{
    // TODO
}

void RadarBurstRangeDopplerView::handleResults(RangeDopplerMap* result){
    //do something with results
    m_plot_maps.push_back(result);
    m_burst_counter += 1;
    m_burst_list->addItem(QString("Burst %1").arg(m_burst_counter));
    m_burst_list->setCurrentIndex(m_burst_list->count()-1);
}

bool RadarBurstRangeDopplerView::createView()
{
    this->logMessage("createView", dcap::LogLevel::INFO_VERBOSE);
    // TODO create the widgets

    m_burst_list = new QComboBox(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_burst_list);
    selectListGroupBox->setLayout(layout);
    return true;
}

bool RadarBurstRangeDopplerView::viewAvailable(const std::vector<std::shared_ptr<dcap::ICapabilityData> > &capabilities, const std::vector<std::shared_ptr<dcap::IModelData> > &modelData)
{
    static_cast<void>(capabilities);

    this->logMessage("viewAvailable", dcap::LogLevel::INFO_VERBOSE);

    // loads in the radar burst and channel data
    for(auto d: modelData){
        auto dId = (d)->getID();
        if(dId == TrexModelDataIds::RangeDopplerId){
            auto _rangeDopplerData = std::dynamic_pointer_cast<RangeDopplerData>(d);
            auto cId = _rangeDopplerData->getChannel();
            if(_rangeDopplerData)
                this->rangeDopplerData = _rangeDopplerData;
            else {
                // should never happen
                this->logMessage("Bad dynamic_pointer_cast<RadarBurstModelData>", dcap::LogLevel::WARNING);
            }
        } else if(dId == dcap::SingleChannelId(MODEL_DATA_CHANNEL_SPECS)){
            auto channelData = std::dynamic_pointer_cast<dcap::ChannelSpecsData>(d);
            auto cId = channelData->getChannel();
            if(channelData) {
                this->channelData = channelData;
            } else {
                // should never happen
                this->logMessage("Bad dynamic_pointer_cast<ChannelSpecsData>", dcap::LogLevel::WARNING);
            }
        }
    }

    // verify we got the data we require for the view
    if(this->channelData == NULL || this->rangeDopplerData == NULL){
        QString message = QString("Missing channel specs data or range doppler data");
        this->logMessage(message, dcap::LogLevel::ERROR);

        return false;
    }

    // setup radar data consumer thread
    dataConsumer = new RadarRangeDopplerConsumer(this->channelData, this->rangeDopplerData);
    dataConsumer->moveToThread(&dataConsumerThread);

    connect(&dataConsumerThread, &QThread::finished, dataConsumer, &RadarRangeDopplerConsumer::deleteLater);
    connect(this, &RadarBurstRangeDopplerView::operate, dataConsumer, &RadarRangeDopplerConsumer::doDataConsume);
    connect(dataConsumer, &RadarRangeDopplerConsumer::resultReady, this, &RadarBurstRangeDopplerView::handleResults);

    typedef void (QComboBox::*IndexChangedFcn)(int);
    connect(m_burst_list, (IndexChangedFcn)&QComboBox::currentIndexChanged, this, &RadarBurstRangeDopplerView::updateBurst);

    dataConsumerThread.start();
    emit operate();

    return true;
}

void RadarBurstRangeDopplerView::updateBurst(int){
    updatePlot();
    m_zoomer->setZoomBase();

//    if(m_zoom_base != true)
//    {
//        m_zoomer->setZoomBase();
//        m_zoom_base = true;
//    }


}

void  RadarBurstRangeDopplerView::updateChannel(){
    updatePlot();
}

void RadarBurstRangeDopplerView::updatePlot() {

    this->logMessage("updating plot ...", dcap::LogLevel::INFO_VERBOSE);

    m_plot->detachItems(QwtPlotItem::Rtti_PlotItem, true);

    m_spectrogram = new RangeDopplerSpectrogram(m_plot_maps[m_burst_list->currentIndex()]);
    m_spectrogram->attach(m_plot);

    QwtInterval xaxis = m_spectrogram->interval(Qt::XAxis);
    m_plot->setAxisScale(QwtPlot::xBottom, xaxis.minValue(), xaxis.maxValue());
    QwtInterval yaxis = m_spectrogram->interval(Qt::YAxis);
    m_plot->setAxisScale(QwtPlot::yLeft, yaxis.minValue(), yaxis.maxValue());

    QwtInterval zaxis = m_spectrogram->interval(Qt::ZAxis);

    QwtScaleWidget *scale = m_plot->axisWidget(QwtPlot::yRight);
    scale->setColorBarEnabled(true);
    scale->setColorMap( zaxis, RangeDopplerSpectrogram::makeColorMap());

    m_plot->setAxisScale(QwtPlot::yRight, zaxis.minValue(), zaxis.maxValue());
    m_plot->enableAxis(QwtPlot::yRight);
    m_plot->setAxisTitle(QwtPlot::yRight, "Power (dB)");

    m_plot->replot();

}


bool RadarBurstRangeDopplerView::viewUnavailable()
{
    this->logMessage("viewUnavailable", dcap::LogLevel::INFO_VERBOSE);

    // stops all feeders...
    if (dataConsumer) {
        dataConsumerThread.quit();
        dataConsumerThread.wait();

        disconnect(&dataConsumerThread, &QThread::finished, dataConsumer, &RadarRangeDopplerConsumer::deleteLater);
        disconnect(this, &RadarBurstRangeDopplerView::operate, dataConsumer, &RadarRangeDopplerConsumer::doDataConsume);
        disconnect(dataConsumer, &RadarRangeDopplerConsumer::resultReady, this, &RadarBurstRangeDopplerView::handleResults);

    }

    // reset burst list
    typedef void (QComboBox::*IndexChangedFcn)(int);
    disconnect(m_burst_list, (IndexChangedFcn)&QComboBox::currentIndexChanged, this, &RadarBurstRangeDopplerView::updateBurst);
    try {
        while(m_burst_list->count() > 0)
            m_burst_list->removeItem(0);
    } catch (std::exception err) {
        this->logMessage(QString("Could not clear burst list: %1").arg(err.what()), dcap::LogLevel::ERROR);
    }

    // clear out range doppler images
    m_plot->detachItems(QwtPlotItem::Rtti_PlotItem, true);

    for (RangeDopplerMap *dop_map : m_plot_maps){
        delete dop_map->data;
    }

    m_plot_maps.clear();

    m_burst_counter = 0;
    m_zoom_base = false;

    return true;
}


}
