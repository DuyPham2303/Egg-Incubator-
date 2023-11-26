#ifndef INC_READ_DATA_H_
#define INC_READ_DATA_H_
#include "stm32f1xx_hal.h"
#include"DHT11.h"
#include"DS3231.h"
#include"main.h"
void Input_Init();
void Read_TempHumi();
void Read_Time();
#endif /* INC_READ_DATA_H_ */
