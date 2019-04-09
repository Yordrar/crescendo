ENTRY(_start)

SECTIONS {
    . = 0xC0100000; /* the code should be linked at 3 GB + 1 MB */

    kernel_virt_start = .;
    kernel_phys_start = . - 0xC0000000;

    .text ALIGN (0x1000) : AT(ADDR(.text) - 0xC0000000)  
    {
        *(.text .stub .text.* .gnu.linkonce.t.*) /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - 0xC0000000) 
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*) /* all read-only data sections from all files */
    }

    /* Include debugging information in kernel memory */
	.stab ALIGN (0x1000) : AT(ADDR(.stab) - 0xC0000000) 
    {
		*(.stab);
		BYTE(0) /* Force the linker to allocate space for this section */
	}

	.stabstr ALIGN (0x1000) : AT(ADDR(.stabstr) - 0xC0000000) 
    {
		*(.stabstr);
		BYTE(0) /* Force the linker to allocate space for this section */
	}

    .data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000) 
    {
        *(.data) /* all data sections from all files */
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss) - 0xC0000000) 
    {
        *(COMMON) /* all COMMON sections from all files */
        *(.bss)   /* all bss sections from all files */
    }

    kernel_virt_end = .;
    kernel_phys_end = . - 0xC0000000;
}
