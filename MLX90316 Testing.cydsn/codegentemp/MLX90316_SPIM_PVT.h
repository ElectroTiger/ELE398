/*******************************************************************************
* File Name: .h
* Version 2.50
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_MLX90316_SPIM_H)
#define CY_SPIM_PVT_MLX90316_SPIM_H

#include "MLX90316_SPIM.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 MLX90316_SPIM_swStatusTx;
extern volatile uint8 MLX90316_SPIM_swStatusRx;

#if(MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 MLX90316_SPIM_txBuffer[MLX90316_SPIM_TX_BUFFER_SIZE];
    extern volatile uint8 MLX90316_SPIM_txBufferRead;
    extern volatile uint8 MLX90316_SPIM_txBufferWrite;
    extern volatile uint8 MLX90316_SPIM_txBufferFull;
#endif /* (MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED) */

#if(MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 MLX90316_SPIM_rxBuffer[MLX90316_SPIM_RX_BUFFER_SIZE];
    extern volatile uint8 MLX90316_SPIM_rxBufferRead;
    extern volatile uint8 MLX90316_SPIM_rxBufferWrite;
    extern volatile uint8 MLX90316_SPIM_rxBufferFull;
#endif /* (MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_MLX90316_SPIM_H */


/* [] END OF FILE */
