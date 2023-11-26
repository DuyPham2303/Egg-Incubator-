#include <Connect_UART.h>
#include <display_data.h>
#include"setting_data.h"
#include"warning.h"
extern DS3231_Name egg_rtc;
extern I2C_HandleTypeDef hi2c1;
extern volatile int8_t flag_enter;
extern int8_t flag_buzz ,flag_sendSMS,temphumi_warning,flag_clr,flag_switch,flag_saved,flag_send_count,machine_mode;
extern int16_t year;
extern float tCelsius,RH;
extern int8_t hour,min,date,month;
extern int16_t NumDay;
extern float Temp_set,Humi_set;
int8_t screen_status = 0;
char temp_buf[16];
char humi_buf[16];
char buff_rtc1[16];
char buff_rtc2[16];
char SetTemp_buff[16];
char SetHumi_buff[16];
char DayCount_buff[16];
char DaySet_buff[16];
char dataset_buff[16];
extern char warning_notice1_buff[16];
extern char warning_notice2_buff[16];
LCD_I2C_Name LCD;
static void Screen_Erase(int8_t *clr){
	if(*clr == 1){
		LCD_I2C_Clear(&LCD);
		HAL_Delay(100);
		*clr = 0;	// reset interrupt flag
	}
}
static void Screen1_Current_TempHumi(){
	Screen_Erase(&flag_clr);
	LCD_I2C_SetCursor(&LCD, 0, 0);
	sprintf(temp_buf,"temp:%.2fC",tCelsius);
	LCD_I2C_WriteString(&LCD, temp_buf);
	LCD_I2C_SetCursor(&LCD, 0, 1);
	sprintf(humi_buf,"humi:%.2f%%",RH);
	LCD_I2C_WriteString(&LCD, humi_buf);
	if(flag_send_count == 3 && temphumi_warning == 1){
		machine_mode = ERROR_MODE;
		//flag_sendSMS = 1;
		temphumi_warning = 0;
		flag_buzz = 1;
		flag_clr = 1;
	}
}
static void Screen2_Current_Time(){
	Screen_Erase(&flag_clr);
	//display time
	LCD_I2C_SetCursor(&LCD,4,0);
	sprintf(buff_rtc1,"%.2d:%.2d:%.2d",egg_rtc.Hours,egg_rtc.Min,egg_rtc.Sec);
	LCD_I2C_WriteString(&LCD,buff_rtc1);
	if(year == 0){
		LCD_I2C_SetCursor(&LCD,4,1);
		sprintf(buff_rtc2,"%.2d/%.2d/%.2d",egg_rtc.Date,egg_rtc.Month,egg_rtc.Year);
	}
	else{
		LCD_I2C_SetCursor(&LCD,3,1);
		sprintf(buff_rtc2,"%.2d/%.2d/20%.2d",egg_rtc.Date,egg_rtc.Month,egg_rtc.Year);
	}
	LCD_I2C_WriteString(&LCD,buff_rtc2);
}
static void Screen3_TempHumi_Set(){
	Screen_Erase(&flag_clr);
	LCD_I2C_SetCursor(&LCD, 0, 0);
	sprintf(SetTemp_buff,"Temp set:%.2fC",Temp_set);
	LCD_I2C_WriteString(&LCD, SetTemp_buff);
	LCD_I2C_SetCursor(&LCD, 0, 1);
	sprintf(SetHumi_buff,"Humi set:%.2f%%",Humi_set);
	LCD_I2C_WriteString(&LCD, SetHumi_buff);
}
static void Screen4_Numdays_Set(){
	Screen_Erase(&flag_clr);
	LCD_I2C_SetCursor(&LCD, 0, 0);
	sprintf(DaySet_buff,"NumDay Set:%.2d",NumDay);
	LCD_I2C_WriteString(&LCD, DaySet_buff);
}
static void Screen_DataSaved(){
	LCD_I2C_SetCursor(&LCD,0,0);
	LCD_I2C_WriteString(&LCD,"   DATA SAVED ");
	LCD_I2C_SetCursor(&LCD, 0, 1);
	LCD_I2C_WriteString(&LCD,"  SUCCESSFULLY");
	HAL_Delay(2000);
}
void Display_Init(){
	  LCD_I2C_Init(&LCD, &hi2c1,PCF8574_ADDRESS,16,2);
}
void Display_Run_Auto(){
		if(flag_switch == 1){
			LCD_I2C_Clear(&LCD);
			LCD_I2C_SetCursor(&LCD,0,0);
			LCD_I2C_WriteString(&LCD,"    AUTO MODE   ");
			LCD_I2C_SetCursor(&LCD,0,1);
			LCD_I2C_WriteString(&LCD,"  IS ACTIVATED ");
			HAL_Delay(2000);
			LCD_I2C_Clear(&LCD);
			flag_switch = 0;
			//Init_UART_Rx(); // keep checking received data from esp32
		}
		if(screen_status == 0) 	    Screen1_Current_TempHumi();
		else if(screen_status == 1) Screen2_Current_Time();
		else if(screen_status == 2) Screen3_TempHumi_Set();
		else if(screen_status == 3) Screen4_Numdays_Set();

}
void Display_Run_Setting(){
		if(flag_switch == 2){
			Screen_DataSaved();
			flag_saved = 1;
			flag_switch = 0;
			//Init_UART_Rx();
		}
		LCD_I2C_SetCursor(&LCD,0,0);
		LCD_I2C_WriteString(&LCD,"  SETTING MODE  ");
		LCD_I2C_SetCursor(&LCD, 0, 1);
		LCD_I2C_WriteString(&LCD,"  IS ACTIVATED  ");
}
void Display_Run_Manual(){
	if(flag_switch == 3){
		LCD_I2C_Clear(&LCD);
		LCD_I2C_SetCursor(&LCD,0,0);
		LCD_I2C_WriteString(&LCD,"   MANUAL MODE  ");
		LCD_I2C_SetCursor(&LCD,0,1);
		LCD_I2C_WriteString(&LCD,"  IS  ACTIVATED ");
		HAL_Delay(2000);
		LCD_I2C_Clear(&LCD);
		//Init_UART_Rx(); // keep checking received data from esp32
		flag_switch = 0;
	}
	Screen1_Current_TempHumi();
}
void Display_Start(){
	LCD_I2C_SetCursor(&LCD,1,0);
	LCD_I2C_WriteString(&LCD,"PROGRAM LOADED");
	LCD_I2C_SetCursor(&LCD,2,1);
	LCD_I2C_WriteString(&LCD,"SUCCESSFULLY");
	HAL_Delay(3000);
	LCD_I2C_Clear(&LCD);
	LCD_I2C_SetCursor(&LCD,1,0);
	LCD_I2C_WriteString(&LCD,"PLEASE CHOOSE");
	LCD_I2C_SetCursor(&LCD,3,1);
	LCD_I2C_WriteString(&LCD,"YOUR MODE ");
}

void Display_Warning(){
	Screen_Erase(&flag_clr);
	LCD_I2C_SetCursor(&LCD, 0, 0);
	LCD_I2C_WriteString(&LCD,warning_notice1_buff);
	LCD_I2C_SetCursor(&LCD, 0, 1);
	LCD_I2C_WriteString(&LCD,warning_notice2_buff);
}
