#ifndef _SI_1153_H_
#define _SI_1153_H_
#include "stm32g0xx.h"

extern I2C_HandleTypeDef hi2c2;

#define SI1153_PROX_THLD_WOLENS     70      //SI1153 proximity threshold without lens
#define SI1153_PROX_THLD_WLENS      55      //SI1153 proximity threshold with lens, there is an object closer then 1,5m

#define SI1153_I2C_CHANNEL					 hi2c2

#define SI1153_ADDRESS               0xA6
#define SI1153_REG_IRQ_ENABLE        0x0F
#define SI1153_REG_COMMAND           0x0B
#define SI1153_REG_HOSTIN0           0x0A
#define SI1153_REG_RESPONSE1         0x10
#define SI1153_REG_RESPONSE0         0x11
#define SI1153_REG_IRQ_STATUS        0x12

#define SI1153_REG_HOSTOUT0          0x13
#define SI1153_REG_HOSTOUT1          0x14
#define SI1153_REG_HOSTOUT2          0x15
#define SI1153_REG_HOSTOUT3          0x16
#define SI1153_REG_HOSTOUT4          0x17
#define SI1153_REG_HOSTOUT5          0x18

#define SI1153_PARAM_CH_LIST         0x01

#define SI1153_PARAM_ADCCONFIG0      0x02
#define SI1153_PARAM_ADCCONFIG1      0x06
#define SI1153_PARAM_ADCCONFIG2      0x0A

#define SI1153_PARAM_MEASCONFIG0     0x05
#define SI1153_PARAM_MEASCONFIG1     0x09
#define SI1153_PARAM_MEASCONFIG2     0x0D

#define SI1153_PARAM_ADCSENS0        0x03
#define SI1153_PARAM_ADCSENS1        0x07
#define SI1153_PARAM_ADCSENS2        0x0B

#define SI1153_PARAM_ADCPOST0        0x04
#define SI1153_PARAM_ADCPOST1        0x08
#define SI1153_PARAM_ADCPOST2        0x0C

#define SI1153_PARAM_LED1_A          0x1F
#define SI1153_PARAM_LED2_A          0x21
#define SI1153_PARAM_LED3_A          0x23

HAL_StatusTypeDef SI1153_SetParameter(uint8_t location, uint8_t value);
HAL_StatusTypeDef SI1153_WriteRegister(uint8_t address, uint8_t value);

HAL_StatusTypeDef SI1153_Reset();
HAL_StatusTypeDef SI1153_Init();
HAL_StatusTypeDef SI1153_Handler();
uint32_t  SI1153_MeasureAmbientLightLevel();

typedef struct
{
    uint8_t      irq_status;
    uint32_t     ch0;
    //uint32_t     ch1;
    //uint32_t     ch2;
    //uint32_t     ch3;
	
} SI1153_channel_info;



#endif //_SI_1153_H_
