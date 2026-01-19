#ifndef ENVIRONMENTGUARD_H
#define ENVIRONMENTGUARD_H

#include "mbed.h"

class EnvironmentGuard {
private:
    I2C* i2c;                   // Pointer to I2C interface
    const int LM75B_ADDRESS = 0x48 << 1;  // 7-bit address shifted left (0x90 for write)

public:
    /**
     * Constructor - initializes the LM75B temperature sensor
     * @param sda I2C SDA pin
     * @param scl I2C SCL pin
     * @param frequency I2C bus frequency (default 100kHz)
     */
    EnvironmentGuard(PinName sda, PinName scl, int frequency = 100000);

    /**
     * Read the current temperature from the LM75B sensor
     * @return Temperature in degrees Celsius (float)
     *         Returns -999.0 in case of communication error
     */
    float readTemperatureLM75B();

    /**
     * Check if current temperature exceeds the given threshold
     * @param threshold Temperature threshold in °C
     * @return true if temperature > threshold, false otherwise
     */
    bool isTemperatureAbove(float threshold);

    // Optional: destructor if needed
    ~EnvironmentGuard();
};

#endif // ENVIRONMENTGUARD_H
