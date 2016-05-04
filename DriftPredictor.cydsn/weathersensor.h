/* weathersensor.h
Header for code that interfaces with the Adafruit 80422 weather sensor system.
*/

#ifndef __WEATHERSENSOR__
    #define __WEATHERSENSOR__
    #include "project.h"
    
    /* Macro Definitions */
    /* The number of ticks per second that occur with a 1 mph wind. */
    #define MPH_PER_TICK 1.492
    /* Conversion from mph to m/s. */
    #define MPH2MS 0.44704
    /* Angle adjustment from raw wind speed reading. */
    
    /* Functions */
    /* Start the weather sensor subsystem. */
    void weathersensor_Start();
    
    /* Read the wind speed in m/s. */
    float weathersensor_GetWindSpeed();
    
    /* Read the wind direction in degrees. */
    float weathersensor_GetWindDirection();
    
#endif



/* [] END OF FILE */
