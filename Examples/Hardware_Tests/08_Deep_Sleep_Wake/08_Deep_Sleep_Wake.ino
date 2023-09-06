// SparkFun DataLogger IoT Test Example
// Tested with Espressif ESP32 v2.0.5 and the "ESP32 Dev Module" board definition

/**********************************************************************************************
 *
 * WARNING!
 * 
 * This is a sketch we wrote to test the DataLogger IoT hardware.
 * Please think very carefully before uploading it to your DataLogger.
 * 
 * You will overwrite the DataLogger firmware, leaving it unable to update or restore itself. 
 * 
 * The DataLogger IoT comes pre-programmed with amazing firmware which can do _so_ much.
 * It is designed to be able to update itself and restore itself if necessary.
 * But it can not do that if you overwrite the firmware with this test sketch.
 * It is just like erasing the restore partition on your computer hard drive.
 * Do not do it - unless you really know what you are doing.
 * 
 * Really. We mean it.
 * 
 * Your friends at SparkFun.
 * 
 * License: MIT. Please see LICENSE.MD for more details
 * 
 **********************************************************************************************/

// 240MHz (WiFi/BT)
// Flash: 80MHz QIO 4MB "Default 4MB with SPIFFS"
// Core Debug: None
// PSRAM: Disabled
// Arduino Runs On: Core 1
// Events Run On: Core 1

// Deep Sleep Current Draw:
// DataLogger IoT is powered from an Otii Arc: https://www.sparkfun.com/products/18585
// Otii Arc is injecting power into the Li-Po connector. Voltage is set to 4.2V to mimic Li-Po
// After code upload, the USB-C cable is disconnected to avoid having the CH340 powered on
// Deep Sleep Current Draw is measured by the Otii Arc using Auto-Range
// Otii Arc is powered by a 9V wall wart and is calibrated before use

// Sleep current should be in the region of 200uA

#define STAT_LED 25 // DataLogger IoT STAT LED is connected to D25

#include "esp_sleep.h"

void setup()
{
  pinMode(STAT_LED, OUTPUT); digitalWrite(STAT_LED, HIGH); // Turn the STAT LED on

  esp_sleep_config_gpio_isolate();

  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC8M, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_VDDSDIO, ESP_PD_OPTION_OFF);

  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Deep Sleep

  //digitalWrite(STAT_LED, LOW); // Turn the STAT LED off. Redundant since the pin is isolated during sleep.

  esp_sleep_enable_timer_wakeup(5000000ULL); // Sleep for 5 seconds - this will undo some of the pd_config settings

  esp_deep_sleep_start();
}

void loop()
{
  // Nothing to do here
}
