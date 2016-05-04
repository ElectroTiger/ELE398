/* system_interface.h
Provides important header functions to interface the existing
C code with a particular embedded system.

Weimen Li, Fall 2016

*/
#define PSOC5LP // For ELE398 - I'm working on the PSoC 5LP.

#ifndef __SYSTEM_INTERFACE__
    #define __SYSTEM_INTERFACE__
    
    /* Include directives. */
   #include <project.h>
    
    /* Functions */
    
    /* Start the UART interface. */
    void SysInter_UART_Start();
    
    /* Start the I2C interface. */
    void SysInter_I2C_Start();
    
    /* Start the SPI interface. */
    void SysInter_SPI_Start();

        
       
#endif







/* [] END OF FILE */
