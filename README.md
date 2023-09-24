# Internet of Things and Cyber Security
## 	Lab 1 - Internet of Things and Arduino - University of South Eastern Norway

# Arduino
Project is compiled using [PlatformIO](https://platformio.org/). The project is located in the folder "Arduino".
 - main.cpp - Main file
 - secrets.h - Contains the WiFi and ThingSpeak credentials. Rename file "secrets.h.example" to "secrets.h" and fill in the credentials.
 - AirHeaterController.(h/cpp) - Library for controlling the air heater
 - WiFiController.(h/cpp) - Library for connecting to WiFi and uploading to ThingSpeak

# LabView
The LabView project is located in the folder "LabView". The project is tested on LabView 2023.
 - Project simulated.vi - Version without Arduino connected, simulate the Air Heater
 - Project TMP36.vi - Version with Arduino connected, read temperature from TMP36 sensor
 - Project.vi - Version with Arduino connected, read temperature from thermistor sensor and control the Air Heater