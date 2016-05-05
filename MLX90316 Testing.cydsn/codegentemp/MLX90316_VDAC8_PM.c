/*******************************************************************************
* File Name: MLX90316_VDAC8_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MLX90316_VDAC8.h"

static MLX90316_VDAC8_backupStruct MLX90316_VDAC8_backup;


/*******************************************************************************
* Function Name: MLX90316_VDAC8_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void MLX90316_VDAC8_SaveConfig(void) 
{
    if (!((MLX90316_VDAC8_CR1 & MLX90316_VDAC8_SRC_MASK) == MLX90316_VDAC8_SRC_UDB))
    {
        MLX90316_VDAC8_backup.data_value = MLX90316_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: MLX90316_VDAC8_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void MLX90316_VDAC8_RestoreConfig(void) 
{
    if (!((MLX90316_VDAC8_CR1 & MLX90316_VDAC8_SRC_MASK) == MLX90316_VDAC8_SRC_UDB))
    {
        if((MLX90316_VDAC8_Strobe & MLX90316_VDAC8_STRB_MASK) == MLX90316_VDAC8_STRB_EN)
        {
            MLX90316_VDAC8_Strobe &= (uint8)(~MLX90316_VDAC8_STRB_MASK);
            MLX90316_VDAC8_Data = MLX90316_VDAC8_backup.data_value;
            MLX90316_VDAC8_Strobe |= MLX90316_VDAC8_STRB_EN;
        }
        else
        {
            MLX90316_VDAC8_Data = MLX90316_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: MLX90316_VDAC8_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  MLX90316_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void MLX90316_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(MLX90316_VDAC8_ACT_PWR_EN == (MLX90316_VDAC8_PWRMGR & MLX90316_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        MLX90316_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        MLX90316_VDAC8_backup.enableState = 0u;
    }
    
    MLX90316_VDAC8_Stop();
    MLX90316_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: MLX90316_VDAC8_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  MLX90316_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MLX90316_VDAC8_Wakeup(void) 
{
    MLX90316_VDAC8_RestoreConfig();
    
    if(MLX90316_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        MLX90316_VDAC8_Enable();

        /* Restore the data register */
        MLX90316_VDAC8_SetValue(MLX90316_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
