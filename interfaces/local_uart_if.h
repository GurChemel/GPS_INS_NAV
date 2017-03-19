/*
 * local_uart_if.h
 *
 *  Created on: 20 Jan 2017
 *      Author: Samsung
 */

#ifndef INTERFACES_LOCAL_UART_IF_H_
#include "../includes/infrastructure.h"
#define INTERFACES_LOCAL_UART_IF_H_

//TODO: switch with shared memory space
char NMEA_msg[120];
int NMEA_len;
char ack_msg[TOT_HDR_LEN + ACK_ACK_LEN];
char nav_posecef_msg[TOT_HDR_LEN + NAV_POSECEF_LEN];
char nav_status_msg [TOT_HDR_LEN + NAV_STATUS_LEN];
int new_ack_msg;
int new_nav_msg;
int new_fix_msg;
int new_gps_sol;
int boot_time;
int fixOk;
int new_gps_msg;
unsigned long UART_STATUS;

void uart_int_handler(void);
void parse_recieved_msg(void);
void init_uart(void);
void reset_global_int(void);

enum {
	LISTENING = 0,
	SYNC1	  = 1,
	SYNC2     = 2,
	CLASS     = 3,
	LOCKED    = 4,
};

enum {
	GOT_$ = 0,
	GOT_G = 1,
	GOT_P = 2,
	GOT_2G = 3,
	GOT_3G = 4,
	LOCKED_NMEA = 5,
	HANGING = 6,
};

#endif /* INTERFACES_LOCAL_UART_IF_H_ */
