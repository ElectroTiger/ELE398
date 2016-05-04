/* GPS.h
Header file to interface with the MTK3339 GPS. 
*/
#include <string.h>
#include "system_interface.h"
#ifndef __GPS_HEADER__
    #define __GPS_HEADER__
    
    /* Start the GPS subroutine for the PSoC. */
    void GPS_Start();
    
    /* Parse a single character ch from the UART. */
    void GPS_Parse(char ch);
    
    int16_t hello;
    
    /* Return the current hour 24 hour format. */
    uint16_t GPS_GetHour();
    /* Return the current minute */
    uint16_t GPS_GetMinute();
    /* Return the current second of the time. */
    float GPS_GetSecond();
    /* Return the current time in HH:MM:SS format. */
    void GPS_GetTime(char* cpTimeString, uint8 len);
    
    /* Return the last two digits of the current year */
    uint8_t GPS_GetYear();
    /* Return the current month as a number. */
    uint8_t GPS_GetMonth();
    /* Return the current day as a number. */
    uint16_t GPS_GetDay();
    /* Return the current date in DD-MM-YY format. */
    void GPS_GetDate(char* cpDateString, uint8 len);
    
    /* Return the latitude degree. */
    uint16_t GPS_GetLatDegree();
    /* Return the latitude minute. */
    float GPS_GetLatMinute();
    /* Return whether system is North. */
    _Bool GPS_GetIsNorth();
    /* Return latitude string in geocode format "DDD MM.MMM". */
    void GPS_GetLat(char* cpLatString, uint8 len);
    
    /* Return the longitudinal degree. */
    uint16_t GPS_GetLongDegree();
    /* Return the longitudinal minute. */
    float GPS_GetLongMinute();
    /* Return whether system is East. */
    _Bool GPS_GetIsEast();
    /* Get longitude string in geocode format "DDD MM.MMM". */
    void GPS_GetLong(char* cpLongString, uint8_t len);
    
    /* Return the speed in knots. */
    float GPS_GetSpeed();
    /* Return the current heading in compass degrees. */
    float GPS_GetHeading();
    /* Get a string containing the current speed and heading. */
    void GPS_GetCourse(char* cpCourseString, uint8_t len);
    
    #endif
    

/* [] END OF FILE */
