/*
 * GPS.c
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */


#include "includes.h"
#include "GPS.h"

void GPS_on(void)
{
	GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0x00); //Turn on GPS
}

void GPS_off(void)
{
	GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0xFF); //Turn off GPS
}
