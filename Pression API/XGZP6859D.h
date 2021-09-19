/*
 *   @file XGZP6859D.h
 *   @brief Header file for XGZP6859D.c file
 *          This file provides the main variables and functions to get the pressure Value from XGZP6859D Pressure Sensor.
 */

#ifndef INC_XGZP6859D_H_
#define INC_XGZP6859D_H_

/* Includes ------------------------------------------------------------------------------- */
#include "i2c.h"
#include "main.h"

/**
 * @brief I2C Handler
 */
#define I2C_HANDLE &hi2c1

/**
 * @brief Device Address
 */
#define XGZP6859D_I2C_ADD (0X6D << 1)

/**
 * @brief Response Time
 */
#define XGZP6859D_I2C_RESPONSE_TIME 4 //ms

/**
 * @brief K cofficient
 */
#define XGZP6859D_PRESSURE_COEF_k 128

I2C_HandleTypeDef hi2c1;


/**
 * @brief Enumeration For Check the Avaibility Pressure, and its
 */
typedef enum
{
    PRESSURE_POSITIVE,
    PRESSURE_NEGATIVE,
    PRESSURE_NAN,
} PressureReadStatus;

/**
 * @brief Gets the Pressure Value From XGZP6859D Sensor.
 * @param pressure Pressure value pointer.
 * @retval PressureReadStatus.
 */
PressureReadStatus Pressure_readPressure(uint32_t *pressure); // unit is Pa

/**
 * @brief Test the monotonic of the value of the pressure
 * @param adcData ADC value
 * @retval PressureReadStatus
 */
PressureReadStatus Pressure_ProcessADC_Data(uint32_t *adcData);

/**
 * @brief Write an address in a register
 * @param add  register address
 * @param value Internal memory address
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef XGZP6859D_RegisterWrite(uint8_t add, uint8_t *value);

/**
 * @brief Read from a register
 * @param add  register address
 * @param value Internal memory address
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef XGZP6859D_RegisterRead(uint8_t add, uint8_t *value);

#endif // PRESSURE_INC
