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
//#define ENABLE_USB
#define ENABLE_DRIFTPREDICTION

int main() {
    CyGlobalIntEnable; /* Enable global interrupts. */
    
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
#ifdef ENABLE_USB
    USBPrint_Start();
    #define USBPRINT_PRINTBUFFER() (USBPRINT_PRINTBUFFER())
    #else
        #define USBPRINT_PRINTBUFFER()
#endif

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;) {
        /* Read and print the BME280 values. */
#ifdef ENABLE_BME280
        double humidity; // Relative humidity in percentage. 
        double temperature; // The temperature is in C.
        double pressure; // The pressure is Pascals. 
        double groundPressure; // The pressure when the button was pressed.
        double altitude; // The current altitude in meters.
        BME280_Read(&temperature, &pressure, &humidity);
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Temperature (C): %f\n", temperature);
        USBPRINT_PRINTBUFFER();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Pressure (Pa): %f\n", pressure);
        USBPRINT_PRINTBUFFER();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Humidity (%%RH): %f\n", humidity);
        USBPRINT_PRINTBUFFER();
        groundPressure = BME280_GetGroundPressure();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Ground Pressure (Pa): %f\n", groundPressure);
        USBPRINT_PRINTBUFFER();
        altitude = BME280_GetAltitude();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Altitude (m): %f\n", altitude);
        USBPRINT_PRINTBUFFER();
#endif
        
        /* Read and print the wind angle. */
#ifdef ENABLE_MLX90316
        double windAngle = MLX90316_ReadAngle();        
        if (!isnan(windAngle)) {
            snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Wind Angle (Deg): %f\n", windAngle);
            USBPRINT_PRINTBUFFER();
        }
        else { 
            MLX90316_GetError(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
            USBPRINT_PRINTBUFFER();
        }
#endif
        
        /* Read and print the wind speed. */
#ifdef ENABLE_ANEMOMETER
        double windSpeed = Anemometer_GetSpeed();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Wind Speed (m/s); %f\n", windSpeed);
        USBPRINT_PRINTBUFFER();
#endif
        
        /* Read and print the GPS data. */
#ifdef ENABLE_GPS
        GPS_GetDate(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
        USBPRINT_PRINTBUFFER();
        GPS_GetLat(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
        USBPRINT_PRINTBUFFER();
        GPS_GetLong(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
        USBPRINT_PRINTBUFFER();
        GPS_GetCourse(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
        USBPRINT_PRINTBUFFER();
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
        setx0(0, 0, altitude);

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
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "\n");
        CyDelay(10);
    }
}

/* [] END OF FILE */
