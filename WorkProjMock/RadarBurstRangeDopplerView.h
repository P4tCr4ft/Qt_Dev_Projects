/**
 *@file RadarBurstRangeDopplerView.h
 * View for RadarBurstModelData
*/

#ifndef RADARBURSTRANGEDOPPLERVIEW_H
#define RADARBURSTRANGEDOPPLERVIEW_H

#include "model/RadarBurstModelData.h"
#include "model/RangeDopplerData.h"
#include "view/RadarBurstRangeDopplerViewInfo.h"
#include "RadarDataSelectList.h"
#include "RadarRangeDopplerConsumer.h"

#include <model/channelspecsdata.h>
#include <view/abstractview.h>
#include <view/iviewcreator.h>
#include <map>

#include <qwt_plot.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_interval.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
//#include <QHBoxLayout>
#include <QBoxLayout>
#include <QGroupBox>

namespace trex {


/**
 * Creates a view to display RadarBurstModelData.
 *
 * The view allows the selection of a given burst and dislplays 2D color map of power/range/doppler.
 */

class RadarBurstRangeDopplerView : public dcap::AbstractView
{
    Q_OBJECT

    /**
     * @brief dataConsumerThread is separate thread used to run data processing in RadarRangeDopplerConsumer
     */
    QThread dataConsumerThread;

public:
//    explicit RadarBurstRangeDopplerView(QWidget *parent = 0);
    RadarBurstRangeDopplerView();
    virtual ~RadarBurstRangeDopplerView();

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
     * @brief handleResults slot function stores results from consumer thread, ready for plotting
     * @param result is result storage object
     */
    void handleResults(RangeDopplerMap *result);

    /**
     * @brief updateBurst slot used to update the plot according to selection made in the burst list
     * @param index is the burst index
     */
    void updateBurst(int index);

    /**
     * @brief updateChannel slot used to update the plot according to selection made in the channel list
     */
    void updateChannel();

signals:

    /**
     * @brief operate signal used to activate main data processing function in the cosumer thread
     */
    void operate();

protected:

    /**
     * @brief createView function creates selectable lists used to plot required data,
     * for data burst and data channel
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

    // is just beamform info, not individual channels
    RangeDopplerDataPtr rangeDopplerData;
    dcap::ChannelSpecsDataPtr channelData;

    // plot member
    QwtPlot *m_plot;
    QwtPlotZoomer *m_zoomer;
    QwtPlotPanner *m_panner;
    QwtPlotMagnifier *m_magnifier;


    // members for spectrogram
    QwtPlotSpectrogram *m_spectrogram;
    QwtScaleWidget * m_rightAxis;

    QHBoxLayout *m_layout;
    QGroupBox *selectListGroupBox;

    QComboBox *m_burst_list;

    RadarRangeDopplerConsumer *dataConsumer;

    std::vector<RangeDopplerMap *> m_plot_maps;
    uint32_t m_burst_counter = 0;
    bool m_zoom_base = false;


    /**
     * @brief updatePlot function plots/replots coloured intensity map of range/doppler,
     * according to selections made in lists
     */
    void updatePlot();

};


/**
 * @brief The RadarBurstRangeDopplerViewCreator class creates view used to display subwindow
 * which in turn contain required radar data plots
 */
class RadarBurstRangeDopplerViewCreator : public dcap::IViewCreator
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
            viewInfo = std::shared_ptr<dcap::IViewInfo>(new RadarBurstRangeDopplerViewInfo());
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
    virtual RadarBurstRangeDopplerView *createView(const std::shared_ptr<dcap::IHardwareController> &controller,
                                  const dcap::MultiSystemIds &systems,
                                  const dcap::MultiChannelIds &channels,
                                  QWidget *parent ) {
        auto *view = new RadarBurstRangeDopplerView();
        view->setController(controller);
        view->create(systems, channels, parent);
        return view;
    }
};

}


#endif // RADARBURSTRANGEDOPPLERVIEW_H
