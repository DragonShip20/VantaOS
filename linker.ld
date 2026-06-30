ENTRY(_start)

SECTIONS 
{
    . = 0x10000;

    _kernel_start = .;

    .text : {
        _text_start = .;
	KEEP(*(.start))
        *(.text*)
        _text_end = .;
    }
    
    .data : {
        _data_start = .;
        *(.data*)
        _data_end = .;
    }

    .bss : {
        _bss_start = .;
        *(.bss*)
        _bss_end = .;
    }

    .rodata : {
        _rodata_start = .;
        *(.rodata*)
        _rodata_end = .;
    }

    _kernel_end = .;
}
