/*
 * Rotary_Encoder.c
 *
 *  Created on: 9 Mar 2023
 *      Author: phang
 */
#include "Rotary_Encoder.h"

__weak void RE_Clockwise_Callback(RE_HandleTypeDef *p_re)
{
	;
}

__weak void RE_Counter_Clockwise_Callback(RE_HandleTypeDef *p_re)
{
	;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == rotary_encoder.re_timer->Instance)
	{
		RE_Get_Value(&rotary_encoder);
	}
}

void RE_Init(RE_HandleTypeDef *p_re, TIM_HandleTypeDef *p_re_timer)
{
	p_re->re_timer = p_re_timer;
	p_re->current_position = 0;
	p_re->last_position = 0;
	HAL_TIM_Encoder_Start_IT(p_re_timer, TIM_CHANNEL_ALL);
}

void RE_Get_Value(RE_HandleTypeDef * p_re)
{
	uint32_t counter = rotary_encoder.re_timer->Instance->CNT;
	p_re->current_position = (int16_t)counter >> 2;
}

void RE_Handle(RE_HandleTypeDef *p_re)
{
	if(p_re->current_position > p_re->last_position)
	{
		RE_Clockwise_Callback(p_re);
		p_re->last_position = p_re->current_position;
	}

	if(p_re->current_position < p_re->last_position)
	{
		RE_Counter_Clockwise_Callback(p_re);
		p_re->last_position = p_re->current_position;
	}
}
