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

#ifndef __USBPRINT__
    #define __USBPRINT__

    #define USBPRINT_BUFFER_SIZE (64u)

    char USBPrintBuffer[USBPRINT_BUFFER_SIZE];

    /* Initialize the USB subsystem. */
    void USBPrint_Start();

    /* Print the contents of the USBPrintBuffer. */
    void USBPrint_PrintBuffer();

#endif

/* [] END OF FILE */
