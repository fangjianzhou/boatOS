
#include "seafarertypes.h"
#include "seafarerctrl.h"

void thrdlst_t_init(thrdlst_t* initp)
{
    list_init(&initp->tdl_lsth);
    initp->tdl_curruntd=NULL;
    initp->tdl_nr=0;
    return;
}

void schdata_t_init(schdata_t* initp)
{
    hal_spinlock_init(&initp->sda_lock);
    initp->sda_cpuid=hal_retn_cpuid();
    initp->sda_schdflgs=NOTS_SCHED_FLGS;
    initp->sda_premptidx=0;
    initp->sda_threadnr=0;
    initp->sda_prityidx=0;
    initp->sda_cpuidle=NULL;
    initp->sda_currtd=NULL;
    for(uint_t ti=0;ti<PRITY_MAX;ti++)
    {
        thrdlst_t_init(&initp->sda_thdlst[ti]);
    }
    return;
}

void schedclass_t_init(schedclass_t* initp)
{
    hal_spinlock_init(&initp->scls_lock);   
    initp->scls_cpunr=CPUCORE_MAX;
    initp->scls_threadnr=0;
    initp->scls_threadid_inc=0;
    for(uint_t si=0;si<CPUCORE_MAX;si++)
    {
        schdata_t_init(&initp->scls_schda[si]);
    }
    return;
}

void init_krlsched()
{
    schedclass_t_init(&osschedcls);
    return;
}

thread_t* krlsched_retn_currthread()
{
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    if(schdap->sda_currtd==NULL)
    {
        hal_sysdie("schdap->sda_currtd NULL");
    }
    return schdap->sda_currtd;
}

void krlsched_wait(kwlst_t* wlst)
{   
    cpuflg_t cufg,tcufg;
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    thread_t* tdp=krlsched_retn_currthread();
    uint_t pity=tdp->td_priority;
    
    if(pity>=PRITY_MAX||wlst==NULL)
    {
        goto err_step;
    }
    if(schdap->sda_thdlst[pity].tdl_nr<1)
    {
        goto err_step;
    }
    
    hal_spinlock_saveflg_cli(&schdap->sda_lock,&cufg);
    
    hal_spinlock_saveflg_cli(&tdp->td_lock,&tcufg);
    //设置进程状态为等待状态
    tdp->td_stus=TDSTUS_WAIT;
    //把进程从调度进程表中的相关链表上拿出来
    list_del(&tdp->td_list);
    hal_spinunlock_restflg_sti(&tdp->td_lock,&tcufg);
    //如果拿出的进程和当前优先级链表上正在运行的进程相同，就让其为NULL
    if(schdap->sda_thdlst[pity].tdl_curruntd==tdp)
    {
        schdap->sda_thdlst[pity].tdl_curruntd=NULL;
    }
    schdap->sda_thdlst[pity].tdl_nr--;
    
    hal_spinunlock_restflg_sti(&schdap->sda_lock,&cufg);
    //把进程加入相关的kwlst_t结构中
    krlwlst_add_thread(wlst,tdp);

    return;
        
err_step:
    hal_sysdie("krlsched_wait err");   
    return;
}

void krlsched_up(kwlst_t* wlst)
{
    cpuflg_t cufg,tcufg;
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    thread_t* tdp;
    uint_t pity;
    if(wlst==NULL)
    {
        goto err_step;
    }
    //返回kwlst_t结构中的进程
    tdp=krlwlst_del_thread(wlst);
    if(tdp==NULL)
    {
       goto err_step;
    }
    pity=tdp->td_priority;
    if(pity>=PRITY_MAX)
    {
        goto err_step;
    }
    hal_spinlock_saveflg_cli(&schdap->sda_lock,&cufg);
    hal_spinlock_saveflg_cli(&tdp->td_lock,&tcufg);
    //设置进程的状态为运行状态
    tdp->td_stus=TDSTUS_RUN;
    hal_spinunlock_restflg_sti(&tdp->td_lock,&tcufg);
    //把该进程加入调度进程表的相应优先级链表中
    list_add_tail(&tdp->td_list,&(schdap->sda_thdlst[pity].tdl_lsth));
    schdap->sda_thdlst[pity].tdl_nr++;
    hal_spinunlock_restflg_sti(&schdap->sda_lock,&cufg);
    
    return;
err_step:
    hal_sysdie("krlsched_up err");   
    return;    
}

thread_t* krlsched_retn_idlethread()
{
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];

    if(schdap->sda_cpuidle==NULL)
    {
        hal_sysdie("schdap->sda_cpuidle NULL");
    }
    return schdap->sda_cpuidle;
}


void krlsched_set_schedflgs()
{
    cpuflg_t cpuflg;
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    
    hal_spinlock_saveflg_cli(&schdap->sda_lock,&cpuflg);
    schdap->sda_schdflgs=NEED_SCHED_FLGS;
    hal_spinunlock_restflg_sti(&schdap->sda_lock,&cpuflg);
    return;
}

void krlsched_chkneed_pmptsched()
{
    cpuflg_t cpuflg;
    uint_t schd=0, cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    
    hal_spinlock_saveflg_cli(&schdap->sda_lock,&cpuflg);
    
    
    if(schdap->sda_schdflgs==NEED_SCHED_FLGS&&schdap->sda_premptidx==PMPT_FLGS)
    {
        schdap->sda_schdflgs=NOTS_SCHED_FLGS;
        schd=1;
    }
    hal_spinunlock_restflg_sti(&schdap->sda_lock,&cpuflg);
    if(schd==1)
    {
       
        krlschedul();
    }
    return;
}
thread_t* krlsched_select_thread()
{
    thread_t* retthd ,*tdtmp ;
    cpuflg_t cufg;
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    
    hal_spinlock_saveflg_cli(&schdap->sda_lock,&cufg);
    //从0级优先级开始扫描，直到63级优先级
    for(uint_t pity=0;pity<PRITY_MAX;pity++)
    {
        //检查当前优先级的进程队列中有没有进程
        if(schdap->sda_thdlst[pity].tdl_nr>0)
        {
            
            if(list_is_empty_careful(&(schdap->sda_thdlst[pity].tdl_lsth))==FALSE)
            {
                //提取进程队列头链表中的第一个进程并脱钩
                tdtmp=list_entry(schdap->sda_thdlst[pity].tdl_lsth.next,thread_t,td_list);
                list_del(&tdtmp->td_list);
                //如果当前进程队列的tdl_curruntd域中有进程，就将其挂载到进程队列头链表的尾部
                if(schdap->sda_thdlst[pity].tdl_curruntd!=NULL)
                {
                    list_add_tail(&(schdap->sda_thdlst[pity].tdl_curruntd->td_list),&schdap->sda_thdlst[pity].tdl_lsth);
                }
                schdap->sda_thdlst[pity].tdl_curruntd=tdtmp;
                //最后将找到的进程放入rethd中以便返回
                retthd=tdtmp;

                goto return_step;
            }
            if(schdap->sda_thdlst[pity].tdl_curruntd!=NULL) 
            {
                retthd=schdap->sda_thdlst[pity].tdl_curruntd;
                goto return_step;
            }
        }
    }

    schdap->sda_prityidx=PRITY_MIN;
    //执行到这里还没有找到可运行的进程，只能返回空转进程
    retthd=krlsched_retn_idlethread();

return_step:

    hal_spinunlock_restflg_sti(&schdap->sda_lock,&cufg);
    return retthd;
}

//主函数
void krlschedul()
{
    
    thread_t* prev=krlsched_retn_currthread(),
    *next=krlsched_select_thread();

    save_to_new_context(next,prev);
    
    return;
}

void krlschdclass_add_thread(thread_t* thdp)
{   
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    cpuflg_t cufg;

    hal_spinlock_saveflg_cli(&schdap->sda_lock,&cufg);
    list_add(&thdp->td_list,&schdap->sda_thdlst[thdp->td_priority].tdl_lsth);
    schdap->sda_thdlst[thdp->td_priority].tdl_nr++;
    schdap->sda_threadnr++;
    hal_spinunlock_restflg_sti(&schdap->sda_lock,&cufg);
    
    hal_spinlock_saveflg_cli(&osschedcls.scls_lock,&cufg);
    osschedcls.scls_threadnr++;
    hal_spinunlock_restflg_sti(&osschedcls.scls_lock,&cufg);
    
    return;
}


void __to_new_context(thread_t* next,thread_t* prev)
{
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];

    schdap->sda_currtd=next;
    if(next->td_stus==TDSTUS_NEW)
    {
        next->td_stus=TDSTUS_RUN;
        
        retnfrom_first_sched(next);
    }

    return;
}

void save_to_new_context(thread_t* next,thread_t* prev)
{
    cpuflg_t cpuflg;
    //先保存CPSR寄存器中的值，然后关中断
    hal_disableirq_savecpuflg(&cpuflg);
    //保存CPU特权管理模式下的寄存器
    __asm__ __volatile__("stmfd sp!,{r0-r12,lr} \n\t"
         :::"memory"
    );
    __asm__ __volatile__(
        //保存当前的SPSR寄存器的值到prev->td_context.ctx_svcspsr中
         "mrs lr,spsr\n\t"
         "str lr,[%[PREV_SPSR]] \n\t"
         //保存当前的CPSR寄存器寄存器的值到prev->td_context.ctx_cpsr中
         "mrs lr,cpsr\n\t"
         "str lr,[%[PREV_CPSR]] \n\t"
         //装载next->td_context.ctx_svcspsr到当前的SPSR寄存器中
         "msr spsr,%[NEXT_SPSR] \n\t"
         //装载next->td_context.ctx_cpsr到当前的CPSR寄存器中
         "msr cpsr,%[NEXT_CPSR] \n\t"

         "str sp,[%[PREV_SVCSP]] \n\t"
         "ldr sp,[%[NEXT_SVCSP]] \n\t"
         //上面两行代码发生了进程PREV和进程NEXT的内核栈切换
         //下面的代码将使用进程NEXT的内核栈运行
         "mov r0,%[NEXT_TD] \n\t"
         "mov r1,%[PREV_TD] \n\t"
         "bl __to_new_context \n\t"
         :
         :[PREV_TD] "r" (prev), [NEXT_TD] "r" (next), 
         [PREV_SVCSP] "r" (&prev->td_context.ctx_svcsp),[PREV_SPSR] "r" (&prev->td_context.ctx_svcspsr),
         [PREV_CPSR] "r" (&prev->td_context.ctx_cpsr),
         [NEXT_SVCSP] "r" (&next->td_context.ctx_svcsp),[NEXT_SPSR] "r" (next->td_context.ctx_svcspsr),
         [NEXT_CPSR] "r" (next->td_context.ctx_cpsr)
         :"lr","cc","memory"
    );
    //恢复上次进程切换之前保存的寄存器组
    __asm__ __volatile__(
        "ldmfd sp!,{r0-r12,lr} \n\t"
         :::"memory"
    );
    //恢复CPSR寄存器
    hal_enableirq_restcpuflg(&cpuflg);
    return;
} 

void retnfrom_first_sched(thread_t* thrdp)
{

    __asm__ __volatile__(
        //把thrdp->td_context->ctx_svcspsr的值送到SPSR寄存器中
         "msr spsr,%[svcspsr]\n\t"
         //把thrdp->td_context.ctx_svcsp的值送到SP寄存器
         "mov sp,%[svcsp] \n\t"
         //把thrdp->td_context.ctx_lr的值送到LR寄存器中
         "mov lr,%[usrlr] \n\t"
         //以上SPSR，SP，LR寄存器都是CPU特权管理下的寄存器
         //把SP寄存器指向的内存块中的15个字加载到CPU用户模式下的r0^r14寄存器中
         "ldmia sp,{r0-lr}^ \n\t"
         ///平衡内核栈
         "add sp,sp,#60 \n\t"
         //把LR寄存器的值送给PC寄存器，这样就开始运行krlcpuidle_main函数了
         //同时会将当前模式下的SPSR复制到CPSR寄存器中，就改变了CPU的工作模式
         "movs pc,lr \n\t"
         :
         :[svcsp] "r" (thrdp->td_context.ctx_svcsp),[svcspsr] "r" (thrdp->td_context.ctx_svcspsr),
          [usrlr] "r" (thrdp->td_context.ctx_lr)
         : "cc","memory"
    );
}