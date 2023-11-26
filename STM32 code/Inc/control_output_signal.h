#ifndef INC_CONTROL_OUTPUT_SIGNAL_H_
#define INC_CONTROL_OUTPUT_SIGNAL_H_
#include "stm32f1xx_hal.h"
#include "heater.h"
#include"fan.h"
#include"Buzz.h"
void Control_Heater_auto();
void Control_Fan_auto();
void Control_Heater_manual();
void Control_Fan_manual();
void Control_Buzz();
#endif /* INC_CONTROL_OUTPUT_SIGNAL_H_ */
