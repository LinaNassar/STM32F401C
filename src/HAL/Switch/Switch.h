/****************************************************************************************************************************************************/
/* File Name:	Switch.h                                                                                                                            */
/* Module	: 	Switch						                                                                                                        */
/* Layer	:	HAL										                                                                                            */
/* AUTHOR   :   Lina Nassar                                                                                                                         */
/****************************************************************************************************************************************************/
#ifndef SWITCH_H
#define SWITCH_H

#include "Libraries/STD_Types.h"


/*Switch Connection*/
#define Sw_PullUp  		1
#define Sw_PullDown  	0

/*Switch Current Value*/
#define Sw_Pressed    	1
#define Sw_NotPressed 	0



/*Structure that has the initial configuration of each Switch*/
typedef struct 
{
    void*    Port;
    uint32_t Pin;
    uint32_t Connection;

}Switch_StartCfg_t;


typedef enum
{
	/*Everything Ok, Function had Performed Correctly*/
	Switch_error_Ok=0,             								/*0*/
	/*NULL Pointer is passed*/
	Switch_error_NullPointer,									/*1*/
	/*Selected Port does not exist*/    
	Switch_error_WrongPort,      								/*2*/
	/*Selected Pin does not exist */
	Switch_error_WrongPin, 										/*3*/
	/*Selected Connection type Not Found*/     
	Switch_error_WrongConnection,                               /*4*/
	/*No Switches were Listed*/    
	Switch_error_SwitchNotExist                                 /*5*/

}Switch_errors_t;

/**
 *@brief  : This function initializes the required Switches' Port, Pin, & connection.
 *@param  : void
 *@return : Error Status               
 */
Switch_errors_t Switch_init(void);


/**
 *@brief  : Gets the value of a Switch
 *@param  : Switch Name and State (on or off)
 *@return : Error Status              
 */
void Switch_enuGetSwitchState(uint32_t SwitchName, uint32_t *SwitchState);

#endif