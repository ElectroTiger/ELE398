/* Weimen Li:
This is the anemometer subsystem header file for ELE 398. 
*/
#ifndef __ANEMOMETER__
    #define __ANEMOMETER__
    #include <project.h>

/* Start the Anemometer subsystem. */
void Anemometer_Start();

/* Read the wind speed in m/s from the anemomometer. */
double Anemometer_GetSpeed();

#endif

/* [] END OF FILE */
