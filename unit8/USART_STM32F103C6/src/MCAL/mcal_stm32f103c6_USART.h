

#ifndef INCLUDE_STM32_F103C6_DRIVERS_USART_H_
#define INCLUDE_STM32_F103C6_DRIVERS_USART_H_
//-----------------------------
//Includes
//-----------------------------
#include "stm32f103_X6.h"
#include "MCAL/mcal_stm32f103X6_gpio.h"


enum Polling_Mechanism{
	Enable,
	Disable
};

//CONFIGURATION STRUCTURE
typedef struct{
	                                             // This parameter must be set based on @ref USART_Mode_define
	uint8_t USART_Mode;			  			   	 // Specifies the TX/RX Mode.

	                                            // This parameter must be set based on @ref USART_BaudRate_define
	uint32_t BaudRate;						    // Specifies the UART communication BaudRate

	                                                 //  This parameter must be set based on @ref USART_StopBits_define
	uint8_t StopBits;								 // Specifies The number of stop bits in the communication frame.

	                                                //  This parameter must be set based on @ref USART_DataLength_define
	uint8_t Payload_length;							 // Specifies The number of data bits in the communication frame.

	                                                // This parameter must be set based on @ref USART_Parity_define
	uint8_t Parity; 								// Determines the Parity type

	                                                // This parameter must be set based on @ref USART_FlowControl_define
	uint8_t FlowControl;  						 //Specifies whether the hardware flow control mode is enabled or disabled

	                                                    // This parameter must be set based on @ref USART_IRQ_Enable_define
	uint8_t IRQ_Enable;  							 // Specifies Interrupt 	Enable / Mask pin

	void(*P_CallBack_Fun)(void);  // The C function() that is called when IRQ is enabled.


}USART_Config;

//===============================================
//      Macros Configuration References
//===============================================

/*
 * @ref USART_Mode_define
 */

#define USART_TX 					(1<<3)			//TE :This bit enables the transmitter.
#define USART_RX					(1<<2)			//RE  = 1
#define USART_TX_RX				(1<<2 | 1<<3)


/*
 * @ref USART_BaudRate_define
 */

#define USART_BaudRate_2400						2400
#define USART_BaudRate_9600						9600
#define USART_BaudRate_19200					19200
#define USART_BaudRate_57600					57600
#define USART_BaudRate_115200					115200
#define USART_BaudRate_230400					230400
#define USART_BaudRate_460800					460800
#define USART_BaudRate_921600					921600
#define USART_BaudRate_2250000					2250000
#define USART_BaudRate_4500000					4500000

/*
 * @ref USART_DataLength_define
 */
#define USART_DataLength8B						(0)
#define USART_DataLength9B						(1<<12)

/*
 * @ref USART_Parity_define
 */
#define USART_Parity_None 						(0)
#define USART_Parity_Even 						(1<<10)
#define USART_Parity_Odd 						(1<<10 | 1<<9)

/*
 *  @ref USART_StopBits_define
 */
/*
 * These bits are used for programming the stop bits.
	00: 1 Stop bit
	01: 0.5 Stop bit
	10: 2 Stop bits
	11: 1.5 Stop bit
 */
#define USART_StopBits_1						(0)
#define USART_StopBits_half						(1<<12)
#define USART_StopBits_2						(2<<12)
#define USART_StopBits_1_half					(3<<12)

/*
 * @ref USART_FlowControl_define
 */
#define USART_FlowControl_NONE					(0)
#define USART_FlowControl_CTS					(1<<9)
#define USART_FlowControl_RTS					(1<<8)
#define USART_FlowControl_CTS_RTS				    (1<<8 | 1<<9)


/*
 * @ref USART_IRQ_Enable_define
 */
#define USART_NONE								(0)
#define USART_RXNEIE							(1<<5)//received data is ready to read
#define USART_TXEIE								(1<<7)//Transmit data register is empty
#define USART_TXEIE_RXNEIE						(1<<5 | 1<<7)
#define USART_TCIE								(1<<6)//transmission complete
#define USART_PEIE								(1<<8)//parity error

/*
 * Baud Rate Calculation
 */
#define USARTDIV(FCLK, BaudRate)				    (FCLK / (16*BaudRate))
#define DIV_Mantissa(FCLK, BaudRate)				(USARTDIV(FCLK,BaudRate)) //Integer Part

#define USARTDIV_Mul100(FCLK, BaudRate)				((FCLK*25) / (4*BaudRate))
#define Mantissa_Mul100(FCLK, BaudRate)				( DIV_Mantissa(FCLK, BaudRate) *100)
#define DIV_Fraction(FCLK, BaudRate)				(((USARTDIV_Mul100(FCLK, BaudRate) - Mantissa_Mul100(FCLK, BaudRate)) *16 ) /100)

#define USART_BRR(FCLK,BaudRate)					( (DIV_Mantissa(FCLK, BaudRate) << 4) | (DIV_Fraction(FCLK, BaudRate) &0xF))
/*
* ===============================================
*      APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/
void USART_init(S_USART_t* USARTX , USART_Config* USART_Config);
void USART_DeInit(S_USART_t* USARTX );

void USART_SetPins(S_USART_t* USARTX );

void USART_Send(S_USART_t* USARTX  , uint16_t *pTxBuffer , enum Polling_Mechanism PollingEn );
void USART_Recieve(S_USART_t* USARTX, uint16_t *pTxBuffer , enum Polling_Mechanism PollingEn );

void USART_Wait_TC(S_USART_t* USARTX);

#endif /* INC_USART_H_ */






