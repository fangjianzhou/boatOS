
#include "seafarertypes.h"
#include "seafarerctrl.h"


void init_krlcpuidle()
{
    new_cpuidle();
    krlcpuidle_start();
    return;
}

void krlcpuidle_start()
{
    
    uint_t cpuid=hal_retn_cpuid();
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];

    thread_t* tdp=schdap->sda_cpuidle;

    tdp->td_stus=TDSTUS_RUN;
    retnfrom_first_sched(tdp);
    return;
}
thread_t* new_cpuidle_thread()
{
    thread_t* ret_td=NULL;
    bool_t acs=FALSE;
    size_t usrstksz=DAFT_TDUSRSTKSZ,krlstksz=DAFT_TDKRLSTKSZ;
    adr_t usrstkadr=NULL,krlstkadr=NULL;
    //分配用户栈
    usrstkadr=krlnew(usrstksz);
    if(usrstkadr==NULL)
    {
        return NULL;
    }
    //分配内核栈
    krlstkadr=krlnew(krlstksz);
    if(krlstkadr==NULL)
    {
        if(krldelete(usrstkadr,usrstksz)==FALSE)
        {
            return NULL;
        }
        return NULL;
    }
    //分配进程描述符的函数
    ret_td=krlnew_thread_dsc();
    if(ret_td==NULL)
    {
        acs=krldelete(usrstkadr,usrstksz);
        acs=krldelete(krlstkadr,krlstksz);
        if(acs==FALSE)
        {
            return NULL;
        }
        return NULL;
    }
    //用户特权，实际上并没有实现进程权限检查
    ret_td->td_privilege=PRILG_USR;
    //最低优先级
    ret_td->td_priority=PRITY_MAX;
    //内核栈顶的开始地址
    ret_td->td_krlstktop=krlstkadr+(adr_t)(krlstksz-1);
    //内核栈的开始地址
    ret_td->td_krlstkstart=krlstkadr;
    //用户栈顶的开始地址
    ret_td->td_usrstktop=usrstkadr+(adr_t)(usrstksz-1);
    //用户栈的开始地址
    ret_td->td_usrstkstart=usrstkadr;
    krlthreadkrlsatck_init(ret_td,(void*)krlcpuidle_main,DAFT_CPSR,DAFT_CIDLESPSR);
    uint_t cpuid=hal_retn_cpuid();
    //以cpuid为下标获取schdata_t结构指针
    schdata_t* schdap=&osschedcls.scls_schda[cpuid];
    schdap->sda_cpuidle=ret_td;
    //标识当前正在运行的进程是空转进程
    schdap->sda_currtd=ret_td;
    return ret_td;
}

void new_cpuidle()
{
    thread_t* thp=new_cpuidle_thread();
    if(thp==NULL)
    {
        hal_sysdie("newcpuilde err");
    }
    printfk("CPUIDLETASK: %x\n\r",(uint_t)thp);
    return;    
}

void krlcpuidle_main()
{
    for(;;)
    {
        printfk("cpuidle is run!!\n\r");
        krlschedul();
    }
    return;
}
