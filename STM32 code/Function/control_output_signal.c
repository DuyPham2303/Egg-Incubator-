#include"control_output_signal.h"
#include"setting_data.h"
#include"Module_Sim.h"
extern float tCelsius,RH,Temp_set,Humi_set;
extern uint8_t Heater_status,Fan_status,wifi_status;
extern int8_t flag_buzz;
void Control_Fan_manual(){
	if(Fan_status == 1) TurnOn_fan();
	else 				TurnOff_fan();
}
void Control_Heater_manual(){
	if(Heater_status == 1) TurnOn_heater();
	else				   TurnOff_heater();
}
void Control_Heater_auto(){
	if(tCelsius > Temp_set){
		TurnOn_fan();
		Fan_status = 1;
	}
	else{
		TurnOff_fan();
		Fan_status = 0;
	}
}
void Control_Fan_auto(){
	if(RH > Humi_set){
		TurnOn_heater();
		Heater_status = 1;
	}
	else{
		TurnOff_heater();
		Heater_status = 0;
	}
}
void Control_Buzz(){
	if(flag_buzz == 1)Buzz_ON();
	else			  Buzz_OFF();
}
