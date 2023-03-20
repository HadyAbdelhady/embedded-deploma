#include "lcd.h"
#define EIGHT_BIT
void E_LCD()
{
    // refresh the enable pin
    CLR_BIT(LCD_CTRL, E);
    delay;
    SET_BIT(LCD_CTRL, E);
}
void Busy_LCD()
{
    DateDir_LCD_PORT &= ~(0xFF << 4); // to be active in 4 bits also
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
    SET_BIT(LCD_CTRL, RS);
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
    Write_CMD_LCD(Display_on_cursor_blinking);
    Clear_LCD();
#ifdef EIGHT_BIT
    Write_CMD_LCD(Return_home);
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
    if (x == 1 && y < 16)
        Write_CMD_LCD(Force_cursor_to_beginning_1st_line + y);
    else if (x == 2 && y < 16)
        Write_CMD_LCD(Force_cursor_to_beginning_2nd_line + y);
}
void Write_String_LCD(char *data, char row, char col)
{
    int index = 0, line0 = 0; // line0 is to make the cursor move from 0,16 to 1,0
    GotoXY_LCD(row, col);
    while (data[index] != '\n' && ((row * 16) + (col + index)) < 32) // calculate the current cursor
    {
        if (((row * 16) + (col + index)) < 16)
            Write_char_LCD(data[index++]);
        else if (((row * 16) + (col + index)) == 16 && line0 == 0) // if line 1 is finished
        {
            GotoXY_LCD(1, 0);
            line0++;
        }
        else if (((row * 16) + (col + index)) < 32 && line0 == 1)
            Write_char_LCD(data[index++]);
    }
}
void CustomChar_LCD(char *Pattern, char CGram_index, char X, char Y)
{
    // CGram_index maybe 0,1,2 -- 7
    char Local_Address = 0;
    int i;
    // CGram consists of 8 locations so if i wanna get the address then get location*8
    if (CGram_index < 8)
    {
        Local_Address = 8 * CGram_index;
        Local_Address = SET_BIT(Local_Address, 6);
        Write_CMD_LCD(Local_Address);
        for (i = 0; i < 8; i++)
        {
            // byte by byte for each location of the 8 ones
            Write_char_LCD(Pattern[i]);
        }
    }
    Write_CMD_LCD(Return_home);
    // setCursor
    CLCD_VidGotoXY(X, Y);
    // show data of each pattern on the lcd
    Write_char_LCD(CGram_index);
}
