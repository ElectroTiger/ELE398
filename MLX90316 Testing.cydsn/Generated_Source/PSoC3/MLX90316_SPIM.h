/*******************************************************************************
* File Name: MLX90316_SPIM.h
* Version 2.50
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Master Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_MLX90316_SPIM_H)
#define CY_SPIM_MLX90316_SPIM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component SPI_Master_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define MLX90316_SPIM_INTERNAL_CLOCK             (0u)

#if(0u != MLX90316_SPIM_INTERNAL_CLOCK)
    #include "MLX90316_SPIM_IntClock.h"
#endif /* (0u != MLX90316_SPIM_INTERNAL_CLOCK) */

#define MLX90316_SPIM_MODE                       (3u)
#define MLX90316_SPIM_DATA_WIDTH                 (8u)
#define MLX90316_SPIM_MODE_USE_ZERO              (0u)
#define MLX90316_SPIM_BIDIRECTIONAL_MODE         (0u)

/* Internal interrupt handling */
#define MLX90316_SPIM_TX_BUFFER_SIZE             (10u)
#define MLX90316_SPIM_RX_BUFFER_SIZE             (10u)
#define MLX90316_SPIM_INTERNAL_TX_INT_ENABLED    (1u)
#define MLX90316_SPIM_INTERNAL_RX_INT_ENABLED    (1u)

#define MLX90316_SPIM_SINGLE_REG_SIZE            (8u)
#define MLX90316_SPIM_USE_SECOND_DATAPATH        (MLX90316_SPIM_DATA_WIDTH > MLX90316_SPIM_SINGLE_REG_SIZE)

#define MLX90316_SPIM_FIFO_SIZE                  (4u)
#define MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED    ((0u != MLX90316_SPIM_INTERNAL_TX_INT_ENABLED) && \
                                                     (MLX90316_SPIM_TX_BUFFER_SIZE > MLX90316_SPIM_FIFO_SIZE))

#define MLX90316_SPIM_RX_SOFTWARE_BUF_ENABLED    ((0u != MLX90316_SPIM_INTERNAL_RX_INT_ENABLED) && \
                                                     (MLX90316_SPIM_RX_BUFFER_SIZE > MLX90316_SPIM_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} MLX90316_SPIM_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  MLX90316_SPIM_Init(void)                           ;
void  MLX90316_SPIM_Enable(void)                         ;
void  MLX90316_SPIM_Start(void)                          ;
void  MLX90316_SPIM_Stop(void)                           ;

void  MLX90316_SPIM_EnableTxInt(void)                    ;
void  MLX90316_SPIM_EnableRxInt(void)                    ;
void  MLX90316_SPIM_DisableTxInt(void)                   ;
void  MLX90316_SPIM_DisableRxInt(void)                   ;

void  MLX90316_SPIM_Sleep(void)                          ;
void  MLX90316_SPIM_Wakeup(void)                         ;
void  MLX90316_SPIM_SaveConfig(void)                     ;
void  MLX90316_SPIM_RestoreConfig(void)                  ;

void  MLX90316_SPIM_SetTxInterruptMode(uint8 intSrc)     ;
void  MLX90316_SPIM_SetRxInterruptMode(uint8 intSrc)     ;
uint8 MLX90316_SPIM_ReadTxStatus(void)                   ;
uint8 MLX90316_SPIM_ReadRxStatus(void)                   ;
void  MLX90316_SPIM_WriteTxData(uint8 txData)  \
                                                            ;
uint8 MLX90316_SPIM_ReadRxData(void) \
                                                            ;
uint8 MLX90316_SPIM_GetRxBufferSize(void)                ;
uint8 MLX90316_SPIM_GetTxBufferSize(void)                ;
void  MLX90316_SPIM_ClearRxBuffer(void)                  ;
void  MLX90316_SPIM_ClearTxBuffer(void)                  ;
void  MLX90316_SPIM_ClearFIFO(void)                              ;
void  MLX90316_SPIM_PutArray(const uint8 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != MLX90316_SPIM_BIDIRECTIONAL_MODE)
    void  MLX90316_SPIM_TxEnable(void)                   ;
    void  MLX90316_SPIM_TxDisable(void)                  ;
#endif /* (0u != MLX90316_SPIM_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(MLX90316_SPIM_TX_ISR);
CY_ISR_PROTO(MLX90316_SPIM_RX_ISR);


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 MLX90316_SPIM_initVar;


/***************************************
*           API Constants
***************************************/

#define MLX90316_SPIM_TX_ISR_NUMBER     ((uint8) (MLX90316_SPIM_TxInternalInterrupt__INTC_NUMBER))
#define MLX90316_SPIM_RX_ISR_NUMBER     ((uint8) (MLX90316_SPIM_RxInternalInterrupt__INTC_NUMBER))

#define MLX90316_SPIM_TX_ISR_PRIORITY   ((uint8) (MLX90316_SPIM_TxInternalInterrupt__INTC_PRIOR_NUM))
#define MLX90316_SPIM_RX_ISR_PRIORITY   ((uint8) (MLX90316_SPIM_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define MLX90316_SPIM_INT_ON_SPI_DONE    ((uint8) (0u   << MLX90316_SPIM_STS_SPI_DONE_SHIFT))
#define MLX90316_SPIM_INT_ON_TX_EMPTY    ((uint8) (0u   << MLX90316_SPIM_STS_TX_FIFO_EMPTY_SHIFT))
#define MLX90316_SPIM_INT_ON_TX_NOT_FULL ((uint8) (1u << \
                                                                           MLX90316_SPIM_STS_TX_FIFO_NOT_FULL_SHIFT))
#define MLX90316_SPIM_INT_ON_BYTE_COMP   ((uint8) (0u  << MLX90316_SPIM_STS_BYTE_COMPLETE_SHIFT))
#define MLX90316_SPIM_INT_ON_SPI_IDLE    ((uint8) (0u   << MLX90316_SPIM_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define MLX90316_SPIM_INT_ON_TX_NOT_FULL_DEF ((MLX90316_SPIM_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (MLX90316_SPIM_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define MLX90316_SPIM_TX_INIT_INTERRUPTS_MASK    (MLX90316_SPIM_INT_ON_SPI_DONE  | \
                                                     MLX90316_SPIM_INT_ON_TX_EMPTY  | \
                                                     MLX90316_SPIM_INT_ON_TX_NOT_FULL_DEF | \
                                                     MLX90316_SPIM_INT_ON_BYTE_COMP | \
                                                     MLX90316_SPIM_INT_ON_SPI_IDLE)

#define MLX90316_SPIM_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          MLX90316_SPIM_STS_RX_FIFO_FULL_SHIFT))
#define MLX90316_SPIM_INT_ON_RX_NOT_EMPTY    ((uint8) (1u << \
                                                                          MLX90316_SPIM_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define MLX90316_SPIM_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          MLX90316_SPIM_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define MLX90316_SPIM_RX_INIT_INTERRUPTS_MASK    (MLX90316_SPIM_INT_ON_RX_FULL      | \
                                                     MLX90316_SPIM_INT_ON_RX_NOT_EMPTY | \
                                                     MLX90316_SPIM_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define MLX90316_SPIM_BITCTR_INIT            (((uint8) (MLX90316_SPIM_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define MLX90316_SPIM_TXDATA_REG (* (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F0_REG)
    #define MLX90316_SPIM_TXDATA_PTR (  (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F0_REG)
    #define MLX90316_SPIM_RXDATA_REG (* (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F1_REG)
    #define MLX90316_SPIM_RXDATA_PTR (  (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(MLX90316_SPIM_USE_SECOND_DATAPATH)
        #define MLX90316_SPIM_TXDATA_REG (* (reg16 *) \
                                          MLX90316_SPIM_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define MLX90316_SPIM_TXDATA_PTR (  (reg16 *) \
                                          MLX90316_SPIM_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define MLX90316_SPIM_RXDATA_REG (* (reg16 *) \
                                          MLX90316_SPIM_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
        #define MLX90316_SPIM_RXDATA_PTR (  (reg16 *) \
                                          MLX90316_SPIM_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
    #else
        #define MLX90316_SPIM_TXDATA_REG (* (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F0_REG)
        #define MLX90316_SPIM_TXDATA_PTR (  (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F0_REG)
        #define MLX90316_SPIM_RXDATA_REG (* (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F1_REG)
        #define MLX90316_SPIM_RXDATA_PTR (  (reg8 *) \
                                                MLX90316_SPIM_BSPIM_sR8_Dp_u0__F1_REG)
    #endif /* (MLX90316_SPIM_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define MLX90316_SPIM_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        MLX90316_SPIM_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)
#define MLX90316_SPIM_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        MLX90316_SPIM_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(MLX90316_SPIM_USE_SECOND_DATAPATH)
    #define MLX90316_SPIM_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        MLX90316_SPIM_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define MLX90316_SPIM_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        MLX90316_SPIM_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
#endif /* (MLX90316_SPIM_USE_SECOND_DATAPATH) */

#define MLX90316_SPIM_COUNTER_PERIOD_REG     (* (reg8 *) MLX90316_SPIM_BSPIM_BitCounter__PERIOD_REG)
#define MLX90316_SPIM_COUNTER_PERIOD_PTR     (  (reg8 *) MLX90316_SPIM_BSPIM_BitCounter__PERIOD_REG)
#define MLX90316_SPIM_COUNTER_CONTROL_REG    (* (reg8 *) MLX90316_SPIM_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define MLX90316_SPIM_COUNTER_CONTROL_PTR    (  (reg8 *) MLX90316_SPIM_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define MLX90316_SPIM_TX_STATUS_REG          (* (reg8 *) MLX90316_SPIM_BSPIM_TxStsReg__STATUS_REG)
#define MLX90316_SPIM_TX_STATUS_PTR          (  (reg8 *) MLX90316_SPIM_BSPIM_TxStsReg__STATUS_REG)
#define MLX90316_SPIM_RX_STATUS_REG          (* (reg8 *) MLX90316_SPIM_BSPIM_RxStsReg__STATUS_REG)
#define MLX90316_SPIM_RX_STATUS_PTR          (  (reg8 *) MLX90316_SPIM_BSPIM_RxStsReg__STATUS_REG)

#define MLX90316_SPIM_CONTROL_REG            (* (reg8 *) \
                                      MLX90316_SPIM_BSPIM_BidirMode_CtrlReg__CONTROL_REG)
#define MLX90316_SPIM_CONTROL_PTR            (  (reg8 *) \
                                      MLX90316_SPIM_BSPIM_BidirMode_CtrlReg__CONTROL_REG)

#define MLX90316_SPIM_TX_STATUS_MASK_REG     (* (reg8 *) MLX90316_SPIM_BSPIM_TxStsReg__MASK_REG)
#define MLX90316_SPIM_TX_STATUS_MASK_PTR     (  (reg8 *) MLX90316_SPIM_BSPIM_TxStsReg__MASK_REG)
#define MLX90316_SPIM_RX_STATUS_MASK_REG     (* (reg8 *) MLX90316_SPIM_BSPIM_RxStsReg__MASK_REG)
#define MLX90316_SPIM_RX_STATUS_MASK_PTR     (  (reg8 *) MLX90316_SPIM_BSPIM_RxStsReg__MASK_REG)

#define MLX90316_SPIM_TX_STATUS_ACTL_REG     (* (reg8 *) MLX90316_SPIM_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define MLX90316_SPIM_TX_STATUS_ACTL_PTR     (  (reg8 *) MLX90316_SPIM_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define MLX90316_SPIM_RX_STATUS_ACTL_REG     (* (reg8 *) MLX90316_SPIM_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define MLX90316_SPIM_RX_STATUS_ACTL_PTR     (  (reg8 *) MLX90316_SPIM_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(MLX90316_SPIM_USE_SECOND_DATAPATH)
    #define MLX90316_SPIM_AUX_CONTROLDP1     (MLX90316_SPIM_AUX_CONTROL_DP1_REG)
#endif /* (MLX90316_SPIM_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define MLX90316_SPIM_STS_SPI_DONE_SHIFT             (0x00u)
#define MLX90316_SPIM_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define MLX90316_SPIM_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define MLX90316_SPIM_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define MLX90316_SPIM_STS_SPI_IDLE_SHIFT             (0x04u)
#define MLX90316_SPIM_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define MLX90316_SPIM_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define MLX90316_SPIM_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define MLX90316_SPIM_STS_SPI_DONE           ((uint8) (0x01u << MLX90316_SPIM_STS_SPI_DONE_SHIFT))
#define MLX90316_SPIM_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << MLX90316_SPIM_STS_TX_FIFO_EMPTY_SHIFT))
#define MLX90316_SPIM_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << MLX90316_SPIM_STS_TX_FIFO_NOT_FULL_SHIFT))
#define MLX90316_SPIM_STS_BYTE_COMPLETE      ((uint8) (0x01u << MLX90316_SPIM_STS_BYTE_COMPLETE_SHIFT))
#define MLX90316_SPIM_STS_SPI_IDLE           ((uint8) (0x01u << MLX90316_SPIM_STS_SPI_IDLE_SHIFT))
#define MLX90316_SPIM_STS_RX_FIFO_FULL       ((uint8) (0x01u << MLX90316_SPIM_STS_RX_FIFO_FULL_SHIFT))
#define MLX90316_SPIM_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << MLX90316_SPIM_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define MLX90316_SPIM_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << MLX90316_SPIM_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define MLX90316_SPIM_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define MLX90316_SPIM_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define MLX90316_SPIM_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define MLX90316_SPIM_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define MLX90316_SPIM_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define MLX90316_SPIM_FIFO_CLR       (MLX90316_SPIM_TX_FIFO_CLR | MLX90316_SPIM_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define MLX90316_SPIM_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define MLX90316_SPIM_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define MLX90316_SPIM_AUX_CTRL_FIFO0_CLR         (0x01u)
#define MLX90316_SPIM_AUX_CTRL_FIFO1_CLR         (0x02u)
#define MLX90316_SPIM_AUX_CTRL_FIFO0_LVL         (0x04u)
#define MLX90316_SPIM_AUX_CTRL_FIFO1_LVL         (0x08u)
#define MLX90316_SPIM_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define MLX90316_SPIM_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define MLX90316_SPIM_IS_ENABLED (0u != (MLX90316_SPIM_TX_STATUS_ACTL_REG & MLX90316_SPIM_INT_ENABLE))

/* Retuns TX status register */
#define MLX90316_SPIM_GET_STATUS_TX(swTxSts) ( (uint8)(MLX90316_SPIM_TX_STATUS_REG | \
                                                          ((swTxSts) & MLX90316_SPIM_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define MLX90316_SPIM_GET_STATUS_RX(swRxSts) ( (uint8)(MLX90316_SPIM_RX_STATUS_REG | \
                                                          ((swRxSts) & MLX90316_SPIM_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define MLX90316_SPIM_WriteByte   MLX90316_SPIM_WriteTxData
#define MLX90316_SPIM_ReadByte    MLX90316_SPIM_ReadRxData
void  MLX90316_SPIM_SetInterruptMode(uint8 intSrc)       ;
uint8 MLX90316_SPIM_ReadStatus(void)                     ;
void  MLX90316_SPIM_EnableInt(void)                      ;
void  MLX90316_SPIM_DisableInt(void)                     ;

#define MLX90316_SPIM_TXDATA                 (MLX90316_SPIM_TXDATA_REG)
#define MLX90316_SPIM_RXDATA                 (MLX90316_SPIM_RXDATA_REG)
#define MLX90316_SPIM_AUX_CONTROLDP0         (MLX90316_SPIM_AUX_CONTROL_DP0_REG)
#define MLX90316_SPIM_TXBUFFERREAD           (MLX90316_SPIM_txBufferRead)
#define MLX90316_SPIM_TXBUFFERWRITE          (MLX90316_SPIM_txBufferWrite)
#define MLX90316_SPIM_RXBUFFERREAD           (MLX90316_SPIM_rxBufferRead)
#define MLX90316_SPIM_RXBUFFERWRITE          (MLX90316_SPIM_rxBufferWrite)

#define MLX90316_SPIM_COUNTER_PERIOD         (MLX90316_SPIM_COUNTER_PERIOD_REG)
#define MLX90316_SPIM_COUNTER_CONTROL        (MLX90316_SPIM_COUNTER_CONTROL_REG)
#define MLX90316_SPIM_STATUS                 (MLX90316_SPIM_TX_STATUS_REG)
#define MLX90316_SPIM_CONTROL                (MLX90316_SPIM_CONTROL_REG)
#define MLX90316_SPIM_STATUS_MASK            (MLX90316_SPIM_TX_STATUS_MASK_REG)
#define MLX90316_SPIM_STATUS_ACTL            (MLX90316_SPIM_TX_STATUS_ACTL_REG)

#define MLX90316_SPIM_INIT_INTERRUPTS_MASK  (MLX90316_SPIM_INT_ON_SPI_DONE     | \
                                                MLX90316_SPIM_INT_ON_TX_EMPTY     | \
                                                MLX90316_SPIM_INT_ON_TX_NOT_FULL_DEF  | \
                                                MLX90316_SPIM_INT_ON_RX_FULL      | \
                                                MLX90316_SPIM_INT_ON_RX_NOT_EMPTY | \
                                                MLX90316_SPIM_INT_ON_RX_OVER      | \
                                                MLX90316_SPIM_INT_ON_BYTE_COMP)
                                                
#define MLX90316_SPIM_DataWidth                  (MLX90316_SPIM_DATA_WIDTH)
#define MLX90316_SPIM_InternalClockUsed          (MLX90316_SPIM_INTERNAL_CLOCK)
#define MLX90316_SPIM_InternalTxInterruptEnabled (MLX90316_SPIM_INTERNAL_TX_INT_ENABLED)
#define MLX90316_SPIM_InternalRxInterruptEnabled (MLX90316_SPIM_INTERNAL_RX_INT_ENABLED)
#define MLX90316_SPIM_ModeUseZero                (MLX90316_SPIM_MODE_USE_ZERO)
#define MLX90316_SPIM_BidirectionalMode          (MLX90316_SPIM_BIDIRECTIONAL_MODE)
#define MLX90316_SPIM_Mode                       (MLX90316_SPIM_MODE)
#define MLX90316_SPIM_DATAWIDHT                  (MLX90316_SPIM_DATA_WIDTH)
#define MLX90316_SPIM_InternalInterruptEnabled   (0u)

#define MLX90316_SPIM_TXBUFFERSIZE   (MLX90316_SPIM_TX_BUFFER_SIZE)
#define MLX90316_SPIM_RXBUFFERSIZE   (MLX90316_SPIM_RX_BUFFER_SIZE)

#define MLX90316_SPIM_TXBUFFER       MLX90316_SPIM_txBuffer
#define MLX90316_SPIM_RXBUFFER       MLX90316_SPIM_rxBuffer

#endif /* (CY_SPIM_MLX90316_SPIM_H) */


/* [] END OF FILE */
