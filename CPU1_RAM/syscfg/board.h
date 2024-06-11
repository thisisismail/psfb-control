/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM1 -> myEPWM1 Pinmux
//
//
// EPWM1A - GPIO Settings
//
#define GPIO_PIN_EPWM1A 0
#define myEPWM1_EPWMA_GPIO 0
#define myEPWM1_EPWMA_PIN_CONFIG GPIO_0_EPWM1A
//
// EPWM1B - GPIO Settings
//
#define GPIO_PIN_EPWM1B 1
#define myEPWM1_EPWMB_GPIO 1
#define myEPWM1_EPWMB_PIN_CONFIG GPIO_1_EPWM1B

//
// EPWM2 -> myEPWM2 Pinmux
//
//
// EPWM2A - GPIO Settings
//
#define GPIO_PIN_EPWM2A 2
#define myEPWM2_EPWMA_GPIO 2
#define myEPWM2_EPWMA_PIN_CONFIG GPIO_2_EPWM2A
//
// EPWM2B - GPIO Settings
//
#define GPIO_PIN_EPWM2B 3
#define myEPWM2_EPWMB_GPIO 3
#define myEPWM2_EPWMB_PIN_CONFIG GPIO_3_EPWM2B

//
// EPWM3 -> myEPWM3 Pinmux
//
//
// EPWM3A - GPIO Settings
//
#define GPIO_PIN_EPWM3A 4
#define myEPWM3_EPWMA_GPIO 4
#define myEPWM3_EPWMA_PIN_CONFIG GPIO_4_EPWM3A
//
// EPWM3B - GPIO Settings
//
#define GPIO_PIN_EPWM3B 5
#define myEPWM3_EPWMB_GPIO 5
#define myEPWM3_EPWMB_PIN_CONFIG GPIO_5_EPWM3B

//
// EPWM4 -> myEPWM4 Pinmux
//
//
// EPWM4A - GPIO Settings
//
#define GPIO_PIN_EPWM4A 6
#define myEPWM4_EPWMA_GPIO 6
#define myEPWM4_EPWMA_PIN_CONFIG GPIO_6_EPWM4A
//
// EPWM4B - GPIO Settings
//
#define GPIO_PIN_EPWM4B 7
#define myEPWM4_EPWMB_GPIO 7
#define myEPWM4_EPWMB_PIN_CONFIG GPIO_7_EPWM4B

//
// EPWM5 -> myEPWM5 Pinmux
//
//
// EPWM5A - GPIO Settings
//
#define GPIO_PIN_EPWM5A 8
#define myEPWM5_EPWMA_GPIO 8
#define myEPWM5_EPWMA_PIN_CONFIG GPIO_8_EPWM5A
//
// EPWM5B - GPIO Settings
//
#define GPIO_PIN_EPWM5B 9
#define myEPWM5_EPWMB_GPIO 9
#define myEPWM5_EPWMB_PIN_CONFIG GPIO_9_EPWM5B

//
// EPWM6 -> myEPWM6 Pinmux
//
//
// EPWM6A - GPIO Settings
//
#define GPIO_PIN_EPWM6A 10
#define myEPWM6_EPWMA_GPIO 10
#define myEPWM6_EPWMA_PIN_CONFIG GPIO_10_EPWM6A
//
// EPWM6B - GPIO Settings
//
#define GPIO_PIN_EPWM6B 11
#define myEPWM6_EPWMB_GPIO 11
#define myEPWM6_EPWMB_PIN_CONFIG GPIO_11_EPWM6B

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define myEPWM1_BASE EPWM1_BASE
#define myEPWM1_TBPRD 0
#define myEPWM1_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM1_TBPHS 0
#define myEPWM1_CMPA 0
#define myEPWM1_CMPB 0
#define myEPWM1_CMPC 0
#define myEPWM1_CMPD 0
#define myEPWM1_DBRED 0
#define myEPWM1_DBFED 0
#define myEPWM1_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM1_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM1_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM2_BASE EPWM2_BASE
#define myEPWM2_TBPRD 0
#define myEPWM2_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM2_TBPHS 0
#define myEPWM2_CMPA 0
#define myEPWM2_CMPB 0
#define myEPWM2_CMPC 0
#define myEPWM2_CMPD 0
#define myEPWM2_DBRED 0
#define myEPWM2_DBFED 0
#define myEPWM2_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM2_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM2_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM3_BASE EPWM3_BASE
#define myEPWM3_TBPRD 0
#define myEPWM3_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM3_TBPHS 0
#define myEPWM3_CMPA 0
#define myEPWM3_CMPB 0
#define myEPWM3_CMPC 0
#define myEPWM3_CMPD 0
#define myEPWM3_DBRED 0
#define myEPWM3_DBFED 0
#define myEPWM3_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM3_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM3_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM4_BASE EPWM4_BASE
#define myEPWM4_TBPRD 0
#define myEPWM4_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM4_TBPHS 0
#define myEPWM4_CMPA 0
#define myEPWM4_CMPB 0
#define myEPWM4_CMPC 0
#define myEPWM4_CMPD 0
#define myEPWM4_DBRED 0
#define myEPWM4_DBFED 0
#define myEPWM4_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM4_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM4_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM5_BASE EPWM5_BASE
#define myEPWM5_TBPRD 0
#define myEPWM5_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM5_TBPHS 0
#define myEPWM5_CMPA 0
#define myEPWM5_CMPB 0
#define myEPWM5_CMPC 0
#define myEPWM5_CMPD 0
#define myEPWM5_DBRED 0
#define myEPWM5_DBFED 0
#define myEPWM5_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM5_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM5_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM6_BASE EPWM6_BASE
#define myEPWM6_TBPRD 0
#define myEPWM6_COUNTER_MODE EPWM_COUNTER_MODE_STOP_FREEZE
#define myEPWM6_TBPHS 0
#define myEPWM6_CMPA 0
#define myEPWM6_CMPB 0
#define myEPWM6_CMPC 0
#define myEPWM6_CMPD 0
#define myEPWM6_DBRED 0
#define myEPWM6_DBFED 0
#define myEPWM6_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM6_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM6_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	EPWM_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
