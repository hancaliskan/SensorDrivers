#include "htm2126.h"

//uint8_t SensorConfigData[2];


HAL_StatusTypeDef HTM2126_ReadMotionStatus(uint8_t *motion_status)
{
	uint8_t SensorCommand;
	uint8_t SensorData[2];
	
	if (HTM2126_SetMotionDetectionFreq(SensorData) != HAL_OK)
		return HAL_ERROR;

	SensorData[0] = 0;
	SensorData[1] = 0;
	SensorCommand = cmd_READ_MOTION_STATUS;	
	
	//Send read temperature command
	if (HAL_I2C_Master_Transmit(&hi2c2, PIR_DETECTOR_I2C_ADDRESS, &SensorCommand, 1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	//Read temperature value from the sensor
	if (HAL_I2C_Master_Receive(&hi2c2, PIR_DETECTOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	*motion_status = (SensorData[1] & MOTION_STATUS_MASK) / MOTION_STATUS_MASK;
	
	return HAL_OK;
}
	
HAL_StatusTypeDef HTM2126_ReadDarknessStatus(uint8_t *darknes_status)
{
	uint8_t SensorCommand;
	uint8_t SensorData[2];
	
	if (HTM2126_SetLuminanceConfig(SensorData) != HAL_OK)
		return HAL_ERROR;
	
	SensorData[0]=0;
	SensorData[1]=0;
	SensorCommand = cmd_READ_DARKNESS_STATUS;
	
	//Send read humidty command
	if (HAL_I2C_Master_Transmit(&hi2c2, PIR_DETECTOR_I2C_ADDRESS, &SensorCommand, 1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	//Read humidty value from the sensor
	if (HAL_I2C_Master_Receive(&hi2c2, PIR_DETECTOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	*darknes_status = (SensorData[1] & DARKNESS_STATUS_MASK) / DARKNESS_STATUS_MASK;
	
	return HAL_OK;
}

HAL_StatusTypeDef HTM2126_SetMotionDetectionFreq(uint8_t *motion_status)
{
	uint8_t SensorCommand;
	uint8_t SensorData[2];
	uint8_t SensorConfigData[3];

	SensorData[0] = 0;
	SensorData[1] = 0;
	SensorCommand = 0;

	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)PIR_DETECTOR_I2C_ADDRESS, &SensorCommand,1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
 	if (HAL_I2C_Master_Receive(&hi2c2, PIR_DETECTOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
  HAL_Delay (10);
	
	SensorConfigData[0] = SensorCommand;
	SensorConfigData[2] = SensorData[1]|3;
	SensorConfigData[1] = SensorData[0];
	
	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)PIR_DETECTOR_I2C_ADDRESS, SensorConfigData,3, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	//Read back the register value and compare with the config data
	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)PIR_DETECTOR_I2C_ADDRESS, &SensorCommand,1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
 	
	if (HAL_I2C_Master_Receive(&hi2c2, PIR_DETECTOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
  HAL_Delay (10);
	
	if (SensorData[0] != SensorConfigData[1] || SensorData[1] != SensorConfigData[2])
		return HAL_ERROR;
	
	return HAL_OK;
}
		
HAL_StatusTypeDef HTM2126_SetLuminanceConfig(uint8_t *motion_status)
{
	uint8_t SensorCommand;
	uint8_t SensorData[2];
	uint8_t SensorConfigData[3];
	
	SensorData[0] = 0;
	SensorData[1] = 0;
	SensorCommand = 2;
	
	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)PIR_DETECTOR_I2C_ADDRESS, &SensorCommand,1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
 	
	if (HAL_I2C_Master_Receive(&hi2c2, PIR_DETECTOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
  HAL_Delay (10);
	
	SensorConfigData[0] = SensorCommand;
	SensorConfigData[1] = 0x7F;
	SensorConfigData[2] = SensorData[1];
	
	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)PIR_DETECTOR_I2C_ADDRESS, SensorConfigData,3, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	//Read back the register value and compare with the config data	
	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)PIR_DETECTOR_I2C_ADDRESS, &SensorCommand,1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
 	if (HAL_I2C_Master_Receive(&hi2c2, PIR_DETECTOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
  HAL_Delay (10);
	
	if (SensorData[0] != SensorConfigData[1] || SensorData[1] != SensorConfigData[2])
		return HAL_ERROR;
	
	return HAL_OK;
	
}