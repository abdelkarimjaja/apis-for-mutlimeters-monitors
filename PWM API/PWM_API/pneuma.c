/*
 *
 * **************************************************************************************************************
 * @file pnuema.c
 * @brief This file provides defined functions for our use case.
 *
 * ***************************************************************************************************************
 *
 */

/* Includes ------------------------------------------------------------------*/
#include"pneuma.h"

/**
 * @brief Start PWM Timer and initiate the duty cycle registers - CCRx - for our pneumatic.
 *
 * */
void PM_Init(void){

	/* Start PWM Tim2 Channel 2 and 3 for the Pump and Valve.*/
	HAL_TIM_PWM_Start(PM_TIM,PM_Pump_PWM_Channel);
	HAL_TIM_PWM_Start(PM_TIM,PM_Valve_PWM_Channel);

	if(PM_Pump_Channel_CCR != 0 && PM_Valve_Channel_CCR !=0){
		PM_Valve_Channel_CCR = 0;
		PM_Pump_Channel_CCR = 0;
	}
}

/**
 * @brief Configure the duty cycle for pump application.
 * @params dutyCycle desired duty cycle.
 *
 */
void PM_Set_DC_Pump(uint8_t dutyCycle){
	PM_Pump_Channel_CCR = dutyCycle;
}

/**
 * @brief Configure the duty cycle for valve application
 * @params dutyCycle desired duty cycle.
 *
 */
void PM_Set_DC_Valve(uint8_t dutyCycle){
	PM_Valve_Channel_CCR = dutyCycle;
}
