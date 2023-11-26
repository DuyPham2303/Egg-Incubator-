#include"Module_Sim.h"
char TX_data[60];
extern char warning_notice1_buff,warning_notice2_buff;
int8_t flag_sendSMS = 0;
void Send_SMS()
{
	if(flag_sendSMS == 1){
		HAL_UART_Transmit(&huart2, (uint8_t*)"AT+CMGF=1\r\n",11, 1000);
		HAL_Delay(100);
		HAL_UART_Transmit(&huart2, (uint8_t*)"AT+CNMI=2,2,0,0\r\n",17, 1000);
		HAL_Delay(100);
		HAL_UART_Transmit(&huart2, (uint8_t*)"AT+CMGS=\"0972665872\"\r\n",22, 5000);
		HAL_Delay(100);
		sprintf(TX_data,"Temperature must < 50\r\nhumidity must < 90 %c",0x1A);
		HAL_UART_Transmit(&huart2, (uint8_t*)TX_data,strlen(TX_data), 1000);
		flag_sendSMS = 0;
	}
}
