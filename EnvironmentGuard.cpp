#include "mbed.h"
#include "EnvironmentGuard.h"

EnvironmentGuard::EnvironmentGuard(PinName sda, PinName scl, int frequency) {
    i2c = new I2C(sda, scl);
    i2c->frequency(frequency);
}

EnvironmentGuard::~EnvironmentGuard() {
    delete i2c;
}

float EnvironmentGuard::readTemperatureLM75B() {
    char cmd[1] = {0x00};           // Temperature register
    char data[2];

    // Write register address
    if (i2c->write(LM75B_ADDRESS, cmd, 1) != 0) {
        return -999.0f;             // Error
    }

    // Read 2 bytes
    if (i2c->read(LM75B_ADDRESS | 0x01, data, 2) != 0) {
        return -999.0f;             // Error
    }

    // Combine bytes and convert (9-bit signed value)
    int16_t raw = (data[0] << 8) | data[1];
    raw >>= 7;                      // Shift right 7 bits (0.5°C resolution)

    return static_cast<float>(raw) * 0.5f;
}

bool EnvironmentGuard::isTemperatureAbove(float threshold) {
    float temp = readTemperatureLM75B();
    
    // Check for valid reading
    if (temp <= -998.0f) {
        return false;               // Communication error → consider not exceeded
    }
    
    return (temp > threshold);
}
