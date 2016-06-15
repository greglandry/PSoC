.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu.inc"
.include "cydevicegnu_trm.inc"

/* IR */
.set IR__0__INTTYPE, CYREG_PICU2_INTTYPE2
.set IR__0__MASK, 0x04
.set IR__0__PC, CYREG_PRT2_PC2
.set IR__0__PORT, 2
.set IR__0__SHIFT, 2
.set IR__1__INTTYPE, CYREG_PICU2_INTTYPE5
.set IR__1__MASK, 0x20
.set IR__1__PC, CYREG_PRT2_PC5
.set IR__1__PORT, 2
.set IR__1__SHIFT, 5
.set IR__AG, CYREG_PRT2_AG
.set IR__AMUX, CYREG_PRT2_AMUX
.set IR__BIE, CYREG_PRT2_BIE
.set IR__BIT_MASK, CYREG_PRT2_BIT_MASK
.set IR__BYP, CYREG_PRT2_BYP
.set IR__CTL, CYREG_PRT2_CTL
.set IR__DM0, CYREG_PRT2_DM0
.set IR__DM1, CYREG_PRT2_DM1
.set IR__DM2, CYREG_PRT2_DM2
.set IR__DR, CYREG_PRT2_DR
.set IR__INP_DIS, CYREG_PRT2_INP_DIS
.set IR__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU2_BASE
.set IR__L__INTTYPE, CYREG_PICU2_INTTYPE2
.set IR__L__MASK, 0x04
.set IR__L__PC, CYREG_PRT2_PC2
.set IR__L__PORT, 2
.set IR__L__SHIFT, 2
.set IR__LCD_COM_SEG, CYREG_PRT2_LCD_COM_SEG
.set IR__LCD_EN, CYREG_PRT2_LCD_EN
.set IR__PORT, 2
.set IR__PRT, CYREG_PRT2_PRT
.set IR__PRTDSI__CAPS_SEL, CYREG_PRT2_CAPS_SEL
.set IR__PRTDSI__DBL_SYNC_IN, CYREG_PRT2_DBL_SYNC_IN
.set IR__PRTDSI__OE_SEL0, CYREG_PRT2_OE_SEL0
.set IR__PRTDSI__OE_SEL1, CYREG_PRT2_OE_SEL1
.set IR__PRTDSI__OUT_SEL0, CYREG_PRT2_OUT_SEL0
.set IR__PRTDSI__OUT_SEL1, CYREG_PRT2_OUT_SEL1
.set IR__PRTDSI__SYNC_OUT, CYREG_PRT2_SYNC_OUT
.set IR__PS, CYREG_PRT2_PS
.set IR__R__INTTYPE, CYREG_PICU2_INTTYPE5
.set IR__R__MASK, 0x20
.set IR__R__PC, CYREG_PRT2_PC5
.set IR__R__PORT, 2
.set IR__R__SHIFT, 5
.set IR__SLW, CYREG_PRT2_SLW

/* IREN */
.set IREN__0__INTTYPE, CYREG_PICU2_INTTYPE7
.set IREN__0__MASK, 0x80
.set IREN__0__PC, CYREG_PRT2_PC7
.set IREN__0__PORT, 2
.set IREN__0__SHIFT, 7
.set IREN__AG, CYREG_PRT2_AG
.set IREN__AMUX, CYREG_PRT2_AMUX
.set IREN__BIE, CYREG_PRT2_BIE
.set IREN__BIT_MASK, CYREG_PRT2_BIT_MASK
.set IREN__BYP, CYREG_PRT2_BYP
.set IREN__CTL, CYREG_PRT2_CTL
.set IREN__DM0, CYREG_PRT2_DM0
.set IREN__DM1, CYREG_PRT2_DM1
.set IREN__DM2, CYREG_PRT2_DM2
.set IREN__DR, CYREG_PRT2_DR
.set IREN__INP_DIS, CYREG_PRT2_INP_DIS
.set IREN__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU2_BASE
.set IREN__LCD_COM_SEG, CYREG_PRT2_LCD_COM_SEG
.set IREN__LCD_EN, CYREG_PRT2_LCD_EN
.set IREN__MASK, 0x80
.set IREN__PORT, 2
.set IREN__PRT, CYREG_PRT2_PRT
.set IREN__PRTDSI__CAPS_SEL, CYREG_PRT2_CAPS_SEL
.set IREN__PRTDSI__DBL_SYNC_IN, CYREG_PRT2_DBL_SYNC_IN
.set IREN__PRTDSI__OE_SEL0, CYREG_PRT2_OE_SEL0
.set IREN__PRTDSI__OE_SEL1, CYREG_PRT2_OE_SEL1
.set IREN__PRTDSI__OUT_SEL0, CYREG_PRT2_OUT_SEL0
.set IREN__PRTDSI__OUT_SEL1, CYREG_PRT2_OUT_SEL1
.set IREN__PRTDSI__SYNC_OUT, CYREG_PRT2_SYNC_OUT
.set IREN__PS, CYREG_PRT2_PS
.set IREN__SHIFT, 7
.set IREN__SLW, CYREG_PRT2_SLW

/* Left1 */
.set Left1__0__INTTYPE, CYREG_PICU6_INTTYPE1
.set Left1__0__MASK, 0x02
.set Left1__0__PC, CYREG_PRT6_PC1
.set Left1__0__PORT, 6
.set Left1__0__SHIFT, 1
.set Left1__AG, CYREG_PRT6_AG
.set Left1__AMUX, CYREG_PRT6_AMUX
.set Left1__BIE, CYREG_PRT6_BIE
.set Left1__BIT_MASK, CYREG_PRT6_BIT_MASK
.set Left1__BYP, CYREG_PRT6_BYP
.set Left1__CTL, CYREG_PRT6_CTL
.set Left1__DM0, CYREG_PRT6_DM0
.set Left1__DM1, CYREG_PRT6_DM1
.set Left1__DM2, CYREG_PRT6_DM2
.set Left1__DR, CYREG_PRT6_DR
.set Left1__INP_DIS, CYREG_PRT6_INP_DIS
.set Left1__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU6_BASE
.set Left1__LCD_COM_SEG, CYREG_PRT6_LCD_COM_SEG
.set Left1__LCD_EN, CYREG_PRT6_LCD_EN
.set Left1__MASK, 0x02
.set Left1__PORT, 6
.set Left1__PRT, CYREG_PRT6_PRT
.set Left1__PRTDSI__CAPS_SEL, CYREG_PRT6_CAPS_SEL
.set Left1__PRTDSI__DBL_SYNC_IN, CYREG_PRT6_DBL_SYNC_IN
.set Left1__PRTDSI__OE_SEL0, CYREG_PRT6_OE_SEL0
.set Left1__PRTDSI__OE_SEL1, CYREG_PRT6_OE_SEL1
.set Left1__PRTDSI__OUT_SEL0, CYREG_PRT6_OUT_SEL0
.set Left1__PRTDSI__OUT_SEL1, CYREG_PRT6_OUT_SEL1
.set Left1__PRTDSI__SYNC_OUT, CYREG_PRT6_SYNC_OUT
.set Left1__PS, CYREG_PRT6_PS
.set Left1__SHIFT, 1
.set Left1__SLW, CYREG_PRT6_SLW

/* Left2 */
.set Left2__0__INTTYPE, CYREG_PICU6_INTTYPE0
.set Left2__0__MASK, 0x01
.set Left2__0__PC, CYREG_PRT6_PC0
.set Left2__0__PORT, 6
.set Left2__0__SHIFT, 0
.set Left2__AG, CYREG_PRT6_AG
.set Left2__AMUX, CYREG_PRT6_AMUX
.set Left2__BIE, CYREG_PRT6_BIE
.set Left2__BIT_MASK, CYREG_PRT6_BIT_MASK
.set Left2__BYP, CYREG_PRT6_BYP
.set Left2__CTL, CYREG_PRT6_CTL
.set Left2__DM0, CYREG_PRT6_DM0
.set Left2__DM1, CYREG_PRT6_DM1
.set Left2__DM2, CYREG_PRT6_DM2
.set Left2__DR, CYREG_PRT6_DR
.set Left2__INP_DIS, CYREG_PRT6_INP_DIS
.set Left2__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU6_BASE
.set Left2__LCD_COM_SEG, CYREG_PRT6_LCD_COM_SEG
.set Left2__LCD_EN, CYREG_PRT6_LCD_EN
.set Left2__MASK, 0x01
.set Left2__PORT, 6
.set Left2__PRT, CYREG_PRT6_PRT
.set Left2__PRTDSI__CAPS_SEL, CYREG_PRT6_CAPS_SEL
.set Left2__PRTDSI__DBL_SYNC_IN, CYREG_PRT6_DBL_SYNC_IN
.set Left2__PRTDSI__OE_SEL0, CYREG_PRT6_OE_SEL0
.set Left2__PRTDSI__OE_SEL1, CYREG_PRT6_OE_SEL1
.set Left2__PRTDSI__OUT_SEL0, CYREG_PRT6_OUT_SEL0
.set Left2__PRTDSI__OUT_SEL1, CYREG_PRT6_OUT_SEL1
.set Left2__PRTDSI__SYNC_OUT, CYREG_PRT6_SYNC_OUT
.set Left2__PS, CYREG_PRT6_PS
.set Left2__SHIFT, 0
.set Left2__SLW, CYREG_PRT6_SLW

/* MotEn */
.set MotEn__0__INTTYPE, CYREG_PICU15_INTTYPE4
.set MotEn__0__MASK, 0x10
.set MotEn__0__PC, CYREG_IO_PC_PRT15_PC4
.set MotEn__0__PORT, 15
.set MotEn__0__SHIFT, 4
.set MotEn__AG, CYREG_PRT15_AG
.set MotEn__AMUX, CYREG_PRT15_AMUX
.set MotEn__BIE, CYREG_PRT15_BIE
.set MotEn__BIT_MASK, CYREG_PRT15_BIT_MASK
.set MotEn__BYP, CYREG_PRT15_BYP
.set MotEn__CTL, CYREG_PRT15_CTL
.set MotEn__DM0, CYREG_PRT15_DM0
.set MotEn__DM1, CYREG_PRT15_DM1
.set MotEn__DM2, CYREG_PRT15_DM2
.set MotEn__DR, CYREG_PRT15_DR
.set MotEn__INP_DIS, CYREG_PRT15_INP_DIS
.set MotEn__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU15_BASE
.set MotEn__LCD_COM_SEG, CYREG_PRT15_LCD_COM_SEG
.set MotEn__LCD_EN, CYREG_PRT15_LCD_EN
.set MotEn__MASK, 0x10
.set MotEn__PORT, 15
.set MotEn__PRT, CYREG_PRT15_PRT
.set MotEn__PRTDSI__CAPS_SEL, CYREG_PRT15_CAPS_SEL
.set MotEn__PRTDSI__DBL_SYNC_IN, CYREG_PRT15_DBL_SYNC_IN
.set MotEn__PRTDSI__OE_SEL0, CYREG_PRT15_OE_SEL0
.set MotEn__PRTDSI__OE_SEL1, CYREG_PRT15_OE_SEL1
.set MotEn__PRTDSI__OUT_SEL0, CYREG_PRT15_OUT_SEL0
.set MotEn__PRTDSI__OUT_SEL1, CYREG_PRT15_OUT_SEL1
.set MotEn__PRTDSI__SYNC_OUT, CYREG_PRT15_SYNC_OUT
.set MotEn__PS, CYREG_PRT15_PS
.set MotEn__SHIFT, 4
.set MotEn__SLW, CYREG_PRT15_SLW

/* Timer_TimerHW */
.set Timer_TimerHW__CAP0, CYREG_TMR0_CAP0
.set Timer_TimerHW__CAP1, CYREG_TMR0_CAP1
.set Timer_TimerHW__CFG0, CYREG_TMR0_CFG0
.set Timer_TimerHW__CFG1, CYREG_TMR0_CFG1
.set Timer_TimerHW__CFG2, CYREG_TMR0_CFG2
.set Timer_TimerHW__CNT_CMP0, CYREG_TMR0_CNT_CMP0
.set Timer_TimerHW__CNT_CMP1, CYREG_TMR0_CNT_CMP1
.set Timer_TimerHW__PER0, CYREG_TMR0_PER0
.set Timer_TimerHW__PER1, CYREG_TMR0_PER1
.set Timer_TimerHW__PM_ACT_CFG, CYREG_PM_ACT_CFG3
.set Timer_TimerHW__PM_ACT_MSK, 0x01
.set Timer_TimerHW__PM_STBY_CFG, CYREG_PM_STBY_CFG3
.set Timer_TimerHW__PM_STBY_MSK, 0x01
.set Timer_TimerHW__RT0, CYREG_TMR0_RT0
.set Timer_TimerHW__RT1, CYREG_TMR0_RT1
.set Timer_TimerHW__SR0, CYREG_TMR0_SR0

/* PWM_IR_PWMUDB */
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB14_15_ACTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB14_15_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB14_15_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB14_15_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB14_15_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG, CYREG_B0_UDB14_15_MSK
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB14_15_MSK
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB14_15_MSK
.set PWM_IR_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB14_15_MSK
.set PWM_IR_PWMUDB_genblk1_ctrlreg__7__MASK, 0x80
.set PWM_IR_PWMUDB_genblk1_ctrlreg__7__POS, 7
.set PWM_IR_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG, CYREG_B0_UDB14_ACTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__CONTROL_REG, CYREG_B0_UDB14_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG, CYREG_B0_UDB14_ST_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__COUNT_REG, CYREG_B0_UDB14_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG, CYREG_B0_UDB14_ST_CTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__MASK, 0x80
.set PWM_IR_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB14_MSK_ACTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB14_MSK_ACTL
.set PWM_IR_PWMUDB_genblk1_ctrlreg__PERIOD_REG, CYREG_B0_UDB14_MSK
.set PWM_IR_PWMUDB_genblk8_stsreg__0__MASK, 0x01
.set PWM_IR_PWMUDB_genblk8_stsreg__0__POS, 0
.set PWM_IR_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB14_15_ACTL
.set PWM_IR_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG, CYREG_B0_UDB14_15_ST
.set PWM_IR_PWMUDB_genblk8_stsreg__2__MASK, 0x04
.set PWM_IR_PWMUDB_genblk8_stsreg__2__POS, 2
.set PWM_IR_PWMUDB_genblk8_stsreg__3__MASK, 0x08
.set PWM_IR_PWMUDB_genblk8_stsreg__3__POS, 3
.set PWM_IR_PWMUDB_genblk8_stsreg__MASK, 0x0D
.set PWM_IR_PWMUDB_genblk8_stsreg__MASK_REG, CYREG_B0_UDB14_MSK
.set PWM_IR_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG, CYREG_B0_UDB14_MSK_ACTL
.set PWM_IR_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG, CYREG_B0_UDB14_MSK_ACTL
.set PWM_IR_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG, CYREG_B0_UDB14_ACTL
.set PWM_IR_PWMUDB_genblk8_stsreg__STATUS_CNT_REG, CYREG_B0_UDB14_ST_CTL
.set PWM_IR_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG, CYREG_B0_UDB14_ST_CTL
.set PWM_IR_PWMUDB_genblk8_stsreg__STATUS_REG, CYREG_B0_UDB14_ST
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG, CYREG_B0_UDB14_15_A0
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG, CYREG_B0_UDB14_15_A1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG, CYREG_B0_UDB14_15_D0
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG, CYREG_B0_UDB14_15_D1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB14_15_ACTL
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG, CYREG_B0_UDB14_15_F0
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG, CYREG_B0_UDB14_15_F1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__A0_A1_REG, CYREG_B0_UDB14_A0_A1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__A0_REG, CYREG_B0_UDB14_A0
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__A1_REG, CYREG_B0_UDB14_A1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__D0_D1_REG, CYREG_B0_UDB14_D0_D1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__D0_REG, CYREG_B0_UDB14_D0
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__D1_REG, CYREG_B0_UDB14_D1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG, CYREG_B0_UDB14_ACTL
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__F0_F1_REG, CYREG_B0_UDB14_F0_F1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__F0_REG, CYREG_B0_UDB14_F0
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__F1_REG, CYREG_B0_UDB14_F1
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG, CYREG_B0_UDB14_MSK_ACTL
.set PWM_IR_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG, CYREG_B0_UDB14_MSK_ACTL

/* Right1 */
.set Right1__0__INTTYPE, CYREG_PICU6_INTTYPE2
.set Right1__0__MASK, 0x04
.set Right1__0__PC, CYREG_PRT6_PC2
.set Right1__0__PORT, 6
.set Right1__0__SHIFT, 2
.set Right1__AG, CYREG_PRT6_AG
.set Right1__AMUX, CYREG_PRT6_AMUX
.set Right1__BIE, CYREG_PRT6_BIE
.set Right1__BIT_MASK, CYREG_PRT6_BIT_MASK
.set Right1__BYP, CYREG_PRT6_BYP
.set Right1__CTL, CYREG_PRT6_CTL
.set Right1__DM0, CYREG_PRT6_DM0
.set Right1__DM1, CYREG_PRT6_DM1
.set Right1__DM2, CYREG_PRT6_DM2
.set Right1__DR, CYREG_PRT6_DR
.set Right1__INP_DIS, CYREG_PRT6_INP_DIS
.set Right1__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU6_BASE
.set Right1__LCD_COM_SEG, CYREG_PRT6_LCD_COM_SEG
.set Right1__LCD_EN, CYREG_PRT6_LCD_EN
.set Right1__MASK, 0x04
.set Right1__PORT, 6
.set Right1__PRT, CYREG_PRT6_PRT
.set Right1__PRTDSI__CAPS_SEL, CYREG_PRT6_CAPS_SEL
.set Right1__PRTDSI__DBL_SYNC_IN, CYREG_PRT6_DBL_SYNC_IN
.set Right1__PRTDSI__OE_SEL0, CYREG_PRT6_OE_SEL0
.set Right1__PRTDSI__OE_SEL1, CYREG_PRT6_OE_SEL1
.set Right1__PRTDSI__OUT_SEL0, CYREG_PRT6_OUT_SEL0
.set Right1__PRTDSI__OUT_SEL1, CYREG_PRT6_OUT_SEL1
.set Right1__PRTDSI__SYNC_OUT, CYREG_PRT6_SYNC_OUT
.set Right1__PS, CYREG_PRT6_PS
.set Right1__SHIFT, 2
.set Right1__SLW, CYREG_PRT6_SLW

/* Right2 */
.set Right2__0__INTTYPE, CYREG_PICU6_INTTYPE3
.set Right2__0__MASK, 0x08
.set Right2__0__PC, CYREG_PRT6_PC3
.set Right2__0__PORT, 6
.set Right2__0__SHIFT, 3
.set Right2__AG, CYREG_PRT6_AG
.set Right2__AMUX, CYREG_PRT6_AMUX
.set Right2__BIE, CYREG_PRT6_BIE
.set Right2__BIT_MASK, CYREG_PRT6_BIT_MASK
.set Right2__BYP, CYREG_PRT6_BYP
.set Right2__CTL, CYREG_PRT6_CTL
.set Right2__DM0, CYREG_PRT6_DM0
.set Right2__DM1, CYREG_PRT6_DM1
.set Right2__DM2, CYREG_PRT6_DM2
.set Right2__DR, CYREG_PRT6_DR
.set Right2__INP_DIS, CYREG_PRT6_INP_DIS
.set Right2__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU6_BASE
.set Right2__LCD_COM_SEG, CYREG_PRT6_LCD_COM_SEG
.set Right2__LCD_EN, CYREG_PRT6_LCD_EN
.set Right2__MASK, 0x08
.set Right2__PORT, 6
.set Right2__PRT, CYREG_PRT6_PRT
.set Right2__PRTDSI__CAPS_SEL, CYREG_PRT6_CAPS_SEL
.set Right2__PRTDSI__DBL_SYNC_IN, CYREG_PRT6_DBL_SYNC_IN
.set Right2__PRTDSI__OE_SEL0, CYREG_PRT6_OE_SEL0
.set Right2__PRTDSI__OE_SEL1, CYREG_PRT6_OE_SEL1
.set Right2__PRTDSI__OUT_SEL0, CYREG_PRT6_OUT_SEL0
.set Right2__PRTDSI__OUT_SEL1, CYREG_PRT6_OUT_SEL1
.set Right2__PRTDSI__SYNC_OUT, CYREG_PRT6_SYNC_OUT
.set Right2__PS, CYREG_PRT6_PS
.set Right2__SHIFT, 3
.set Right2__SLW, CYREG_PRT6_SLW

/* PWM_MOT_PWMUDB */
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB13_14_ACTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB13_14_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB13_14_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB13_14_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB13_14_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_MASK_MASK_REG, CYREG_B0_UDB13_14_MSK
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB13_14_MSK
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB13_14_MSK
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB13_14_MSK
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__7__MASK, 0x80
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__7__POS, 7
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__CONTROL_AUX_CTL_REG, CYREG_B0_UDB13_ACTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__CONTROL_REG, CYREG_B0_UDB13_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__CONTROL_ST_REG, CYREG_B0_UDB13_ST_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__COUNT_REG, CYREG_B0_UDB13_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__COUNT_ST_REG, CYREG_B0_UDB13_ST_CTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__MASK, 0x80
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB13_MSK_ACTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB13_MSK_ACTL
.set PWM_MOT_PWMUDB_genblk1_ctrlreg__PERIOD_REG, CYREG_B0_UDB13_MSK
.set PWM_MOT_PWMUDB_genblk8_stsreg__0__MASK, 0x01
.set PWM_MOT_PWMUDB_genblk8_stsreg__0__POS, 0
.set PWM_MOT_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB13_14_ACTL
.set PWM_MOT_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG, CYREG_B0_UDB13_14_ST
.set PWM_MOT_PWMUDB_genblk8_stsreg__2__MASK, 0x04
.set PWM_MOT_PWMUDB_genblk8_stsreg__2__POS, 2
.set PWM_MOT_PWMUDB_genblk8_stsreg__3__MASK, 0x08
.set PWM_MOT_PWMUDB_genblk8_stsreg__3__POS, 3
.set PWM_MOT_PWMUDB_genblk8_stsreg__MASK, 0x0D
.set PWM_MOT_PWMUDB_genblk8_stsreg__MASK_REG, CYREG_B0_UDB13_MSK
.set PWM_MOT_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG, CYREG_B0_UDB13_MSK_ACTL
.set PWM_MOT_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG, CYREG_B0_UDB13_MSK_ACTL
.set PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG, CYREG_B0_UDB13_ACTL
.set PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_CNT_REG, CYREG_B0_UDB13_ST_CTL
.set PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG, CYREG_B0_UDB13_ST_CTL
.set PWM_MOT_PWMUDB_genblk8_stsreg__STATUS_REG, CYREG_B0_UDB13_ST
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG, CYREG_B0_UDB13_14_A0
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG, CYREG_B0_UDB13_14_A1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG, CYREG_B0_UDB13_14_D0
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG, CYREG_B0_UDB13_14_D1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB13_14_ACTL
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG, CYREG_B0_UDB13_14_F0
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG, CYREG_B0_UDB13_14_F1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__A0_A1_REG, CYREG_B0_UDB13_A0_A1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__A0_REG, CYREG_B0_UDB13_A0
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__A1_REG, CYREG_B0_UDB13_A1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__D0_D1_REG, CYREG_B0_UDB13_D0_D1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__D0_REG, CYREG_B0_UDB13_D0
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__D1_REG, CYREG_B0_UDB13_D1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG, CYREG_B0_UDB13_ACTL
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__F0_F1_REG, CYREG_B0_UDB13_F0_F1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__F0_REG, CYREG_B0_UDB13_F0
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__F1_REG, CYREG_B0_UDB13_F1
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG, CYREG_B0_UDB13_MSK_ACTL
.set PWM_MOT_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG, CYREG_B0_UDB13_MSK_ACTL

/* Clock_Timer */
.set Clock_Timer__CFG0, CYREG_CLKDIST_DCFG1_CFG0
.set Clock_Timer__CFG1, CYREG_CLKDIST_DCFG1_CFG1
.set Clock_Timer__CFG2, CYREG_CLKDIST_DCFG1_CFG2
.set Clock_Timer__CFG2_SRC_SEL_MASK, 0x07
.set Clock_Timer__INDEX, 0x01
.set Clock_Timer__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set Clock_Timer__PM_ACT_MSK, 0x02
.set Clock_Timer__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set Clock_Timer__PM_STBY_MSK, 0x02

/* Miscellaneous */
.set BCLK__BUS_CLK__HZ, 12000000
.set BCLK__BUS_CLK__KHZ, 12000
.set BCLK__BUS_CLK__MHZ, 12
.set CyClock_100kHz__CFG0, CYREG_CLKDIST_DCFG0_CFG0
.set CyClock_100kHz__CFG1, CYREG_CLKDIST_DCFG0_CFG1
.set CyClock_100kHz__CFG2, CYREG_CLKDIST_DCFG0_CFG2
.set CyClock_100kHz__CFG2_SRC_SEL_MASK, 0x07
.set CyClock_100kHz__INDEX, 0x00
.set CyClock_100kHz__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set CyClock_100kHz__PM_ACT_MSK, 0x01
.set CyClock_100kHz__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set CyClock_100kHz__PM_STBY_MSK, 0x01
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PANTHER, 19
.set CYDEV_CHIP_DIE_PSOC4A, 11
.set CYDEV_CHIP_DIE_PSOC5LP, 18
.set CYDEV_CHIP_DIE_TMA4, 2
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC5
.set CYDEV_CHIP_JTAG_ID, 0x2E123069
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 11
.set CYDEV_CHIP_MEMBER_4C, 16
.set CYDEV_CHIP_MEMBER_4D, 7
.set CYDEV_CHIP_MEMBER_4E, 4
.set CYDEV_CHIP_MEMBER_4F, 12
.set CYDEV_CHIP_MEMBER_4G, 2
.set CYDEV_CHIP_MEMBER_4H, 10
.set CYDEV_CHIP_MEMBER_4I, 15
.set CYDEV_CHIP_MEMBER_4J, 8
.set CYDEV_CHIP_MEMBER_4K, 9
.set CYDEV_CHIP_MEMBER_4L, 14
.set CYDEV_CHIP_MEMBER_4M, 13
.set CYDEV_CHIP_MEMBER_4N, 6
.set CYDEV_CHIP_MEMBER_4O, 5
.set CYDEV_CHIP_MEMBER_4U, 3
.set CYDEV_CHIP_MEMBER_5A, 18
.set CYDEV_CHIP_MEMBER_5B, 17
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_5B
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PANTHER_ES0, 0
.set CYDEV_CHIP_REV_PANTHER_ES1, 1
.set CYDEV_CHIP_REV_PANTHER_PRODUCTION, 1
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REV_TMA4_ES, 17
.set CYDEV_CHIP_REV_TMA4_ES2, 33
.set CYDEV_CHIP_REV_TMA4_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4C_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4E_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256K, 0
.set CYDEV_CHIP_REVISION_4G_ES, 17
.set CYDEV_CHIP_REVISION_4G_ES2, 33
.set CYDEV_CHIP_REVISION_4G_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4H_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4I_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4J_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4K_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4L_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4M_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4N_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4O_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4U_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_5B_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_FASTBOOT_ENABLED, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_DMA, 0
.set CYDEV_CONFIGURATION_ECC, 1
.set CYDEV_CONFIGURATION_IMOENABLED, CYDEV_CONFIG_FASTBOOT_ENABLED
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_ENABLE_MASK, 0x20
.set CYDEV_DEBUG_ENABLE_REGISTER, CYREG_MLOGIC_DEBUG
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_JTAG_4, 1
.set CYDEV_DEBUGGING_DPS_JTAG_5, 0
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS_SWD_SWV, 6
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD_SWV
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_DEBUGGING_XRES, 0
.set CYDEV_DMA_CHANNELS_AVAILABLE, 24
.set CYDEV_ECC_ENABLE, 0
.set CYDEV_HEAP_SIZE, 0x0000
.set CYDEV_INSTRUCT_CACHE_ENABLED, 1
.set CYDEV_INTR_RISING, 0x00000000
.set CYDEV_IS_EXPORTING_CODE, 0
.set CYDEV_IS_IMPORTING_CODE, 0
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LAUNCHER, 5
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER, 4
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_PROTECTION_ENABLE, 0
.set CYDEV_STACK_SIZE, 0x0000
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 0
.set CYDEV_VDDA_MV, 5000
.set CYDEV_VDDD_MV, 5000
.set CYDEV_VDDIO0_MV, 5000
.set CYDEV_VDDIO1_MV, 5000
.set CYDEV_VDDIO2_MV, 5000
.set CYDEV_VDDIO3_MV, 5000
.set CYDEV_VIO0_MV, 5000
.set CYDEV_VIO1_MV, 5000
.set CYDEV_VIO2_MV, 5000
.set CYDEV_VIO3_MV, 5000
.set CYIPBLOCK_ARM_CM3_VERSION, 0
.set CYIPBLOCK_P3_ANAIF_VERSION, 0
.set CYIPBLOCK_P3_CAN_VERSION, 0
.set CYIPBLOCK_P3_CAPSENSE_VERSION, 0
.set CYIPBLOCK_P3_COMP_VERSION, 0
.set CYIPBLOCK_P3_DECIMATOR_VERSION, 0
.set CYIPBLOCK_P3_DFB_VERSION, 0
.set CYIPBLOCK_P3_DMA_VERSION, 0
.set CYIPBLOCK_P3_DRQ_VERSION, 0
.set CYIPBLOCK_P3_DSM_VERSION, 0
.set CYIPBLOCK_P3_EMIF_VERSION, 0
.set CYIPBLOCK_P3_I2C_VERSION, 0
.set CYIPBLOCK_P3_LCD_VERSION, 0
.set CYIPBLOCK_P3_LPF_VERSION, 0
.set CYIPBLOCK_P3_OPAMP_VERSION, 0
.set CYIPBLOCK_P3_PM_VERSION, 0
.set CYIPBLOCK_P3_SCCT_VERSION, 0
.set CYIPBLOCK_P3_TIMER_VERSION, 0
.set CYIPBLOCK_P3_USB_VERSION, 0
.set CYIPBLOCK_P3_VIDAC_VERSION, 0
.set CYIPBLOCK_P3_VREF_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 0
.set CYIPBLOCK_S8_IRQ_VERSION, 0
.set CYIPBLOCK_S8_SAR_VERSION, 0
.set CYIPBLOCK_S8_SIO_VERSION, 0
.set CYIPBLOCK_S8_UDB_VERSION, 0
.set DMA_CHANNELS_USED__MASK0, 0x00000000
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif