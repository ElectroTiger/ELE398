/*******************************************************************************
* File Name: MLX90316_SPIM_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MLX90316_SPIM_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START MLX90316_SPIM_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: MLX90316_SPIM_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  MLX90316_SPIM_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  MLX90316_SPIM_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  MLX90316_SPIM_txBuffer[MLX90316_SPIM_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(MLX90316_SPIM_TX_ISR)
{
    #if(MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef MLX90316_SPIM_TX_ISR_ENTRY_CALLBACK
        MLX90316_SPIM_TX_ISR_EntryCallback();
    #endif /* MLX90316_SPIM_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START MLX90316_SPIM_TX_ISR_START` */

    /* `#END` */
    
    #if(MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(MLX90316_SPIM_txBufferRead != MLX90316_SPIM_txBufferWrite)
        {
            tmpStatus = MLX90316_SPIM_GET_STATUS_TX(MLX90316_SPIM_swStatusTx);
            MLX90316_SPIM_swStatusTx = tmpStatus;

            if(0u != (MLX90316_SPIM_swStatusTx & MLX90316_SPIM_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == MLX90316_SPIM_txBufferFull)
                {
                   MLX90316_SPIM_txBufferRead++;

                    if(MLX90316_SPIM_txBufferRead >= MLX90316_SPIM_TX_BUFFER_SIZE)
                    {
                        MLX90316_SPIM_txBufferRead = 0u;
                    }
                }
                else
                {
                    MLX90316_SPIM_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(MLX90316_SPIM_TXDATA_PTR, 
                                             MLX90316_SPIM_txBuffer[MLX90316_SPIM_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(MLX90316_SPIM_txBufferRead == MLX90316_SPIM_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            MLX90316_SPIM_TX_STATUS_MASK_REG &= ((uint8) ~MLX90316_SPIM_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START MLX90316_SPIM_TX_ISR_END` */

    /* `#END` */
    
    #ifdef MLX90316_SPIM_TX_ISR_EXIT_CALLBACK
        MLX90316_SPIM_TX_ISR_ExitCallback();
    #endif /* MLX90316_SPIM_TX_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: MLX90316_SPIM_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  MLX90316_SPIM_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  MLX90316_SPIM_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  MLX90316_SPIM_rxBuffer[MLX90316_SPIM_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(MLX90316_SPIM_RX_ISR)
{
    #if(MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED) */

    #ifdef MLX90316_SPIM_RX_ISR_ENTRY_CALLBACK
        MLX90316_SPIM_RX_ISR_EntryCallback();
    #endif /* MLX90316_SPIM_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START MLX90316_SPIM_RX_ISR_START` */

    /* `#END` */
    
    #if(MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = MLX90316_SPIM_GET_STATUS_RX(MLX90316_SPIM_swStatusRx);
        MLX90316_SPIM_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (MLX90316_SPIM_swStatusRx & MLX90316_SPIM_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(MLX90316_SPIM_RXDATA_PTR);

            /* Set next pointer. */
            MLX90316_SPIM_rxBufferWrite++;
            if(MLX90316_SPIM_rxBufferWrite >= MLX90316_SPIM_RX_BUFFER_SIZE)
            {
                MLX90316_SPIM_rxBufferWrite = 0u;
            }

            if(MLX90316_SPIM_rxBufferWrite == MLX90316_SPIM_rxBufferRead)
            {
                MLX90316_SPIM_rxBufferRead++;
                if(MLX90316_SPIM_rxBufferRead >= MLX90316_SPIM_RX_BUFFER_SIZE)
                {
                    MLX90316_SPIM_rxBufferRead = 0u;
                }

                MLX90316_SPIM_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            MLX90316_SPIM_rxBuffer[MLX90316_SPIM_rxBufferWrite] = rxData;

            tmpStatus = MLX90316_SPIM_GET_STATUS_RX(MLX90316_SPIM_swStatusRx);
            MLX90316_SPIM_swStatusRx = tmpStatus;
        }

    #endif /* (MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START MLX90316_SPIM_RX_ISR_END` */

    /* `#END` */
    
    #ifdef MLX90316_SPIM_RX_ISR_EXIT_CALLBACK
        MLX90316_SPIM_RX_ISR_ExitCallback();
    #endif /* MLX90316_SPIM_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
