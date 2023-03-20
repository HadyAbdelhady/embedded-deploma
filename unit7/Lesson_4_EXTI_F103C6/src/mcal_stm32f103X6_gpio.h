#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_
#include "stm32f103_X6.h" // Config Structure

typedef struct GPIO_CONFIG
{
    uint16_t GPIO_Pin_Number;  // Specifies the GPIO PIN to be configured
                               // This parameter can Take values @Ref GPIO_PINs_Define
    uint8_t GPIO_Mode;         // Specifies the Operating Mode of the Selected PIN
                               // This parameter can Take values @Ref GPIO_Mode_Define
    uint8_t GPIO_OUTPUT_Speed; // Specifies the Speed of the Selected Pin
                               // This Parameter can be value of @Ref GPIO_SPEED_Define
} GPIO_Pin_Config_t;
// @ref GPIO_PIN_State
typedef enum GPIO_PIN_State
{
    LOW,
    HIGH
} GPIO_PIN_State;
// @ref GPIO_Return LOCK
typedef enum GPIO_LOCK
{
    GPIO_Return_Lock_Disabled,
    GPIO_Return_Lock_Enabled
} GPIO_LOCK;

// @ref GPIO_PINS_define
#define GPIO_PIN_0 ((uint16_t)0x0001)   /* Pin 0 selected    */
#define GPIO_PIN_1 ((uint16_t)0x0002)   /* Pin 1 selected  10  */
#define GPIO_PIN_2 ((uint16_t)0x0004)   /* Pin 2 selected  100  */
#define GPIO_PIN_3 ((uint16_t)0x0008)   /* Pin 3 selected  1000  */
#define GPIO_PIN_4 ((uint16_t)0x0010)   /* Pin 4 selected  10000  */
#define GPIO_PIN_5 ((uint16_t)0x0020)   /* Pin 5 selected    */
#define GPIO_PIN_6 ((uint16_t)0x0040)   /* Pin 6 selected    */
#define GPIO_PIN_7 ((uint16_t)0x0080)   /* Pin 7 selected    */
#define GPIO_PIN_8 ((uint16_t)0x0100)   /* Pin 8 selected    */
#define GPIO_PIN_9 ((uint16_t)0x0200)   /* Pin 9 selected    */
#define GPIO_PIN_10 ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11 ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12 ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13 ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14 ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15 ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All ((uint16_t)0xFFFF) /* All pins selected */

#define GPIO_PIN_MASK 0x0000FFFFu /* PIN mask for assert test */

//@ref GPIO_MODE_define
// 0: Analog mode
// 1: Floating input (reset state)
// 2: Input with pull-up
// 3:  pull-down
// 4: General purpose output push-pull
// 5: General purpose output Open-drain
// 6: Alternate function output Push-pull
// 7: Alternate function output Open-drain
// 8: Alternate function  INPUT
#define GPIO_Mode_Analog 0x00000000u       // Analog mode
#define GPIO_Mode_Input_FLO 0x00000001u    // Floating input
#define GPIO_Mode_Input_PU 0x00000002u     // Input with pull-up
#define GPIO_Mode_Input_PD 0x00000003u     // Input with pull-down
#define GPIO_Mode_Output_PP 0x00000004u    // General purpose output push-pull
#define GPIO_Mode_Output_OD 0x00000005u    // General purpose output Open-drain
#define GPIO_Mode_Output_AF_PP 0x00000006u // Alternate function output Push-pull
#define GPIO_Mode_Output_AF_OD 0x00000007u // Alternate function output Open-drain
#define GPIO_Mode_AF_Input 0x00000008u     // Alternate function INPUT

//@Ref GPIO_SPEED_Define
#define GPIO_INPUT_MODE 0x00000000u  // Input mode ,
#define GPIO_SPEED_10MHz 0x00000001u // Output mode, max speed 10 MHz.
#define GPIO_SPEED_2MHz 0x00000002u  // Output mode, max speed 2 MHz.
#define GPIO_SPEED_50MHz 0x00000003u // Output mode, max speed 50 MHz.

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
void MCAL_GPIO_SET_Pin(S_GPIO_t *GPIOport, uint16_t Pin_number, uint8_t mode, uint8_t speed);

// global variable
GPIO_Pin_Config_t GPIOx;

#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */