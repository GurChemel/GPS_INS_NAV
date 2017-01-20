/*
 * local_uart_if.c
 *
 *  Created on: 20 Jan 2017
 *      Author: Samsung
 */

#include "../sensors/sensors.h"
#include "local_uart_if.h"

void UART1_Handler(void){
	unsigned long UART_STATUS;
	UART_STATUS = UARTIntStatus(UARTA1_BASE, true);
	UARTIntClear(UARTA1_BASE, UART_INT_RX);
	UARTIntDisable(UARTA1_BASE, UART_INT_RX);

	int idx=0;
	char msg [60]={0};
	while((UART_STATUS & UART_INT_RX) && UARTCharsAvail(UARTA1_BASE)){
		msg[idx] = (char)UARTCharGetNonBlocking(UARTA1_BASE);
		idx++;
	}
	if ((msg[SYNC_CHAR1_POS]==SYNC_CHAR1) && (msg[SYNC_CHAR2_POS]==SYNC_CHAR2)){
		if ((msg[CLASS_POS] == NAV_MSG_CLASS) && (msg[ID_POS] == NAV_POSECEF_ID)){
			memcpy(msg, nav_msg, TOT_HDR_LEN + NAV_POSECEF_LEN);
			new_nav_msg =1;
		}
		if ((msg[CLASS_POS] == ACK_MSG_CLASS) && (msg[ID_POS] == ACK_ID)){
			memcpy(msg, ack_msg, TOT_HDR_LEN + ACK_ACK_LEN);
			new_ack_msg =1;
		}
	}
	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
}

void init_uart(void){
	UARTConfigSetExpClk(UARTA1_BASE,PRCMPeripheralClockGet(PRCM_UARTA1),
				9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
						UART_CONFIG_PAR_NONE));
	UARTFIFOLevelSet(UARTA1_BASE,UART_FIFO_TX1_8, UART_FIFO_RX6_8);
	UARTFIFOEnable(UARTA1_BASE); //Enable FIFO
	UARTIntRegister(UARTA1_BASE, UART1_Handler);
	UARTIntEnable(UARTA1_BASE, UART_INT_RX); //enable interrupts
	UARTEnable(UARTA1_BASE);
}


