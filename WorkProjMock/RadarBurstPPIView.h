/**
 *@file RadarBurstPPIView.h
 * View for RadarBurstModelData
*/

#ifndef RADARBURSTPPIVIEW_H
#define RADARBURSTPPIVIEW_H

#include "model/RadarBurstModelData.h"
#include "view/RadarBurstPPIViewInfo.h"
#include "RadarDataSelectList.h"
#include "RadarBurstDataConsumer.h"

#include <model/channelspecsdata.h>
#include <view/abstractview.h>
#include <view/iviewcreator.h>
#include <map>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
//#include <QHBoxLayout>
#include <QBoxLayout>
#include <QGroupBox>

namespace trex {

class RadarBurstPPIPlot;

/**
 * Creates a view to display RadarBurstModelData.
 *
 * The view allows the selection of a given burst and dislplays radar platform and target/s on a Plan Position Indicator map.
 */

class RadarBurstPPIView : public dcap::AbstractView
{
    Q_OBJECT

    /**
     * @brief dataConsumerThread is separate thread used to run data processing in RadarPPIConsumer
     */
    QThread dataConsumerThread;

public:
//    explicit RadarBurstPPIView(QWidget *parent = 0);
    RadarBurstPPIView();
    virtual ~RadarBurstPPIView();

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
     * @brief handleResults slot function stores results from data processing in consumer thread,
     * ready for plotting
     * @param result is a storage object
     */
    void handleResults(const std::map<dcap::SingleChannelId, sRadarBurstCurves_t *> *result);


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
    // variables for burstdata and channeldata
    /// The radar bursts we are displaying, indexed by channel ID
    std::map<dcap::SingleChannelId, RadarBurstModelDataPtr> burstData;

    /// the channel information, indexed by channel ID
    std::map<dcap::SingleChannelId, dcap::ChannelSpecsDataPtr> channelData;

    // plot member
    RadarBurstPPIPlot *m_plot;

    QHBoxLayout *m_layout;
    QGroupBox *selectListGroupBox;

    QComboBox *m_burst_list;

    QListWidget *m_chan_list;
    std::map<QListWidgetItem*, dcap::SingleChannelId> m_channel_map;

    RadarBurstDataConsumer *dataConsumer;

    typedef const std::map<dcap::SingleChannelId, sRadarBurstCurves_t*> *CurveMapPtr;
    std::vector<CurveMapPtr> m_plot_curves;
    uint32_t m_burst_counter = 0;

    /**
     * @brief updatePlot function plots/replots coloured plan position indicator,
     * according to selections made in lists
     */
    void updatePlot();

};

/**
 * @brief The RadarBurstPPIViewCreator class creates view used to display subwindow
 * which in turn contain required radar data plots
 */
class RadarBurstPPIViewCreator : public dcap::IViewCreator
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
            viewInfo = std::shared_ptr<dcap::IViewInfo>(new RadarBurstPPIViewInfo());
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
    virtual RadarBurstPPIView *createView(const std::shared_ptr<dcap::IHardwareController> &controller,
                                  const dcap::MultiSystemIds &systems,
                                  const dcap::MultiChannelIds &channels,
                                  QWidget *parent ) {
        auto *view = new RadarBurstPPIView();
        view->setController(controller);
        view->create(systems, channels, parent);
        return view;
    }
};

}


#endif // RADARBURSTPPIVIEW_H
