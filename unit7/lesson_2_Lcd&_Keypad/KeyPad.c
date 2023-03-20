#include "KeyPad.h"
void init_Keypad()
{
    CLR_BIT(Data_dir_KeyPad_PORT, R0);
    CLR_BIT(Data_dir_KeyPad_PORT, R1);
    CLR_BIT(Data_dir_KeyPad_PORT, R2);
    CLR_BIT(Data_dir_KeyPad_PORT, R3);
    SET_BIT(Data_dir_KeyPad_PORT, C0);
    SET_BIT(Data_dir_KeyPad_PORT, C1);
    SET_BIT(Data_dir_KeyPad_PORT, C2);
    SET_BIT(Data_dir_KeyPad_PORT, C3);
    KeyPad_PORT = 0xFF;
}
char GetKey_Keypad()
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        SET_BIT(KeyPad_PORT, Keypad_C[0]);
        SET_BIT(KeyPad_PORT, Keypad_C[1]);
        SET_BIT(KeyPad_PORT, Keypad_C[2]);
        SET_BIT(KeyPad_PORT, Keypad_C[3]);
        CLR_BIT(KeyPad_PORT, Keypad_C[i]);
        for (int j = 0; j < 4; j++)
        {
            if (!(Keypad_PIN & (1 << Keypad_R[i])))
            {
                while (!(Keypad_PIN & (1 << Keypad_R[i])))
                {
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
    }
}