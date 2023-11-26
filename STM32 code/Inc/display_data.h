#ifndef INC_DISPLAY_DATA_H_
#define INC_DISPLAY_DATA_H_
#include"main.h"
#include"LCD_I2C.h"
#include"DS3231.h"
void Display_Init();
void Display_Warning();
void Display_Run_Auto();
void Display_Run_Manual();
void Display_Run_Setting();
void Display_Start();
void Screen_1_RunMode();
#endif /* INC_DISPLAY_DATA_H_ */
