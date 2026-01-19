# EnvironmentGuard mbed Library

Simple library for LM75B temperature sensor with threshold detection for mbed-enabled devices.

## Overview

EnvironmentGuard is a lightweight mbed library designed to interface with the LM75B digital temperature sensor via I2C. It provides easy-to-use functions for reading temperature values and detecting when temperature thresholds are exceeded.

## Features

- Read temperature from LM75B sensor via I2C
- Threshold detection functionality
- Error handling for communication failures
- Simple API for integration into mbed projects

## Hardware Requirements

- mbed-enabled microcontroller board
- LM75B temperature sensor
- I2C connections (SDA and SCL pins)
- Pull-up resistors for I2C lines (usually built into development boards)

## Installation

1. Clone or download this library into your mbed project's `lib` folder
2. Include the header in your code: `#include "EnvironmentGuard.h"`

## Usage

### Basic Example

```cpp
#include "mbed.h"
#include "EnvironmentGuard.h"

// Initialize the EnvironmentGuard with SDA and SCL pins
EnvironmentGuard envGuard(D14, D15);  // Adjust pins as needed for your board

int main() {
    printf("EnvironmentGuard Library Test\n");
    
    while(true) {
        float temperature = envGuard.readTemperatureLM75B();
        
        if (temperature <= -998.0f) {
            printf("Error reading temperature from LM75B\n");
        } else {
            printf("Current temperature: %.2f°C\n", temperature);
            
            if (envGuard.isTemperatureAbove(30.0f)) {
                printf("ALERT: Temperature exceeded 30°C!\n");
            }
        }
        
        wait(1.0); // Wait for 1 second before next reading
    }
}
```

### API Reference

#### Constructor
```cpp
EnvironmentGuard(PinName sda, PinName scl, int frequency = 100000)
```
Initializes the LM75B temperature sensor.

Parameters:
- `sda`: I2C SDA pin
- `scl`: I2C SCL pin
- `frequency`: I2C bus frequency in Hz (default 100kHz)

#### readTemperatureLM75B()
```cpp
float readTemperatureLM75B()
```
Reads the current temperature from the LM75B sensor.

Returns:
- Temperature in degrees Celsius (float)
- Returns -999.0 in case of communication error

#### isTemperatureAbove()
```cpp
bool isTemperatureAbove(float threshold)
```
Checks if current temperature exceeds the given threshold.

Parameters:
- `threshold`: Temperature threshold in °C

Returns:
- `true` if temperature > threshold, `false` otherwise

## Wiring

Connect the LM75B to your mbed board as follows:

| LM75B Pin | mbed Board Pin |
|-----------|----------------|
| VCC       | 3.3V or 5V     |
| GND       | GND            |
| SDA       | SDA pin (e.g., D14) |
| SCL       | SCL pin (e.g., D15) |
| OS/INT    | Not connected (optional) |

## Installation for Community Use

### Using mbed CLI

1. Navigate to your mbed project directory
2. Run the following command to add this library as a dependency:

   ```bash
   mbed add https://github.com/heiskevinmranda/EnvironmentGuard-mbed-library
   ```

### Manual Installation

1. Download the library from: https://github.com/heiskevinmranda/EnvironmentGuard-mbed-library
2. Extract the contents to your project's `lib` folder
3. Rename the extracted folder to `EnvironmentGuard`

## Contributing

Contributions are welcome! Feel free to submit pull requests or open issues on the GitHub repository.

## License

This library is released under the MIT License. See the LICENSE file for more details.

## Author

Kevin Mranda