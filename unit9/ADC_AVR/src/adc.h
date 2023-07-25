
#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>


//USER TYPE DEFINITIONs
//-----------------------------
typedef struct{

	uint8_t ADC_Mode;// specifies ADC Mode
	// This parameter must be set based on @ref ADC_MODE_DEFINE
		
	uint8_t ADC_Volt_Ref;// specifies ADC Voltage Referrnce 
	// This parameter must be set based on @ref ADC_VOLT_REF_DEFINE
	
	uint8_t ADC_Res_presentation;// specifies ADC Output result presentation(right adjusted or left adjusted)
	// This parameter must be set based on @ref ADC_RES_PRESENTATION_DEFINE
	
	uint8_t ADC_Prescaler;//  Selects the division factor between the XTAL frequency and the input clock to ADC
	// This parameter must be set based on @ref ADC_PRESCALER_DEFINE
	
	uint8_t ADC_IRQ_Enable;// Enable or Disable IRQ
	// This parameter must be set based on @ref ADC_IRQ_ENABLE_DEFINE
	
	void (*P_CallBack)(void);//set the C Function which will be called once IRQ Happens
	}ADC_Config_t;
	

//Macros

//@ref ADC_MODE_DEFINE
#define ADC_MODE_SINGLE_CONVERSION							  (uint8_t)(0)
#define ADC_MODE_FREE_RUNNING								  (uint8_t)(1<<ADCSRA)

//@ref ADC_VOLT_REF_DEFINE
#define ADC_VOLT_REF_AREF									( 0<<7 | 0<<6)
#define ADC_VOLT_REF_AVCC									( 0<<7 | 1<<6)
#define ADC_VOLT_REF_INTERNAL								( 1<<7 | 1<<6)

//@ref ADC_RES_PRESENTATION_DEFINE
#define ADC_RES_PRESENTATION_RIGHT_ADJUSTED			       (uint8_t)(0)
#define ADC_RES_PRESENTATION_LEFT_ADJUSTED			       (uint8_t)(1<<5)

//@ref ADC_PRESCALER_DEFINE
#define ADC_PRESCALER_2									(1<<0)
#define ADC_PRESCALER_4									(2<<0)
#define ADC_PRESCALER_8									(3<<0)
#define ADC_PRESCALER_16								(4<<0)
#define ADC_PRESCALER_32								(5<<0)
#define ADC_PRESCALER_64								(6<<0)
#define ADC_PRESCALER_128								(7<<0)

//@ref ADC_IRQ_ENABLE_DEFINE
#define ADC_IRQ_ENABLE_NONE								( 0<<3)
#define ADC_IRQ_ENABLE_ADIE								( 1<<3)

typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}Channel_Select_t;

typedef enum
{
	ENABLE,
	DISABLE
}Polling_Mechanism_t;	
/*
 *============================================
 *============================================
 * APIs Supported by "MCAL ADC DRIVER"
 *============================================
 *============================================
 *
 */
void MCAL_ADC_Init(ADC_Config_t *config);
void MCAL_ADC_DeInit(void);

void MCAL_ADC_Start_Conversion(void);
void MCAL_ADC_Get_Result(Channel_Select_t channel,uint16_t *data,Polling_Mechanism_t polling);

#endif /* ADC_H_ */