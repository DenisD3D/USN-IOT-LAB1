#include "WiFiController.h"

WiFiController::WiFiController(const char *ssid, const char *password, const char *thingspeak_key) : ssid(ssid), password(password), thingspeak_key(thingspeak_key) {}

void WiFiController::CheckWiFi() {
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        while (true);
    }

    String fv = WiFiClass::firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
    }
}

void WiFiController::connect() {
    CheckWiFi();

    if (WiFi.status() == WL_CONNECTED) return;

    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    client.connect("api.thingspeak.com", 80);
    Serial.println("Connected to server.");
}

void WiFiController::ThingSpeakWrite(double value) {
    client.print("GET /update?api_key=");
    client.print(thingspeak_key);
    client.print("&field1=");
    client.print(value);
    client.println("HTTP/1.0");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
    Serial.println("Request sent.");
}
