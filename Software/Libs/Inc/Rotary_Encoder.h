/*
 * Rotary_Encoder.h
 *
 *  Created on: 9 Mar 2023
 *      Author: phang
 */

#ifndef INC_ROTARY_ENCODER_H_
#define INC_ROTARY_ENCODER_H_

#include "main.h"

typedef struct
{
	TIM_HandleTypeDef *re_timer;
	int16_t current_position;
	int16_t last_position;
} RE_HandleTypeDef;

extern RE_HandleTypeDef rotary_encoder;

void RE_Init(RE_HandleTypeDef * p_re, TIM_HandleTypeDef *p_re_timer);
void RE_Get_Value(RE_HandleTypeDef * p_re);
void RE_Handle(RE_HandleTypeDef * p_re);



#endif /* INC_ROTARY_ENCODER_H_ */
