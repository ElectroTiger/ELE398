/* Author: Weimen Li
 * File: bme280api.h
 * Description: This header file declares the necessary functions required for
 * our application code to interact with the BME280 library.  */
    
#ifndef __BME280_API__
    #define __BME280_API__
    #include <bme280.h>
    #include <project.h>
    
    /* "Global" variable which references the bme280. */
    struct bme280_t bme280;
    
    /* Comments from the following I2C Interface declarations were adapted from bme280support.c */
    
        /*	\Brief: The function is used as SPI bus write
     *	\Return : Status of the SPI write
     *	\param dev_addr : The device address of the sensor
     *	\param reg_addr : Address of the first register, will data is going to be written
     *	\param reg_data : It is a value hold in the array,
     *		will be used for write the value into the register
     *	\param cnt : The no of byte of data to be write
     */
    s8 BME280_bus_write(u8 dev_addr, u8 reg_addr, u8* reg_data, u8 cnt);
    
        /*	\Brief: The function is used as SPI bus read
     *	\Return : Status of the SPI read
     *	\param dev_addr : The device address of the sensor
     *	\param reg_addr : Address of the first register, will data is going to be read
     *	\param reg_data : This data read from the sensor, which is hold in an array
     *	\param cnt : The no of byte of data to be read */
    s8 BME280_bus_read(u8 dev_addr, u8 reg_addr, u8* reg_data, u8 cnt);
    
        /*
     * \Brief: SPI/I2C init routine
    */
    s8 SPI_routine(void);
    
    /*	Brief : The delay routine
     *	\param : delay in ms
    */
    void BME280_delay_msec(u32 msec);
    
    /* Function I defined for the end user: Reading temp, pressure, and humidity as floats.*/
    void BME280_Read(double* temp, double* pres, double* humidity);
    
    /* Get the ground-level pressure from the system. */
    double BME280_GetGroundPressure();

    /* Return the current altitude in meters. */
    double BME280_GetAltitude();

    /* Start all subsystem components relating to the BME280, then initializes the BME280. */
    void BME280_Start();
    #endif

/* [] END OF FILE */
