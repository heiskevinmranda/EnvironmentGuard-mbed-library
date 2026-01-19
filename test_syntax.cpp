// Test file to check syntax without mbed dependencies
#include <cstdio>
#include <cstdint>

// Mock mbed types and classes
typedef void* PinName;
#define D14 ((PinName)0)
#define D15 ((PinName)1)

class I2C {
private:
    PinName _sda, _scl;

public:
    I2C(PinName sda, PinName scl) : _sda(sda), _scl(scl) {}
    int write(int addr, char* data, int len) { return 0; }
    int read(int addr, char* data, int len) { return 0; }
    void frequency(int freq) {}
};

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

// Implementation
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

int main() {
    printf("Testing EnvironmentGuard syntax...\n");
    
    EnvironmentGuard envGuard(D14, D15);  // SDA, SCL on most FRDM-K64F boards
    
    if (envGuard.isTemperatureAbove(30.0f)) {
        printf("ALERT: Temperature exceeded 30°C!\n");
    } else {
        printf("Temperature is OK.\n");
    }
    
    float temp = envGuard.readTemperatureLM75B();
    printf("Current temperature: %.2f°C\n", temp);
    
    return 0;
}