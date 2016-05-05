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
#include <stdio.h>
#include "MLX90316.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    MLX90316_Start(); // Start the SPIM Module
    LCD_Stop();
    LCD_Init();
    LCD_Start();
    LCD_ClearDisplay();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        char LCDBuffer[17];
        double angle = MLX90316_ReadAngle();
        int16 angleInt = (int) angle;
        //sprintf(LCDBuffer, "Angle: %d\n", angleInt);
         LCD_Position(0,0);
         LCD_ClearDisplay();
         LCD_IsReady();
         LCD_PrintNumber(angleInt);
        //LCD_PrintString(LCDBuffer);
         CyDelay(1000);
        
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
