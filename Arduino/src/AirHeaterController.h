#ifndef IOT1_AIR_HEATER_CONTROLLER_H
#define IOT1_AIR_HEATER_CONTROLLER_H

#include <Arduino.h>

double mapd(double x, double in_min, double in_max, double out_min, double out_max);

class AirHeaterController {
private:
    int temp_pin;

    double error = 0;
    double u = 0;
    double Ts = 0.1;
    double Tout;

    // PI controller parameters
    double Kp = 0.8;
    double Ti = 20;
    double setPoint;

    // Air heater model parameters
    double Kh = 3.5;
    double theta_t = 22;
    double Tenv = 21.5;

    // Low pass filter parameters
    double Tf = 5 * Ts;
    double a = Ts / (Tf + Ts);
    double yf_prev = 0;

    bool simulateAirHeater;
public:
    AirHeaterController(int temp_pin, double Tinit, double setPoint, bool simulateAirHeater);

    void tick();

    void UpdatePI_BackwardEuler();

    double AirHeaterModel();

    double LowPassFilter(double y);

    double readTemperatureTMP36() const;

    double readTemperature() const;

    double getTout() const {
        return Tout;
    }

    double getTs() const {
        return Ts;
    }

    bool isSimulated() const {
        return simulateAirHeater;
    }

    double getU() const {
        return u;
    }

};

#endif //IOT1_AIR_HEATER_CONTROLLER_H
