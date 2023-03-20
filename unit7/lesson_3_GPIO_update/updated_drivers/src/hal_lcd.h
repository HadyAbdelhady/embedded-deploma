#ifndef _LCD_
#define _LCD_
GPIO_Pin_Config_t PinCfg;

#include "mcal_stm32f103X6_gpio.h"
#include "stm32f103_X6.h"

#define LCD_PORT			GPIOA

#define LCD_CTRL			GPIOA


#define DATA_SHIFT			(4) // 0:4 bit date mode | 4:8 bit data mode


// Options for LCD
#define RS									GPIO_PIN_8
#define	RW									GPIO_PIN_9
#define E									GPIO_PIN_10
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FIRST_COLUMN							(0)

// Commands of LCD
#define LCD_CMD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_CMD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_CMD_FUNCTION_4BIT_2LINES_1st_CMD 			(0x02)
#define LCD_CMD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_CMD_MOVE_DISP_LEFT   						(0x18)
#define LCD_CMD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_CMD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_CMD_DISP_OFF   								(0x08)
#define LCD_CMD_DISP_ON_CURSOR   						(0x0E)
#define LCD_CMD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_CMD_DISP_ON_BLINK   						(0x0D)
#define LCD_CMD_DISP_ON   								(0x0C)
#define LCD_CMD_ENTRY_DEC   							(0x04)
#define LCD_CMD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_CMD_ENTRY_INC_   							(0x06)
#define LCD_CMD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_CMD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_CMD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CMD_CLEAR_SCREEN							(0x01)
#define LCD_CMD_ENTRY_MODE								(0x06)

// // bitmath
// #define SET_BIT(VAR, BIT) (VAR) |= (1 << (BIT))
// #define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))
// #define TOG_BIT(VAR, BIT) (VAR) ^= (1 << (BIT))
// #define READ_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01)

// lcd functions
void init_LCD(void);
void Write_CMD_LCD(unsigned char command);
void Write_char_LCD(unsigned char data);
void Write_String_LCD(char *data);
void GotoXY_LCD(unsigned char x, unsigned char y);
void Busy_LCD(void);
void Clear_LCD(void);
void CustomChar_LCD(char *Pattern, char CGram_index, char X, char Y);

#endif