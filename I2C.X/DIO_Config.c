#include "DIO_Config.h"


DIO_Cfg_s Dio_configutation_A_ADC =
{
    GPIOA,PIN0,INPUT,PORT_NORMAL_MODE
};
DIO_Cfg_s Dio_configutation_A_7_seg = 
{
GPIOA,
PIN2|PIN3
,OUTPUT
,PORT_NORMAL_MODE
};
DIO_Cfg_s Dio_configutation_B =
{
    GPIOB,
    FULL_PORT,
    OUTPUT,
};
DIO_Cfg_s Dio_configutation_C=
{
    GPIOC,FULL_PORT,INPUT
            ,
};
DIO_Cfg_s Dio_configutation_D = 
{ 
    GPIOD,FULL_PORT,OUTPUT,
};
DIO_Cfg_s Dio_configutation_E;

