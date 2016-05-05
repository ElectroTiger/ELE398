/*******************************************************************************
* File Name: MLX90316_MOSI_DEBUG.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MLX90316_MOSI_DEBUG_H) /* Pins MLX90316_MOSI_DEBUG_H */
#define CY_PINS_MLX90316_MOSI_DEBUG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MLX90316_MOSI_DEBUG_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MLX90316_MOSI_DEBUG_Write(uint8 value) ;
void    MLX90316_MOSI_DEBUG_SetDriveMode(uint8 mode) ;
uint8   MLX90316_MOSI_DEBUG_ReadDataReg(void) ;
uint8   MLX90316_MOSI_DEBUG_Read(void) ;
void    MLX90316_MOSI_DEBUG_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   MLX90316_MOSI_DEBUG_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MLX90316_MOSI_DEBUG_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define MLX90316_MOSI_DEBUG_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define MLX90316_MOSI_DEBUG_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define MLX90316_MOSI_DEBUG_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define MLX90316_MOSI_DEBUG_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define MLX90316_MOSI_DEBUG_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define MLX90316_MOSI_DEBUG_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define MLX90316_MOSI_DEBUG_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define MLX90316_MOSI_DEBUG_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MLX90316_MOSI_DEBUG_MASK               MLX90316_MOSI_DEBUG__MASK
#define MLX90316_MOSI_DEBUG_SHIFT              MLX90316_MOSI_DEBUG__SHIFT
#define MLX90316_MOSI_DEBUG_WIDTH              1u

/* Interrupt constants */
#if defined(MLX90316_MOSI_DEBUG__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MLX90316_MOSI_DEBUG_SetInterruptMode() function.
     *  @{
     */
        #define MLX90316_MOSI_DEBUG_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define MLX90316_MOSI_DEBUG_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define MLX90316_MOSI_DEBUG_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define MLX90316_MOSI_DEBUG_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define MLX90316_MOSI_DEBUG_INTR_MASK      (0x01u)
#endif /* (MLX90316_MOSI_DEBUG__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MLX90316_MOSI_DEBUG_PS                     (* (reg8 *) MLX90316_MOSI_DEBUG__PS)
/* Data Register */
#define MLX90316_MOSI_DEBUG_DR                     (* (reg8 *) MLX90316_MOSI_DEBUG__DR)
/* Port Number */
#define MLX90316_MOSI_DEBUG_PRT_NUM                (* (reg8 *) MLX90316_MOSI_DEBUG__PRT) 
/* Connect to Analog Globals */                                                  
#define MLX90316_MOSI_DEBUG_AG                     (* (reg8 *) MLX90316_MOSI_DEBUG__AG)                       
/* Analog MUX bux enable */
#define MLX90316_MOSI_DEBUG_AMUX                   (* (reg8 *) MLX90316_MOSI_DEBUG__AMUX) 
/* Bidirectional Enable */                                                        
#define MLX90316_MOSI_DEBUG_BIE                    (* (reg8 *) MLX90316_MOSI_DEBUG__BIE)
/* Bit-mask for Aliased Register Access */
#define MLX90316_MOSI_DEBUG_BIT_MASK               (* (reg8 *) MLX90316_MOSI_DEBUG__BIT_MASK)
/* Bypass Enable */
#define MLX90316_MOSI_DEBUG_BYP                    (* (reg8 *) MLX90316_MOSI_DEBUG__BYP)
/* Port wide control signals */                                                   
#define MLX90316_MOSI_DEBUG_CTL                    (* (reg8 *) MLX90316_MOSI_DEBUG__CTL)
/* Drive Modes */
#define MLX90316_MOSI_DEBUG_DM0                    (* (reg8 *) MLX90316_MOSI_DEBUG__DM0) 
#define MLX90316_MOSI_DEBUG_DM1                    (* (reg8 *) MLX90316_MOSI_DEBUG__DM1)
#define MLX90316_MOSI_DEBUG_DM2                    (* (reg8 *) MLX90316_MOSI_DEBUG__DM2) 
/* Input Buffer Disable Override */
#define MLX90316_MOSI_DEBUG_INP_DIS                (* (reg8 *) MLX90316_MOSI_DEBUG__INP_DIS)
/* LCD Common or Segment Drive */
#define MLX90316_MOSI_DEBUG_LCD_COM_SEG            (* (reg8 *) MLX90316_MOSI_DEBUG__LCD_COM_SEG)
/* Enable Segment LCD */
#define MLX90316_MOSI_DEBUG_LCD_EN                 (* (reg8 *) MLX90316_MOSI_DEBUG__LCD_EN)
/* Slew Rate Control */
#define MLX90316_MOSI_DEBUG_SLW                    (* (reg8 *) MLX90316_MOSI_DEBUG__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MLX90316_MOSI_DEBUG_PRTDSI__CAPS_SEL       (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MLX90316_MOSI_DEBUG_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MLX90316_MOSI_DEBUG_PRTDSI__OE_SEL0        (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__OE_SEL0) 
#define MLX90316_MOSI_DEBUG_PRTDSI__OE_SEL1        (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MLX90316_MOSI_DEBUG_PRTDSI__OUT_SEL0       (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__OUT_SEL0) 
#define MLX90316_MOSI_DEBUG_PRTDSI__OUT_SEL1       (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MLX90316_MOSI_DEBUG_PRTDSI__SYNC_OUT       (* (reg8 *) MLX90316_MOSI_DEBUG__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MLX90316_MOSI_DEBUG__SIO_CFG)
    #define MLX90316_MOSI_DEBUG_SIO_HYST_EN        (* (reg8 *) MLX90316_MOSI_DEBUG__SIO_HYST_EN)
    #define MLX90316_MOSI_DEBUG_SIO_REG_HIFREQ     (* (reg8 *) MLX90316_MOSI_DEBUG__SIO_REG_HIFREQ)
    #define MLX90316_MOSI_DEBUG_SIO_CFG            (* (reg8 *) MLX90316_MOSI_DEBUG__SIO_CFG)
    #define MLX90316_MOSI_DEBUG_SIO_DIFF           (* (reg8 *) MLX90316_MOSI_DEBUG__SIO_DIFF)
#endif /* (MLX90316_MOSI_DEBUG__SIO_CFG) */

/* Interrupt Registers */
#if defined(MLX90316_MOSI_DEBUG__INTSTAT)
    #define MLX90316_MOSI_DEBUG_INTSTAT             (* (reg8 *) MLX90316_MOSI_DEBUG__INTSTAT)
    #define MLX90316_MOSI_DEBUG_SNAP                (* (reg8 *) MLX90316_MOSI_DEBUG__SNAP)
    
	#define MLX90316_MOSI_DEBUG_0_INTTYPE_REG 		(* (reg8 *) MLX90316_MOSI_DEBUG__0__INTTYPE)
#endif /* (MLX90316_MOSI_DEBUG__INTSTAT) */

#endif /* End Pins MLX90316_MOSI_DEBUG_H */


/* [] END OF FILE */
