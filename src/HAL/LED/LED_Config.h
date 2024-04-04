/****************************************************************************************************************************************************/
/* File Name:	LED_Config.h                                                                                                                        */
/* Module	: 	LED							                                                                                                        */
/* Layer	:	HAL										                                                                                            */
/* AUTHOR   :   Lina Nassar                                                                                                                         */
/****************************************************************************************************************************************************/

#ifndef LED_CONFIG_H
#define LED_CONFIG_H

/*Add the names of the required switches to the list before _Switch_Num*/
typedef enum
{
    //Alarm_Led, /*Example*/
    Led_Green,
    Led_Yellow,
    Led_Red,
    _Led_Num,

}Leds_t;



#endif  