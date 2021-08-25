/*
 *
 * **************************************************************************************************************
 *
 * @file pnuema.h
 * @brief Header file for pneuma.c file
 *        This file contains the main functions for controlling the speed of pump and valve.
 * ***************************************************************************************************************
 *
 */



#ifndef INC_PNEUMA_H_
#define INC_PNEUMA_H_

/* Includes ------------------------------------------------------------------*/
#include"tim.h"

/**
 * @brief Pneumatic Timer.
 */
#define PM_TIM &htim2
/**
 * @brief Pump Timer Channel.
 */
#define PM_Pump_PWM_Channel TIM_CHANNEL_2

/**
 * @brief Valve Timer Channel.
 */
#define PM_Valve_PWM_Channel TIM_CHANNEL_3//

/**
 * @brief  duty cycle register CCR2 channel 2 for a pump.
 */
#define PM_Pump_Channel_CCR TIM2->CCR2

/**
 * @brief duty cycle register CCR3 channel 3 for a valve.
 *
 */
#define PM_Valve_Channel_CCR TIM2->CCR3 // .

/**
 * @brief Start PWM Timer and initiate the duty cycle registers - CCRx - for our pneumatic.
 *
 * */
void PM_Init(void);

/**
 * @brief Configure the duty cycle for pump application.
 * @param dutyCycle desired duty cycle.
 *
 */
void PM_Set_DC_Pump(uint8_t dutyCycle);

/**
 * @brief Configure the duty cycle for valve application
 * @param dutyCycle desired duty cycle.
 *
 */
void PM_Set_DC_Valve(uint8_t dutyCycle);


#endif /* INC_PNEUMA_H_ */
