/**
  *@file RadarBurstDataConsumer.cpp
  * Management class to to hanldle separate threaded process of
  * polling radar data feed for incoming data and converting
  * and storing this data used for signal power plotting
*/

#include <map>
#include <QTimer>

#include "Gui.h"
#include "RadarBurstDataConsumer.h"
#include "RadarBurstSignalPowerView.h"


using namespace dcap;

namespace trex {

RadarBurstDataConsumer::RadarBurstDataConsumer(std::map<dcap::SingleChannelId, dcap::ChannelSpecsDataPtr> &_channelData,
                                               std::map<dcap::SingleChannelId, RadarBurstModelDataPtr> &_burstData,
                                               QObject *parent) :
    QObject(parent),
    m_channelData(_channelData),
    m_burstData(_burstData),
    index(-1)
{
    for (auto channel : m_channelData) {
        RadarBurstModelDataPtr model_data = m_burstData[channel.first];
        m_Readers[channel.first] = std::make_shared<RadarBurstDataReader>(model_data);
    }

}


void RadarBurstDataConsumer::doDataConsume(){

    const uint8_t timeout = 100;
    const uint8_t retries = 20;


    bool drop_burst = false;

    auto *m_plot_curves = new std::map<dcap::SingleChannelId, sRadarBurstCurves_t*>();

    // polling to check for new radar data

    for (auto channel : m_channelData) {
        sRadarBurstData_t RadarBurstData;
        RadarBurstDataReaderPtr reader = m_Readers[channel.first];
        attempts = retries;
        RadarBurstBufferRaw buffer;
        while (attempts) {
            buffer = reader->request(timeout);
            // set initial index
            if (index == -1) { index = buffer.index; }

            // if this is the index we expected, use this buffer
            if (index == buffer.index && buffer.index >= 0)
                break;

            // if we expected a greater index, allow buffer to catch up
            if (index > buffer.index && buffer.index >= 0) {
                attempts = retries;
                reader->release(buffer);
//                this->logMessage(QString("Buffer dropped on channel %1, expected index %2 and got %3")
//                                 .arg(channel.first.toString())
//                                 .arg(index)
//                                 .arg(buffer.index), dcap::LogLevel::ERROR);
                continue;
            }
            attempts--;
        }
        if (!attempts) {
            drop_burst = true;
            break;
        };
        //allocate curves
        sRadarBurstCurves_t *curve = new sRadarBurstCurves_t();
        (*m_plot_curves)[channel.first] = curve;
        // time scale
        int samples = buffer.bytes/reader->getBytesPerSample();
        RadarBurstData.time_samples = new double[samples];
        for (int i = 0; i < samples; i++)
            RadarBurstData.time_samples[i] = i/channel.second->getSampleRate();
        RadarBurstData.real_samples = new double[samples];
        auto type = reader->getSampleType();
        switch (type) {
        case RadarBurstDataType::INT32_REAL:
            for (int i = 0; i < samples; i++)
                RadarBurstData.real_samples[i] = ((int32_t *)buffer.buffer)[i];
            break;
        case RadarBurstDataType::UINT32_REAL:
            for (int i = 0; i < samples; i++)
                RadarBurstData.real_samples[i] = ((uint32_t *)buffer.buffer)[i];
            break;
        case RadarBurstDataType::FLOAT32_REAL:
            for (int i = 0; i < samples; i++)
                RadarBurstData.real_samples[i] = ((float *)buffer.buffer)[i];
            break;
        case RadarBurstDataType::FLOAT64_REAL:
            for (int i = 0; i < samples; i++)
                RadarBurstData.real_samples[i] = ((double *)buffer.buffer)[i];
            break;
            // complex
        case RadarBurstDataType::INT16_COMPLEX:
            RadarBurstData.imag_samples = new double[samples];
            RadarBurstData.ampl_samples = new double[samples];
            RadarBurstData.phase_samples = new double[samples];
            curve->imag_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Im)"));
            curve->ampl_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Am)"));
            curve->phase_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Ph)"));
            for (int i = 0; i < samples; i++) {
                RadarBurstData.real_samples[i] = ((std::complex<std::int16_t> *)buffer.buffer)[i].real();
                RadarBurstData.imag_samples[i] = ((std::complex<std::int16_t> *)buffer.buffer)[i].imag();
                RadarBurstData.ampl_samples[i] = sqrt(pow(RadarBurstData.real_samples[i], 2.0) + pow(RadarBurstData.imag_samples[i], 2.0));
                RadarBurstData.phase_samples[i] = atan2(RadarBurstData.imag_samples[i], RadarBurstData.real_samples[i]);

                curve->imag_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.imag_samples, samples);
                curve->ampl_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.ampl_samples, samples);
                curve->phase_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.phase_samples, samples);
            }
            break;
        case RadarBurstDataType::FLOAT64_COMPLEX:
            RadarBurstData.imag_samples = new double[samples];
            RadarBurstData.ampl_samples = new double[samples];
            RadarBurstData.phase_samples = new double[samples];
            curve->imag_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Im)"));
            curve->ampl_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Am)"));
            curve->phase_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Ph)"));
            for (int i = 0; i < samples; i++) {
                RadarBurstData.real_samples[i] = ((std::complex<double> *)buffer.buffer)[i].real();
                RadarBurstData.imag_samples[i] = ((std::complex<double> *)buffer.buffer)[i].imag();
                RadarBurstData.ampl_samples[i] = sqrt(pow(RadarBurstData.real_samples[i], 2.0) + pow(RadarBurstData.imag_samples[i], 2.0));
                RadarBurstData.phase_samples[i] = atan2(RadarBurstData.imag_samples[i], RadarBurstData.real_samples[i]);

                curve->imag_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.imag_samples, samples);
                curve->ampl_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.ampl_samples, samples);
                curve->phase_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.phase_samples, samples);
            }
            break;
        default:
//            this->logMessage("Datatype not supported", dcap::LogLevel::WARNING);
//            return false;
            break;
        }
        // Every case will generate real samples
        curve->real_samples = new QwtPlotCurve(channel.second->getName() + QString(" (Re)"));
        curve->real_samples->setRawSamples(RadarBurstData.time_samples, RadarBurstData.imag_samples, samples);

        reader->release(buffer);
    }

    if (drop_burst)
    {
        for (auto curve_pair : *m_plot_curves) {
            sRadarBurstCurves_t *curve = curve_pair.second;
            if (curve->real_samples)  delete curve->real_samples;
            if (curve->imag_samples)  delete curve->imag_samples;
            if (curve->ampl_samples)  delete curve->ampl_samples;
            if (curve->phase_samples) delete curve->phase_samples;
            delete curve;
        }
        delete m_plot_curves;
    }
    else {
        emit resultReady(m_plot_curves);
        index ++;
    }

    QTimer::singleShot(0, this, &RadarBurstDataConsumer::doDataConsume);
}

}

