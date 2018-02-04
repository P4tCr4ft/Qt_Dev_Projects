/**
  *@file RadarBurstDataConsumer.h
  * Management class to to hanldle separate threaded process of
  * polling radar data feed for incoming data and converting
  * and storing this data used for signal power plotting
*/

#ifndef RADARBURSTDATACONSUMER_H
#define RADARBURSTDATACONSUMER_H

#include <QObject>
#include <QThread>

#include "Gui.h"
#include "model/RadarBurstDataReader.h"
#include <qwt_plot_curve.h>


namespace trex {

/**
  *@brief The sRadarBurstCurves_t struct
  * struct containing curve ojects for all modes
  * of data, which are attached to the plot and displayed
  */
typedef struct {
    QwtPlotCurve *real_samples = NULL;
    QwtPlotCurve *imag_samples = NULL;
    QwtPlotCurve *ampl_samples = NULL;
    QwtPlotCurve *phase_samples = NULL;
} sRadarBurstCurves_t ;

/**
  *@brief The sRadarBurstData_t struct
  * struct containing datasets of all modes
  * of data, used to generate curves for plotting
  */
typedef struct {
    double *time_samples = NULL;
    double *real_samples = NULL;
    double *imag_samples = NULL;
    double *ampl_samples = NULL;
    double *phase_samples = NULL;
} sRadarBurstData_t;

/**
  *@brief RadarBurstDataReaderPtr type used to create data reader
  */
typedef std::shared_ptr<RadarBurstDataReader> RadarBurstDataReaderPtr;

/**
 * @brief The RadarBurstDataConsumer class
 *
 * In a separate thread, this class continually interrogates radar data reader
 * and separates, coverts and stores the incoming data from reader
 * into real and imag storage structures ready to plot radar burst signal power
 *
 */
class RadarBurstDataConsumer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief RadarBurstDataConsumer
     * @param _channelData is a map mapping channelID to corresponding individual channel specifications
     * @param _burstData is a map mapping channelID against radar burst data model for that channel
     * @param parent is parent class of instance of this class
     */
    explicit RadarBurstDataConsumer(std::map<dcap::SingleChannelId, dcap::ChannelSpecsDataPtr> &_channelData,
                                    std::map<dcap::SingleChannelId, RadarBurstModelDataPtr> &_burstData,
                                    QObject *parent = 0);

signals:
    /**
     * @brief resultReady is signal used to pass pointer to curve data to slot function,
     * which stores data curves to be displayed in plot
     * @param result is map mapping channleId to resuting radar burst data curve
     */
    void resultReady(const std::map<dcap::SingleChannelId, sRadarBurstCurves_t*> *result);

public slots:
    /**
     * @brief doDataConsume main slot function to poll for new radar burst data,
     * categorise, convert and store any new data into real and imag datasets,
     * which then are used to generate curves for plotting
     */
    void doDataConsume();

private:
    std::map<dcap::SingleChannelId, dcap::ChannelSpecsDataPtr> &m_channelData;
    std::map<dcap::SingleChannelId, RadarBurstModelDataPtr> &m_burstData;
    std::map<dcap::SingleChannelId, RadarBurstDataReaderPtr> m_Readers;

    int index;
    uint8_t attempts;

};


}

#endif // RADARBURSTDATACONSUMER_H
