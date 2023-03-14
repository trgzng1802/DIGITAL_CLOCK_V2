/*
 * RTC.c
 *
 *  Created on: Mar 10, 2023
 *      Author: phang
 */
#define DS3231_ADDRESS 	0xD0
#define START_ADDRESS 	0x00

#include "DS3231.h"

static uint8_t Dec_To_Bcd(uint8_t val)
{
  return  ((val / 10 * 16) + (val % 10));
}

static uint8_t Bcd_To_Dec(uint8_t val)
{
  return ((val / 16 * 10) + (val % 16));
}

void DS3231_Init(DS3231_HandleTypeDef *p_ds3231, I2C_HandleTypeDef *ds3231_i2c)
{
	p_ds3231->hi2c = ds3231_i2c;
}

void DS3231_Set_Time(DS3231_HandleTypeDef *p_ds3231, uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
	uint8_t set_time_buf[7];
	set_time_buf[0] = Dec_To_Bcd(sec);
	set_time_buf[1] = Dec_To_Bcd(min);
	set_time_buf[2] = Dec_To_Bcd(hour);
	set_time_buf[3] = Dec_To_Bcd(day);
	set_time_buf[4] = Dec_To_Bcd(date);
	set_time_buf[5] = Dec_To_Bcd(month);
	set_time_buf[6] = Dec_To_Bcd(year);

	HAL_I2C_Mem_Write(p_ds3231->hi2c, DS3231_ADDRESS, START_ADDRESS, I2C_MEMADD_SIZE_8BIT, set_time_buf, 7, 1000);
}

void DS3231_Get_Time(DS3231_HandleTypeDef *p_ds3231)
{
	uint8_t get_time_buf[7];

	HAL_I2C_Mem_Read(p_ds3231->hi2c, DS3231_ADDRESS, START_ADDRESS, I2C_MEMADD_SIZE_8BIT, get_time_buf, 7, 1000);

	p_ds3231->current_second = Bcd_To_Dec(get_time_buf[0]);
	p_ds3231->current_minute = Bcd_To_Dec(get_time_buf[1]);
	p_ds3231->current_hour = Bcd_To_Dec(get_time_buf[2]);
	p_ds3231->current_day = Bcd_To_Dec(get_time_buf[3]);
	p_ds3231->current_date = Bcd_To_Dec(get_time_buf[4]);
	p_ds3231->current_month = Bcd_To_Dec(get_time_buf[5]);
	p_ds3231->current_year = Bcd_To_Dec(get_time_buf[6]);
}
