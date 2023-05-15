#include "MCAL/inc/mcal_SPI.h"

//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|

#define SPI_SR_TXE ((uint8_t)0x02)  //!< Transmit buffer empty
#define SPI_SR_RXNE ((uint8_t)0x01) //!< Receive buffer not empty

//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|

SPI_CFG_t *GP_SPI_CFG[3] = {NULL, NULL, NULL};

enum SPI_INDEX
{
    SPI1_INDEX,
    SPI2_INDEX,
    SPI3_INDEX
};

//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|

void MCAL_SPI_INIT(S_SPI_t *SPIx, SPI_CFG_t *SPI_Config)
{
    // safety for registers
    uint16_t tmpreg_CR1 = 0;
    uint16_t tmpreg_CR2 = 0;

    // SPI CLOCK ENABLE
    if (SPIx == SPI1)
    {
        GP_SPI_CFG[SPI1_INDEX] = SPI_Config;
        RCC_SPI1_CLK_EN;
    }
    else if (SPIx == SPI2)
    {
        GP_SPI_CFG[SPI2_INDEX] = SPI_Config;
        RCC_SPI2_CLK_EN;
    }
    else if (SPIx == SPI3)
    {
        GP_SPI_CFG[SPI3_INDEX] = SPI_Config;
        RCC_SPI3_CLK_EN;
    }
    // Enable SPI CR1 : BIT 6   SPE : enable
    tmpreg_CR1 = 1 << 6;
    // Slave or Master
    tmpreg_CR1 |= SPI_Config->Master_Slave;
    // SPI communication mode
    tmpreg_CR1 |= SPI_Config->Communication_Mode;
    // SPI frame format
    tmpreg_CR1 |= SPI_Config->Frame_Format;
    // Data size
    tmpreg_CR1 |= SPI_Config->DFF;
    // Clock polarity
    tmpreg_CR1 |= SPI_Config->CPOL;
    // Clock phase
    tmpreg_CR1 |= SPI_Config->CPHA;
    // NSS
    if (SPI_Config->NSS == NSS_Hard_Master_SS_output_enable)
        tmpreg_CR2 |= SPI_Config->NSS;
    
    else if (SPI_Config->NSS == NSS_Hard_Master_SS_output_disable)
        tmpreg_CR2 &= SPI_Config->NSS;
    else
        tmpreg_CR1 |= SPI_Config->NSS;
    
    // Baud rate prescaler
    tmpreg_CR1 |= SPI_Config->Prescaler;
    // Interrupt enable
    if (SPI_Config->SPI_IRQ != SPI_IRQ_Enable_NONE)
    {
        tmpreg_CR2 |= SPI_Config->SPI_IRQ;

        if (SPIx == SPI1)
        {
            NVIC_IRQ35_SPI1_ENABLE;
        }
        else if (SPIx == SPI2)
        {
            NVIC_IRQ36_SPI2_ENABLE;
        }
    }
    SPIx->CR1 = tmpreg_CR1;
    SPIx->CR2 = tmpreg_CR2;
}

void MCAL_SPI_RESET(S_SPI_t *SPIx)
{
    if (SPIx == SPI1)
    {
        NVIC_IRQ35_SPI1_DISABLE;
        RCC_SPI1_RESET;
    }
    else if (SPIx == SPI2)
    {
        NVIC_IRQ36_SPI2_DISABLE;
        RCC_SPI2_RESET;
    }
}

void MCAL_SPI_GPIO_SetPins(S_SPI_t *SPIx)
{
    // GPIO_Pin_Config_t SPI_PinCFG;
    if (SPIx == SPI1)
    {
        // PA4 : SPI1_NSS
        // PA5 : SPI1_SCK
        // PA6 : SPI1_MISO
        // PA7 : SPI1_MOSI
        if (GP_SPI_CFG[SPI1_INDEX]->Master_Slave == Master)
        {

            // PA4 : SPI1_NSS
            switch (GP_SPI_CFG[SPI1_INDEX]->NSS)
            {
            case ((uint16_t)NSS_Hard_Master_SS_output_disable):
                MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_4, GPIO_Mode_Input_FLO, GPIO_SPEED_10MHz);
                break;

            case NSS_Hard_Master_SS_output_enable:
                // Hardware master / slave NSS output enabled Alternative function push-pull
                MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_4, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
                break;
            default:
                break;
            }

            // PA5 : SPI1_SCK
            // Master Alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_5, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
            // PA6 : SPI1_MISO
            // full duplex / master input floating
            MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_6, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);

            // PA7 : SPI1_MOSI
            // full duplex / master alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_7, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
        }
        else if (GP_SPI_CFG[SPI1_INDEX]->Master_Slave == Slave)
        {
            // PA4 : SPI1_NSS
            if (GP_SPI_CFG[SPI1_INDEX]->NSS == NSS_Hard_Slave)
            {
                // Hardware master / slave Input floating
                MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_4, GPIO_Mode_Input_FLO, GPIO_SPEED_10MHz);
            }
            // PA5 : SPI1_SCK
            // Slave input floating
            MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_5, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);
            // PA6 : SPI1_MISO
            // full duplex / master input floating
            MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_6, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
            // PA7 : SPI1_MOSI
            // full duplex / master alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_7, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);
        }
    }
    else if (SPIx == SPI2)
    {
        // PB12 : SPI2_NSS
        // PB13 : SPI2_SCK
        // PB14 : SPI2_MISO
        // PB15 : SPI2_MOSI
        if (GP_SPI_CFG[SPI2_INDEX]->Master_Slave == Master)
        {
            // PB12 : SPI2_NSS
            switch (GP_SPI_CFG[SPI2_INDEX]->NSS)
            {
            case (uint16_t)NSS_Hard_Master_SS_output_disable:
                // Hardware master / slave Input floating
                MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_Mode_Input_FLO, GPIO_SPEED_10MHz);
                break;
            case NSS_Hard_Master_SS_output_enable:
                // Hardware master / slave NSS output enabled Alternative function push-pull
                MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
                break;
            }
            // PB13 : SPI2_SCK
            // Master Alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_13, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);

            // PB14 : SPI1_MISO
            // full duplex / master input floating
            MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_14, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);

            // PB15 : SPI1_MOSI
            // full duplex / master alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_15, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
        }
        else if (GP_SPI_CFG[SPI2_INDEX]->Master_Slave == Slave)
        {
            // PB12 : SPI2_NSS
            if (GP_SPI_CFG[SPI2_INDEX]->NSS == NSS_Hard_Slave)
            {
                // Hardware master / slave Input floating
                MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_Mode_Input_FLO, GPIO_SPEED_10MHz);
            }
            // PB13 : SPI2_SCK
            // Slave input floating
            MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_13, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);
            // PB14 : SPI2_MISO
            // full duplex / master input floating
            MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_14, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
            // PB15 : SPI2_MOSI
            // full duplex / master alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_15, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);
        }
    }
    else if (SPIx == SPI3) //NSS pin is not used in SPI3.
    {
        // PC10 : SPI3_SCK
        // PC11 : SPI3_MISO
        // PC12 : SPI3_MOSI
        if (GP_SPI_CFG[SPI3_INDEX]->Master_Slave == Master)
        {
            // PC10 : SPI3_SCK
            // Master Alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOC, GPIO_PIN_10, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);

            // PC11 : SPI3_MISO
            // full duplex / master input floating
            MCAL_GPIO_SET_Pin(GPIOC, GPIO_PIN_11, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);

            // PC12 : SPI3_MOSI
            // full duplex / master alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOC, GPIO_PIN_12, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);
        }
        else if (GP_SPI_CFG[SPI3_INDEX]->Master_Slave == Slave)
        {
            // PC10 : SPI3_SCK
            // Slave input floating
            MCAL_GPIO_SET_Pin(GPIOC, GPIO_PIN_10, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);

            // PC11 : SPI3_MISO
            // full duplex / master input floating
            MCAL_GPIO_SET_Pin(GPIOC, GPIO_PIN_11, GPIO_Mode_Output_AF_PP, GPIO_SPEED_10MHz);

            // PC12 : SPI3_MOSI
            // full duplex / master alternative function push-pull
            MCAL_GPIO_SET_Pin(GPIOC, GPIO_PIN_12, GPIO_Mode_AF_Input, GPIO_SPEED_10MHz);
        }
    }
}

void MCAL_SPI_Send(S_SPI_t *SPIx, uint16_t *PTxBuffer, enum SPI_Polling_mechanism PollingEn)
{
    if (PollingEn == SPI_enable)
        while (!(SPIx->SR & SPI_SR_TXE))
            ;
    SPIx->DR = *PTxBuffer;
}

void MCAL_SPI_Receive(S_SPI_t *SPIx, uint16_t *PTxBuffer, enum SPI_Polling_mechanism PollingEn)
{
    if (PollingEn == SPI_enable)
        while (!(SPIx->SR & SPI_SR_RXNE))
            ;
    *PTxBuffer = SPIx->DR;
}
void MCAL_SPI_TX_RX(S_SPI_t *SPIx, uint16_t *PTxBuffer, enum SPI_Polling_mechanism PollingEn)
{
    if (PollingEn == SPI_enable) {
        // while(SPIx->SR != 2);
        SPIx->DR = *PTxBuffer;
        while (!(SPIx->SR & SPI_SR_RXNE));
        *PTxBuffer = SPIx->DR;
    } else {
        // enable interrupts for RXNE and TXE flags
        SPIx->CR2 |= SPI_IRQ_Enable_RXNEIE | SPI_IRQ_Enable_TXEIE;
    }
}
// SPIx->SR & SPI_SR_TXE
