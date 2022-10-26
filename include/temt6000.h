#ifndef TEMT6000_H
#define TEMT6000_H

#include <stdbool.h>
#include <stdint.h>

#include "driver/adc.h"
#include "esp_adc_cal.h"

typedef enum TEMT6000_powersupply_t TEMT6000_powersupply_t;
typedef struct TEMT6000_t           TEMT6000_t;

typedef float                       TEMT6000_intensity_t;
typedef float                       TEMT6000_illuminance_t;

struct TEMT6000_t
{
    esp_adc_cal_characteristics_t adcChars;
    adc_channel_t channel;
};

bool temt6000__Init(TEMT6000_t *device, adc_unit_t unit, adc1_channel_t channel);
bool temt6000__ReadIlluminance(TEMT6000_t *device, uint32_t samplesNo, TEMT6000_illuminance_t *illuminanceOut);
bool temt6000__ReadLightIntensity(TEMT6000_t *device, uint32_t samplesNo, TEMT6000_intensity_t *intensityOut);

TEMT6000_intensity_t temt6000__IlluminanceToLightIntensity(TEMT6000_illuminance_t illuminance);

#endif /* TEMT6000_H */
