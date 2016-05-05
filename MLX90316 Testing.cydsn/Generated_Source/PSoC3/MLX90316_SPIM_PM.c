/*******************************************************************************
* File Name: MLX90316_SPIM_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MLX90316_SPIM_PVT.h"

static MLX90316_SPIM_BACKUP_STRUCT MLX90316_SPIM_backup =
{
    MLX90316_SPIM_DISABLED,
    MLX90316_SPIM_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: MLX90316_SPIM_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MLX90316_SPIM_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: MLX90316_SPIM_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MLX90316_SPIM_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: MLX90316_SPIM_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MLX90316_SPIM_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MLX90316_SPIM_Sleep(void) 
{
    /* Save components enable state */
    MLX90316_SPIM_backup.enableState = ((uint8) MLX90316_SPIM_IS_ENABLED);

    MLX90316_SPIM_Stop();
}


/*******************************************************************************
* Function Name: MLX90316_SPIM_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MLX90316_SPIM_backup - used when non-retention registers are restored.
*  MLX90316_SPIM_txBufferWrite - modified every function call - resets to
*  zero.
*  MLX90316_SPIM_txBufferRead - modified every function call - resets to
*  zero.
*  MLX90316_SPIM_rxBufferWrite - modified every function call - resets to
*  zero.
*  MLX90316_SPIM_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MLX90316_SPIM_Wakeup(void) 
{
    #if(MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED)
        MLX90316_SPIM_rxBufferFull  = 0u;
        MLX90316_SPIM_rxBufferRead  = 0u;
        MLX90316_SPIM_rxBufferWrite = 0u;
    #endif /* (MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED) */

    #if(MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED)
        MLX90316_SPIM_txBufferFull  = 0u;
        MLX90316_SPIM_txBufferRead  = 0u;
        MLX90316_SPIM_txBufferWrite = 0u;
    #endif /* (MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    MLX90316_SPIM_ClearFIFO();

    /* Restore components block enable state */
    if(0u != MLX90316_SPIM_backup.enableState)
    {
        MLX90316_SPIM_Enable();
    }
}


/* [] END OF FILE */
