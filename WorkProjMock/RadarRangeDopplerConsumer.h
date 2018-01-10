/**
  *@file RadarRangeDopplerConsumer.h
  * Management class to to hanldle separate threaded process of
  * polling radar data feed for incoming data and converting
  * and storing this data used for signal power plotting
*/

#ifndef RADARRANGEDOPPLERCONSUMER_H
#define RADARRANGEDOPPLERCONSUMER_H

#include <QObject>
#include <QThread>

#include "Gui.h"
#include "model/RangeDopplerDataReader.h"
#include <qwt_plot_curve.h>


namespace trex {

class RangeDopplerMap {

public:
    std::double_t * data;

    /// number of range bins (X axis)
    std::int32_t rangeBins;

    /// number of doppler bins (Y axis)
    std::int32_t dopplerBins;

    RangeDopplerMap() {
        data = NULL;
    }
    ~RangeDopplerMap() {
        if (data) delete[] data;
    }
};

/**
 * @brief The RadarRangeDopplerConsumer class
 *
 * In a separate thread, this class continually interrogates radar data reader
 * and separates, coverts and stores the incoming data from reader
 * into real and imag storage structures ready to plot radar burst signal power
 *
 */
class RadarRangeDopplerConsumer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief RadarRangeDopplerConsumer
     * @param _channelData is a map mapping channelID to corresponding individual channel specifications
     * @param _burstData is a map mapping channelID against radar burst data model for that channel
     * @param parent is parent class of instance of this class
     */
    explicit RadarRangeDopplerConsumer(dcap::ChannelSpecsDataPtr &_channelData, RangeDopplerDataPtr &_rangeDopplerData,
                                    QObject *parent = 0);

signals:
    /**
     * @brief resultReady is signal used to pass pointer to curve data to slot function,
     * which stores data curves to be displayed in plot
     * @param result is map mapping channleId to resuting radar burst data curve
     */
    void resultReady(RangeDopplerMap* result);

public slots:
    /**
     * @brief doDataConsume main slot function to poll for new radar burst data,
     * categorise, convert and store any new data into real and imag datasets,
     * which then are used to generate curves for plotting
     */
    void doDataConsume();

private:
    dcap::ChannelSpecsDataPtr &m_channelData;
    RangeDopplerDataPtr &m_rangeDopplerData;
    RadarRangeDopplerReaderPtr m_Reader;


};


}

#endif // RADARBURSTDATACONSUMER_H
