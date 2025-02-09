#include "i2c_help_fyn.h"


/* Bus I2C Write.
 * @param I2Cx 	   Selected I2C
 * @param Addr 	   Slave Address
 * @param reg 	   Slave Register
 * @param pData	   Slave Buffer
 * @param size	   Data Size
 */
void I2C_Bus_Write(I2C_TypeDef *I2Cx, uint8_t Addr, uint8_t reg, uint8_t *pData, uint8_t size)
{
	while (LL_I2C_IsActiveFlag_BUSY(I2Cx)) {}; 				//Wait for I2C bus is free
    LL_I2C_HandleTransfer(I2Cx, Addr, LL_I2C_ADDRSLAVE_7BIT, 1, I2C_CR2_RELOAD, LL_I2C_GENERATE_START_WRITE); 	//Send Slave Address

    while (!LL_I2C_IsActiveFlag_TXIS(I2Cx)){};   			//Wait for TXIS is ready
    LL_I2C_TransmitData8(I2Cx, reg);						//Send Memory Address

	while (!LL_I2C_IsActiveFlag_TCR(I2Cx)) {};
	LL_I2C_HandleTransfer(I2Cx, Addr, LL_I2C_ADDRSLAVE_7BIT, size, I2C_CR2_AUTOEND , LL_I2C_GENERATE_NOSTARTSTOP);

	for(uint8_t i = 0; i < size; i++)
	{
    	while (!LL_I2C_IsActiveFlag_TXIS(I2Cx)) {};			//Wait until TXIS flag is set
        LL_I2C_TransmitData8(I2Cx, pData[i]);			//Write data to TXDR
    }
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx)) {};				//Wait until STOPF flag is reset
    LL_I2C_ClearFlag_NACK(I2Cx);							//Clear NACKF Flag
    LL_I2C_ClearFlag_STOP(I2Cx);							//Clear STOP Flag
}
/* Single I2C Write.
 * @param I2Cx 	   Selected I2C
 * @param Addr 	   Slave Address
 * @param reg 	   Slave Register
 */
uint8_t I2C_Singl_Read(I2C_TypeDef *I2Cx, uint8_t Addr, uint8_t reg)
{
	uint8_t buf = 0;

	while (LL_I2C_IsActiveFlag_BUSY(I2Cx)) {}; 				//Wait for I2C bus is free
    LL_I2C_HandleTransfer(I2Cx, Addr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE); 	//Send Slave Address

    while (!LL_I2C_IsActiveFlag_TXIS(I2Cx)){};   			//Wait for TXIS is ready
    LL_I2C_TransmitData8(I2Cx, reg);						//Send Memory Address

    while (!LL_I2C_IsActiveFlag_TC(I2Cx)) {};
    LL_I2C_HandleTransfer(I2Cx, Addr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

    while (!LL_I2C_IsActiveFlag_RXNE(I2Cx)) {};			//Wait until RXNE flag is set
    buf = LL_I2C_ReceiveData8(I2Cx);						//Read data from RXDR

    while (!LL_I2C_IsActiveFlag_STOP(I2Cx)) {};			//Wait until STOPF flag is reset
    LL_I2C_ClearFlag_STOP(I2Cx);							//Clear STOP Flag

    return buf;
}

/* Bus I2C Write.
 * @param I2Cx 	   Selected I2C
 * @param Addr 	   Slave Address
 * @param reg 	   Slave Register
 * @param pData	   Master Buffer
 * @param size	   Data Size
 */
void I2C_Bus_Read(I2C_TypeDef *I2Cx, uint8_t Addr, uint8_t reg, uint8_t *pData, uint8_t size)
{

	while (LL_I2C_IsActiveFlag_BUSY(I2Cx)) {}; 				//Wait for I2C bus is free
	LL_I2C_HandleTransfer(I2Cx, Addr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE); 	//Send Slave Address

    while (!LL_I2C_IsActiveFlag_TXIS(I2Cx)){};   			//Wait for TXIS is ready
    LL_I2C_TransmitData8(I2Cx, reg);						//Send Memory Address

    while (!LL_I2C_IsActiveFlag_TC(I2Cx)) {};
    LL_I2C_HandleTransfer(I2Cx, Addr, LL_I2C_ADDRSLAVE_7BIT, size, I2C_CR2_AUTOEND, LL_I2C_GENERATE_START_READ);

	for(uint8_t i = 0; i < size; i++)
	{
        while (!LL_I2C_IsActiveFlag_RXNE(I2Cx)) {};			//Wait until RXNE flag is set
        pData[i] = LL_I2C_ReceiveData8(I2Cx);				//Read data from RXDR
	}

    while (!LL_I2C_IsActiveFlag_STOP(I2Cx)) {};				//Wait until STOPF flag is reset
    LL_I2C_ClearFlag_STOP(I2Cx);							//Clear STOP Flag
}
