#include "stm32f103c6_gpio_driver.h"
uint8_t Get_CRLH_position(uint32_t pin)
{
    switch (pin)
    {
    case GPIO_PIN_0:
        return 0;
        break;
    case GPIO_PIN_1:
        return 4;
        break;
    case GPIO_PIN_2:
        return 8;
        break;
    case GPIO_PIN_3:
        return 12;
        break;
    case GPIO_PIN_4:
        return 16;
        break;
    case GPIO_PIN_5:
        return 20;
        break;
    case GPIO_PIN_6:
        return 24;
        break;
    case GPIO_PIN_7:
        return 28;
        break;
    case GPIO_PIN_8:
        return 0;
        break;
    case GPIO_PIN_9:
        return 4;
        break;
    case GPIO_PIN_10:
        return 8;
        break;
    case GPIO_PIN_11:
        return 12;
        break;
    case GPIO_PIN_12:
        return 16;
        break;
    case GPIO_PIN_13:
        return 20;
        break;
    case GPIO_PIN_14:
        return 24;
        break;
    case GPIO_PIN_15:
        return 28;
        break;

    default:
        break;
    }
}

/*************************************************************
 *   @Fun - MCAL_GPIO_Init
 *   @param [in]- GPIOx where x is the port A,B,C,D
 *   @param [in]- PinConfig pin configured in GPIO_cfg.c
 *   @brief - initlize pin Mode , Speed
 *   @retval - none
 *   @Note - Port c and d are partial in stm32f10x8
 */
void MCAL_GPIO_Init(S_GPIO_t *GPIOx, GPIO_Pin_Config_t *P_Config)
{
    volatile uint32_t *config = NULL;
    uint8_t PIN_Cnfg = 0;

    // Port x configuration bits (y= 0 .. 7) and CRL , 8. . .15 CRH
    config = (P_Config->GPIO_Pin_Number <= 7) ? &GPIOx->CRL : &GPIOx->CRH;
    // clear the current config
    (*config) &= ~(0xf << Get_CRLH_position(P_Config->GPIO_Pin_Number));
    // if mode is output
    if (P_Config->GPIO_Mode == GPIO_Mode_Output_AF_OD || P_Config->GPIO_Mode == GPIO_Mode_Output_AF_PP || P_Config->GPIO_Mode == GPIO_Mode_Output_OD || P_Config->GPIO_Mode == GPIO_Mode_Output_PP)

        PIN_Cnfg = (((P_Config->GPIO_Mode << 2) | P_Config->GPIO_OUTPUT_Speed) & 0x0f);

    // if mode is input
    else
    {
        if (P_Config->GPIO_Mode == GPIO_Mode_Analog || P_Config->GPIO_Mode == GPIO_Mode_Input_FLO || P_Config->GPIO_Mode == GPIO_Mode_AF_Input)

            PIN_Cnfg = (((P_Config->GPIO_Mode << 2) | 0x00) & 0x0f);

        else
        {
            PIN_Cnfg = (((GPIO_Mode_Input_PU << 2) | 0x0) & 0xf);

            if (P_Config->GPIO_Mode == GPIO_Mode_Input_PU)
                GPIOx->ODR |= P_Config->GPIO_Pin_Number;

            else

                GPIOx->ODR &= ~(P_Config->GPIO_Pin_Number);
        }
    }
    *(config) = PIN_Cnfg << Get_CRLH_position(P_Config->GPIO_Pin_Number);
}

/*************************************************************
 *   @Fun - MCAL_GPIO_DeInit
 *   @brief - Deinit GPIO port and return it to reset state
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @retval -none
 *   @Note -
 */
void MCAL_GPIO_Reset(S_GPIO_t *GPIOx)
{

    /*
      IOPARST: I/O port A reset
      Set and cleared by software.
      0: No effect
      1: Reset I/O port A */
    if (GPIOx == GPIOA)
    {
        RCC->RCC_APB2ENR |= (1 << 2);
        RCC->RCC_APB2ENR &= ~(1 << 2);
    }
    else if (GPIOx == GPIOB)
    {
        RCC->RCC_APB2ENR |= (1 << 3);
        RCC->RCC_APB2ENR &= ~(1 < 3);
    }
    else if (GPIOx == GPIOC)
    {
        RCC->RCC_APB2ENR |= (1 << 4);
        RCC->RCC_APB2ENR &= ~(1 << 4);
    }
    else if (GPIOx == GPIOD)
    {
        RCC->RCC_APB2ENR |= (1 << 5);
        RCC->RCC_APB2ENR &= ~(1 << 5);
    }
    else if (GPIOx == GPIOE)
    {
        RCC->RCC_APB2ENR |= (1 << 6);
        RCC->RCC_APB2ENR &= ~(1 << 6);
    }
}

/**================================================================
 * @Fn- MCAL_GPIO_WRITE_PIN
 * @brief - Write the GPIOx PINy according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - pin_number: GPIOx PIN Number
 * @param [in] - value: The desired value to write
 * @retval - None
 * Note-
 */
void MCAL_GPIO_WritePin(S_GPIO_t *GPIOx, uint16_t Pin_Number, uint8_t value)
{
    if (value == GPIO_PIN_Set)
        GPIOx->ODR |= Pin_Number;
    else
        GPIOx->ODR &= ~(Pin_Number);
}

/**================================================================
 * @Fn- MCAL_GPIO_WritePort
 * @brief - Write the GPIOx according to specified parameters in Pin_config
 * @param [in] - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in] - value: The desired value to write
 * @retval -
 * Note-
 */
void MCAL_GPIO_WritePort(S_GPIO_t *GPIOx, uint16_t value)
{
    GPIOx->ODR = (uint16_t)value;
}

/**================================================================
 * @Fn              - MCAL_GPIO_ReadPin
 * @brief           - Read the GPIOx PINy according to specified parameters in Pin_config
 * @param [in]      - GPIOx: where x can be (A...E Depending on device used) to select the GPIO Peripheral
 * @param [in]      - Pin_No: GPIOx PIN Number
 * @retval          - uint8_t -> @ref GPIO_PIN_State
 * Note             - none
 */
uint8_t MCAL_GPIO_ReadPin(S_GPIO_t *GPIOx, uint16_t Pin_Number)
{
    uint8_t tmp;
    if ((GPIOx->IDR & Pin_Number) == 0)
    {
        tmp = GPIO_PIN_Reset;
    }
    else
    {
        tmp = GPIO_PIN_Set;
    }
    return tmp;
}

/*************************************************************
 *   @**
 *   @fun - MCAL_GPIO_ReadPort
 *   @brief - Read a port value
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @retval - uint16_t value
 *   @Note -
 */

uint16_t MCAL_GPIO_ReadPORT(S_GPIO_t *GPIOx)
{
    uint16_t tmp;
    tmp = (uint16_t)GPIOx->IDR;
    return tmp;
}

/*************************************************************
 *   @Fun -MCAL_GPIO_TogglePin
 *   @brief - toggle Pin
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - PinNum at @ref GPIO_PIN_DEFINE
 *   @retval - none
 *   @Note -
 */
void MCAL_GPIO_TogglePin(S_GPIO_t *GPIOx, uint16_t Pin_Number)
{
    GPIOx->ODR ^= Pin_Number;
}

/*************************************************************
 *   @Fun -  MCAL_GPIO_LockPin
 *   @brief - lock a pin from chaninging until reset
 *   @param [in] - GPIOx where x is the port A,B,C,D
 *   @param [in] - PinNum at @ref GPIO_PIN_DEFINE
 *   @retval - sucess or not
 *   @Note -
 */
uint8_t MCAL_GPIO_LOCKPin(S_GPIO_t *GPIOx, uint16_t Pin_Number)
{
    /*  LCKK[16]: Lock key
            This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
            0: Port configuration lock key not active
            1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
            LOCK key writing sequence:
            Write 1
            Write 0
            Write 1
            Read 0
            Read 1 (this read is optional but confirms that the lock is active)
         */
    uint32_t temp = (1 << 16);

    /* LOCK pin */
    temp |= Pin_Number;
    /*Apply sequence on LCKK[16]: Lock key */
    /* Write 1*/
    GPIOx->LCKR |= temp;
    /* Write 0*/
    GPIOx->LCKR = Pin_Number;
    /* Write 1*/
    GPIOx->LCKR |= temp;
    /*Read 0*/
    temp = GPIOx->LCKR;

    /* Read 1 (this read is optional but confirms that the lock is active)*/
    if ((uint32_t)((GPIOx->LCKR) & (1 << 16)))
        return 1;
    else
        return 0;
}
