/*
 * Display.h
 *
 *  Created on: Mar 10, 2023
 *      Author: phang
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "DS3231.h"

typedef enum {
	HR_AND_MIN,
	DAY_OF_WEEK,
	DATE_AND_MONTH,
} time_component_t;

void Display_LED(SPI_HandleTypeDef *hspi, DS3231_HandleTypeDef *ds3231);

#endif /* INC_DISPLAY_H_ */
