/**
  *@file RadarRangeDopplerConsumer.cpp
  * Management class to to hanldle separate threaded process of
  * polling radar data feed for incoming data and converting
  * and storing this data used for signal power plotting
*/

#include <map>
#include <QTimer>

#include "Gui.h"
#include "RadarRangeDopplerConsumer.h"
#include "model/RangeDopplerData.h"
#include "model/RangeDopplerDataReader.h"


using namespace dcap;

namespace trex {

RadarRangeDopplerConsumer::RadarRangeDopplerConsumer(dcap::ChannelSpecsDataPtr &_channelData,
                                               RangeDopplerDataPtr &_rangeDopplerData,
                                               QObject *parent) :
    QObject(parent),
    m_channelData(_channelData),
    m_rangeDopplerData(_rangeDopplerData)

{
    m_Reader = std::make_shared<RangeDopplerDataReader>(m_rangeDopplerData);

}


void RadarRangeDopplerConsumer::doDataConsume(){

    do {
        RangeDopplerBufferRaw buffer = m_Reader->request(100);
        if (m_Reader->getSampleType() != cbf::BasicType::FLOAT64_COMPLEX)
            throw std::runtime_error("Wrong Datatype read in RadarRangeDopplerConsumer");
        // TODO Deal with timed out request
        if (buffer.bytes <= 0) break;

        RangeDopplerMap *map = new RangeDopplerMap();
        int samples = buffer.bytes/m_Reader->getBytesPerSample();
        map->data = new double[samples];
        auto *buff = reinterpret_cast<std::complex<double> *>(buffer.buffer);
        for (size_t sample; sample < samples; sample++) {
            double mag = sqrt(pow(buff[sample].real(), 2.0) + pow(buff[sample].real(), 2.0));
            map->data[sample] = 20.0 * std::log10(mag);
        }

        map->rangeBins = buffer.rangeBins;
        map->dopplerBins = buffer.dopplerBins;
        m_Reader->release(buffer);

        emit resultReady(map);

    } while (false);


    QTimer::singleShot(0, this, &RadarRangeDopplerConsumer::doDataConsume);
}

}

