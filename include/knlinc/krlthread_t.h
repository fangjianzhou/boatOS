
#ifndef _KRLTHREAD_T_H
#define _KRLTHREAD_T_H
#define TDSTUS_RUN 0
#define TDSTUS_SLEEP 3
#define TDSTUS_WAIT 4
#define TDSTUS_NEW 5
#define TDSTUS_ZOMB 6

#define TDRUN_TICK 20

#define PRITY_MAX 64
#define PRITY_MIN 0
#define PRILG_SYS 0
#define PRILG_USR 5

#define MICRSTK_MAX 4

#define DAFT_TDUSRSTKSZ 0x8000
#define DAFT_TDKRLSTKSZ 0x8000

#define DAFT_SPSR 0x10
#define DAFT_CPSR 0xd3
#define DAFT_CIDLESPSR 0x13

#define TD_HAND_MAX 8   
typedef struct s_MICRSTK
{
    uint_t msk_val[MICRSTK_MAX];
}micrstk_t;



typedef struct s_CONTEXT
{
    reg_t       ctx_usrsp; //用户模式下的栈指针寄存器
    reg_t       ctx_svcsp; //内核模式下的栈指针寄存器
    reg_t       ctx_svcspsr; //内核模式下的备份程序状态寄存器
    reg_t       ctx_cpsr; //当前程序状态寄存器
    reg_t       ctx_lr; //内核模式下的链接寄存器
}context_t;
typedef struct s_THREAD
{
    spinlock_t  td_lock; //保护其自身的自旋锁
    list_h_t    td_list; // 链表
    uint_t      td_flgs; // 进程标志
    uint_t      td_stus; // 进程状态
    uint_t      td_cpuid; // 进程CPUID
    uint_t      td_id; // 进程自身ID
    uint_t      td_tick; // 进程TICK
    uint_t      td_privilege; 
    uint_t      td_priority; //进程优先级
    uint_t      td_runmode; // 进程运行模式
    adr_t       td_krlstktop; // 进程内核栈的栈顶
    adr_t       td_krlstkstart; //进程内核栈的开始地址
    adr_t       td_usrstktop; //进程用户栈的栈顶
    adr_t       td_usrstkstart; // 进程用户栈的开始地址
    void*       td_mmdsc; //进程内存描述符
    void*       td_resdsc; 
    void*       td_privtep;
    void*       td_extdatap; //以后扩展所用
    context_t   td_context; //进程的CPU上下文
    objnode_t*  td_handtbl[TD_HAND_MAX]; //进程使用的资源数组
}thread_t;

#endif // KRLTHREAD_T_H
