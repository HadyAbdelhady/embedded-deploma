#include "HAL/inc/hal_KeyPad.h"
#include "MCAL/inc/mcal_gpio.h"

char KEYS[4][4] = {{'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, {'C', '0', '=', '+'}};
int Keypad_ROWS[4] = {R0, R1, R2, R3};
int Keypad_COLUMNS[4] = {C0, C1, C2, C3};

void init_Keypad(void)
{
    MCAL_GPIO_SET_Pin(KeyPad_PORT,R0,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,R1,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,R2,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,R3,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,C0,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,C1,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,C2,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_SET_Pin(KeyPad_PORT,C3,GPIO_Mode_Output_PP,GPIO_SPEED_10MHz);
    MCAL_GPIO_WritePort(KeyPad_PORT, 0xFF);
}
char GetKey_Keypad(void)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_COLUMNS[0], HIGH);
        MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_COLUMNS[1], HIGH);
        MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_COLUMNS[2], HIGH);
        MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_COLUMNS[3], HIGH);
        MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_COLUMNS[i], LOW);
        for (j = 0; j < 4; j++)
        {
            if (MCAL_GPIO_ReadPin(KeyPad_PORT, Keypad_ROWS[j]) == 0)
            {
                while (MCAL_GPIO_ReadPin(KeyPad_PORT, Keypad_ROWS[j]) == 0)
                    ;
                switch (i)
                {
                case 0:
                    switch (j)
                    {
                    case 0:
                        return KEYS[0][0];
                        break;
                    case 1:
                        return KEYS[0][1];
                        break;
                    case 2:
                        return KEYS[0][2];
                        break;
                    case 3:
                        return KEYS[0][3];
                        break;
                    default:
                        return '!';
                    }
                    break;
                case 1:
                    switch (j)
                    {
                    case 0:
                        return KEYS[1][0];
                        break;
                    case 1:
                        return KEYS[1][1];
                        break;
                    case 2:
                        return KEYS[1][2];
                        break;
                    case 3:
                        return KEYS[1][3];
                        break;
                    default:
                        return '!';
                    }
                    break;
                case 2:
                    switch (j)
                    {
                    case 0:
                        return KEYS[2][0];
                        break;
                    case 1:
                        return KEYS[2][1];
                        break;
                    case 2:
                        return KEYS[2][2];
                        break;
                    case 3:
                        return KEYS[2][3];
                        break;
                    default:
                        return '!';
                    }
                    break;
                case 3:
                    switch (j)
                    {
                    case 0:
                        return KEYS[3][0];
                        break;
                    case 1:
                        return KEYS[3][1];
                        break;
                    case 2:
                        return KEYS[3][2];
                        break;
                    case 3:
                        return KEYS[3][3];
                        break;
                    default:
                        return '!';
                    }
                    break;
                default:
                    return '!';
                }
            }
        }
    }
    return ' ';
}

