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
#include "anemometer.h"

#define TIMER_CLOCK_FREQUENCY_HZ 10000
#define TIMEPERIODTOMPH 1.492
#define MPH2MS 0.44704

static double currentSpeed;

CY_ISR(Anemometer_Inter_Vector) {
    uint16 clockPeriod = Timer_Anemometer_ReadCapture();
    double clockTimePeriod = ((double) clockPeriod) / TIMER_CLOCK_FREQUENCY_HZ;
    currentSpeed = clockTimePeriod * TIMEPERIODTOMPH * TIMER_CLOCK_FREQUENCY_HZ;
    
    
}

/* Start the Anenometer subsystem. */
void Anemometer_Start() {
    Timer_Anemometer_Start();
    Anemometer_Inter_StartEx(Anemometer_Inter_Vector);
}

/* Read the wind speed in m/s from the anenomometer. */
double Anemometer_GetSpeed() {
    return currentSpeed;
}

/* [] END OF FILE */
