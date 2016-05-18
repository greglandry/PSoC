/*******************************************************************************
* File Name: LCD.h
* Version 1.30
*
* Description:
*  This file provides constants and parameter values for the Segment LCD
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SegLCD_P4_LCD_H)
#define CY_SegLCD_P4_LCD_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define LCD_SUBFR_DIV                (0x0138u)
#define LCD_DEAD_DIV                 (0x2D93u)
#define LCD_LCD_MODE                 (1u)
#define LCD_WAVEFORM_TYPE            (1u)
#define LCD_DRIVING_MODE             (1u)
#define LCD_BIAS                     (0u)
#define LCD_COM_NUM                  (4u)
#define LCD_CONTRAST                 (30u)

#define LCD_BUFFER_LENGTH            (0x05u)


/***************************************
*        Function Prototypes
***************************************/

void    LCD_Init(void);
void    LCD_Enable(void);
void    LCD_Start(void);
void    LCD_Stop(void);
void    LCD_SetSpeedMode(uint32 mode);
void    LCD_SetOperationMode(uint32 mode);
void    LCD_SetBiasType(uint32 bias);
void    LCD_SetWaveformType(uint32 type);
uint32  LCD_SetContrast(uint32 contrast);
void    LCD_WriteInvertState(uint32 invertState);
uint32  LCD_ReadInvertState(void);
void    LCD_ClearDisplay(void);
uint32  LCD_WritePixel(uint32 pixelNumber, uint32 pixelState);
uint32  LCD_ReadPixel(uint32 pixelNumber);
void    LCD_Sleep(void);
void    LCD_Wakeup(void);
void    LCD_SaveConfig(void);
void    LCD_RestoreConfig(void);

void    LCD_Write7SegDigit_0(uint32 digit, uint32 position);
void    LCD_Write7SegNumber_0(uint32 value, uint32 position, uint32 mode);
void    LCD_WriteBargraph_1(uint32 location, int32 mode);

#define LCD_7SEG

/* Calculates pixel location in the frame buffer. */
#define LCD_FIND_PIXEL(port, pin, row)    (((uint32)((uint32)(row) << LCD_ROW_SHIFT)) | \
                                   ((uint32)((uint32)(port) << LCD_BYTE_SHIFT)) | ((uint32)(pin)))

/* Internal macros that extract pixel information from a pixel number */
#define LCD_EXTRACT_ROW(pixel)       ((uint32)(((pixel) & LCD_ROW_MASK) >> \
                                                                      LCD_ROW_SHIFT))
#define LCD_EXTRACT_PORT(pixel)      ((uint32)(((pixel) & LCD_BYTE_MASK) >> \
                                                                      LCD_BYTE_SHIFT))
#define LCD_EXTRACT_PIN(pixel)       ((uint32)((pixel) & LCD_BIT_MASK))


/***************************************
*           Global Variables
***************************************/

extern uint32 LCD_initVar;


/***************************************
*           API Constants
***************************************/

#define LCD_NOT_CON                  (0xFFFFu)

#define LCD_MAX_CONTRAST             (100u)
#define LCD_MIN_CONTRAST             (10u)
#define LCD_CONTRAST_DIVIDERS_NUMBER (10u)

#define LCD_ROW_SHIFT                (0x10u)
#define LCD_ROW_MASK                 ((uint32)((uint32)0xFFu << LCD_ROW_SHIFT))
#define LCD_BYTE_SHIFT               (0x08u)
#define LCD_BYTE_MASK                ((uint32)((uint32)0xFFu << LCD_BYTE_SHIFT))
#define LCD_BIT_SHIFT                (0x00u)
#define LCD_BIT_MASK                 ((uint32)((uint32)0xFFu << LCD_BIT_SHIFT))

#define LCD_ENABLE_MASK              ((uint32)0x03u)
#define LCD_SPEED_LS                 (0x00u)
#define LCD_SPEED_HS                 (0x01u)
#define LCD_MODE_PWM                 (0x00u)
#define LCD_MODE_DIG_COR             (0x01u)
#define LCD_BIAS_1_2                 (0x00u)
#define LCD_BIAS_1_3                 (0x01u)
#define LCD_BIAS_1_4                 (0x02u)
#define LCD_BIAS_1_5                 (0x03u)
#define LCD_TYPE_A                   (0x00u)
#define LCD_TYPE_B                   (0x01u)

#define LCD_STATE_NORMAL             (0x00u)
#define LCD_STATE_INVERTED           (0x01u)

/* Number of pixels for different kind of LCDs */
#define LCD_7SEG_PIX_NUM             (0x07u)
#define LCD_14SEG_PIX_NUM            (0x0Eu)
#define LCD_16SEG_PIX_NUM            (0x10u)
#define LCD_DM_CHAR_HEIGHT           (0x08u)
#define LCD_DM_CHAR_WIDTH            (0x05u)

/* API parameter pixel state constants */
#define LCD_PIXEL_STATE_OFF          ((uint32)0x00u)
#define LCD_PIXEL_STATE_ON           ((uint32)0x01u)
#define LCD_PIXEL_STATE_INVERT       ((uint32)0x02u)
#define LCD_PIXEL_UNKNOWN_STATE      ((uint32)0xFFu)

/* 0 - No leading zeros, 1 - leading zeros */
#define LCD_NO_LEADING_ZEROES        (0x00u)
#define LCD_LEADING_ZEROES           (0x01u)

#define LCD_DEAD_DIVS                (0x00u)
#define LCD_SUBFR_DIVS               (0x01u)

#define LCD_MAX_BUFF_ROWS            (0x04u)

#define LCD_PINS_PER_PORT            (0x08u)

/* Defines index of "blank" digit in the look-up table for 7 segment helper */
#define LCD_7SEG_BLANK_DIG           (0x10u)

#define LCD_DIGIT_NUM_0              (4u)
#define LCD_DIGIT_NUM_1              (4u)

#define LCD_COM0_PORT                (LCD_bSeg_LCD__COMMON_0 / LCD_PINS_PER_PORT)
#define LCD_COM0_PIN                 (LCD_bSeg_LCD__COMMON_0 % LCD_PINS_PER_PORT)
#define LCD_COM1_PORT                (LCD_bSeg_LCD__COMMON_1 / LCD_PINS_PER_PORT)
#define LCD_COM1_PIN                 (LCD_bSeg_LCD__COMMON_1 % LCD_PINS_PER_PORT)
#define LCD_COM2_PORT                (LCD_bSeg_LCD__COMMON_2 / LCD_PINS_PER_PORT)
#define LCD_COM2_PIN                 (LCD_bSeg_LCD__COMMON_2 % LCD_PINS_PER_PORT)
#define LCD_COM3_PORT                (LCD_bSeg_LCD__COMMON_3 / LCD_PINS_PER_PORT)
#define LCD_COM3_PIN                 (LCD_bSeg_LCD__COMMON_3 % LCD_PINS_PER_PORT)

#define LCD_Com0                     LCD_FIND_PIXEL(LCD_COM0_PORT,  LCD_COM0_PIN,  0u)
#define LCD_Com1                     LCD_FIND_PIXEL(LCD_COM1_PORT,  LCD_COM1_PIN,  1u)
#define LCD_Com2                     LCD_FIND_PIXEL(LCD_COM2_PORT,  LCD_COM2_PIN,  2u)
#define LCD_Com3                     LCD_FIND_PIXEL(LCD_COM3_PORT,  LCD_COM3_PIN,  3u)

#define LCD_SEG0_PORT                (LCD_bSeg_LCD__SEGMENT_0 / LCD_PINS_PER_PORT)
#define LCD_SEG0_PIN                 (LCD_bSeg_LCD__SEGMENT_0 % LCD_PINS_PER_PORT)
#define LCD_SEG1_PORT                (LCD_bSeg_LCD__SEGMENT_1 / LCD_PINS_PER_PORT)
#define LCD_SEG1_PIN                 (LCD_bSeg_LCD__SEGMENT_1 % LCD_PINS_PER_PORT)
#define LCD_SEG2_PORT                (LCD_bSeg_LCD__SEGMENT_2 / LCD_PINS_PER_PORT)
#define LCD_SEG2_PIN                 (LCD_bSeg_LCD__SEGMENT_2 % LCD_PINS_PER_PORT)
#define LCD_SEG3_PORT                (LCD_bSeg_LCD__SEGMENT_3 / LCD_PINS_PER_PORT)
#define LCD_SEG3_PIN                 (LCD_bSeg_LCD__SEGMENT_3 % LCD_PINS_PER_PORT)
#define LCD_SEG4_PORT                (LCD_bSeg_LCD__SEGMENT_4 / LCD_PINS_PER_PORT)
#define LCD_SEG4_PIN                 (LCD_bSeg_LCD__SEGMENT_4 % LCD_PINS_PER_PORT)
#define LCD_SEG5_PORT                (LCD_bSeg_LCD__SEGMENT_5 / LCD_PINS_PER_PORT)
#define LCD_SEG5_PIN                 (LCD_bSeg_LCD__SEGMENT_5 % LCD_PINS_PER_PORT)
#define LCD_SEG6_PORT                (LCD_bSeg_LCD__SEGMENT_6 / LCD_PINS_PER_PORT)
#define LCD_SEG6_PIN                 (LCD_bSeg_LCD__SEGMENT_6 % LCD_PINS_PER_PORT)
#define LCD_SEG7_PORT                (LCD_bSeg_LCD__SEGMENT_7 / LCD_PINS_PER_PORT)
#define LCD_SEG7_PIN                 (LCD_bSeg_LCD__SEGMENT_7 % LCD_PINS_PER_PORT)

#define LCD_H7SEG0_A                 LCD_FIND_PIXEL(LCD_SEG1_PORT, LCD_SEG1_PIN, 3u)
#define LCD_H7SEG0_B                 LCD_FIND_PIXEL(LCD_SEG1_PORT, LCD_SEG1_PIN, 2u)
#define LCD_H7SEG0_C                 LCD_FIND_PIXEL(LCD_SEG1_PORT, LCD_SEG1_PIN, 1u)
#define LCD_H7SEG0_D                 LCD_FIND_PIXEL(LCD_SEG0_PORT, LCD_SEG0_PIN, 0u)
#define LCD_H7SEG0_E                 LCD_FIND_PIXEL(LCD_SEG0_PORT, LCD_SEG0_PIN, 1u)
#define LCD_H7SEG0_F                 LCD_FIND_PIXEL(LCD_SEG0_PORT, LCD_SEG0_PIN, 3u)
#define LCD_H7SEG0_G                 LCD_FIND_PIXEL(LCD_SEG0_PORT, LCD_SEG0_PIN, 2u)
#define LCD_H7SEG1_A                 LCD_FIND_PIXEL(LCD_SEG3_PORT, LCD_SEG3_PIN, 3u)
#define LCD_H7SEG1_B                 LCD_FIND_PIXEL(LCD_SEG3_PORT, LCD_SEG3_PIN, 2u)
#define LCD_H7SEG1_C                 LCD_FIND_PIXEL(LCD_SEG3_PORT, LCD_SEG3_PIN, 1u)
#define LCD_H7SEG1_D                 LCD_FIND_PIXEL(LCD_SEG2_PORT, LCD_SEG2_PIN, 0u)
#define LCD_H7SEG1_E                 LCD_FIND_PIXEL(LCD_SEG2_PORT, LCD_SEG2_PIN, 1u)
#define LCD_H7SEG1_F                 LCD_FIND_PIXEL(LCD_SEG2_PORT, LCD_SEG2_PIN, 3u)
#define LCD_H7SEG1_G                 LCD_FIND_PIXEL(LCD_SEG2_PORT, LCD_SEG2_PIN, 2u)
#define LCD_H7SEG2_A                 LCD_FIND_PIXEL(LCD_SEG5_PORT, LCD_SEG5_PIN, 3u)
#define LCD_H7SEG2_B                 LCD_FIND_PIXEL(LCD_SEG5_PORT, LCD_SEG5_PIN, 2u)
#define LCD_H7SEG2_C                 LCD_FIND_PIXEL(LCD_SEG5_PORT, LCD_SEG5_PIN, 1u)
#define LCD_H7SEG2_D                 LCD_FIND_PIXEL(LCD_SEG4_PORT, LCD_SEG4_PIN, 0u)
#define LCD_H7SEG2_E                 LCD_FIND_PIXEL(LCD_SEG4_PORT, LCD_SEG4_PIN, 1u)
#define LCD_H7SEG2_F                 LCD_FIND_PIXEL(LCD_SEG4_PORT, LCD_SEG4_PIN, 3u)
#define LCD_H7SEG2_G                 LCD_FIND_PIXEL(LCD_SEG4_PORT, LCD_SEG4_PIN, 2u)
#define LCD_H7SEG3_A                 LCD_FIND_PIXEL(LCD_SEG7_PORT, LCD_SEG7_PIN, 3u)
#define LCD_H7SEG3_B                 LCD_FIND_PIXEL(LCD_SEG7_PORT, LCD_SEG7_PIN, 2u)
#define LCD_H7SEG3_C                 LCD_FIND_PIXEL(LCD_SEG7_PORT, LCD_SEG7_PIN, 1u)
#define LCD_H7SEG3_D                 LCD_FIND_PIXEL(LCD_SEG6_PORT, LCD_SEG6_PIN, 0u)
#define LCD_H7SEG3_E                 LCD_FIND_PIXEL(LCD_SEG6_PORT, LCD_SEG6_PIN, 1u)
#define LCD_H7SEG3_F                 LCD_FIND_PIXEL(LCD_SEG6_PORT, LCD_SEG6_PIN, 3u)
#define LCD_H7SEG3_G                 LCD_FIND_PIXEL(LCD_SEG6_PORT, LCD_SEG6_PIN, 2u)
#define LCD_DP1                      LCD_FIND_PIXEL(LCD_SEG1_PORT, LCD_SEG1_PIN, 0u)
#define LCD_DP2                      LCD_FIND_PIXEL(LCD_SEG3_PORT, LCD_SEG3_PIN, 0u)
#define LCD_DP3                      LCD_FIND_PIXEL(LCD_SEG5_PORT, LCD_SEG5_PIN, 0u)
#define LCD_COLON                    LCD_FIND_PIXEL(LCD_SEG7_PORT, LCD_SEG7_PIN, 0u)


/***************************************
*    Enumerated Types and Parameters
***************************************/


/***************************************
*    Initial Parameter Constants
***************************************/


/***************************************
*             Registers
***************************************/

/* LCD's fixed block registers */
#define LCD_DIVIDER_REG              (*(reg32*) CYREG_LCD_DIVIDER)
#define LCD_DIVIDER_PTR              ((reg32*) CYREG_LCD_DIVIDER)
#define LCD_CONTROL_REG              (*(reg32*) CYREG_LCD_CONTROL)
#define LCD_CONTROL_PTR              ((reg32*) CYREG_LCD_CONTROL)
#define LCD_DATA0_REG                (*(reg32*) CYREG_LCD_DATA00)
#define LCD_DATA0_PTR                ((reg32*) CYREG_LCD_DATA00)
#define LCD_DATA1_REG                (*(reg32*) CYREG_LCD_DATA01)
#define LCD_DATA1_PTR                ((reg32*) CYREG_LCD_DATA01)
#define LCD_DATA2_REG                (*(reg32*) CYREG_LCD_DATA02)
#define LCD_DATA2_PTR                ((reg32*) CYREG_LCD_DATA02)
#define LCD_DATA3_REG                (*(reg32*) CYREG_LCD_DATA03)
#define LCD_DATA3_PTR                ((reg32*) CYREG_LCD_DATA03)
#define LCD_DATA4_REG                (*(reg32*) CYREG_LCD_DATA04)
#define LCD_DATA4_PTR                ((reg32*) CYREG_LCD_DATA04)
#define LCD_DATA5_REG                (*(reg32*) CYREG_LCD_DATA05)
#define LCD_DATA5_PTR                ((reg32*) CYREG_LCD_DATA05)
#define LCD_DATA6_REG                (*(reg32*) CYREG_LCD_DATA06)
#define LCD_DATA6_PTR                ((reg32*) CYREG_LCD_DATA06)
#define LCD_DATA7_REG                (*(reg32*) CYREG_LCD_DATA07)
#define LCD_DATA7_PTR                ((reg32*) CYREG_LCD_DATA07)
#define LCD_DATA10_REG               (*(reg32*) CYREG_LCD_DATA10)
#define LCD_DATA10_PTR               ((reg32*) CYREG_LCD_DATA10)
#define LCD_DATA11_REG               (*(reg32*) CYREG_LCD_DATA11)
#define LCD_DATA11_PTR               ((reg32*) CYREG_LCD_DATA11)
#define LCD_DATA12_REG               (*(reg32*) CYREG_LCD_DATA12)
#define LCD_DATA12_PTR               ((reg32*) CYREG_LCD_DATA12)
#define LCD_DATA13_REG               (*(reg32*) CYREG_LCD_DATA13)
#define LCD_DATA13_PTR               ((reg32*) CYREG_LCD_DATA13)
#define LCD_DATA14_REG               (*(reg32*) CYREG_LCD_DATA14)
#define LCD_DATA14_PTR               ((reg32*) CYREG_LCD_DATA14)
#define LCD_DATA15_REG               (*(reg32*) CYREG_LCD_DATA15)
#define LCD_DATA15_PTR               ((reg32*) CYREG_LCD_DATA15)
#define LCD_DATA16_REG               (*(reg32*) CYREG_LCD_DATA16)
#define LCD_DATA16_PTR               ((reg32*) CYREG_LCD_DATA16)
#define LCD_DATA17_REG               (*(reg32*) CYREG_LCD_DATA17)
#define LCD_DATA17_PTR               ((reg32*) CYREG_LCD_DATA17)


/***************************************
*       Register Constants
***************************************/

/* Offset between LCD Pin Data Registers for different Commons (0x0100) divided by number of byte in one Register (4) */
#define LCD_DATA_REGS_OFFSET         (64u)

/* Divider Register bits */
#define LCD_SUBFR_DIV_MASK_SHIFT     (0x00u)
#define LCD_DEAD_DIV_MASK_SHIFT      (0x10u)

#define LCD_SUBFR_DIV_MASK           ((uint32)((uint32)0xFFFFu << LCD_SUBFR_DIV_MASK_SHIFT))
#define LCD_DEAD_DIV_MASK            ((uint32)((uint32)0xFFFFu << LCD_DEAD_DIV_MASK_SHIFT))
#define LCD_DIVIDER_MASK             (LCD_DEAD_DIV_MASK | LCD_SUBFR_DIV_MASK)

#define LCD_SUBFR_DIVIDER            ((uint32)((uint32)LCD_SUBFR_DIV << \
                                                                    LCD_SUBFR_DIV_MASK_SHIFT))
#define LCD_DEAD_DIVIDER             ((uint32)((uint32)LCD_DEAD_DIV << \
                                                                    LCD_DEAD_DIV_MASK_SHIFT))
#define LCD_INIT_DIVIDERS            (LCD_SUBFR_DIVIDER | LCD_DEAD_DIVIDER)

/* Control Register bits */
#define LCD_LS_EN_SHIFT              (0x00u)
#define LCD_HS_EN_SHIFT              (0x01u)
#define LCD_MODE_SHIFT               (0x02u)
#define LCD_TYPE_SHIFT               (0x03u)
#define LCD_OP_MODE_SHIFT            (0x04u)
#define LCD_BIAS_MASK_SHIFT          (0x05u)
#define LCD_COM_NUM_MASK_SHIFT       (0x08u)
#define LCD_LS_EN_STAT_SHIFT         (0x1Fu)

#define LCD_LS_EN                    ((uint32)((uint32)0x01u << LCD_LS_EN_SHIFT))
#define LCD_HS_EN                    ((uint32)((uint32)0x01u << LCD_HS_EN_SHIFT))
#define LCD_MODE                     ((uint32)((uint32)0x01u << LCD_MODE_SHIFT))
#define LCD_TYPE                     ((uint32)((uint32)0x01u << LCD_TYPE_SHIFT))
#define LCD_OP_MODE                  ((uint32)((uint32)0x01u << LCD_OP_MODE_SHIFT))
#define LCD_BIAS_MASK                ((uint32)((uint32)0x03u << LCD_BIAS_MASK_SHIFT))
#define LCD_COM_NUM_MASK             ((uint32)((uint32)0x0Fu << LCD_COM_NUM_MASK_SHIFT))
#define LCD_LS_EN_STAT               ((uint32)((uint32)0x01u << LCD_LS_EN_STAT_SHIFT))
#define LCD_CONFIG_MASK              ((uint32)(~(LCD_MODE | LCD_TYPE | \
                                                   LCD_OP_MODE | LCD_BIAS_MASK | \
                                                   LCD_COM_NUM_MASK)))

#define LCD_LCD_SPEED_MODE           ((uint32)((uint32)LCD_LCD_MODE << \
                                                                    LCD_MODE_SHIFT))
#define LCD_WAVEFORMS_TYPE           ((uint32)((uint32)LCD_WAVEFORM_TYPE << \
                                                                    LCD_TYPE_SHIFT))
#define LCD_DRIVING_OP_MODE          ((uint32)((uint32)LCD_DRIVING_MODE << \
                                                                    LCD_OP_MODE_SHIFT))
#define LCD_PWM_BIAS                 ((uint32)((uint32)LCD_BIAS << \
                                                                    LCD_BIAS_MASK_SHIFT))
#define LCD_COM_NUMBER               ((uint32)((uint32)(LCD_COM_NUM - 2u) << \
                                                                     LCD_COM_NUM_MASK_SHIFT))
#define LCD_INIT_CONTROL             (LCD_LCD_SPEED_MODE | LCD_WAVEFORMS_TYPE | \
                                                   LCD_DRIVING_OP_MODE | LCD_PWM_BIAS | \
                                                   LCD_COM_NUMBER)

#endif /* End CY_SegLCD_P4_LCD_H */


/* [] END OF FILE */
