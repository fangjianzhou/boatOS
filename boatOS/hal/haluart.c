
#include "seafarertypes.h"
#include "seafarerctrl.h"



void init_haluart()
{
    
    init_uart0();
    return;
}

void init_uart0()
{
    hal_io32_write(ULCON0_R,3); //设置串口0的通信模式，发送，接收格式，校验方式
    hal_io32_write(UCON0_R,5); // 设置串口0的时钟源，发送，接受
    hal_io32_write(UFCON0_R,0); // 不采用FIFO模式
    hal_io32_write(UMCON0_R,0); // 不使用控制流
    hal_io32_write(UBRDIV0_R,26); // 设置串口0的波特率为115200bit/s
    return;
}

void hal_uart0_putc(char_t c)
{
    //读状态寄存器，检测串口0发送器是否为空，不为空就循环检测，直到为空
    while(!(hal_io32_read(UTRSTAT0_R)&4));
    
    //把数据写到串口0的数据发送寄存器中
    hal_io32_write(UTXH0_R,c);
    return;
}


drvstus_t hal_uart_write(uint_t uart,void* buf,uint_t len)
{
    char_t* p=buf;
    cpuflg_t cpuflg;
    hal_disableirq_savecpuflg(&cpuflg);
    
    while(*p)
    {
          if(uart_send_char(uart,*p)==DFCERRSTUS)
          {
                
                hal_sysdie("uart err");
                return DFCERRSTUS;
          }
          p++;
    }
    hal_enableirq_restcpuflg(&cpuflg);
    return DFCOKSTUS;
}

drvstus_t hal_uart_read(uint_t uart,void* buf,uint_t* retlen)
{
    return DFCOKSTUS;
}

drvstus_t hal_uart_ioctrl(uint_t uart,uint_t ctrlcode,void* ctrdata)
{
    return DFCOKSTUS;
}


drvstus_t uart_send_char(uint_t uart,char_t ch)
{
    uint_t time=0;
    if(uart!=0)
    {
        return  DFCERRSTUS;
    }
    while(!(hal_io32_read(UTRSTAT0_R)&4))
    {
        if(time>0x100000)
        {
            return DFCERRSTUS;
        }
        time++;    
    }
    hal_io32_write(UTXH0_R,ch);
    
    return DFCOKSTUS;
}

drvstus_t uart_receive_char(uint_t uart,char_t* retch)
{
    return DFCOKSTUS;
}
