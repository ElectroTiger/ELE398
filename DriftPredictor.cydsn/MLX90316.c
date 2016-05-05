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
#include <stdio.h>
#include <math.h>
#include "MLX90316.h"

#define ACTIVE_LOW 0
#define INACTIVE_HIGH 1
#define MLX90316_FRAME_SIZE 10

#define MLX90316_ERROR_DETECTION_MASK 0x0003
#define MLX90316_ERROR_NOERRORVALUE 1

#define MLX90316_ANGLE_MASK 0x3FFF
#define MLX90316_ANGLE_SHIFT 2

#define MLX90316_ANGLE_STEP (360. / (1 << 14))

static uint16 receivedData;

/* Start the MLX 90316 Module. */
void MLX90316_Start() {
    MLX90316_SPIM_Start();
    MLX90316_MISO_Comp_Start();
    MLX90316_VDAC8_Start();
    MLX90316_SS_ControlReg_Write(INACTIVE_HIGH);
}

/* Read the current angle. */
double MLX90316_ReadAngle() {
    double angle;
    int i;
    const uint8 sendingArray[MLX90316_FRAME_SIZE] = {0xAA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    uint8 receivingArray[MLX90316_FRAME_SIZE] = {0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    // const uint8 sendingArray[MLX90316_FRAME_SIZE] = {0,0,0,0,0,0,0,0,0,0};
    /* First, we pull down SS for at least 1.5 us. */
    MLX90316_SS_ControlReg_Write(ACTIVE_LOW);
    // CyDelay(1);
    /* Transfer size is 10 bytes. We initiate a transfer by writing 0xAA, then 9 bytes of 0xFF. */
    MLX90316_SPIM_PutArray(sendingArray, MLX90316_FRAME_SIZE);
    /* Block while we wait for the transfer to complete. */
    // while(!(MLX90316_SPIM_ReadTxStatus() & MLX90316_SPIM_STS_TX_FIFO_EMPTY));
    while ((MLX90316_SPIM_GetRxBufferSize() != 9));
    /* Parse the received data.  */
    for(i = MLX90316_FRAME_SIZE - 1; i >= 0; i--) {
        receivingArray[i] = MLX90316_SPIM_ReadByte();
    }
    
    receivedData = (((uint16) receivingArray[7]) << 8) + ((uint16) receivingArray[6]);
     
    /* We pull the SS back up to terminate the transaction. */
    MLX90316_SS_ControlReg_Write(INACTIVE_HIGH);
    
    /* Now we process the received data. */
    if ((receivedData & MLX90316_ERROR_DETECTION_MASK) == MLX90316_ERROR_NOERRORVALUE) {
        angle = ((receivedData >> MLX90316_ANGLE_SHIFT) & MLX90316_ANGLE_MASK) * MLX90316_ANGLE_STEP;
    } else {return NAN;};
    return angle;
}

/* Get a character string containing the error. Returns null if there are no errors.*/
void MLX90316_GetError(char* errorString, int iLen) {
    /* If there is no error. */
    if ((receivedData & MLX90316_ERROR_DETECTION_MASK) == MLX90316_ERROR_NOERRORVALUE) {
        errorString[0] = '\0';
    }
    
    /* Error bit masks: */
    #define F_ADCMONITOR (1L << 2)
    #define F_ADCSATURA (1L << 3)
    #define F_RGTOOLOW (1L << 4)
    #define F_MAGTOOLOW (1L << 5)
    #define F_MAGTOOHIGH (1L << 6)
    #define F_RGTOOHIGH (1L << 7)
    #define F_MT7V (1L << 10)
    
    if (receivedData & F_ADCMONITOR) {
        snprintf(errorString, iLen, "ADC Failure\n");
    } else if (receivedData & F_ADCSATURA) {
        snprintf(errorString, iLen, "ADC Saturation\n");
    } else if (receivedData & F_RGTOOLOW) {
        snprintf(errorString, iLen, "Analog gain below trimmed threshold\n");
    } else if (receivedData & F_MAGTOOLOW) {
        snprintf(errorString, iLen, "Magnetic Field Too Weak\n");
    } else if (receivedData & F_MAGTOOHIGH) {
        snprintf(errorString, iLen, "Magnetic Field Too Strong.");
    } else if (receivedData & F_RGTOOHIGH) {
        snprintf(errorString, iLen, "Analog gain above trimmed threshold\n");
    } else if (receivedData & F_RGTOOHIGH) {
        snprintf(errorString, iLen, "Device Supply Greater than 7V\n");
    } else {
        snprintf(errorString, iLen, "Undefined: %xL", receivedData);
    }
    
    
}

/* [] END OF FILE */
