#include "receive_data.h"
extern String received_data;
extern SoftwareSerial softSerial;
extern float temperature_value,humidity_value,Tempset_value,Humiset_value;
extern uint8_t Fan_status,Heater_status;
static void Get_TempHumi_DeviceStatus(){
    received_data = softSerial.readString();
    // Look for "Temp:" and "Humi:" in the received string
    int tempIndex = received_data.indexOf("Temp:");
    int humiIndex = received_data.indexOf("Humi:");
    int FanstatusIndex = received_data.indexOf("Fan_status:");
    int HeaterstatusIndex = received_data.indexOf("Heater_status:");
    int TempsetIndex = received_data.indexOf("TempSet:");
    int HumisetIndex = received_data.indexOf("HumiSet:");

    if (tempIndex != -1 && humiIndex != -1 && 
        FanstatusIndex != -1 && HeaterstatusIndex != -1 &&
        TempsetIndex != -1 && HumisetIndex != -1) {
        // Extract the temperature and humidity values
        tempIndex += 5;  // Move the index past "Temp:" -> move the pointer 5 times until it reach the get value
        humiIndex += 5;  // Move the index past "Humi:"
        FanstatusIndex += 11;
        HeaterstatusIndex += 14;
        TempsetIndex += 8;
        HumisetIndex += 8;
        
        // Find the next ',' after the extracted values
        int commaIndex = received_data.indexOf(',', tempIndex);
        //get realtime temp
        if (commaIndex != -1) {
            String temperature_str = received_data.substring(tempIndex, commaIndex); 
            temperature_value = temperature_str.toFloat();

            commaIndex = received_data.indexOf(',', humiIndex);
            //get realtime humiAb
            if (commaIndex != -1) {
                String humidity_str = received_data.substring(humiIndex, commaIndex);
                humidity_value = humidity_str.toFloat();
                //get fan status
                commaIndex = received_data.indexOf(',',FanstatusIndex);
                if(commaIndex != -1){
                    String Fanstatus_str = received_data.substring(FanstatusIndex,commaIndex);
                    Fan_status = Fanstatus_str.toInt();

                    commaIndex = received_data.indexOf(',',HeaterstatusIndex);
                    //get heater status
                    if(commaIndex != -1){
                        String Heaterstatus_str = received_data.substring(HeaterstatusIndex,commaIndex);
                        Heater_status = Heaterstatus_str.toInt();

                        commaIndex = received_data.indexOf(',',TempsetIndex);
                        //get tempset value
                        if(commaIndex != -1){
                            String Tempset_str = received_data.substring(TempsetIndex,commaIndex);
                            Tempset_value = Tempset_str.toFloat();

                            commaIndex = received_data.indexOf(',',HumisetIndex);
                            //get humiset value
                            if(commaIndex != -1){
                                String Humiset_str = received_data.substring(HumisetIndex,commaIndex);
                                Humiset_value = Humiset_str.toFloat();
                            }
                        }
                    }
                }
            }
        }
    } 

}
static void Print_data(){
    Serial.println("temp:" + String(temperature_value) + "°C" + "  humi:" + String(humidity_value) + "%" + 
                 ",fan status:" + String(Fan_status) + ",heater status:" + String(Heater_status) + 
                 ",temp set:" + String(Tempset_value) + ",humi set:" + String(Humiset_value));
}

void Receive_Data(){
 while(softSerial.available()) {
        Get_TempHumi_DeviceStatus();
        Print_data();
    }   
}