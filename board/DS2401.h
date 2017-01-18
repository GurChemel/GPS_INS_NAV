/*
 * OneWire.h
 *
 *  Created on: Sep 7, 2014
 *      Author: Rafi
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

int ds2401_get_number(unsigned char id[6]);
uint64_t ds2401_get_id_long(void);

void init_ds2401(void);

#endif /* ONEWIRE_H_ */
