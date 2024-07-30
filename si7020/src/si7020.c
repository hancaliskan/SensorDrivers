#include "si7020.h"

//uint8_t SensorConfigData[2];

HAL_StatusTypeDef SI7020_ReadTemperature(float *temperature)
{
	uint8_t SensorCommand;
	uint8_t SensorData[2];
	uint16_t Sensor_Temp_Val;
	
	SensorCommand = cmd_READ_TEMP;
	
	//Send read temperature command
	if (HAL_I2C_Master_Transmit(&hi2c2,(uint16_t)TEMP_HUMIDITY_SENSOR_I2C_ADDRESS, &SensorCommand,1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	//Read temperature value from the sensor
	if (HAL_I2C_Master_Receive(&hi2c2, TEMP_HUMIDITY_SENSOR_I2C_ADDRESS|1, SensorData, 2, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	Sensor_Temp_Val = SensorData[0]*256 + SensorData[1];
	*temperature = 175.72 * Sensor_Temp_Val / 65536 - 46.85;
	
	return HAL_OK;
}
	
HAL_StatusTypeDef SI7020_ReadHumidity(float *humidity)
{
	uint8_t SensorCommand;
	uint8_t SensorData[2];
	uint16_t Sensor_Humidity_Val;
	
	SensorCommand = cmd_READ_HUMIDITY;
	
	//Send read humidty command
	if (HAL_I2C_Master_Transmit(&hi2c2, TEMP_HUMIDITY_SENSOR_I2C_ADDRESS, &SensorCommand, 1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	//Read humidty value from the sensor
	if (HAL_I2C_Master_Receive(&hi2c2, TEMP_HUMIDITY_SENSOR_I2C_ADDRESS|1, SensorData, 1, 1000) != HAL_OK)
		return HAL_ERROR;
	HAL_Delay (10);
	
	Sensor_Humidity_Val = SensorData[0] * 256 + SensorData[1];
	*humidity = 125 * Sensor_Humidity_Val / 65536 - 6;
	
	return HAL_OK;
}