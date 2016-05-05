/*******************************************************************************
* File Name: MLX90316_MISO_Comp.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "MLX90316_MISO_Comp.h"

static MLX90316_MISO_Comp_backupStruct MLX90316_MISO_Comp_backup;


/*******************************************************************************
* Function Name: MLX90316_MISO_Comp_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void MLX90316_MISO_Comp_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: MLX90316_MISO_Comp_RestoreConfig
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
********************************************************************************/
void MLX90316_MISO_Comp_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: MLX90316_MISO_Comp_Sleep
********************************************************************************
*
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
*  MLX90316_MISO_Comp_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void MLX90316_MISO_Comp_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(MLX90316_MISO_Comp_ACT_PWR_EN == (MLX90316_MISO_Comp_PWRMGR & MLX90316_MISO_Comp_ACT_PWR_EN))
    {
        /* Comp is enabled */
        MLX90316_MISO_Comp_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        MLX90316_MISO_Comp_backup.enableState = 0u;
    }    
    
    MLX90316_MISO_Comp_Stop();
    MLX90316_MISO_Comp_SaveConfig();
}


/*******************************************************************************
* Function Name: MLX90316_MISO_Comp_Wakeup
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
*  MLX90316_MISO_Comp_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MLX90316_MISO_Comp_Wakeup(void) 
{
    MLX90316_MISO_Comp_RestoreConfig();
    
    if(MLX90316_MISO_Comp_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        MLX90316_MISO_Comp_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
