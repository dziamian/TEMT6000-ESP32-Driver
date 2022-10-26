#include "temt6000.h"

#define TEMT6000_ADC_WIDTH                          ADC_WIDTH_BIT_12

#define TEMT6000_ADC_ATTEN                          ADC_ATTEN_DB_11
#define TEMT6000_ADC_ATTEN_VREF                     3900

#define TEMT6000_PERCENTAGE_CONVERTER_VALUE         100.f
#define TEMT6000_INTENSITY_CONVERTER_VALUE          0.2f
#define TEMT6000_ILLUMINANCE_CONVERTER_VALUE        1000.f

#define TEMT6000_ADC_ZERO                           0

#define TEMT6000_ADC_MARGIN_LOW_MV                  142

bool temt6000__Init(TEMT6000_t *device, adc_unit_t unit, adc1_channel_t channel)
{
    if (!device)
    {
        return false;
    }

    if (ADC_UNIT_1 == unit)
    {
        if (ESP_OK != adc1_config_width(TEMT6000_ADC_WIDTH))
        {
            return false;
        }
        if (ESP_OK != adc1_config_channel_atten((adc1_channel_t) channel, TEMT6000_ADC_ATTEN))
        {
            return false;
        }
    }
    else
    {
        if (ESP_OK != adc2_config_channel_atten((adc2_channel_t) channel, TEMT6000_ADC_ATTEN))
        {
            return false;
        }
    }

    esp_adc_cal_characterize(unit, TEMT6000_ADC_ATTEN, TEMT6000_ADC_WIDTH, TEMT6000_ADC_ATTEN_VREF, &device->adcChars);
    device->channel = channel;

    return true;
}

bool temt6000__ReadIlluminance(TEMT6000_t *device, uint32_t samplesNo, TEMT6000_illuminance_t *illuminanceOut)
{
    if (!device || !illuminanceOut)
    {
        return false;
    }

    int allAdcRaws = 0;
    int adcRaw = 0;
    for (uint32_t i = 0; i < samplesNo; ++i)
    {
        if (ADC_UNIT_1 == device->adcChars.adc_num)
        {
            adcRaw = adc1_get_raw((adc1_channel_t) device->channel);
        }
        else
        {
            if (ESP_OK != adc2_get_raw((adc2_channel_t) device->channel, TEMT6000_ADC_WIDTH, &adcRaw))
            {
                return false;
            }
        }
        allAdcRaws += adcRaw;
    }
    uint32_t milliVoltage = esp_adc_cal_raw_to_voltage(allAdcRaws / samplesNo, &device->adcChars);
    if (TEMT6000_ADC_MARGIN_LOW_MV >= milliVoltage)
    {
        milliVoltage = 0.f;
    }
    *illuminanceOut = TEMT6000_INTENSITY_CONVERTER_VALUE * milliVoltage;

    return true;
}

bool temt6000__ReadLightIntensity(TEMT6000_t *device, uint32_t samplesNo, TEMT6000_intensity_t *intensityOut)
{
    if (!intensityOut)
    {
        return false;
    }

    TEMT6000_illuminance_t illuminance;
    if (!temt6000__ReadIlluminance(device, samplesNo, &illuminance))
    {
        return false;
    }

    *intensityOut = temt6000__IlluminanceToLightIntensity(illuminance);

    return true;
}

TEMT6000_intensity_t temt6000__IlluminanceToLightIntensity(TEMT6000_illuminance_t illuminance)
{
    return illuminance / TEMT6000_ILLUMINANCE_CONVERTER_VALUE * TEMT6000_PERCENTAGE_CONVERTER_VALUE;
}