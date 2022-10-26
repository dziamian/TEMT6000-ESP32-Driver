#include "temt6000_tests.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "temt6000.h"

#define TAG                     "temt6000"

#define TEMT6000_ADC_UNIT       ADC_UNIT_1
#define TEMT6000_ADC_CHANNEL    ADC_CHANNEL_0

#define TEMT6000_SAMPLES_NO     10

#define TEMT6000_TASK_PERIOD_MS 1000

void temt6000_init_test(void)
{
    TEMT6000_t device;
    if (!temt6000__Init(&device, TEMT6000_ADC_UNIT, TEMT6000_ADC_CHANNEL))
    {
        ESP_LOGI(TAG, "Failure while initializing TEMT6000 driver.");
        return;
    }

    ESP_LOGI(TAG, "Successfully initialized TEMT6000 driver.");

    return;
}

void temt6000_reading_test(void)
{
    TEMT6000_t device;
    if (!temt6000__Init(&device, TEMT6000_ADC_UNIT, TEMT6000_ADC_CHANNEL))
    {
        ESP_LOGI(TAG, "Failure while initializing TEMT6000 driver.");
        return;
    }

    while (1)
    {
        TEMT6000_intensity_t lightIntensity;
        if (!temt6000__ReadLightIntensity(&device, TEMT6000_SAMPLES_NO, &lightIntensity))
        {
            ESP_LOGI(TAG, "Failure while reading light intensity...");
        }
        else
        {
            ESP_LOGI(TAG, "Light intensity: %.2f%%", lightIntensity);
        }
        
        TEMT6000_illuminance_t illuminance;
        if (!temt6000__ReadIlluminance(&device, TEMT6000_SAMPLES_NO, &illuminance))
        {
            ESP_LOGI(TAG, "Failure while reading illuminance...");
        }
        else
        {
            ESP_LOGI(TAG, "Illuminance: %.2f lux", illuminance);
        }

        vTaskDelay(pdMS_TO_TICKS(TEMT6000_TASK_PERIOD_MS));
    }

    return;
}