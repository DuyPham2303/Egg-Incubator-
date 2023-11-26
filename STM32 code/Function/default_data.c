#include "default_data.h"
extern DS3231_Name egg_rtc;
extern int8_t flag_enter;
extern int8_t flag_clr;
extern int8_t hour,min,sec,date,month;
extern uint32_t current_time,previous_time;
extern int16_t year,NumDay;
extern float Temp_set,Humi_set;
extern uint8_t Fan_status,Heater_status,mode_status,screen_status;
extern volatile int8_t flag_saved,flag_switch;
extern float RH,tCelsius;
static void Reset_time(){
	hour = 0,min = 0,date = 0,month = 0,year = 0;
}

void Default_Initalize(){
	 flag_enter = 0;
	 flag_clr = 0;
	 hour = 0,min = 0,sec = 0;
	 date = 0,month = 0,year = 0;
	 NumDay = 0;
	 Temp_set = 0,Humi_set = 0;
	 flag_saved = 0,flag_switch = 0;
	 current_time = 0,previous_time = 0;
	 RH = 0,tCelsius = 0;
	 Buzz_OFF();
	 Reset_time();
	 Set_Time();

}
