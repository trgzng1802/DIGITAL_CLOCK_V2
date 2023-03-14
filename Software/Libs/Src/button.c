/*
 * button.c
 *
 *  Created on: Mar 9, 2023
 *      Author: phang
 */

#include "button.h"

#define PRESSING                    0       /*Press button, GND*/
#define NOT_PRESSING                1       /*Don't press button, pull-up resistor*/
#define DEBOUNCING					1
#define NOT_DEBOUNCING				0
#define PRESS_LONG					1
#define NOT_PRESS_LONG				0
#define BUTTON_FILTER               1
#define BUTTON_DEBOUNCING_TIME      15
#define BUTTON_PRESS_SHORT_TIME     500    /*Pressing under 1s*/
#define BUTTON_PRESS_LONG_TIME      2000    /*Pressing 3s above*/

/**
 * @brief 
 * 
 * @param p_button 
 * @return __weak 
 */
__weak void BUTTON_Pressing_Callback(BUTTON_HandleTypeDef *p_button)
{
	;
}

/**
 * @brief 
 * 
 * @param p_button 
 * @return __weak 
 */
__weak void BUTTON_Short_Pressing_Callback(BUTTON_HandleTypeDef *p_button)
{
	;
}

/**
 * @brief 
 * 
 * @param p_button 
 * @return __weak 
 */
__weak void BUTTON_Long_Pressing_Callback(BUTTON_HandleTypeDef *p_button)
{
	;
}

/**
 * @brief 
 * 
 * @param p_button 
 * @return __weak 
 */
__weak void BUTTON_Releasing_Callback(BUTTON_HandleTypeDef *p_button)
{
	;
}

/**
 * @brief 
 * 
 * @param p_button 
 * @param GPIOx 
 * @param GPIO_Pin 
 */
void BUTTON_Init(BUTTON_HandleTypeDef *p_button, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    p_button->GPIOx = GPIOx;
    p_button->GPIO_Pin = GPIO_Pin;
    p_button->button_current_state = NOT_PRESSING;
    p_button->button_last_state = NOT_PRESSING;
    p_button->button_filter = BUTTON_FILTER;
    p_button->is_debouncing = NOT_DEBOUNCING;
    p_button->is_press_long = NOT_PRESS_LONG;
}

/**
 * @brief 
 * 
 * @param p_button 
 */
void BUTTON_Handle(BUTTON_HandleTypeDef *p_button)
{
    uint8_t temp_state = HAL_GPIO_ReadPin(p_button->GPIOx,p_button->GPIO_Pin);

    if (temp_state != p_button->button_filter)
    {
    	p_button->button_filter = temp_state;
    	p_button->is_debouncing = DEBOUNCING;
    	p_button->debounce_time = HAL_GetTick();
    }

    if (p_button->is_debouncing && (HAL_GetTick() - p_button->debounce_time >= BUTTON_DEBOUNCING_TIME))
    {
    	p_button->button_current_state = p_button->button_filter;
    	p_button->is_debouncing = NOT_DEBOUNCING;
    }

    if (p_button->button_current_state != p_button->button_last_state)
    {
    	if (p_button->button_current_state == PRESSING)
    	{
    		BUTTON_Pressing_Callback(p_button);
    		p_button->is_press_long = PRESS_LONG;
    		p_button->time_start_press = HAL_GetTick();
    	}
    	else
    	{
    		p_button->is_press_long = NOT_PRESS_LONG;
    		if (HAL_GetTick() - p_button->time_start_press <= BUTTON_PRESS_SHORT_TIME)
    		{
    			BUTTON_Short_Pressing_Callback(p_button);
    		}
    		BUTTON_Releasing_Callback(p_button);
    	}
    	p_button->button_last_state = p_button->button_current_state;
    }

    if (p_button->is_press_long && (HAL_GetTick() -  p_button->time_start_press >= BUTTON_PRESS_LONG_TIME))
    {
    	BUTTON_Long_Pressing_Callback(p_button);
    	p_button->is_press_long = NOT_PRESS_LONG;
    }
}
