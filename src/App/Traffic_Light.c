#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "HAL/LED/LED.h"
#include "HAL/LED/LED_Config.h"

#define Peroidicity_S 2
#define Green_Time    6  
#define Yellow_Time   4 
#define Red_Time      4 

enum Lights
{
    green,
    yellow,
    red,
};

static uint32_t Curr_State=green;
static uint32_t Prev_State=green;

void Traffic_Lights(void)
{
    static uint32_t seconds=0;
    seconds += Peroidicity_S;

    switch (Curr_State)
    {
    case yellow:
        
        Led_SetLedState(Led_Green,Led_State_On);
        Led_SetLedState(Led_Yellow,Led_State_Off);
        Led_SetLedState(Led_Red,Led_State_Off);

        if(seconds == Green_Time)
        {
            Curr_State=yellow;
            Prev_State=green;
            seconds=0;
        }

    case green:
        
        Led_SetLedState(Led_Green,Led_State_On);
        Led_SetLedState(Led_Yellow,Led_State_Off);
        Led_SetLedState(Led_Red,Led_State_Off);

        if(seconds == Yellow_Time)
        {
            if(Prev_State == green)
            {
                Curr_State=red;
                Prev_State=yellow;
                seconds=0;
            }
            else if(Prev_State == red)
            {
                Curr_State=green;
                Prev_State=yellow;
                seconds=0;
            }
        }
        break;

    case red:
        Led_SetLedState(Led_Green,Led_State_Off);
        Led_SetLedState(Led_Yellow,Led_State_Off);
        Led_SetLedState(Led_Red,Led_State_On);
        
        if(seconds == Red_Time)
        {
            Curr_State=yellow;
            Prev_State=red;
            seconds=0;
        }
        break;
    
    default:
        break;
    }


}