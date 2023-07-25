
#include "hal_lcd.h"

void Busy_LCD(void)
{
	LCD_DATA_dir_PORT &= ~(0xff<<DATA_shift);
	LCD_CTRL |= (1<<RW); //read
	LCD_CTRL  &= ~(1<<RS);
	
	lcd_kick();
	LCD_DATA_dir_PORT = 0xff;
	LCD_CTRL &= ~(1<<RW); //write
}
void lcd_kick(void)
{
	LCD_CTRL &= ~(1<<EN); 
	asm volatile ("nop");
	asm volatile ("nop");
	_delay_ms(50);
	LCD_CTRL |= (1<<EN); 

}
void Write_CMD_LCD(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE 
		Busy_LCD();
		LCD_PORT = command;
		LCD_CTRL &= ~(1<<RW) | (1<<RS);
		lcd_kick();
		
#endif
	#ifdef FOUR_BIT_MODE
		Busy_LCD();
		LCD_PORT = (LCD_PORT & 0x0F) | (command &0xF0);	
		LCD_CTRL &= ~(1<<RW) | (1<<RS);
		lcd_kick();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
		LCD_CTRL &= ~(1<<RW) | (1<<RS);
		lcd_kick();
#endif
	
}
void init_LCD(void)
{
	_delay_ms(20);
	LCD_CTRL_dir_PORT |= (1<<EN | 1<<RW |1<<RS );
	LCD_CTRL &= ~(1<<EN | 1<<RW |1<<RS );
	LCD_DATA_dir_PORT = 0xFF;
	_delay_ms(20);
	
	Clear_LCD();
	#ifdef EIGHT_BIT_MODE
		Write_CMD_LCD(LCD_8BIT_MODE_2_LINE);
#endif

	#ifdef FOUR_BIT_MODE
		Write_CMD_LCD(0x02);
		Write_CMD_LCD(LCD_CMD_FUNCTION_4BIT_2LINES);
	#endif
	Write_CMD_LCD(LCD_CMD_ENTRY_MODE);
	Write_CMD_LCD(LCD_CMD_BEGIN_AT_FIRST_ROW);
	Write_CMD_LCD(LCD_CMD_DISP_ON_CURSOR_BLINK);
}
void Write_char_LCD(unsigned char The_char)
{
		#ifdef EIGHT_BIT_MODE
			Busy_LCD();
			LCD_PORT = The_char;
			LCD_PORT =((The_char)<< DATA_shift);
			LCD_CTRL |= 1<<RS;
			LCD_CTRL &= ~(1<<RW);
			lcd_kick();
		#endif

		#ifdef FOUR_BIT_MODE
			LCD_PORT = (LCD_PORT & 0x0F) | (The_char &0xF0);
			LCD_CTRL |= 1<<RS;
			LCD_CTRL &= ~(1<<RW);
			lcd_kick();
			LCD_PORT = (LCD_PORT & 0x0F) | (The_char << 4);
			
			LCD_CTRL |= 1<<RS;
			LCD_CTRL &= ~(1<<RW);
			lcd_kick();
		#endif
}
void Write_String_LCD( char* The_char)
{
	int count=0;
	while(*The_char){
		Write_char_LCD(*The_char++);
		count++;
		if(count == 16){
			Write_CMD_LCD(LCD_CMD_BEGIN_AT_SECOND_ROW);
		}
		else if( count == 32 || count == 33){
			Clear_LCD();
			Write_CMD_LCD(LCD_CMD_BEGIN_AT_FIRST_ROW);
			count = 0;
		}
	}
	
}
void GotoXY_LCD(unsigned char line ,unsigned char pos)
{
	if(line == 0){
		if(pos <16 && pos>=0){
			Write_CMD_LCD(0x80+pos);
		}else if(line == 1){
			if(pos <16 && pos>=0){
				Write_CMD_LCD(0x80+pos);
				}
		}
	}
	
}
void Clear_LCD(void)
{
	Write_CMD_LCD(LCD_CMD_CLEAR_SCREEN);
	}