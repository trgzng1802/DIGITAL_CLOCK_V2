/*
 * RTC.h
 *
 *  Created on: Mar 10, 2023
 *      Author: phang
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#include "main.h"

typedef struct {
	uint8_t current_hour;
	uint8_t current_minute;
	uint8_t current_second;
	uint8_t current_day;
	uint8_t current_date;
	uint8_t current_month;
	uint8_t current_year;
	I2C_HandleTypeDef *hi2c;
} DS3231_HandleTypeDef;

void DS3231_Init(DS3231_HandleTypeDef *p_ds3231, I2C_HandleTypeDef *ds3231_i2c);
void DS3231_Set_Time(DS3231_HandleTypeDef *p_ds3231, uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void DS3231_Get_Time(DS3231_HandleTypeDef *p_ds3231);
#endif /* INC_DS3231_H_ */
