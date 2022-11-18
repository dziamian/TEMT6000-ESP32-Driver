#include "temt6000.h"

/** Output range of configured ADC unit */
#define TEMT6000_ADC_WIDTH                          ADC_WIDTH_BIT_12

/** Input range of configured ADC unit */
#define TEMT6000_ADC_ATTEN                          ADC_ATTEN_DB_11
/** Default reference voltage of configured ADC unit */
#define TEMT6000_ADC_ATTEN_VREF                     3900

/** Coefficient used for percentage convertion */
#define TEMT6000_PERCENTAGE_CONVERTER_VALUE         100.f
/** Coefficient used for illuminance convertion from read output in voltage */
#define TEMT6000_ILLUMINANCE_CONVERTER_VALUE        0.2f
/** Coefficient used for light intensity convertion from given illuminance */
#define TEMT6000_INTENSITY_CONVERTER_VALUE          1000.f

/** Specifies the value of lower margin reduction */
#define TEMT6000_ADC_MARGIN_LOW_REDUCED_VALUE       0
/** Specifies lower margin of ADC measurement result (in millivoltages) - value is reduced to TEMT6000_ADC_MARGIN_LOW_REDUCED_VALUE */
#define TEMT6000_ADC_MARGIN_LOW_MV                  142

TEMT6000_error_t temt6000__Init(TEMT6000_t * const device, const adc_unit_t unit, const adc_channel_t channel)
{
    if (!device)
    {
        return TEMT6000_INV_ARG;
    }

    if (ADC_UNIT_1 == unit)
    {
        if (ESP_OK != adc1_config_width(TEMT6000_ADC_WIDTH))
        {
            return TEMT6000_ADC_CONF_FAIL;
        }
        if (ESP_OK != adc1_config_channel_atten((adc1_channel_t) channel, TEMT6000_ADC_ATTEN))
        {
            return TEMT6000_ADC_CONF_FAIL;
        }
    }
    else
    {
        if (ESP_OK != adc2_config_channel_atten((adc2_channel_t) channel, TEMT6000_ADC_ATTEN))
        {
            return TEMT6000_ADC_CONF_FAIL;
        }
    }

    esp_adc_cal_characterize(unit, TEMT6000_ADC_ATTEN, TEMT6000_ADC_WIDTH, TEMT6000_ADC_ATTEN_VREF, &device->adcCharacteristics);
    device->channel = channel;

    return TEMT6000_OK;
}

TEMT6000_error_t temt6000__ReadIlluminance(TEMT6000_t * const device, const uint32_t samplesNo, TEMT6000_illuminance_t * const illuminanceOut)
{
    if (!device || !illuminanceOut)
    {
        return TEMT6000_INV_ARG;
    }

    int allAdcRaws = 0;
    int adcRaw;
    for (uint32_t i = 0; i < samplesNo; ++i)
    {
        if (ADC_UNIT_1 == device->adcCharacteristics.adc_num)
        {
            adcRaw = adc1_get_raw((adc1_channel_t) device->channel);
        }
        else
        {
            if (ESP_OK != adc2_get_raw((adc2_channel_t) device->channel, TEMT6000_ADC_WIDTH, &adcRaw))
            {
                return TEMT6000_ADC_OP_FAIL;
            }
        }
        allAdcRaws += adcRaw;
    }
    uint32_t milliVoltage = esp_adc_cal_raw_to_voltage(allAdcRaws / samplesNo, &device->adcCharacteristics);
    if (TEMT6000_ADC_MARGIN_LOW_MV >= milliVoltage)
    {
        milliVoltage = TEMT6000_ADC_MARGIN_LOW_REDUCED_VALUE;
    }
    *illuminanceOut = TEMT6000_ILLUMINANCE_CONVERTER_VALUE * milliVoltage;

    return TEMT6000_OK;
}

TEMT6000_error_t temt6000__ReadLightIntensity(TEMT6000_t * const device, const uint32_t samplesNo, TEMT6000_intensity_t * const intensityOut)
{
    TEMT6000_error_t status;
    if (!intensityOut)
    {
        return TEMT6000_INV_ARG;
    }

    TEMT6000_illuminance_t illuminance;
    status = temt6000__ReadIlluminance(device, samplesNo, &illuminance);
    if (TEMT6000_OK != status)
    {
        return status;
    }

    *intensityOut = temt6000__IlluminanceToLightIntensity(illuminance);

    return TEMT6000_OK;
}

TEMT6000_intensity_t temt6000__IlluminanceToLightIntensity(const TEMT6000_illuminance_t illuminance)
{
    return illuminance / TEMT6000_INTENSITY_CONVERTER_VALUE * TEMT6000_PERCENTAGE_CONVERTER_VALUE;
}