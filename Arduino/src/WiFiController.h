#ifndef IOT1_WIFICONTROLLER_H
#define IOT1_WIFICONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

class WiFiController {
private:
    const char *ssid;
    const char *password;
    const char *thingspeak_key;

    WiFiClient client;
public:
    WiFiController(const char *ssid, const char *password, const char *thingspeak_key);

    void connect();

    static void CheckWiFi();

    void ThingSpeakWrite(double value);
};
#endif //IOT1_WIFICONTROLLER_H
