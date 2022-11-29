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
 * @file temt6000_types_res.h
 * @author Damian Ślusarczyk
 * @brief Contains all output types required to communicate with TEMT6000 driver.
 * 
 */
#ifndef TEMT6000_TYPES_RES_H
#define TEMT6000_TYPES_RES_H

/** Light intensity measured by the device */
typedef float                               TEMT6000_intensity_t;
/** Illuminance measured by the device */
typedef float                               TEMT6000_illuminance_t;

typedef struct TEMT6000_measurement_data_t  TEMT6000_measurement_data_t;

/**
 * @brief Contains all measurement data from TEMT6000. 
 * 
 */
struct TEMT6000_measurement_data_t
{
    TEMT6000_intensity_t    lightIntensity;
    TEMT6000_illuminance_t  illuminance;
};

#endif /* TEMT6000_TYPES_RES_H */
