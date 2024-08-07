﻿
#ifndef _HALINTUPT_T_H
#define _HALINTUPT_T_H

#define IFLG_PRESENT (1<<0)
#define IFLG_INTINTP (1<<1)
#define IFLG_EXTINTP (1<<2)
#define IFLG_SUBINTP (1<<3)
#define IFLG_CLXINTP (1<<4)

#define CLXSUBINR(clxn,subn) (((clxn)<<16)|(subn))
#define INTPDEVID(mdn,sdn) (((mdn)<<16)|(sdn))

#define ONEHANDLE_FLG 0
#define MULHANDLE_FLG 1
#define INTSRC_FLG 1
#define SUBINTSRC_FLG 2

#define INTLINE_MAX 60
#define SUBINTLINE_MAX 14

#define INTMSK_R 0x4a000008
#define INTSUBMSK_R 0x4a00001c 
#define EINTMASK_R 0x560000a4
#define EINTPEND_R 0x560000a8 
#define LCDINTPND_R 0x4d000054



#define INTOFFSET_R 0x4a000014
#define INTPND_R 0x4a000010
#define SRCPND_R 0x4a000000
#define INTMOD_R 0x4a000004
#define SUBSRCPND_R 0x4a000018

#define SUBSRCPND_BITS_MASK 0x7fff
#define EINTPEND_BITS_MASK 0xffffff
#define LCDSRCPND_BITS_MASK 0x3

#define EINTPEND_R_BIT_S 4
#define EINTPEND_R_BIT_E 24
 
#define SUBSRCPND_R_BIT_S 0
#define SUBSRCPND_R_BIT_E 15

#define MINT_OFFSET 0
#define SINT_OFFSET 32
#define EINT_OFFSET 47
#define IRQ_MAX 71

#define MINTNR_START (0+MINT_OFFSET)
#define MINTNR_END (31+MINT_OFFSET)

#define SINTNR_START (0+SINT_OFFSET)
#define SINTNR_END (14+SINT_OFFSET)

#define EINTNR_START (0+EINT_OFFSET)
#define EINTNR_END (23+EINT_OFFSET)

#define MINT_FLG 1
#define SINT_FLG 2
#define EINT_FLG 3


#define MINT_IFDNR(x) (x+MINT_OFFSET)
#define SINT_IFDNR(x) (x+SINT_OFFSET)
#define EINT_IFDNR(x) (x+EINT_OFFSET)

#define EINT4_7 4
#define EINT8_23 5
#define INT_CAM 6
#define INT_WDT_AC97 9
#define INT_UART2 15
#define INT_LCD 16
#define INT_UART1 23
#define INT_UART0 28
#define INT_ADC 31

#define EI4_7_PNDBTS 4
#define EI4_7_PNDBTE 8

#define EI8_23_PNDBTS 8
#define EI8_23_PNDBTE 24

#define IUART0_PNDBTS 0
#define IUART0_PNDBTE 3

#define IUART1_PNDBTS 3
#define IUART1_PNDBTE 6

#define IUART2_PNDBTS 6
#define IUART2_PNDBTE 9

#define IADC_PNDBTS 9
#define IADC_PNDBTE 11

#define ICAM_PNDBTS 11
#define ICAM_PNDBTE 13

#define IACWDT_PNDBTS 13
#define IACWDT_PNDBTE 15

#define ILCD_PNDBTS 0
#define ILCD_PNDBTE 2


typedef struct s_ILNEDSC
{
    u32_t ild_modflg;
    u32_t ild_devid;
    u32_t ild_physid;
    u32_t ild_clxsubinr;
}ilnedsc_t;




typedef struct s_INTFLTDSC
{
    spinlock_t  i_lock; //自旋锁
    list_h_t    i_serlist; //设备中断服务程序链
    uint_t      i_sernr; //设备中断服务程序链个数
    u32_t       i_flg; //相关标志位
    u32_t       i_stus; //相关状态位
    u32_t       i_pndbitnr; //中断源挂起寄存器
    uint_t      i_irqnr; //中断号
    uint_t      i_deep; //保留
    uint_t      i_indx; //产生中断的次数
}intfltdsc_t;



typedef struct s_INTSERDSC
{
    list_h_t    s_list; //该链表是挂在intfltdsc_t中的i_serlist上
    list_h_t    s_indevlst; //该链表是挂在设备描述符中的相关链表上
    u32_t       s_flg; //一些标志
    intfltdsc_t* s_intfltp; //指向它所在的intfltdsc_t，通过这个可快速找到intfltdsc_t
    void*       s_device; //指向其设备描述符，可以通过它找到这是哪个设备的中断
    uint_t      s_indx; //该中断回调函数的运行计数
    intflthandle_t s_handle; //回调函数的指针
}intserdsc_t;




#endif // HALINTUPT_T_H
