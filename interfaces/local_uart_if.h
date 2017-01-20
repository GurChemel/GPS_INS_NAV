/*
 * local_uart_if.h
 *
 *  Created on: 20 Jan 2017
 *      Author: Samsung
 */

#ifndef INTERFACES_LOCAL_UART_IF_H_
#define INTERFACES_LOCAL_UART_IF_H_

//TODO: switch with shared memory space
char ack_msg[TOT_HDR_LEN + ACK_ACK_LEN];
char nav_msg[TOT_HDR_LEN + NAV_POSECEF_LEN];
int new_ack_msg;
int new_nav_msg;

void UART1_Handler(void);
void init_uart(void);


#endif /* INTERFACES_LOCAL_UART_IF_H_ */
