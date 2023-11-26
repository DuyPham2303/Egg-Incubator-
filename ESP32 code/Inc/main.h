
#ifndef __MAIN_H
#define __MAIN_H
#define BLYNK_PRINT Serial
#define TEMPSET       V0
#define TEMP          V1
#define HUMISET       V2
#define HUMI          V3
#define SWITCH_FAN    V6
#define SWITCH_HEATER V7
#define SWITCH_MODE   V8
#define TEMP_INPUT    V9
#define HUMI_INPUT    V10
#define HOUR          V11
#define MIN           V12
#define DATE          V13
#define MONTH         V14
#define YEAR          V15
#define EGG_TYPE      V16
#define NUMDAYS       V17
#define SAVE          V18  
#define SCREEN        V19
#define AUTO_MODE    1
#define SETTING_MODE 2
#define MANUAL_MODE  3    
#define RX_PIN 16 
#define TX_PIN 17
#include "SoftwareSerial.h"  
#include "string.h"
#include "cstring"
#endif