/*******************************************************************************
* File Name: MLX90316_SS_ControlReg.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_MLX90316_SS_ControlReg_H) /* CY_CONTROL_REG_MLX90316_SS_ControlReg_H */
#define CY_CONTROL_REG_MLX90316_SS_ControlReg_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} MLX90316_SS_ControlReg_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    MLX90316_SS_ControlReg_Write(uint8 control) ;
uint8   MLX90316_SS_ControlReg_Read(void) ;

void MLX90316_SS_ControlReg_SaveConfig(void) ;
void MLX90316_SS_ControlReg_RestoreConfig(void) ;
void MLX90316_SS_ControlReg_Sleep(void) ; 
void MLX90316_SS_ControlReg_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define MLX90316_SS_ControlReg_Control        (* (reg8 *) MLX90316_SS_ControlReg_Sync_ctrl_reg__CONTROL_REG )
#define MLX90316_SS_ControlReg_Control_PTR    (  (reg8 *) MLX90316_SS_ControlReg_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_MLX90316_SS_ControlReg_H */


/* [] END OF FILE */
