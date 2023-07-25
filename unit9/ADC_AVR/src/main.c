
#include "ADC.h"
#include"hal_lcd.h"

uint16_t ADC_Data;
uint32_t Temp;

int main(void)
{
	init_LCD();
	ADC_Config_t adc_cfg;
	adc_cfg.ADC_Mode =ADC_MODE_SINGLE_CONVERSION;
	adc_cfg.ADC_Prescaler = ADC_PRESCALER_64;
	adc_cfg.ADC_Res_presentation = ADC_RES_PRESENTATION_LEFT_ADJUSTED;
	adc_cfg.ADC_Volt_Ref = ADC_VOLT_REF_AVCC;
	adc_cfg.ADC_IRQ_Enable = ADC_IRQ_ENABLE_NONE;
	adc_cfg.P_CallBack = NULL;
	
	MCAL_ADC_Init(&adc_cfg);
	while(1){
	MCAL_ADC_Get_Result(ADC1,&ADC_Data,ENABLE);
	Temp  =(((ADC_Data *5000) / 1024) /10);
	Write_String_LCD("Temp: ");
	Write_char_LCD(Temp);
	Write_String_LCD(" C");
	_delay_ms(1000);
	Clear_LCD();
	}
}
