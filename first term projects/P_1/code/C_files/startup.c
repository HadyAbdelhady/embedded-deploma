#include "Platform_Types.h"
extern uint32 _STACK_TOP;
extern uint32 *_E_TEXT;
extern uint32 *_S_BSS;
extern uint32 *_E_BSS;
extern uint32 *_S_DATA;
extern uint32 *_E_DATA;
extern int main(void);
void Reset_handler(void);
void default_handler(void)
{
    Reset_handler();
}
void NMI_handler(void) __attribute__((weak, alias("default_handler")));
;
void HFault_handler(void) __attribute__((weak, alias("default_handler")));
;

uint32 _vectors[] __attribute__((section(".vectors"))) = {(uint32)&_STACK_TOP, (uint32)&NMI_handler, (uint32)&HFault_handler};

void Reset_handler()
{
    // copy data from flash to ram
    uint32 _data_size = (uint32 *)&_E_DATA - (uint32 *)&_S_DATA;
    uint32 *_p_data = (uint32 *)&_S_DATA;
    uint32 *_P_txt = (uint32 *)&_E_TEXT;
    for (uint32 i = 0; i < _data_size; i++)
    {
        *((uint32 *)_p_data++) = *((uint32 *)_P_txt++);
    }

    _p_data = (uint32 *)_S_BSS;
    // clear bss section
    uint32 _bss_size = (uint32 *)&_E_BSS - (uint32 *)&_S_BSS;
    for (uint32 i = 0; i < _bss_size; i++)
    {
        *((uint32 *)_p_data++) = (uint32)0;
    }
    main();
}