#ifndef __DATA_SETTING_H
#define __DATA_SETTING_H
#include "main.h"
enum egg_type{
    User_egg,
    Chicken_egg,
    Duck_egg
};
class data_setting{
public:
    float temp_set;
    float humi_set;
    int8_t numday;
    int8_t date,month,year;
    int8_t hour,min;
};
void ChickenEgg_Setting();
void DuckEgg_Setting();
#endif