

MEMORY
{
	/* Let's use the address space start from 0x00000000 */
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 2048k /* 2048K */
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 192k  /* 192K  */
}

/* Section Definitions */

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	} >FLASH
	
	.data : AT (_etext)
	{
		_data = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	} >SRAM

	.bss (NOLOAD) :
	{
		_bss = .;
		*(.bss)
		. = ALIGN(4);
		_ebss = .;
	} >SRAM

	_end = .;
}
