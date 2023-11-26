#include "send_data.h"
#include "data_setting.h"
extern SoftwareSerial softSerial;
extern uint8_t flag_save,flag_switch_mode,flag_switch_screen,flag_switch_fan,flag_switch_heater,Fan_status,Heater_status,mode_status,screen_status;
extern data_setting data;
extern egg_type select_egg;
void Check_Mode_Status(){
    if(flag_switch_mode == 1){
            String buff_mode_tx = "mode status:" + String(mode_status) + "*";
            softSerial.print(buff_mode_tx);
            if(mode_status == AUTO_MODE)        Serial.println("Auto mode selected");
            else if(mode_status == SETTING_MODE)Serial.println("Setting mode selected");
            else if(mode_status == MANUAL_MODE) Serial.println("Manual mode selected");
        }
        flag_switch_mode = 0;
}
void Change_Screen(){
    if(flag_switch_screen == 1){
        String Screen_buff = "screen status:" + String(screen_status) + "%";
        softSerial.print(Screen_buff);
        flag_switch_screen = 0;
    }
}
void Send_Setting_Data(){
    if(flag_save == 1){
        String EggSelect_str = "data have been saved for ";
        if(select_egg == Chicken_egg){
            ChickenEgg_Setting();
            String ChickenEgg_str = "chicken egg setting";
            EggSelect_str = EggSelect_str + ChickenEgg_str;
        }
        else if(select_egg == Duck_egg){
            DuckEgg_Setting();
            String DuckEgg_str = "duck egg setting";
            EggSelect_str = EggSelect_str + DuckEgg_str;
        }
        else if(select_egg == User_egg){
            String UserEgg_str = "user egg setting";
            EggSelect_str = EggSelect_str + UserEgg_str;
        }
         String buff_dataset ="temp:"    + String(data.temp_set) + "!" +
                              "humi:"    + String(data.humi_set) + "@" +
                              "numdays:" + String(data.numday)   + "#" +
                              "date:"    + String(data.date)     + "$" +
                              "month:"   + String(data.month)    + "%" +
                              "year:"    + String(data.year)     + "^" +
                              "hour:"    + String(data.hour)     + "&" +
                              "min:"     + String(data.min)      + "(" ; 
        softSerial.print(buff_dataset);
        Serial.println(buff_dataset);
        Serial.println(EggSelect_str);
        flag_save = 0;
    }
}
void Send_FanHeater_Status(){
    if(flag_switch_fan == 1 || flag_switch_heater == 1){
        String buff_device_tx = "fan status:" + String(Fan_status) + 
                                "^heater status:" + String(Heater_status) + ",";
        softSerial.print(buff_device_tx);
        if(Fan_status == 1) Serial.println("fan on");
        else                Serial.println("fan off");
        if(Heater_status == 1) Serial.println("heater on");
        else                Serial.println("heater off");
        Serial.println("--------");
        flag_switch_fan = 0;
        flag_switch_heater = 0;
    }
} 