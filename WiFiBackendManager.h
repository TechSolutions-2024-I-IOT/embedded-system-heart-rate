#ifndef WIFI_BACKEND_MANAGER_H
#define WIFI_BACKEND_MANAGER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

class WiFiBackendManager {
  private:
    HTTPClient client_http;
    const char* ssid;
    const char* password;
    const char* backendUrl;

  public:
    WiFiBackendManager();
    void connectWifi();
    void sendHeartRateData(int heartRate);
    bool isConnected();
};

#endif