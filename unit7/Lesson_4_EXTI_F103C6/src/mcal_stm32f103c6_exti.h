
#ifndef INC_STM32F103X6_EXTI_DRIVER_H_
#define INC_STM32F103X6_EXTI_DRIVER_H_
#include "stm32f103_X6.h"
#include "mcal_stm32f103X6_gpio.h"

typedef struct
{
    uint16_t ETI_InputLineNumber;
    GPIO_Pin_Config_t *GPIO_Port;
    uint16_t GPIO_PIN;
    uint8_t IVT_IRQ_Number;
} EXTI_GPIO_Mapping_t;

typedef struct
{
    EXTI_GPIO_Mapping_t EXTI_PIN; // Specifies the External interrupt  GPIO mapping.
                                  // This parameter must be set based on @ref EXTI_define
    uint8_t Trigger_Case;         // Specifies RISING or Falling or Both trigger .
                                  // This parameter must be set based on @ref EXTI_Trigger_define
    uint8_t IRQ_EN;               // Enable Or Disable the EXTI IRQ (That Will Enable the IRQ MASK in EXTI and Also on the NVIC Interrupt Controller)
                                  // This parameter must be set based on @ref EXTI_IRQ_define
    void (*P_IRQ_CallBack)(void); // Set the C Function() which will be called once the IRQ  Happen

} EXTI_PinConfig_t;

//================================
// Macros Configuration References
//================================
typedef enum
{
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    EXTI5,
    EXTI6,
    EXTI7,
    EXTI8,
    EXTI9,
    EXTI10,
    EXTI11,
    EXTI12,
    EXTI13,
    EXTI14,
    EXTI15,
} EXTI_Line;

// Reference Macros

//@ref EXTI_define

#define EXTI_P(N,Port) (EXTI_GPIO_Mapping_t)  {EXTI##N,Port,GPIO_PIN_##N,EXTI##N##_IRQ}

//@ref EXTI_Trigger_define

typedef enum
{
    EXTI_Trigger_RISING,
    EXTI_Trigger_FALLING,
    EXTI_Trigger_RisingAndFalling
} EXTI_Tigger;

//@ref EXTI_IRQ_define

typedef enum
{
    EXTI_IRQ_Disable,
    EXTI_IRQ_Enable
} EXTI_State;

/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Pin,EXTI_GPIO_Mapping_t Pin_Config,uint8_t trigger,uint8_t IQR_Enabled ,void (*F_Callbacl)(void));
void MCAL_EXTI_GPIO_DeInit(void);
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Pin, EXTI_GPIO_Mapping_t Pin_Config, uint8_t trigger, uint8_t IQR_Enabled, void (*F_Callback)(void));
#endif /* INC_STM32F103X8_EXTI_DRIVER_H_ */