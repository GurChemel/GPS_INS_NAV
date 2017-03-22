/*
 * GPS.c
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */
#include "sensors.h"
#include "math.h"
#include "../interfaces/local_uart_if.h"
#include "../includes/infrastructure.h"

/****************************************************************************************************/
int init_gps (){
	int i;
	boot_time = ON;
	GPS_off();
	for(i=0;i<100000;i++){}
	GPS_on();
	DEBUG_PRINT("\n\r\t\t gps on \n\r");
	init_uart();
	if(!NMEA){
		int status = cfg_gps_uart_and_protocol();
		//while(1){}
		if(!status) return CFG_GPS_FAIL;
		DEBUG_PRINT("\n\r\t\t cfg_gps_uart_and_protocol \n\r");
		status = disable_ubx_periodic();
		if(!status) return DIS_UBX_P;
		status = enable_ubx_periodic();
		if(!status) return EN_UBX_P;
		status = get_fixed_pos();
		if(!status) return FIX_NOT_AQUIRED;
		boot_time=OFF;
	}
	else{
		//cfg_NMEA_if();
		//while(1){};
		get_fixed_pos();
	}
	return GOOD_OP;
}
/****************************************************************************************************/
int get_fixed_pos(){
	int fixed_pos = NO_FIX;
	reset_global_int();
	if (!NMEA){
		char* status_poll_msg = build_gps_ubx_msg(NAV_MSG_CLASS, NAV_STATUS_ID, POLL_PAYLOAD_ANY_LEN, NULL);
		while(fixed_pos == NO_FIX){
				send_uart_message(status_poll_msg, POLL_MSG_TOT_LEN);
				while (new_gps_msg == 0){}
				parse_recieved_msg();
				if (new_fix_msg && (nav_status_msg[PAYLOAD_START_POS+NAV_STATUS_FLAGS] & FIX)){
					fixed_pos = FIX;
					new_fix_msg = OLD;
					DEBUG_PRINT("\n\r\t\t Got Fixed! \n\r");
					free (status_poll_msg);
				}
		}
	}else{
		while(!fixOk){}

		fixed_pos=FIX;
	}
	return fixed_pos;
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
	print_msg(msg_prt_payload,CFG_PRT_LEN);
	char* msg =build_gps_ubx_msg(CFG_MSG_CLASS, CFG_PRT_ID, CFG_PRT_LEN, msg_prt_payload);
	DEBUG_PRINT("\n\r\t\t uart config message: \n\r");
	print_msg(msg, CFG_PRT_LEN+TOT_HDR_LEN);
	int status = send_uart_message(msg, CFG_PRT_LEN+TOT_HDR_LEN);
	if (status == BAD_OP) DEBUG_PRINT("\n\r\t\t failed send cfg uart msg \n\r");
	//status = verify_message(CFG_MSG_CLASS,CFG_PRT_ID); //ack in uart
	free(msg);
	return status;
}
/****************************************************************************************************/
void print_msg (char* msg, int msg_len){
	int i;
	DEBUG_PRINT("\n\r message: ");
	if (!NMEA){
		DEBUG_PRINT(" 0x");
		for (i=0; i< msg_len; i++) DEBUG_PRINT("%c", msg[i]);
	}
	else for (i=0; i< msg_len; i++) DEBUG_PRINT("%c", msg[i]);
	//DEBUG_PRINT("\n\r");
}
/****************************************************************************************************/
void build_NMEA_cfg_msg(char* msg, int msg_id){
	//char X,Y,Z;
	char cr = 0xd, lf = 0xa;
	char CK_A=0, CK_B=0;
	char temp_msg[PUBX_40_FL+1]={0};// = "$PUBX,40,DTM,0,0,0,0,0,0*000";
	strcpy(temp_msg,"$PUBX,40,XYZ,0,0,0,0,0,0*00");
	//temp_msg[6]=40;
	if (!HARD_CODED){
		/*switch (msg_id){
				case DTM:
					copy_char_arr(temp_msg+9,"DTM",3);
					//X='D';Y='T';Z='M';
					break;
				case GBS:
					copy_char_arr(temp_msg+9, "GBS",3);
					//X='G';Y='B';Z='S';
					break;
				case GGA:
					copy_char_arr(temp_msg+9,"GGA",3);
					////X='G';Y='G';Z='A';
					break;
				case GLL:
					copy_char_arr(temp_msg+9, "GLL",3);
					 //X='G';Y='L';Z='L';
					 break;
				case GPQ:
					copy_char_arr(temp_msg+9, "GPQ",3);
					 //X='G';Y='P';Z='Q';
					 break;
				case GRS:
					copy_char_arr(temp_msg+9, "GRS",3);
					 //X='G';Y='R';Z='S';
					 break;
				case GSA:
					copy_char_arr(temp_msg+9, "GSA",3);
					 //X='G';Y='S';Z='A';
					 break;
				case GST:
					copy_char_arr(temp_msg+9, "GST",3);
					 //X='G';Y='S';Z='T';
					 break;
				case GSV:
					copy_char_arr(temp_msg+9, "GSV",3);
					 //X='G';Y='S';Z='V';
					 break;
				case THS:
					copy_char_arr(temp_msg+9, "THS",3);
					 //X='T';Y='H';Z='S';
					 break;
				case TXT:
					copy_char_arr(temp_msg+9, "TXT",3);
					 //X='T';Y='X';Z='T';
					 break;
				case VTG:
					copy_char_arr(temp_msg+9, "VTG",3);
					 //X='V';Y='T';Z='G';
					 break;
				case ZDA:
					copy_char_arr(temp_msg+9, "ZDA",3);
					 //X='Z';Y='D';Z='A';
					 break;
				case RMC:
					copy_char_arr(temp_msg+9, "RMC",3);
					 //X='T';Y='H';Z='S';
				default: break;
			 }
			 calc_msg_checksum (&CK_A, &CK_B, temp_msg, PUBX_40_BDY_LEN);
			 temp_msg[CK_POS_HIGH] = CK_A;
			 temp_msg[CK_POS_LOW] = CK_B;
			 temp_msg[PUBX_40_FL-2]=cr;
			 temp_msg[PUBX_40_FL-1]=lf;
			 copy_char_arr(msg,temp_msg , PUBX_40_FL);*/
	} else {
		switch (msg_id){
						case GGA:
							strcpy(msg,"$PUBX,40,GGA,1,1,1,0*5B\r\n");
							break;
						case GLL:
							strcpy(msg,"$PUBX,40,GLL,0,0,0,0*5C \r\n");
							 break;
						case GSA:
							strcpy(msg,"$PUBX,40,GSA,0,0,0,0*4E\r\n");
							 break;
						case GSV:
							strcpy(msg,"$PUBX,40,GSV,0,0,0,0*59\r\n");
							 break;
						case VTG:
							strcpy(msg,"$PUBX,40,VTG,0,0,0,0*5E\r\n");
							 break;
						case RMC:
							strcpy(msg,"$PUBX,40,RMC,0,0,0,0*47\r\n");
							break;
						default: break;
					 }

	}
			 //temp_msg[X_POS]=X; temp_msg[Y_POS]=Y; temp_msg[Z_POS]=Z;
			 print_msg (msg, PUBX_40_FL);

}
/****************************************************************************************************/
void cfg_NMEA_if (){
	int msg_id;
	int i=0;
	UARTIntDisable(UARTA1_BASE, UART_INT_RX);
	char msg[PUBX_40_FL]={0};
	for (msg_id=GGA; msg_id<=RMC; msg_id++){
		 for (i=0; i<10; i++){
			 build_NMEA_cfg_msg(msg,msg_id);
			 send_uart_message(msg, PUBX_40_FL);
		 }
	}
	while (i<16000000){i++;}
	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
	//while(1){}
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
	for (i=0; i<(MSG_TO_DIS*2); i+=2){
		char disable_payload [CFG_MSG_LEN] = {msg_to_disable[i],msg_to_disable[i+1],IDLE};
		disable_msg = build_gps_ubx_msg(CFG_MSG_CLASS, CFG_MSG_ID, CFG_MSG_LEN, disable_payload);
		print_msg(disable_msg, CFG_MSG_LEN+TOT_HDR_LEN);
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
	for (i=0; i < (MSG_TO_EN*2); i+=2){
		char enable_payload[CFG_MSG_LEN] = {msg_to_enable[i],msg_to_enable[i+1], MSG_RATE};
		enable_msg = build_gps_ubx_msg(CFG_MSG_CLASS, CFG_MSG_ID, CFG_MSG_LEN, enable_payload);
		print_msg(enable_msg, CFG_MSG_LEN+TOT_HDR_LEN);
		status = send_uart_message(enable_msg, (CFG_PRT_LEN+TOT_HDR_LEN));
		free(enable_msg);
		if (BAD_OP == status) return BAD_OP;
		status = verify_message(CFG_MSG_CLASS,CFG_MSG_ID);
		if (BAD_OP == status) return BAD_OP;
	}
	return GOOD_OP;
}
/****************************************************************************************************/
char* build_gps_ubx_msg(unsigned char msg_class, unsigned char msg_id, int msg_len, char* payload){
	char ck_a=0, ck_b=0;
	int pos;
	int msg_tot_len	     = TOT_HDR_LEN + msg_len;
	int length_to_chksum = MSG_HDR_LEN + MSG_CLASS_LEN + MSG_ID_LEN+ MSG_LEN_IND + msg_len;
	int ck_a_pos = msg_tot_len - 2;
	int ck_b_pos = msg_tot_len - 1;
	char msg_len_low  = msg_len;
	char msg_len_high = msg_len >> BYTE;
	char* msg = (char*)malloc(msg_tot_len);
	for (pos = 0; pos<PAYLOAD_START_POS ;pos++)
		switch (pos){
			case SYNC_CHAR1_POS:
				msg[pos] = SYNC_CHAR1;
				break;
			case SYNC_CHAR2_POS:
				msg[pos] = SYNC_CHAR2;
				break;
			case CLASS_POS:
				msg[pos] = msg_class;
				DEBUG_PRINT("\n\rmsg_class: 0x%x", msg[pos]);
				break;
			case ID_POS:
				msg[pos] = msg_id;
				DEBUG_PRINT("\n\r msg_ID: 0x%x", msg[pos]);
				break;
			case LEN_LOW_POS:
				msg[pos] = make_ltl_end(msg_len_low); //TODO: check if this is the order that should take place and if should be inverted to little endian
				DEBUG_PRINT("\n\r msg_len_low: 0x%x", msg[pos]);
				break;
			case LEN_HIGH_POS:
				msg[pos] = make_ltl_end(msg_len_high) ;
				DEBUG_PRINT("\n\r msg_len_high: 0x%x", msg[pos]);
				break;
			default: break;
		}
	if(payload != NULL) copy_char_arr (msg+sizeof(char)*PAYLOAD_START_POS, payload,msg_len);
	calc_msg_checksum (&ck_a, &ck_b, msg ,length_to_chksum);
	msg[ck_a_pos] =ck_a;
	msg[ck_b_pos] =ck_b;
	return msg;
}
/****************************************************************************************************/
void copy_char_arr(char* dest,char* src ,int len) {
	int i;
	for (i=0;i<len;i++){
		dest[i]=src[i];
	}
}
/****************************************************************************************************/
void calc_msg_checksum (char* CK_A, char* CK_B, char* msg_body, int msg_body_len){
	int byte_num, bit_num;
	char current_byte;
	if (!NMEA){
		for(byte_num=CLASS_POS; byte_num<msg_body_len; byte_num++){
			current_byte = *(msg_body+sizeof(char)*byte_num);
			for (bit_num=0; bit_num<BYTE; bit_num++){
				*CK_A = *CK_A + (current_byte & 0x1);
				*CK_B = *CK_B + *CK_A;
				 current_byte = current_byte >> BIT;
			}
		}
	}
	else {
		*CK_A = msg_body[IDENTIFIER_START_POS];
		for(byte_num = IDENTIFIER_START_POS+1; byte_num<=msg_body_len; byte_num++)
			*CK_A = *CK_A ^ msg_body[byte_num];
		*CK_B = (*CK_A & 0xf)<10 ? (*CK_A & 0xf) + 48 : (*CK_A & 0xf) + 55;//ascii value for int
		*CK_A = (*CK_A >> 4) <10 ? (*CK_A >> 4)  + 48 : (*CK_A >> 4)  + 55;
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
	int byte_idx;
	UARTIntDisable(UARTA1_BASE, UART_INT_RX);
	for (byte_idx=0; byte_idx< length; byte_idx++){
		//DEBUG_PRINT("\n\r\t\t byte num: %d  ",byte_idx);
		//while (!UARTSpaceAvail(UARTA1_BASE)){}
		UARTCharPut(UARTA1_BASE, msg[byte_idx]);
		//DEBUG_PRINT(" - sent!");
	}
	DEBUG_PRINT("  - message sent!");
	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
	return GOOD_OP;
}
/****************************************************************************************************/
int verify_message(char class, char id){//TODO: think with Gur if this can create bugs
	int verify = BAD_OP;
	while (new_ack_msg == OLD){}
	DEBUG_PRINT("\n\r new msg\n\r");
	if (new_ack_msg == NEW){
		print_msg(ack_msg, ACK_ACK_LEN+TOT_HDR_LEN);
		verify = ((ack_msg[CLASS_ACK_POS] == class) ? ((ack_msg[ID_ACK_POS] == id) ? GOOD_OP : BAD_OP) : BAD_OP) ;
		new_ack_msg = OLD;
	}
	return verify;
}
/****************************************************************************************************/
char make_ltl_end(char word){
	char temp =0xff;
	int i;
	for (i=1;i<=BYTE;i++){
		temp = (temp << BIT) + (word&0x1);
		word= (word >> BIT) ;
	}
	//DEBUG_PRINT("0x%x",temp);
	return temp;
}

double ascii_2_num (char* ascii, int length){
	int i, before_dot=1;
	double num=0;
	for (i=0; i<length;i++){
		if(ascii[i]=='.'){
			before_dot =0;
			continue;
		}
		num = before_dot ? num+(ascii[i]-48)*10 : num+((double)(ascii[i]-48))/pow(10,i);
	}
	return num;
}

void gga_2_llh (char* message, double* llh) {
		char *token;
		char tmp[8];

		token = strtok(message, ",");
		token = strtok(NULL, ","); // Date and time
		token = strtok(NULL, ","); // Latitude
		strncpy(tmp, token, 2);
		tmp[2] = 0;
		llh[0] = atof(tmp) + atof(token+2)/60.0;

		token = strtok(NULL, ","); // North or south
		if (token[0]=='S'){
			llh[0] *= -1.0;
		}

		token = strtok(NULL, ","); // Longitude
		strncpy(tmp, token, 3);
		tmp[3] = 0;
		llh[1] = atof(tmp) + atof(token+3)/60.0;

		token = strtok(NULL, ","); // East or west
		if (token[0]=='W'){
			llh[1] *= -1.0;
		}

		token = strtok(NULL, ","); // GPS fix
		token = strtok(NULL, ","); // Number of satellites
		token = strtok(NULL, ","); // HDOP
		token = strtok(NULL, ","); // Altitude above meas sea level
		llh[2] = atof(token);

		token = strtok(NULL, ","); // in meter
		token = strtok(NULL, ","); // Geoid height above WGS84 ellipsoid
		llh[2] += atof(token);

		return;
}

int get_lon_lat(gps_local_data_NMEA_str* gps_data) {

	if (!fixOk) {
	//GPIOPinWrite(GPIOA0_BASE, GPIO_PIN_7, 0x00);
	return BAD_DATA;
	}
	double llh[3];
	gga_2_llh (NMEA_msg,llh);
	gps_data->lat = llh[0];
	gps_data->lon = llh[1];
	gps_data->alt = llh[2];
	//DEBUG_PRINT("lat_deg: %d",gps_data->lat_deg);
	//DEBUG_PRINT("lat_min: %d",gps_data->lat_min);
	//DEBUG_PRINT("lon_deg: %d",gps_data->lon_deg);
	//DEBUG_PRINT("lon_min: %d",gps_data->lon_min);
	//DEBUG_PRINT("POE: 0x%x",gps_data->POE);
	return GOOD_DATA;
}
