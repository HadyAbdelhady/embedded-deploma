#ifndef _LCD_
#define _LCD_

// lcd commands
#define Clear_display_screen 0x01
#define Return_home 0x02
#define Decrement_cursor 0x04
#define Shift_display_right 0x05
#define Increment_cursor 0x06
#define Shift_display_left 0x07
#define Display_cursor_off 0x08
#define Display_off_cursor_on 0x0A
#define Display_on_cursor_off 0x0C
#define Display_on_cursor_blinking 0x0E
#define Display_cursor_on 0x0F
#define Shift_cursor_position_to_left 0x10
#define Shift_cursor_position_to_right 0x14
#define Shift_the_entire_display_to_the_left 0x18
#define Shift_the_entire_display_to_the_right 0x1C
#define Force_cursor_to_beginning_1st_line 0x80
#define Force_cursor_to_beginning_2nd_line 0xC0
#define _2_lines_8_Bit 0x38
#define _2_lines_4_Bit 0x28

// delay

#define delay \
    for (int i = 0; i < 10000; i++)

// ports of avr
#define LCD_PORT *(volatile unsigned char *)(0x3B)         // portA
#define DateDir_LCD_PORT *(volatile unsigned char *)(0x3A) // DDRA
#define LCD_CTRL *(volatile unsigned char *)(0x38)         // portB
#define DateDir_LCD_CTRL *(volatile unsigned char *)(0x37) // DDRB

// lcd switchs
#define RS 1
#define RW 2
#define E 3

// bitmath
#define SET_BIT(VAR, BIT) (VAR) |= (1 << (BIT))
#define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))
#define TOG_BIT(VAR, BIT) (VAR) ^= (1 << (BIT))
#define READ_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01)

// lcd functions

void init_LCD(void);
void Write_CMD_LCD(unsigned char command);
void Write_char_LCD(unsigned char data);
void Write_String_LCD(char *data, char row, char col);
void GotoXY_LCD(unsigned char x, unsigned char y);
void Busy_LCD(void);
void Clear_LCD(void);

#endif