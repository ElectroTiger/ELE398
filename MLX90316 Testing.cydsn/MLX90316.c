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
#include "MLX90316.h"

#define ACTIVE_LOW 0
#define INACTIVE_HIGH 1
#define MLX90316_FRAME_SIZE 10

#define MLX90316_ERROR_DETECTION_MASK 0x0003
#define MLX90316_ERROR_NOERRORVALUE 1

#define MLX90316_ANGLE_MASK 0x3FFF
#define MLX90316_ANGLE_SHIFT 2

#define MLX90316_ANGLE_RANGE (360. / (1 << 14))

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
    uint16 receivedData;
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
    // First two bytes are discarded. 
    // MLX90316_SPIM_ReadByte();
    // MLX90316_SPIM_ReadByte();
    // MLX90316_SPIM_ReadByte();
    // Next two bytes represent valid data. 
    receivedData = (((uint16) receivingArray[7]) << 8) + ((uint16) receivingArray[6]);
    // The rest of the bytes may be discarded.
    MLX90316_SPIM_ClearRxBuffer();
     
    /* We pull the SS back up to terminate the transaction. */
    MLX90316_SS_ControlReg_Write(INACTIVE_HIGH);
    
    /* Now we process the received data. */
    if ((receivedData & MLX90316_ERROR_DETECTION_MASK) == MLX90316_ERROR_NOERRORVALUE) {
        angle = ((receivedData >> MLX90316_ANGLE_SHIFT) & MLX90316_ANGLE_MASK) * MLX90316_ANGLE_RANGE;
    } else {return -1;};
    return angle;
}

/* [] END OF FILE */
