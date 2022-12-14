/*
 * MIT License
 *
 * Copyright (c) 2022 Damian Ślusarczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
/**
 * @file temt6000.h
 * @author Damian Ślusarczyk
 * @brief Contains functions to communicate with TEMT6000 using ADC.
 * 
 */
#ifndef TEMT6000_H
#define TEMT6000_H

#include <stdint.h>

#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "temt6000_error_codes.h"
#include "temt6000_types_res.h"

typedef struct TEMT6000_t           TEMT6000_t;

/**
 * @brief Describes characteristics of single TEMT6000.
 * 
 * @note Call temt6000__Init() method to initialize this structure.
 */
struct TEMT6000_t
{
    esp_adc_cal_characteristics_t   adcCharacteristics; /**< Characteristics of selected ADC unit */
    adc_channel_t                   channel;            /**< Selected ADC channel */
};

/**
 * @brief Initializes TEMT6000 device instance with given ADC characteristics.
 * 
 * Prepares ADC unit to measure voltage output generated by the connected device.
 * 
 * @param device Pointer to TEMT6000 characteristics instance to initialize
 * @param unit ADC unit selected for measuring output from TEMT6000
 * @param channel ADC channel selected for measuring output from TEMT6000
 * @return TEMT6000_error_t Status code of the operation
 */
TEMT6000_error_t temt6000__Init(TEMT6000_t * const device, const adc_unit_t unit, const adc_channel_t channel);

/**
 * @brief Reads measured illuminance (lux) by selected TEMT6000.
 * 
 * Converts voltage output from the connected device into human-readable value.
 * Convertion is based on specified number of samples - then the average of the measurement results is calculated.
 * 
 * @param device Pointer to TEMT6000 characteristics instance
 * @param samplesNo Number of measurement samples
 * @param illuminanceOut Pointer to variable where measured illuminance will be saved eventually
 * @return TEMT6000_error_t Status code of the operation
 */
TEMT6000_error_t temt6000__ReadIlluminance(const TEMT6000_t * const device, const uint32_t samplesNo, TEMT6000_illuminance_t * const illuminanceOut);

/**
 * @brief Reads measured light intensity (%) by selected TEMT6000.
 * 
 * Converts voltage output from the connected device into human-readable value.
 * Convertion is based on specified number of samples - then the average of the measurement results is calculated.
 * 
 * @param device Pointer to TEMT6000 characteristics instance
 * @param samplesNo Number of measurement samples
 * @param intensityOut Pointer to variable where measured light intensity will be saved eventually
 * @return TEMT6000_error_t Status code of the operation
 */
TEMT6000_error_t temt6000__ReadLightIntensity(const TEMT6000_t * const device, const uint32_t samplesNo, TEMT6000_intensity_t * const intensityOut);

/**
 * @brief Converts specified illuminance to light intensity.
 * 
 * @param illuminance Specified illuminance (lux)
 * @return TEMT6000_intensity_t Result of the convertion - light intensity (%)
 */
TEMT6000_intensity_t temt6000__IlluminanceToLightIntensity(const TEMT6000_illuminance_t illuminance);

#endif /* TEMT6000_H */
