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
#define USB_PRINT

#include <project.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS.h"
#ifdef USB_PRINT
	#include "USBPrint.h"
#endif

    /* Time variables */
    volatile static uint16 hour;
    volatile static uint16 minute;
    volatile static float second;
    
    volatile static uint8 dateYear;
    volatile static uint8 dateMonth;
    volatile static uint16 dateDay;
    
    /* Position Variables */
    volatile static uint16 latDegree;
    volatile static float latMinute;
    volatile static _Bool isNorth;
    
    volatile static uint16 longDegree;
    volatile static float longMinute;
    volatile static _Bool isEast;
    
    /* Heading Variables*/
    volatile static float speedInKnots;
    volatile static float heading;
    
    /* Other */
    volatile static char8 mode;

CY_ISR(Inter_GPS_Vector) {
    enum State_T {ID, TIME, STATUS, LATITUDE, NS, LONGITUDE, EW, SPEED, COURSE, DATE, MAGNETIC, MAGNETIC_DIR, MODE, CHECKSUM, WAIT};
    static char8 buf[15];
    static uint8 pos;
    static enum State_T state;
    char ch = UART_GPS_GetChar();
    #ifdef USB_PRINT
    snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "%c", ch);
    USBPrint_PrintBuffer();
    snprintf(USBPrintBuffer, USBPRINT_BUFFER_SIZE, "HELLO!\n");
    USBPrint_PrintBuffer();
    #endif
    if (ch == '$') state = ID;
    
    switch(state) {
        case ID:
            if (ch != ',') {
                buf[pos] = ch;
                pos++;
            }
            else {
                if (strncmp(buf, "$GPRMC", 6) == 0) {
                    state = TIME;
                }
                else {
                    state = WAIT;
                }
                pos = 0;
            }
        break;
        case TIME:
            if (ch != ',') {
                buf[pos] = ch;
                pos++;
            }
            else {
                char8 temp[15];
                buf[pos] = '\0'; // Terminate the string.
                /* Handle the hour. */
                strncpy(buf,temp,2); // Copy hour into temp.
                hour = atoi(temp);
                
                /* Handle the minute. */
                strncpy(&buf[2], temp, 2); // Copy the minute into temp.
                minute = atoi(temp);
                
                /* Handle the second. */
                strncpy(&buf[4], temp, 6); // Copy the second into temp.
                second = atof(temp);
                
                /* Route to the next stage. */
                pos = 0;
                state = STATUS;
            }

        break;
        case STATUS: // Do nothing for this for now.
            if (ch == ',')
                state = LATITUDE;

        break;
        case LATITUDE: 
            if (ch != ',') {
                buf[pos] = ch;
                pos++;
            }
            else {
                char8 temp[15];
                buf[pos] = '\0'; // Terminate the string.
                /* Handle the degree. */
                strncpy(buf,temp,2); // Copy hour into temp.
                latDegree = atoi(temp);
                
                /* Handle the minute. */
                strncpy(&buf[2], temp, 7); // Copy the minute into temp.
                latMinute = atof(temp);
                
                /* Route to the next stage. */
                pos = 0;
                state = NS;
            }
            
        break;
        case NS:
            if (ch == ',') {
                state = LONGITUDE;
            }
            else {
                isNorth = (ch == 'N');
            }
        break;
        case LONGITUDE:
             if (ch != ',') {
                buf[pos] = ch;
                pos++;
            }
            else {
                char8 temp[15];
                buf[pos] = '\0'; // Terminate the string.
                /* Handle the degree. */
                strncpy(buf,temp,2); // Copy hour into temp.
                longDegree = atoi(temp);
                
                /* Handle the minute. */
                strncpy(&buf[2], temp, 7); // Copy the minute into temp.
                longMinute = atof(temp);
                
                /* Route to the next stage. */
                pos = 0;
                state = EW;
            }
        break;
        case EW:
            if (ch == ',') {
                state = SPEED;
            }
            else {
                isEast = (ch == 'E');
            }
        break;
        case SPEED:
            if (ch == ',') {
                buf[pos] = '\0'; // Terminate the buffer.
                speedInKnots = atof(buf);
                
                /* Route to the next stage. */
                pos = 0;
                state = COURSE;
            }
            else {
                buf[pos] = ch;
                pos++;
            }
        break;
        case COURSE:
            if (ch == ',') {
                buf[pos] = '\0'; // Terminate the buffer.
                heading = atof(buf);
                
                /* Route to the next stage. */
                pos = 0;
                state = DATE;
            }
            else {
                buf[pos] = ch;
                pos++;
            }
        break;
        case DATE:
            if (ch == ',') {
                char8 temp[15];
                buf[pos] = '\0'; // Terminate the buffer.
                
                /* Handle the day. */
                strncpy(buf,temp,2); // Copy day into temp.
                dateDay = atoi(temp);
                
                /* Handle the month. */
                strncpy(&buf[2], temp, 7); // Copy the month into temp.
                dateMonth = atoi(temp);
                
                /* Handle the year */
                strncpy(&buf[4], temp, 7); // Copy the year into temp.
                dateYear = 2000 + atoi(temp);
                
                /* Route to the next stage. */
                pos = 0;
                state = EW;
            }
            else {
                buf[pos] = ch;
                pos++;
            }
            
        break;
        case MAGNETIC:
            if (ch == ',') {
                state = MAGNETIC_DIR;
            }
            else {
                
            }
        break;
        case MAGNETIC_DIR:
            if (ch == ',') {
                state = MODE;
            }
        break;
        case MODE:
            if (ch == ',')
                state = CHECKSUM;
            else
                mode = ch;
        break;
        case CHECKSUM:
            if (ch == ',')
                state = WAIT;
        break;
        case WAIT:
        break;
    }
    
    
    
}

/* Start the GPS subroutine. */
void GPS_Start() {
    UART_GPS_Start();
    Inter_GPS_StartEx(Inter_GPS_Vector);
    GPS_En_Write(1); // Set the GPS En Line.

#ifdef USB_PRINT
    USBPrint_Start();
#endif

}

/* Return the current hour 24 hour format. */
uint16 GPS_GetHour() {
    return hour;
}
/* Return the current minute */
uint16 GPS_GetMinute() {
    return minute;
}
/* Return the current second of the time. */
float GPS_GetSecond() {
    return second;
}
/* Return the current time in HH:MM:SS.SSS format. */
void GPS_GetTime(char* cpTimeString, uint8 len) {
    snprintf(cpTimeString, len, "Time: %2d:%2d:%6f\n",hour, minute, second);
}
    
/* Return the last two digits of the current year */
uint8 GPS_GetYear() {
    return dateYear;
}
/* Return the current month as a number. */
uint8 GPS_GetMonth() {
    return dateMonth;
}
/* Return the current day as a number. */
uint16 GPS_GetDay() {
    return dateDay;
}
/* Return the current date in DD-MM-YY format. */
void GPS_GetDate(char* cpDateString, uint8 len) {
    snprintf(cpDateString, len, "Date: %2d-%2d-%2d\n", dateDay, dateMonth, dateYear);
}

/* Return the latitude degree. */
uint16 GPS_GetLatDegree() {
    return latDegree;
}
/* Return the latitude minute. */
float GPS_GetLatMinute() {
    return latMinute; 
}
/* Return whether system is North. */
_Bool GPS_GetIsNorth() {
    return isNorth;
}
/* Return latitude string in geocode format "DDD MM.MMM". */
void GPS_GetLat(char* cpLatString, uint8 len) {
    char8 dirChar = isNorth ? 'N' : 'S';
    snprintf(cpLatString, len, "Latitude: %c%2d %6f\n", dirChar, latDegree, latMinute);
}

/* Return the longitudinal degree. */
uint16 GPS_GetLongDegree() {
    return longDegree;
}
/* Return the longitudinal minute. */
float GPS_GetLongMinute() {
    return longMinute;
}
/* Return whether system is East. */
_Bool GPS_GetIsEast() {
    return isEast;
}
/* Return longitude string in geocode format "DDD MM.MMM". */
void GPS_GetLong(char* cpLongString, uint8 len) {
    char8 dirChar = isEast ? 'E' : 'W';
    snprintf(cpLongString, len, "Longitude: %c%2d %6f\n", dirChar, longDegree, longMinute);
}

/* Return the speed in knots. */
float GPS_GetSpeed() {
    return speedInKnots;
}
/* Return the current heading in compass degrees. */
float GPS_GetHeading() {
    return heading;
}

/* Get a string containing the current speed and heading. */
void GPS_GetCourse(char* cpCourseString, uint8_t len) {
    snprintf(cpCourseString, len, "Speed (knots): %f; Heading (deg): %f\n", speedInKnots, heading);
}
    


/* [] END OF FILE */
