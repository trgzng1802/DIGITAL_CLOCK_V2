/*
 * Display.c
 *
 *  Created on: Mar 10, 2023
 *      Author: phang
 */
#include "Display.h"


const uint8_t led_number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t led_data_buf[4] = {};
time_component_t time_component = HR_AND_MIN;

void Display_LED(SPI_HandleTypeDef *hspi, DS3231_HandleTypeDef *ds3231)
{
    switch (time_component)
    {
    case HR_AND_MIN:
        led_data_buf[0] = led_number[(ds3231->current_minute) % 10];
        led_data_buf[1] = led_number[(ds3231->current_minute) / 10];
        led_data_buf[2] = led_number[(ds3231->current_hour) % 10];
        led_data_buf[3] = led_number[(ds3231->current_hour) / 10];
        break;
    
    case DAY_OF_WEEK:
        if (ds3231->current_day)
        {
            led_data_buf[0] = 0x54;
            led_data_buf[1] = 0x39;
        } else
        {
            led_data_buf[0] = led_number[ds3231->current_day];
            led_data_buf[1] = 0x78;
        }
        led_data_buf[2] = 0x00;
        led_data_buf[3] = 0x00;
        break;

    case DATE_AND_MONTH:
        led_data_buf[0] = led_number[(ds3231->current_date) % 10];
        led_data_buf[1] = led_number[(ds3231->current_date) / 10];
        led_data_buf[2] = led_number[(ds3231->current_month) % 10];
        led_data_buf[3] = led_number[(ds3231->current_month) / 10];
        break;

    default:
        break;
    }

    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, 0);
    HAL_SPI_Transmit(hspi, led_data_buf, 4, 1000);
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, 1);
}
