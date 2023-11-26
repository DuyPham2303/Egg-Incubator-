#include "Connect_UART.h"
#include "setting_data.h"
#include "save_data.h"
#include "warning.h"
extern UART_HandleTypeDef huart1;
extern float RH,tCelsius;
extern int8_t flag_clr;
extern int8_t machine_mode;
extern float Temp_set,Humi_set;
extern int8_t hour,min,date,month;
extern int16_t NumDay,year;
extern int8_t screen_status;
volatile int8_t flag_saved,flag_setting_count,flag_manual_count,flag_auto_count,flag_switch;
volatile uint8_t Fan_status,Heater_status,mode_status;
//
char buff_tx[79];
char buff_rx[75];
char* wifi_key = "wifi status:";
char wifi_status_buff[1];
int8_t wifi_status;
char* mode_key = "mode status:";
char mode_status_buff[1];

//data in manual mode
char* Fan_key = "fan status:";
char* Heater_key = "heater status:";
char Fan_status_buff[1];
char Heater_status_buff[1];

//data in auto mode
char* screen_key = "screen status:";
char screen_status_buff[1];

//data in setting mode
char* temp_key = "temp:";
char tempset_buff[5];
char humiset_buff[5];
char Numday_buff[2];
char hour_buff[2];
char min_buff[2];
char date_buff[2];
char month_buff[2];
char year_buff[2];
//
uint8_t rx_index = 0;
uint32_t current_time = 0,previous_time = 0;
int8_t flag_send_count = 0;
uint8_t data_rx;

static void Send_tempHumi_FanHeater(){
	sprintf(buff_tx,"Temp:%.2f,Humi:%.2f,Fan_status:%d,Heater_status:%d,TempSet:%.2f,HumiSet:%.2f,",tCelsius,RH,Fan_status,Heater_status,Temp_set,Humi_set);
	HAL_UART_Transmit(&huart1,(uint8_t*)buff_tx,strlen(buff_tx),HAL_MAX_DELAY);
}
static void Get_Screen_Status(){
		rx_index = 0;
		char* key_pos = strstr(buff_rx,screen_key) + strlen(screen_key);
		do{
			screen_status_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '%');
		screen_status = atoi(screen_status_buff);
		rx_index = 0;
		memset(buff_rx,0,sizeof(buff_rx));
		flag_clr = 1;
}
static void Get_Mode_Status(){
	rx_index = 0;
	char* key_pos = strstr(buff_rx,mode_key) + strlen(mode_key);
	do{
		mode_status_buff[rx_index] = key_pos[rx_index];
		rx_index++;
	}while(key_pos[rx_index] != '*');
	mode_status = atoi(mode_status_buff);
	if(mode_status == 1) {
		machine_mode = AUTO_MODE;
		flag_switch = 1;
	}
	else if(mode_status == 2){
		machine_mode = SETTING_MODE;
	}
	else if(mode_status == 3){
		machine_mode = MANUAL_MODE;
		flag_switch = 3;
	}
	rx_index = 0;
	memset(buff_rx,0,sizeof(buff_rx));
	flag_auto_count++;
}
static void Get_Setting_Data(){
		//get temp set
		rx_index = 0;
		char* key_pos = strstr(buff_rx,temp_key) + strlen(temp_key);
		do{
			tempset_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '!');

		//get humi set
		rx_index = 0;
		key_pos = key_pos + 11;
		do{
			humiset_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '@');

		//get numdays input
		rx_index = 0;
		key_pos = key_pos + 14;
		do{
			Numday_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '#');

		//get date input
		rx_index = 0;
		key_pos = key_pos + 8;
		do{
			date_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '$');

		//get month input
		rx_index = 0;
		key_pos = key_pos + 9;
		do{
			month_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '%');

		//get year input
		rx_index = 0;
		key_pos = key_pos + 8;
		do{
			year_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '^');

		//get hour input
		rx_index = 0;
		key_pos = key_pos + 8;
		do{
			hour_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '&');

		//get min input
		rx_index = 0;
		key_pos = key_pos + 7;
		do{
			min_buff[rx_index] = key_pos[rx_index];
			rx_index++;
		}while(key_pos[rx_index] != '(');
		//convert received buffer to control value
		Temp_set = atof(tempset_buff);
		Humi_set = atof(humiset_buff);
		NumDay = atoi(Numday_buff);
		date = atoi(date_buff);
		month = atoi(month_buff);
		year = atoi(year_buff);
		hour = atoi(hour_buff);
		min = atoi(min_buff);
		rx_index = 0;
		memset(buff_rx,0,sizeof(buff_rx));
		flag_setting_count++;
		flag_switch = 2;
}
static void Get_FanHeater_Status(){
	rx_index = 0;
	//get fan status
	char *key_pos = strstr(buff_rx,Fan_key) + strlen(Fan_key);
	do{
		Fan_status_buff[rx_index] = key_pos[rx_index];
		rx_index++;
	}while(key_pos[rx_index] != '^');

	//get heater status message
	rx_index = 0;
	key_pos = key_pos + 16;
	do{
		Heater_status_buff[rx_index] = key_pos[rx_index];
		rx_index++;
	}while(key_pos[rx_index] != ',');
	//convert value
	Fan_status = atoi(Fan_status_buff);
	Heater_status = atoi(Heater_status_buff);
	rx_index = 0;
	memset(buff_rx,0,sizeof(buff_rx));
	flag_manual_count++;
}
void Init_UART_Rx(){
	//HAL_UART_Receive_IT(&huart1, &data_rx, sizeof(data_rx));
	HAL_UART_Receive_DMA(&huart1, &data_rx, sizeof(data_rx));
}
void Send_Data_UART(){
	current_time = HAL_GetTick();
	if(current_time - previous_time > 1000){
		Send_tempHumi_FanHeater();
		flag_send_count++;
		previous_time = current_time;
	}
}
void Get_ESP32data(){
		buff_rx[rx_index] = data_rx;
		rx_index++;
		//receive mode status
		if(data_rx == '*'){
			if(flag_saved == 1){
				Set_Time();
				Write_Flash();
				flag_send_count = 0;
				check_temphumi();
				flag_saved = 0;
			}
			Get_Mode_Status();
		}
		//receive device status in MANUAL MODE
		else if(data_rx == ','){
			if(machine_mode == MANUAL_MODE)
			Get_FanHeater_Status();
		}
		//receive screen status in AUTO MODE
		else if(data_rx == '%'){
			if(machine_mode == AUTO_MODE)
			Get_Screen_Status();
		}
		//receive dataset in SETTING MODE
		else if(data_rx == '('){
			if(machine_mode == SETTING_MODE)
			Get_Setting_Data();
		}
		//HAL_UART_Receive_IT(&huart1, &data_rx, sizeof(data_rx));*/
}































