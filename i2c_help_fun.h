#ifndef _I2C_HELP_FUN_H
#define _I2C_HELP_FUN_H

#include "stm32f0xx_ll_i2c.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_gpio.h"

void I2C_Bus_Write(I2C_TypeDef *I2Cx, uint8_t Addr, uint8_t reg, uint8_t *pData, uint8_t size);
void I2C_Bus_Read(I2C_TypeDef *I2Cx, uint8_t Addr, uint8_t reg, uint8_t *pData, uint8_t size);
uint8_t I2C_Singl_Read(I2C_TypeDef *I2Cx, uint8_t Addr, uint8_t reg);

#endif
