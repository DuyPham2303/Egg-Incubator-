#include"warning.h"
#include"control_output_signal.h"
extern float Temp_set,Humi_set;
int8_t temphumi_warning = 0,flag_buzz = 0;
char warning_notice1_buff[16];
char warning_notice2_buff[16];
void check_temphumi(){
	if(Temp_set > MAX_TEMP_SET && Humi_set > MAX_HUMI_SET){
			strcpy(warning_notice1_buff," Temp must < 50");
			strcpy(warning_notice2_buff," Humi must < 90");
			temphumi_warning = 1;
	}
	else{
		Buzz_OFF();
		temphumi_warning = 0;
		flag_buzz = 0;
	}
}
