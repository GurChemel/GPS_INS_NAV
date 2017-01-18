/*
 * borad.h
 *
 *  Created on: 13 Jan 2017
 *      Author: Samsung
 */

#ifndef INIT_HW_H_
#define INIT_HW_H_

#define CLOCK_PERIOD_NSEC 12.5
#define CLOCK_PERIOD_USEC 0.0125
#define CLOCK_PERIOD_MSEC 0.0000125
#define CLOCK_PERIOD_SEC  0.0000000125

#include "pinmux.h"
#include "SD_card.h"
#include "DS2401.h"

void BoardInit();

#endif /* INIT_HW_H_ */
