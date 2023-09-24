#include <Arduino.h>

#include "AirHeaterController.h"
#include "WiFiController.h"
#include "secrets.h"
#include "MCP_DAC.h"

#define TEMP_PIN A0
//#define AIR_HEATER_CONTROL_PIN 11  // To control the air heater using the low pass filter
#define AIR_HEATER_SELECT_PIN 10
AirHeaterController controller(TEMP_PIN, 24, 29, true);

WiFiController wifiController(SECRET_SSID, SECRET_PASS, SECRET_THINGSPEAK_API_KEY);
int thingSpeakDelayCounter = 0;

MCP4911 MCP(11, 13);

void setup() {
//    pinMode(AIR_HEATER_CONTROL_PIN, OUTPUT);  // To control the air heater using the low pass filter

    Serial.begin(9600);

    MCP.begin(AIR_HEATER_SELECT_PIN);

    wifiController.connect();
    Serial.println("Connected to WiFi.");

}

void loop() {
    controller.tick();
    if (!controller.isSimulated()) {
//        analogWrite(AIR_HEATER_CONTROL_PIN, (int) (controller.getU() / 5 * 255)); // To control the air heater using the low pass filter
        MCP.analogWrite((int) (controller.getU() / 5 * 1023), 0);
    }

    Serial.println(">u:" + String(controller.getU()));
    Serial.println(">T:" + String(controller.getTout()));

    // Execute ThingSpeak write every 15 seconds
    if (thingSpeakDelayCounter++ % (int) (15 / controller.getTs()) == 0) {
        wifiController.ThingSpeakWrite(controller.getTout());
    }

    delay((long) controller.getTs() * 1000);
}
