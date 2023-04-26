#include "HAL/hal_lcd.h"
#define SET_BIT(BYTE,Bit_NO) (BYTE |= (1<<(Bit_NO)))


#define EIGHT_BIT_MODE

void delay_ms(uint32_t time)
{
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++)
            ;
}

void E_LCD()
{
    MCAL_GPIO_WritePin(LCD_CTRL, E, HIGH);
    delay_ms(50);
    MCAL_GPIO_WritePin(LCD_CTRL, E, LOW);
}
void Busy_LCD()
{
    //*******************updated driver*******************
    PinCfg.GPIO_Pin_Number = GPIO_PIN_0;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_1;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_2;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_3;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_4;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_5;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_6;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_Pin_Number = GPIO_PIN_7;
    PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    MCAL_GPIO_WritePin(LCD_CTRL, RW, HIGH);
    MCAL_GPIO_WritePin(LCD_CTRL, RS, LOW);
    //	LCD_CTRL |= (1 << RW_SWITCH);
    //	LCD_CTRL &= ~(1 << RS_SWITCH);
    E_LCD();
    //	DataDir_LCD_PORT |= (0xFF << DATA_shift);
    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    //	LCD_CTRL &= ~(1 << RW_SWITCH);
}
void Clear_LCD(void)
{
    Write_CMD_LCD(LCD_CMD_CLEAR_SCREEN);
}
void GotoXY_LCD(unsigned char x, unsigned char y)
{
    if (x == 1)
    {
        if (y < 16 && x >= 0)
        {
            Write_CMD_LCD(LCD_CMD_BEGIN_AT_FIRST_ROW + x);
        }
    }
    if (x == 2)
    {
        if (y < 16 && x >= 0)
        {
            Write_CMD_LCD(LCD_CMD_BEGIN_AT_SECOND_ROW + x);
        }
    }
}
void Write_String_LCD(char *data)
{
    int count = 0;
    while (*data != 0)
    {
        if (count == 16)
        {
            GotoXY_LCD(LCD_SECOND_LINE, LCD_FIRST_COLUMN);
        }
        else if (count > 31)
        {
            Clear_LCD();
            GotoXY_LCD(LCD_FIRST_LINE, LCD_FIRST_COLUMN);
            count = 0;
        }
        count++;
        Write_char_LCD(*data++);
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
        SET_BIT(Local_Address, 6);
        Write_CMD_LCD(Local_Address);
        for (i = 0; i < 8; i++)
        {
            // byte by byte for each location of the 8 ones
            Write_char_LCD(Pattern[i]);
        }
    }
    // Write_CMD_LCD(home);
    // setCursor
    GotoXY_LCD(X, Y);
    // show data of each pattern on the lcd
    Write_char_LCD(CGram_index);
}
void init_LCD()
{

    MCAL_GPIO_SET_Pin(LCD_CTRL, RS, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, RW, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, E, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    delay_ms(20);
//============================
// SET THE NEXT 8 PINS AS INPUT
//============================
#ifdef EIGHT_BIT_MODE
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_0, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_1, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_2, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_3, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_4, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_5, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_6, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_7, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    //	DataDir_LCD_CTRL |= (1 << E | 1 << RS | 1 << RW);
    MCAL_GPIO_WritePin(LCD_CTRL, RS, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, E, LOW);
    delay_ms(15);
    Clear_LCD();
    Write_CMD_LCD(LCD_CMD_FUNCTION_8BIT_2LINES);
#endif
#ifdef FOUR_BIT_MODE
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_4, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_5, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_6, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(LCD_CTRL, GPIO_PIN_7, GPIO_Mode_Output_PP, GPIO_SPEED_10MHz);

    //	DataDir_LCD_CTRL |= (1 << E | 1 << RS | 1 << RW);
    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, RS, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, E, LOW);
    delay_ms(15);
    Clear_LCD();
    Write_CMD_LCD(LCD_CMD_FUNCTION_4BIT_2LINES_1st_CMD);
    Write_CMD_LCD(LCD_CMD_FUNCTION_4BIT_2LINES);
#endif
    delay_ms(15);
    Write_CMD_LCD(LCD_CMD_ENTRY_MODE);
    Write_CMD_LCD(LCD_CMD_BEGIN_AT_FIRST_ROW);
    Write_CMD_LCD(LCD_CMD_DISP_ON_CURSOR_BLINK);
}

void Write_CMD_LCD(unsigned char command)
{

//*******************updated driver*******************
// Busy_LCD();
#ifdef EIGHT_BIT_MODE

    // MCAL_GPIO_WritePort(LCD_CTRL, command);
    MCAL_GPIO_WritePort(LCD_CTRL, (command));

    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, RS, LOW);

    delay_ms(5);
    E_LCD();
#endif

#ifdef FOUR_BIT_MODE

    MCAL_GPIO_WritePort(LCD_CTRL, ((MCAL_GPIO_ReadPORT(LCD_CTRL) & 0xFF0F) | (command & 0xF0)));

    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, RS, LOW);

    delay_ms(1);
    E_LCD();

    MCAL_GPIO_WritePort(LCD_CTRL, ((MCAL_GPIO_ReadPORT(LCD_CTRL) & 0xFF0F) | ((command & 0x0F) << 4)));

    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    MCAL_GPIO_WritePin(LCD_CTRL, RS, LOW);
    // delay_ms(5);
    E_LCD();

#endif
}
void Write_char_LCD(unsigned char character)
{
    //*******************updated driver*******************
#ifdef EIGHT_BIT_MODE

    // MCAL_GPIO_WritePort(LCD_CTRL, character);
    MCAL_GPIO_WritePort(LCD_PORT, (character));
    MCAL_GPIO_WritePin(LCD_CTRL, RS, HIGH);
    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    delay_ms(1);
    E_LCD();
#endif
#ifdef FOUR_BIT_MODE

    MCAL_GPIO_WritePort(LCD_CTRL, ((MCAL_GPIO_ReadPORT(LCD_CTRL) & 0xFF0F) | (character & 0xF0)));
    MCAL_GPIO_WritePin(LCD_CTRL, RS, HIGH);
    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    E_LCD();

    MCAL_GPIO_WritePort(LCD_CTRL, ((MCAL_GPIO_ReadPORT(LCD_CTRL) & 0xFF0F) | ((character & 0x0F) << 4)));
    MCAL_GPIO_WritePin(LCD_CTRL, RS, HIGH);
    MCAL_GPIO_WritePin(LCD_CTRL, RW, LOW);
    E_LCD();
#endif
}
