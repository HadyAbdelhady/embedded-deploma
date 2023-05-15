/*
 * SPI.h
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|
#include "stm32f103_X6.h"
#include "MCAL/inc/mcal_gpio.h"
#include "MCAL/inc/mcal_RCC.h"

//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|

//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|
struct S_IRQ_SRC
{
    uint8_t TXE : 1;      // Tx buffer empty interrupt
    uint8_t RXNE : 1;     // Rx buffer not empty interrupt
    uint8_t ERRI : 1;     // Error interrupt
    uint8_t Reserved : 5; // Don't touch
};

//		|-----------------------------------------------|
//		|==============GENERIC FUNCTIONS================|
//		|-----------------------------------------------|

//		|-----------------------------------------------|
//		|======User Type Definitions (structures)=======|
//		|-----------------------------------------------|
typedef struct
{

    uint16_t Master_Slave; // Specifies the SPI operation mode (Master/Slave) @ref MSTR_define

    uint16_t Communication_Mode; // Output enable in bidirectional mode & Bidirectional data mode enable
                              //@ref BIDIOE_BIDIMODE_define
                              // NOTE : This bit is not used in I2S mode.
                              // In master mode, the MOSI pin is used while the MISO pin is used in slave mode

    uint16_t Frame_Format; // Specifies (LSB/MSB) @ref LSBFIRST_define

    uint16_t DFF; // Specifies Data size transmitted @ref Payload_length

    uint16_t CPOL; // Specifies Polarity of the SPI clock @ref CPOL_define

    uint16_t CPHA; // Specifies Phase of the SPI clock @ref CPHA_define

    uint16_t NSS; // Specifies whether the NSS signal is managed by
                  // hardware (NSS pin) or by software using the SSI bit enable
                  //@ref NSS_define

    uint16_t Prescaler; // Specifies the baud rate prescalar value which will be used to configure
                 // the transmit and receive SCK clock.
                 // This parameter can be a value of @ref BR_define
                 // NOTE : the communication clock is derived from the master clock
                 // the slave clock does not need to be set
                 // take care you have to configure RCC to enter the correct clock to APB2 >>> to SPI1
                 //    or APB1 >>> to SPI2

    uint16_t SPI_IRQ; // Enable the interrupt of the SPI @ref SPI_IRQ_define

    void (*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src); // Set the function() which will be called once the IRQ happen
} SPI_CFG_t;

//		|------------------------------------------------------------------|
//		|=================Macros Configuration References==================|
//		|------------------------------------------------------------------|

//***********************@ref MSTR_define***********************

#define Slave 0         // Slave configuration
#define Master (1 << 2) // Master configuration

//***********************@ref BIDIOE_BIDIMODE_define***********************

#define MODE_2LINES 0                               // 2-line unidirectional data mode selected & Output disabled (receive-only mode)
#define MODE_2LINES_RXONLY (1 << 10)                // Output disabled (Receive-only mode) & Output disabled (receive-only mode)
#define MODE_1LINE_ReceiveONLY (1 << 15)            // 1-line bidirectional data mode selected
#define MODE_1LINE_transmitONLY (1 << 15 | 1 << 14) // Output enabled (transmit-only mode) & 1-line bidirectional data mode selected

//***********************@ref LSBFIRST_define***********************

#define Frame_Format_MSB 0        // MSB transmitted first
#define Frame_Format_LSB (1 << 7) // LSB transmitted first

//***********************@ref Payload_length ***********************

#define Payload_length_8BIT 0          // 8-bit data frame format is selected for transmission/reception
#define Payload_length_16BIT (1 << 11) // 16-bit data frame format is selected for transmission/reception

//***********************@ref CPOL_define***********************

#define CPOL_LOW 0         // CK to 0 when idle
#define CPOL_HIGH (1 << 1) // CK to 1 when idle

//*********************** @ref CPHA_define***********************

#define CPHA_First_edge 0         // The first clock transition is the first data capture edge
#define CPHA_Second_edge (1 << 0) // The second clock transition is the first data capture edge

//***********************@ref Baud_Rate_Prescalar_define***********************

#define BR_Prescaler_2 0
#define BR_Prescaler_4 (0b001 << 3)
#define BR_Prescaler_8 (0b010 << 3)
#define BR_Prescaler_16 (0b011 << 3)
#define BR_Prescaler_32 (0b100 << 3)
#define BR_Prescaler_64 (0b101 << 3)
#define BR_Prescaler_128 (0b110 << 3)
#define BR_Prescaler_256 (0b111 << 3)

//***********************@ref NSS_define***********************

// Hardware
#define NSS_Hard_Slave 0                          // Hardware NSS management (SSM = 0)
#define NSS_Hard_Master_SS_output_enable (1 << 2) // NSS output enabled (SSM = 0, SSOE = 1)
#define NSS_Hard_Master_SS_output_disable 0       // NSS output disabled (SSM = 0, SSOE = 0)

// Software
#define NSS_Soft_reset (1 << 9)        // Software slave management disabled
#define NSS_Soft_set (1 << 9 | 1 << 8) // Software slave management enabled &

//***********************@ref SPI_IRQ_define***********************

#define SPI_IRQ_Enable_NONE (uint32_t)(0)        // No interrupt enabled
#define SPI_IRQ_Enable_TXEIE (uint32_t)(1 << 7)  // TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
#define SPI_IRQ_Enable_RXNEIE (uint32_t)(1 << 6) // RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set.
#define SPI_IRQ_Enable_ERRIE (uint32_t)(1 << 5)  // Error interrupt is enabled

//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|

enum SPI_Polling_mechanism
{
    SPI_enable,
    SPI_disable
};

/**================================================================
 * @Fn - MCAL_SPI_INIT
 * @brief - Initialize SPI
 * @param[in] - SPI number (1 , 2 ) & registers
 * @param[in] - SPI pin configurations
 */
void MCAL_SPI_INIT(S_SPI_t *SPIx, SPI_CFG_t *SPI_Config);

/**================================================================
 * @Fn - MCAL_SPI_RESET
 * @brief - Reset SPI
 * @param[in] - SPI number (1 , 2 ) & registers
 */
void MCAL_SPI_RESET(S_SPI_t *SPIx);

/**================================================================
 * @Fn - MCAL_SPI_GPIO_SetPins
 * @brief - Set the GPIO pins according to the chosen SPI
 * @param[in] - SPI number (1 , 2 ) & registers
 * @param[in] - SPI pin configurations
 */
void MCAL_SPI_GPIO_SetPins(S_SPI_t *SPIx);

/**================================================================
 * @Fn - MCAL_SPI_SendData
 * @brief - Send data from the microcontroller to another peripheral cross SPI
 * @param[in] - SPI number (1 , 2 ) & registers
 * @param[in] - Pointer to the buffer used to store data
 * @param[in] - Check if the polling mechanism enabled or not
 * @param[in] - SPI pin configurations
 */
void MCAL_SPI_Send(S_SPI_t *SPIx, uint16_t *PTxBuffer, enum SPI_Polling_mechanism PollingEn);

/**================================================================
 * @Fn - MCAL_SPI_ReceiveData
 * @brief - Receive data from a particular peripheral to microcontroller cross SPI
 * @param[in] - SPI number (1 , 2 ) & registers
 * @param[in] - Pointer to the buffer used to store data
 * @param[in] - Check if the polling mechanism enabled or not
 * @param[in] - SPI pin configurations
 */
void MCAL_SPI_Receive(S_SPI_t *SPIx, uint16_t *PTxBuffer, enum SPI_Polling_mechanism PollingEn);

/**================================================================
 * @Fn - MCAL_SPI_ReceiveData
 * @brief - Receive data from a particular peripheral to microcontroller cross SPI
 * @param[in] - SPI number (1 , 2 ) & registers
 * @param[in] - Pointer to the buffer used to store data
 * @param[in] - Check if the polling mechanism enabled or not
 * @Note : used in full duplex to send and receive at the same time
 */
void MCAL_SPI_TX_RX(S_SPI_t *SPIx, uint16_t *PTxBuffer, enum SPI_Polling_mechanism PollingEn);

//,SPI_CFG_t * SPI_Config
#endif /* INC_SPI_H_ */