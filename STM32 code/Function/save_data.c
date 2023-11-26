#include "save_data.h"
#include "stdint.h"
int16_t read_numday = 0;
float read_Tempset = 0,read_Humiset = 0;
extern int16_t NumDay;
extern float Temp_set,Humi_set;
static void write_flash_tempset(){
	Flash_erase(ADDRESS_125_TEMP);
	Flash_Write_Float(ADDRESS_125_TEMP,Temp_set);
}
static void write_flash_humiset(){
	Flash_erase(ADDRESS_126_HUMI);
	Flash_Write_Float(ADDRESS_126_HUMI,Humi_set);
}
static void write_flash_Numday(){
	Flash_erase(ADDRESS_127_NUMDAY);
	Flash_Write_Int(ADDRESS_127_NUMDAY,NumDay);
}
void Write_Flash(){
	write_flash_tempset();
	write_flash_humiset();
	write_flash_Numday();
}
static void read_flash_Temp(){
	read_Tempset = Flash_Read_Float(ADDRESS_125_TEMP);
	Temp_set = read_Tempset;
}
static void read_flash_Humi(){
	read_Humiset = Flash_Read_Float(ADDRESS_126_HUMI);
	Humi_set = read_Humiset;
}
static void read_flash_Numday(){
	read_numday = Flash_Read_Int(ADDRESS_127_NUMDAY);
	NumDay = read_numday;
}
void Read_Flash(){
	read_flash_Humi();
	read_flash_Temp();
	read_flash_Numday();
}
