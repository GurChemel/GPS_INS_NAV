//*****************************************************************************
// Copyright (C) 2014 Texas Instruments Incorporated
//
// All rights reserved. Property of Texas Instruments Incorporated.
// Restricted rights to use, duplicate or disclose this code are
// granted through contract.
// The program may not be used without the written permission of
// Texas Instruments Incorporated or against the terms and conditions
// stipulated in the agreement under which this program has been supplied,
// and under no circumstances can it be used with non-TI connectivity device.
//
//*****************************************************************************


//*****************************************************************************
//
// Application Name     - HTTP Client Demo
// Application Overview - This sample application demonstrates how to use
//                          HTTP Client (In Minimum mode) API for HTTP based
//                          application development.
//                          This application explain user to how to:
//                          1. Connect to an access point
//                          2. Connect to a HTTP Server with and without proxy
//                          3. Do POST, GET, PUT and DELETE
//                          4. Parse JSON data using “Jasmine JSON Parser”
// Note: To use HTTP Client in minimum mode, user need to compile library (webclient)
// 			with HTTPCli_LIBTYPE_MIN option.
//
// 			HTTP Client (minimal) library supports synchronous mode, redirection
// 			handling, chunked transfer encoding support, proxy support and TLS
// 			support (for SimpleLink Only. TLS on other platforms are disabled)
//
// 			HTTP Client (Full) library supports all the features of the minimal
// 			library + asynchronous mode and content handling support +
// 			TLS support (all platforms). To use HTTP Client in full mode user need
//			to compile library (webclient) with HTTPCli_LIBTYPE_MIN option. For full
//			mode RTOS is needed.
//
// Application Details  -
// http://processors.wiki.ti.com/index.php/
// or
// docs\examples\
//
//*****************************************************************************


#include "includes.h"

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************

#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif


//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
static void
DisplayBanner(char * AppName)
{
	UART_PRINT("\n\n\n\r");
	UART_PRINT("\t\t *************************************************\n\r");
	UART_PRINT("\t\t      CC3200 %s Application       \n\r", AppName);
	UART_PRINT("\t\t *************************************************\n\r");
	UART_PRINT("\n\n\n\r");
}


//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{

	IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);

	IntMasterEnable();
	IntEnable(FAULT_SYSTICK);

	PRCMCC3200MCUInit();
}

char printing;

void UART1_Handler(void)
{
	unsigned long UART_STATUS;
	//	char stringinging[] = "$GPRMC,165431.00,A,4029.88110,N,07424.85655,W,0.492,,030816,,,A*64";

	UART_STATUS = UARTIntStatus(UARTA1_BASE, true);
	UARTIntClear(UARTA1_BASE, UART_INT_RX);
	UARTIntDisable(UARTA1_BASE, UART_INT_RX);



	while((UART_STATUS & UART_INT_RX) && UARTCharsAvail(UARTA1_BASE))
	{
		printing = (char) UARTCharGetNonBlocking(UARTA1_BASE);
		//	printing = stringinging[kkk++];
		//	if(kkk>strlen(stringinging)) kkk=0;
		ParseGPS(printing);
		//if(gpsFix==0)	UART_PRINT(&printing);
	}

	UARTIntEnable(UARTA1_BASE, UART_INT_RX);
}




int main(void)
{
	long lRetVal = -1;
	HTTPCli_Struct httpClient;
	char pBuffer[100];



	BoardInit();
	PinMuxConfig();

	InitTerm();
	//
	// Clearing the Terminal.
	//
	ClearTerm();
	//GPIO_IF_LedConfigure(LED1|LED2|LED3);
	//DisplayBanner(APP_NAME);


	init_HMC5883(MAG_ADDR, true);
	if(init_ADXL345(ACC_ADDR)<0)
	{
		while(1)
		{
			UART_PRINT("!!! mag I2c Error\n\r");
		}
	}
	init_MPL115A2();
	init_ds2401();
	init_SD_card();

	GPS_on();
	GPS_off();

	SD_write_file("hello.txt", "my name is", strlen("my name is"), SD_CREATE_AND_DELETE);

	char strbuffer[128];
	char databuf[100];

	float Xmag=-1, Ymag=-1, Zmag=-1;
	float Xacc=-1, Yacc=-1, Zacc=-1;
	double roll=-1, pitch=-1, yaw=-1;
	float accMag=-1;

	float pressure;

	/*
	InitializeAppVariables();

	UART_PRINT("\n\r\n\rStops here on failure caused by debug!\n\r\n\r");
	lRetVal = ConnectToAP();

	if(lRetVal < 0)
	{
		UART_PRINT("\n\rError!!!\n\r");
		LOOP_FOREVER();
	}

	lRetVal = ConnectToHTTPServer(&httpClient);
	if(lRetVal < 0)
	{
		LOOP_FOREVER();
	}
	UART_PRINT("Connected to server!\n\r\n\r");
	 */
	GPIOPinWrite(GPIOA0_BASE, GPIO_PIN_7|GPIO_PIN_6, 0x00);
	//if(ADXL345_read_accdata(ACC_ADDR, &Xacc, &Yacc, &Zacc)<0) UART_PRINT("!!! acc I2c Error\n\r");
	while(1)
	{
		//if(gpsFix==1)
		//long acc_it =  GPIOPinRead(GPIOA0_BASE, GPIO_PIN_4);
		//GPIOPinWrite(GPIOA0_BASE, GPIO_PIN_7, 0xFF*(acc_it == 0));
		//if(acc_it>0)
		//{


		UART_PRINT("\33[H\33[2J");
		UART_PRINT("Software compiled: ");
		UART_PRINT(__TIME__);
		UART_PRINT(" ");
		UART_PRINT(__DATE__);
		UART_PRINT("\n\r");
		UART_PRINT("\n\rREADY...\n\r");

		while(abs(Xacc) < 5)
		{
			if(ADXL345_read_accdata(ACC_ADDR, &Xacc, &Yacc, &Zacc)<0) UART_PRINT("!!! acc I2c Error\n\r");
			accMag = sqrt(Xacc*Xacc + Yacc*Yacc + Zacc*Zacc);
		}
		accMag=100;
		UART_PRINT("\n");
		while(abs(accMag-1) > 0.1)
		{
			if(ADXL345_read_accdata(ACC_ADDR, &Xacc, &Yacc, &Zacc)<0) UART_PRINT("!!! acc I2c Error\n\r");
			accMag = sqrt(Xacc*Xacc + Yacc*Yacc + Zacc*Zacc);
			sprintf(databuf,"\n\r|ACC| = %f               ",accMag);
			UART_PRINT(databuf);
		}
		sprintf(databuf,"\r|ACC| = %f               ",accMag);
		UART_PRINT(databuf);
		UART_PRINT("\n\r");

		if(HMC5883_read_magdata(MAG_ADDR, &Xmag, &Ymag, &Zmag)<0) UART_PRINT("!!! mag I2c Error\n\r");

		IMU_calculate(-Xacc/accMag, -Yacc/accMag, Zacc/accMag, -Xmag, -Ymag, Zmag, &roll, &pitch, &yaw);
		int yawyaw = yaw;
		sprintf(databuf,"MAG=(%5f, %5f, %5f) ACC=(%5f, %5f, %5f) |ACC| = %f\n\r(roll, pitch, yaw) = (%5f, %5f, %5f)\n\r", Xmag, Ymag, Zmag, Xacc, Yacc, Zacc, accMag, roll, pitch, yaw);
		UART_PRINT(databuf);

		sprintf(databuf,"ID=%lld\n\r", ds2401_get_id_long());
		UART_PRINT(databuf);

		if(MPL115A2_get_pressure(&pressure)<0) UART_PRINT("!!! bar I2c Error\n\r");
		sprintf(pBuffer,"pressure=%fkPa\n\r", pressure);
		UART_PRINT(pBuffer);

		UART_PRINT("Wait for GPS lock here...");
		GPS_on();
		//	while(gpsFix==0)
		//	{
		//
		//	}
		gpsLat = 32.776674;
		gpsLong = 35.024696;
		sprintf(databuf,"Time:%d.%05d\n\rDate:%d\n\rLat:%ld Long:%ld\n\rFix:%s\n\r",
				gpsTime, gpsMsecs, gpsDate, gpsLat, gpsLong, (gpsFix>0)?"Yes":"No");
		GPS_off();
		UART_PRINT(databuf);

		sprintf(databuf,"X: %f    %f\n\rY:%f    %f\n\rZ:%f    %f\n\r",
				Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
		UART_PRINT(databuf);





		InitializeAppVariables();
		//ConfigureSimpleLinkToDefaultState();

		UART_PRINT("\n\r\n\rStops here on failure caused by debug!\n\r\n\r");
		lRetVal = ConnectToAP();

		if(lRetVal < 0)
		{
			UART_PRINT("\n\rError!!!\n\r");
			LOOP_FOREVER();
		}

		lRetVal = ConnectToHTTPServer(&httpClient);
		if(lRetVal < 0)
		{
			LOOP_FOREVER();
		}
		UART_PRINT("Connected to server!\n\r\n\r");

		sprintf(strbuffer,"/shots/get/%ld/%ld/%ld/%d/%d",(long) ds2401_get_id_long(), gpsLat, gpsLong, (int)pressure, yawyaw);

		//sprintf(strbuffer,"/shots/get/1/2/3/4/5");
		lRetVal = HTTPGetMethod(&httpClient, strbuffer);
		if(lRetVal < 0)
		{
			UART_PRINT("HTTP Post Get failed.\n\r");
		}
		UART_PRINT("HTTP Get sent to server! (");
		UART_PRINT(strbuffer);
		UART_PRINT(")\n\r\n\r");

		HTTPCli_disconnect(&httpClient);
		sl_WlanDisconnect();
		sl_Stop(30);
		UART_PRINT("Connection closed.\n\r");
	}

	HTTPCli_disconnect(&httpClient);
	sl_WlanDisconnect();
	UART_PRINT("Connection closed.\n\r");
	//LOOP_FOREVER();
	return 0;
}


void shot_routine(void)
{

}
