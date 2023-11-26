#include"setting_data.h"
extern DS3231_Name egg_rtc;
extern int8_t hour,min,sec,day,date,month;
extern int16_t year;
void Set_Time(){
	DS3231_SetTime(&egg_rtc, hour, min, sec);
    DS3231_SetDate(&egg_rtc,day,date,month,year);
}
