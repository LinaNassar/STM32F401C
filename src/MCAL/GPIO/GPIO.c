/***************************************************************************************************************************/
/* File Name:	GPIO.c                                                                                                     */
/* Module	: 	GPIO						                                                                               */
/* Layer	:	MCAL										                                                               */
/* AUTHOR   :   Lina Nassar                                                                                                */
/* Date     :   20/2/2024                                                                                                  */
/***************************************************************************************************************************/

#include "GPIO.h"

#define GPIO_MODERBits   0   
#define GPIO_OTYPERBits  2   
#define GPIO_PUPDRBits   3   
#define GPIO_AFRegBit   32 

#define GPIO_AFRL       0
#define GPIO_AFRH       8



typedef struct GPIO
{
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;    
    uint32_t IDR;       
    uint32_t ODR;       
    uint32_t BSSR;       
    uint32_t PUPDR;       
    uint32_t AFRL;       
    uint32_t AFRH;    

}GPIO_Reg_t;

#define GPIO_Validate_Port(Port)        ((Port) < GPIO_PortA || (Port) > GPIO_PortH)
#define GPIO_Validate_Pin(Pin)          ((Pin) < GPIO_Pin0 || (Pin) > GPIO_Pin15)
#define GPIO_Validate_Speed             ((Pin_Config->Speed) < GPIO_Speed_Low || (Pin_Config->Port) > GPIO_Speed_VHigh)                             
#define GPIO_Validate_AF                ((Pin_Config->AF) < GPIO_AF_non || (Pin_Config->Port) > GPIO_AF15)    
#define GPIO_Validate_SetPin(GPIO_Pin)  (GPIO_Pin < GPIO_Pin0_Set || GPIO_Pin > GPIO_Pin15_Reset)
#define GPIO_Validate_Cfgr              ((Pin_Config->Cfg) == GPIO_Cfg_Output_PP    || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Output_PP_PU || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Output_PP_PD || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Output_OD    || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Output_OD_PU || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Output_OD_PD || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Input_Float  || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Input_PU     || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Input_Pd     || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_Analog       || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_AF_PP        || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_AF_PP_PU     || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_AF_PP_PD     || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_AF_OD        || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_AF_OD_Pu     || \
                                         (Pin_Config->Cfg) == GPIO_Cfg_AF_OD_PD        )



GPIO_errors_t GPIO_init(GPIO_Pin_t *Pin_Config)
{
    uint32_t Loc_RegisterTempVal, Loc_AFReg;
    GPIO_errors_t Ret_GpioInit = GPIO_error_Ok;
    
    if(Pin_Config == NULL)
    {
      Ret_GpioInit = GPIO_error_NuLLPtr; 
    }
    else if(!GPIO_Validate_Port((uint32_t)(Pin_Config->Port)))
    {
      Ret_GpioInit = GPIO_error_WrongPort; 
    } 
    else if(!GPIO_Validate_Pin(Pin_Config->Pin))
    {
      Ret_GpioInit = GPIO_error_WrongPin; 
    }
    else if(!GPIO_Validate_Cfgr)
    {
      Ret_GpioInit = GPIO_error_WrongCfg; 
    }
    else if(!GPIO_Validate_Speed)
    {
      Ret_GpioInit = GPIO_error_WrongSpeed; 
    }
    else if(!GPIO_Validate_AF)
    {
      Ret_GpioInit = GPIO_error_WrongAF; 
    }
    else if(Ret_GpioInit == GPIO_error_Ok)
    {
        /*MODE Register*/
        Loc_RegisterTempVal =  ((GPIO_Reg_t*)(Pin_Config->Port))->MODER;
        Loc_RegisterTempVal &= (~(Reg_Mask_2bits << (Pin_Config->Pin * Reg_Offset_2bit)));
        Loc_RegisterTempVal |= ( (EXTRACT_2BIT(Pin_Config->Cfg,GPIO_MODERBits)) << (Pin_Config->Pin * Reg_Offset_2bit));
        ((GPIO_Reg_t*)(Pin_Config->Port))->MODER = Loc_RegisterTempVal;

        /*OTYPE Register*/
        Loc_RegisterTempVal =  ((GPIO_Reg_t*)(Pin_Config->Port))->OTYPER;
        Loc_RegisterTempVal &= (~(Reg_Mask_1bit << Pin_Config->Pin));
        Loc_RegisterTempVal |= ( (EXTRACT_1BIT(Pin_Config->Cfg,GPIO_OTYPERBits)) << (Pin_Config->Pin));
        ((GPIO_Reg_t*)(Pin_Config->Port))->OTYPER = Loc_RegisterTempVal;

        /*PUPD Register*/
        Loc_RegisterTempVal =  ((GPIO_Reg_t*)(Pin_Config->Port))->PUPDR;
        Loc_RegisterTempVal &= (~(Reg_Mask_2bits << (Pin_Config->Pin * Reg_Offset_2bit)));
        Loc_RegisterTempVal |= ( (EXTRACT_2BIT(Pin_Config->Cfg,GPIO_PUPDRBits)) << (Pin_Config->Pin * Reg_Offset_2bit));
        ((GPIO_Reg_t*)(Pin_Config->Port))->PUPDR = Loc_RegisterTempVal;        

        /*OSPEED Register*/
        Loc_RegisterTempVal =  ((GPIO_Reg_t*)(Pin_Config->Port))->OSPEEDR;
        Loc_RegisterTempVal &= (~(Reg_Mask_2bits << (Pin_Config->Pin * Reg_Offset_2bit)));
        Loc_RegisterTempVal |= ( Pin_Config->Speed << (Pin_Config->Pin * Reg_Offset_2bit));
        ((GPIO_Reg_t*)(Pin_Config->Port))->OSPEEDR = Loc_RegisterTempVal;  

        /*AFRL & AFRH Register*/
        if(Pin_Config->Pin < GPIO_AFRH)
        {
            Loc_RegisterTempVal =  ((GPIO_Reg_t*)(Pin_Config->Port))->AFRL;
            Loc_RegisterTempVal &= (~(Reg_Mask_4bits<<(Pin_Config->Pin * Reg_Offset_4bit)));
            Loc_RegisterTempVal |= (Pin_Config->Speed<<(Pin_Config->Pin * Reg_Offset_4bit));
            ((GPIO_Reg_t*)(Pin_Config->Port))->AFRL = Loc_RegisterTempVal;
        }
        else
        {
            Loc_RegisterTempVal =  ((GPIO_Reg_t*)(Pin_Config->Port))->AFRH;
            Loc_RegisterTempVal &= (~(Reg_Mask_4bits<<((Pin_Config->Pin-8) * Reg_Offset_4bit)));
            Loc_RegisterTempVal |= (Pin_Config->Speed<<((Pin_Config->Pin-8) * Reg_Offset_4bit));
            ((GPIO_Reg_t*)(Pin_Config->Port))->AFRH = Loc_RegisterTempVal;
        }
    }

    return Ret_GpioInit;
}

GPIO_errors_t GPIO_SetPinValue(void *GPIO_Port, uint32_t GPIO_Pin) 
{
    GPIO_errors_t Ret_SetPinValue = GPIO_error_Ok;

    if(!GPIO_Validate_Port(GPIO_Port))
    {
      Ret_SetPinValue = GPIO_error_WrongPort; 
    } 
    else if(!GPIO_Validate_SetPin(GPIO_Pin))
    {
      Ret_SetPinValue = GPIO_error_WrongPin; 
    }
    else if(Ret_SetPinValue == GPIO_error_Ok)
    {
        ((GPIO_Reg_t*)(GPIO_Port))->BSSR= GPIO_Pin;
    }
    return Ret_SetPinValue;
}


GPIO_errors_t GPIO_GetPinValue(void *GPIO_Port, uint32_t GPIO_Pin, uint32_t *PinValue) /*GPIO_Pin0_Get*/
{
    GPIO_errors_t Ret_GetPinValue = GPIO_error_Ok;
    
    if(PinValue == NULL)
    {
      Ret_GetPinValue = GPIO_error_NuLLPtr; 
    }
    if(!GPIO_Validate_Port(GPIO_Port))
    {
      Ret_GetPinValue = GPIO_error_WrongPort; 
    } 
    else if(!GPIO_Validate_SetPin(GPIO_Pin))
    {
      Ret_GetPinValue = GPIO_error_WrongPin; 
    }
    else if(Ret_GetPinValue == GPIO_error_Ok)
    {
        *PinValue = ( (((GPIO_Reg_t*)(GPIO_Port))->IDR & (1 << GPIO_Pin)) >> GPIO_Pin );
    }

    return Ret_GetPinValue;
}


