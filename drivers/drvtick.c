
#include "seafarertypes.h"
#include "seafarerctrl.h"

void init_s3c2440_timer4()
{
    u32_t cfgtmp=hal_io32_read(TCFG0_R);
    cfgtmp&=0xffff00ff;
    cfgtmp|=0xff00;
    hal_io32_write(TCFG0_R,cfgtmp);
    
    cfgtmp=hal_io32_read(TCFG1_R);
    cfgtmp&=(0xfff0ffff);
    hal_io32_write(TCFG1_R,cfgtmp);
    
    hal_io32_write(TCNTB4_R,0x41);
    
    cfgtmp=hal_io32_read(TCON_R);
    cfgtmp&=0xff8fffff;
    hal_io32_write(TCON_R,cfgtmp);
    
    cfgtmp=hal_io32_read(TCON_R);
    cfgtmp|=(0x700000);
    hal_io32_write(TCON_R,cfgtmp);
    
    cfgtmp=hal_io32_read(TCON_R);
    cfgtmp&=(~0x200000);
    hal_io32_write(TCON_R,cfgtmp);
    return;
}

void systick_set_driver(driver_t* drvp)
{
    drvp->drv_dipfun[IOIF_CODE_OPEN]=systick_open;
    drvp->drv_dipfun[IOIF_CODE_CLOSE]=systick_close;
    drvp->drv_dipfun[IOIF_CODE_READ]=systick_read;
    drvp->drv_dipfun[IOIF_CODE_WRITE]=systick_write;
    drvp->drv_dipfun[IOIF_CODE_LSEEK]=systick_lseek;
    drvp->drv_dipfun[IOIF_CODE_IOCTRL]=systick_ioctrl;
    drvp->drv_dipfun[IOIF_CODE_DEV_START]=systick_dev_start;
    drvp->drv_dipfun[IOIF_CODE_DEV_STOP]=systick_dev_stop;
    drvp->drv_dipfun[IOIF_CODE_SET_POWERSTUS]=systick_set_powerstus;
    drvp->drv_dipfun[IOIF_CODE_ENUM_DEV]=systick_enum_dev;
    drvp->drv_dipfun[IOIF_CODE_FLUSH]=systick_flush;
    drvp->drv_dipfun[IOIF_CODE_SHUTDOWN]=systick_shutdown;
    drvp->drv_name="systick0drv";
    return;
}

void systick_set_device(device_t* devp,driver_t* drvp)
{
    
    devp->dev_flgs=DEVFLG_SHARE;
    devp->dev_stus=DEVSTS_NORML;
    devp->dev_id.dev_mtype=SYSTICK_DEVICE;
    devp->dev_id.dev_stype=0;
    devp->dev_id.dev_nr=0;

    devp->dev_name="systick0";
    return;
}


drvstus_t systick_entry(driver_t* drvp,uint_t val,void* p)
{
    if(drvp==NULL)
    {
        return DFCERRSTUS;
    }
    //创建device_t结构的实例变量
    device_t* devp=new_device_dsc();
    if(devp==NULL)
    {
        return DFCERRSTUS;
    }
    //设置驱动程序数据结构和设备数据结构中的相关域
    systick_set_driver(drvp);
    systick_set_device(devp,drvp);
    //向驱动程序注册设备
    if(krldev_add_driver(devp,drvp)==DFCERRSTUS)
    {
        if(del_device_dsc(devp)==DFCERRSTUS)//注意释放资源。
        {
            return DFCERRSTUS;
        }
        return DFCERRSTUS;
    }
    //向seafarer内核注册设备
    if(krlnew_device(devp)==DFCERRSTUS)
    {
        if(del_device_dsc(devp)==DFCERRSTUS)//注意释放资源
        {
            return DFCERRSTUS;
        }
        return DFCERRSTUS;
    }
    //注册回调函数
    if(krlnew_devhandle(devp,systick_handle,MINT_IFDNR(SYSTICK_PHYINTLINE))==DFCERRSTUS)
    {
       
        return DFCERRSTUS;  //注意释放资源。
    }
    //初始化定时器设备
    init_s3c2440_timer4();
    
    //解除中断控制器对该位设备的中断屏蔽
    if(krlenable_intline(MINT_IFDNR(SYSTICK_PHYINTLINE))==DFCERRSTUS)
    { 
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}


drvstus_t systick_exit(driver_t* drvp,uint_t val,void* p)
{
    return DFCERRSTUS;
}

drvstus_t systick_handle(uint_t ift_nr,void* devp,void* sframe)
{
    krlthd_inc_tick(krlsched_retn_currthread());
	//printfk("systick_handle run!!\n\r");
    return DFCOKSTUS;
}



drvstus_t systick_open(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_close(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_read(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_write(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_lseek(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_ioctrl(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_dev_start(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_dev_stop(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_set_powerstus(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_enum_dev(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_flush(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t systick_shutdown(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}
