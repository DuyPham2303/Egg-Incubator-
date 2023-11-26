#include"heater.h"
void TurnOn_heater(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,1);
}
void TurnOff_heater(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,0);
}
