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

int main() {
    CyGlobalIntEnable; /* Enable global interrupts. */
    
//    GPS_Start();
    /* Start PSoC Firmware. */
    ILO_Trim_Start();
    MLX90316_Start(); // Start the magnetic rotary position sensor subsystem.
    BME280_Start(); // Start the BME280 subsystem.
    Anemometer_Start(); // Start the Anenometer subsystem. 
    GPS_Start(); // Start the GPS subsystem. 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;) {
        /* Read and print the BME280 values. */
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
        
        /* Read and print the wind angle. */
        double windAngle = MLX90316_ReadAngle();        
        if (!isnan(windAngle)) {
            snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Wind Angle (Deg): %f", windAngle);
            USBPrint_PrintBuffer();
        }
        else { 
            MLX90316_GetError(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
            USBPrint_PrintBuffer();
        }
        
        /* Read and print the wind speed. */
        double windSpeed = Anemometer_GetSpeed();
        snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "Wind Speed (m/s); %f", windSpeed);
        USBPrint_PrintBuffer();
        
        /* Read and print the GPS data. */
        GPS_GetCourse(USBPrintBuffer, USBPRINT_BUFFER_SIZE);
        USBPrint_PrintBuffer();
    }
}

/* [] END OF FILE */
