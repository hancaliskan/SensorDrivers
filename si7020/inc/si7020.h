#include "stm32g0xx.h"

extern I2C_HandleTypeDef hi2c2;


#define TEMP_HUMIDITY_SENSOR_I2C_ADDRESS 0x80

//Sensor Commands => Register Fields
#define cmd_READ_TEMP 		0xE3
#define cmd_READ_HUMIDITY 0xE5

HAL_StatusTypeDef SI7020_ReadTemperature(float *temperature);
HAL_StatusTypeDef SI7020_ReadHumidity(float *humidty);