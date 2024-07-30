/*
*         Copyright (c), NXP Semiconductors Caen / France
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

#include <stdint.h>
#include <driver_config.h>
#include <LPC11U6x/inc/i2c_11u6x.h>

#define SPEED_100KHZ         100000
#define SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    SPEED_100KHZ

void i2c_Init(void)
{
	/* Initialize I2C */
	Chip_I2C_Init(DEFAULT_I2C);
	Chip_I2C_SetClockRate(DEFAULT_I2C, I2C_DEFAULT_SPEED);

	Chip_I2C_SetMasterEventHandler(DEFAULT_I2C, Chip_I2C_EventHandlerPolling);
	NVIC_DisableIRQ(I2C0_IRQn);
}

uint8_t i2c_Read(uint8_t add, uint8_t *pRsp, uint16_t Rsp_size)
{
	uint16_t tmp = Chip_I2C_MasterRead(DEFAULT_I2C, add, pRsp, Rsp_size);
	return (tmp == Rsp_size ? SUCCESS : ERROR);
}

uint8_t i2c_Write(uint8_t add, uint8_t *pCmd, uint16_t Cmd_size)
{
	uint16_t tmp = Chip_I2C_MasterSend(DEFAULT_I2C, add, pCmd, Cmd_size);
	return (tmp == Cmd_size ? SUCCESS : ERROR);
}
