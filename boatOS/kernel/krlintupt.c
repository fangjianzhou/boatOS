
#include "seafarertypes.h"
#include "seafarerctrl.h"



intserdsc_t* krladd_irqhandle(void* device,intflthandle_t handle,uint_t phyiline)
{
    if(device==NULL||handle==NULL)
    {
        return NULL;
    }
    //返回中断源描述符
    intfltdsc_t* intp=hal_retn_intfltdsc(phyiline);
    if(intp==NULL)
    {
        return NULL;    
    }
    //分配一个intserdsc_t
    intserdsc_t* serdscp=(intserdsc_t*)krlnew(sizeof(intserdsc_t));
    if(serdscp==NULL)
    {
        return NULL;
    }
    //初始化该intserdsc_t数据结构变量
    intserdsc_t_init(serdscp,0,intp,device,handle);

    //如果intserdsc_t加入到intfltdsc_t中是失败，则释放intserdsc_t数据结构变量的空间
    if(hal_add_ihandle(intp,serdscp)==FALSE)
    {
        
        if(krldelete((adr_t)serdscp,sizeof(intserdsc_t))==FALSE)
        {
            hal_sysdie("krladd_irqhandle ERR");
        }
        return NULL;
    }
    
    return serdscp;
}


drvstus_t krlenable_intline(uint_t ifdnr)
{
    
    return hal_enable_intline(ifdnr);
}

drvstus_t krldisable_intline(uint_t ifdnr)
{
 
    return hal_disable_intline(ifdnr);

}





