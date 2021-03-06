#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* IR */
IR__0__INTTYPE EQU CYREG_PICU2_INTTYPE2
IR__0__MASK EQU 0x04
IR__0__PC EQU CYREG_PRT2_PC2
IR__0__PORT EQU 2
IR__0__SHIFT EQU 2
IR__1__INTTYPE EQU CYREG_PICU2_INTTYPE5
IR__1__MASK EQU 0x20
IR__1__PC EQU CYREG_PRT2_PC5
IR__1__PORT EQU 2
IR__1__SHIFT EQU 5
IR__AG EQU CYREG_PRT2_AG
IR__AMUX EQU CYREG_PRT2_AMUX
IR__BIE EQU CYREG_PRT2_BIE
IR__BIT_MASK EQU CYREG_PRT2_BIT_MASK
IR__BYP EQU CYREG_PRT2_BYP
IR__CTL EQU CYREG_PRT2_CTL
IR__DM0 EQU CYREG_PRT2_DM0
IR__DM1 EQU CYREG_PRT2_DM1
IR__DM2 EQU CYREG_PRT2_DM2
IR__DR EQU CYREG_PRT2_DR
IR__INP_DIS EQU CYREG_PRT2_INP_DIS
IR__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
IR__L__INTTYPE EQU CYREG_PICU2_INTTYPE2
IR__L__MASK EQU 0x04
IR__L__PC EQU CYREG_PRT2_PC2
IR__L__PORT EQU 2
IR__L__SHIFT EQU 2
IR__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
IR__LCD_EN EQU CYREG_PRT2_LCD_EN
IR__PORT EQU 2
IR__PRT EQU CYREG_PRT2_PRT
IR__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
IR__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
IR__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
IR__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
IR__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
IR__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
IR__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
IR__PS EQU CYREG_PRT2_PS
IR__R__INTTYPE EQU CYREG_PICU2_INTTYPE5
IR__R__MASK EQU 0x20
IR__R__PC EQU CYREG_PRT2_PC5
IR__R__PORT EQU 2
IR__R__SHIFT EQU 5
IR__SLW EQU CYREG_PRT2_SLW

/* IREN */
IREN__0__INTTYPE EQU CYREG_PICU2_INTTYPE7
IREN__0__MASK EQU 0x80
IREN__0__PC EQU CYREG_PRT2_PC7
IREN__0__PORT EQU 2
IREN__0__SHIFT EQU 7
IREN__AG EQU CYREG_PRT2_AG
IREN__AMUX EQU CYREG_PRT2_AMUX
IREN__BIE EQU CYREG_PRT2_BIE
IREN__BIT_MASK EQU CYREG_PRT2_BIT_MASK
IREN__BYP EQU CYREG_PRT2_BYP
IREN__CTL EQU CYREG_PRT2_CTL
IREN__DM0 EQU CYREG_PRT2_DM0
IREN__DM1 EQU CYREG_PRT2_DM1
IREN__DM2 EQU CYREG_PRT2_DM2
IREN__DR EQU CYREG_PRT2_DR
IREN__INP_DIS EQU CYREG_PRT2_INP_DIS
IREN__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
IREN__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
IREN__LCD_EN EQU CYREG_PRT2_LCD_EN
IREN__MASK EQU 0x80
IREN__PORT EQU 2
IREN__PRT EQU CYREG_PRT2_PRT
IREN__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
IREN__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
IREN__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
IREN__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
IREN__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
IREN__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
IREN__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
IREN__PS EQU CYREG_PRT2_PS
IREN__SHIFT EQU 7
IREN__SLW EQU CYREG_PRT2_SLW

/* Left1 */
Left1__0__INTTYPE EQU CYREG_PICU6_INTTYPE1
Left1__0__MASK EQU 0x02
Left1__0__PC EQU CYREG_PRT6_PC1
Left1__0__PORT EQU 6
Left1__0__SHIFT EQU 1
Left1__AG EQU CYREG_PRT6_AG
Left1__AMUX EQU CYREG_PRT6_AMUX
Left1__BIE EQU CYREG_PRT6_BIE
Left1__BIT_MASK EQU CYREG_PRT6_BIT_MASK
Left1__BYP EQU CYREG_PRT6_BYP
Left1__CTL EQU CYREG_PRT6_CTL
Left1__DM0 EQU CYREG_PRT6_DM0
Left1__DM1 EQU CYREG_PRT6_DM1
Left1__DM2 EQU CYREG_PRT6_DM2
Left1__DR EQU CYREG_PRT6_DR
Left1__INP_DIS EQU CYREG_PRT6_INP_DIS
Left1__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU6_BASE
Left1__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
Left1__LCD_EN EQU CYREG_PRT6_LCD_EN
Left1__MASK EQU 0x02
Left1__PORT EQU 6
Left1__PRT EQU CYREG_PRT6_PRT
Left1__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
Left1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
Left1__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
Left1__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
Left1__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
Left1__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
Left1__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
Left1__PS EQU CYREG_PRT6_PS
Left1__SHIFT EQU 1
Left1__SLW EQU CYREG_PRT6_SLW

/* Left2 */
Left2__0__INTTYPE EQU CYREG_PICU6_INTTYPE0
Left2__0__MASK EQU 0x01
Left2__0__PC EQU CYREG_PRT6_PC0
Left2__0__PORT EQU 6
Left2__0__SHIFT EQU 0
Left2__AG EQU CYREG_PRT6_AG
Left2__AMUX EQU CYREG_PRT6_AMUX
Left2__BIE EQU CYREG_PRT6_BIE
Left2__BIT_MASK EQU CYREG_PRT6_BIT_MASK
Left2__BYP EQU CYREG_PRT6_BYP
Left2__CTL EQU CYREG_PRT6_CTL
Left2__DM0 EQU CYREG_PRT6_DM0
Left2__DM1 EQU CYREG_PRT6_DM1
Left2__DM2 EQU CYREG_PRT6_DM2
Left2__DR EQU CYREG_PRT6_DR
Left2__INP_DIS EQU CYREG_PRT6_INP_DIS
Left2__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU6_BASE
Left2__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
Left2__LCD_EN EQU CYREG_PRT6_LCD_EN
Left2__MASK EQU 0x01
Left2__PORT EQU 6
Left2__PRT EQU CYREG_PRT6_PRT
Left2__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
Left2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
Left2__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
Left2__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
Left2__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
Left2__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
Left2__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
Left2__PS EQU CYREG_PRT6_PS
Left2__SHIFT EQU 0
Left2__SLW EQU CYREG_PRT6_SLW

/* MotEn */
MotEn__0__INTTYPE EQU CYREG_PICU15_INTTYPE4
MotEn__0__MASK EQU 0x10
MotEn__0__PC EQU CYREG_IO_PC_PRT15_PC4
MotEn__0__PORT EQU 15
MotEn__0__SHIFT EQU 4
MotEn__AG EQU CYREG_PRT15_AG
MotEn__AMUX EQU CYREG_PRT15_AMUX
MotEn__BIE EQU CYREG_PRT15_BIE
MotEn__BIT_MASK EQU CYREG_PRT15_BIT_MASK
MotEn__BYP EQU CYREG_PRT15_BYP
MotEn__CTL EQU CYREG_PRT15_CTL
MotEn__DM0 EQU CYREG_PRT15_DM0
MotEn__DM1 EQU CYREG_PRT15_DM1
MotEn__DM2 EQU CYREG_PRT15_DM2
MotEn__DR EQU CYREG_PRT15_DR
MotEn__INP_DIS EQU CYREG_PRT15_INP_DIS
MotEn__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU15_BASE
MotEn__LCD_COM_SEG EQU CYREG_PRT15_LCD_COM_SEG
MotEn__LCD_EN EQU CYREG_PRT15_LCD_EN
MotEn__MASK EQU 0x10
MotEn__PORT EQU 15
MotEn__PRT EQU CYREG_PRT15_PRT
MotEn__PRTDSI__CAPS_SEL EQU CYREG_PRT15_CAPS_SEL
MotEn__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT15_DBL_SYNC_IN
MotEn__PRTDSI__OE_SEL0 EQU CYREG_PRT15_OE_SEL0
MotEn__PRTDSI__OE_SEL1 EQU CYREG_PRT15_OE_SEL1
MotEn__PRTDSI__OUT_SEL0 EQU CYREG_PRT15_OUT_SEL0
MotEn__PRTDSI__OUT_SEL1 EQU CYREG_PRT15_OUT_SEL1
MotEn__PRTDSI__SYNC_OUT EQU CYREG_PRT15_SYNC_OUT
MotEn__PS EQU CYREG_PRT15_PS
MotEn__SHIFT EQU 4
MotEn__SLW EQU CYREG_PRT15_SLW

/* Timer_TimerHW */
Timer_TimerHW__CAP0 EQU CYREG_TMR0_CAP0
Timer_TimerHW__CAP1 EQU CYREG_TMR0_CAP1
Timer_TimerHW__CFG0 EQU CYREG_TMR0_CFG0
Timer_TimerHW__CFG1 EQU CYREG_TMR0_CFG1
Timer_TimerHW__CFG2 EQU CYREG_TMR0_CFG2
Timer_TimerHW__CNT_CMP0 EQU CYREG_TMR0_CNT_CMP0
Timer_TimerHW__CNT_CMP1 EQU CYREG_TMR0_CNT_CMP1
Timer_TimerHW__PER0 EQU CYREG_TMR0_PER0
Timer_TimerHW__PER1 EQU CYREG_TMR0_PER1
Timer_TimerHW__PM_ACT_CFG EQU CYREG_PM_ACT_CFG3
Timer_TimerHW__PM_ACT_MSK EQU 0x01
Timer_TimerHW__PM_STBY_CFG EQU CYREG_PM_STBY_CFG3
Timer_TimerHW__PM_STBY_MSK EQU 0x01
Timer_TimerHW__RT0 EQU CYREG_TMR0_RT0
Timer_TimerHW__RT1 EQU CYREG_TMR0_RT1
Timer_TimerHW__SR0 EQU CYREG_TMR0_SR0

/* PWM_IR_PWMUDB */
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB14_15_ACTL
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB14_15_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB14_15_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB14_15_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB14_15_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB14_15_MSK
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB14_15_MSK
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB14_15_MSK
PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB14_15_MSK
PWM_IR_PWMUDB_genblk1_ctrlreg__7__MASK EQU 0x80
PWM_IR_PWMUDB_genblk1_ctrlreg__7__POS EQU 7
PWM_IR_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB14_ACTL
PWM_IR_PWMUDB_genblk1_ctrlreg__CONTROL_REG EQU CYREG_B0_UDB14_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG EQU CYREG_B0_UDB14_ST_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__COUNT_REG EQU CYREG_B0_UDB14_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG EQU CYREG_B0_UDB14_ST_CTL
PWM_IR_PWMUDB_genblk1_ctrlreg__MASK EQU 0x80
PWM_IR_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB14_MSK_ACTL
PWM_IR_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB14_MSK_ACTL
PWM_IR_PWMUDB_genblk1_ctrlreg__PERIOD_REG EQU CYREG_B0_UDB14_MSK
PWM_IR_PWMUDB_genblk8_stsreg__0__MASK EQU 0x01
PWM_IR_PWMUDB_genblk8_stsreg__0__POS EQU 0
PWM_IR_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB14_15_ACTL
PWM_IR_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG EQU CYREG_B0_UDB14_15_ST
PWM_IR_PWMUDB_genblk8_stsreg__2__MASK EQU 0x04
PWM_IR_PWMUDB_genblk8_stsreg__2__POS EQU 2
PWM_IR_PWMUDB_genblk8_stsreg__3__MASK EQU 0x08
PWM_IR_PWMUDB_genblk8_stsreg__3__POS EQU 3
PWM_IR_PWMUDB_genblk8_stsreg__MASK EQU 0x0D
PWM_IR_PWMUDB_genblk8_stsreg__MASK_REG EQU CYREG_B0_UDB14_MSK
PWM_IR_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB14_MSK_ACTL
PWM_IR_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB14_MSK_ACTL
PWM_IR_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB14_ACTL
PWM_IR_PWMUDB_genblk8_stsreg__STATUS_CNT_REG EQU CYREG_B0_UDB14_ST_CTL
PWM_IR_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG EQU CYREG_B0_UDB14_ST_CTL
PWM_IR_PWMUDB_genblk8_stsreg__STATUS_REG EQU CYREG_B0_UDB14_ST
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB14_15_A0
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB14_15_A1
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB14_15_D0
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB14_15_D1
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB14_15_ACTL
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB14_15_F0
PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB14_15_F1
PWM_IR_PWMUDB_sP8_pwmdp_u0__A0_A1_REG EQU CYREG_B0_UDB14_A0_A1
PWM_IR_PWMUDB_sP8_pwmdp_u0__A0_REG EQU CYREG_B0_UDB14_A0
PWM_IR_PWMUDB_sP8_pwmdp_u0__A1_REG EQU CYREG_B0_UDB14_A1
PWM_IR_PWMUDB_sP8_pwmdp_u0__D0_D1_REG EQU CYREG_B0_UDB14_D0_D1
PWM_IR_PWMUDB_sP8_pwmdp_u0__D0_REG EQU CYREG_B0_UDB14_D0
PWM_IR_PWMUDB_sP8_pwmdp_u0__D1_REG EQU CYREG_B0_UDB14_D1
PWM_IR_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB14_ACTL
PWM_IR_PWMUDB_sP8_pwmdp_u0__F0_F1_REG EQU CYREG_B0_UDB14_F0_F1
PWM_IR_PWMUDB_sP8_pwmdp_u0__F0_REG EQU CYREG_B0_UDB14_F0
PWM_IR_PWMUDB_sP8_pwmdp_u0__F1_REG EQU CYREG_B0_UDB14_F1
PWM_IR_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB14_MSK_ACTL
PWM_IR_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB14_MSK_ACTL

/* Right1 */
Right1__0__INTTYPE EQU CYREG_PICU6_INTTYPE2
Right1__0__MASK EQU 0x04
Right1__0__PC EQU CYREG_PRT6_PC2
Right1__0__PORT EQU 6
Right1__0__SHIFT EQU 2
Right1__AG EQU CYREG_PRT6_AG
Right1__AMUX EQU CYREG_PRT6_AMUX
Right1__BIE EQU CYREG_PRT6_BIE
Right1__BIT_MASK EQU CYREG_PRT6_BIT_MASK
Right1__BYP EQU CYREG_PRT6_BYP
Right1__CTL EQU CYREG_PRT6_CTL
Right1__DM0 EQU CYREG_PRT6_DM0
Right1__DM1 EQU CYREG_PRT6_DM1
Right1__DM2 EQU CYREG_PRT6_DM2
Right1__DR EQU CYREG_PRT6_DR
Right1__INP_DIS EQU CYREG_PRT6_INP_DIS
Right1__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU6_BASE
Right1__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
Right1__LCD_EN EQU CYREG_PRT6_LCD_EN
Right1__MASK EQU 0x04
Right1__PORT EQU 6
Right1__PRT EQU CYREG_PRT6_PRT
Right1__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
Right1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
Right1__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
Right1__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
Right1__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
Right1__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
Right1__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
Right1__PS EQU CYREG_PRT6_PS
Right1__SHIFT EQU 2
Right1__SLW EQU CYREG_PRT6_SLW

/* Right2 */
Right2__0__INTTYPE EQU CYREG_PICU6_INTTYPE3
Right2__0__MASK EQU 0x08
Right2__0__PC EQU CYREG_PRT6_PC3
Right2__0__PORT EQU 6
Right2__0__SHIFT EQU 3
Right2__AG EQU CYREG_PRT6_AG
Right2__AMUX EQU CYREG_PRT6_AMUX
Right2__BIE EQU CYREG_PRT6_BIE
Right2__BIT_MASK EQU CYREG_PRT6_BIT_MASK
Right2__BYP EQU CYREG_PRT6_BYP
Right2__CTL EQU CYREG_PRT6_CTL
Right2__DM0 EQU CYREG_PRT6_DM0
Right2__DM1 EQU CYREG_PRT6_DM1
Right2__DM2 EQU CYREG_PRT6_DM2
Right2__DR EQU CYREG_PRT6_DR
Right2__INP_DIS EQU CYREG_PRT6_INP_DIS
Right2__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU6_BASE
Right2__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
Right2__LCD_EN EQU CYREG_PRT6_LCD_EN
Right2__MASK EQU 0x08
Right2__PORT EQU 6
Right2__PRT EQU CYREG_PRT6_PRT
Right2__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
Right2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
Right2__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
Right2__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
Right2__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
Right2__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
Right2__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
Right2__PS EQU CYREG_PRT6_PS
Right2__SHIFT EQU 3
Right2__SLW EQU CYREG_PRT6_SLW

/* PWM_MOT_PWMUDB */
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB13_14_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB13_14_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB13_14_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB13_14_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB13_14_MSK
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB13_14_MSK
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB13_14_MSK
PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB13_14_MSK
PWM_MOT_PWMUDB_genblk1_ctrlreg__7__MASK EQU 0x80
PWM_MOT_PWMUDB_genblk1_ctrlreg__7__POS EQU 7
PWM_MOT_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__CONTROL_REG EQU CYREG_B0_UDB13_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG EQU CYREG_B0_UDB13_ST_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__COUNT_REG EQU CYREG_B0_UDB13_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG EQU CYREG_B0_UDB13_ST_CTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__MASK EQU 0x80
PWM_MOT_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
PWM_MOT_PWMUDB_genblk1_ctrlreg__PERIOD_REG EQU CYREG_B0_UDB13_MSK
PWM_MOT_PWMUDB_genblk8_stsreg__0__MASK EQU 0x01
PWM_MOT_PWMUDB_genblk8_stsreg__0__POS EQU 0
PWM_MOT_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
PWM_MOT_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG EQU CYREG_B0_UDB13_14_ST
PWM_MOT_PWMUDB_genblk8_stsreg__2__MASK EQU 0x04
PWM_MOT_PWMUDB_genblk8_stsreg__2__POS EQU 2
PWM_MOT_PWMUDB_genblk8_stsreg__3__MASK EQU 0x08
PWM_MOT_PWMUDB_genblk8_stsreg__3__POS EQU 3
PWM_MOT_PWMUDB_genblk8_stsreg__MASK EQU 0x0D
PWM_MOT_PWMUDB_genblk8_stsreg__MASK_REG EQU CYREG_B0_UDB13_MSK
PWM_MOT_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
PWM_MOT_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_CNT_REG EQU CYREG_B0_UDB13_ST_CTL
PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG EQU CYREG_B0_UDB13_ST_CTL
PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_REG EQU CYREG_B0_UDB13_ST
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB13_14_A0
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB13_14_A1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB13_14_D0
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB13_14_D1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB13_14_F0
PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB13_14_F1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__A0_A1_REG EQU CYREG_B0_UDB13_A0_A1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__A0_REG EQU CYREG_B0_UDB13_A0
PWM_MOT_PWMUDB_sP8_pwmdp_u0__A1_REG EQU CYREG_B0_UDB13_A1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__D0_D1_REG EQU CYREG_B0_UDB13_D0_D1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__D0_REG EQU CYREG_B0_UDB13_D0
PWM_MOT_PWMUDB_sP8_pwmdp_u0__D1_REG EQU CYREG_B0_UDB13_D1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
PWM_MOT_PWMUDB_sP8_pwmdp_u0__F0_F1_REG EQU CYREG_B0_UDB13_F0_F1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__F0_REG EQU CYREG_B0_UDB13_F0
PWM_MOT_PWMUDB_sP8_pwmdp_u0__F1_REG EQU CYREG_B0_UDB13_F1
PWM_MOT_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
PWM_MOT_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL

/* Clock_Timer */
Clock_Timer__CFG0 EQU CYREG_CLKDIST_DCFG1_CFG0
Clock_Timer__CFG1 EQU CYREG_CLKDIST_DCFG1_CFG1
Clock_Timer__CFG2 EQU CYREG_CLKDIST_DCFG1_CFG2
Clock_Timer__CFG2_SRC_SEL_MASK EQU 0x07
Clock_Timer__INDEX EQU 0x01
Clock_Timer__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
Clock_Timer__PM_ACT_MSK EQU 0x02
Clock_Timer__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
Clock_Timer__PM_STBY_MSK EQU 0x02

/* Miscellaneous */
BCLK__BUS_CLK__HZ EQU 12000000
BCLK__BUS_CLK__KHZ EQU 12000
BCLK__BUS_CLK__MHZ EQU 12
CyClock_100kHz__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
CyClock_100kHz__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
CyClock_100kHz__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
CyClock_100kHz__CFG2_SRC_SEL_MASK EQU 0x07
CyClock_100kHz__INDEX EQU 0x00
CyClock_100kHz__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
CyClock_100kHz__PM_ACT_MSK EQU 0x01
CyClock_100kHz__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
CyClock_100kHz__PM_STBY_MSK EQU 0x01
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 19
CYDEV_CHIP_DIE_PSOC4A EQU 11
CYDEV_CHIP_DIE_PSOC5LP EQU 18
CYDEV_CHIP_DIE_TMA4 EQU 2
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E123069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 11
CYDEV_CHIP_MEMBER_4C EQU 16
CYDEV_CHIP_MEMBER_4D EQU 7
CYDEV_CHIP_MEMBER_4E EQU 4
CYDEV_CHIP_MEMBER_4F EQU 12
CYDEV_CHIP_MEMBER_4G EQU 2
CYDEV_CHIP_MEMBER_4H EQU 10
CYDEV_CHIP_MEMBER_4I EQU 15
CYDEV_CHIP_MEMBER_4J EQU 8
CYDEV_CHIP_MEMBER_4K EQU 9
CYDEV_CHIP_MEMBER_4L EQU 14
CYDEV_CHIP_MEMBER_4M EQU 13
CYDEV_CHIP_MEMBER_4N EQU 6
CYDEV_CHIP_MEMBER_4O EQU 5
CYDEV_CHIP_MEMBER_4U EQU 3
CYDEV_CHIP_MEMBER_5A EQU 18
CYDEV_CHIP_MEMBER_5B EQU 17
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4C_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4O_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x0000
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000000
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x0000
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */
