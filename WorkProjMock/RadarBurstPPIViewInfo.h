/**
 *@file RadarBurstPPIViewInfo.h
 * View info for RadarBurstModelData
*/

#ifndef RADARBURSTPPIVIEWINFO_H
#define RADARBURSTPPIVIEWINFO_H

#include "model/TrexModelDataIds.h"

#include <view/iviewinfo.h>
#include <model/modeldefinitions.h>

namespace trex {

class RadarBurstPPIViewInfo : public dcap::IViewInfo {
public:
    QString getName() const {
        return "Radar Burst PPI View";
    }

    // TODO find images for PPI
    QIcon getAvailableIcon() const {
        return QIcon(":/images/radarburstsignalpowerview");
    }

    QIcon getUnavailableIcon() const {
        return QIcon(":/images/radarburstsignalpowerview_grey");
    }

    dcap::MultiCapabilityIds getRequiredCapabilities() const {
        return dcap::MultiCapabilityIds();
    }

    dcap::MultiCapabilityIds getOptionalCapabilities() const {
        dcap::MultiCapabilityIds caps;
        return caps;
    }

    dcap::MultiModelDataIds getRequiredModelData() const {
        dcap::MultiModelDataIds md;
        md.addID(dcap::SingleModelDataId(MODEL_DATA_CHANNEL_SPECS));
        md.addID(TrexModelDataIds::RadarBurstId);
        return md;
    }

    dcap::MultiModelDataIds getOptionalModelData() const {
        dcap::MultiModelDataIds md;
        return md;
    }

    bool isSingleChannel() const {
        return false;
    }

    bool isSingleSystem() const {
        return true;
    }

    dcap::DisplayType getPreferredDisplayType() {
        return dcap::MDI;
    }

    bool isUnique() const {
        return true;
    }
};

}

#endif // RADARBURSTPPIVIEWINFO_H
