#include <read_data.h>
#include"setting_data.h"
#include"display_data.h"
#include"Connect_UART.h"
DS3231_Name egg_rtc;
DHT11_Name egg_dht;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim3;
void Input_Init(){
	DS3231_Init(&egg_rtc,&hi2c1);
	DHT11_Init(&egg_dht, GPIOA, GPIO_PIN_12, &htim3);
	Init_UART_Rx();
}
void Read_Time(){
	DS3231_GetTime(&egg_rtc);
	DS3231_GetDate(&egg_rtc);
}
void Read_TempHumi(){
	if(DHT11_Start(&egg_dht)){
		DHT11_output(&egg_dht);
	}
}
