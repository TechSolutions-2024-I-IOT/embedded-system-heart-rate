#include <Wire.h> 
#include <Arduino.h>
#include <ThingSpeak.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "PulseSimulator.h"

// Pin Definitions
#define PULSE_PIN 35
#define LED_PIN 13

// ThingSpeak Channel Credentials
#define WIFI_SSID "Wokwi-GUEST" 
#define WIFI_PASSWORD ""
#define MY_CHANNEL 2566527 
#define API_KEY "EOVRV2RJBUZBX6TU"

// EdgeBackend
#define EDGE_BACKEND_URL "https://taskedgelayerservice.azurewebsites.net/api/v1/sensor-data"

// HTTP Client
HTTPClient client_http;

// WiFi Client
WiFiClient client_wifi;

// Pulse Simulator
PulseSimulator pulseSimulator;

// Function Prototypes
void connectWifi();
void sendThingSpeak(int heartRate);
int readPulse();
int calculateHeartRate(float voltage);
void controlLed(int heartRate);

void setup() {
    Wire.begin(23, 22);
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Hello, ESP32!");
    connectWifi();
    ThingSpeak.begin(client_wifi); // Connecting with ThingSpeak
    connectEdgeBackend(); // Método POST para enviar datos del sensor
    pulseSimulator.begin(PULSE_PIN); // Initialize Pulse Simulator
}

void loop() {
    // int16_t pulseValue = readPulse();
    // float voltage = pulseValue * (5.0 / 4095.0);
    // int heartRate = calculateHeartRate(voltage);
    
    float voltage = pulseSimulator.readVoltage();
    int heartRate = calculateHeartRate(voltage);

    Serial.print("\nHeart Rate: ");
    Serial.print(heartRate);
    testSendBackend(heartRate);
    
    // client_http.end(); // Liberar los recursos

    //sendThingSpeak(heartRate);
    controlLed(heartRate);
    
    delay(500);
}

void testSendBackend(int heartRate){    
  String jsonData = "{\"pulse\":\"" + String(heartRate) + "\"}";
  int httpCode2 = client_http.POST(jsonData); 
}

void connectEdgeBackend(){
  client_http.begin(EDGE_BACKEND_URL); // Especificar el URL
  client_http.addHeader("Content-Type", "application/json"); // Añadir cabecera para JSON
}

void connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
}

void sendThingSpeak(int heartRate) {
    if (heartRate > 0) {
        ThingSpeak.setField(1, heartRate);                
        ThingSpeak.writeFields(MY_CHANNEL, API_KEY);
    }
}

int readPulse() {
    return analogRead(PULSE_PIN);
}

int calculateHeartRate(float voltage) {
    return (voltage / 3.3) * 675;
}

void controlLed(int heartRate) {
    if (heartRate < 60 || heartRate > 140) {
        digitalWrite(LED_PIN, HIGH);
        // Here send the notification to the backend
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}
