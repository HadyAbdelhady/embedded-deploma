#include "Stm32f103x6.h"
#include "MCAL/mcal_stm32f103X6_gpio.h"
#include "MCAL/mcal_stm32f103c6_exti.h"
#include "MCAL/mcal_stm32f103c6_USART.h"
#include "MCAL/mcal_stm32f103c6_RCC.h"

//Global Variable
uint16_t ch ;

void CLOCK_INIT(void)
{
    RCC_GPIOA_CLK_EN;
    RCC_GPIOB_CLK_EN;
    RCC_AFIO_CLK_EN;
}

int main(void)
{
	USART_Config USARTCFG ;
	// clock_init();
	USARTCFG.BaudRate = USART_BaudRate_115200;
	USARTCFG.FlowControl = USART_FlowControl_NONE;
	USARTCFG.IRQ_Enable = USART_NONE;
	USARTCFG.P_CallBack_Fun = NULL ;
	USARTCFG.Parity = USART_Parity_None;
	USARTCFG.Payload_length = USART_DataLength8B;
	USARTCFG.StopBits = USART_StopBits_1;
	USARTCFG.USART_Mode = USART_TX_RX;
	USART_init(USART1 , &USARTCFG);
	USART_SetPins(USART1);
	while (1)
	{
		USART_Send(USART1  , &ch , Enable );
		USART_Recieve(USART1, &ch , Enable );
	}
}