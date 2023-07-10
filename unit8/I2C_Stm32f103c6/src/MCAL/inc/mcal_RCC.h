/*
 * Stm32_f103c6_Drivers_RCC.h
 *      Author: Hadi
 */

#ifndef INCLUDE_STM32_F103C6_DRIVERS_RCC_H_
#define INCLUDE_STM32_F103C6_DRIVERS_RCC_H_
//-----------------------------
//Includes
//-----------------------------
#include "stm32f103_X6.h"
//-----------------------------
#define HSI 		(uint32_t)8000000   //8 MEGA HZ
#define HSE 		(uint32_t)16000000  //8 MEGA HZ
/*
* ===============================================
*      APIs Supported by "MCAL RCC DRIVER"
* ===============================================
*/
uint32_t  MCAL_RCC_get_SYSCLK_Freq(void);

uint32_t  MCAL_RCC_get_PCKL1_Freq(void);
uint32_t  MCAL_RCC_get_PCKL2_Freq(void);
uint32_t  MCAL_RCC_get_HCKL_Freq(void);

#endif /* INC_RCC_H_ */






