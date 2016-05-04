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
#include "bme280api.h"
#include "project.h"
#include "bme280.h"
#include "stdlib.h"

    s8 bme280i2c_bus_write(uint8 device_addr, uint8 register_addr, uint8* register_data, uint8 wr_len) {
       uint8 status;
        /* Send the slave address over I2C. */
       status = I2C_MasterSendStart(device_addr, 0); /* Send the slave address over I2C. */
       if (status != I2C_MSTR_NO_ERROR) {
            return -1; // If there was an error, return -1.
       }
        /* Send register data over I2C. */
       status = I2C_MasterWriteBuf(register_addr, register_data, wr_len, I2C_MODE_REPEAT_START);
       if (status != I2C_MSTR_NO_ERROR) {
            return -1; // If there was an error, return -1.
       }
    return 0; // Return 0 on success. 
    }
    
    s8 bme280i2c_bus_read(uint8 device_addr, uint8 register_addr, uint8* register_data, uint8 rd_len) {
        uint8 status;
        /* Send the slave address over I2C. */
        status = I2C_MasterSendStart(device_addr, 0); // Send the slave address over I2C.
        if (status != I2C_MSTR_NO_ERROR) {
            return -1; // If there was an error, return -1.
        }
        /* Read register data from I2C.*/
        status = I2C_MasterReadBuf(register_addr, register_data, rd_len, I2C_MODE_REPEAT_START);
        if (status != I2C_MSTR_NO_ERROR) {
            return -1; // If there was an error, return -1.
        }
    return 0; // Return 0 on success.
    }
    
    void bme280i2c_delay(uint16 msec) {
        CyDelay((uint32) msec);
    }
    
    void bme280api_Start(struct bme280_t bme280) {
        {
            uint32 com_rslt; // Variable to store error.
            do {
                /* Set variables in the BME280 structure) */
                	bme280.bus_write = bme280i2c_bus_write;
                	bme280.bus_read = bme280i2c_bus_read;
                	bme280.dev_addr = BME280_I2C_ADDRESS1; // Address pin wired to ground.
                	bme280.delay_msec = &CyDelay;
                
                /* Initialize bme280 structure */
                com_rslt = bme280_init(&bme280); 
                
                /* Set parameters in the bme280. */
                com_rslt += bme280_set_power_mode(BME280_NORMAL_MODE);
                com_rslt += bme280_set_oversamp_humidity(BME280_OVERSAMP_1X);
        	    com_rslt += bme280_set_oversamp_pressure(BME280_OVERSAMP_2X);
        	    com_rslt += bme280_set_oversamp_temperature(BME280_OVERSAMP_4X);
            } while (com_rslt != 0);
        }
        
    }

/* [] END OF FILE */
