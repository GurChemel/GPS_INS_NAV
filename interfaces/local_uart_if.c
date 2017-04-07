/*
 * local_uart_if.c
 *
 *  Created on: 20 Jan 2017
 *      Author: Samsung
 */

#include "../sensors/sensors.h"
#include "local_uart_if.h"
char static_NMEA_msg[74] = "$GPGGA,193813.00,3246.86405,N,03500.84086,E,1,04,5.26,214.7,M,18.8,M,,*51";

void reset_global_int(void){
	new_ack_msg = OLD;
	new_nav_msg = OLD;
	new_fix_msg = OLD;
	new_gps_msg = OLD;
}

void uart_int_handler(void) {
	//DEBUG_PRINT("\n\r inside int handler boot time: %d\n\r", boot_time);
	//DEBUG_PRINT("\n\r UART handler print.");
	UART_STATUS = UARTIntStatus(UARTA1_BASE, true);
	UARTIntClear(UARTA1_BASE, UART_INT_RX);
	char temp;
	int i;
	if (STATIC_GPS) {
		for (i=0;i<5;i++) {
			temp = (char)UARTCharGet(UARTA1_BASE);
		}
		copy_char_arr(NMEA_msg, static_NMEA_msg ,74);
		new_gps_msg =NEW;
		fixOk = 1;
		return;
	}
	UARTIntDisable(UARTA1_BASE, UART_INT_RX);
	//char temp;
	int idx=0;
	char incom_msg [100]={0};
	int cont_get_char = 1;
	if (!NMEA){
		int state = LISTENING;
		int next_state = LISTENING;
		int max_size = 10;
		while((UART_STATUS & UART_INT_RX) && UARTCharsAvail(UARTA1_BASE) && cont_get_char){
			temp = (char)UARTCharGet(UARTA1_BASE);
			switch (state){
				case LISTENING:
					if (temp == SYNC_CHAR1) {
						incom_msg[SYNC_CHAR1_POS]=temp;
						next_state = SYNC1;
						break;
					}
					next_state = LISTENING;
					break;
				case SYNC1:
					if (temp == SYNC_CHAR2){
						incom_msg[SYNC_CHAR2_POS]=temp;
						next_state = SYNC2;
						break;
					}
					next_state = LISTENING;
					break;
				case SYNC2:
					if ((temp == ACK_MSG_CLASS) || (temp == NAV_MSG_CLASS)){
						incom_msg[CLASS_POS]=temp;
						next_state = CLASS;
						break;
					}
					next_state = LISTENING;
					break;
				case CLASS:
					if ((temp == ACK_ID) || (temp == NAV_POSECEF_ID) || (temp == NAV_STATUS_LEN)){
						incom_msg[ID_POS]=temp;
						idx = 4;
						next_state = LOCKED;
						break;
					}
					next_state = LISTENING;
					break;
				case LOCKED:
					incom_msg[idx] = temp;
					if (idx == 5) max_size = ((incom_msg[5] >> BYTE) && incom_msg[4]) + TOT_HDR_LEN;
					if (idx < max_size) idx++;
					else cont_get_char = 0;
					break;
				default: break;
			}
			state = next_state;
			//DEBUG_PRINT("\n\r cur char: 0x%x%x", temp>>4,(temp&0xf));
			DEBUG_PRINT("%c", temp);
		}
		if (boot_time){
			if ((incom_msg[SYNC_CHAR1_POS]==SYNC_CHAR1) && (incom_msg[SYNC_CHAR2_POS]==SYNC_CHAR2)){
				if ((incom_msg[CLASS_POS] == NAV_MSG_CLASS) && (incom_msg[ID_POS] == NAV_POSECEF_ID)){
					memcpy(incom_msg, nav_posecef_msg, TOT_HDR_LEN + NAV_POSECEF_LEN);
					new_nav_msg =NEW;
				}
				if ((incom_msg[CLASS_POS] == ACK_MSG_CLASS) && (incom_msg[ID_POS] == ACK_ID)){
					memcpy(incom_msg, ack_msg, TOT_HDR_LEN + ACK_ACK_LEN);
					new_ack_msg =NEW;
				}
				if ((incom_msg[CLASS_POS] == NAV_MSG_CLASS) && (incom_msg[ID_POS] == NAV_STATUS_ID)){
					memcpy(incom_msg, nav_status_msg, TOT_HDR_LEN + NAV_STATUS_LEN);
					new_fix_msg =NEW;
				}
			}
				UARTIntEnable(UARTA1_BASE, UART_INT_RX);
		}
	}else{
		int state = HANGING;
		int next_state = HANGING;
		int mal_msg = 0;
		int no_sync = 0;
		while(cont_get_char){
			temp = (char)UARTCharGet(UARTA1_BASE);
			switch (state){
				case HANGING:
					if (temp == '$') {
						incom_msg[0]=temp;
						next_state = GOT_$;
						mal_msg = 0;
						break;
					}
					mal_msg = 1;
					no_sync++;
					cont_get_char = ((temp == 0xa) || no_sync==100) ? 0 : 1;
					next_state = HANGING;
					break;
				case GOT_$:
					if (temp == 'G'){
						incom_msg[1]=temp;
						next_state = GOT_G;
						break;
					}
					next_state =(temp == '$') ? GOT_$ : HANGING;
					break;
				case GOT_G:
					if (temp == 'P'){
						incom_msg[2]=temp;
						next_state = GOT_P;
						break;
					}
					next_state =(temp == '$') ? GOT_$ : HANGING;
					break;
				case GOT_P:
					if (temp == 'G'){
						incom_msg[3]=temp;
						next_state = GOT_2G;
						break;
					}
					next_state =(temp == '$') ? GOT_$ : HANGING;
					break;
				case GOT_2G:
					if (temp == 'G'){
						incom_msg[4]=temp;
						next_state = GOT_3G; break;
					}
					next_state =(temp == '$') ? GOT_$ : HANGING; break;
				case GOT_3G:
					if (temp == 'A'){
						incom_msg[5]=temp;
						next_state = LOCKED_NMEA;
						idx=6; break;
					}
					next_state =(temp == '$') ? GOT_$ : HANGING; break;
				case LOCKED_NMEA:
					//if (temp== '$'){next_state = GOT_$; break;}
					next_state = (temp == '$') ? GOT_$ : next_state;
					incom_msg[idx] = temp;
					cont_get_char = ((temp == 0xa) && incom_msg[idx-1]==0xd) ? 0 : 1;
					idx++;
					if (idx>90) {
						mal_msg = 1;
						cont_get_char = 0;
					}
					break;
				default: break;
			}
			state = next_state;
			//DEBUG_PRINT("\n\r cur char: 0x%x%x", temp>>4,(temp&0xf));
			//DEBUG_PRINT("%c", temp);
		}
		if (!mal_msg){
			NMEA_len = idx+1;
			if (STATIC_GPS) copy_char_arr(NMEA_msg, static_NMEA_msg ,idx+1);
			else			copy_char_arr(NMEA_msg, incom_msg ,idx+1);
			fixOk = (incom_msg[44]=='1' || incom_msg[44]=='2')? 1 : 0 ;
			if (!fixOk){
				print_msg(NMEA_msg, idx);
			} else {
				new_gps_msg =NEW;
			}
		}
	}
	//DEBUG_PRINT("\n\r done handler");
	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
}


void parse_recieved_msg(void){
	new_gps_msg=OLD;
	//UART_STATUS = UARTIntStatus(UARTA1_BASE, true);
	//UARTIntClear(UARTA1_BASE, UART_INT_RX);
	UARTIntDisable(UARTA1_BASE, UART_INT_RX);
	DEBUG_PRINT("\n\r handler print: ");
	char temp;
	int idx=0;
	char msg [60]={0};
	int state = LISTENING;
	int next_state = LISTENING;
	int cont_get_char = 1;
	int max_size = 10;
	while((UART_STATUS & UART_INT_RX) && UARTCharsAvail(UARTA1_BASE) && cont_get_char){
		temp = (char)UARTCharGet(UARTA1_BASE);
		switch (state){
			case LISTENING:
				if (temp == SYNC_CHAR1) {
					msg[SYNC_CHAR1_POS]=temp;
					next_state = SYNC1;
					break;
				}
				next_state = LISTENING;
				break;
			case SYNC1:
				if (temp == SYNC_CHAR2){
					msg[SYNC_CHAR2_POS]=temp;
					next_state = SYNC2;
					break;
				}
				next_state = LISTENING;
				break;
			case SYNC2:
				if ((temp == ACK_MSG_CLASS) || (temp == NAV_MSG_CLASS)){
					msg[CLASS_POS]=temp;
					next_state = CLASS;
					break;
				}
				next_state = LISTENING;
				break;
			case CLASS:
				if ((temp == ACK_ID) || (temp == NAV_POSECEF_ID) || (temp == NAV_STATUS_LEN)){
					msg[ID_POS]=temp;
					idx = 4;
					next_state = LOCKED;
					break;
				}
				next_state = LISTENING;
				break;
			case LOCKED:
				msg[idx] = temp;
				if (idx == 5) max_size = ((msg[5] >> BYTE) && msg[4]) + TOT_HDR_LEN;
				if (idx < max_size) idx++;
				else cont_get_char = 0;
				break;
			default: break;
		}
		state = next_state;
		//DEBUG_PRINT(" cur char: 0x%x%x", temp>>4,(temp&0xf));
		DEBUG_PRINT("%c", temp);
	}
	if ((msg[SYNC_CHAR1_POS]==SYNC_CHAR1) && (msg[SYNC_CHAR2_POS]==SYNC_CHAR2)){
		if ((msg[CLASS_POS] == NAV_MSG_CLASS) && (msg[ID_POS] == NAV_POSECEF_ID)){
			memcpy(msg, nav_posecef_msg, TOT_HDR_LEN + NAV_POSECEF_LEN);
			new_nav_msg =NEW;
		}
		if ((msg[CLASS_POS] == ACK_MSG_CLASS) && (msg[ID_POS] == ACK_ID)){
			memcpy(msg, ack_msg, TOT_HDR_LEN + ACK_ACK_LEN);
			new_ack_msg =NEW;
		}
		if ((msg[CLASS_POS] == NAV_MSG_CLASS) && (msg[ID_POS] == NAV_STATUS_ID)){
			memcpy(msg, nav_status_msg, TOT_HDR_LEN + NAV_STATUS_LEN);
			new_fix_msg =NEW;
		}

	}
	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
	DEBUG_PRINT("\n\r done handler");
}

void init_uart(void){
	UARTConfigSetExpClk(UARTA1_BASE,PRCMPeripheralClockGet(PRCM_UARTA1),
				9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
						UART_CONFIG_PAR_NONE));
	UARTFIFOLevelSet(UARTA1_BASE,UART_FIFO_TX7_8, UART_FIFO_RX7_8);
	UARTFIFOEnable(UARTA1_BASE); //Disable FIFO
	UARTIntRegister(UARTA1_BASE, uart_int_handler);
	UARTIntEnable(UARTA1_BASE, UART_INT_RX); //enable interrupts
	UARTEnable(UARTA1_BASE);
}


