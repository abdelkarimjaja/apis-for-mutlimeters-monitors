/*
 *  @file XGZP6859D.c
 *  @brief This file contain the defined functions of XGZP6859D Pressure Sensor Module.
 */

/* Includes _________________________________________________________*/
#include "XGZP6859D.h"

uint8_t I2C_Cplt_Rx_Tx = 0;

PressureReadStatus Pressure_readPressure(uint32_t *pressure)
{
    HAL_StatusTypeDef status;
    PressureReadStatus readStatus;
    uint8_t temp = 0;
    uint32_t pressureADC = 0;
    uint8_t dataMSB, dataCSB, dataLSB;
//HAL_BUSY
    status = XGZP6859D_RegisterRead(0xA5, &temp);
    if (status != HAL_BUSY)
        return PRESSURE_NAN;

    temp = temp & 0xFD;
    status = XGZP6859D_RegisterWrite(0xA5, &temp);
    if (status != HAL_BUSY)
     	return PRESSURE_NAN;

    temp = 0x0A;
    status = XGZP6859D_RegisterWrite(0x30, &temp);
    if (status != HAL_BUSY)
    	return PRESSURE_NAN;

    temp = 0xFF;
    status = XGZP6859D_RegisterRead(0x30, &temp);

    if ((temp & 0x08) == 0)
    {

        status = XGZP6859D_RegisterRead(0x06, &dataMSB);
        if (status != HAL_BUSY)
             return PRESSURE_NAN;
        status = XGZP6859D_RegisterRead(0x07, &dataCSB);

        if (status != HAL_BUSY)
             return PRESSURE_NAN;
        status = XGZP6859D_RegisterRead(0x08, &dataLSB);
        if (status != HAL_BUSY)
             return PRESSURE_NAN;

        pressureADC = ((((uint32_t)dataMSB) << 16) + (((uint32_t)dataCSB) << 8) + ((uint32_t)dataLSB));
        readStatus = Pressure_ProcessADC_Data(&pressureADC);
        *pressure = pressureADC;
        return readStatus;
    }

    return PRESSURE_NAN;
}

PressureReadStatus Pressure_ProcessADC_Data(uint32_t *adcData)
{
    if (*adcData & 0x00800000)
    {
        *adcData = (*adcData - 16777216) / XGZP6859D_PRESSURE_COEF_k;
        return PRESSURE_NEGATIVE;
    }
    else
    {
        *adcData = *adcData / XGZP6859D_PRESSURE_COEF_k;
        return PRESSURE_POSITIVE;
    }
}

HAL_StatusTypeDef XGZP6859D_RegisterRead(uint8_t add, uint8_t *value)
{
    HAL_StatusTypeDef status;

    if (I2C_Cplt_Rx_Tx)
        return HAL_BUSY;

    I2C_Cplt_Rx_Tx = 1;
    status = HAL_I2C_Mem_Read_DMA(I2C_HANDLE, XGZP6859D_I2C_ADD, add, 1, value, 1);

    if (status != HAL_OK)
    {
        HAL_I2C_Master_Abort_IT(I2C_HANDLE, XGZP6859D_I2C_ADD);
        I2C_Cplt_Rx_Tx = 0;
        return status;
    }

    HAL_Delay(XGZP6859D_I2C_RESPONSE_TIME);

    if (I2C_Cplt_Rx_Tx)
    {
        HAL_I2C_Master_Abort_IT(I2C_HANDLE, XGZP6859D_I2C_ADD);
        I2C_Cplt_Rx_Tx = 0;
        return HAL_TIMEOUT;
    }
    return HAL_OK;
}

HAL_StatusTypeDef XGZP6859D_RegisterWrite(uint8_t add, uint8_t *value)
{
    HAL_StatusTypeDef status;
    if (I2C_Cplt_Rx_Tx)
        return HAL_BUSY;
    I2C_Cplt_Rx_Tx = 1;
    status = HAL_I2C_Mem_Write_DMA(I2C_HANDLE, XGZP6859D_I2C_ADD, add, 1, value, 1);
    if (status != HAL_OK)
    {
        I2C_Cplt_Rx_Tx = 0;
        HAL_I2C_Master_Abort_IT(I2C_HANDLE, XGZP6859D_I2C_ADD);
        return status;
    }
    HAL_Delay(XGZP6859D_I2C_RESPONSE_TIME);
    if (I2C_Cplt_Rx_Tx)
    {
        HAL_I2C_Master_Abort_IT(I2C_HANDLE, XGZP6859D_I2C_ADD);
        I2C_Cplt_Rx_Tx = 0;
        return HAL_TIMEOUT;
    }
    return HAL_OK;
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c == I2C_HANDLE)
        I2C_Cplt_Rx_Tx = 0;
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c == I2C_HANDLE)
        I2C_Cplt_Rx_Tx = 0;
}
