/*******************************************************************************
* File Name: LCD.h
* Version 3.40
*
* Description:
*  This header file contains definitions associated with the Segment LCD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SEGLCD_LCD_H)
#define CY_SEGLCD_LCD_H

#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"
#include <LCD_Int_Clock.h>


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCD_COMM_NUM            (4u)

#define LCD_BIT_MASK            (0x0007u)
#define LCD_BYTE_MASK           (0x00F0u)
#define LCD_ROW_MASK            (0x0F00u)

#define LCD_BYTE_SHIFT          (0x04u)
#define LCD_ROW_SHIFT           (0x08u)

#define LCD__TYPE_A 0
#define LCD__TYPE_B 1


#define LCD_WAVEFORM_TYPE       (1u)

/* Print error if cy_boot version is below 3.0 */
#ifndef CY_PSOC5LP
    #error Component SegLCD_v3_40 requires cy_boot v3.0 or later
#endif /* CY_PSOC5LP */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} LCD_BACKUP_STRUCT;

/* DMA_PROTO_GROUP_NAME=SegLcdPort */
struct LCD_DMA_TD_PROTO_ENTRY
{
	uint8 offset;	/* offset of the first register in this TD */
	uint8 length;	/* length of the register block in this TD */
};

/***************************************
*        Function Prototypes
***************************************/

void    LCD_Init(void) ;
uint8   LCD_Enable(void) ;
uint8   LCD_Start(void) ;
void    LCD_Stop(void) ;
void    LCD_EnableInt(void) ;
void    LCD_DisableInt(void) ;
uint8   LCD_SetBias(uint8 biasLevel) ;
uint8   LCD_WriteInvertState(uint8 invertState) ;
uint8   LCD_ReadInvertState(void) ;
void    LCD_ClearDisplay(void) ;
uint8   LCD_WritePixel(uint16 pixelNumber, uint8 pixelState)
                                                                    ;
uint8   LCD_ReadPixel(uint16 pixelNumber);
void    LCD_Sleep(void) ;
uint8   LCD_Wakeup(void) ;
void    LCD_SaveConfig(void) ;
void    LCD_RestoreConfig(void) ;

#define LCD_7SEG
void    LCD_Write7SegDigit_0(uint8 digit, uint8 position) ;
void    LCD_Write7SegNumber_0(uint16 value, uint8 position, uint8 mode) ;
void    LCD_WriteBargraph_1(uint16 location, int8 mode) ;
CY_ISR_PROTO(LCD_ISR);
CY_ISR_PROTO(LCD_WAKEUP_ISR);

#define LCD_WRITE_PIXEL(pixelNumber,pixelState) (void) LCD_WritePixel(pixelNumber,pixelState)
#define LCD_READ_PIXEL(pixelNumber)             LCD_ReadPixel(pixelNumber)

/* Calculates pixel location in the frame buffer. */
#define LCD_FIND_PIXEL(port, pin, row)          ((uint16)(((((uint16)(row)) << LCD_ROW_SHIFT) + \
                                                             (((uint16)(port)) << LCD_BYTE_SHIFT)) + ((uint16)(pin))))

/* Internal macros that extract pixel information from a pixel number */
#define LCD_EXTRACT_ROW(pixel)                  ((uint8)(((pixel) & LCD_ROW_MASK) >> \
                                                                            LCD_ROW_SHIFT))
#define LCD_EXTRACT_PORT(pixel)                 ((uint8)(((pixel) & LCD_BYTE_MASK) >> \
                                                                            LCD_BYTE_SHIFT))
#define LCD_EXTRACT_PIN(pixel)                  ((uint8)((pixel) & LCD_BIT_MASK))


/***************************************
*           Global Variables
***************************************/

extern uint8 LCD_initVar;


/***************************************
*           API Constants
***************************************/
#if(CY_PSOC3)
    #define LCD_DMA_ADDRESS_MASK          (0x0000FFFFul)
#endif /* (CY_PSOC3) */

#define LCD_LOW_POWER                 (0x01u)

/* Frame buffer row length */
#define LCD_ROW_LENGTH                (0x10u)
#define LCD_BUFFER_LENGTH             (LCD_COMM_NUM * LCD_ROW_LENGTH)

#if(LCD_WAVEFORM_TYPE == LCD__TYPE_A)
    #define LCD_CONTROL_WRITE_COUNT   (0x02u)
#else
    #define LCD_CONTROL_WRITE_COUNT   (2u * LCD_COMM_NUM)
#endif /* (LCD_WAVEFORM_TYPE == LCD__TYPE_A) */

#define LCD_INVERT_BIT_MASK           (0x04u)
#define LCD_INVERT_SHIFT              (0x02u)

#define LCD_LCD_STATE_DISABLED        (0x00u)
#define LCD_LCD_STATE_ENABLED         (0x01u)

#define LCD_NORMAL_STATE              (0x00u)
#define LCD_INVERTED_STATE            (0x01u)
#define LCD_STATE_MASK                (0x01u)

/* Number of pixels for different kind of LCDs */
#define LCD_7SEG_PIX_NUM              (0x07u)
#define LCD_14SEG_PIX_NUM             (0x0Eu)
#define LCD_16SEG_PIX_NUM             (0x10u)
#define LCD_DM_CHAR_HEIGHT            (0x08u)
#define LCD_DM_CHAR_WIDTH             (0x05u)

/* API parameter pixel state constants */
#define LCD_PIXEL_STATE_OFF           (0x00u)
#define LCD_PIXEL_STATE_ON            (0x01u)
#define LCD_PIXEL_STATE_INVERT        (0x02u)
#define LCD_PIXEL_UNKNOWN_STATE       (0xFFu)

/* 0 - No leadig zeros, 1 - leadig zeros */
#define LCD_MODE_0                    (0x00u)
#define LCD_MODE_1                    (0x01u)

#define LCD_MAX_BUFF_ROWS             (0x10u)
#define LCD_ROW_BYTE_LEN              (0x10u)

#define LCD_ISR_NUMBER                ((uint8) LCD_TD_DoneInt__INTC_NUMBER)
#define LCD_ISR_PRIORITY              ((uint8) LCD_TD_DoneInt__INTC_PRIOR_NUM)

#if(CY_PSOC5LP)
    #define LCD_WAKEUP_ISR_NUMBER         ((uint8) LCD_Wakeup__INTC_NUMBER)
    #define LCD_WAKEUP_ISR_PRIORITY       ((uint8) LCD_Wakeup__INTC_PRIOR_NUM)
#endif /* CY_PSOC5LP */

#define LCD_DIGIT_NUM_0            (4u)
#define LCD_DIGIT_NUM_1            (4u)

#define LCD_COM0_PORT            LCD_Com__LCD_COM_PORT__0
#define LCD_COM0_PIN            LCD_Com__LCD_COM_PIN__0
#define LCD_COM1_PORT            LCD_Com__LCD_COM_PORT__1
#define LCD_COM1_PIN            LCD_Com__LCD_COM_PIN__1
#define LCD_COM2_PORT            LCD_Com__LCD_COM_PORT__2
#define LCD_COM2_PIN            LCD_Com__LCD_COM_PIN__2
#define LCD_COM3_PORT            LCD_Com__LCD_COM_PORT__3
#define LCD_COM3_PIN            LCD_Com__LCD_COM_PIN__3

#define LCD_Com0            LCD_FIND_PIXEL(LCD_COM0_PORT,  LCD_COM0_PIN,  0)
#define LCD_Com1            LCD_FIND_PIXEL(LCD_COM1_PORT,  LCD_COM1_PIN,  1)
#define LCD_Com2            LCD_FIND_PIXEL(LCD_COM2_PORT,  LCD_COM2_PIN,  2)
#define LCD_Com3            LCD_FIND_PIXEL(LCD_COM3_PORT,  LCD_COM3_PIN,  3)

#define LCD_SEG0_PORT            LCD_Seg__LCD_SEG_PORT__0
#define LCD_SEG0_PIN            LCD_Seg__LCD_SEG_PIN__0
#define LCD_SEG1_PORT            LCD_Seg__LCD_SEG_PORT__1
#define LCD_SEG1_PIN            LCD_Seg__LCD_SEG_PIN__1
#define LCD_SEG2_PORT            LCD_Seg__LCD_SEG_PORT__2
#define LCD_SEG2_PIN            LCD_Seg__LCD_SEG_PIN__2
#define LCD_SEG3_PORT            LCD_Seg__LCD_SEG_PORT__3
#define LCD_SEG3_PIN            LCD_Seg__LCD_SEG_PIN__3
#define LCD_SEG4_PORT            LCD_Seg__LCD_SEG_PORT__4
#define LCD_SEG4_PIN            LCD_Seg__LCD_SEG_PIN__4
#define LCD_SEG5_PORT            LCD_Seg__LCD_SEG_PORT__5
#define LCD_SEG5_PIN            LCD_Seg__LCD_SEG_PIN__5
#define LCD_SEG6_PORT            LCD_Seg__LCD_SEG_PORT__6
#define LCD_SEG6_PIN            LCD_Seg__LCD_SEG_PIN__6
#define LCD_SEG7_PORT            LCD_Seg__LCD_SEG_PORT__7
#define LCD_SEG7_PIN            LCD_Seg__LCD_SEG_PIN__7

#define LCD_H7SEG0_A            LCD_FIND_PIXEL(LCD_SEG1_PORT,  LCD_SEG1_PIN,  3)
#define LCD_H7SEG0_B            LCD_FIND_PIXEL(LCD_SEG1_PORT,  LCD_SEG1_PIN,  2)
#define LCD_H7SEG0_C            LCD_FIND_PIXEL(LCD_SEG1_PORT,  LCD_SEG1_PIN,  1)
#define LCD_H7SED0_D            LCD_FIND_PIXEL(LCD_SEG0_PORT,  LCD_SEG0_PIN,  0)
#define LCD_H7SEG0_E            LCD_FIND_PIXEL(LCD_SEG0_PORT,  LCD_SEG0_PIN,  1)
#define LCD_H7SEG0_F            LCD_FIND_PIXEL(LCD_SEG0_PORT,  LCD_SEG0_PIN,  3)
#define LCD_H7SEG0_G            LCD_FIND_PIXEL(LCD_SEG0_PORT,  LCD_SEG0_PIN,  2)
#define LCD_H7SEG1_A            LCD_FIND_PIXEL(LCD_SEG3_PORT,  LCD_SEG3_PIN,  3)
#define LCD_H7SEG1_B            LCD_FIND_PIXEL(LCD_SEG3_PORT,  LCD_SEG3_PIN,  2)
#define LCD_H7SEG1_C            LCD_FIND_PIXEL(LCD_SEG3_PORT,  LCD_SEG3_PIN,  1)
#define LCD_H7SEG1_D            LCD_FIND_PIXEL(LCD_SEG2_PORT,  LCD_SEG2_PIN,  0)
#define LCD_H7SEG1_E            LCD_FIND_PIXEL(LCD_SEG2_PORT,  LCD_SEG2_PIN,  1)
#define LCD_H7SEG1_F            LCD_FIND_PIXEL(LCD_SEG2_PORT,  LCD_SEG2_PIN,  3)
#define LCD_H7SEG1_G            LCD_FIND_PIXEL(LCD_SEG2_PORT,  LCD_SEG2_PIN,  2)
#define LCD_H7SEG2_A            LCD_FIND_PIXEL(LCD_SEG5_PORT,  LCD_SEG5_PIN,  3)
#define LCD_H7SEG2_B            LCD_FIND_PIXEL(LCD_SEG5_PORT,  LCD_SEG5_PIN,  2)
#define LCD_H7SEG2_C            LCD_FIND_PIXEL(LCD_SEG5_PORT,  LCD_SEG5_PIN,  1)
#define LCD_H7SEG2_D            LCD_FIND_PIXEL(LCD_SEG4_PORT,  LCD_SEG4_PIN,  0)
#define LCD_H7SEG2_E            LCD_FIND_PIXEL(LCD_SEG4_PORT,  LCD_SEG4_PIN,  1)
#define LCD_H7SEG2_F            LCD_FIND_PIXEL(LCD_SEG4_PORT,  LCD_SEG4_PIN,  3)
#define LCD_H7SEG2_G            LCD_FIND_PIXEL(LCD_SEG4_PORT,  LCD_SEG4_PIN,  2)
#define LCD_H7SEG3_A            LCD_FIND_PIXEL(LCD_SEG7_PORT,  LCD_SEG7_PIN,  3)
#define LCD_H7SEG3_B            LCD_FIND_PIXEL(LCD_SEG7_PORT,  LCD_SEG7_PIN,  2)
#define LCD_H7SEG3_C            LCD_FIND_PIXEL(LCD_SEG7_PORT,  LCD_SEG7_PIN,  1)
#define LCD_H7SEG3_D            LCD_FIND_PIXEL(LCD_SEG6_PORT,  LCD_SEG6_PIN,  0)
#define LCD_H7SEG3_E            LCD_FIND_PIXEL(LCD_SEG6_PORT,  LCD_SEG6_PIN,  1)
#define LCD_H7SEG3_F            LCD_FIND_PIXEL(LCD_SEG6_PORT,  LCD_SEG6_PIN,  3)
#define LCD_H7SEG3_G            LCD_FIND_PIXEL(LCD_SEG6_PORT,  LCD_SEG6_PIN,  2)
#define LCD_DP0            LCD_FIND_PIXEL(LCD_SEG1_PORT,  LCD_SEG1_PIN,  0)
#define LCD_DP1            LCD_FIND_PIXEL(LCD_SEG3_PORT,  LCD_SEG3_PIN,  0)
#define LCD_DP2            LCD_FIND_PIXEL(LCD_SEG5_PORT,  LCD_SEG5_PIN,  0)
#define LCD_COLON            LCD_FIND_PIXEL(LCD_SEG7_PORT,  LCD_SEG7_PIN,  0)


#define LCD_NOT_CON            (0xFFFFu)
#define LCD_SegLcdPort_DMA_TD_PROTO_COUNT 1

#define LCD_LCD_TD_SIZE               ((uint8) LCD_SegLcdPort_DMA_TD_PROTO_COUNT)

#define LCD_COM_TD_COUNT              ((uint8) \
                                                   ((LCD_COMM_NUM * LCD_LCD_TD_SIZE) - 1u))

#define LCD_MODE_MASK                 (0x06u)

/* Defines index of "blank" didgit in the look-up table for 7 segment helper */
#define LCD_7SEG_BLANK_DIG            (0x10u)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define LCD__NO_SLEEP 0
#define LCD__LOW_POWER_32XTAL 2
#define LCD__LOW_POWER_ILO 1


/***************************************
*    Initial Parameter Constants
***************************************/

#define LCD_SEG_NUM               (8u)
#define LCD_BIAS_TYPE             (0u)
#define LCD_BIAS_VOLTAGE          (63u)
#define LCD_POWER_MODE            (0u)
#define LCD_FRAME_RATE            (60u)
#define LCD_HI_DRIVE_TIME         (2u)
#define LCD_LOW_DRIVE_TIME        (252u)
#define LCD_HIDRIVE_STRENGTH      (1u)
#define LCD_LOWDRIVE_STRENGTH     (0u)

#if(LCD_POWER_MODE == LCD__NO_SLEEP)
    #define LCD_DRIVE_TIME        ((LCD_LOW_DRIVE_TIME + LCD_HI_DRIVE_TIME) - 1u)
#else
    #define LCD_DRIVE_TIME        (LCD_HI_DRIVE_TIME)
#endif /* LCD_POWER_MODE == LCD__NO_SLEEP */

#if(LCD_POWER_MODE == LCD__NO_SLEEP)

    /* Set PWM period for 255 in NoSleep mode */
    #define LCD_PWM_PERIOD_VAL        (0xFFu)
    /* D0 = 255 - HiDrive time */
    #define LCD_PWM_DRIVE_VAL        ((LCD_PWM_PERIOD_VAL) - (LCD_HI_DRIVE_TIME))
    /* D1 = 255 - Drive time */
    #define LCD_PWM_LOWDRIVE_VAL     ((LCD_PWM_PERIOD_VAL) - (LCD_DRIVE_TIME))

#else

    /* PWM period will be equal to 0 */
    #define LCD_PWM_PERIOD_VAL        (0x00u)
    /* D0 is equal to HiDrive time, as it used as period reg for Low Power mode */
    #define LCD_PWM_DRIVE_VAL         (LCD_HI_DRIVE_TIME - 1u)
    /* Make sure D1 is 0 */
    #define LCD_PWM_LOWDRIVE_VAL      (0x00u)

#endif /* LCD_POWER_MODE == LCD__NO_SLEEP */


/***************************************
*             Registers
***************************************/

/* LCD's fixed block registers */
#define LCD_LCDDAC_CONTROL_REG       (* (reg8*) LCD_LCD__CR0)
#define LCD_LCDDAC_CONTROL_PTR       ((reg8*) LCD_LCD__CR0)
#define LCD_CONTRAST_CONTROL_REG     (* (reg8*) LCD_LCD__CR1)
#define LCD_CONTRAST_CONTROL_PTR     ((reg8*) LCD_LCD__CR1)
#define LCD_DRIVER_CONTROL_REG       (* (reg8*)LCD_LCD__CR)
#define LCD_DRIVER_CONTROL_PTR       ((reg8*)LCD_LCD__CR)
#define LCD_TIMER_CONTROL_REG        (* (reg8*) LCD_LCD__CFG)
#define LCD_TIMER_CONTROL_PTR        ((reg8*) LCD_LCD__CFG)
#define LCD_ALIASED_AREA_PTR         ((reg32) CYREG_PRT0_DR_ALIAS)
#define LCD_PWR_MGR_REG              (* (reg8 *) LCD_LCD__PM_ACT_CFG)
#define LCD_PWR_MGR_PTR              ((reg8 *) LCD_LCD__PM_ACT_CFG)
#define LCD_PWR_MGR_STBY_REG         (* (reg8 *) LCD_LCD__PM_STBY_CFG)
#define LCD_PWR_MGR_STBY_PTR         ((reg8 *) LCD_LCD__PM_STBY_CFG)

#if(LCD_POWER_MODE == LCD__LOW_POWER_32XTAL)
    #define LCD_TM_WL_GFG_REG         (*(reg8 *) CYREG_PM_TW_CFG2)
    #define LCD_TM_WL_GFG_PTR         ((reg8 *) CYREG_PM_TW_CFG2)
#endif /* LCD_POWER_MODE == LCD__LOW_POWER_32XTAL */

#define LCD_LCDDAC_SWITCH_REG0_REG   (* (reg8*)LCD_LCD__SW0)
#define LCD_LCDDAC_SWITCH_REG1_REG   (* (reg8*)LCD_LCD__SW1)
#define LCD_LCDDAC_SWITCH_REG2_REG   (* (reg8*)LCD_LCD__SW2)
#define LCD_LCDDAC_SWITCH_REG3_REG   (* (reg8*)LCD_LCD__SW3)
#define LCD_LCDDAC_SWITCH_REG4_REG   (* (reg8*)LCD_LCD__SW4)

#define LCD_LCDDAC_SWITCH_REG0_PTR   ((reg8*)LCD_LCD__SW0)
#define LCD_LCDDAC_SWITCH_REG1_PTR   ((reg8*)LCD_LCD__SW1)
#define LCD_LCDDAC_SWITCH_REG2_PTR   ((reg8*)LCD_LCD__SW2)
#define LCD_LCDDAC_SWITCH_REG3_PTR   ((reg8*)LCD_LCD__SW3)
#define LCD_LCDDAC_SWITCH_REG4_PTR   ((reg8*)LCD_LCD__SW4)

/* UDB registers */
#if(LCD_POWER_MODE == LCD__NO_SLEEP)
    #define LCD_PWM_PERIOD_REG         (* (reg8 *) LCD_bLCDDSD_NoSleep_bSegLCDdp_u0__A1_REG)
    #define LCD_PWM_PERIOD_PTR         ((reg8 *) LCD_bLCDDSD_NoSleep_bSegLCDdp_u0__A1_REG)
    #define LCD_PWM_DRIVE_REG          (* (reg8 *) LCD_bLCDDSD_NoSleep_bSegLCDdp_u0__D0_REG)
    #define LCD_PWM_DRIVE_PTR          ((reg8 *) LCD_bLCDDSD_NoSleep_bSegLCDdp_u0__D0_REG)
    #define LCD_PWM_LODRIVE_REG        (* (reg8 *) LCD_bLCDDSD_NoSleep_bSegLCDdp_u0__D1_REG)
    #define LCD_PWM_LODRIVE_PTR        ((reg8 *) LCD_bLCDDSD_NoSleep_bSegLCDdp_u0__D1_REG)
#else
    #define LCD_PWM_PERIOD_REG         (* (reg8 *) LCD_bLCDDSD_LowPower_bSegLCDdp_u0__A1_REG)
    #define LCD_PWM_PERIOD_PTR         ((reg8 *) LCD_bLCDDSD_LowPower_bSegLCDdp_u0__A1_REG)
    #define LCD_PWM_DRIVE_REG          (* (reg8 *) LCD_bLCDDSD_LowPower_bSegLCDdp_u0__D0_REG)
    #define LCD_PWM_DRIVE_PTR          ((reg8 *) LCD_bLCDDSD_LowPower_bSegLCDdp_u0__D0_REG)
    #define LCD_PWM_LODRIVE_REG        (* (reg8 *) LCD_bLCDDSD_LowPower_bSegLCDdp_u0__D1_REG)
    #define LCD_PWM_LODRIVE_PTR        ((reg8 *) LCD_bLCDDSD_LowPower_bSegLCDdp_u0__D1_REG)
#endif /* LCD_POWER_MODE == LCD__NO_SLEEP */

#define LCD_CONTROL_REG                (* (reg8 *) LCD_bLCDDSD_CtrlReg__CONTROL_REG)
#define LCD_CONTROL_PTR                ((reg8 *) LCD_bLCDDSD_CtrlReg__CONTROL_REG)

/* This is required for DmaInitialize() fou usage as a
* base destination address of conrol register. 
*/
#define LCD_CONTROL_REG_BASE           (CYDEV_PERIPH_BASE)

/***************************************
*       Register Constants
***************************************/

/* PM Control Register bits */
#define LCD_LCD_EN                    (LCD_LCD__PM_ACT_MSK)
#define LCD_LCD_STBY_EN               (LCD_LCD__PM_STBY_MSK)

/* LCD DAC Control Register Bits */
#define LCD_LCDDAC_UDB_LP_EN          (0x80u)
#define LCD_LCDDAC_CONT_DRIVE         (0x08u)
#define LCD_BIAS_TYPE_MASK            (0x03u)

#define LCD_LCDDAC_VOLTAGE_SEL        (0x01u)
#define LCD_LCDDAC_CONT_DRIVE         (0x08u)
#define LCD_LCDDAC_CONT_DRIVE_MASK    (~0x08u)

/* LCD Driver Control Register Bits */
#define LCD_LCDDRV_DISPLAY_BLNK       (0x01u)
#define LCD_LCDDRV_MODE0_MASK         (0x02u)
#define LCD_LCDDRV_MODE0_SHIFT        (0x01u)
#define LCD_LCDDRV_INVERT             (0x04u)
#define LCD_LCDDRV_PTS                (0x08u)
#define LCD_LCDDRV_BYPASS_EN          (0x10u)

#if(LCD_POWER_MODE == LCD__LOW_POWER_32XTAL)
    #define LCD_ONE_PPS_EN            (0x10u)
#endif /* LCD_POWER_MODE == LCD__LOW_POWER_32XTAL */

#if(LCD_POWER_MODE != LCD__NO_SLEEP)

    /* LCD Timer Control Register Bits */
    #define LCD_TIMER_EN                  (0x01u)
    #define LCD_TIMER_ILO_SEL             (0x00u)
    #define LCD_TIMER_32XTAL_SEL          (0x02u)
    #define LCD_TIMER_CLK_SEL_MASK        (0x02u)
    #define LCD_TIMER_PERIOD_MASK         (0xFCu)
    #define LCD_TIMER_PERIOD_SHIFT        (0x02u)

    #define LCD_TIMER_PERIOD              (10u)

#endif /* LCD_POWER_MODE != LCD__NO_SLEEP */

/* UDB Control Register bits */
#define LCD_CNTL_CLK_EN               (0x01u)
#define LCD_CNTL_CLK_EN_MASK          (~LCD_CNTL_CLK_EN)
#define LCD_CNTL_MODE_SHIFT           (0x01u)
#define LCD_CNTL_MODE_MASK            (~0x06u)
#define LCD_CNTL_FRAME_DONE           (0x08u)
#define LCD_CNTL_FRAME_DONE_MASK      (~LCD_CNTL_FRAME_DONE)


#endif  /* CY_SEGLCD_LCD_H */

/* [] END OF FILE */
