
#include "adc.h"
#include "Bit_Math.h"

ADC_Config_t G_ADC_Config;

void MCAL_ADC_Init(ADC_Config_t *config){
	G_ADC_Config = *config;
	
	
	ADCSRA |= config->ADC_Mode;
	
	ADCSRA |= config->ADC_IRQ_Enable;

	ADMUX |= config->ADC_Res_presentation;
	
	ADMUX |= config->ADC_Prescaler;
	
	ADMUX |= config->ADC_Volt_Ref;
	
	if(config->ADC_IRQ_Enable == ADC_IRQ_ENABLE_ADIE){
			sei();
	}
	
	SET_BIT(ADCSRA,7);

	if(config->ADC_Mode == ADC_MODE_FREE_RUNNING){
		SET_BIT(ADCSRA,6);
	}
}
void MCAL_ADC_DeInit(void){
	ADMUX = 0x0;
	ADCSRA =0x0;
	SFIOR &= ~(1<<5 | 1<<6 | 1<<7);
}

void MCAL_ADC_Start_Conversion(void){
	if(G_ADC_Config.ADC_Mode == ADC_MODE_SINGLE_CONVERSION){
		SET_BIT(ADCSRA,6);
	}
}
void MCAL_ADC_Get_Result(Channel_Select_t channel,uint16_t *data,Polling_Mechanism_t polling){
	ADMUX &= ~(0x1F);
	ADMUX |= (uint8_t)channel;
	CLR_BIT(DDRA,channel);
	MCAL_ADC_Start_Conversion();
	
	if(polling == ENABLE){
		while(!READ_BIT(ADCSRA,4));
	}
	if(G_ADC_Config.ADC_Res_presentation == ADC_RES_PRESENTATION_RIGHT_ADJUSTED){
		*data = (ADCL | ((ADCH & (0x03)) <<8 ));
	}
	else{
		*data = ((ADCL & (0xC0)) >>6)  | (ADCH << 2);
	}
	CLR_BIT(ADCSRA, 4);

}

ISR(ADC_vect){
	G_ADC_Config.P_CallBack();
}