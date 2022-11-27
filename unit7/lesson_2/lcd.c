#include "lcd.h"
#define EIGHT_BIT
void E_LCD()
{
    CLR_BIT(LCD_CTRL, E);
    delay;
    SET_BIT(LCD_CTRL, E);
}
void Busy_LCD()
{
    DateDir_LCD_PORT &= ~(0xFF << 4); // to be active in 4 bits only
    SET_BIT(LCD_CTRL, RW);            // readmode
    CLR_BIT(LCD_CTRL, RS);
    E_LCD();
    DateDir_LCD_PORT = 0xFF;
    CLR_BIT(LCD_CTRL, RW);
}
void Clear_LCD(void)
{
    Write_CMD_LCD(Clear_display_screen);
}
void Write_CMD_LCD(unsigned char command)
{
    Busy_LCD();
#ifdef EIGHT_BIT
    LCD_PORT = command;
    CLR_BIT(LCD_CTRL, RW);
    CLR_BIT(LCD_CTRL, RS);
    delay;
    E_LCD();
#elif FOUR_BIT
    LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
    CLR_BIT(LCD_CTRL, RS);
    CLR_BIT(LCD_CTRL, RW);
    delay;
    E_LCD();
    LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
    CLR_BIT(LCD_CTRL, RS);
    CLR_BIT(LCD_CTRL, RW);
    E_LCD();

#endif
}
void Write_char_LCD(unsigned char data)
{
    Busy_LCD();
#ifdef EIGHT_BIT
    LCD_PORT = data;
    CLR_BIT(LCD_CTRL, RW);
    CLR_BIT(LCD_CTRL, RS);
    delay;
    E_LCD();
#elif FOUR_BIT
    LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
    CLR_BIT(LCD_CTRL, RS);
    CLR_BIT(LCD_CTRL, RW);
    delay;
    E_LCD();
    LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
    CLR_BIT(LCD_CTRL, RS);
    CLR_BIT(LCD_CTRL, RW);
    delay;
    E_LCD();

#endif
}
void init_LCD(void)
{
    delay;
    Busy_LCD();
    SET_BIT(DateDir_LCD_CTRL, E);
    SET_BIT(DateDir_LCD_CTRL, RW);
    SET_BIT(DateDir_LCD_CTRL, RS);
    CLR_BIT(LCD_CTRL, E);
    CLR_BIT(LCD_CTRL, RW);
    CLR_BIT(LCD_CTRL, RS);
    DateDir_LCD_PORT = 0xFF; // output
    Clear_LCD();
#ifdef EIGHT_BIT
    Write_CMD_LCD(_2_lines_8_Bit);
#elif FOUR_BIT
    Write_CMD_LCD(Return_home);
    Write_CMD_LCD(_2_lines_4_Bit);
#endif
    Write_CMD_LCD(Increment_cursor);
    Write_CMD_LCD(Force_cursor_to_beginning_1st_line);
    Write_CMD_LCD(Display_on_cursor_blinking);
}
void GotoXY_LCD(unsigned char x, unsigned char y)
{
    if (x == 1)
    {
        if (y < 32 && y >= 0)
        {
            Write_CMD_LCD(Force_cursor_to_beginning_1st_line + y);
        }
    }
    else if (x == 2)
    {
        if (y < 32 && y >= 0)
        {
            Write_CMD_LCD(Force_cursor_to_beginning_2nd_line + y);
        }
    }
}
void Write_String_LCD(char *data)
{
    int count = 0;
    while (*data > 0)
    {
        count++;
        Write_char_LCD(data++);
        if (count == 16)
            GotoXY_LCD(2, 0);
        else if (count == 32)
        {
            Clear_LCD();
            GotoXY_LCD(1, 0);
            count = 0;
        }
    }
}

void CustomChar_LCD(char *Copy_pu8Pattern, char Copy_u8PatternNumber,char Copy_u8XPOS,char Copy_u8YPOS){
	char Local_u8Address =0;
	//Copy_u8PatternNumber maybe 0,1,2 -- 7
	//CGram consists of 8 locations so if i wanna get the address:
	Local_u8Address =8 *Copy_u8PatternNumber;
	//go to this address by the key of CGram "its address 64"
	CLCD_VidSendCommand (64+ Local_u8Address);
	//write on this address
	for(char i=0; i<8;i++){
		//byte by byte for each location of the 8 ones
		//send data to cgram it won't appear on lcd
		CLCD_VidSendData (Copy_pu8Pattern[i]);
	}
	//3awz a5rog mn CGRAm w aro7 ll DDRam 34an a write on LCD
	CLCD_VidGotoXY(Copy_u8XPOS,Copy_u8YPOS);
	//show data of each pattern on the lcd
	CLCD_VidSendData (Copy_u8PatternNumber);
}
