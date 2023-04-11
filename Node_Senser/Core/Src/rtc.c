/*
 * rtc.c
 *
 *  Created on: Apr 10, 2023
 *      Author: DELL
 */

#ifndef SRC_RTC_C_
#define SRC_RTC_C_

#include "rtc.h"
#include "stm32l0xx.h"

extern RTC_HandleTypeDef hrtc;


uint8_t binaryToBCD(uint8_t binary){
	if(binary<=9){
		return binary;
	}else {
		uint8_t fistNumber=0;
		uint8_t endNumber=0;
		uint8_t BCDNumber=0;
		fistNumber = (binary/10);
		endNumber = (binary%10);
		BCDNumber = (fistNumber<<4)|endNumber;
		return BCDNumber;
	}
}

bool setTime(void){
	  RTC_TimeTypeDef sTime = {0};
	  RTC_DateTypeDef sDate = {0};
	/** Initialize RTC and set the Time and Date
	  */
	  sTime.Hours = 0x15;
	  sTime.Minutes = 0x09;
	  sTime.Seconds = 0x00;
	  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	  {
	    return false;
	  }
	  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	  sDate.Month = RTC_MONTH_APRIL;
	  sDate.Date = 0x3;
	  sDate.Year = 0x23;

	  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	  {
		  return false;
	  }

	  /* USER CODE BEGIN Check_RTC_BKUP */
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x478);  // backup register
	  /* USER CODE END Check_RTC_BKUP */
	  return true;

}
void getTime(uint8_t *data)
{
  RTC_DateTypeDef gDate;
  RTC_TimeTypeDef gTime;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

  /* Display time Format: hh:mm:ss */
  *data = gTime.Hours;
  *(data+1)=gTime.Minutes;
  *(data+2)=gTime.Seconds;
}
bool setAlarm(uint8_t Hours,uint8_t Minutes , uint8_t Seconds  ){
		RTC_AlarmTypeDef sAlarm = {0};
	  sAlarm.AlarmTime.Hours = Hours;
	  sAlarm.AlarmTime.Minutes = Minutes;
	  sAlarm.AlarmTime.Seconds = Seconds;
	  sAlarm.AlarmTime.SubSeconds = 0x0;
	  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
	  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	  sAlarm.AlarmDateWeekDay = 0x3;
	  sAlarm.Alarm = RTC_ALARM_A;
	  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
	  {
		  return false;
	  }
	  return true;
}


#endif /* SRC_RTC_C_ */
