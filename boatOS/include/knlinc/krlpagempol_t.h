
#ifndef _KRLPAGEMPOL_T_H
#define _KRLPAGEMPOL_T_H

#define MPALCLST_MAX 5

#define PMPLMAP_MAX 32
#define KMEMPALCSZ_MIN 1
#define KMEMPALCSZ_MAX 0x400000

#define OBJSORPAGE 2048
#define KPMPORHALM (PAGE_SIZE*31)

#define MPLHTY_PAGE 1
#define MPLHTY_OBJS 2

#define OBJS_ALIGN(x) ALIGN(x,4) 

typedef struct s_PGLMAP
{
    adr_t            pgl_start; //保存内存池中一个页面的首地址
    struct s_PGLMAP* pgl_next; //指向自身的一个指针
}pglmap_t;

typedef struct s_MPLHEAD
{
    spinlock_t      mh_lock; //自旋锁
    list_h_t        mh_list; //链表
    uint_t          mh_hedty; //内存池管理头的类型
    adr_t           mh_start; //内存池的开始地址
    adr_t           mh_end; //内存池的结束地址
    adr_t           mh_firtfreadr; 
    pglmap_t*       mh_firtpmap; //指向第一个空闲页状态描述结构的指针
    uint_t          mh_objnr; //池中页的个数
    uint_t          mh_aliobsz; 
    uint_t          mh_objsz; //池中页的大小
    uint_t          mh_nxtpsz; //确定下一个对象指针的偏移
    uint_t          mh_afindx; //已经分配对象的个数
    uint_t          mh_pmnr; //页状态描述结构的个数
    pglmap_t*       mh_pmap; //页状态描述结构的存放地址
}mplhead_t;

typedef struct s_KMEMPOOL
{
    spinlock_t      mp_lock;  //自旋锁
    list_h_t        mp_list; //链表
    uint_t          mp_stus; //状态
    uint_t          mp_flgs; //标志
    spinlock_t      mp_pglock; //保存页级内存池的自旋锁
    spinlock_t      mp_oblock; //保存字级内存池的自旋锁
    uint_t          mp_pgmplnr; //页级内存池的个数
    uint_t          mp_obmplnr; //字级内存池的个数
    list_h_t        mp_pgmplmheadl; //挂载页级内存池的链表头
    list_h_t        mp_obmplmheadl; //挂载字级内存池的链表头
    mplhead_t*      mp_pgmplmhcach; //保存当前操作过的页级mplhead_t结构
    mplhead_t*      mp_obmplmhcach; //保存当前操作过的字级mplhead_t结构
}kmempool_t;




#endif // KRLPAGEMPOL_T_H
