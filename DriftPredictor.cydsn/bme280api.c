/* This file contains the implementations for the bme280api functions. */
#include "bme280api.h"
#include <stdlib.h>

/* Comments from the following I2C Interface declarations were adapted from bme280support.c */

/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : Ignored.
 *	\param reg_addr : Address of the first register, where data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */

#define ACTIVE_LOW 0
#define INACTIVE_HIGH 1

//s8 BME280_bus_write(u8 dev_addr, u8 reg_addr, u8* reg_data, u8 cnt) {
////	Allocate space for writing things to the buffer.
//	uint8_t* writeBuffer = calloc(2 * cnt, sizeof(uint8_t));
//	/*The first byte transmitted is the register address, with the MSB cleared*/
//	int i;
//	for (i = 0; i < 2 * cnt; i += 2) {
//		writeBuffer[i] = reg_addr;
//		reg_addr += 1;
//		writeBuffer[i + 1] = *(reg_data);
//		reg_data++;
//	}
////	Put the data into the transmit buffer.
//	BME280_SPIM_PutArray(writeBuffer, 2 * cnt);
////	Clear the received data buffer.
//	while (BME280_SPIM_GetRxBufferSize() != 2 * cnt)
//		;
//	BME280_SPIM_ClearRxBuffer();
//	free(writeBuffer);
//
//	return 0;
//}

s8 BME280_bus_write(u8 dev_addr, u8 reg_addr, u8* reg_data, u8 cnt) {
    int i = 0;
    for (i = 0; i < cnt; i++) {
        BME280_SPIM_WriteTxData(reg_addr & ~0x80); // First bit clear for write.
        reg_addr++;
        BME280_SPIM_WriteTxData(*reg_data);
        reg_data++;
        while (BME280_SPIM_GetRxBufferSize() != 2);
	    BME280_SPIM_ReadRxData();
        BME280_SPIM_ReadRxData();
    }

	return 0;
}

/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor. Ignored.
 *	\param reg_addr : Address of the first register, where data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read */
s8 BME280_bus_read(u8 dev_addr, u8 reg_addr, u8* reg_data, u8 cnt) {

	int i;
	/* First, we signal that we wish to read by pulling the line down low. */
	BME280_SS_CTRL_Write(ACTIVE_LOW);
	/* To read, we first send the register address, and discard the resulting transmission. */
	BME280_SPIM_WriteTxData(reg_addr | 0x80); // Set the first bit to indicate a read.
	while (BME280_SPIM_GetRxBufferSize() != 1);
	BME280_SPIM_ReadRxData();

	/* Now we transmit the number of bytes we want to read - the value doesn't
	 * matter, as they are all dummy values. */
	for (i = 0; i < cnt; i++) {
		BME280_SPIM_WriteTxData(0xFF);
		while (BME280_SPIM_GetRxBufferSize() != 1);
		reg_data[i] = BME280_SPIM_ReadRxData();
	}

	/* Now the operation is complete, so we write high to SS. */
	BME280_SS_CTRL_Write(INACTIVE_HIGH);
    // strncpy(readBuffer, reg_data, cnt);

	/* Now the operation is complete. */
	return 0;
}

/*
 This routine configures the bme280_t object's read and write
 functions to the SPI read and write functions in this API.
 */
s8 SPI_routine(void) {
	BME280_SS_CTRL_Write(INACTIVE_HIGH);
	bme280.bus_write = BME280_bus_write;
	bme280.bus_read = BME280_bus_read;
	bme280.delay_msec = BME280_delay_msec;
	return BME280_INIT_VALUE;
}

/*	Brief : The delay routine
 *	\param : delay in ms
 */
void BME280_delay_msec(u32 msec) {
	CyDelay(msec);
}

/* Function I defined for the end user: Reading temp, pressure, and humidity as floats.*/
/* Temperature in C. Pressure in Pascals. Humidity in relative humidity. */
void BME280_Read(double* temperature, double* pressure, double* humidity) {
	s32 iHum; // Is in 1024*Actual relative humidity
	s32 iPres; // Is in pascals.
	s32 iTemp; // Pressure in units where it needs to be Pres/500 + 24;
	bme280_get_calib_param();
	bme280_read_uncomp_pressure_temperature_humidity(&iPres, &iTemp, &iHum);
	*temperature = bme280_compensate_temperature_double(iTemp);
	*pressure = bme280_compensate_pressure_double(iPres);
	*humidity = bme280_compensate_humidity_double(iHum);
}

/* Start all subsystem components relating to the BME280, then initializes the BME280. */
void BME280_Start() {
	BME280_SPIM_Start();
	BME280_MISO_Comp_Start();

	SPI_routine();
	bme280_init(&bme280);
	bme280_set_spi3(0); // Use the 4-wire SPi mode.
	bme280_set_power_mode(BME280_NORMAL_MODE);
	bme280_set_oversamp_humidity(BME280_OVERSAMP_1X);
	bme280_set_oversamp_temperature(BME280_OVERSAMP_1X);
	bme280_set_oversamp_pressure(BME280_OVERSAMP_1X);
	bme280_set_standby_durn(BME280_STANDBY_TIME_125_MS);
}

/* [] END OF FILE */
