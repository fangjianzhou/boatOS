

#include "config.h"
#include "platform_t.h"
#include "buildfile.h"


INPUT(LINKR_IPUT_FILE)
OUTPUT(LINKR_OPUT_FILE)
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{

        
        . = 0x30008000;
        __begin_kernel = .;
        __begin_seafarer_hal_head_text = .;
        .head.text ALIGN(4) : { *(.head.text) }
        __end_seafarer_hal_head_text = .;
        
        __begin_seafarer_hal_head_data = .;
        .head.data ALIGN(4) : { *(.head.data) }
        __end_seafarer_hal_head_data = .;
        
        __begin_seafarer_hal_init = .;
        .seafarer_hal.init ALIGN(4) : { *(.seafarer_hal.init) }
        __end_seafarer_hal_init = .;

        __begin_seafarer_hal_vector = .;
        .seafarer_hal.vector ALIGN(4) : { *(.seafarer_hal.vector) }
        __end_seafarer_hal_vector = .;
        
        __begin_seafarer_hal_intvect = .;
        .seafarer_hal.intvect ALIGN(4) : { *(.seafarer_hal.intvect) }
        __end_seafarer_hal_intvect = .;

        __begin_text = .;
        .text ALIGN(4) : { *(.text) }
        __end_text = .;

        __begin_data = .;
        .data ALIGN(4) :{ *(.data) }
        __end_data = .;

        __begin_rodata = .;
        .rodata ALIGN(4) :{ *(.rodata) *(.rodata.*) }
        __end_rodata = .;

        __begin_kstrtab = .;
        .kstrtab ALIGN(4) : { *(.kstrtab) }
        __end_kstrtab = .;

        __begin_bss = .;
        .bss ALIGN(4) : { *(.bss) }
        __end_bss = .;
        __end_kernel = .;
        
         /DISCARD/ : { *(.dynstr*) }
         /DISCARD/ : { *(.dynamic*) }
         /DISCARD/ : { *(.plt*) }
         /DISCARD/ : { *(.interp*) }
         /DISCARD/ : { *(.gnu*) }
}
