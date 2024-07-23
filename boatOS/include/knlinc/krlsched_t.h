
#ifndef _KRLSCHED_T_H
#define _KRLSCHED_T_H
#define NOTS_SCHED_FLGS 0
#define NEED_SCHED_FLGS 1

#define PMPT_FLGS 0

typedef struct s_THRDLST
{
    list_h_t    tdl_lsth; //链表头
    thread_t*   tdl_curruntd; //该链表头中正在运行的进程的指针
    uint_t      tdl_nr; // 计数器变量
}thrdlst_t;

typedef struct s_SCHDATA
{
    spinlock_t  sda_lock;    //自旋锁
    uint_t      sda_cpuid;   //CPU id
    uint_t      sda_schdflgs; //调度标志
    uint_t      sda_premptidx; //内核可抢占标志
    uint_t      sda_threadnr; //进程数
    uint_t      sda_prityidx; //当前动态优先级
    thread_t*   sda_cpuidle; //当前CPU上的空转进程
    thread_t*   sda_currtd; //当前CPU上正在运行的进程
    thrdlst_t   sda_thdlst[PRITY_MAX];//thrdlst_t结构体数组
}schdata_t;

typedef struct s_SCHEDCALSS
{
    spinlock_t  scls_lock; //自旋锁
    uint_t      scls_cpunr; //CPU数量，在目前情况下只有一颗CPU
    uint_t      scls_threadnr;// 进程总数量
    uint_t      scls_threadid_inc; //保留以后使用
    schdata_t   scls_schda[CPUCORE_MAX]; //schdata_t结构数组，CPUCORE_MAX为1
}schedclass_t;



#endif // KRLSCHED_T_H
