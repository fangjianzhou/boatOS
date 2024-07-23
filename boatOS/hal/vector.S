

.section .seafarer_hal.vector,"ax"
.code 32
.align 0

.extern hal_undefins
.extern hal_swi
.extern hal_prefabt
.extern hal_dataabt
.extern hal_bugdie
.extern hal_irq
.extern hal_frq
.extern _start

.global vector
vector:
        ldr pc,seafarer_restart_l
        ldr pc,seafarer_undefins_l
        ldr pc,seafarer_swi_l
        ldr pc,seafarer_prefabt_l
        ldr pc,seafarer_dataabt_l
        ldr pc,seafarer_bugdie_l
        ldr pc,seafarer_irq_l
        ldr pc,seafarer_frq_l
        nop
        nop
        nop
        nop
 _err:
        b   _start

.align 4
seafarer_restart_l:  .word _start
seafarer_undefins_l: .word hal_undefins
seafarer_swi_l:      .word hal_swi
seafarer_prefabt_l:  .word hal_prefabt
seafarer_dataabt_l:  .word hal_dataabt
seafarer_bugdie_l:   .word hal_bugdie
seafarer_irq_l:      .word hal_irq
seafarer_frq_l:      .word hal_frq


.end
