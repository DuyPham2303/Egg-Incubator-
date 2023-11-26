#include "data_setting.h"
extern data_setting data;
void ChickenEgg_Setting(){
    data.temp_set = 37.5;
    data.humi_set = 55;
    data.numday = 21;
}
void DuckEgg_Setting(){
    data.temp_set = 37.8;
    data.humi_set = 60;
    data.numday = 35;
}