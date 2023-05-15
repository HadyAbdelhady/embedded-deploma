#include "inc/mcal_exti.h"
#include "Bit_Math.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */

void (*GP_IRQ_CallBack[15])(void);

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

#define AFIO_GPIO_EXTI_Mapping(x) (((S_GPIO_t *)x == GPIOA) ? 0 : ((S_GPIO_t *)x == GPIOB) ? 1 \
                                                              : ((S_GPIO_t *)x == GPIOC)   ? 2 \
                                                              : ((S_GPIO_t *)x == GPIOD)   ? 3 \
                                                                                           : 0)

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

void Enable_NVIC(uint16_t IRQ)
{
    switch (IRQ)
    {
    case 0:
        NVIC_IRQ6_EXTI0_ENABLE;
        break;
    case 1:
        NVIC_IRQ7_EXTI1_ENABLE;
        break;
    case 2:
        NVIC_IRQ8_EXTI2_ENABLE;
        break;
    case 3:
        NVIC_IRQ9_EXTI3_ENABLE;
        break;
    case 4:
        NVIC_IRQ10_EXTI4_ENABLE;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        NVIC_IRQ23_EXTI5_9_ENABLE;
        break;

    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        NVIC_IRQ40_EXTI10_15_ENABLE;
        break;
    }
}

void Disable_NVIC(uint16_t IRQ)
{
    switch (IRQ)
    {
    case 0:
        NVIC_IRQ6_EXTI0_DISABLE;
        break;
    case 1:
        NVIC_IRQ7_EXTI1_DISABLE;
        break;
    case 2:
        NVIC_IRQ8_EXTI2_DISABLE;
        break;
    case 3:
        NVIC_IRQ9_EXTI3_DISABLE;
        break;
    case 4:
        NVIC_IRQ10_EXTI4_DISABLE;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        NVIC_IRQ23_EXTI5_9_DISABLE;
        break;

    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        NVIC_IRQ40_EXTI10_15_DISABLE;
        break;
    }
}
void Update_EXTI(EXTI_PinConfig_t *EXTI_Config)
{
    // 1- Configure GPIO to be AF Input -> Floating INPUT
    MCAL_GPIO_SET_Pin((S_GPIO_t *)(AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)), EXTI_Config->EXTI_PIN.GPIO_PIN, GPIO_Mode_Input_FLO, GPIO_INPUT_MODE);

    uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_PIN.ETI_InputLineNumber / 4;

    uint8_t AFIO_EXTICR_Postion = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber % 4) * 4;

    // 2- Update AFIO pins

    // clear the four bit
    AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_Postion);
    // set the bit in the wanted position
    AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)) << AFIO_EXTICR_Postion);

    // 3- rising edge or falling or both

    CLR_BIT(EXTI->EXTI_FTSR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
    CLR_BIT(EXTI->EXTI_RTSR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

    if (EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
    {
        SET_BIT(EXTI->EXTI_RTSR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
    }
    else if (EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
    {
        SET_BIT(EXTI->EXTI_FTSR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
    }
    else if (EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling)
    {
        SET_BIT(EXTI->EXTI_RTSR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
        SET_BIT(EXTI->EXTI_FTSR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
    }

    // 4- Update IRQ Handling CALLBACK

    GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

    // 5 enable NVIC

    if (EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
    {
        SET_BIT(EXTI->EXTI_IMR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
        Enable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
    }
    else
    {
        CLR_BIT(EXTI->EXTI_IMR, EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
        Disable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
    }
}
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Pin, EXTI_GPIO_Mapping_t Pin_Config, uint8_t trigger, uint8_t IQR_Enabled, void (*F_Callback)(void))
{
    EXTI_Pin->EXTI_PIN = EXTI_P(9, GPIOB);
    EXTI_Pin->Trigger_Case = trigger;
    EXTI_Pin->IRQ_EN = IQR_Enabled;
    EXTI_Pin->P_IRQ_CallBack = F_Callback;
    Update_EXTI(EXTI_Pin);
}
void MCAL_EXTI_GPIO_DeInit(void)
{

    EXTI->EXTI_IMR = 0x00000000;
    EXTI->EXTI_EMR = 0x00000000;
    EXTI->EXTI_RTSR = 0x00000000;
    EXTI->EXTI_FTSR = 0x00000000;
    EXTI->EXTI_SWIER = 0x00000000;
    // rc_w1  cleared by writing a ‘1’ into the PR
    EXTI->EXTI_PR = 0xFFFFFFFF;
    NVIC_IRQ6_EXTI0_DISABLE;
    NVIC_IRQ7_EXTI1_DISABLE;
    NVIC_IRQ8_EXTI2_DISABLE;
    NVIC_IRQ9_EXTI3_DISABLE;
    NVIC_IRQ10_EXTI4_DISABLE;
    NVIC_IRQ23_EXTI5_9_DISABLE;
    NVIC_IRQ40_EXTI10_15_DISABLE;
}
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Pin, EXTI_GPIO_Mapping_t Pin_Config, uint8_t trigger, uint8_t IQR_Enabled, void (*F_Callback)(void))
{
    EXTI_Pin->EXTI_PIN = EXTI_P(9, GPIOB);
    EXTI_Pin->Trigger_Case = trigger;
    EXTI_Pin->IRQ_EN = IQR_Enabled;
    EXTI_Pin->P_IRQ_CallBack = F_Callback;
    Update_EXTI(EXTI_Pin);
}
