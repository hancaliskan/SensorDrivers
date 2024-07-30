#include "stm32g0xx.h"

extern I2C_HandleTypeDef hi2c2;


#define PIR_DETECTOR_I2C_ADDRESS 	0x98	

//Sensor Commands => Register Fields
#define cmd_READ_MOTION_STATUS		0X08
#define cmd_READ_DARKNESS_STATUS 	0X08
#define MOTION_STATUS_MASK 				0x02
#define DARKNESS_STATUS_MASK 			0x80

HAL_StatusTypeDef HTM2126_ReadMotionStatus(uint8_t *motion_status);
HAL_StatusTypeDef HTM2126_ReadDarknessStatus(uint8_t *darknes_status);
HAL_StatusTypeDef HTM2126_SetMotionDetectionFreq(uint8_t *motion_status);
HAL_StatusTypeDef HTM2126_SetLuminanceConfig(uint8_t *motion_status);