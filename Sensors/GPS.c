/*
 * GPS.c
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */
#include "sensors.h"
#include "../interfaces/local_uart_if.h"
/****************************************************************************************************/
int init_gps (){
	GPS_on();
	init_uart();
	int status = cfg_gps_uart_and_protocol();
	if(!status) return CFG_GPS_FAIL;
	status = disable_ubx_periodic();
	if(!status) return DIS_UBX_P;
	status = enable_ubx_periodic();
	if(!status) return EN_UBX_P;
	return GOOD_OP;
}
/****************************************************************************************************/
void GPS_on(void){
	GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0x00); //Turn on GPS
}
/****************************************************************************************************/
void GPS_off(void){
	GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0xFF); //Turn off GPS
}
/****************************************************************************************************/
int cfg_gps_uart_and_protocol(){
	char msg_prt_payload[CFG_PRT_LEN] = {CFG_PRT_PORT_ID, IDLE, IDLE, IDLE, CHAR_LEN_BYTE,
										 PARITY_BYTE, IDLE, IDLE, BAUD_RATE0, BAUD_RATE1, BAUD_RATE2,
										 BAUD_RATE3, IN_PROTO, IDLE, OUT_PROTO, IDLE, IDLE, IDLE, IDLE,
										 IDLE};
	char* msg =build_gps_ubx_msg(CFG_MSG_CLASS, CFG_PRT_ID, CFG_PRT_LEN, msg_prt_payload);
	int status;
	status =1;
	//send_uart_message(msg, CFG_PRT_LEN);
	//status = verify_message(); //ack in uart
	free(msg);
	return status;
}
/****************************************************************************************************/
int disable_ubx_periodic(){
	char msg_to_disable[MSG_TO_DIS*2] = {AID_MSG_CLASS, AID_ALP_ID,//even- class, odd-id- all along
										 ESF_MSG_CLASS, ESF_STATUS_ID,
										 MON_MSG_CLASS, MON_HW2_ID, MON_MSG_CLASS, MON_HW_ID, MON_MSG_CLASS, MON_IO_ID, MON_MSG_CLASS, MON_MSGPP_ID, MON_MSG_CLASS, MON_RXBUF_ID, MON_MSG_CLASS, MON_TXBUF_ID,
										 NAV_MSG_CLASS, NAV_AOPSTATUS_ID, NAV_MSG_CLASS, NAV_CLOCK_ID, NAV_MSG_CLASS, NAV_DGPS_ID, NAV_MSG_CLASS, NAV_DOP_ID, NAV_MSG_CLASS, NAV_EKFSTATUS_ID,
										 NAV_MSG_CLASS, NAV_POSECEF_ID, NAV_MSG_CLASS, NAV_POSLLH_ID, NAV_MSG_CLASS, NAV_SBAS_ID, NAV_MSG_CLASS, NAV_SOL_ID, NAV_MSG_CLASS, NAV_STATUS_ID,
										 NAV_MSG_CLASS, NAV_SVINFO_ID, NAV_MSG_CLASS, NAV_TIMEGPS_ID, NAV_MSG_CLASS, NAV_TIMEUTC_ID, NAV_MSG_CLASS, NAV_VELECEF_ID, NAV_MSG_CLASS, NAV_VELNED_ID,
										 RXM_MSG_CLASS, RXM_ALM_ID, RXM_MSG_CLASS, RXM_EPH_ID, RXM_MSG_CLASS, RXM_RAW_ID, RXM_MSG_CLASS, RXM_SFRB_ID, RXM_MSG_CLASS, RXM_SVSI_ID,
										 TIM_MSG_CLASS, TIM_SVIN_ID, TIM_MSG_CLASS, TIM_TM2_ID, TIM_MSG_CLASS, TIM_TP_ID, TIM_MSG_CLASS, TIM_VRFY_ID};
	int i, status;
	char* disable_msg;
	for (i=0; i<(MSG_TO_DIS*2); i+2){
		char disable_payload [CFG_MSG_LEN] = {msg_to_disable[i],msg_to_disable[i+1],IDLE};
		disable_msg = build_gps_ubx_msg(CFG_MSG_CLASS, CFG_MSG_ID, CFG_MSG_LEN, disable_payload);
		status = send_uart_message(disable_msg, (CFG_PRT_LEN+TOT_HDR_LEN));
		free(disable_msg);
		if (BAD_OP == status) return BAD_OP;
		status = verify_message(msg_to_disable[i],msg_to_disable[i+1]);
		if (BAD_OP == status) return BAD_OP;
	}
	return GOOD_OP;
}
/****************************************************************************************************/
int enable_ubx_periodic(){
	char msg_to_enable[MSG_TO_EN*2] = {NAV_MSG_CLASS, NAV_POSECEF_ID, NAV_MSG_CLASS, NAV_STATUS_ID};
	int i, status;
	char* enable_msg;
	for (i=0; i < (MSG_TO_EN*2); i+2){
		char enable_payload[CFG_MSG_LEN] = {msg_to_enable[i],msg_to_enable[i+1], MSG_RATE};
		enable_msg = build_gps_ubx_msg(CFG_MSG_CLASS, CFG_MSG_ID, CFG_MSG_LEN, enable_payload);
		status = send_uart_message(enable_msg, (CFG_PRT_LEN+TOT_HDR_LEN));
		free(enable_msg);
		if (BAD_OP == status) return BAD_OP;
		//status = verify_message();
		if (BAD_OP == status) return BAD_OP;
	}
	return GOOD_OP;
}
/****************************************************************************************************/
char* build_gps_ubx_msg(char msg_class, char msg_id, int msg_len, char* payload){
	char ck_a, ck_b;
	int msg_tot_len	 = MSG_HDR_LEN + MSG_CLASS_LEN + MSG_ID_LEN+ MSG_LEN_IND + msg_len + MSG_CKS_LEN;
	int msg_body_len = MSG_CLASS_LEN + MSG_ID_LEN+ MSG_LEN_IND + msg_len;
	int ck_a_pos = msg_tot_len -2;
	int ck_b_pos = msg_tot_len -1;
	char msg_len_low  = msg_len;
	char msg_len_high = msg_len >> BYTE;
	char* msg_body = (char*)malloc(msg_body_len);
	char temp_body[4] = {msg_class, msg_id, msg_len_low, msg_len_high};
	memcpy(msg_body, temp_body, 4);
	memcpy ((msg_body+4*sizeof(char)), payload, strlen(payload));
	calc_msg_checksum (&ck_a, &ck_b, msg_body,msg_body_len);
	free (msg_body);
	char* msg = (char*)malloc(msg_tot_len);
	char temp [6*BYTE] = {SYNC_CHAR1, SYNC_CHAR2, msg_class, msg_id, msg_len_low, msg_len_high};
	memcpy(msg, temp, 6);
	memcpy ((msg+6*sizeof(char)),payload,strlen(payload));
	msg[ck_a_pos] =ck_a;
	msg[ck_b_pos] =ck_b;
	return msg;
}
/****************************************************************************************************/
void calc_msg_checksum (char* CK_A, char* CK_B, char* msg_body, int msg_body_len){
	int byte_num, bit_num;
	char current_byte;
	for(byte_num=0; byte_num<msg_body_len; byte_num++){
		current_byte = *(msg_body+sizeof(char)*byte_num);
		for (bit_num=0; bit_num<BYTE; bit_num++){
			*CK_A = *CK_A + (current_byte & 0x1);
			*CK_B = *CK_B + *CK_A;
			 current_byte = current_byte << BIT;
		}
	}
}
/****************************************************************************************************/
int parse_ubx_nav_msg (gps_local_data_str* gps_data, char* data){
	if ((data[SYNC_CHAR1_POS] != SYNC_CHAR1) || (data[SYNC_CHAR2_POS] != SYNC_CHAR2)) return BAD_DATA;
	int i;
	int X = RESET, Y = RESET, Z = RESET, Acc= RESET;
	for (i = BYTE-1; i >= 0 ;i--){
		X   = (X << BYTE)   & data[PAYLOAD_START_POS + NAV_POSECEF_X + i];
		Y   = (Y << BYTE)   & data[PAYLOAD_START_POS + NAV_POSECEF_Y + i];
		Z   = (Z << BYTE)   & data[PAYLOAD_START_POS + NAV_POSECEF_Z + i];
		Acc = (Acc << BYTE) & data[PAYLOAD_START_POS + NAV_POSECEF_ACC + i];
	}
	gps_data->X = X; //cm
	gps_data->Y = Y; //cm
	gps_data->Z = Z; //cm
	gps_data->Acc = Acc; //cm
	return GOOD_DATA;
}
/****************************************************************************************************/
int send_uart_message(char* msg, int length){
	int byte_idx, status;
	for (byte_idx=0; byte_idx< length; byte_idx++){
		status = UARTCharPutNonBlocking(UARTA1_BASE, msg[byte_idx]);
		if (!status) return BAD_OP;
	}
	return GOOD_OP;
}
/****************************************************************************************************/
int verify_message(char class, char id){//TODO: think with Gur if this can create bugs
	int verify = BAD_OP;
	if (new_ack_msg == 1){
		//TODO: think: what if at this moment the ack havn't received yet?
		verify = ((ack_msg[CLASS_ACK_POS] == class) ? ((ack_msg[CLASS_ACK_POS] == class) ? GOOD_OP : BAD_OP) : BAD_OP) ;
	}
	return verify;
}
/****************************************************************************************************/




