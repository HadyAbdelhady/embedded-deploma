/*
arm_cortex_m3
author:hady abdelhady
*/
MEMORY
{
	flash(RX) : ORIGIN = 0x08000000 , LENGTH = 128k
	sram(RWX) : ORIGIN = 0x20000000 , LENGTH = 20k
}
SECTIONS
{
	.text :
	{
	  *(.vectors*)
	  *(.text*)
	  *(.rodata)	
	    _E_TEXT = . ;
	}> flash
	.data :
	{
	  _S_DATA = . ;
	  *(.data)
 	  _E_DATA_ = . ;
	}>sram AT> flash
	.bss :
	{
	  _S_BSS = . ;
	  *(.bss*)
        _E_BSS = . ;
	}> sram
	_STACK_TOP = . + 0x1000;
}