/* INSERT HEADER */

/* INSERT INCLUDES */

ENTRY(${start_symbol})

SECTIONS
{
    /* INSERT TEXT_SECTION */

    /* MAIN TEXT SECTION */    
    .text : ALIGN(${text_align})
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* INSERT SECTION_TABLE */

        . = 0x200;
        *(.after_vectors*)
        
        /* INSERT CRP */
    } >${CODE}
    
    .text : ALIGN(${text_align})    
    {
         *(.text*)
        /* INSERT RODATA */
        
        /* INSERT CPP_INFO */
    } > ${CODE}

    /* INSERT EXDATA */
    
    _etext = .;
        
    /* INSERT DATA_SECTION */
    
    /* MAIN DATA SECTION */
    
    /* INSERT MTB_DEFAULT_SECTION */

    .uninit_RESERVED : ALIGN(${data_align})
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > ${DATA}

	/* INSERT MAIN_DATA_SECTION */

    /* INSERT BSS_SECTION */

    /* MAIN BSS SECTION */
    .bss : ALIGN(${bss_align})
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(${bss_align}) ;
        _ebss = .;
        PROVIDE(end = .);
    } > ${DATA}
        
    /* INSERT NOINIT_SECTION */
    
    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(${bss_align})
    {
        _noinit = .;
        *(.noinit*) 
         . = ALIGN(${bss_align}) ;
        _end_noinit = .;
    } > ${DATA}
    
    PROVIDE(${heap_symbol} = .);
    PROVIDE(_vStackTop = __top_${DATA} - ${STACK_OFFSET});
}

