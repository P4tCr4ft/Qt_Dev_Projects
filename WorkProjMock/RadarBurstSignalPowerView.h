//------------------------------------------------------------------------------
// Copyright (c) DST, 2017
//
// Project:                 EA EP Testbed
// Classification:          Unclassified
// Intellectual Property:   DST
//
//------------------------------------------------------------------------------
// $Id: RadarBurstSignalPowerView.h 4521 2017-12-19 06:19:43Z triplets $
//------------------------------------------------------------------------------
//
/**
 *@file RadarBurstSignalPowerView.h
 * View for RadarBurstModelData
*/

#ifndef RADARBURSTSIGNALPOWER_H
#define RADARBURSTSIGNALPOWER_H

#include "model/RadarBurstModelData.h"
#include "view/RadarBurstSignalPowerViewInfo.h"
#include "RadarDataSelectList.h"
#include "RadarBurstDataConsumer.h"

#include <model/channelspecsdata.h>
#include <view/abstractview.h>
#include <view/iviewcreator.h>
#include <map>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
#include <qwt_legend.h>
#include <QLabel>

//#include <QHBoxLayout>
#include <QBoxLayout>
#include <QGroupBox>

namespace trex {

/**
 * Creates a view to display RadarBurstModelData.
 *
 * The view allows the selection of a given burst and will display all the channels available for that burst.
 */

class RadarBurstSignalPowerView : public dcap::AbstractView
{
    Q_OBJECT

    /**
     * @brief dataConsumerThread is separate thread used to run data processing in RadarBurstDataConsumer
     */
    QThread dataConsumerThread;

public:
    RadarBurstSignalPowerView();
    virtual ~RadarBurstSignalPowerView();

    QColor GetColor(float v, float vmin, float vmax);

    // AbstractView interface
    virtual QSize sizeHint() const override;

    /**
     * @brief writeConfiguration function saves menu list selections upon application exit
     * @param settings are used to store save settings parameters in a file
     */
    virtual void writeConfiguration(QSettings &settings) override;

    /**
     * @brief readConfiguration function loads saved menu list selections from file upon starting application
     * @param settings are used to store save settings parameters in a file
     */
    virtual void readConfiguration(QSettings &settings) override;

public slots:

    /**
     * @brief handleResults slot function stores resulting curves from data processing in consumer thread,
     * ready for plotting
     * @param result is a map of channelId to the results curve
     */
    void handleResults(const std::map<dcap::SingleChannelId, sRadarBurstCurves_t *> *result);

    /**
     * @brief updateBurst slot used to update the plot according to selection made in the burst list
     * @param index is the burst index
     */
    void updateBurst(int index);

    /**
     * @brief updateMode slot used to update the plot according to selections made in the mode list
     */
    void updateMode();

    /**
     * @brief updateChannel slot used to update the plot according to selection made in the channel list
     */
    void updateChannel();

    /**
     * @brief dataStateChanged slot used to change the state of data polling in the consumer
     * @param oldState
     * @param newState
     */
    void dataStateChanged(const dcap::ModelDataState oldState, const dcap::ModelDataState newState);

signals:

    /**
     * @brief operate signal used to activate main data processing function in the cosumer thread
     */
    void operate();

protected:

    // AbstractView interface

    /**
     * @brief createView function creates selectable lists used to plot required data,
     * for data burst, data mode, and data channel
     * @return boolean
     */
    bool createView() override;

    /**
     * @brief viewAvailable function loads in the radar burst and channel data based on model data structures,
     * which is then used to process incoming data in the consumer thread.
     * viewAvailable also spawns off thread for data processing in consumer.
     * @param capabilities is data cababilities attributes
     * @param modelData is data model/structure
     * @return boolean
     */
    bool viewAvailable(const std::vector<std::shared_ptr<dcap::ICapabilityData> > &capabilities,
                       const std::vector<std::shared_ptr<dcap::IModelData> > &modelData) override;

    /**
     * @brief viewUnavailable stops the consumer thread, disconnects stateChange signals
     * and clears burst and channel data
     * @return boolean
     */
    virtual bool viewUnavailable() override;

private:
    /// The radar bursts we are displaying, indexed by channel ID
    std::map<dcap::SingleChannelId, RadarBurstModelDataPtr> burstData;

    /// the channel information, indexed by channel ID
    std::map<dcap::SingleChannelId, dcap::ChannelSpecsDataPtr> channelData;

    // plot member
    QwtPlot *m_plot;
    QwtLegend *m_legend;
    QwtPlotZoomer *m_zoomer;
    QwtPlotPanner *m_panner;
    QwtPlotMagnifier *m_magnifier;

    QHBoxLayout *m_layout;
    QGroupBox *selectListGroupBox;

    QComboBox *m_burst_list;
    RadarDataSelectList *m_mode_list;
    QListWidget *m_chan_list;
    std::map<QListWidgetItem*, dcap::SingleChannelId> m_channel_map;

    std::vector<bool> m_init_channels;

    RadarBurstDataConsumer *dataConsumer;

    typedef const std::map<dcap::SingleChannelId, sRadarBurstCurves_t*> *CurveMapPtr;
    std::vector<CurveMapPtr> m_plot_curves;
    uint32_t m_burst_counter = 0;
    bool m_zoom_base = false;
    bool m_update_zoom = false;

    /**
     * @brief updatePlot function plots/replots coloured curves/graphs of resulting radar signla power data,
     * according to selections made in lists
     */
    void updatePlot();
};


/**
 * @brief The RadarBurstSignalPowerViewCreator class creates view used to display subwindow
 * which in turn contain required radar data plots
 */
class RadarBurstSignalPowerViewCreator : public dcap::IViewCreator
{
private:
    std::shared_ptr<dcap::IViewInfo> viewInfo;

public:

    /**
     * @brief getViewInfo retrieves name, capability and model info for created view
     * @return view info
     */
    std::shared_ptr<dcap::IViewInfo> getViewInfo() {
        if (!viewInfo) {
            viewInfo = std::shared_ptr<dcap::IViewInfo>(new RadarBurstSignalPowerViewInfo());
        }
        return viewInfo;
    }

    /**
     * @brief createView creates the new view object
     * @param controller is the controller used to communucate with the hardware
     * @param systems radar systesm
     * @param channels data channels
     * @param parent is parent class new object is a child of
     * @return view object
     */
    virtual RadarBurstSignalPowerView *createView(const std::shared_ptr<dcap::IHardwareController> &controller,
                                  const dcap::MultiSystemIds &systems,
                                  const dcap::MultiChannelIds &channels,
                                  QWidget *parent ) {
        auto *view = new RadarBurstSignalPowerView();
        view->setController(controller);
        view->create(systems, channels,parent);
        return view;
    }

};

}

#endif // RADARBURSTSIGNALPOWER_H
