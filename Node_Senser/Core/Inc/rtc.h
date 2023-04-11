/*
 * rtc.h
 *
 *  Created on: Apr 10, 2023
 *      Author: DELL
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include <stdint.h>
#include "stdbool.h"

bool setAlarm(uint8_t Hours,uint8_t Minutes , uint8_t Seconds );
void getTime(uint8_t *data);
bool setTime(void);
uint8_t binaryToBCD(uint8_t binary);
#endif /* INC_RTC_H_ */
