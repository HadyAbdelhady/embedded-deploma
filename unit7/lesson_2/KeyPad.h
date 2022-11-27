#ifndef _KEYPAD_
#define _KEYPAD_

#define KeyPad_PORT *(volatile unsigned char *)(0x32)
#define Data_dir_KeyPad_PORT *(volatile unsigned char *)(0x31)
#define Keypad_PIN *(volatile unsigned char *)(0x30)

// bitmath
#define SET_BIT(VAR, BIT) (VAR) |= (1 << (BIT))
#define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))
#define TOG_BIT(VAR, BIT) (VAR) ^= (1 << (BIT))
#define READ_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01)

enum Keypad_RC
{
    R0,
    R1,
    R2,
    R3,
    C0,
    C1,
    C2,
    C3
};
char KEYS[4][4] = {{'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, {'C', '0', '=', '+'}};
int Keypad_R[4] = {R0, R1, R2, R3};
int Keypad_C[4] = {C0, C1, C2, C3};

void init_Keypad();
char GetKey_Keypad();
#endif