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
#include <project.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "MLX90316.h"
#include "GPS.h"
#include "USBPrint.h"
#include "bme280.h"
#include "bme280api.h"
#include "anemometer.h"
#include "driftPredictor.h"

#define M_PI 3.14159265358979323846
/* Selective subsystem enable helps with debugging. */
#define ENABLE_MLX90316
#define ENABLE_BME280
#define ENABLE_ANEMOMETER
#define ENABLE_GPS
#define ENABLE_USB
#define ENABLE_DRIFTPREDICTION

int main() {
    CyGlobalIntEnable; /* Enable global interrupts. */
    
//    GPS_Start();
    /* Start PSoC Firmware. */
    ILO_Trim_Start();
#ifdef ENABLE_MLX90316
    MLX90316_Start(); // Start the magnetic rotary position sensor subsystem.
#endif
#ifdef ENABLE_BME280
    BME280_Start(); // Start the BME280 subsystem.
#endif
#ifdef ENABLE_ANEMOMETER
    Anemometer_Start();
    // Start the Anemometer subsystem.
#endif
#ifdef ENABLE_GPS
    GPS_Start(); // Start the GPS subsystem.
#endif

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;) {
        /* Read and print the BME280 values. */
#ifdef ENABLE_BME280
        double humidity; // Relative humidity in percentage. 
        double temperature; // The temperature is in C.
        double pressure; // The pressure is Pascals. 
        BME280_Read(&temperature, &pressure, &humidity);
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Temperature (C): %f", temperature);
        USBPrint_PrintBuffer();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Pressure (Pa): %f", pressure);
        USBPrint_PrintBuffer();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Humidity (%%RH): %f", humidity);
        USBPrint_PrintBuffer();
#endif
        
        /* Read and print the wind angle. */
#ifdef ENABLE_MLX90316
        double windAngle = MLX90316_ReadAngle();        
        if (!isnan(windAngle)) {
            snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Wind Angle (Deg): %f", windAngle);
            USBPrint_PrintBuffer();
        }
        else { 
            MLX90316_GetError(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
            USBPrint_PrintBuffer();
        }
#endif
        
        /* Read and print the wind speed. */
#ifdef ENABLE_ANEMOMETER
        double windSpeed = Anemometer_GetSpeed();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Wind Speed (m/s); %f", windSpeed);
        USBPrint_PrintBuffer();
#endif
        
        /* Read and print the GPS data. */
#ifdef ENABLE_GPS
        GPS_GetCourse(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
        USBPrint_PrintBuffer();
#endif
        
        /* Perform the calculations to calculate the drift. */
#ifdef ENABLE_DRIFTPREDICTION
    	    /* Set other droplet size parameters
         * Arguments:
         * diameter: Droplet diameter in mm
         * dragCoeff: The drag coefficient
         * */
        /* Assume droplet diameter is 1mm;
         * spherical droplet has 0.5 drag coefficient;
         * water has ideal density of 1 g/cm^3 */
        setParams(1, 0.5, 1);

    	/* Set the initial position of the particle in meters. */
        /* Assume zero for now, as we operate on a stationary platform.
         * Future work would use the GPS coordinates.
         */
        setx0(0, 0, getAltitude(pressure ,101300));

        /* Set the initial velocity of the particle in meters. */
        setv0(0, 0, 1);

        /* Set the wind velocity condition in meters. */
        setw(windSpeed * cos(windAngle * M_PI / 180.), windSpeed * sin(windAngle * M_PI / 180.), 0);

        /* Set alpha, the constant for the drift equation.
         * Arguments:
         * pressure: Pressure in Pascals
         * temperature: Temperature in Celsius
         * humidity: Relative humidity*/
        setAlpha(pressure, temperature, humidity);


        /* Calculate the current drift. */
        double fallTime; // Fall time in seconds.
        double xPos; // Final x-position in meters.
        double yPos; // Final y-position in meters.
        getDrift (&fallTime, &xPos, &yPos);
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Fall Time: %f\n xPos: %f\n yPos: %f\n", fallTime, xPos, yPos);
#endif
     
    }
}

/* [] END OF FILE */
