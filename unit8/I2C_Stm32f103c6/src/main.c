#include"mcal/inc/mcal_gpio.h"
#include"mcal/inc/mcal_exti.h"
#include"mcal/inc/mcal_SPI.h"
#include"mcal/inc/mcal_USART.h"

uint16_t ch;
#define MCU_Act_As_Master
// #define MCU_Act_As_Slave
void clock_init()
{
	RCC_GPIOA_CLK_EN;  // Enable GPIOA Clock
	RCC_GPIOB_CLK_EN;   //Enable GPIOB Clock
	RCC_AFIO_CLK_EN;
}
void SPI_Interrupt_Call_Back(struct S_IRQ_SRC irq_src)
{
#ifdef MCU_Act_As_Slave
	if(irq_src.RXNE)
	{
		ch=0xf;
		MCAL_SPI_TX_RX(SPI1, &ch, SPI_disable);
		MCAL_USART_Send(USART1, &ch, SPI_enable);
	}
#endif
}
void Uart_CallBack(void)
{

#ifdef MCU_Act_As_Master
	MCAL_USART_Recieve(USART1, &ch, Disable);
	MCAL_USART_Send(USART1, &ch, Enable);
	//Write zero to send data
	//manually reset PA4 to work as slave select and enable the transmission
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, LOW);
	MCAL_SPI_TX_RX(SPI1, &ch, SPI_enable);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,HIGH);
#endif

}

int main(void)
{
	clock_init();
	USART_Config CFG;
	CFG.BaudRate = USART_BaudRate_115200;
	CFG.FlowControl = USART_FlowControl_NONE;
	CFG.IRQ_Enable = USART_RXNEIE;
	CFG.Parity = USART_Parity_None;
	CFG.Payload_length =USART_DataLength8B ;
	CFG.StopBits = USART_StopBits_1;
	CFG.USART_Mode = USART_TX_RX;
	CFG.P_CallBack_Fun = Uart_CallBack;
	MCAL_USART_init(USART1,&CFG);
	MCAL_USART_SetPins(USART1);

	//===============================SPI============================//
	SPI_CFG_t SPICfg;
	SPICfg.CPHA = CPHA_First_edge;
	SPICfg.CPOL = CPOL_HIGH;
	SPICfg.Frame_Format = Frame_Format_MSB;
	SPICfg.DFF = Payload_length_8BIT;
	SPICfg.Prescaler = BR_Prescaler_8;
	SPICfg.Communication_Mode = MODE_2LINES;

#ifdef MCU_Act_As_Master
	SPICfg.Master_Slave = Master;
	SPICfg.SPI_IRQ =  SPI_IRQ_Enable_NONE;
	SPICfg.NSS = NSS_Soft_set;
	SPICfg.P_IRQ_CallBack = NULL;

	//Manually operate PA4 as SS and set idle state to 1
	MCAL_GPIO_SET_Pin(GPIOA,GPIO_PIN_4,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
	//Write one
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,HIGH);
#endif
#ifdef MCU_Act_As_Slave
	SPICfg.Master_Slave = Slave;
	SPICfg.SPI_IRQ  = SPI_IRQ_Enable_RXNEIE;
	SPICfg.NSS = NSS_Hard_Slave;
	SPICfg.P_IRQ_CallBack = SPI_Interrupt_Call_Back;
#endif
	MCAL_SPI_INIT(SPI1, &SPICfg);
	MCAL_SPI_GPIO_SetPins(SPI1);
	while (1)
	{

	}
}