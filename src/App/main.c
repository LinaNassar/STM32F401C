#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"

int main (void)
{
    uint32_t Pina=0, Pinb=0, Pinc=0;
    RCC_ControlClock(Clock_HSE,ClockStatus_Enable);

    // RCC_ControlPeripheralClock(Peri_GPIOA, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_GPIOB, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_GPIOC, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_OTGFS, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_I2C3, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_USART2, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_TIM11, PeriStatus_Enable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_SPI2, PeriStatus_Enable, PowerMode_Normal);

    // RCC_ControlPeripheralClock(Peri_GPIOA, PeriStatus_Disable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_GPIOB, PeriStatus_Disable, PowerMode_Normal);
    // RCC_ControlPeripheralClock(Peri_GPIOC, PeriStatus_Disable, PowerMode_Normal);

    RCC_ControlPeripheralClock(Peri_GPIOA, PeriStatus_Enable, PowerMode_Normal);
    RCC_ControlPeripheralClock(Peri_GPIOB, PeriStatus_Enable, PowerMode_Normal);
    RCC_ControlPeripheralClock(Peri_GPIOC, PeriStatus_Enable, PowerMode_Normal);

    GPIO_Pin_t pinA=
    {
        .Port= GPIO_PortA,
        .Pin= GPIO_Pin0,
        .Cfg = GPIO_Cfg_Output_PP,
        .Speed= GPIO_Speed_Med,
        .AF= GPIO_AF_non
    };
    GPIO_Pin_t pinB=
    {
        .Port= GPIO_PortB,
        .Pin= GPIO_Pin4,
        .Cfg = GPIO_Cfg_Output_PP,
        .Speed= GPIO_Speed_Med,
        .AF= GPIO_AF_non
    };
    GPIO_Pin_t pinC=
    {
        .Port= GPIO_PortC,
        .Pin= GPIO_Pin13,
        .Cfg = GPIO_Cfg_Output_PP,
        .Speed= GPIO_Speed_Med,
        .AF= GPIO_AF_non
    };


    GPIO_init(&pinA);
    GPIO_init(&pinB);
    GPIO_init(&pinC);

    GPIO_SetPinValue(GPIO_PortA,GPIO_Pin0_Set);
    GPIO_SetPinValue(GPIO_PortB,GPIO_Pin4_Set);
    GPIO_SetPinValue(GPIO_PortC,GPIO_Pin13_Set);
    
    GPIO_GetPinValue(GPIO_PortA,GPIO_Pin0, &Pina);
    GPIO_GetPinValue(GPIO_PortB,GPIO_Pin4, &Pinb);
    GPIO_GetPinValue(GPIO_PortC,GPIO_Pin13, &Pinc);



    GPIO_SetPinValue(GPIO_PortA,GPIO_Pin0_Reset);
    GPIO_SetPinValue(GPIO_PortB,GPIO_Pin4_Reset);
    GPIO_SetPinValue(GPIO_PortC,GPIO_Pin13_Reset);
    while(1)
    {

    };
}