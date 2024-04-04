/****************************************************************************************************************************************************/
/* File Name:	LED_Config.c                                                                                                                        */
/* Module	: 	LED							                                                                                                        */
/* Layer	:	HAL										                                                                                            */
/* AUTHOR   :   Lina Nassar                                                                                                                         */
/****************************************************************************************************************************************************/

#include "LED.h"
#include "LED_Config.h"
#include "MCAL/GPIO/GPIO.h"

/*********************** User should choose from: ************************/
/*                                                                       */
/*  In .Port:     In .Pin:       In  .Connection:    In .DefaultState:   */
/*  *********     ********       ****************    *****************   */    
/*  GPIO_PortA    GPIO_Pin0      Led_Forward_Conn    Led_Sate_On 	 	 */
/*  GPIO_PortB    GPIO_Pin1      Led_REverse_Conn    Led_Sate_Off	 	 */
/*  GPIO_PortC    GPIO_Pin3                              			 	 */
/*  GPIO_PortD    GPIO_Pin4                              			 	 */
/*  GPIO_PortE    GPIO_Pin5                              			 	 */
/*  GPIO_PortH    GPIO_Pin6                               			 	 */
/*                GPIO_Pin7                              			 	 */
/*                GPIO_Pin8                              			 	 */
/*                GPIO_Pin9                              			 	 */
/*                GPIO_Pin10                             			 	 */
/*                GPIO_Pin11                             			 	 */
/*                GPIO_Pin12                             			 	 */
/*                GPIO_Pin13                             			 	 */
/*                GPIO_Pin14                             			 	 */
/*                GPIO_Pin15                             			 	 */
/*************************************************************************/

const Led_StartCfg_t Leds[_Led_Num]={
	/*[Alarm_Led]=
	{
		 .Port= 	,
		 .Pin= 		, 
		 .Connection=	, 
		 .DefaultState=		, 
	},*/
	[Led_Green]=
	{
		 .Port= GPIO_PortA,
		 .Pin= GPIO_Pin3, 
		 .Connection= Led_Forward_Conn	, 
		 .DefaultState=	Led_State_On	, 
	},
	[Led_Yellow]=
	{
		 .Port= GPIO_PortB,
		 .Pin= GPIO_Pin5, 
		 .Connection= Led_Forward_Conn	, 
		 .DefaultState=	Led_State_Off	, 
	},
	[Led_Red]=
	{
		 .Port= GPIO_PortA,
		 .Pin= GPIO_Pin1, 
		 .Connection= Led_Forward_Conn	, 
		 .DefaultState=	Led_State_Off	, 
	},

};