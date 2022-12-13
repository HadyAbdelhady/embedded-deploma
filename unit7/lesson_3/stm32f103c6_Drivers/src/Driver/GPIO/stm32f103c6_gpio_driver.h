#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_
#include"Z:\embeddedDiploma\embedded-deploma\embedded-deploma\unit7\lesson_3\stm32f103c6_Drivers\src\stm32f103c6.h" // Config Structure
typedef struct GPIO_CONFIG
{
    uint16_t GPIO_Pin_Number;  // Specifies the GPIO PIN to be configured
                               // This parameter can Take values @Ref GPIO_PINs_Define
    uint8_t GPIO_Mode;         // Specifies the Operating Mode of the Selected PIN
                               // This parameter can Take values @Ref GPIO_Mode_Define
    uint8_t GPIO_OUTPUT_Speed; // Specifies the Speed of the Selected Pin
                               // This Parameter can be value of @Ref GPIO_SPEED_Define
} GPIO_Pin_Config_t;
// ref GPIO_PIN_State
typedef enum GPIO_PIN_State
{
    GPIO_PIN_Reset,
    GPIO_PIN_Set
} GPIO_PIN_State;
// @ref GPIO_Return LOCK
typedef enum GPIO_LOCK
{
    GPIO_Return_Lock_Disabled,
    GPIO_Return_Lock_Enabled
} GPIO_LOCK;

// @ref GPIO_PINS define
typedef enum GPIO_PINS
{
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_ALL_PIN = 0xFFFF,
};

//@ref GPIO_Mode_Define
typedef enum INPUT_Mode
{
    GPIO_Mode_Input_FLO = 1, // Floating input
    GPIO_Mode_Input_PU,      // Input with pull-up
    GPIO_Mode_Input_PD,      // pull-down
    GPIO_Mode_AF_Input = 8   // Alternate function input
};
#define GPIO_Mode_Analog 0 // Analog mode
typedef enum OUTPUT_Mode
{
    GPIO_Mode_Output_PP = 4, // output push-pull
    GPIO_Mode_Output_OD,     // output Open-drain
    GPIO_Mode_Output_AF_PP,  // Alternate function output Push-pull
    GPIO_Mode_Output_AF_OD   // Alternate function output Open-drain
};
//@Ref GPIO_SPEED_Define
typedef enum GPIO_SPEED
{
    GPIO_SPEED_10MHz = 1, // Output mode, max speed 10 MHz.
    GPIO_SPEED_2Mhz,      // Output mode, max speed 2 MHz.
    GPIO_SPEED_50Mhz      // Output mode, max speed 50 MHz.
};
/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
void MCAL_GPIO_Init(S_GPIO_t *GPIOx, GPIO_Pin_Config_t *P_Config);
void MCAL_GPIO_Reset(S_GPIO_t *GPIOx);
uint8_t MCAL_GPIO_ReadPin(S_GPIO_t *GPIOx, uint16_t Pin_Number);
uint16_t MCAL_GPIO_ReadPORT(S_GPIO_t *GPIOx);
void MCAL_GPIO_WritePin(S_GPIO_t *GPIOx, uint16_t Pin_Number, uint8_t value);
void MCAL_GPIO_WritePort(S_GPIO_t *GPIOx, uint16_t value);
uint8_t MCAL_GPIO_LOCKPin(S_GPIO_t *GPIOx, uint16_t Pin_Number);
void MCAL_GPIO_TogglePin(S_GPIO_t *GPIOx, uint16_t Pin_Number);
#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */