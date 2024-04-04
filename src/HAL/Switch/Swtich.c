/****************************************************************************************************************************************************/
/* File Name:	Switch.c                                                                                                                            */
/* Module	: 	Switch						                                                                                                        */
/* Layer	:	HAL										                                                                                            */
/* AUTHOR   :   Lina Nassar                                                                                                                         */
/****************************************************************************************************************************************************/

#include "Switch.h"
#include "Switch_Config.h"
#include "MCAL/GPIO/GPIO.h"

/*Global Variables*/
extern Switch_StartCfg_t Switches[_Switch_Num];
static uint8_t Switches_States[_Switch_Num];

static uint8_t Sw_ReturnState(uint32_t Switch_Name)
{
    uint8_t PinValue;

    GPIO_GetPinValue(Switches[Switch_Name].Port, Switches[Switch_Name].Pin, &PinValue);

    return (PinValue ^ Switches[Switch_Name].Connection);
}


void Switch_Runnable(uint32_t Switch_Name)
{
    uint8_t CurrentState=-1;
    static uint32_t PrevState=-1;
    static uint32_t count=0;
    
    CurrentState = Sw_ReturnState(Switch_Name);

    if(CurrentState == PrevState)
    {
        count++;
    }
    else
    {
        count=0;
    }

    if(count==5)
    {
        Switches_States[Switch_Name]= CurrentState;
    }
    PrevState= CurrentState;

}

Switch_errors_t Switch_init(void)
{
    Switch_errors_t Ret_Swinit= Switch_error_Ok;
    GPIO_Pin_t Switch;
    uint32_t itr=0;
   
    if(_Switch_Num <= 0)
    {
        Ret_Swinit= Switch_error_SwitchNotExist;
    }
    else
    {
        Switch.Speed = GPIO_Speed_High;
        Switch.AF= GPIO_AF_non;

        for (itr=0 ; itr < _Switch_Num ; itr++)
        {
            Switch.Port= Switches[itr].Port;
            Switch.Pin= Switches[itr].Port;

            switch (Switches[itr].Connection)
            {
            case Sw_PullUp:
                Switch.Cfg = GPIO_Cfg_Input_PU;
                break;

            case Sw_PullDown:
                Switch.Cfg = GPIO_Cfg_Input_Pd;
                break;

            default: 
                break;
            }

            GPIO_init(&Switch);
        }
    }
    return Ret_Swinit;
}


Switch_errors_t Switch_GetSwitchState(uint32_t SwitchName, uint8_t* State) 
{
    Switch_errors_t Ret_GetSw= Switch_error_Ok;

    if(SwitchName > _Switch_Num || SwitchName <= 0)
    {
        Ret_GetSw= Switch_error_SwitchNotExist;
    }
    else if(!State)
    {
        Ret_GetSw= Switch_error_NullPointer;
    }
    if(Ret_GetSw == Switch_error_Ok)
    {
        State = Switches_States[SwitchName];
    }

    return Ret_GetSw;
}



