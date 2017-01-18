/*
 * SD_card.c
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */
#include "SD_card.h"
#include "includes.h"


void SD_on(void)
{
	GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, 0x00); //Turn on SD
}

void SD_off(void)
{
	GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, 0xFF); //Turn off SD
}

void init_SD_card(void)
{
	//
	// Enable MMCHS
	//
	PRCMPeripheralClkEnable(PRCM_SDHOST, PRCM_RUN_MODE_CLK);

	//
	// Reset MMCHS
	//
	PRCMPeripheralReset(PRCM_SDHOST);

	//
	// Configure MMCHS
	//
	SDHostInit(SDHOST_BASE);

	//
	// Configure card clock
	//
	SDHostSetExpClk(SDHOST_BASE, PRCMPeripheralClockGet(PRCM_SDHOST), 15000000);
}




int SD_write_file(char* file, char* text, int len, char options)
{
	FIL fp;
	FATFS fs;
	FRESULT res;
	DIR dir;
	UINT Size;

	SD_on();

	res = f_mount(&fs,"0",1);
	if(res!=FR_OK)	return res;

	res = f_opendir(&dir,"/");
	if(res!=FR_OK)	return res;

	res = f_open(&fp,file, options);  //FA_CREATE_ALWAYS|FA_READ|FA_WRITE
	if(res!=FR_OK)	return res;

	res = f_write(&fp,text,len,&Size);
	if(res!=FR_OK)	return res;

	res = f_close(&fp);
	if(res!=FR_OK)	return res;

	SD_off();

	return 0;
}
