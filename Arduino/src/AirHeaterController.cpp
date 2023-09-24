#include "AirHeaterController.h"

AirHeaterController::AirHeaterController(int temp_pin, double Tinit, double setPoint, bool simulateAirHeater) : temp_pin(temp_pin), Tout(Tinit), setPoint(setPoint), simulateAirHeater(simulateAirHeater) {}

void AirHeaterController::tick() {
    this->UpdatePI_BackwardEuler();
    double newTout;
    if (simulateAirHeater)
        newTout = this->AirHeaterModel();
    else
        newTout = this->readTemperatureTMP36();
    Tout = this->LowPassFilter(newTout);
}

void AirHeaterController::UpdatePI_BackwardEuler() {
    double prevError = error;
    error = setPoint - Tout;
    u = u + Kp * (error - prevError) + (Kp * Ts / Ti) * error;
    u = constrain(u, 0, 5);
}

double AirHeaterController::AirHeaterModel() {
    double prevTout = Tout;
    Tout = prevTout + (Ts / theta_t) * (-prevTout + Kh * u + Tenv);
    return Tout;
}

double AirHeaterController::LowPassFilter(double y) {
    double yf = (1-a) * yf_prev + a*y;
    yf_prev = yf;
    return yf;
}

double AirHeaterController::readTemperatureTMP36() const {
    double temp = analogRead(temp_pin); // read the input pin
    temp = temp * 5.0 / 1023.0; // convert to voltage with 5.0V as reference
    temp = temp - 0.5; // subtract the offset
    temp = temp * 100; // convert to degrees
    return temp;
}

double AirHeaterController::readTemperature() const {
    double temp = analogRead(temp_pin); // read the input pin
    temp = temp * 5.0 / 1023.0; // convert to voltage with 5.0V as reference
    temp = mapd(temp, 1, 5, 0, 50);
    return temp;
}

double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
