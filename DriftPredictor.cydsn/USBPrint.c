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
#include "USBPrint.h"

#define USB_DEVICE_NUM (0u)

void USBPrint_Start() {
    USB_Start(USB_DEVICE_NUM, USB_5V_OPERATION);
}

void USBPrint_PrintBuffer() {
    /* Initialize the system once the USB line is valid. */
    if((0u != USB_IsConfigurationChanged()) && (0u != USB_GetConfiguration())) {
        USB_CDC_Init();
    }    
    
    /* Service the device once the USB is configured. */
    if(USB_GetConfiguration() !=0) {
        int count;
        count = USB_GetAll(0); // Grab the data, but do nothing with it. 
        while(!USB_CDCIsReady());
        USB_PutString(USBPrintBuffer);
        if (count == USBPRINT_BUFFER_SIZE) {
            while (!USB_CDCIsReady());
            USB_PutData(NULL, 0u);
        }
    }
}


/* [] END OF FILE */
