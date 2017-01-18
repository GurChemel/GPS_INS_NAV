//*****************************************************************************
// pin_mux_config.c
//
// configure the device pins for different signals
//
// Copyright (c) 2016, Texas Instruments Incorporated - http://www.ti.com/ 
// All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 6/16/2016 at 4:38:08 AM
// by TI PinMux version 
//
//*****************************************************************************

#include "pinmux.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "includes.h"
#include "gpio.h"
#include "prcm.h"

//*****************************************************************************
void PinMuxConfig(void)
{


	//
	// Set unused pins to PIN_MODE_0 with the exception of JTAG pins 16,17,19,20
	//
	PinModeSet(PIN_05, PIN_MODE_0);
	PinModeSet(PIN_15, PIN_MODE_0);
	PinModeSet(PIN_18, PIN_MODE_0);
	PinModeSet(PIN_21, PIN_MODE_0);
	PinModeSet(PIN_53, PIN_MODE_0);
	PinModeSet(PIN_50, PIN_MODE_0);
	PinModeSet(PIN_58, PIN_MODE_0);
	PinModeSet(PIN_59, PIN_MODE_0);
	PinModeSet(PIN_60, PIN_MODE_0);
	PinModeSet(PIN_61, PIN_MODE_0);
	PinModeSet(PIN_62, PIN_MODE_0);
	PinModeSet(PIN_63, PIN_MODE_0);
	PinModeSet(PIN_64, PIN_MODE_0);

	PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);
	PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);

	//GPS pwr pin (0-on, 1-off)
	GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT);

	//Onewire pin
	GPIODirModeSet(GPIOA0_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);

	//SD_CS
	GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT);

	//
	// Enable Peripheral Clocks
	//
	PRCMPeripheralClkEnable(PRCM_SDHOST, PRCM_RUN_MODE_CLK);
	PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);
	PRCMPeripheralClkEnable(PRCM_UARTA1, PRCM_RUN_MODE_CLK);
	PRCMPeripheralClkEnable(PRCM_I2CA0, PRCM_RUN_MODE_CLK);




	//
	// Configure PIN_06 for SDHost0 SDCARD_DATA
	//
	PinTypeSDHost(PIN_06, PIN_MODE_8);

	//
	// Configure PIN_01 for SDHost0 SDCARD_CLK
	//
	PinTypeSDHost(PIN_01, PIN_MODE_6);

	//
	// Configure PIN_02 for SDHost0 SDCARD_CMD
	//
	PinTypeSDHost(PIN_02, PIN_MODE_6);


	//
	// Set the SD card clock as output pin
	//
	PinDirModeSet(PIN_01,PIN_DIR_MODE_OUT);

	//
	// Enable Pull up on data
	//
	PinConfigSet(PIN_06,PIN_STRENGTH_4MA, PIN_TYPE_STD_PU);

	//
	// Enable Pull up on CMD
	//
	PinConfigSet(PIN_02,PIN_STRENGTH_4MA, PIN_TYPE_STD_PU);


	//
	// Configure PIN_55 for UART0 UART0_TX
	//
	PinTypeUART(PIN_55, PIN_MODE_3);

	//
	// Configure PIN_57 for UART0 UART0_RX
	//
	PinTypeUART(PIN_57, PIN_MODE_3);




	//
	// Configure PIN_07 for UART1 UART1_TX
	//
	PinTypeUART(PIN_07, PIN_MODE_5);

	//
	// Configure PIN_08 for UART1 UART1_RX
	//
	PinTypeUART(PIN_08, PIN_MODE_5);

	UARTConfigSetExpClk(UARTA1_BASE,PRCMPeripheralClockGet(PRCM_UARTA1),
			9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
					UART_CONFIG_PAR_NONE));

	UARTFIFODisable(UARTA1_BASE); //disable fifo

	UARTIntRegister(UARTA1_BASE, UART1_Handler); //enable interrupts
	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
	UARTEnable(UARTA1_BASE);




	//
	// Configure PIN_03 for I2C0 I2C_SCL
	//
	PinTypeI2C(PIN_03, PIN_MODE_5);

	//
	// Configure PIN_04 for I2C0 I2C_SDA
	//
	PinTypeI2C(PIN_04, PIN_MODE_5);

	PRCMPeripheralReset(PRCM_I2CA0);
	I2C_IF_Open(I2C_MASTER_MODE_STD);
	I2CMasterIntClearEx(I2CA0_BASE, 0xFFF);
	I2CMasterEnable(I2CA0_BASE);



	//61 62 //63
	//LED pins
	PinConfigSet(PIN_61,PIN_STRENGTH_2MA, PIN_TYPE_STD_PU);
	PinConfigSet(PIN_62,PIN_STRENGTH_2MA, PIN_TYPE_STD_PU);
	//PinConfigSet(PIN_63,PIN_STRENGTH_6MA, PIN_TYPE_STD_PU);

	GPIODirModeSet(GPIOA0_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT);
	GPIODirModeSet(GPIOA0_BASE, GPIO_PIN_7, GPIO_DIR_MODE_OUT);
	//GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT);

	//GPIOPinWrite(GPIOA0_BASE, GPIO_PIN_6|GPIO_PIN_7, 0xFF);
	//GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, 0xFF);


	// ACC interrupt pin
	GPIODirModeSet(GPIOA0_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);








}



