#ifndef INC_SAVE_DATA_H_
#define INC_SAVE_DATA_H_
#define ADDRESS_125_TEMP 	((uint32_t)0x0801F400)
#define ADDRESS_126_HUMI 	((uint32_t)0x0801F800)
#define ADDRESS_127_NUMDAY  ((uint32_t)0x0801FC00)
#include"FLASH.h"
#include"main.h"
void Write_Flash();
void Read_Flash();
#endif /* INC_SAVE_DATA_H_ */
