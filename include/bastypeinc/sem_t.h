
#ifndef _SEM_T_H
#define _SEM_T_H
#define SEM_FLG_MUTEX 0
#define SEM_FLG_MULTI 1
#define SEM_MUTEX_ONE_LOCK 1
#define SEM_MULTI_LOCK 0

typedef struct s_KWLST
{   
    spinlock_t wl_lock;
    uint_t   wl_tdnr;
    list_h_t wl_list;
}kwlst_t;

typedef struct s_SEM
{
	spinlock_t sem_lock; //自旋锁
	uint_t sem_flg; // 该信号量的一些标志和类型
	sint_t sem_count; // 该信号量的信号值
	kwlst_t sem_waitlst; // 该信号量的等待链
}sem_t;

#endif
