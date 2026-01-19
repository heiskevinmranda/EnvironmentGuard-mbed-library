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