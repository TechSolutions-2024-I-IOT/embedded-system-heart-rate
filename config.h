#ifndef CONFIG_H
#define CONFIG_H

// WiFi configuration
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// ThingSpeak configuration
#define MY_CHANNEL 2566527 
#define API_KEY "EOVRV2RJBUZBX6TU"

// Backend URL
#define EDGE_BACKEND_URL "https://taskedgelayerservice.azurewebsites.net/api/v1/sensor-data"

// Pin definitions
#define PULSE_PIN 35
#define LED_PIN 13

// I2C pins
#define SDA_PIN 23
#define SCL_PIN 22

// Pulse simulation parameters
#define SIMULATION_UPDATE_INTERVAL 500 // ms

// Heart rate thresholds
#define MIN_HEART_RATE 60
#define MAX_HEART_RATE 140

// ADC to voltage conversion
#define ADC_MAX 4095
#define VOLTAGE_MAX 5.0

#endif // CONFIG_H