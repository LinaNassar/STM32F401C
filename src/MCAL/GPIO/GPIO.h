/***************************************************************************************************************************/
/* File Name:	GPIO.h                                                                                                     */
/* Module	: 	GPIO						                                                                               */
/* Layer	:	MCAL										                                                               */
/* AUTHOR   :   Lina Nassar                                                                                                */
/* Date     :   20/2/2024                                                                                                  */
/***************************************************************************************************************************/

#ifndef GPIO_H
#define GPIO_H

#include "Masks.h"
#include "STD_Types.h"

/*GPIO Ports*/
#define GPIO_PortA      0x40020000
#define GPIO_PortB      0x40020400
#define GPIO_PortC      0x40020800
#define GPIO_PortD      0x40020C00
#define GPIO_PortE      0x40021000
#define GPIO_PortH      0x40021C00

/*GPIO Pins*/
#define GPIO_Pin0       0x0
#define GPIO_Pin1       0x1
#define GPIO_Pin2       0x2
#define GPIO_Pin3       0x3
#define GPIO_Pin4       0x4
#define GPIO_Pin5       0x5
#define GPIO_Pin6       0x6
#define GPIO_Pin7       0x7
#define GPIO_Pin8       0x8
#define GPIO_Pin9       0x9
#define GPIO_Pin10      0xA
#define GPIO_Pin11      0xB
#define GPIO_Pin12      0xC
#define GPIO_Pin13      0xD
#define GPIO_Pin14      0xE
#define GPIO_Pin15      0xF


/*GPIO Pin Cfg*/                   
#define GPIO_Cfg_Output_PP     0b00001    
#define GPIO_Cfg_Output_PP_PU  0b01001  
#define GPIO_Cfg_Output_PP_PD  0b10001  
#define GPIO_Cfg_Output_OD     0b00101  
#define GPIO_Cfg_Output_OD_PU  0b01101  
#define GPIO_Cfg_Output_OD_PD  0b10101  
#define GPIO_Cfg_Input_Float   0b00000       
#define GPIO_Cfg_Input_PU      0b01000    
#define GPIO_Cfg_Input_Pd      0b10000    
#define GPIO_Cfg_Analog        0b00011
#define GPIO_Cfg_AF_PP         0b00010      
#define GPIO_Cfg_AF_PP_PU      0b01010       
#define GPIO_Cfg_AF_PP_PD      0b10010       
#define GPIO_Cfg_AF_OD         0b00110      
#define GPIO_Cfg_AF_OD_Pu      0b01110       
#define GPIO_Cfg_AF_OD_PD      0b10110        


/*GPIO Pin Speeds*/
#define GPIO_Speed_Low          0
#define GPIO_Speed_Med          1
#define GPIO_Speed_High         2
#define GPIO_Speed_VHigh        3



/*GPIO Bits SET*/
#define GPIO_Pin0_Set           Reg_Mask_bit0                 
#define GPIO_Pin1_Set           Reg_Mask_bit1                   
#define GPIO_Pin2_Set           Reg_Mask_bit2                   
#define GPIO_Pin3_Set           Reg_Mask_bit3                   
#define GPIO_Pin4_Set           Reg_Mask_bit4                   
#define GPIO_Pin5_Set           Reg_Mask_bit5                   
#define GPIO_Pin6_Set           Reg_Mask_bit6                   
#define GPIO_Pin7_Set           Reg_Mask_bit7                   
#define GPIO_Pin8_Set           Reg_Mask_bit8                   
#define GPIO_Pin9_Set           Reg_Mask_bit9                   
#define GPIO_Pin10_Set          Reg_Mask_bit10                   
#define GPIO_Pin11_Set          Reg_Mask_bit11                   
#define GPIO_Pin12_Set          Reg_Mask_bit12                   
#define GPIO_Pin13_Set          Reg_Mask_bit13                   
#define GPIO_Pin14_Set          Reg_Mask_bit14                   
#define GPIO_Pin15_Set          Reg_Mask_bit15                   


/*GPIO Bits Reset*/
#define GPIO_Pin0_Reset         Reg_Mask_bit16       
#define GPIO_Pin1_Reset         Reg_Mask_bit17       
#define GPIO_Pin2_Reset         Reg_Mask_bit18       
#define GPIO_Pin3_Reset         Reg_Mask_bit19       
#define GPIO_Pin4_Reset         Reg_Mask_bit20       
#define GPIO_Pin5_Reset         Reg_Mask_bit21       
#define GPIO_Pin6_Reset         Reg_Mask_bit22       
#define GPIO_Pin7_Reset         Reg_Mask_bit23       
#define GPIO_Pin8_Reset         Reg_Mask_bit24       
#define GPIO_Pin9_Reset         Reg_Mask_bit25       
#define GPIO_Pin10_Reset        Reg_Mask_bit26
#define GPIO_Pin11_Reset        Reg_Mask_bit27
#define GPIO_Pin12_Reset        Reg_Mask_bit28
#define GPIO_Pin13_Reset        Reg_Mask_bit29
#define GPIO_Pin14_Reset        Reg_Mask_bit30 
#define GPIO_Pin15_Reset        Reg_Mask_bit31
 

/*Alternate Functions*/        
#define GPIO_AF_non             0x0
#define GPIO_AF0                0x0
#define GPIO_AF1                0x1
#define GPIO_AF2                0x2
#define GPIO_AF3                0x3
#define GPIO_AF4                0x4
#define GPIO_AF5                0x5
#define GPIO_AF6                0x6
#define GPIO_AF7                0x7
#define GPIO_AF8                0x8
#define GPIO_AF9                0x9
#define GPIO_AF10               0xA
#define GPIO_AF11               0xB
#define GPIO_AF12               0xC
#define GPIO_AF13               0xD
#define GPIO_AF14               0xE
#define GPIO_AF15               0xF


typedef struct
{
    void*    Port;     
    uint32_t Pin;    
    uint32_t Cfg;
    uint32_t Speed;
    uint32_t AF;

}GPIO_Pin_t;


typedef enum
{
    GPIO_error_Ok,
    GPIO_error_NOk,
    GPIO_error_NuLLPtr,
    GPIO_error_WrongPort,
    GPIO_error_WrongPin,
    GPIO_error_WrongCfg,
    GPIO_error_WrongSpeed,
    GPIO_error_WrongAF,

}GPIO_errors_t;

/**
 * @brief   : Initializes the GPIO Pin as per provided in GPIO_Pin_t struct, this icludes: Pin Cfgr,
 *            speed & alternate finction if applicable.
 * @param   : Address of Pin_Config, the initializaiton struct.
 * @return  : GPIO_errors_t
 */
GPIO_errors_t GPIO_init(GPIO_Pin_t *Pin_Config);

/**
 * @brief   : Controls the status of an output GPIO Pin to set(High) or reset(Low).
 * @param   : Port of the PIn, the Pin number and status included, ex:GPIO_Pin0_Set || GPIO_Pin0_Reset
 * @return  : GPIO_errors_t
 */
GPIO_errors_t GPIO_SetPinValue(void *GPIO_Port, uint32_t GPIO_Pin); 

/**
 * @brief   : Gets the current value of an input GPIO Pin and assigns it in Pinvalue.
 * @param   : Port of the Pin, the Pin number and an address to variable to hold the value of the pin
 * @return  : GPIO_errors_t
 */
GPIO_errors_t GPIO_GetPinValue(void *GPIO_Port, uint32_t GPIO_Pin, uint32_t *PinValue); /*GPIO_Pin0_Get*/


#endif