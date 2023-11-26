#include"fan.h"
/*void Fan_Init(fan_init* fan,TIM_HandleTypeDef* htim,
			  uint32_t PWM_channel,
		      GPIO_TypeDef* fan_port,
			  uint16_t fan_pin
			  ){
	fan->fan_port = fan_port;
	fan->fan_pin = fan_pin;
	fan->fan_PWM_channel = PWM_channel;
	fan->htim = htim;
	HAL_TIM_PWM_Start(fan->htim ,fan->fan_PWM_channel);
}
void Fan_Run(fan_init* fan , float duty){
	fan->fan_duty = duty;
	HAL_GPIO_WritePin(fan->fan_port,fan->fan_pin,GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(fan->htim,fan->fan_PWM_channel,fan->fan_duty);
}*/
void TurnOn_fan(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,1);
}
void TurnOff_fan(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,0);
}

