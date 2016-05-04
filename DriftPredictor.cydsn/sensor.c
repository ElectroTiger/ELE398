/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "bme280.h"
#include "sensor.h"
#include "stdlib.h"
#include "bme280api.h"

/*Sensor objects which there may only be one of. */
static struct bme280_t bme280; // Temp, Pres, Altitude, Humidity.

struct Sensor {
    float humidity;
    float temp;
    float pressure;
    float xVel;
    float yVel;
    float altitude;
};

Sensor_T Sensor_Start() {
    Sensor_T oSensor = malloc(sizeof(struct Sensor));
    bme280api_Start(bme280);
    
    return oSensor;
}

void Sensor_Acquire(Sensor_T oSensor) {
    /* Acquire information from the BME280. */
    u32 uiPres;
    s32 iTemp;
    u32 uiHumi;
    bme280_read_pressure_temperature_humidity(&uiPres, &iTemp, &uiHumi);
    oSensor->pressure = (float) uiPres;
    oSensor->temp = (float) iTemp;
    oSensor->humidity = (float) uiHumi;

}

/* [] END OF FILE */
