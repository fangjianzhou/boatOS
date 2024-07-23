
#ifndef _HALMACH_T_H
#define _HALMACH_T_H
typedef struct s_MACH
{
    spinlock_t mh_lock; //自旋锁
    list_h_t   mh_list; //链表
    adr_t      mh_kerinramstart; //内核在内存中的开始地址
    adr_t      mh_kerinramend; // 内存在内存中的结束地址
    mmapdsc_t* mh_mmapdscadr; // 内存描述符在内存中的开始地址
    uint_t     mh_mmapdscnr; // 内存描述符的个数
    
    uint_t     mh_spedscnr; //物理地址空间描述符的个数
    phyadrspce_t *mh_spedsc; //物理地址空间描述符的地址
    ilnedsc_t* mh_ilnedsc;
    uint_t     mh_ilnedscnr;
    intfltdsc_t* mh_intfltdsc; // 中断源描述符地址
    uint_t     mh_intfltnr; // 中断源描述符个数
}mach_t;
#endif // HALINIT_H
