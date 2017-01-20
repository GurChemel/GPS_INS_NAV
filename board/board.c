/*
 *board.c
 *
 *  Created on: 13 Jan 2017
 *      Author: Samsung
 */

#include "../includes/std_inc.h"
#include "../includes/ex_common.h"
#include "../includes/inc.h"
#include "../includes/driverlib.h"

#include "simplelink.h"
#include "../includes/parameters.h"


#include "board.h"

#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
void BoardInit(){

	//IntVTableBaseSet((unsigned long)&g_pfnVectors[0]); //TODO: resolve this issue

	IntMasterEnable();
	IntEnable(FAULT_SYSTICK);

	PRCMCC3200MCUInit();
}


