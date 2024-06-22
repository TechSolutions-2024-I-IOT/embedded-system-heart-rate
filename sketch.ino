#include <Wire.h> 
#include <Arduino.h>
#include <ThingSpeak.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "PulseSimulator.h"
#include "config.h"

// HTTP Client
HTTPClient client_http;

// WiFi Client
WiFiClient client_wifi;

// Pulse Simulator
PulseSimulator pulseSimulator;

// Function Prototypes
void connectWifi();
void sendThingSpeak(int heartRate);
int calculateHeartRate(float voltage);
void controlLed(int heartRate);
void connectEdgeBackend();
void sendToBackend(int heartRate);

void setup() {
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Hello, ESP32!");
    connectWifi();
    ThingSpeak.begin(client_wifi);
    connectEdgeBackend();
    pulseSimulator.begin(PULSE_PIN);
}

void loop() {
    float voltage = pulseSimulator.readVoltage();
    int heartRate = calculateHeartRate(voltage);

    Serial.print("\nHeart Rate: ");
    Serial.println(heartRate);
    
    sendToBackend(heartRate);
    //sendThingSpeak(heartRate);
    controlLed(heartRate);
    
    delay(500);
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

int calculateHeartRate(float voltage) {
    return (voltage / 3.3) * 675;
}

void controlLed(int heartRate) {
    if (heartRate < MIN_HEART_RATE || heartRate > MAX_HEART_RATE) {
        digitalWrite(LED_PIN, HIGH);
        // Here send the notification to the backend
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}

void connectEdgeBackend() {
    client_http.begin(EDGE_BACKEND_URL);
    client_http.addHeader("Content-Type", "application/json");
}

void sendToBackend(int heartRate) {
    String jsonData = "{\"pulse\":\"" + String(heartRate) + "\"}";
    int httpCode = client_http.POST(jsonData);
    if (httpCode > 0) {
        Serial.printf("HTTP Response code: %d\n", httpCode);
    } else {
        Serial.printf("HTTP Request failed: %s\n", client_http.errorToString(httpCode).c_str());
    }
}