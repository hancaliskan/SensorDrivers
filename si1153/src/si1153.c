#include "si1153.h"
//#include "frost/frost_time.h"
//#include <stdio.h>

HAL_StatusTypeDef SI1153_SetParameter(uint8_t location, uint8_t value)
{
    HAL_StatusTypeDef error;
		uint8_t response;
    uint8_t Addr = 0x00;
		uint8_t SensorConfigData[2];
    uint8_t si1153_data = 0x00;
	
		//Read RESPONSE0 register
		Addr = SI1153_REG_RESPONSE0;
    error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;
		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &response, 1, 1000);
		if (error!=HAL_OK)
			return error;
		
		
		//SET PARAMETER
		Addr = SI1153_REG_HOSTIN0;
    //error = HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL, SI1153_ADDRESS, &Addr, 1, &value, 1);
		SensorConfigData[0]= Addr;
		SensorConfigData[1]= value;
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, SensorConfigData,2, 1000);
		if (error!=HAL_OK)
			return error;

    Addr = SI1153_REG_COMMAND;
		si1153_data = location | 128;
		
		SensorConfigData[0]= Addr;
		SensorConfigData[1]= si1153_data;
    
    //error &= mapi_I2cWrite(SI1153_I2C_CHANNEL, SI1153_ADDRESS, &Addr, 1, &si1153_data, 1);
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, SensorConfigData,2, 1000);
		if (error!=HAL_OK)
			return error;
		
		
		//Read RESPONSE0 register
		Addr = SI1153_REG_RESPONSE0;
    error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;
		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &response, 1, 1000);
		if (error!=HAL_OK)
			return error;
		
		
		//read back parameter
		
		Addr = SI1153_REG_COMMAND;
		si1153_data = location | 64;
		SensorConfigData[0]= Addr;
		SensorConfigData[1]= si1153_data;
    
    //error &= mapi_I2cWrite(SI1153_I2C_CHANNEL, SI1153_ADDRESS, &Addr, 1, &si1153_data, 1);
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, SensorConfigData,2, 1000);
		if (error!=HAL_OK)
			return error;
		
		Addr = SI1153_REG_RESPONSE1;
    
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;
		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &si1153_data, 1, 1000);
		if (error!=HAL_OK)
			return error;
		
		
    /*if (error == FALSE)
    {
        printf("%s Failed !!!\n",__FUNCTION__);
        return FALSE;
    }
		*/

    return HAL_OK;
}

HAL_StatusTypeDef SI1153_WriteRegister(uint8_t address, uint8_t value)
{
    HAL_StatusTypeDef error;
		uint8_t SensorConfigData[2];
	
		SensorConfigData[0]= address;
		SensorConfigData[1]= value;	
	
    //error = mapi_I2cWrite(SI1153_I2C_CHANNEL, SI1153_ADDRESS, &address, 1, &value, 1);
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, SensorConfigData,2, 1000);
		if (error!=HAL_OK)
			return error;
		
		HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, SensorConfigData,1, 1000);
		HAL_Delay(10);
		HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, SensorConfigData,1, 1000);
/*
    if (error == FALSE)
    {
        printf("%s Failed !!!\n",__FUNCTION__);
        return FALSE;
    }
*/
    return HAL_OK;
}

HAL_StatusTypeDef SI1153_Reset()
{
    //FROST_Sleep(30);
		HAL_Delay(30);


    SI1153_WriteRegister(SI1153_REG_COMMAND, 1);

    //FROST_Sleep(10);
		HAL_Delay(10);

    return HAL_OK;
}

HAL_StatusTypeDef SI1153_Force()
{
    //FROST_Sleep(30);
		HAL_Delay(30);

    SI1153_WriteRegister(SI1153_REG_COMMAND, 0x11);

    //FROST_Sleep(10);
		HAL_Delay(10);

    return HAL_OK;
}

HAL_StatusTypeDef SI1153_Start()
{
    HAL_Delay(30);

    SI1153_WriteRegister(SI1153_REG_COMMAND, 0x13);

    HAL_Delay(10);

    return HAL_OK;
}

HAL_StatusTypeDef SI1153_Init()
{
    SI1153_Reset();

    HAL_Delay(10);

/*
    // Initialize LED current for proximity detection
    SI1153_SetParameter(SI1153_PARAM_LED1_A, 0x3F);
    SI1153_SetParameter(SI1153_PARAM_LED2_A, 0x3F);
    SI1153_SetParameter(SI1153_PARAM_LED3_A, 0x3F);
*/
    // Enable 1 channel for ambient light measurement
    SI1153_SetParameter(SI1153_PARAM_CH_LIST, 0x01);

    // Configure ADC and enable LED drive
    SI1153_SetParameter(SI1153_PARAM_ADCCONFIG0, 0x4B);	//ADC speed Normal, Photodiode D1 selected
    SI1153_SetParameter(SI1153_PARAM_ADCSENS0, 0x3);
    SI1153_SetParameter(SI1153_PARAM_ADCPOST0, 0x00);		//0x40 for 24 bit result
    //SI1153_SetParameter(SI1153_PARAM_MEASCONFIG0, 0x34);
/*
    SI1153_SetParameter(SI1153_PARAM_ADCCONFIG1, 0x62);
    SI1153_SetParameter(SI1153_PARAM_ADCSENS1, 0x06);
    SI1153_SetParameter(SI1153_PARAM_ADCPOST1, 0x40);
    SI1153_SetParameter(SI1153_PARAM_MEASCONFIG1, 0x31);

    SI1153_SetParameter(SI1153_PARAM_ADCCONFIG2, 0x62);
    SI1153_SetParameter(SI1153_PARAM_ADCSENS2, 0x04);
    SI1153_SetParameter(SI1153_PARAM_ADCPOST2, 0x40);
    SI1153_SetParameter(SI1153_PARAM_MEASCONFIG2, 0x32);
*/
    // Enable Interrupt
    SI1153_WriteRegister(SI1153_REG_IRQ_ENABLE, 0x01);

    return HAL_OK;
}

HAL_StatusTypeDef SI1153_Handler(SI1153_channel_info *channel_info)
{
    uint8_t buffer[13];
    uint8_t Addr = SI1153_REG_IRQ_STATUS;
    HAL_StatusTypeDef error;
		
		//error = mapi_I2cRead(SI1153_I2C_CHANNEL, SI1153_ADDRESS, &Addr, 1, &buffer, 13);
		
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;

		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)(SI1153_ADDRESS|1), &buffer[0],1, 1000);
		if (error!=HAL_OK)
			return error;
		
		
		
	//*********************	result
		Addr=SI1153_REG_HOSTOUT0;
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;
		HAL_Delay(10);
		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)(SI1153_ADDRESS|1), &buffer[1],1, 1000);
		if (error!=HAL_OK)
			return error;
		HAL_Delay(10);
		
		Addr=SI1153_REG_HOSTOUT1;
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;
		HAL_Delay(10);
		
		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)(SI1153_ADDRESS|1), &buffer[2],1, 1000);
		if (error!=HAL_OK)
			return error;
		HAL_Delay(10);
		
		/*
		Addr=SI1153_REG_HOSTOUT2;
		error=HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		if (error!=HAL_OK)
			return error;
		HAL_Delay(10);
		
		error=HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)(SI1153_ADDRESS|1), &buffer[3],1, 1000);
		if (error!=HAL_OK)
			return error;
		HAL_Delay(10);
		*/
    channel_info->irq_status = buffer[0];

		channel_info->ch0 = buffer[1] << 8;
    channel_info->ch0 |= buffer[2];
		/*
    channel_info->ch0 = buffer[1] << 16;
    channel_info->ch0 |= buffer[2] << 8;
    channel_info->ch0 |= buffer[3];
		*/
		
/*
    if (channel_info->ch0 & 0x800000)
    {
        channel_info->ch0 |= 0xFF000000;
    }*/
		
		
		//******************************************
/*
    channel_info->ch1 = buffer[4] << 16;
    channel_info->ch1 |= buffer[5] << 8;
    channel_info->ch1 |= buffer[6];

    if (channel_info->ch1 & 0x800000)
    {
        channel_info->ch1 |= 0xFF000000;
    }

    channel_info->ch2 = buffer[7] << 16;
    channel_info->ch2 |= buffer[8] << 8;
    channel_info->ch2 |= buffer[9];

    if (channel_info->ch2 & 0x800000)
    {
        channel_info->ch2 |= 0xFF000000;
    }

    channel_info->ch3 = buffer[10] << 16;
    channel_info->ch3 |= buffer[11] << 8;
    channel_info->ch3 |= buffer[12];

    if (channel_info->ch3 & 0x800000)
    {
        channel_info->ch3 |= 0xFF000000;
    }

/*    if (error == FALSE)
    {
        printf("%s Failed !!!\n",__FUNCTION__);
        return FALSE;
    }
*/
    return HAL_OK;
}

uint32_t SI1153_MeasureAmbientLightLevel()
{
    uint32_t ambientlightlevel;
    SI1153_channel_info channel_info;

    //Force SI1153
	uint8_t Addr=SI1153_REG_COMMAND;
	uint8_t buffer[2];
		
    SI1153_WriteRegister(SI1153_REG_COMMAND, 0x11);
		HAL_Delay(10);
		//HAL_I2C_Master_Transmit(&SI1153_I2C_CHANNEL,(uint16_t)SI1153_ADDRESS, &Addr,1, 1000);
		HAL_Delay(10);
		//HAL_I2C_Master_Receive(&SI1153_I2C_CHANNEL,(uint16_t)(SI1153_ADDRESS|1), buffer,1, 1000);

		SI1153_Handler(&channel_info);
/*	
    if (!SI1153_Handler(&channel_info))
    {
        return SI1153_PROX_THLD_WLENS;
    }
*/
    //printf("SI1153 CH0 = %u, CH1 = %u, CH2 = %u *****\n", channel_info.ch0, channel_info.ch1, channel_info.ch2);

    ambientlightlevel = channel_info.ch0;

    return ambientlightlevel;
}


