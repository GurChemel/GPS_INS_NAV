/*
 * GPS.h
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */

#ifndef GPS_H_
#define GPS_H_


/**************************************************************************/
//Message structure
/**************************************************************************/
#define SYNC_CHAR1 		((unsigned char) 0xB5)
#define SYNC_CHAR2 		((unsigned char) 0x62)
#define MSG_HDR_LEN 	0x02
#define MSG_CLASS_LEN 	0x01
#define MSG_ID_LEN 		0x01
#define MSG_LEN_IND 	((unsigned char) 0x02)
#define MSG_CKS_LEN		0x02


#define SYNC_CHAR1_POS     0
#define SYNC_CHAR2_POS     1
#define CLASS_POS 		   2
#define ID_POS 		 	   3
#define PAYLOAD_START_POS  6
#define TOT_HDR_LEN        MSG_HDR_LEN+MSG_CLASS_LEN+MSG_ID_LEN+(int)MSG_LEN_IND+MSG_CKS_LEN

/**************************************************************************/
//classes defines
/**************************************************************************/
#define CFG_MSG_CLASS 	((unsigned char) 0x06)
#define NAV_MSG_CLASS 	((unsigned char) 0x01)
#define PUBX_MSG_CLASS 	((unsigned char) 0xF1)
#define NMEA_MSG_CLASS 	((unsigned char) 0xF0)
#define AID_MSG_CLASS 	((unsigned char) 0xF0)
#define ESF_MSG_CLASS 	((unsigned char) 0x10)
#define MON_MSG_CLASS 	((unsigned char) 0x0A)
#define RXM_MSG_CLASS 	((unsigned char) 0x02)
#define TIM_MSG_CLASS 	((unsigned char) 0x0D)
#define ACK_MSG_CLASS	((unsigned char) 0x05)

/**************************************************************************/
//ID defines
/**************************************************************************/
#define CFG_MSG_ID 		((unsigned char) 0x01)
#define CFG_PRT_ID 		((unsigned char) 0x00)
#define ACK_ID 			((unsigned char) 0x00)
#define NAK_ID 			((unsigned char) 0x01)

#define AID_ALP_ID		((unsigned char) 0x50)
//1
#define ESF_STATUS_ID	((unsigned char) 0x10)
//1
#define MON_HW2_ID		((unsigned char) 0x0B)
#define MON_HW_ID		((unsigned char) 0x09)
#define MON_IO_ID		((unsigned char) 0x02)
#define MON_MSGPP_ID    ((unsigned char) 0x06)
#define MON_RXBUF_ID	((unsigned char) 0x07)
#define MON_TXBUF_ID	((unsigned char) 0x08)
//6
#define NAV_AOPSTATUS_ID  	((unsigned char) 0x60)
#define NAV_CLOCK_ID  		((unsigned char) 0x22)
#define NAV_DGPS_ID  		((unsigned char) 0x31)
#define NAV_DOP_ID  		((unsigned char) 0x04)
#define NAV_EKFSTATUS_ID  	((unsigned char) 0x40)
#define NAV_POSECEF_ID  	((unsigned char) 0x01)
#define NAV_POSLLH_ID  		((unsigned char) 0x02)
#define NAV_SBAS_ID  		((unsigned char) 0x32)
#define NAV_SOL_ID  		((unsigned char) 0x06)
#define NAV_STATUS_ID  		((unsigned char) 0x03)
#define NAV_SVINFO_ID  		((unsigned char) 0x30)
#define NAV_TIMEGPS_ID  	((unsigned char) 0x20)
#define NAV_TIMEUTC_ID  	((unsigned char) 0x21)
#define NAV_VELECEF_ID  	((unsigned char) 0x11)
#define NAV_VELNED_ID  		((unsigned char) 0x12)
//15
#define RXM_ALM_ID  		((unsigned char) 0x30)
#define RXM_EPH_ID  		((unsigned char) 0x31)
#define RXM_RAW_ID  		((unsigned char) 0x10)
#define RXM_SFRB_ID  		((unsigned char) 0x11)
#define RXM_SVSI_ID  		((unsigned char) 0x20)
//5
#define TIM_SVIN_ID  		((unsigned char) 0x04)
#define TIM_TM2_ID  		((unsigned char) 0x03)
#define TIM_TP_ID  			((unsigned char) 0x01)
#define TIM_VRFY_ID  		((unsigned char) 0x06)
//4
#define MSG_TO_DIS 32
#define MSG_TO_EN  2


/**************************************************************************/
//Messages payload lengths
/**************************************************************************/
#define CFG_MSG_LEN 	((unsigned char) 3)
#define CFG_PRT_LEN 	((unsigned char) 20)
#define NAV_POSECEF_LEN ((unsigned char) 20)
#define ACK_ACK_LEN 	((unsigned char) 2)
#define ACK_NAK_LEN 	((unsigned char) 2)


/**************************************************************************/
//NAV-POSECEF payload structure
/**************************************************************************/
#define NAV_POSECEF_X   4
#define NAV_POSECEF_Y   8
#define NAV_POSECEF_Z   12
#define NAV_POSECEF_ACC 16


/**************************************************************************/
//ACK message structure
/**************************************************************************/
#define CLASS_ACK_POS 6
#define ID_ACK_POS	  7


/**************************************************************************/
//GPS CFG PRT payload structure
/**************************************************************************/
#define CFG_PRT_PORT_ID ((unsigned char) 1)

#define CHAR_LEN ((unsigned char) 3)
#define PARITY   ((unsigned char) 4)
#define STOP_BIT ((unsigned char) 0)

#define CHAR_LEN_BYTE ((unsigned char) CHAR_LEN << 6)
#define PARITY_BYTE ((unsigned char) (((STOP_BIT << 3 ) & PARITY) << 1))

#define IN_PROTO  ((unsigned char) 1)
#define OUT_PROTO ((unsigned char) 1)

#define BAUD_RATE 9600
#define BAUD_RATE0 (unsigned char)(BAUD_RATE)
#define BAUD_RATE1 (unsigned char)(BAUD_RATE >> BYTE)
#define BAUD_RATE2 (unsigned char)(BAUD_RATE >> 2*BYTE)
#define BAUD_RATE3 (unsigned char)(BAUD_RATE >> 3*BYTE)

#define MSG_RATE ((unsigned char) 1)
/********************************************************/
//general defines
/********************************************************/
#define IDLE ((unsigned char) 0)
#define RESET 0

#define DIS_UBX_P -1
#define EN_UBX_P  -2
#define CFG_GPS_FAIL -3

#define BAD_DATA  0
#define GOOD_DATA 1
#define GOOD_OP 1
#define BAD_OP 0

#define EMPTY_BYTE 0
#define BYTE 8
#define BIT 1

typedef struct {
	int X;
	int Y;
	int Z;
	int Acc;
}gps_local_data_str;

int init_gps ();
void GPS_on(void);
void GPS_off(void);
int cfg_gps_uart_and_protocol();
int disable_ubx_periodic();
int enable_ubx_periodic();
char* build_gps_ubx_msg(char msg_class, char msg_id, int msg_len, char* payload);
void calc_msg_checksum (char* CK_A, char* CK_B, char* msg_body, int msg_body_len);
int parse_ubx_nav_msg (gps_local_data_str* gps_data, char* data);
int send_uart_message(char* msg, int length);
int verify_message(char class, char id);
#endif /* GPS_H_ */
