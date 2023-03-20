#include "Z:\Program_Files\Freq_used\utilities\Platform_Types.h"
#include "Z:\Program_Files\Freq_used\utilities\Bit_Math.h"
#define PORTD *(vuint8 *)(0x32)
#define DDRD *(vuint8 *)(0x31)
#define delay                       \
  for (uint32 i = 0; i < 8000; i++) \
    

void main()
{
  DDRD = 0xff;
  // to clear the output pins
  CLR_BIT(PORTD, 5);
  CLR_BIT(PORTD, 6);
  CLR_BIT(PORTD, 7);
  while (1)
  {
    //////////////////////////////////////first task (lecture)/////////////////////////////////

    // first led on and delay then off
    SET_BIT(PORTD, 5);
    delay;
        CLR_BIT(PORTD, 5);
    // second led on and delay then off
    SET_BIT(PORTD, 6);
    delay;
        CLR_BIT(PORTD, 6);
    // third led on and delay then off
    SET_BIT(PORTD, 7);
    delay;
        CLR_BIT(PORTD, 7);
    // buzzer on then off
    SET_BIT(PORTD, 4);
    delay;
        CLR_BIT(PORTD, 4);

    //////////////////////////////////////second task (section)/////////////////////////////////
    for (int i = 0; i <= 255; i = i * 2 + 1)
    {
      PORTD = i;
      delay;
    }
    for (int i = 255; i >= 1; i = i / 2)
    {
      PORTD = i;
      delay;
    }
  }
}
