/*
 * flash.h
 *
 *  Created on: Apr 5, 2023
 *      Author: DELL
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "stm32l0xx_hal.h"
#include <string.h>
#include <stdio.h>

uint32_t flashWriteData (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords);

void flashReadData (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Convert_To_Str (uint32_t *Data, char *Buf);

void flashWriteNumber (uint32_t StartSectorAddress, float Num);

float flashReadNumber (uint32_t StartSectorAddress);

uint32_t deletePage();

#endif /* INC_FLASH_H_ */
