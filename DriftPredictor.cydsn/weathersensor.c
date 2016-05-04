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

#include "weathersensor.h"

/* Start the weather sensor subsystem. */
void weathersensor_Start() {
    Timer_Anemometer_Start();
}

/* Read the wind speed in m/s. */
float weathersensor_GetWindSpeed() {
}

/* Read the wind direction in degrees. */
float weathersensor_GetWindDirection() {
}

/* [] END OF FILE */
