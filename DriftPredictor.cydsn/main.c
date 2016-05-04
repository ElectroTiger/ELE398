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
#include "GPS.h"
#include "bme280.h"
#include "bme280api.h"
#define USB_DEVICE_NUM (0u)

#define USBUART_BUFFER_SIZE (64u)
#define LINE_STR_LENGTH     (20u)

#define KNOTS2METERS 0.514444

/* Subroutine to handle sending serial data to the USB. */
static void HandleUSB() {
    const int iLen = 64;
    char buffer[iLen];
    GPS_GetTime(buffer, iLen);
    USB_PutString(buffer);
}


int main() {
    struct bme280_t bme280;
    CyGlobalIntEnable; /* Enable global interrupts. */
    USB_Start(USB_DEVICE_NUM, USB_5V_OPERATION);
//    GPS_Start();
    bme280_init(&bme280);
    bme280api_Start(bme280);
    
    const int iLen = 64;
    char USBBuffer[iLen];
    
    uint16 count;
    uint8 buffer[USBUART_BUFFER_SIZE];
    uint8 state;

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
//        float speed;
//        float heading;
//        float humidity;
//        float temperature;
//        float pressure;
//        float altitude;
//        float wind_speed;
//        float wind_direction;
//        
//        speed = GPS_GetSpeed() * KNOTS2METERS;
//        heading = GPS_GetHeading();
            uint32_t iHum;
            uint32_t iPres;
            int32_t iTemp;
            bme280_read_pressure_temperature_humidity(&iPres, &iTemp, &iHum);
//            humidity = iHum / 1024.;
//            pressure = iPres / 256.;
//            temperature = iTemp / 1000;
        
        /* Initialize the system once the USB line is valid. */
        if(0u != USB_IsConfigurationChanged()) {
            if (0u != USB_GetConfiguration()) {
                USB_CDC_Init();
            }
        }
        
        /* Service the device once the USB is configured. */
        if(USB_GetConfiguration() !=0) {
            count = USB_GetAll(buffer); // Grab the data, but do nothing with it. 
            while(!USB_CDCIsReady());
            USB_PutString("Hello, World");
            snprintf("Humidity: %d\nPressure: %d\n Temperature: %d\n", iLen, USBBuffer, iHum, iPres, iTemp);
            USB_PutString(USBBuffer);
            CyDelay(1000);
            if (count == USBUART_BUFFER_SIZE) {
                while (!USB_CDCIsReady());
                USB_PutData(NULL, 0u);
            }
        }
        
        state = USB_IsLineChanged();
        if (state != 0) {
            
        }
        
        // HandleUSB();

    }
}

/* [] END OF FILE */
