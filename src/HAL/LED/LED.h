/****************************************************************************************************************************************************/
/* File Name:	LED.h                                                                                                                               */
/* Module	: 	LED							                                                                                                        */
/* Layer	:	HAL										                                                                                            */
/* AUTHOR   :   Lina Nassar                                                                                                                         */
/* Date     :   10/12/2023                                                                                                                          */
/****************************************************************************************************************************************************/

#ifndef LED_H
#define LED_H

#include "Libraries/STD_Types.h"

/*Led Connection Type*/
#define Led_Forward_Conn     0
#define Led_Reverse_Conn     1

/*Led State*/
#define Led_State_On 		 1
#define Led_State_Off 	     0


typedef enum
{
	/*Everything Ok, Function had Performed Correctly*/
	Led_error_Ok,             									
	/*NULL Pointer is passed*/
	Led_error_NullPointer,										
	/* Select Configuration type Not Found*/     
	Led_error_WrongConnection,    								
	/*Selected State not found*/     
	Led_error_WrongState,                                   
	/*No Leds were Listed*/     
	Led_error_LedNotExist                                  	

}Led_errors_t;


/*Structure that has the initial configuration of each Led*/
typedef struct 
{
    void* 	 Port;
    uint32_t Pin;
    uint32_t Connection;
    uint32_t DefaultState;

}Led_StartCfg_t;

/**
 *@brief  : This function initializes the required LEDs' Ports & Pins, their Active Status and Value.
 *@param  : void
 *@return : Error Status               
 */
Led_errors_t Led_init(void);


/**
 *@brief  : Sets a LED to ON or OFF
 *@param  : LED Name and State (on or off)
 *@return : Error Status              
 */
Led_errors_t Led_SetLedState(uint32_t Led_Name, uint8_t Led_State);

#endif