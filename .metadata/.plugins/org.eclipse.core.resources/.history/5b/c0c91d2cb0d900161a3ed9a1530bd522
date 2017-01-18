/*
 * SD_card.h
 *
 *  Created on: Aug 4, 2016
 *      Author: Rafi
 */

#ifndef SD_CARD_H_
#define SD_CARD_H_

#define SD_OPEN_IF_EXISTS 		FA_READ|FA_WRITE|FA_OPEN_EXISTING 	//Opens if exists, fails otherwise
#define SD_CREATE_OR_OPEN		FA_READ|FA_WRITE|FA_OPEN_ALWAYS		//Open if exists, creates new otherwise
#define SD_CREATE_AND_DELETE	FA_READ|FA_WRITE|FA_CREATE_ALWAYS	//Creates new, deletes if exists

//Internal funstions
void SD_on(void);
void SD_off(void);

//External functions
void init_SD_card(void);
int SD_write_file(char* file, char* text, int len, char options);



#endif /* SD_CARD_H_ */
