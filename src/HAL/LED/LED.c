/****************************************************************************************************************************************************/
/* File Name:	LED.c                                                                                                                               */
/* Module	: 	LED							                                                                                                        */
/* Layer	:	HAL										                                                                                            */
/* AUTHOR   :   Lina Nassar                                                                                                                         */
/* Date     :   10/12/2023                                                                                                                          */
/****************************************************************************************************************************************************/


#include "LED.h"
#include "LED_Config.h"
#include "MCAL/GPIO/GPIO.h"

#define Led_Pin_High   1
#define Led_Pin_Low    0


/*Global Variables*/
extern const Led_StartCfg_t Leds[_Led_Num];


Led_errors_t Led_init(void)
{
    
    Led_errors_t Ret_Ledinit= Led_error_Ok;
    GPIO_Pin_t Led;
    uint32_t itr=0;
   
    if(_Led_Num <= 0)
    {
        Ret_Ledinit= Led_error_LedNotExist;
    }
    else 
    {
        Led.Cfg = GPIO_Cfg_Output_PP;
        Led.Speed= GPIO_Speed_High;
        Led.AF= GPIO_AF_non;

        for (itr=0 ; itr < _Led_Num ; itr++)
        {
            Led.Port = Leds[itr].Port;
            Led.Pin = Leds[itr].Pin;    
            GPIO_init(&Led);
            Led_SetLedState(itr, Leds[itr].DefaultState);        
        }

    }

    return Ret_Ledinit;
}


Led_errors_t Led_SetLedState(uint32_t Led_Name, uint8_t Led_State)
{
    Led_errors_t Ret_LedSet = Led_error_Ok;
    uint32_t Led_Pin_State;

    if(Led_Name >= _Led_Num || Led_Name < 0)
    {
        Ret_LedSet = Led_error_LedNotExist;
    }
    else if (!(Led_State == Led_State_On || Led_State == Led_State_Off))
    {
        Ret_LedSet = Led_error_WrongState;

    }
    if( Ret_LedSet == Led_error_Ok)
    {
        Led_Pin_State =(Leds[Led_Name].Connection ^ Led_State);

        switch (Led_Pin_State)
        {
        case Led_Pin_High:
            GPIO_SetPinState(Leds[Led_Name].Port , Leds[Led_Name].Pin , GPIO_State_Set);
            break;
        case Led_Pin_Low:
            GPIO_SetPinState(Leds[Led_Name].Port , Leds[Led_Name].Pin , GPIO_State_Reset);
            break;
        default:
            break;
        }
        
    }

    return Ret_LedSet;
}



