#define BLYNK_TEMPLATE_ID "TMPL6bAPmBKhu"
#define BLYNK_TEMPLATE_NAME "EggIncubator"
#define BLYNK_AUTH_TOKEN "VM-fUe9v-HKlYjz-KUmBCkJn1YNaEvYB"
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "main.h"
#include "data_setting.h"
#include "send_data.h"
#include "receive_data.h"
char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "The Coffee House";
//char pass[] = "thecoffeehouse";
char ssid[] = "Duy Khoa";
char pass[] = "gacon123";
float temperature_value,humidity_value,Tempset_value,Humiset_value;
char data_rx;
String buff_mode_tx = "mode status:";
uint8_t screen_status,Fan_status,mode_status,mode_blynk,Heater_status,save_status;
String received_data;
uint8_t flag_switch_screen = 0,flag_switch_mode = 0,flag_switch_fan = 0,flag_switch_heater = 0,flag_save = 0;
data_setting data;
egg_type select_egg;
WidgetLED FAN_STATUS_LED(V4);
WidgetLED HEATER_STATUS_LED(V5);
SoftwareSerial softSerial(RX_PIN, TX_PIN);  // Create a software serial object
void setup() {
    Serial.begin(115200);  // Initialize the Arduino Serial Monitor for debugging
    Blynk.begin(auth,ssid,pass);
    softSerial.begin(38400);  // Initialize the software serial interface with the same baud rate
    softSerial.listen();
    Serial.println("ESP32 Software Serial Communication Ready");
}
BLYNK_WRITE(SCREEN){
    if(mode_blynk == AUTO_MODE){
        screen_status = param.asInt();
        flag_switch_screen = 1;
    }
}
BLYNK_WRITE(SWITCH_FAN){
    if(mode_blynk == MANUAL_MODE){
        Fan_status = param.asInt();
        flag_switch_fan = 1;
        if(Fan_status == 1) FAN_STATUS_LED.on();
        else                FAN_STATUS_LED.off();
    }
}
BLYNK_WRITE(SWITCH_HEATER){
    if(mode_blynk == MANUAL_MODE){
        Heater_status = param.asInt();
        flag_switch_heater = 1;
        if(Heater_status == 1) HEATER_STATUS_LED.on();
        else                   HEATER_STATUS_LED.off();
    }
}
BLYNK_WRITE(SWITCH_MODE){
    mode_blynk = param.asInt();
    if(mode_blynk == 1) {
        mode_status = AUTO_MODE;
    }
    else if(mode_blynk == 2){
        mode_status = SETTING_MODE;
    }
    else if(mode_blynk == 3){
        mode_status =  MANUAL_MODE;
    }

    flag_switch_mode = 1;
}
BLYNK_WRITE(SAVE){
    if(mode_blynk == SETTING_MODE){
        save_status = param.asInt();
        if(save_status == 1) flag_save = 1;
    }
}
BLYNK_WRITE(TEMP_INPUT){
    if(mode_blynk == SETTING_MODE){
        data.temp_set = param.asDouble();
    }
}
BLYNK_WRITE(HUMI_INPUT){
    if(mode_blynk == SETTING_MODE){
        data.humi_set = param.asDouble();
    }       
}
BLYNK_WRITE(HOUR){
    if(mode_blynk == SETTING_MODE){
        data.hour = param.asInt();
    }
}
BLYNK_WRITE(MIN){
    if(mode_blynk == SETTING_MODE){
        data.min = param.asInt();
    }           
}
BLYNK_WRITE(DATE){
    if(mode_blynk == SETTING_MODE){
        data.date = param.asInt();
    }     
}
BLYNK_WRITE(MONTH){
    if(mode_blynk == SETTING_MODE){
        data.month = param.asInt();
    }              
}
BLYNK_WRITE(YEAR){
    if(mode_blynk == SETTING_MODE){
       data.year = param.asInt();
    }           
}
BLYNK_WRITE(EGG_TYPE){
    if(mode_blynk == SETTING_MODE){
        int type_egg = param.asInt();
        if(type_egg == 0){
            select_egg = User_egg;
        }
        else if(type_egg == 1){
            select_egg = Chicken_egg;
        }
        else{
            select_egg = Duck_egg;
        }
    }          
}
BLYNK_WRITE(NUMDAYS){
     if(mode_blynk == SETTING_MODE){
        data.numday = param.asInt();
    }          
}
void Public_TempHumi(){
    Blynk.virtualWrite(TEMP,temperature_value);
    Blynk.virtualWrite(HUMI,humidity_value);
    Blynk.virtualWrite(TEMPSET,Tempset_value);
    Blynk.virtualWrite(HUMISET,Humiset_value);  
}
void Public_FanHeater_Status(){
    if(Fan_status == 1)    FAN_STATUS_LED.on();
    else                   FAN_STATUS_LED.off();
    if(Heater_status == 1) HEATER_STATUS_LED.on();
    else                   HEATER_STATUS_LED.off(); 
}

void loop() {
    Blynk.run();
    switch(mode_status){
        case AUTO_MODE:
        Check_Mode_Status();
        Change_Screen();
        Receive_Data();
        Public_FanHeater_Status();
        Public_TempHumi();
        break;
        case SETTING_MODE:
        Check_Mode_Status();
        Send_Setting_Data();
        break;
        case MANUAL_MODE:
        Check_Mode_Status();
        Send_FanHeater_Status();
        Public_FanHeater_Status();
        break; 
    }; 
}
